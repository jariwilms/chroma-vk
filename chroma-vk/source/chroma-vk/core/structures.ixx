export module vx.structures;

import std;
import <vulkan/vulkan.h>;
import vx.types;
import vx.flags;
import vx.constants;

export namespace vx
{
    template<typename T>
    class alias_of
    {
    public:
        using native_t = T;

        alias_of()
            : value_{} {}
        alias_of(T value)
            : value_{ value } {}

        operator       native_t&()
        {
            return value_;
        }
        operator const native_t&() const
        {
            return value_;
        }

    private:
        native_t value_;
    };

    using image         = vx::alias_of<vx::image_t        >;
    using image_view    = vx::alias_of<vx::image_view_t   >;
    using shader_module = vx::alias_of<vx::shader_module_t>;





    template<typename From, typename To> struct  chain_link : std::false_type {};
    template<typename From, typename To> concept valid_chain_link = vx::chain_link<From, To>::value;

    template<typename... Ts>
    consteval auto validate_structure_chain() -> vx::bool_t
    {
        if constexpr (sizeof...(Ts) <= 1u) return vx::true_;
        else 
        {
            auto check_pairs = []<std::size_t... I>(std::index_sequence<I...>) 
            {
                using tuple_t = std::tuple<Ts...>;
                return (vx::chain_link<std::tuple_element_t<I, tuple_t>, std::tuple_element_t<I + 1u, tuple_t>>::value && ...);
            };

            return check_pairs(std::make_index_sequence<sizeof...(Ts) - 1u>{});
        }
    }
    template<typename... Ts>
    concept valid_structure_chain = vx::validate_structure_chain<Ts...>();

    template<typename... Ts> requires vx::valid_structure_chain<Ts...>
    class structure_chain
    {
    public:
        structure_chain(Ts&&... chain)
            : chain_{ std::forward<Ts>(chain)... }
        {
            link_chain(std::make_index_sequence<sizeof...(Ts)>{});
        }

        template<typename T>
        auto get(this auto&& self) -> auto&&
        {
            return std::get<T>(self.chain_);
        }

    private:
        template<std::size_t... I>
        void link_chain(std::index_sequence<I...>)
        {
            ((link_element<I>()), ...);
        }
        template<std::size_t I>
        void link_element()
        {
            if constexpr (I < sizeof...(Ts) - 1u) std::get<I>(chain_).next = &std::get<I + 1u>(chain_);
        }

        std::tuple<Ts...> chain_;
    };





    struct structure_t
    {
        structure_t(const vx::structure_type_e structure_type)
            : structure_type_{ structure_type } {}

    private:
        const vx::structure_type_e structure_type_;
    };

