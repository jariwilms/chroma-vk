export module vx.physical_device;

import std;
import <vulkan/vulkan.h>;
import vx;
import vx.instance;

export namespace vx
{
    struct memory_type
    {
        vx::memory_property_flags_e flags;
        vx::uint32_t                heap_index;
    };
    struct memory_heap
    {
        using native_t = VkMemoryHeap;

        operator       VkMemoryHeap*()
        {
            return std::bit_cast<VkMemoryHeap*>(this);
        }
        operator const VkMemoryHeap*() const
        {
            return std::bit_cast<const VkMemoryHeap*>(this);
        }

        vx::device_size         size;
        vx::memory_heap_flags_e flags;
    };
    struct extent_3d
    {
        using native_t = VkExtent3D;

        vx::uint32_t width;
        vx::uint32_t height;
        vx::uint32_t depth;
    };
    struct queue_family_properties
    {
        using native_t = VkQueueFamilyProperties2;

        operator       VkQueueFamilyProperties2*()
        {
            return std::bit_cast<      VkQueueFamilyProperties2*>(this);
        }
        operator const VkQueueFamilyProperties2*() const
        {
            return std::bit_cast<const VkQueueFamilyProperties2*>(this);
        }

        vx::structure_type_e structure_type                     = vx::structure_type_e::queue_family_properties;
        vx::next_t           next                               = {};

        vx::queue_flags_e    queue_flags                        = {};
        vx::uint32_t         queue_count                        = {};
        vx::uint32_t         timestamp_valid_bits               = {};
        vx::extent_3d        minimum_image_transfer_granularity = {};
    };
    struct extension_properties
    {
        using native_t = VkExtensionProperties;

        vx::char_t   name[VK_MAX_EXTENSION_NAME_SIZE] = {};
        vx::uint32_t specification_version            = {};
    };
    struct physical_device_limits
    {
        using native_t = VkPhysicalDeviceLimits;

