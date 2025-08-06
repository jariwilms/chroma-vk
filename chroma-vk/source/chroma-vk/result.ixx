module;

#include <vulkan/vulkan_raii.hpp>
#include <glfw/glfw3.h>

export module result;

import std;
import glm;

static VKAPI_ATTR vk::Bool32 VKAPI_CALL debug_callback(
    vk::DebugUtilsMessageSeverityFlagBitsEXT      message_severity,
    vk::DebugUtilsMessageTypeFlagsEXT             /*message_types*/,
    const vk::DebugUtilsMessengerCallbackDataEXT* callback_data,
    void*                                         /*user_data*/)
{
    if (message_severity <= vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo) return vk::False;

    std::println("{}", callback_data->pMessage);
    return vk::False;
}

namespace fox
{
    template<typename T, std::uint32_t N>
    using vector_t = glm::vec<N, T, glm::packed_highp>;

    using vector1u = fox::vector_t<std::uint32_t, 1u>;
    using vector2u = fox::vector_t<std::uint32_t, 2u>;
    using vector3u = fox::vector_t<std::uint32_t, 3u>;
    using vector4u = fox::vector_t<std::uint32_t, 4u>;

    using vector1f = fox::vector_t<std::float_t, 1u>;
    using vector2f = fox::vector_t<std::float_t, 2u>;
    using vector3f = fox::vector_t<std::float_t, 3u>;
    using vector4f = fox::vector_t<std::float_t, 4u>;

    template<typename T>
    auto select(bool test, T&& true_result, T&& false_result) -> auto
    {
        if   (test) return std::forward<T>(true_result );
        else        return std::forward<T>(false_result);
    }
}
export namespace vk
{
    constexpr auto is_debug_build           = _DEBUG;
    constexpr auto maximum_frames_in_flight = std::uint32_t{ 2u };

    class application
    {
    public:
        application()
        {
            create_window();

            create_context();
            create_instance();
            create_surface();
            select_physical_device();
            create_logical_device();
            create_swap_chain();
            create_image_views();
            create_graphics_pipeline();
            create_command_pool();
            create_command_buffers();
            create_synchronization_objects();

            loop();
            cleanup();
        }

        void create_window()
        {
            glfwInit();
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

            window_ = glfwCreateWindow(800u, 600u, "Vulkan", nullptr, nullptr);

            glfwSetWindowUserPointer      (window_, this                     );
            glfwSetFramebufferSizeCallback(window_, framebufferResizeCallback);
        }

        static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {

            auto app = reinterpret_cast<application*>(glfwGetWindowUserPointer(window));
            app->frame_buffer_resized = true;
        }

