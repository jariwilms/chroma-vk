export module vx.physical_device;

import std;
import <vulkan/vulkan.h>;
import vx;
import vx.instance;

export namespace vx
{
    enum class physical_device_type_e : std::underlying_type_t<VkPhysicalDeviceType>
    {
        other          = VK_PHYSICAL_DEVICE_TYPE_OTHER         , 
        integrated_gpu = VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU, 
        discrete_gpu   = VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU  , 
        virtual_gpu    = VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU   , 
        cpu            = VK_PHYSICAL_DEVICE_TYPE_CPU           , 
        maximum        = VK_PHYSICAL_DEVICE_TYPE_MAX_ENUM      , 
    };
    enum class sample_count_e : std::underlying_type_t<VkSampleCountFlagBits>
    {
        _1      = VK_SAMPLE_COUNT_1_BIT             , 
        _2      = VK_SAMPLE_COUNT_2_BIT             , 
        _4      = VK_SAMPLE_COUNT_4_BIT             , 
        _8      = VK_SAMPLE_COUNT_8_BIT             , 
        _16     = VK_SAMPLE_COUNT_16_BIT            , 
        _32     = VK_SAMPLE_COUNT_32_BIT            , 
        _64     = VK_SAMPLE_COUNT_64_BIT            , 

        maximum = VK_SAMPLE_COUNT_FLAG_BITS_MAX_ENUM, 
    };
    
    enum class device_size : vx::uint64_t;

    class physical_device
    {
    public:
        using native_t = VkPhysicalDevice;

        struct limits
        {
            using native_t = VkPhysicalDeviceLimits;

            operator const VkPhysicalDeviceLimits*() const
            {
                return std::bit_cast<VkPhysicalDeviceLimits*>(this);
            }