    struct layer_properties : vx::enable_conversion<vx::layer_properties, VkLayerProperties>
    {
        vx::array<vx::char_t, vx::maximum_extension_name_size> name;
        vx::uint32_t                                           specification_version;
        vx::uint32_t                                           implementation_version;
        vx::array<vx::char_t, vx::maximum_description_size>    description;
    };
    struct memory_type : vx::enable_conversion<vx::memory_type, VkMemoryType>
    {
        vx::memory_property_flags_e flags;
        vx::uint32_t                heap_index;
    };
    struct memory_heap : vx::enable_conversion<vx::memory_heap, VkMemoryHeap>
    {
        vx::device_size         size;
        vx::memory_heap_flags_e flags;
    };
    struct extent_2d : vx::enable_conversion<vx::extent_2d, VkExtent2D>
    {
        vx::uint32_t width;
        vx::uint32_t height;
    };
    struct extent_3d : vx::enable_conversion<vx::extent_3d, VkExtent3D>
    {
        vx::uint32_t width;
        vx::uint32_t height;
        vx::uint32_t depth;
    };
    struct extension_properties : vx::enable_conversion<vx::extension_properties, VkExtensionProperties>
    {
        vx::array<vx::char_t, vx::maximum_extension_name_size> name                  = {};
        vx::uint32_t                                           specification_version = {};
    };
    struct physical_device_limits : vx::enable_conversion<vx::physical_device_limits, VkPhysicalDeviceLimits>
    {
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
    struct physical_device_sparse_properties : vx::enable_conversion<vx::physical_device_sparse_properties, VkPhysicalDeviceSparseProperties>
    {
        vx::bool32_t residency_standard_2d_block_shape             = {};
        vx::bool32_t residency_standard_2d_multisample_block_shape = {};
        vx::bool32_t residency_standard_3d_block_shape             = {};
        vx::bool32_t residency_aligned_mip_size                    = {};
        vx::bool32_t residency_non_resident_strict                 = {};
    };
    struct surface_capabilities : vx::enable_conversion<vx::surface_capabilities, VkSurfaceCapabilitiesKHR>
    {
        vx::uint32_t                  minimum_image_count        = {};
        vx::uint32_t                  maximum_image_count        = {};
        vx::extent_2d                 current_extent             = {};
        vx::extent_2d                 minimum_image_extent       = {};
        vx::extent_2d                 maximum_image_extent       = {};
        vx::uint32_t                  maximum_image_array_layers = {};
        vx::surface_transform_flags_e supported_transforms       = {};
        vx::surface_transform_flags_e current_transform          = {};
        vx::composite_alpha_flags_e   supported_composite_alpha  = {};
        vx::image_usage_flags_e       supported_usage_flags      = {};
    };
    struct component_mapping : vx::enable_conversion<vx::component_mapping, VkComponentMapping>
    {
        vx::component_swizzle_e r = {};
        vx::component_swizzle_e g = {};
        vx::component_swizzle_e b = {};
        vx::component_swizzle_e a = {};
    };
    struct image_sub_resource_range : vx::enable_conversion<vx::image_sub_resource_range, VkImageSubresourceRange>
    {
        vx::image_aspect_flags_e aspect_flags     = {};
        vx::uint32_t             base_mip_level   = {};
        vx::uint32_t             level_count      = {};
        vx::uint32_t             base_array_layer = {};
        vx::uint32_t             layer_count      = {};
    };
    struct viewport : vx::enable_conversion<vx::viewport, VkViewport>
    {
        vx::float32_t x             = {}; //TODO: vector2 (or vector4?)
        vx::float32_t y             = {};
        vx::float32_t width         = {};
        vx::float32_t height        = {};
        vx::float32_t minimum_depth = {};
        vx::float32_t maximum_depth = {};
    };
    struct offset_2d : vx::enable_conversion<vx::offset_2d, VkOffset2D>
    {
        vx::int32_t x = {}; //TODO: vec2i
        vx::int32_t y = {};
    };
    struct rectangle_2d : vx::enable_conversion<vx::rectangle_2d, VkRect2D>
    {
        vx::offset_2d offset = {};
        vx::extent_2d extent = {};
    };
    struct specialization_map_entry : vx::enable_conversion<vx::specialization_map_entry, VkSpecializationMapEntry>
    {
        vx::uint32_t constant_id = {};
        vx::uint32_t offset      = {};
        vx::size_t   size        = {};
    };
    struct specialization_info : vx::enable_conversion<vx::specialization_info, VkSpecializationInfo>
    {
        vx::uint32_t                                  entry_count = {}; //TODO: span
        vx::pointer_t<const specialization_map_entry> map_entries = {};
        vx::size_t                                    data_size   = {}; //TODO: span (64-bit size)
        vx::pointer_t<const vx::void_t>               data        = {};
    };
    struct vertex_input_binding_description : vx::enable_conversion<vx::vertex_input_binding_description, VkVertexInputBindingDescription>
    {
        vx::uint32_t            binding    = {};
        vx::uint32_t            stride     = {};
        vx::vertex_input_rate_e input_rate = {};
    };
    struct vertex_input_attribute_description : vx::enable_conversion<vx::vertex_input_attribute_description, VkVertexInputAttributeDescription>
    {
        vx::uint32_t location = {};
        vx::uint32_t binding  = {};
        vx::format_e format   = {};
        vx::uint32_t offset   = {};
    };
    struct pipeline_color_blend_attachment_state : vx::enable_conversion<vx::pipeline_color_blend_attachment_state, VkPipelineColorBlendAttachmentState>
    {
        vx::bool32_t             enable_blending                = {};
        vx::blending_factor_e    source_color_blend_factor      = {};
        vx::blending_factor_e    destination_color_blend_factor = {};
        vx::blending_operation_e color_blending_operation       = {};
        vx::blending_factor_e    source_alpha_blend_factor      = {};
        vx::blending_factor_e    destination_alpha_blend_factor = {};
        vx::blending_operation_e alpha_blend_operation          = {};
        vx::color_component_e    color_write_mask               = {};
    };
    