        void create_context() 
        {
            context_ = std::make_unique<vk::raii::Context>();
        }
        void create_instance() 
        {
                  auto check_layers                  = [&](const std::vector<const char*>& requested_layers, const std::vector<vk::LayerProperties>& layer_properties) -> bool
                {
                    return std::ranges::all_of(requested_layers, [&](const char* name) -> bool
                        {
                            return std::ranges::any_of(layer_properties, [&](const vk::LayerProperties& property) -> bool
                                {
                                    return !strcmp(property.layerName.data(), name);
                                });
                        });
                };

            const auto application_info              = vk::ApplicationInfo{
                    "Kloete Tutorial", std::uint32_t{ 0u },
                    "Fox Engine"     , std::uint32_t{ 0u },
                    vk::ApiVersion14
            };
            const auto required_layers               = std::vector<const char*>{
                "VK_LAYER_KHRONOS_validation",
            };
            const auto required_extensions           = std::invoke([&]() -> std::vector<const char*>
                {
                    auto glfw_extension_count              = std::uint32_t{ 0u };
                    auto required_glfw_instance_extensions = std::span  <const char*>{ glfwGetRequiredInstanceExtensions(&glfw_extension_count), glfw_extension_count };
                    auto extensions                        = std::vector<const char*>{ std::from_range, required_glfw_instance_extensions };

                    if constexpr (is_debug_build) extensions.emplace_back(vk::EXTDebugUtilsExtensionName);

                    return extensions;
                });
            const auto instance_layer_properties     = context_->enumerateInstanceLayerProperties    ();
            const auto instance_extension_properties = context_->enumerateInstanceExtensionProperties();

            if (!check_layers(required_layers, instance_layer_properties)) throw std::runtime_error{ "Missing required layers!" };
            
            const auto debug_messenger_create_info   = vk::DebugUtilsMessengerCreateInfoEXT{
                vk::DebugUtilsMessengerCreateFlagBitsEXT{}, 
                vk::DebugUtilsMessageSeverityFlagsEXT{ 
                    vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose | 
                    vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning | 
                    vk::DebugUtilsMessageSeverityFlagBitsEXT::eError   }, 
                vk::DebugUtilsMessageTypeFlagsEXT{ 
                    vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral     | 
                    vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation  | 
                    vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance }, 
                debug_callback
            };
            const auto instance_create_info          = vk::InstanceCreateInfo{ 
                vk::InstanceCreateFlags{}   , &application_info  , 
                required_layers             , required_extensions, 
                &debug_messenger_create_info
            };

            instance_                                = std::make_unique<vk::raii::Instance              >(context_ ->createInstance              (instance_create_info       ));
            debug_messenger_                         = std::make_unique<vk::raii::DebugUtilsMessengerEXT>(instance_->createDebugUtilsMessengerEXT(debug_messenger_create_info));
        }
        void create_surface()
        {
            auto glfw_surface = VkSurfaceKHR{};
            if (glfwCreateWindowSurface(instance_->operator vk::Instance(), window_, nullptr, &glfw_surface) != VkResult::VK_SUCCESS) throw std::runtime_error{ "Failed to create surface!" };
            
            surface_ = std::make_unique<vk::raii::SurfaceKHR>(*instance_, glfw_surface);
        }
        void select_physical_device()
        {
            physical_device_                    = std::make_unique<vk::raii::PhysicalDevice>(std::invoke([&]() -> vk::raii::PhysicalDevice
                {
                    const auto physical_devices            = instance_->enumeratePhysicalDevices();
                    if (physical_devices.empty()) throw std::runtime_error{ "No physical device found!" };

                    const auto required_device_extensions = std::vector{
                        vk::KHRSwapchainExtensionName, 
                        vk::KHRSpirv14ExtensionName, 
                        vk::KHRSynchronization2ExtensionName, 
                        vk::KHRCreateRenderpass2ExtensionName, 
                    };
                    const auto candidates                  = std::invoke([&]() -> std::map<std::uint32_t, vk::raii::PhysicalDevice>
                        {
                            auto result = std::map<std::uint32_t, vk::raii::PhysicalDevice>{};
                            std::ranges::for_each(physical_devices, [&](const vk::raii::PhysicalDevice& physical_device)
                                {
                                          auto score                       = std::uint32_t { 0u };
                                          auto max_video_memory            = vk::DeviceSize{ 0u };

                                    const auto features                    = physical_device.getFeatures                       ();
                                    const auto properties                  = physical_device.getProperties                     ();
                                    const auto memory_properties           = physical_device.getMemoryProperties               ();
                                    const auto queue_families              = physical_device.getQueueFamilyProperties          ();
                                    const auto device_extension_properties = physical_device.enumerateDeviceExtensionProperties();

                                    if (properties.apiVersion < vk::ApiVersion14)                                            return;
                                    if (!std::ranges::any_of(queue_families            , [&](const auto& family) -> bool
                                        { 
                                            return !(family.queueFlags & vk::QueueFlagBits::eGraphics); 
                                        })) return;
                                    if (!std::ranges::all_of(required_device_extensions, [&](const char* name  ) -> bool
                                        {
                                            return std::ranges::any_of(device_extension_properties, [&](const vk::ExtensionProperties& property) -> bool
                                                {
                                                    return !strcmp(property.extensionName.data(), name);
                                                });
                                        })) return;



                                         if (properties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu  ) score += 8;
                                    else if (properties.deviceType == vk::PhysicalDeviceType::eIntegratedGpu) score += 2;
                                    else                                                                      score += 1;

                                    std::ranges::for_each(std::views::iota(0u, memory_properties.memoryHeapCount), [&](auto index)
                                        {
                                            if (memory_properties.memoryHeaps[index].flags & vk::MemoryHeapFlagBits::eDeviceLocal)
                                                max_video_memory = std::max(max_video_memory, memory_properties.memoryHeaps[index].size);
                                        });

                                    score += static_cast<std::uint32_t>(max_video_memory / static_cast<std::uint32_t>(std::pow(2u, 30u))); //1 Gigabyte
                                    result.emplace(score, physical_device);
                                });

                            return result;
                        });

                    if (candidates.empty()) throw std::runtime_error{ "No suitable physical device found!" };
                    return candidates.rbegin()->second;
                }));

        }
        void create_logical_device()
        {
            queue_index_                                       = std::numeric_limits<std::uint32_t>::max();

            for (const auto [index, value] : std::views::enumerate(physical_device_->getQueueFamilyProperties()))
            {
                if (!(value.queueFlags & vk::QueueFlagBits::eGraphics))                                          break;
                if (!physical_device_->getSurfaceSupportKHR(static_cast<std::uint32_t>(index), *surface_.get())) break;

                queue_index_ = static_cast<std::uint32_t>(index);
            }

            if (queue_index_ == std::numeric_limits<std::uint32_t>::max()) throw std::runtime_error{ "Could not find a queue that supports graphics and presentation!" };

                  auto queue_priority                          = std::float_t{};
            const auto required_logical_device_extensions      = std::vector{
                vk::KHRSwapchainExtensionName, 
                vk::KHRSpirv14ExtensionName, 
                vk::KHRSynchronization2ExtensionName, 
                vk::KHRCreateRenderpass2ExtensionName, 
                vk::KHRShaderDrawParametersExtensionName, 
            };
            const auto logical_device_queue_create_info        = vk::DeviceQueueCreateInfo{ 
                vk::DeviceQueueCreateFlags{}, 
                queue_index_                , 
                std::uint32_t{ 1u }         , &queue_priority
            };
            const auto feature_chain                           = vk::StructureChain<vk::PhysicalDeviceFeatures2, vk::PhysicalDeviceVulkan13Features, vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT> {
                vk::PhysicalDeviceFeatures2                      {                                                          }, 
                vk::PhysicalDeviceVulkan13Features               { {}  , {}, {}, {}, {}, {}, {}, {}, {}, true, {}, {}, true }, 
                vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT{ true,                                                    }, 
            };
            const auto logical_device_create_info              = vk::DeviceCreateInfo{
                vk::DeviceCreateFlags{}                                         , 
                std::uint32_t{ 1u }                                             , &logical_device_queue_create_info                , 
                {}                                                              , {}                                               , 
                static_cast<uint32_t>(required_logical_device_extensions.size()), required_logical_device_extensions.data()        , 
                {}                                                              , &feature_chain.get<vk::PhysicalDeviceFeatures2>(), 
            };

            logical_device_ = std::make_unique<vk::raii::Device>(*physical_device_, logical_device_create_info                     );
            queue_          = std::make_unique<vk::raii::Queue >(*logical_device_ , queue_index_              , std::uint32_t{ 0u });
        }
        void create_swap_chain()
        {
            const auto surface_capabilities = physical_device_->getSurfaceCapabilitiesKHR(*surface_);
            const auto available_formats    = physical_device_->getSurfaceFormatsKHR     (*surface_);

            swap_chain_image_format_ = std::invoke([&]() -> vk::Format
                {
                    const auto iterator = std::ranges::find_if(available_formats, [](const auto& surface) 
                        {
                            return surface.format == vk::Format::eB8G8R8A8Srgb && surface.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear;
                        });
                    
                    return iterator != available_formats.end() ? iterator->format : available_formats.at(0u).format;
                });
            swap_chain_extent_       = std::invoke([&]() -> vk::Extent2D
                {
                    if (surface_capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) return surface_capabilities.currentExtent;

                    std::int32_t width, height;
                    glfwGetFramebufferSize(window_, &width, &height);

                    return 
                    {
                        std::clamp<uint32_t>(width , surface_capabilities.minImageExtent.width , surface_capabilities.maxImageExtent.width ), 
                        std::clamp<uint32_t>(height, surface_capabilities.minImageExtent.height, surface_capabilities.maxImageExtent.height)
                    };
                });

            const auto maximum_image_count  = std::max(3u, surface_capabilities.minImageCount);
            const auto minimum_image_count  = fox::select(
                surface_capabilities.maxImageCount, 
                std::min(maximum_image_count, surface_capabilities.maxImageCount), 
                maximum_image_count);

            const auto presentation_mode      = std::ranges::any_of(physical_device_->getSurfacePresentModesKHR(*surface_), [](const vk::PresentModeKHR value)
                { 
                    return vk::PresentModeKHR::eMailbox == value; 
                }) ? vk::PresentModeKHR::eMailbox : vk::PresentModeKHR::eFifo;
            const auto swap_chain_create_info = vk::SwapchainCreateInfoKHR{
                vk::SwapchainCreateFlagsKHR{}        , *surface_,
                minimum_image_count                  , swap_chain_image_format_,
                vk::ColorSpaceKHR::eSrgbNonlinear    , swap_chain_extent_,
                std::uint32_t{ 1u }                  , vk::ImageUsageFlagBits::eColorAttachment,
                vk::SharingMode::eExclusive          , {},
                surface_capabilities.currentTransform, vk::CompositeAlphaFlagBitsKHR::eOpaque,
                presentation_mode                    , vk::True
            };

            swap_chain_        = std::make_unique<vk::raii::SwapchainKHR>(*logical_device_, swap_chain_create_info);
            swap_chain_images_ = swap_chain_->getImages();
        }
        void create_image_views()
        {
            auto image_view_create_info = vk::ImageViewCreateInfo{ 
                vk::ImageViewCreateFlags{}, vk::Image{}, 
                vk::ImageViewType::e2D    , swap_chain_image_format_, 
                vk::ComponentMapping{}    , 
                vk::ImageSubresourceRange{ 
                    vk::ImageAspectFlagBits::eColor, std::uint32_t{ 0u }, std::uint32_t{ 1u }, std::uint32_t{ 0u }, std::uint32_t{ 1u }
                } 
            };
            
            std::ranges::for_each(swap_chain_images_, [&](const vk::Image& image)
                {
                    image_view_create_info.image = image;
                    swap_chain_image_views_.emplace_back(*logical_device_, image_view_create_info);
                });
        }
        void create_graphics_pipeline()
        {
                  auto read_file                             = [](const std::filesystem::path& path) -> std::vector<std::uint8_t>
                {
                    std::ifstream file(path, std::ios::binary);
                    if (!file) throw std::invalid_argument{ "Could not open file!" };

                    file.seekg(0, std::ios::end);
                    const auto file_size = static_cast<std::size_t>(file.tellg());
                    file.seekg(0, std::ios::beg);

                    auto buffer = std::vector<uint8_t>(file_size);
                    file.read(reinterpret_cast<char*>(buffer.data()), file_size);
                    if (!file) throw std::runtime_error{ "Could not read file!" };

                    return buffer;
                };

            const auto shader_file                           = std::filesystem::path{ "slang.spv" };
            const auto shader_module                         = std::invoke([&](const std::vector<std::uint8_t>& code) -> vk::raii::ShaderModule
                {
                    const auto shader_module_create_info = vk::ShaderModuleCreateInfo{ 
                        vk::ShaderModuleCreateFlags{}, 
                        code.size() * sizeof(std::uint8_t), std::bit_cast<const uint32_t*>(code.data()) 
                    };

                    return vk::raii::ShaderModule{ *logical_device_, shader_module_create_info };
                }, read_file(shader_file));

            const auto vertex_shader_stage_info              = vk::PipelineShaderStageCreateInfo{ 
                vk::PipelineShaderStageCreateFlags{}, 
                vk::ShaderStageFlagBits::eVertex, 
                shader_module, 
                "vertMain" 
            };
            const auto fragment_shader_stage_info            = vk::PipelineShaderStageCreateInfo{ 
                vk::PipelineShaderStageCreateFlags{}, 
                vk::ShaderStageFlagBits::eFragment, 
                shader_module, 
                "fragMain" 
            };
            const auto shader_stages                         = std::array<vk::PipelineShaderStageCreateInfo, 2u>{ 
                vertex_shader_stage_info  , 
                fragment_shader_stage_info, 
            };

            const auto input_assembly_state_create_info      = vk::PipelineInputAssemblyStateCreateInfo{
                vk::PipelineInputAssemblyStateCreateFlags{}, 
                vk::PrimitiveTopology::eTriangleList       , 
            };
            const auto vertex_input_state_create_info        = vk::PipelineVertexInputStateCreateInfo{};
            const auto viewport_state_create_info            = vk::PipelineViewportStateCreateInfo{ 
                vk::PipelineViewportStateCreateFlags{}, 
                std::uint32_t{ 1u }, nullptr          , 
                std::uint32_t{ 1u }, nullptr          , 
            };
            const auto rasterization_state_create_info       = vk::PipelineRasterizationStateCreateInfo{ 
                vk::PipelineRasterizationStateCreateFlags{}           , 
                vk::False                , vk::False                  , 
                vk::PolygonMode::eFill   , vk::CullModeFlagBits::eBack, 
                vk::FrontFace::eClockwise, vk::False                  , 
                {}, {}, {}               , std::float_t{1.0f}         , 
            };
            const auto multisample_create_info               = vk::PipelineMultisampleStateCreateInfo{ 
                vk::PipelineMultisampleStateCreateFlags{}, 
                vk::SampleCountFlagBits::e1, vk::False 
            };
            const auto pipeline_color_blend_attachment_state = vk::PipelineColorBlendAttachmentState{ //bruh
                vk::False, {}, {}, {}, {}, {}, {}, 
                vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA
            };

            const auto color_blending_state_create_info      = vk::PipelineColorBlendStateCreateInfo{ 
                vk::PipelineColorBlendStateCreateFlags{}  , 
                vk::False          , vk::LogicOp::eCopy   , 
                std::uint32_t{ 1u }, &pipeline_color_blend_attachment_state, 
            };
            const auto dynamic_states                        = std::vector{
                vk::DynamicState::eViewport, 
                vk::DynamicState::eScissor , 
            };
            const auto pipeline_dynamic_state_create_info    = vk::PipelineDynamicStateCreateInfo{ 
                vk::PipelineDynamicStateCreateFlags{}, 
                static_cast<uint32_t>(dynamic_states.size()), dynamic_states.data() 
            };
            const auto pipeline_layout_info                  = vk::PipelineLayoutCreateInfo{
                vk::PipelineLayoutCreateFlags{}, 
                std::uint32_t{ 0u }, nullptr, 
                std::uint32_t{ 0u }, 
            };
            
            pipeline_layout_                                 = std::make_unique<vk::raii::PipelineLayout>(*logical_device_, pipeline_layout_info);

            const auto pipeline_rendering_create_info        = vk::PipelineRenderingCreateInfo{ 
                {}, std::uint32_t{ 1u }, &swap_chain_image_format_, 
            };
            const auto pipeline_create_info                  = vk::GraphicsPipelineCreateInfo{ 
                vk::PipelineCreateFlags{}          , 
                std::uint32_t{ 2u }                , shader_stages.data()             , 
                &vertex_input_state_create_info    , &input_assembly_state_create_info, 
                {}                                 , &viewport_state_create_info      , 
                &rasterization_state_create_info   , &multisample_create_info         , 
                {}                                 , &color_blending_state_create_info, 
                &pipeline_dynamic_state_create_info, *pipeline_layout_                , 
                {}, {}, {}, {}                     , &pipeline_rendering_create_info  , 
            };

            pipeline_ = std::make_unique<vk::raii::Pipeline>(*logical_device_, nullptr, pipeline_create_info);
        }
        void create_command_pool()
        {
            const auto command_pool_create_info = vk::CommandPoolCreateInfo{
                vk::CommandPoolCreateFlagBits::eResetCommandBuffer,
                queue_index_, 
            };

            command_pool_ = std::make_unique<vk::raii::CommandPool>(*logical_device_, command_pool_create_info);
        }
        void create_command_buffers()
        {
            const auto command_buffer_allocate_info = vk::CommandBufferAllocateInfo{ 
                *command_pool_                  , 
                vk::CommandBufferLevel::ePrimary, 
                maximum_frames_in_flight        , 
            };
            command_buffers_ = vk::raii::CommandBuffers(*logical_device_, command_buffer_allocate_info);
        }
        void create_synchronization_objects()
        {
            std::ranges::for_each(std::views::iota(0u, swap_chain_images_.size()), [&](auto)
                {
                    present_complete_semaphore_  .emplace_back(*logical_device_, vk::SemaphoreCreateInfo());
                    rendering_finished_semaphore_.emplace_back(*logical_device_, vk::SemaphoreCreateInfo());
                });
            std::ranges::for_each(std::views::iota(0u, maximum_frames_in_flight ), [&](auto)
                {
                    in_flight_fences_.emplace_back(*logical_device_, vk::FenceCreateInfo{ vk::FenceCreateFlagBits::eSignaled });
                });
        }
        void clean_up_swap_chain() {

            swap_chain_image_views_.clear();
            swap_chain_ = nullptr;
        }
        void recreate_swap_chain() 
        {
            int width = 0, height = 0;
            glfwGetFramebufferSize(window_, &width, &height);

            while (width == 0 || height == 0) 
            {
                glfwGetFramebufferSize(window_, &width, &height);
                glfwWaitEvents();
            }

            logical_device_->waitIdle();

            clean_up_swap_chain();
            create_swap_chain  ();
            create_image_views ();
        }