            vx::uint32_t                 max_image_dimension_1d                                = {};
            vx::uint32_t                 max_image_dimension_2d                                = {};
            vx::uint32_t                 max_image_dimension_3d                                = {};
            vx::uint32_t                 max_image_dimension_cube                              = {};
            vx::uint32_t                 max_image_array_layers                                = {};
            vx::uint32_t                 max_texel_buffer_elements                             = {};
            vx::uint32_t                 max_uniform_buffer_range                              = {};
            vx::uint32_t                 max_storage_buffer_range                              = {};
            vx::uint32_t                 max_push_constants_size                               = {};
            vx::uint32_t                 max_memory_allocation_count                           = {};
            vx::uint32_t                 max_sampler_allocation_count                          = {};
            vx::device_size              buffer_image_granularity                              = {};
            vx::device_size              sparse_address_space_size                             = {};
            vx::uint32_t                 max_bound_descriptor_sets                             = {};
            vx::uint32_t                 max_per_stage_descriptor_samplers                     = {};
            vx::uint32_t                 max_per_stage_descriptor_uniform_buffers              = {};
            vx::uint32_t                 max_per_stage_descriptor_storage_buffers              = {};
            vx::uint32_t                 max_per_stage_descriptor_sampled_images               = {};
            vx::uint32_t                 max_per_stage_descriptor_storage_images               = {};
            vx::uint32_t                 max_per_stage_descriptor_input_attachments            = {};
            vx::uint32_t                 max_per_stage_resources                               = {};
            vx::uint32_t                 max_descriptor_set_samplers                           = {};
            vx::uint32_t                 max_descriptor_set_uniform_buffers                    = {};
            vx::uint32_t                 max_descriptor_set_uniform_buffers_dynamic            = {};
            vx::uint32_t                 max_descriptor_set_storage_buffers                    = {};
            vx::uint32_t                 max_descriptor_set_storage_buffers_dynamic            = {};
            vx::uint32_t                 max_descriptor_set_sampled_images                     = {};
            vx::uint32_t                 max_descriptor_set_storage_images                     = {};
            vx::uint32_t                 max_descriptor_set_input_attachments                  = {};
            vx::uint32_t                 max_vertex_input_attributes                           = {};
            vx::uint32_t                 max_vertex_input_bindings                             = {};
            vx::uint32_t                 max_vertex_input_attribute_offset                     = {};
            vx::uint32_t                 max_vertex_input_binding_stride                       = {};
            vx::uint32_t                 max_vertex_output_components                          = {};
            vx::uint32_t                 max_tessellation_generation_level                     = {};
            vx::uint32_t                 max_tessellation_patch_size                           = {};
            vx::uint32_t                 max_tessellation_control_per_vertex_input_components  = {};
            vx::uint32_t                 max_tessellation_control_per_vertex_output_components = {};
            vx::uint32_t                 max_tessellation_control_per_patch_output_components  = {};
            vx::uint32_t                 max_tessellation_control_total_output_components      = {};
            vx::uint32_t                 max_tessellation_evaluation_input_components          = {};
            vx::uint32_t                 max_tessellation_evaluation_output_components         = {};
            vx::uint32_t                 max_geometry_shader_invocations                       = {};
            vx::uint32_t                 max_geometry_input_components                         = {};
            vx::uint32_t                 max_geometry_output_components                        = {};
            vx::uint32_t                 max_geometry_output_vertices                          = {};
            vx::uint32_t                 max_geometry_total_output_components                  = {};
            vx::uint32_t                 max_fragment_input_components                         = {};
            vx::uint32_t                 max_fragment_output_attachments                       = {};
            vx::uint32_t                 max_fragment_dual_src_attachments                     = {};
            vx::uint32_t                 max_fragment_combined_output_resources                = {};
            vx::uint32_t                 max_compute_shared_memory_size                        = {};
            vx::array<vx::uint32_t, 3u>  max_compute_work_group_count                          = {};
            vx::uint32_t                 max_compute_work_group_invocations                    = {};
            vx::array<vx::uint32_t, 3u>  max_compute_work_group_size                           = {};
            vx::uint32_t                 sub_pixel_precision_bits                              = {};
            vx::uint32_t                 sub_texel_precision_bits                              = {};
            vx::uint32_t                 mipmap_precision_bits                                 = {};
            vx::uint32_t                 max_draw_indexed_index_value                          = {};
            vx::uint32_t                 max_draw_indirect_count                               = {};
            vx::float32_t                max_sampler_lod_bias                                  = {};
            vx::float32_t                max_sampler_anisotropy                                = {};
            vx::uint32_t                 max_viewports                                         = {};
            vx::array<vx::uint32_t, 2u>  max_viewport_dimensions                               = {};
            vx::array<vx::float32_t, 2u> viewport_bounds_range                                 = {};
            vx::uint32_t                 viewport_sub_pixel_bits                               = {};
            vx::size_t                   min_memory_map_alignment                              = {};
            vx::device_size              min_texel_buffer_offset_alignment                     = {};
            vx::device_size              min_uniform_buffer_offset_alignment                   = {};
            vx::device_size              min_storage_buffer_offset_alignment                   = {};
            vx::int32_t                  min_texel_offset                                      = {};
            vx::uint32_t                 max_texel_offset                                      = {};
            vx::int32_t                  min_texel_gather_offset                               = {};
            vx::uint32_t                 max_texel_gather_offset                               = {};
            vx::float32_t                min_interpolation_offset                              = {};
            vx::float32_t                max_interpolation_offset                              = {};
            vx::uint32_t                 sub_pixel_interpolation_offset_bits                   = {};
            vx::uint32_t                 max_framebuffer_width                                 = {};
            vx::uint32_t                 max_framebuffer_height                                = {};
            vx::uint32_t                 max_framebuffer_layers                                = {};
            vx::sample_count_e           framebuffer_color_sample_counts                       = {};
            vx::sample_count_e           framebuffer_depth_sample_counts                       = {};
            vx::sample_count_e           framebuffer_stencil_sample_counts                     = {};
            vx::sample_count_e           framebuffer_no_attachments_sample_counts              = {};
            vx::uint32_t                 max_color_attachments                                 = {};
            vx::sample_count_e           sampled_image_color_sample_counts                     = {};
            vx::sample_count_e           sampled_image_integer_sample_counts                   = {};
            vx::sample_count_e           sampled_image_depth_sample_counts                     = {};
            vx::sample_count_e           sampled_image_stencil_sample_counts                   = {};
            vx::sample_count_e           storage_image_sample_counts                           = {};
            vx::uint32_t                 max_sample_mask_words                                 = {};
            vx::bool32_t                 timestamp_compute_and_graphics                        = {};
            vx::float32_t                timestamp_period                                      = {};
            vx::uint32_t                 max_clip_distances                                    = {};
            vx::uint32_t                 max_cull_distances                                    = {};
            vx::uint32_t                 max_combined_clip_and_cull_distances                  = {};
            vx::uint32_t                 discrete_queue_priorities                             = {};
            vx::array<vx::float32_t, 2u> point_size_range                                      = {};
            vx::array<vx::float32_t, 2u> line_width_range                                      = {};
            vx::float32_t                point_size_granularity                                = {};
            vx::float32_t                line_width_granularity                                = {};
            vx::bool32_t                 strict_lines                                          = {};
            vx::bool32_t                 standard_sample_locations                             = {};
            vx::device_size              optimal_buffer_copy_offset_alignment                  = {};
            vx::device_size              optimal_buffer_copy_row_pitch_alignment               = {};
            vx::device_size              non_coherent_atom_size                                = {};
        };
        struct features
        {
            using native_t = VkPhysicalDeviceFeatures2;