    struct application_info : vx::enable_conversion<vx::application_info, VkApplicationInfo>
    {
        vx::structure_t   structure_type = vx::structure_type_e::application_info;
        vx::next_t        next           = {};
        vx::string_view   name           = {};
        vx::uint32_t      version        = {};
        vx::string_view   engine_name    = {};
        vx::uint32_t      engine_version = {};
        vx::api_version_e api_version    = {};
    };
    struct debug_messenger_create_info : vx::enable_conversion<vx::debug_messenger_create_info, VkDebugUtilsMessengerCreateInfoEXT>
    {
        vx::structure_t                          structure_type = vx::structure_type_e::debug_messenger;
        vx::next_t                               next           = {};
        vx::debug_utils_messenger_create_flags_e flags          = {};
        vx::debug_utils_message_severity_e       severity       = {};
        vx::debug_utils_message_type_e           type           = {};
        vx::debug_utils_messenger_callback_t     callback       = {};
        vx::next_t                               user_data      = {};
    };
    struct instance_create_info : vx::enable_conversion<vx::instance_create_info, VkInstanceCreateInfo>
    {
        vx::structure_t                             structure_type   = vx::structure_type_e::instance_create_info;
        vx::next_t                                  next             = {};
        vx::instance_create_flags_e                 flags            = {};
        vx::reference_t<const vx::application_info> application_info = {};
        vx::span<const vx::string_view>             layer_names      = {};
        vx::span<const vx::string_view>             extension_names  = {};
    };
    struct queue_family_properties : vx::enable_conversion<vx::queue_family_properties, VkQueueFamilyProperties2>
    {
        vx::structure_t   structure_type                     = vx::structure_type_e::queue_family_properties;
        vx::next_t        next                               = {};
        vx::queue_flags_e queue_flags                        = {};
        vx::uint32_t      queue_count                        = {};
        vx::uint32_t      timestamp_valid_bits               = {};
        vx::extent_3d     minimum_image_transfer_granularity = {};
    };
    struct physical_device_features : vx::enable_conversion<vx::physical_device_features, VkPhysicalDeviceFeatures2>
    {
        vx::structure_t structure_type                               = vx::structure_type_e::physical_device_features;
        vx::next_t      next                                         = {};
        vx::bool32_t    robust_buffer_access                         = {};
        vx::bool32_t    full_draw_index_uint32                       = {};
        vx::bool32_t    image_cube_array                             = {};
        vx::bool32_t    independent_blend                            = {};
        vx::bool32_t    geometry_shader                              = {};
        vx::bool32_t    tessellation_shader                          = {};
        vx::bool32_t    sample_rate_shading                          = {};
        vx::bool32_t    dual_src_blend                               = {};
        vx::bool32_t    logic_op                                     = {};
        vx::bool32_t    multi_draw_indirect                          = {};
        vx::bool32_t    draw_indirect_first_instance                 = {};
        vx::bool32_t    depth_clamp                                  = {};
        vx::bool32_t    depth_bias_clamp                             = {};
        vx::bool32_t    fill_mode_non_solid                          = {};
        vx::bool32_t    depth_bounds                                 = {};
        vx::bool32_t    wide_lines                                   = {};
        vx::bool32_t    large_points                                 = {};
        vx::bool32_t    alpha_to_one                                 = {};
        vx::bool32_t    multi_viewport                               = {};
        vx::bool32_t    sampler_anisotropy                           = {};
        vx::bool32_t    texture_compression_etc2                     = {};
        vx::bool32_t    texture_compression_astc_ldr                 = {};
        vx::bool32_t    texture_compression_bc                       = {};
        vx::bool32_t    occlusion_query_precise                      = {};
        vx::bool32_t    pipeline_statistics_query                    = {};
        vx::bool32_t    vertex_pipeline_stores_and_atomics           = {};
        vx::bool32_t    fragment_stores_and_atomics                  = {};
        vx::bool32_t    shader_tessellation_and_geometry_point_size  = {};
        vx::bool32_t    shader_image_gather_extended                 = {};
        vx::bool32_t    shader_storage_image_extended_formats        = {};
        vx::bool32_t    shader_storage_image_multisample             = {};
        vx::bool32_t    shader_storage_image_read_without_format     = {};
        vx::bool32_t    shader_storage_image_write_without_format    = {};
        vx::bool32_t    shader_uniform_buffer_array_dynamic_indexing = {};
        vx::bool32_t    shader_sampled_image_array_dynamic_indexing  = {};
        vx::bool32_t    shader_storage_buffer_array_dynamic_indexing = {};
        vx::bool32_t    shader_storage_image_array_dynamic_indexing  = {};
        vx::bool32_t    shader_clip_distance                         = {};
        vx::bool32_t    shader_cull_distance                         = {};
        vx::bool32_t    shader_float64                               = {};
        vx::bool32_t    shader_int64                                 = {};
        vx::bool32_t    shader_int16                                 = {};
        vx::bool32_t    shader_resource_residency                    = {};
        vx::bool32_t    shader_resource_min_lod                      = {};
        vx::bool32_t    sparse_binding                               = {};
        vx::bool32_t    sparse_residency_buffer                      = {};
        vx::bool32_t    sparse_residency_image2_d                    = {};
        vx::bool32_t    sparse_residency_image3_d                    = {};
        vx::bool32_t    sparse_residency2_samples                    = {};
        vx::bool32_t    sparse_residency4_samples                    = {};
        vx::bool32_t    sparse_residency8_samples                    = {};
        vx::bool32_t    sparse_residency16_samples                   = {};
        vx::bool32_t    sparse_residency_aliased                     = {};
        vx::bool32_t    variable_multisample_rate                    = {};
        vx::bool32_t    inherited_queries                            = {};
    };
    struct physical_device_properties : vx::enable_conversion<vx::physical_device_properties, VkPhysicalDeviceProperties2>
    {
        vx::structure_t                                              structure_type      = vx::structure_type_e::physical_device_properties;
        vx::next_t                                                   next                = {};
        vx::api_version_e                                            api_version         = {};
        vx::uint32_t                                                 driver_version      = {};
        vx::uint32_t                                                 vendor_id           = {};
        vx::uint32_t                                                 device_id           = {};
        vx::physical_device_type_e                                   device_type         = {};
        vx::array<vx::char_t, vx::maximum_physical_device_name_size> device_name         = {};
        vx::array<vx::char_t, vx::uuid_size                        > pipeline_cache_uuid = {};
        vx::physical_device_limits                                   limits              = {};
        vx::physical_device_sparse_properties                        sparse_properties   = {};
    };
    struct physical_device_memory_properties : vx::enable_conversion<vx::physical_device_memory_properties, VkPhysicalDeviceMemoryProperties2>
    {
        vx::structure_t                                      structure_type    = vx::structure_type_e::physical_device_memory_properties;
        vx::next_t                                           next              = {};
        vx::uint32_t                                         memory_type_count = {}; //TODO: inplace_array/vector/whatever
        vx::array<vx::memory_type, vx::maximum_memory_types> memory_types      = {}; //(pre-allocated max memory limit, count for current size)
        vx::uint32_t                                         memory_heap_count = {}; //IDEM
        vx::array<vx::memory_heap, vx::maximum_memory_heaps> memory_heaps      = {};
    };
    struct surface_format : vx::enable_conversion<vx::surface_format, VkSurfaceFormat2KHR>
    {
        vx::structure_t   structure_type = vx::structure_type_e::surface_format;
        vx::next_t        next           = {};
        vx::format_e      format         = {};
        vx::color_space_e color_space    = {};
    };
    struct physical_device_surface_info : vx::enable_conversion<vx::physical_device_surface_info, VkPhysicalDeviceSurfaceInfo2KHR>
    {
        vx::structure_t structure_type = vx::structure_type_e::physical_device_surface_info;
        vx::next_t      next           = {};
        vx::surface_t   surface        = {};
    };
    struct swap_chain_create_info : vx::enable_conversion<vx::swap_chain_create_info, VkSwapchainCreateInfoKHR>
    {
        vx::structure_t               structure_type       = vx::structure_type_e::swap_chain_create_info;
        vx::next_t                    next                 = {};
        vx::swap_chain_create_flags_e flags                = {};
        vx::surface_t                 surface              = {};
        vx::uint32_t                  minimum_image_count  = {};
        vx::format_e                  image_format         = {};
        vx::color_space_e             image_color_space    = {};
        vx::extent_2d                 image_extent         = {};
        vx::uint32_t                  image_array_layers   = {};
        vx::image_usage_flags_e       image_usage          = {};
        vx::sharing_mode_e            image_sharing_mode   = {};
        vx::padded_span<vx::uint32_t> queue_family_indices = {};
        vx::surface_transform_flags_e pre_transform        = {};
        vx::composite_alpha_flags_e   composite_alpha      = {};
        vx::presentation_mode_e       presentation_mode    = {};
        vx::bool32_t                  clipped              = {};
        vx::swap_chain_t              old_swap_chain       = {};
    };
    struct device_queue_create_info : vx::enable_conversion<device_queue_create_info, VkDeviceQueueCreateInfo>
    {
        vx::structure_t                      structure_type     = vx::structure_type_e::device_queue_create_info;
        vx::next_t                           next               = {};
        vx::device_queue_create_flags_e      flags              = {};
        vx::uint32_t                         queue_family_index = {};
        vx::padded_span<const vx::float32_t> queue_priorities   = {};
    };
    struct physical_device_vulkan_1_3_features : vx::enable_conversion<vx::physical_device_vulkan_1_3_features, VkPhysicalDeviceVulkan13Features>
    {
        vx::structure_t structure_type                                            = vx::structure_type_e::physical_device_vulkan_1_3_features;
        vx::next_t      next                                                      = {};
        vx::bool32_t    robust_image_access                                       = {};
        vx::bool32_t    inline_uniform_block                                      = {};
        vx::bool32_t    descriptor_binding_inline_uniform_block_update_after_bind = {};
        vx::bool32_t    pipeline_creation_cache_control                           = {};
        vx::bool32_t    private_data                                              = {};
        vx::bool32_t    shader_demote_to_helper_invocation                        = {};
        vx::bool32_t    shader_terminate_invocation                               = {};
        vx::bool32_t    subgroup_size_control                                     = {};
        vx::bool32_t    compute_full_subgroups                                    = {};
        vx::bool32_t    synchronization                                           = {};
        vx::bool32_t    texture_compression_astc_hdr                              = {};
        vx::bool32_t    shader_zero_initialize_workgroup_memory                   = {};
        vx::bool32_t    dynamic_rendering                                         = {};
        vx::bool32_t    shader_integer_dot_product                                = {};
        vx::bool32_t    maintenance                                               = {};
    };
    struct physical_device_extended_dynamic_state_features : vx::enable_conversion<vx::physical_device_extended_dynamic_state_features, VkPhysicalDeviceExtendedDynamicStateFeaturesEXT>
    {
        vx::structure_t structure_type         = vx::structure_type_e::physical_device_extended_dynamic_state_features;
        vx::next_t      next                   = {};
        vx::bool32_t    extended_dynamic_state = {};
    };
    struct image_view_create_info : vx::enable_conversion<vx::image_view_create_info, VkImageViewCreateInfo>
    {
        vx::structure_t               structure_type     = vx::structure_type_e::image_view_create_info;
        vx::next_t                    next               = {};
        vx::image_view_create_flags_e flags              = {};
        vx::image                     image              = {};
        vx::image_view_type_e         view_type          = {};
        vx::format_e                  format             = {};
        vx::component_mapping         component_mapping  = {};
        vx::image_sub_resource_range  sub_resource_range = {};
    };
    struct shader_module_create_info : vx::enable_conversion<vx::shader_module_create_info, VkShaderModuleCreateInfo>
    {
        vx::structure_t                   structure_type = vx::structure_type_e::shader_module_create_info;
        vx::next_t                        next           = {};
        vx::shader_module_create_flags_e  flags          = {};
        vx::size_t                        code_size      = {}; //TODO: span (64-bit size type required)
        vx::pointer_t<const vx::uint32_t> code           = {};
    };
    struct pipeline_shader_stage_create_info : vx::enable_conversion<vx::pipeline_shader_stage_create_info, VkPipelineShaderStageCreateInfo>
    {
        vx::structure_t                              structure           = vx::structure_type_e::pipeline_shader_stage_create_info;
        vx::next_t                                   next                = {};
        vx::pipeline_shader_stage_create_flags_e     flags               = {};
        vx::shader_stage_flags_e                     stage               = {};
        vx::shader_module                            module              = {};
        vx::string_view                              name                = {};
        vx::pointer_t<const vx::specialization_info> specialization_info = {};
    };
    struct pipeline_input_assembly_state_create_info : vx::enable_conversion<vx::pipeline_input_assembly_state_create_info, VkPipelineInputAssemblyStateCreateInfo>
    {
        vx::structure_t                                  structure_type           = vx::structure_type_e::pipeline_input_assembly_state_create_info;
        vx::next_t                                       next                     = {};
        vx::pipeline_input_assembly_state_create_flags_e flags                    = {};
        vx::primitive_topology_e                         topology                 = {};
        vx::bool32_t                                     enable_primitive_restart = {};
    };
    struct pipeline_vertex_input_state_create_info : vx::enable_conversion<vx::pipeline_vertex_input_state_create_info, VkPipelineVertexInputStateCreateInfo>
    {
        vx::structure_t                                                structure_type                = vx::structure_type_e::pipeline_vertex_input_state_create_info;
        vx::next_t                                                     next                          = {};
        vx::pipeline_vertex_input_state_create_flags_e                 flags                         = {};
        vx::aligned_span<const vx::vertex_input_binding_description>   vertex_binding_descriptions   = {};
        vx::padded_span <const vx::vertex_input_attribute_description> vertex_attribute_descriptions = {};
    };
    struct pipeline_viewport_state_create_info : vx::enable_conversion<vx::pipeline_viewport_state_create_info, VkPipelineViewportStateCreateInfo>
    {
        vx::structure_t                            structure_type = vx::structure_type_e::pipeline_viewport_state_create_info;
        vx::next_t                                 next           = {};
        vx::pipeline_viewport_state_create_flags_e flags          = {};
        vx::aligned_span<const vx::viewport    >   viewports      = {};
        vx::padded_span <const vx::rectangle_2d>   scissors       = {};
    };
    struct pipeline_rasterization_state_create_info : vx::enable_conversion<vx::pipeline_rasterization_state_create_info, VkPipelineRasterizationStateCreateInfo>
    {
        vx::structure_t                                 structure_type               = vx::structure_type_e::pipeline_rasterization_state_create_info;
        vx::next_t                                      next                         = {};
        vx::pipeline_rasterization_state_create_flags_e flags                        = {};
        vx::bool32_t                                    enable_depth_clamp           = {};
        vx::bool32_t                                    enable_rasterization_discard = {};
        vx::polygon_mode_e                              polygon_mode                 = {};
        vx::culling_mode_e                              culling_mode                 = {};
        vx::front_face_e                                front_face                   = {};
        vx::bool32_t                                    enable_depth_bias            = {};
        vx::float32_t                                   depth_bias_constant_factor   = {};
        vx::float32_t                                   depth_bias_clamp             = {};
        vx::float32_t                                   depth_bias_slope_factor      = {};
        vx::float32_t                                   line_width                   = {};
    };
    struct pipeline_multisample_state_create_info : vx::enable_conversion<vx::pipeline_multisample_state_create_info, VkPipelineMultisampleStateCreateInfo>
    {
        vx::structure_t                               structure_type           = vx::structure_type_e::pipeline_multisample_state_create_info;
        vx::next_t                                    next                     = {};
        vx::pipeline_multisample_state_create_flags_e flags                    = {};
        vx::sample_count_e                            rasterization_samples    = {};
        vx::bool32_t                                  enable_sample_shading    = {};
        vx::float32_t                                 minimum_sample_shading   = {};
        vx::pointer_t<const vx::sample_mask>          sample_mask              = {}; //TODO: ...? check docs or smth
        vx::bool32_t                                  enable_alpha_to_coverage = {};
        vx::bool32_t                                  enable_alpha_to_one      = {};
    };
    struct command_pool_create_info : vx::enable_conversion<vx::command_pool_create_info, VkCommandPoolCreateInfo>
    {
        vx::structure_t                 structure_type     = vx::structure_type_e::command_pool_create_info;
        vx::next_t                      next               = {};
        vx::command_pool_create_flags_e flags              = {};
        vx::uint32_t                    queue_family_index = {};
    };
    struct logical_device_create_info : vx::enable_conversion<vx::logical_device_create_info, VkDeviceCreateInfo>
    {
        vx::structure_t                                      structure_type          = vx::structure_type_e::logical_device_create_info;
        vx::next_t                                           next                    = {};
        vx::logical_device_create_flags_e                    flags                   = {};
        vx::aligned_span<const vx::device_queue_create_info> queue_create_info       = {};
        vx::padded_span <const vx::string_view>              enabled_layer_names     = {}; //deprecated
        vx::padded_span <const vx::string_view>              enabled_extension_names = {};
        vx::pointer_t   <const vx::physical_device_features> enabled_features        = {};
    };





    template<> struct vx::chain_link<vx::physical_device_features           , vx::physical_device_vulkan_1_3_features            > : std::true_type {};
    template<> struct vx::chain_link<vx::physical_device_vulkan_1_3_features, vx::physical_device_extended_dynamic_state_features> : std::true_type {};
}