        void loop()
        {
            auto transition_image_layout = [&](
                std::uint32_t           image_index    , 
                std::size_t             current_frame  , 
                vk::ImageLayout         old_layout     ,
                vk::ImageLayout         new_layout     ,
                vk::AccessFlags2        src_access_mask,
                vk::AccessFlags2        dst_access_mask,
                vk::PipelineStageFlags2 src_stage_mask ,
                vk::PipelineStageFlags2 dst_stage_mask ) 
                {
                    const auto barrier         = vk::ImageMemoryBarrier2{
                        src_stage_mask         , src_access_mask, 
                        dst_stage_mask         , dst_access_mask, 
                        old_layout             , new_layout, 
                        VK_QUEUE_FAMILY_IGNORED, VK_QUEUE_FAMILY_IGNORED, 
                        swap_chain_images_.at(image_index), 
                        vk::ImageSubresourceRange{
                            vk::ImageAspectFlagBits::eColor, 
                            std::uint32_t { 0u }, std::uint32_t { 1u }, 
                            std::uint32_t { 0u }, std::uint32_t { 1u }, 
                        }
                    };
                    const auto dependency_info = vk::DependencyInfo{
                        vk::DependencyFlags{}, {}, {}, {}, {}, 
                        std::uint32_t{ 1u }, &barrier
                    };
                    
                    command_buffers_[current_frame].pipelineBarrier2(dependency_info);
                };

            auto record_command_buffer = [&](std::uint32_t image_index, std::size_t current_frame)
                {
                    command_buffers_.at(current_frame).begin({});

                    transition_image_layout(
                        image_index                                      , current_frame                           , 
                        vk::ImageLayout           ::eUndefined           , vk::ImageLayout::eColorAttachmentOptimal, {}, 
                        vk::AccessFlagBits2       ::eColorAttachmentWrite, 
                        vk::PipelineStageFlagBits2::eTopOfPipe           , vk::PipelineStageFlagBits2::eColorAttachmentOutput);

                    const auto clear_color               = vk::ClearColorValue(0.0f, 0.0f, 0.0f, 1.0f);
                    const auto rendering_attachment_info = vk::RenderingAttachmentInfo{
                        swap_chain_image_views_.at(image_index)       , 
                        vk::ImageLayout      ::eColorAttachmentOptimal, 
                        {}, {}, {}                                    , 
                        vk::AttachmentLoadOp ::eClear                 , 
                        vk::AttachmentStoreOp::eStore                 , 
                        clear_color                                    , 
                    };
                    const auto rendering_info            = vk::RenderingInfo{
                        vk::RenderingFlags{}                                  , 
                        vk::Rect2D{ vk::Offset2D{ 0, 0 }, swap_chain_extent_ }, 
                        std::uint32_t{ 1u }                                   , {}             , 
                        std::uint32_t{ 1u }                                   , &rendering_attachment_info, 
                    };
                    
                    command_buffers_.at(current_frame).beginRendering(rendering_info);
                    command_buffers_.at(current_frame).bindPipeline  (vk::PipelineBindPoint::eGraphics, *pipeline_);
                    command_buffers_.at(current_frame).setViewport   (0, vk::Viewport(0.0f, 0.0f, static_cast<float>(swap_chain_extent_.width), static_cast<float>(swap_chain_extent_.height), 0.0f, 1.0f));
                    command_buffers_.at(current_frame).setScissor    (0, vk::Rect2D(vk::Offset2D(0, 0), swap_chain_extent_));
                    command_buffers_.at(current_frame).draw          (3, 1, 0, 0);
                    command_buffers_.at(current_frame).endRendering  ();

                    transition_image_layout(
                        image_index                                       , current_frame                            , 
                        vk::ImageLayout::eColorAttachmentOptimal          , vk::ImageLayout::ePresentSrcKHR          , 
                        vk::AccessFlagBits2::eColorAttachmentWrite        , {}                                       , 
                        vk::PipelineStageFlagBits2::eColorAttachmentOutput, vk::PipelineStageFlagBits2::eBottomOfPipe);

                    command_buffers_.at(current_frame).end();
                };

            auto current_frame   = std::size_t{ 0u };
            auto semaphore_index = std::size_t{ 0u };

            while (!glfwWindowShouldClose(window_)) {
                glfwPollEvents();

                while (vk::Result::eTimeout == logical_device_->waitForFences(*in_flight_fences_[current_frame], vk::True, UINT64_MAX));
                auto [result, image_index] = swap_chain_->acquireNextImage(UINT64_MAX, *present_complete_semaphore_[semaphore_index], nullptr);

                if (result == vk::Result::eErrorOutOfDateKHR) 
                {
                    recreate_swap_chain();
                    continue;
                }
                if (result != vk::Result::eSuccess && result != vk::Result::eSuboptimalKHR)
                    throw std::runtime_error("failed to acquire swap chain image!");

                logical_device_->resetFences(*in_flight_fences_[current_frame]);
                command_buffers_[current_frame].reset();
                record_command_buffer(image_index, current_frame);

                const auto wait_destination_stage_mask = vk::PipelineStageFlags{ vk::PipelineStageFlagBits::eColorAttachmentOutput };
                const auto submit_info                 = vk::SubmitInfo{
                    std::uint32_t{ 1u }      , std::addressof(*present_complete_semaphore_  [semaphore_index]), 
                    &wait_destination_stage_mask, 
                    std::uint32_t{ 1u }      , std::addressof(*command_buffers_             [current_frame  ]), 
                    std::uint32_t{ 1u }      , std::addressof(*rendering_finished_semaphore_[image_index     ]), 
                };
                queue_->submit(submit_info, *in_flight_fences_[current_frame]);

                const auto present_info                = vk::PresentInfoKHR{ 
                    std::uint32_t{ 1u }        , std::addressof(*rendering_finished_semaphore_.at(image_index)), 
                    std::uint32_t{ 1u }        , &swap_chain_->operator*(),
                    std::addressof(image_index), 
                };

                try //Disable vulkan exceptions? Calling presentKHR WILL throw an exception if the framebuffer is resized
                {
                    std::ignore = queue_->presentKHR(present_info);
                }
                catch(vk::OutOfDateKHRError) 
                {
                    frame_buffer_resized = false;
                    recreate_swap_chain();
                }

                semaphore_index                        = ++semaphore_index % present_complete_semaphore_.size();
                current_frame                          = ++current_frame   % maximum_frames_in_flight;
            }


            logical_device_->waitIdle();
        }
        void cleanup()
        {
            glfwDestroyWindow(window_);
            glfwTerminate();
        }