            vx::structure_type_e structure_type                               = vx::structure_type_e::physical_device_features;
            vx::next_t           next                                         = {};

            vx::bool_t           robust_buffer_access                         = {};
            vx::bool_t           full_draw_index_uint32                       = {};
            vx::bool_t           image_cube_array                             = {};
            vx::bool_t           independent_blend                            = {};
            vx::bool_t           geometry_shader                              = {};
            vx::bool_t           tessellation_shader                          = {};
            vx::bool_t           sample_rate_shading                          = {};
            vx::bool_t           dual_src_blend                               = {};
            vx::bool_t           logic_op                                     = {};
            vx::bool_t           multi_draw_indirect                          = {};
            vx::bool_t           draw_indirect_first_instance                 = {};
            vx::bool_t           depth_clamp                                  = {};
            vx::bool_t           depth_bias_clamp                             = {};
            vx::bool_t           fill_mode_non_solid                          = {};
            vx::bool_t           depth_bounds                                 = {};
            vx::bool_t           wide_lines                                   = {};
            vx::bool_t           large_points                                 = {};
            vx::bool_t           alpha_to_one                                 = {};
            vx::bool_t           multi_viewport                               = {};
            vx::bool_t           sampler_anisotropy                           = {};
            vx::bool_t           texture_compression_etc2                     = {};
            vx::bool_t           texture_compression_astc_ldr                 = {};
            vx::bool_t           texture_compression_bc                       = {};
            vx::bool_t           occlusion_query_precise                      = {};
            vx::bool_t           pipeline_statistics_query                    = {};
            vx::bool_t           vertex_pipeline_stores_and_atomics           = {};
            vx::bool_t           fragment_stores_and_atomics                  = {};
            vx::bool_t           shader_tessellation_and_geometry_point_size  = {};
            vx::bool_t           shader_image_gather_extended                 = {};
            vx::bool_t           shader_storage_image_extended_formats        = {};
            vx::bool_t           shader_storage_image_multisample             = {};
            vx::bool_t           shader_storage_image_read_without_format     = {};
            vx::bool_t           shader_storage_image_write_without_format    = {};
            vx::bool_t           shader_uniform_buffer_array_dynamic_indexing = {};
            vx::bool_t           shader_sampled_image_array_dynamic_indexing  = {};
            vx::bool_t           shader_storage_buffer_array_dynamic_indexing = {};
            vx::bool_t           shader_storage_image_array_dynamic_indexing  = {};
            vx::bool_t           shader_clip_distance                         = {};
            vx::bool_t           shader_cull_distance                         = {};
            vx::bool_t           shader_float64                               = {};
            vx::bool_t           shader_int64                                 = {};
            vx::bool_t           shader_int16                                 = {};
            vx::bool_t           shader_resource_residency                    = {};
            vx::bool_t           shader_resource_min_lod                      = {};
            vx::bool_t           sparse_binding                               = {};
            vx::bool_t           sparse_residency_buffer                      = {};
            vx::bool_t           sparse_residency_image2_d                    = {};
            vx::bool_t           sparse_residency_image3_d                    = {};
            vx::bool_t           sparse_residency2_samples                    = {};
            vx::bool_t           sparse_residency4_samples                    = {};
            vx::bool_t           sparse_residency8_samples                    = {};
            vx::bool_t           sparse_residency16_samples                   = {};
            vx::bool_t           sparse_residency_aliased                     = {};
            vx::bool_t           variable_multisample_rate                    = {};
            vx::bool_t           inherited_queries                            = {};
        };
        struct sparse_properties
        {
            using native_t = VkPhysicalDeviceSparseProperties;

            operator const VkPhysicalDeviceSparseProperties* () const
            {
                return std::bit_cast<VkPhysicalDeviceSparseProperties*>(this);
            }

            vx::bool32_t residency_standard_2d_block_shape             = {};
            vx::bool32_t residency_standard_2d_multisample_block_shape = {};
            vx::bool32_t residency_standard_3d_block_shape             = {};
            vx::bool32_t residency_aligned_mip_size                    = {};
            vx::bool32_t residency_non_resident_strict                 = {};
        };
        struct properties
        {
            using native_t = VkPhysicalDeviceProperties2;

            operator const VkPhysicalDeviceProperties2*() const
            {
                return std::bit_cast<VkPhysicalDeviceProperties2*>(this);
            }

            vx::structure_type_e                   structure_type                                = vx::structure_type_e::physical_device_properties;
            vx::next_t                             next                                          = {};

            vx::uint32_t                           api_version                                   = 0u;
            vx::uint32_t                           driver_version                                = 0u;
            vx::uint32_t                           vendor_id                                     = 0u;
            vx::uint32_t                           device_id                                     = 0u;
            vx::physical_device_type_e             device_type                                   = {};
            vx::char_t                             device_name[VK_MAX_PHYSICAL_DEVICE_NAME_SIZE] = {};
            vx::uint8_t                            pipeline_cache_uuid[VK_UUID_SIZE]             = {};
            vx::physical_device::limits            limits                                        = {};
            vx::physical_device::sparse_properties sparse_properties                             = {};
        };
        
