//export module vx.pipeline;
//
//import std;
//import <vulkan/vulkan.h>;
//import <vulkan/vulkan_raii.hpp>;
//import <glm/glm.hpp>; //REMOVE
//import vx;
//import vx.logical_device;
//import vx.swap_chain;
//
//export namespace vx
//{
//    auto read_file(const std::filesystem::path& path) -> std::vector<vx::byte_t>
//    {
//        auto file = std::ifstream{ path, std::ios::binary };
//        if (!file) throw std::invalid_argument{ "Could not open file!" };
//
//        file.seekg(0, std::ios::end);
//        const auto file_size = static_cast<vx::size_t>(file.tellg());
//        file.seekg(0, std::ios::beg);
//
//        auto buffer = std::vector<vx::byte_t>(file_size);
//        file.read(reinterpret_cast<char*>(buffer.data()), file_size);
//        if (!file) throw std::runtime_error{ "Could not read file!" };
//
//        return buffer;
//    };
//
//
//
//    template<std::convertible_to<vx::logical_device_t> T>
//    auto create_shader_module(T logical_device, const vx::shader_module_create_info& shader_module_create_info) -> vx::shader_module
//    {
//        auto vk_shader_module = vx::shader_module_t{};
//        ::vkCreateShaderModule(logical_device, shader_module_create_info, nullptr, &vk_shader_module);
//
//        return vk_shader_module;
//    }
//
//    struct my_vertex 
//    {
//        glm::vec2 position;
//        glm::vec3 color;
//        
//        static auto vertex_input_binding_description  () -> vx::vertex_input_binding_description
//        {
//            return vx::vertex_input_binding_description
//            { 
//                .binding    = vx::uint32_t{ 0u }             , 
//                .stride     = sizeof(vx::my_vertex)          , 
//                .input_rate = vx::vertex_input_rate_e::vertex, 
//            };
//        }
//        static auto vertex_input_attribute_description() -> std::array<vx::vertex_input_attribute_description, 2u>
//        {
//            return std::array<vx::vertex_input_attribute_description, 2u>
//            {
//                vx::vertex_input_attribute_description
//                {
//                    .format   = vx::format_e::r32g32_sfloat      , 
//                    .offset   = offsetof(vx::my_vertex, position), 
//                }, 
//                vx::vertex_input_attribute_description
//                { 
//                    .location = vx::uint32_t{ 1u }               , 
//                    .format   = vx::format_e::r32g32b32_sfloat   , 
//                    .offset   = offsetof(vx::my_vertex, color)   , 
//                }, 
//            };
//        };
//    };
//    const auto my_vertices = std::vector<vx::my_vertex>
//    {
//        vx::my_vertex{ {  0.0f, -0.5f }, { 1.0f, 0.0f, 0.0f } }, 
//        vx::my_vertex{ {  0.5f,  0.5f }, { 0.0f, 1.0f, 0.0f } }, 
//        vx::my_vertex{ { -0.5f,  0.5f }, { 0.0f, 0.0f, 1.0f } }, 
//    };
//
//
//
//
//
//    enum class pipeline_color_blend_state_create_flags_e : std::underlying_type_t<VkPipelineColorBlendStateCreateFlagBits>
//    {
//        rasterization_order_attachment_access = VkPipelineColorBlendStateCreateFlagBits::VK_PIPELINE_COLOR_BLEND_STATE_CREATE_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_BIT_EXT, 
//        maximum                               = VkPipelineColorBlendStateCreateFlagBits::VK_PIPELINE_COLOR_BLEND_STATE_CREATE_FLAG_BITS_MAX_ENUM                           , 
//    };
//    enum class logical_operation_e : std::underlying_type_t<VkLogicOp>
//    {
//        clear         = VK_LOGIC_OP_CLEAR        , 
//        and_          = VK_LOGIC_OP_AND          , 
//        and_reverse   = VK_LOGIC_OP_AND_REVERSE  , 
//        copy          = VK_LOGIC_OP_COPY         , 
//        and_inverted  = VK_LOGIC_OP_AND_INVERTED , 
//        no_op         = VK_LOGIC_OP_NO_OP        , 
//        xor_          = VK_LOGIC_OP_XOR          , 
//        or_           = VK_LOGIC_OP_OR           , 
//        nor           = VK_LOGIC_OP_NOR          , 
//        equivalent    = VK_LOGIC_OP_EQUIVALENT   , 
//        invert        = VK_LOGIC_OP_INVERT       , 
//        or_reverse    = VK_LOGIC_OP_OR_REVERSE   , 
//        copy_inverted = VK_LOGIC_OP_COPY_INVERTED, 
//        or_inverted   = VK_LOGIC_OP_OR_INVERTED  , 
//        nand          = VK_LOGIC_OP_NAND         , 
//        set           = VK_LOGIC_OP_SET          , 
//        maximum       = VK_LOGIC_OP_MAX_ENUM     , 
//    };
//    enum class pipeline_dynamic_state_create_flags_e : std::underlying_type_t<vx::flag_t>
//    {
//
//    };
//    enum class pipeline_layout_create_flags_e : std::underlying_type_t<VkPipelineLayoutCreateFlagBits>
//    {
//        independent_sets = VK_PIPELINE_LAYOUT_CREATE_INDEPENDENT_SETS_BIT_EXT, 
//        maximum          = VK_PIPELINE_LAYOUT_CREATE_FLAG_BITS_MAX_ENUM      , 
//    };
//    enum class pipeline_create_flags_e : std::underlying_type_t<VkPipelineCreateFlagBits>
//    {
//        disable_optimization                                 = VkPipelineCreateFlagBits::VK_PIPELINE_CREATE_DISABLE_OPTIMIZATION_BIT                                    , 
//        allow_derivatives                                    = VkPipelineCreateFlagBits::VK_PIPELINE_CREATE_ALLOW_DERIVATIVES_BIT                                       , 
//        derivative                                           = VkPipelineCreateFlagBits::VK_PIPELINE_CREATE_DERIVATIVE_BIT                                              , 
//        view_index_from_device_index                         = VkPipelineCreateFlagBits::VK_PIPELINE_CREATE_VIEW_INDEX_FROM_DEVICE_INDEX_BIT                            , 
//        dispatch_base                                        = VkPipelineCreateFlagBits::VK_PIPELINE_CREATE_DISPATCH_BASE_BIT                                           , 
//        fail_on_pipeline_compile_required                    = VkPipelineCreateFlagBits::VK_PIPELINE_CREATE_FAIL_ON_PIPELINE_COMPILE_REQUIRED_BIT                       , 
//        early_return_on_failure                              = VkPipelineCreateFlagBits::VK_PIPELINE_CREATE_EARLY_RETURN_ON_FAILURE_BIT                                 , 
//        no_protected_access                                  = VkPipelineCreateFlagBits::VK_PIPELINE_CREATE_NO_PROTECTED_ACCESS_BIT                                     , 
//        protected_access_only                                = VkPipelineCreateFlagBits::VK_PIPELINE_CREATE_PROTECTED_ACCESS_ONLY_BIT                                   , 
//        ray_tracing_no_null_any_hit_shaders                  = VkPipelineCreateFlagBits::VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_ANY_HIT_SHADERS_BIT_KHR                 , 
//        ray_tracing_no_null_closest_hit_shaders              = VkPipelineCreateFlagBits::VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_CLOSEST_HIT_SHADERS_BIT_KHR             , 
//        ray_tracing_no_null_miss_shaders                     = VkPipelineCreateFlagBits::VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_MISS_SHADERS_BIT_KHR                    , 
//        ray_tracing_no_null_intersection_shaders             = VkPipelineCreateFlagBits::VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_INTERSECTION_SHADERS_BIT_KHR            , 
//        ray_tracing_skip_triangles                           = VkPipelineCreateFlagBits::VK_PIPELINE_CREATE_RAY_TRACING_SKIP_TRIANGLES_BIT_KHR                          , 
//        ray_tracing_skip_aabbs                               = VkPipelineCreateFlagBits::VK_PIPELINE_CREATE_RAY_TRACING_SKIP_AABBS_BIT_KHR                              , 
//        ray_tracing_shader_group_handle_capture_replay       = VkPipelineCreateFlagBits::VK_PIPELINE_CREATE_RAY_TRACING_SHADER_GROUP_HANDLE_CAPTURE_REPLAY_BIT_KHR      , 
//        defer_compile                                        = VkPipelineCreateFlagBits::VK_PIPELINE_CREATE_DEFER_COMPILE_BIT_NV                                        , 
//        rendering_fragment_density_map_attachment            = VkPipelineCreateFlagBits::VK_PIPELINE_CREATE_RENDERING_FRAGMENT_DENSITY_MAP_ATTACHMENT_BIT_EXT           , 
//        rendering_fragment_shading_rate_attachment           = VkPipelineCreateFlagBits::VK_PIPELINE_CREATE_RENDERING_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR          , 
//        capture_statistics                                   = VkPipelineCreateFlagBits::VK_PIPELINE_CREATE_CAPTURE_STATISTICS_BIT_KHR                                  , 
//        capture_internal_representations                     = VkPipelineCreateFlagBits::VK_PIPELINE_CREATE_CAPTURE_INTERNAL_REPRESENTATIONS_BIT_KHR                    , 
//        indirect_bindable                                    = VkPipelineCreateFlagBits::VK_PIPELINE_CREATE_INDIRECT_BINDABLE_BIT_NV                                    , 
//        library                                              = VkPipelineCreateFlagBits::VK_PIPELINE_CREATE_LIBRARY_BIT_KHR                                             , 
//        descriptor_buffer                                    = VkPipelineCreateFlagBits::VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT                                   , 
//        retain_link_time_optimization_info                   = VkPipelineCreateFlagBits::VK_PIPELINE_CREATE_RETAIN_LINK_TIME_OPTIMIZATION_INFO_BIT_EXT                  , 
//        link_time_optimization                               = VkPipelineCreateFlagBits::VK_PIPELINE_CREATE_LINK_TIME_OPTIMIZATION_BIT_EXT                              , 
//        ray_tracing_allow_motion                             = VkPipelineCreateFlagBits::VK_PIPELINE_CREATE_RAY_TRACING_ALLOW_MOTION_BIT_NV                             , 
//        color_attachment_feedback_loop                       = VkPipelineCreateFlagBits::VK_PIPELINE_CREATE_COLOR_ATTACHMENT_FEEDBACK_LOOP_BIT_EXT                      , 
//        depth_stencil_attachment_feedback_loop               = VkPipelineCreateFlagBits::VK_PIPELINE_CREATE_DEPTH_STENCIL_ATTACHMENT_FEEDBACK_LOOP_BIT_EXT              , 
//        ray_tracing_opacity_micromap                         = VkPipelineCreateFlagBits::VK_PIPELINE_CREATE_RAY_TRACING_OPACITY_MICROMAP_BIT_EXT                        , 
//        maximum                                              = VkPipelineCreateFlagBits::VK_PIPELINE_CREATE_FLAG_BITS_MAX_ENUM                                          , 
//    };
//    enum class pipeline_tessellation_state_create_flags_e : std::underlying_type_t<vx::flag_t>
//    {
//
//    };
//    enum class pipeline_depth_stencil_state_create_flags_e : std::underlying_type_t<VkPipelineDepthStencilStateCreateFlagBits>
//    {
//        rasterization_order_attachment_depth_access   = VK_PIPELINE_DEPTH_STENCIL_STATE_CREATE_RASTERIZATION_ORDER_ATTACHMENT_DEPTH_ACCESS_BIT_EXT  , 
//        rasterization_order_attachment_stencil_access = VK_PIPELINE_DEPTH_STENCIL_STATE_CREATE_RASTERIZATION_ORDER_ATTACHMENT_STENCIL_ACCESS_BIT_EXT, 
//        maximum                                       = VK_PIPELINE_DEPTH_STENCIL_STATE_CREATE_FLAG_BITS_MAX_ENUM                                   , 
//    };
//    enum class compare_operation_e : std::underlying_type_t<VkCompareOp>
//    {
//        never            = VK_COMPARE_OP_NEVER           , 
//        less             = VK_COMPARE_OP_LESS            , 
//        equal            = VK_COMPARE_OP_EQUAL           , 
//        less_or_equal    = VK_COMPARE_OP_LESS_OR_EQUAL   , 
//        greater          = VK_COMPARE_OP_GREATER         , 
//        not_equal        = VK_COMPARE_OP_NOT_EQUAL       , 
//        greater_or_equal = VK_COMPARE_OP_GREATER_OR_EQUAL, 
//        always           = VK_COMPARE_OP_ALWAYS          , 
//        maximum          = VK_COMPARE_OP_MAX_ENUM        , 
//    };
//    enum class stencil_operation_e : std::underlying_type_t<VkStencilOp>
//    {
//        keep                = VK_STENCIL_OP_KEEP               , 
//        zero                = VK_STENCIL_OP_ZERO               , 
//        replace             = VK_STENCIL_OP_REPLACE            , 
//        increment_and_clamp = VK_STENCIL_OP_INCREMENT_AND_CLAMP, 
//        decrement_and_clamp = VK_STENCIL_OP_DECREMENT_AND_CLAMP, 
//        invert              = VK_STENCIL_OP_INVERT             , 
//        increment_and_wrap  = VK_STENCIL_OP_INCREMENT_AND_WRAP , 
//        decrement_and_wrap  = VK_STENCIL_OP_DECREMENT_AND_WRAP , 
//        maximum             = VK_STENCIL_OP_MAX_ENUM           , 
//    };
//
//    using descriptor_set_layout_t = VkDescriptorSetLayout;
//    using pipeline_layout_t       = VkPipelineLayout;
//    using pipeline_cache_t        = VkPipelineCache;
//
//    struct push_constant_range
//    {
//        vx::shader_stage_flags_e flags  = {};
//        vx::uint32_t             offset = {};
//        vx::uint32_t             size   = {};
//    };
//    struct pipeline_color_blend_state_create_info : vx::enable_conversion<vx::pipeline_color_blend_state_create_info, VkPipelineColorBlendStateCreateInfo>
//    {
//        vx::structure_t                                                   structure_type         = vx::structure_type_e::pipeline_color_blend_state_create_info;
//        vx::next_t                                                        next                   = {};
//        vx::pipeline_color_blend_state_create_flags_e                     flags                  = {};
//        vx::bool32_t                                                      enable_logic_operation = {};
//        vx::logical_operation_e                                           logical_operation      = {};
//        vx::aligned_span<const vx::pipeline_color_blend_attachment_state> attachments            = {};
//        vx::array<vx::float32_t, 4u>                                      blending_constants     = {};
//    };
//    struct pipeline_dynamic_state_create_info : vx::enable_conversion<vx::pipeline_dynamic_state_create_info, VkPipelineDynamicStateCreateInfo>
//    {
//        vx::structure_t                             structure_type = vx::structure_type_e::pipeline_dynamic_state_create_info;
//        vx::next_t                                  next           = {};
//        vx::pipeline_dynamic_state_create_flags_e   flags          = {};
//        vx::aligned_span<const vx::dynamic_state_e> dynamic_states = {};
//    };
//    struct pipeline_layout_create_info : vx::enable_conversion<vx::pipeline_layout_create_info, VkPipelineLayoutCreateInfo>
//    {
//        vx::structure_t                                     structure_type       = vx::structure_type_e::pipeline_layout_create_info;
//        vx::next_t                                          next                 = {};
//        vx::pipeline_layout_create_flags_e                  flags                = {};
//        vx::aligned_span<const vx::descriptor_set_layout_t> layouts              = {};
//        vx::padded_span <const vx::push_constant_range    > push_constant_ranges = {};
//    };
//    struct pipeline_rendering_create_info : vx::enable_conversion<vx::pipeline_rendering_create_info, VkPipelineRenderingCreateInfo>
//    {
//        vx::structure_t                      structure_type            = vx::structure_type_e::pipeline_rendering_create_info;
//        vx::next_t                           next                      = {};
//        vx::uint32_t                         view_mask                 = {};
//        vx::aligned_span<const vx::format_e> color_attachment_formats  = {};
//        vx::format_e                         depth_attachment_format   = {};
//        vx::format_e                         stencil_attachment_format = {};
//    };
//    struct pipeline_tessellation_state_create_info : vx::enable_conversion<vx::pipeline_tessellation_state_create_info, VkPipelineTessellationStateCreateInfo>
//    {
//        vx::structure_t                                structure_type       = vx::structure_type_e::pipeline_tessellation_state_create_info;
//        vx::next_t                                     next                 = {};
//        vx::pipeline_tessellation_state_create_flags_e flags                = {};
//        vx::uint32_t                                   patch_control_points = {};
//    };
//    struct stencil_operation_state : vx::enable_conversion<vx::stencil_operation_state, VkStencilOpState>
//    {
//        vx::stencil_operation_e fail_operation       = {};
//        vx::stencil_operation_e pass_operation       = {};
//        vx::stencil_operation_e depth_fail_operation = {};
//        vx::compare_operation_e compare_operation    = {};
//        vx::uint32_t            compare_mask         = {};
//        vx::uint32_t            write_mask           = {};
//        vx::uint32_t            reference            = {};
//    };
//    struct pipeline_depth_stencil_state_create_info : vx::enable_conversion<vx::pipeline_depth_stencil_state_create_info, VkPipelineDepthStencilStateCreateInfo>
//    {
//        vx::structure_t                                 structure_type           = vx::structure_type_e::pipeline_depth_stencil_state_create_info;
//        vx::next_t                                      next                     = {};
//        vx::pipeline_depth_stencil_state_create_flags_e flags                    = {};
//        vx::bool32_t                                    enable_depth_test        = {};
//        vx::bool32_t                                    enable_depth_write       = {};
//        vx::compare_operation_e                         depth_compare_operation  = {};
//        vx::bool32_t                                    enable_depth_bounds_test = {};
//        vx::bool32_t                                    enable_stencil_test      = {};
//        vx::stencil_operation_e                         front                    = {};
//        vx::stencil_operation_e                         back                     = {};
//        vx::float32_t                                   minimum_depth_bounds     = {};
//        vx::float32_t                                   maximum_depth_bounds     = {};
//    };
//    struct graphics_pipeline_create_info : vx::enable_conversion<vx::graphics_pipeline_create_info, VkGraphicsPipelineCreateInfo>
//    {
//        vx::structure_t                                                       structure_type       = vx::structure_type_e::graphics_pipeline_create_info;
//        vx::next_t                                                            next                 = {};
//        vx::pipeline_create_flags_e                                           flags                = {};
//        vx::aligned_span<const vx::pipeline_shader_stage_create_info        > stages               = {};
//        vx::pointer_t   <const vx::pipeline_vertex_input_state_create_info  > vertex_input_state   = {};
//        vx::pointer_t   <const vx::pipeline_input_assembly_state_create_info> input_assembly_state = {};
//        vx::pointer_t   <const vx::pipeline_tessellation_state_create_info  > tessellation_state   = {};
//        vx::pointer_t   <const vx::pipeline_viewport_state_create_info      > viewport_state       = {};
//        vx::pointer_t   <const vx::pipeline_rasterization_state_create_info > rasterization_state  = {};
//        vx::pointer_t   <const vx::pipeline_multisample_state_create_info   > multisample_state    = {};
//        vx::pointer_t   <const vx::pipeline_depth_stencil_state_create_info > depth_stencil_state  = {};
//        vx::pointer_t   <const vx::pipeline_color_blend_state_create_info   > color_blending_state = {};
//        vx::pointer_t   <const vx::pipeline_dynamic_state_create_info       > dynamic_state        = {};
//        vx::pipeline_layout_t                                                 layout               = {};
//        vx::render_pass_t                                                     render_pass          = {};
//        vx::uint32_t                                                          sub_pass             = {};
//        vx::pipeline_t                                                        base_pipeline_handle = {};
//        vx::int32_t                                                           base_pipeline_index  = {};
//    };
//
//
//
//    template<std::convertible_to<vx::logical_device_t> T>
//    auto create_pipeline_layout(T logical_device, const vx::pipeline_layout_create_info& pipeline_layout_create_info) -> vx::pipeline_layout_t
//    {
//        auto vk_pipeline_layout = vx::pipeline_layout_t{};
//        const auto result = std::bit_cast<vx::result_e>(::vkCreatePipelineLayout(logical_device, pipeline_layout_create_info, nullptr, &vk_pipeline_layout));
//        if (result != vx::result_e::success) throw std::runtime_error{ "" };
//
//        return vk_pipeline_layout;
//    }
//    template<std::convertible_to<vx::logical_device_t> T>
//    auto create_graphics_pipelines(T logical_device, vx::span<const vx::graphics_pipeline_create_info> graphics_pipeline_create_info) -> std::vector<vx::pipeline_t>
//    {
//        const auto size                  = graphics_pipeline_create_info.size();
//        const auto data                  = std::bit_cast<const vx::graphics_pipeline_create_info::native_t*>(graphics_pipeline_create_info.data());
//              auto vk_graphics_pipelines = std::vector<vx::pipeline_t>(size);
//        const auto result                = std::bit_cast<vx::result_e>(::vkCreateGraphicsPipelines(logical_device, nullptr, size, data, nullptr, vk_graphics_pipelines.data()));
//        if (result != vx::result_e::success) throw std::runtime_error{ "" };
//
//        return vk_graphics_pipelines;
//    }
//
//
//    class pipeline
//    {
//    public:
//        pipeline(vx::logical_device logical_device, vx::swap_chain swap_chain)
//        {
//            const auto shader_file_path                      = std::filesystem::path{ "slang.spv" };
//            const auto shader_module                         = std::invoke([&](const std::vector<vx::byte_t>& code) -> vx::shader_module
//                {
//                    const auto shader_module_create_info = vx::shader_module_create_info
//                    { 
//                        .code_size = code.size() * sizeof(vx::uint8_t)         , 
//                        .code      = std::bit_cast<const vx::uint32_t*>(code.data()), 
//                    };
//
//                    return vx::create_shader_module(logical_device, shader_module_create_info);
//                }, vx::read_file(shader_file_path));
//            const auto vertex_shader_stage_info              = vx::pipeline_shader_stage_create_info
//            { 
//                .stage  = vx::shader_stage_flags_e::vertex, 
//                .module = shader_module                   , 
//                .name   = "vertMain"                      , 
//            };
//            const auto fragment_shader_stage_info            = vx::pipeline_shader_stage_create_info
//            {
//                .stage  = vx::shader_stage_flags_e::fragment, 
//                .module = shader_module                     , 
//                .name   = "fragMain"                        , 
//            };
//            const auto shader_stages                         = vx::array<vx::pipeline_shader_stage_create_info, 2u>
//            {
//                vertex_shader_stage_info  , 
//                fragment_shader_stage_info, 
//            };
//            const auto input_assembly_state_create_info      = vx::pipeline_input_assembly_state_create_info
//            {
//                .topology = vx::primitive_topology_e::triangle_list, 
//            };
//            
//            const auto vertex_input_binding_description      = vx::my_vertex::vertex_input_binding_description  ();
//            const auto vertex_input_attribute_description    = vx::my_vertex::vertex_input_attribute_description();
//            const auto vertex_input_state_create_info        = vx::pipeline_vertex_input_state_create_info
//            {
//                .vertex_binding_descriptions   = vx::span{ &vertex_input_binding_description , 1u }, 
//                .vertex_attribute_descriptions = vx::span{ vertex_input_attribute_description     }, 
//            };
//            const auto viewport_state_create_info            = vx::pipeline_viewport_state_create_info
//            {
//                .viewports = vx::span<const vx::viewport    >{}, 
//                .scissors  = vx::span<const vx::rectangle_2d>{}, 
//            };
//            const auto rasterization_state_create_info       = vx::pipeline_rasterization_state_create_info
//            {
//                .polygon_mode = vx::polygon_mode_e::fill   , 
//                .culling_mode = vx::culling_mode_e::back   , 
//                .front_face   = vx::front_face_e::clockwise, 
//                .line_width   = vx::float32_t{ 1.0f }      , 
//            };
//            const auto multisample_create_info               = vx::pipeline_multisample_state_create_info
//            {
//                .rasterization_samples = vx::sample_count_e::_1,
//            };
//            const auto pipeline_color_blend_attachment_state = vx::pipeline_color_blend_attachment_state
//            {
//                .color_write_mask = vx::color_component_e::r | vx::color_component_e::g | vx::color_component_e::b | vx::color_component_e::a
//            };
//            const auto color_blending_state_create_info      = vx::pipeline_color_blend_state_create_info
//            {
//                .logical_operation = vx::logical_operation_e::copy                                         , 
//                .attachments       = vx::span{ &pipeline_color_blend_attachment_state, vx::uint32_t{ 1u } }, 
//            };
//
//            const auto dynamic_states                        = std::vector<vx::dynamic_state_e>
//            {
//                vx::dynamic_state_e::viewport, 
//                vx::dynamic_state_e::scissor , 
//            };
//            const auto pipeline_dynamic_state_create_info    = vx::pipeline_dynamic_state_create_info
//            {
//                .dynamic_states = vx::span{ dynamic_states }, 
//            };
//            const auto pipeline_layout_create_info           = vx::pipeline_layout_create_info
//            {
//
//            };
//
//            layout_ = vx::create_pipeline_layout(logical_device, pipeline_layout_create_info);
//
//            const auto swap_chain_image_format               = swap_chain.image_format();
//            const auto pipeline_rendering_create_info        = vx::pipeline_rendering_create_info
//            {
//                .color_attachment_formats = vx::span{ &swap_chain_image_format, vx::uint32_t{ 1u } }, 
//            };
//            const auto graphics_pipeline_create_info         = vx::graphics_pipeline_create_info
//            {
//                .next                 = &pipeline_rendering_create_info    , 
//                .stages               = shader_stages                      , 
//                .vertex_input_state   = &vertex_input_state_create_info    , 
//                .input_assembly_state = &input_assembly_state_create_info  , 
//                .viewport_state       = &viewport_state_create_info        , 
//                .rasterization_state  = &rasterization_state_create_info   , 
//                .multisample_state    = &multisample_create_info           , 
//                .color_blending_state = &color_blending_state_create_info  , 
//                .dynamic_state        = &pipeline_dynamic_state_create_info, 
//                .layout               = layout_                            , 
//            };
//
//            const auto pipelines = vx::create_graphics_pipelines(logical_device, vx::span{ &graphics_pipeline_create_info, vx::uint32_t{ 1u } });
//            pipeline_ = pipelines.at(0u);
//        }
//
//    private:
//        vx::pipeline_t        pipeline_;
//        vx::pipeline_layout_t layout_;
//    };
//}
