//module;
//
//#define VULKAN_HPP_NO_TO_STRING
//
//#include <vulkan/vulkan_raii.hpp>
//#include <glfw/glfw3.h>
//
//export module fox.vulkan;
//
//import std;
//
//static VKAPI_ATTR vk::Bool32 VKAPI_CALL debug_callback(
//    vk::DebugUtilsMessageSeverityFlagBitsEXT      message_severity, 
//    vk::DebugUtilsMessageTypeFlagsEXT             /*message_types*/,
//    const vk::DebugUtilsMessengerCallbackDataEXT* callback_data, 
//    void*                                         /*user_data*/)
//{
//    if (message_severity <= vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo) return vk::False;
//
//    std::println("{}", callback_data->pMessage);
//    return vk::False;
//}
//
//template<bool B>
//constexpr auto select(auto true_result, auto false_result) -> auto
//{
//    if   constexpr (B) return true_result ;
//    else               return false_result;
//}
//
//export namespace vk
//{
//#ifndef _DEBUG
//#define _DEBUG 0
//#endif
//
//    constexpr auto debug_build = static_cast<bool>(_DEBUG);
//
//    class context
//    {
//    public:
//        context()
//        {
//            glfwInit();
//
//            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
//            glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
//
//            window_ = glfwCreateWindow(800u, 600u, "Vulkan", nullptr, nullptr);
//
//
//
//
//
//                 auto check_layers                        = [](const std::vector<const char*>& requested_layers         , const std::vector<vk::LayerProperties>& layer_properties             ) -> bool
//                {
//                    return std::ranges::all_of(requested_layers, [&](const char* name) -> bool
//                        {
//                            return std::ranges::any_of(layer_properties, [&](const vk::LayerProperties& property) -> bool
//                                {
//                                    return !strcmp(property.layerName.data(), name);
//                                });
//                        });
//                };
//                 auto check_queues                        = [](const std::vector<vk::QueueFlagBits>& requested_queues, const std::vector<vk::QueueFamilyProperties>& queue_family_properties) -> bool
//                     {
//                         return std::ranges::all_of(requested_queues, [&](vk::QueueFlagBits flags) -> bool
//                             {
//                                 return std::ranges::any_of(queue_family_properties, [&](const vk::QueueFamilyProperties& property) -> bool
//                                     {
//                                         return static_cast<bool>(property.queueFlags & flags);
//                                     });
//                             });
//                     };
//
//            context_                                      = std::make_unique<vk::raii::Context>();
//            
//            const auto required_layers                    = std::vector<const char*>{
//                "VK_LAYER_KHRONOS_validation", 
//            };
//            const auto required_extensions                = std::invoke([&]() ->std::vector<const char*>
//                {
//                    auto glfw_extension_count              = std::uint32_t{ 0u };
//                    auto required_glfw_instance_extensions = std::span  <const char*>{ glfwGetRequiredInstanceExtensions(&glfw_extension_count), glfw_extension_count };
//                    auto extensions                        = std::vector<const char*>{ std::from_range, required_glfw_instance_extensions };
//
//                    if constexpr (debug_build) extensions.emplace_back(vk::EXTDebugUtilsExtensionName);
//
//                    return extensions;
//                });
//            const auto instance_layer_properties          = context_->enumerateInstanceLayerProperties    ();
//            const auto instance_extension_properties      = context_->enumerateInstanceExtensionProperties();
//
//            if (!check_layers(required_layers, instance_layer_properties)) throw std::runtime_error{ "Missing required layers!" };
//
//            const auto application_info                   = vk::ApplicationInfo{
//                "Vulkan", 1u,  
//                "Fox"   , 1u, 
//                VK_API_VERSION_1_4, 
//            };
//            const auto debug_messenger_create_info        = vk::DebugUtilsMessengerCreateInfoEXT{
//                vk::DebugUtilsMessengerCreateFlagBitsEXT{}, 
//                vk::DebugUtilsMessageSeverityFlagsEXT{ 
//                    vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose | 
//                    vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning | 
//                    vk::DebugUtilsMessageSeverityFlagBitsEXT::eError   }, 
//                vk::DebugUtilsMessageTypeFlagsEXT{ 
//                    vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral     | 
//                    vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation  | 
//                    vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance }, 
//                debug_callback
//            };
//            const auto instance_create_info               = vk::InstanceCreateInfo{ 
//                vk::InstanceCreateFlags{}   , &application_info  , 
//                required_layers             , required_extensions, 
//                &debug_messenger_create_info
//            };
//
//            instance_                                     = std::make_unique<vk::raii::Instance              >(context_->createInstance(instance_create_info));
//            debug_messenger_                              = std::make_unique<vk::raii::DebugUtilsMessengerEXT>(*instance_, debug_messenger_create_info       );
//
//                  auto glfw_surface                       = VkSurfaceKHR{};
//            if (glfwCreateWindowSurface(instance_->operator vk::Instance(), window_, nullptr, &glfw_surface) != VkResult::VK_SUCCESS) throw std::runtime_error{ "Failed to create surface!" };
//
//            surface_                                      = std::make_unique<vk::raii::SurfaceKHR>(*instance_, glfw_surface);
//
//            const auto physical_devices                   = instance_->enumeratePhysicalDevices();
//            const auto physical_device                    = std::invoke([&](const std::vector<vk::raii::PhysicalDevice>& physical_devices) -> vk::raii::PhysicalDevice
//                {
//                    if (physical_devices.empty()) throw std::runtime_error{ "No physical devices found!" };
//
//                    auto candidates = std::map<std::uint32_t, vk::raii::PhysicalDevice>{};
//                    std::ranges::for_each(physical_devices, [&](const vk::raii::PhysicalDevice& device)
//                        {
//                            const auto properties        = device.getProperties();
//                            const auto memory_properties = device.getMemoryProperties();
//                            const auto features          = device.getFeatures  ();
//
//                                  auto score             = std::uint32_t { 0u };
//                                  auto max_video_memory  = vk::DeviceSize{ 0u };
//                            const auto gigabyte          = static_cast<std::uint32_t>(std::pow(2u, 30u));
//                            
//                                 if (properties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu  ) score += 4;
//                            else if (properties.deviceType == vk::PhysicalDeviceType::eIntegratedGpu) score += 2;
//                            else                                                                      score += 1;
//
//                            std::ranges::for_each(std::views::iota(0u, memory_properties.memoryHeapCount), [&](auto index)
//                                {
//                                    if (memory_properties.memoryHeaps[index].flags & vk::MemoryHeapFlagBits::eDeviceLocal)
//                                        max_video_memory = std::max(max_video_memory, memory_properties.memoryHeaps[index].size);
//                                });
//
//                            score += static_cast<std::uint32_t>(max_video_memory / gigabyte);
//                            candidates.emplace(score, device);
//                        });
//
//                    return candidates.rbegin()->second;
//                }, physical_devices);
//            const auto requested_queue_properties         = std::vector<vk::QueueFlagBits>{ vk::QueueFlagBits::eGraphics, vk::QueueFlagBits::eCompute };
//            const auto queue_family_properties            = physical_device.getQueueFamilyProperties();
//
//            if (!check_queues(requested_queue_properties, queue_family_properties)) throw std::runtime_error{ "Not all required queues are supported!" };
//            
//            const auto family_graphics_queue_index        = std::invoke([&]() -> std::uint32_t
//                {
//                    auto iterator = std::ranges::find_if(queue_family_properties, [](const vk::QueueFamilyProperties& property) -> bool
//                            {
//                                return static_cast<bool>(property.queueFlags & vk::QueueFlagBits::eGraphics);
//                            });
//
//                    if (iterator == queue_family_properties.end()) throw std::runtime_error{ "Graphics queue index not found!" };
//                    return static_cast<uint32_t>(std::distance(queue_family_properties.begin(), iterator));
//                });
//            
//            //TODO: check if device supports given extensions
//            //TODO: check swap chain compatibility with surface
//                  auto queue_priority                     = std::float_t{ 1.0f };
//            const auto required_logical_device_extensions = std::vector<const char*>{
//                vk::KHRSwapchainExtensionName
//            };
//            const auto queue_create_info                  = vk::DeviceQueueCreateInfo{
//                vk::DeviceQueueCreateFlags{}, 
//                family_graphics_queue_index, 
//                std::uint32_t{ 1u }, &queue_priority
//            };
//            const auto device_create_info                 = vk::DeviceCreateInfo{
//                vk::DeviceCreateFlags{}, 
//                queue_create_info, 
//                {}, 
//                required_logical_device_extensions
//            };
//            const auto logical_device                     = vk::raii::Device{ physical_device, device_create_info };
//
//            //TODO: find a way to get queue info, present_queue could be a different queue from graphics_queue
//            const auto graphics_queue                     = logical_device.getQueue(family_graphics_queue_index, std::uint32_t{ 0u });
//            const auto present_queue                      = logical_device.getQueue(family_graphics_queue_index, std::uint32_t{ 0u });
//
//
//            //TODO: query for wether swap chains are supported
//            //auto swap_chain_support = std::invoke([]()
//            //    {
//            //        SwapChainSupportDetails details;
//
//            //        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);
//
//            //        uint32_t formatCount;
//            //        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);
//
//            //        if (formatCount != 0) {
//            //            details.formats.resize(formatCount);
//            //            vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
//            //        }
//
//            //        uint32_t presentModeCount;
//            //        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);
//
//            //        if (presentModeCount != 0) {
//            //            details.presentModes.resize(presentModeCount);
//            //            vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
//            //        }
//
//            //        return details;
//            //    });
//
//
//
//
//
//
//            while (!glfwWindowShouldClose(window_)) 
//            {
//                glfwPollEvents();
//            }
//
//            glfwDestroyWindow(window_);
//            glfwTerminate();
//        }
//
//        std::unique_ptr<vk::raii::Context >               context_;
//        std::unique_ptr<vk::raii::Instance>               instance_;
//        std::unique_ptr<vk::raii::DebugUtilsMessengerEXT> debug_messenger_;
//        std::unique_ptr<vk::raii::SurfaceKHR>             surface_;
//        std::unique_ptr<vk::raii::SwapchainKHR>           swapchain_;
//        std::vector<vk::raii::Image>                      swapchain_images_;
//        vk::Extent2D                                      swapchain_extent_;
//        std::vector<vk::raii::ImageView>                  image_views_;
//        std::vector<vk::raii::Framebuffer>                frame_buffers_;
//        vk::raii::RenderPass                              render_pass_;
//        vk::raii::PipelineLayout                          pipeline_layout_;
//        vk::raii::Pipeline                                pipeline_;
//        vk::raii::CommandPool                             command_pool_;
//        vk::raii::CommandBuffer                           command_buffer_;
//        vk::raii::Semaphore                               image_available_semaphore_;
//        vk::raii::Semaphore                               render_pass_finished_semaphore;
//        vk::raii::Fence                                   in_flight_fence_;
//        GLFWwindow*                                       window_;
//    };
//}