    private:
        std::unique_ptr<vk::raii::Context               > context_;
        std::unique_ptr<vk::raii::Instance              > instance_;
        std::unique_ptr<vk::raii::DebugUtilsMessengerEXT> debug_messenger_;
        std::unique_ptr<vk::raii::SurfaceKHR            > surface_;
        std::unique_ptr<vk::raii::PhysicalDevice        > physical_device_;
        std::unique_ptr<vk::raii::Device                > logical_device_;
        std::unique_ptr<vk::raii::Queue                 > queue_;
        std::unique_ptr<vk::raii::SwapchainKHR          > swap_chain_;
        std::unique_ptr<vk::raii::PipelineLayout        > pipeline_layout_;
        std::unique_ptr<vk::raii::Pipeline              > pipeline_;
        std::unique_ptr<vk::raii::CommandPool           > command_pool_;

        vk::Format                                        swap_chain_image_format_;
        vk::Extent2D                                      swap_chain_extent_;

        std::vector<vk::Image>                            swap_chain_images_; //remove? is just swap_chain_->getImages()
        std::vector<vk::raii::ImageView>                  swap_chain_image_views_;
        std::vector<vk::raii::CommandBuffer>              command_buffers_;
        std::vector<vk::raii::Semaphore>                  present_complete_semaphore_;
        std::vector<vk::raii::Semaphore>                  rendering_finished_semaphore_;
        std::vector<vk::raii::Fence>                      in_flight_fences_;

        std::uint32_t                                     queue_index_;
        bool                                              frame_buffer_resized;
        
        GLFWwindow*                                       window_;
    };
}