        physical_device() = default;
        physical_device(std::shared_ptr<vx::instance> instance, std::vector<vx::string_view> required_extensions)
        {
                  auto physical_device_count = vx::uint32_t{};
            if (vkEnumeratePhysicalDevices(*instance, &physical_device_count, nullptr)                 != VkResult::VK_SUCCESS) throw std::runtime_error{ "Failed to enumerate instance layer properties!" };
                  auto physical_devices      = std::vector<VkPhysicalDevice>(physical_device_count);
            if (vkEnumeratePhysicalDevices(*instance, &physical_device_count, physical_devices.data()) != VkResult::VK_SUCCESS) throw std::runtime_error{ "Failed to enumerate instance layer properties!" };

            const auto candidates                  = std::invoke([&]() -> std::map<vx::uint32_t, VkPhysicalDevice>
                {
                    auto result = std::map<vx::uint32_t, VkPhysicalDevice>{};
                    std::ranges::for_each(physical_devices, [&](const VkPhysicalDevice& physical_device)
                        {
                                  auto score                                    = vx::uint32_t{ 0u };
                                  auto max_video_memory                         = VkDeviceSize { 0u };

                                  auto physical_device_features                 = VkPhysicalDeviceFeatures2        {};
                            vkGetPhysicalDeviceFeatures2             (physical_device,                                                     &physical_device_features                  );

                                  auto physical_device_properties               = VkPhysicalDeviceProperties2      {};
                            vkGetPhysicalDeviceProperties2           (physical_device,                                                     &physical_device_properties                );

                                  auto physical_device_memory_properties        = VkPhysicalDeviceMemoryProperties2{};
                            vkGetPhysicalDeviceMemoryProperties2     (physical_device,                                                     &physical_device_memory_properties         );

                                  auto physical_device_queue_family_count       = vx::uint32_t{};
                            vkGetPhysicalDeviceQueueFamilyProperties2(physical_device,          &physical_device_queue_family_count      , nullptr                                    );
                                  auto physical_device_queue_families           = std::vector<VkQueueFamilyProperties>(physical_device_queue_family_count);
                            vkGetPhysicalDeviceQueueFamilyProperties2(physical_device,          &physical_device_queue_family_count      , physical_device_queue_families.data()      );

                                  auto physical_device_extension_property_count = vx::uint32_t{};
                            vkEnumerateDeviceExtensionProperties    (physical_device, nullptr, &physical_device_extension_property_count, nullptr                                    );
                                  auto physical_device_extension_properties     = std::vector<VkExtensionProperties>(physical_device_extension_property_count);
                            vkEnumerateDeviceExtensionProperties    (physical_device, nullptr, &physical_device_extension_property_count, physical_device_extension_properties.data());



                            if (physical_device_properties.apiVersion < std::to_underlying(vx::api_version::_1_4)) return;
                            if (!std::ranges::any_of(queue_families     , [&](const auto& family) -> bool
                                { 
                                    return !(family.queueFlags & VkQueueFlagBits::eGraphics); 
                                })) return;
                            if (!std::ranges::all_of(required_extensions, [&](const char* name  ) -> bool
                                {
                                    return std::ranges::any_of(device_extension_properties, [&](const VkExtensionProperties& property) -> bool
                                        {
                                            return !strcmp(property.extensionName.data(), name);
                                        });
                                })) return;

                                    if (properties.deviceType == VkPhysicalDeviceType::eDiscreteGpu  ) score += 8;
                            else if (properties.deviceType == VkPhysicalDeviceType::eIntegratedGpu) score += 2;
                            else                                                                      score += 1;

                            std::ranges::for_each(std::views::iota(0u, memory_properties.memoryHeapCount), [&](auto index)
                                {
                                    if (memory_properties.memoryHeaps[index].flags & VkMemoryHeapFlagBits::eDeviceLocal)
                                        max_video_memory = std::max(max_video_memory, memory_properties.memoryHeaps[index].size);
                                });

                            score += static_cast<vx::uint32_t>(max_video_memory / static_cast<vx::uint32_t>(std::pow(2u, 30u))); //1 Gigabyte
                            result.emplace(score, physical_device);
                        });

                    return result;
                });
            if (candidates.empty      ()) throw std::runtime_error{ "No suitable physical device found!" };

            physical_device_ = candidates.rbegin()->second;
        }

        operator const VkPhysicalDevice() const
        {
            return physical_device_;
        }

    private:
        VkPhysicalDevice physical_device_;
    };
}