        operator       VkPhysicalDeviceLimits*() 
        {
            return std::bit_cast<VkPhysicalDeviceLimits*>(this);
        }
        operator const VkPhysicalDeviceLimits*() const
        {
            return std::bit_cast<const VkPhysicalDeviceLimits*>(this);
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
    struct physical_device_features
    {
        using native_t = VkPhysicalDeviceFeatures2;

        operator       VkPhysicalDeviceFeatures2*() 
        {
            return std::bit_cast<VkPhysicalDeviceFeatures2*>(this);
        }
        operator const VkPhysicalDeviceFeatures2*() const
        {
            return std::bit_cast<const VkPhysicalDeviceFeatures2*>(this);
        }

        vx::structure_type_e structure_type                               = vx::structure_type_e::physical_device_features;
        vx::next_t           next                                         = {};
            
        vx::bool32_t         robust_buffer_access                         = {};
        vx::bool32_t         full_draw_index_uint32                       = {};
        vx::bool32_t         image_cube_array                             = {};
        vx::bool32_t         independent_blend                            = {};
        vx::bool32_t         geometry_shader                              = {};
        vx::bool32_t         tessellation_shader                          = {};
        vx::bool32_t         sample_rate_shading                          = {};
        vx::bool32_t         dual_src_blend                               = {};
        vx::bool32_t         logic_op                                     = {};
        vx::bool32_t         multi_draw_indirect                          = {};
        vx::bool32_t         draw_indirect_first_instance                 = {};
        vx::bool32_t         depth_clamp                                  = {};
        vx::bool32_t         depth_bias_clamp                             = {};
        vx::bool32_t         fill_mode_non_solid                          = {};
        vx::bool32_t         depth_bounds                                 = {};
        vx::bool32_t         wide_lines                                   = {};
        vx::bool32_t         large_points                                 = {};
        vx::bool32_t         alpha_to_one                                 = {};
        vx::bool32_t         multi_viewport                               = {};
        vx::bool32_t         sampler_anisotropy                           = {};
        vx::bool32_t         texture_compression_etc2                     = {};
        vx::bool32_t         texture_compression_astc_ldr                 = {};
        vx::bool32_t         texture_compression_bc                       = {};
        vx::bool32_t         occlusion_query_precise                      = {};
        vx::bool32_t         pipeline_statistics_query                    = {};
        vx::bool32_t         vertex_pipeline_stores_and_atomics           = {};
        vx::bool32_t         fragment_stores_and_atomics                  = {};
        vx::bool32_t         shader_tessellation_and_geometry_point_size  = {};
        vx::bool32_t         shader_image_gather_extended                 = {};
        vx::bool32_t         shader_storage_image_extended_formats        = {};
        vx::bool32_t         shader_storage_image_multisample             = {};
        vx::bool32_t         shader_storage_image_read_without_format     = {};
        vx::bool32_t         shader_storage_image_write_without_format    = {};
        vx::bool32_t         shader_uniform_buffer_array_dynamic_indexing = {};
        vx::bool32_t         shader_sampled_image_array_dynamic_indexing  = {};
        vx::bool32_t         shader_storage_buffer_array_dynamic_indexing = {};
        vx::bool32_t         shader_storage_image_array_dynamic_indexing  = {};
        vx::bool32_t         shader_clip_distance                         = {};
        vx::bool32_t         shader_cull_distance                         = {};
        vx::bool32_t         shader_float64                               = {};
        vx::bool32_t         shader_int64                                 = {};
        vx::bool32_t         shader_int16                                 = {};
        vx::bool32_t         shader_resource_residency                    = {};
        vx::bool32_t         shader_resource_min_lod                      = {};
        vx::bool32_t         sparse_binding                               = {};
        vx::bool32_t         sparse_residency_buffer                      = {};
        vx::bool32_t         sparse_residency_image2_d                    = {};
        vx::bool32_t         sparse_residency_image3_d                    = {};
        vx::bool32_t         sparse_residency2_samples                    = {};
        vx::bool32_t         sparse_residency4_samples                    = {};
        vx::bool32_t         sparse_residency8_samples                    = {};
        vx::bool32_t         sparse_residency16_samples                   = {};
        vx::bool32_t         sparse_residency_aliased                     = {};
        vx::bool32_t         variable_multisample_rate                    = {};
        vx::bool32_t         inherited_queries                            = {};
    };
    struct physical_device_sparse_properties
    {
        using native_t = VkPhysicalDeviceSparseProperties;

        operator       VkPhysicalDeviceSparseProperties*()
        {
            return std::bit_cast<VkPhysicalDeviceSparseProperties*>(this);
        }
        operator const VkPhysicalDeviceSparseProperties*() const
        {
            return std::bit_cast<const VkPhysicalDeviceSparseProperties*>(this);
        }

        vx::bool32_t residency_standard_2d_block_shape             = {};
        vx::bool32_t residency_standard_2d_multisample_block_shape = {};
        vx::bool32_t residency_standard_3d_block_shape             = {};
        vx::bool32_t residency_aligned_mip_size                    = {};
        vx::bool32_t residency_non_resident_strict                 = {};
    };
    struct physical_device_properties
    {
        using native_t = VkPhysicalDeviceProperties2;

        operator       VkPhysicalDeviceProperties2*()
        {
            return std::bit_cast<VkPhysicalDeviceProperties2*>(this);
        }
        operator const VkPhysicalDeviceProperties2*() const
        {
            return std::bit_cast<const VkPhysicalDeviceProperties2*>(this);
        }

        vx::structure_type_e                  structure_type                                = vx::structure_type_e::physical_device_properties;
        vx::next_t                            next                                          = {};

        vx::api_version_e                     api_version                                   = {};
        vx::uint32_t                          driver_version                                = {};
        vx::uint32_t                          vendor_id                                     = {};
        vx::uint32_t                          device_id                                     = {};
        vx::physical_device_type_e            device_type                                   = {};
        vx::char_t                            device_name[VK_MAX_PHYSICAL_DEVICE_NAME_SIZE] = {};
        vx::uint8_t                           pipeline_cache_uuid[VK_UUID_SIZE]             = {};
        vx::physical_device_limits            limits                                        = {};
        vx::physical_device_sparse_properties sparse_properties                             = {};
    };
    struct physical_device_memory_properties
    {
        using native_t = VkPhysicalDeviceMemoryProperties2;

        operator       VkPhysicalDeviceMemoryProperties2*()
        {
            return std::bit_cast<VkPhysicalDeviceMemoryProperties2*>(this);
        }
        operator const VkPhysicalDeviceMemoryProperties2*() const
        {
            return std::bit_cast<const VkPhysicalDeviceMemoryProperties2*>(this);
        }

        vx::structure_type_e structure_type                    = vx::structure_type_e::physical_device_memory_properties;
        vx::next_t           next                              = {};

        vx::uint32_t         memory_type_count                 = {};
        vx::memory_type      memory_types[VK_MAX_MEMORY_TYPES] = {};
        vx::uint32_t         memory_heap_count                 = {};
        vx::memory_heap      memory_heaps[VK_MAX_MEMORY_HEAPS] = {};
    };




    template<std::convertible_to<VkPhysicalDevice> T, std::convertible_to<VkInstance> U>
    auto enumerate_physical_devices                 (U& instance) -> std::vector<T>
    {
        return vx::query_and_retrieve<vkEnumeratePhysicalDevices, T>(instance);
    }

    template<std::convertible_to<VkPhysicalDevice> T>
    auto get_physical_device_features               (T& physical_device) -> vx::physical_device_features
    {
        auto physical_device_features = vx::physical_device_features{};
        ::vkGetPhysicalDeviceFeatures2(physical_device, physical_device_features);

        return physical_device_features;
    }
    template<std::convertible_to<VkPhysicalDevice> T>
    auto get_physical_device_properties             (T& physical_device) -> vx::physical_device_properties
    {
        auto physical_device_properties = vx::physical_device_properties{};
        ::vkGetPhysicalDeviceProperties2(physical_device, physical_device_properties);

        return physical_device_properties;
    }
    template<std::convertible_to<VkPhysicalDevice> T>
    auto get_physical_device_memory_properties      (T& physical_device) -> vx::physical_device_memory_properties
    {
        auto physical_device_memory_properties = vx::physical_device_memory_properties{};
        ::vkGetPhysicalDeviceMemoryProperties2(physical_device, physical_device_memory_properties);

        return physical_device_memory_properties;
    }

    template<std::convertible_to<VkPhysicalDevice> T>
    auto get_physical_device_queue_family_properties(T physical_device) -> std::vector<vx::queue_family_properties>
    {
        return vx::query_and_retrieve<::vkGetPhysicalDeviceQueueFamilyProperties2, vx::queue_family_properties>(physical_device);
    }
    template<std::convertible_to<VkPhysicalDevice> T>
    auto enumerate_device_extension_properties      (T physical_device, vx::string_view layer_name = {}) -> std::vector<vx::extension_properties>
    {
        return vx::query_and_retrieve<::vkEnumerateDeviceExtensionProperties, vx::extension_properties>(physical_device, layer_name);
    }


    class physical_device
    {
    public:
        using native_t = VkPhysicalDevice;

        physical_device() = default;
        physical_device(std::shared_ptr<vx::instance> instance, std::vector<vx::string_view> required_extensions)
        {
                  auto physical_devices = vx::enumerate_physical_devices<vx::physical_device>(*instance);
            const auto candidates       = std::invoke([&]() -> std::map<vx::uint32_t, vx::physical_device>
                {
                    auto result = std::map<vx::uint32_t, vx::physical_device>{};
                    std::ranges::for_each(physical_devices, [&](vx::physical_device& physical_device)
                        {
                            const auto features                 = vx::get_physical_device_features               (physical_device);
                            const auto properties               = vx::get_physical_device_properties             (physical_device);
                            const auto memory_properties        = vx::get_physical_device_memory_properties      (physical_device);
                            const auto queue_family_properties  = vx::get_physical_device_queue_family_properties(physical_device);
                            const auto extension_properties     = vx::enumerate_device_extension_properties      (physical_device);
                            
                            if (properties.api_version < vx::api_version_e::_1_4) return;

                            const auto has_graphics_queue       = std::ranges::any_of(queue_family_properties, [ ](const vx::queue_family_properties& queue_family_properties) -> vx::bool_t
                                {
                                    return static_cast<vx::bool_t>(queue_family_properties.queue_flags & vx::queue_flags_e::graphics);
                                });
                            if (!has_graphics_queue)       return;

                            const auto all_extensions_supported = std::ranges::all_of(required_extensions    , [&](const vx::string_view required_name) -> vx::bool_t
                                {
                                    return std::ranges::any_of(extension_properties, [required_name](const vx::extension_properties& property) -> vx::bool_t
                                        {
                                            return std::strcmp(property.name, required_name) == vx::int32_t{ 0 };
                                        });
                                });
                            if (!all_extensions_supported) return;

                            const auto score                    = std::invoke([&]() -> vx::uint32_t
                                {
                                    const auto device_type_score  = std::invoke([&]() -> vx::uint32_t
                                        {
                                            switch (properties.device_type)
                                            {
                                                case vx::physical_device_type_e::discrete_gpu  : return 8u;
                                                case vx::physical_device_type_e::integrated_gpu: return 2u;

                                                default                                        : return 1u;
                                            }
                                        });
                                    const auto video_memory_score = std::invoke([&]() -> vx::uint32_t
                                        {
                                            const auto local_heaps = std::views::iota(vx::uint32_t{ 0u }, memory_properties.memory_heap_count)
                                                | std::views::transform([&](      vx::uint32_t     index      ) { return memory_properties.memory_heaps[index];                                                    })
                                                | std::views::filter   ([ ](const vx::memory_heap& memory_heap) { return (memory_heap.flags & vx::memory_heap_flags_e::device_local) != vx::memory_heap_flags_e{}; })
                                                | std::ranges::to<std::vector>();
                                            
                                            const auto max_video_memory = std::ranges::max_element(local_heaps, std::less{}, &vx::memory_heap::size);
                                            if (max_video_memory == local_heaps.end()) return vx::uint32_t{ 0u };
                                            
                                            const auto gigabyte = static_cast<vx::uint32_t>(std::pow(2u, 30u));
                                            return static_cast<vx::uint32_t>(std::to_underlying(max_video_memory->size) / gigabyte);
                                        });

                                    return device_type_score + video_memory_score;
                                });
                            result.emplace(score, physical_device);
                        });

                    return result;
                });

            if (candidates.empty()) throw std::runtime_error{ "No suitable physical device found!" };

            physical_device_ = candidates.rbegin()->second;
        }

        operator       VkPhysicalDevice()
        {
            return physical_device_;
        }
        operator const VkPhysicalDevice() const
        {
            return physical_device_;
        }

    private:
        VkPhysicalDevice physical_device_;
    };
}
