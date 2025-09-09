export module vx.flags;

import std;
import <vulkan/vulkan.h>;
import vx.types;

export namespace vx
{
    constexpr auto make_api_version(vx::uint32_t variant, vx::uint32_t major, vx::uint32_t minor, vx::uint32_t patch) -> vx::uint32_t
    {
        return (variant << 29u | major << 22u | minor << 12u | patch);
    }

    enum class flag_t : VkFlags;

    enum class api_version_e : vx::uint32_t
    {
        _1_1 = vx::make_api_version(0u, 1u, 1u, 0u), 
        _1_2 = vx::make_api_version(0u, 1u, 2u, 0u), 
        _1_3 = vx::make_api_version(0u, 1u, 3u, 0u), 
        _1_4 = vx::make_api_version(0u, 1u, 4u, 0u), 
    };
    enum class debug_utils_message_severity_e : std::underlying_type_t<VkDebugUtilsMessageSeverityFlagBitsEXT>
    {
        verbose = VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT       , 
        info    = VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT          , 
        warning = VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT       , 
        error   = VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT         , 
        maximum = VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_FLAG_BITS_MAX_ENUM_EXT, 
    };
    enum class debug_utils_message_type_e : std::underlying_type_t<VkDebugUtilsMessageTypeFlagBitsEXT>
    {
        general         = VkDebugUtilsMessageTypeFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT               , 
        validation      = VkDebugUtilsMessageTypeFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT            , 
        performance     = VkDebugUtilsMessageTypeFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT           , 
        address_binding = VkDebugUtilsMessageTypeFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT, 
        maximum         = VkDebugUtilsMessageTypeFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_TYPE_FLAG_BITS_MAX_ENUM_EXT        , 
    };
    enum class debug_utils_messenger_create_flags_e : std::underlying_type_t<VkDebugUtilsMessageTypeFlagBitsEXT>
    {

    };
    enum class instance_create_flags_e : std::underlying_type_t<VkInstanceCreateFlagBits>
    {

    };
    enum class memory_heap_flags_e : std::underlying_type_t<VkMemoryHeapFlagBits>
    {
        device_local   = VkMemoryHeapFlagBits::VK_MEMORY_HEAP_DEVICE_LOCAL_BIT      , 
        multi_instance = VkMemoryHeapFlagBits::VK_MEMORY_HEAP_MULTI_INSTANCE_BIT    , 
        tile_memory    = VkMemoryHeapFlagBits::VK_MEMORY_HEAP_TILE_MEMORY_BIT_QCOM  , 

        _maximum       = VkMemoryHeapFlagBits::VK_MEMORY_HEAP_FLAG_BITS_MAX_ENUM    ,
    };
    enum class memory_property_flags_e : std::underlying_type_t<VkMemoryPropertyFlagBits>
    {
        device_local     = VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT       , 
        host_visible     = VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT       , 
        host_coherent    = VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_HOST_COHERENT_BIT      , 
        host_cached      = VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_HOST_CACHED_BIT        , 
        lazily_allocated = VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT   , 
        protected_       = VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_PROTECTED_BIT          , 
        device_coherent  = VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD, 
        uncached         = VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD, 
        rdma_capable     = VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_RDMA_CAPABLE_BIT_NV    , 
        
        _maximum         = VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_FLAG_BITS_MAX_ENUM     , 
    };
    enum class physical_device_type_e : std::underlying_type_t<VkPhysicalDeviceType>
    {
        other          = VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_OTHER         , 
        integrated_gpu = VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU, 
        discrete_gpu   = VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU  , 
        virtual_gpu    = VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU   , 
        cpu            = VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_CPU           , 
        
        _maximum       = VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_MAX_ENUM      , 
    };
    enum class queue_flags_e : std::underlying_type_t<VkQueueFlagBits>
    {
        graphics       = VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT        , 
        compute        = VkQueueFlagBits::VK_QUEUE_COMPUTE_BIT         , 
        transfer       = VkQueueFlagBits::VK_QUEUE_TRANSFER_BIT        , 
        sparse_binding = VkQueueFlagBits::VK_QUEUE_SPARSE_BINDING_BIT  , 
        protected_     = VkQueueFlagBits::VK_QUEUE_PROTECTED_BIT       , 
        video_decode   = VkQueueFlagBits::VK_QUEUE_VIDEO_DECODE_BIT_KHR, 
        video_encode   = VkQueueFlagBits::VK_QUEUE_VIDEO_ENCODE_BIT_KHR, 
        optical_flow   = VkQueueFlagBits::VK_QUEUE_OPTICAL_FLOW_BIT_NV , 
        data_graph     = VkQueueFlagBits::VK_QUEUE_DATA_GRAPH_BIT_ARM  , 
        
        _maximum       = VkQueueFlagBits::VK_QUEUE_FLAG_BITS_MAX_ENUM  , 
    };
    enum class result_e : std::underlying_type_t<VkResult>
    {
        success               = VkResult::VK_SUCCESS                       , 
        not_ready             = VkResult::VK_NOT_READY                     , 
        timeout               = VkResult::VK_TIMEOUT                       , 
        event_set             = VkResult::VK_EVENT_SET                     , 
        event_reset           = VkResult::VK_EVENT_RESET                   , 
        incomplete            = VkResult::VK_INCOMPLETE                    , 
        out_of_host_memory    = VkResult::VK_ERROR_OUT_OF_HOST_MEMORY      , 
        out_of_device_memory  = VkResult::VK_ERROR_OUT_OF_DEVICE_MEMORY    , 
        initialization_failed = VkResult::VK_ERROR_INITIALIZATION_FAILED   , 
        device_lost           = VkResult::VK_ERROR_DEVICE_LOST             , 
        memory_map_failed     = VkResult::VK_ERROR_MEMORY_MAP_FAILED       , 
        layer_not_present     = VkResult::VK_ERROR_LAYER_NOT_PRESENT       , 
        extension_not_present = VkResult::VK_ERROR_EXTENSION_NOT_PRESENT   , 
        feature_not_present   = VkResult::VK_ERROR_FEATURE_NOT_PRESENT     , 
        incompatible_driver   = VkResult::VK_ERROR_INCOMPATIBLE_DRIVER     , 
        too_many_objects      = VkResult::VK_ERROR_TOO_MANY_OBJECTS        , 
        format_not_supported  = VkResult::VK_ERROR_FORMAT_NOT_SUPPORTED    , 
        surface_lost          = VkResult::VK_ERROR_SURFACE_LOST_KHR        , 
        suboptimal            = VkResult::VK_SUBOPTIMAL_KHR                , 
        out_of_date           = VkResult::VK_ERROR_OUT_OF_DATE_KHR         , 
        incompatible_display  = VkResult::VK_ERROR_INCOMPATIBLE_DISPLAY_KHR,  
        native_window_in_use  = VkResult::VK_ERROR_NATIVE_WINDOW_IN_USE_KHR,  
        validation_failed     = VkResult::VK_ERROR_VALIDATION_FAILED_EXT   , 
        maximum               = VkResult::VK_RESULT_MAX_ENUM               , 
    };
    enum class sample_count_e : std::underlying_type_t<VkSampleCountFlagBits>
    {
        _1       = VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT             , 
        _2       = VkSampleCountFlagBits::VK_SAMPLE_COUNT_2_BIT             , 
        _4       = VkSampleCountFlagBits::VK_SAMPLE_COUNT_4_BIT             , 
        _8       = VkSampleCountFlagBits::VK_SAMPLE_COUNT_8_BIT             , 
        _16      = VkSampleCountFlagBits::VK_SAMPLE_COUNT_16_BIT            , 
        _32      = VkSampleCountFlagBits::VK_SAMPLE_COUNT_32_BIT            , 
        _64      = VkSampleCountFlagBits::VK_SAMPLE_COUNT_64_BIT            , 

        _maximum = VkSampleCountFlagBits::VK_SAMPLE_COUNT_FLAG_BITS_MAX_ENUM, 
    };
    enum class structure_type_e : std::underlying_type_t<VkStructureType>
    {
        application_info                                = VkStructureType::VK_STRUCTURE_TYPE_APPLICATION_INFO                                   , 
        debug_messenger                                 = VkStructureType::VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT              , 
        device_queue_create_info                        = VkStructureType::VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO                           , 
        instance_create_info                            = VkStructureType::VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO                               , 
        logical_device_create_info                      = VkStructureType::VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO                                 , 
        physical_device_extended_dynamic_state_features = VkStructureType::VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_DYNAMIC_STATE_FEATURES_EXT, 
        physical_device_features                        = VkStructureType::VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2                         , 
        physical_device_memory_properties               = VkStructureType::VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PROPERTIES_2                , 
        physical_device_properties                      = VkStructureType::VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2                       , 
        physical_device_surface_info                    = VkStructureType::VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SURFACE_INFO_2_KHR                 , 
        physical_device_vulkan_1_1_features             = VkStructureType::VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES                , 
        physical_device_vulkan_1_1_properties           = VkStructureType::VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_PROPERTIES              , 
        physical_device_vulkan_1_2_features             = VkStructureType::VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES                , 
        physical_device_vulkan_1_2_properties           = VkStructureType::VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_PROPERTIES              , 
        physical_device_vulkan_1_3_features             = VkStructureType::VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES                , 
        physical_device_vulkan_1_3_properties           = VkStructureType::VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_PROPERTIES              , 
        physical_device_vulkan_1_4_features             = VkStructureType::VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_4_FEATURES                , 
        physical_device_vulkan_1_4_properties           = VkStructureType::VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_4_PROPERTIES              , 
        queue_family_properties                         = VkStructureType::VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2                          , 
        surface_format                                  = VkStructureType::VK_STRUCTURE_TYPE_SURFACE_FORMAT_2_KHR                               , 
        swap_chain_create_info                          = VkStructureType::VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR                          , 
    };
    enum class device_queue_create_flags_e : std::underlying_type_t<VkDeviceQueueCreateFlagBits>
    {
        protected_ = VK_DEVICE_QUEUE_CREATE_PROTECTED_BIT     , 
        _maximum   = VK_DEVICE_QUEUE_CREATE_FLAG_BITS_MAX_ENUM, 
    };
    enum class logical_device_create_flags_e : std::underlying_type_t<vx::flag_t>
    {

    };
    enum class surface_transform_flags_e : std::underlying_type_t<VkSurfaceTransformFlagBitsKHR>
    {
        identity                     = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR                    , 
        rotate_90                    = VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR                   , 
        rotate_180                   = VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR                  , 
        rotate_270                   = VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR                  , 
        horizontal_mirror            = VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_BIT_KHR           , 
        horizontal_mirror_rotate_90  = VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90_BIT_KHR , 
        horizontal_mirror_rotate_180 = VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_180_BIT_KHR, 
        horizontal_mirror_rotate_270 = VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270_BIT_KHR, 
        inherit                      = VK_SURFACE_TRANSFORM_INHERIT_BIT_KHR                     , 
        
        _maximum                     = VK_SURFACE_TRANSFORM_FLAG_BITS_MAX_ENUM_KHR              , 
    };
    enum class composite_alpha_flags_e : std::underlying_type_t<VkCompositeAlphaFlagBitsKHR>
    {
        opaque          = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR         , 
        pre_multiplied  = VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR , 
        post_multiplied = VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR, 
        inherit         = VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR        , 
                                                                      
        _maximum        = VK_COMPOSITE_ALPHA_FLAG_BITS_MAX_ENUM_KHR , 
    };
    enum class image_usage_flags_e : std::underlying_type_t<VkImageUsageFlagBits>
    {
        transfer_source                         = VK_IMAGE_USAGE_TRANSFER_SRC_BIT                           , 
        transfer_destination                    = VK_IMAGE_USAGE_TRANSFER_DST_BIT                           , 
        sampled                                 = VK_IMAGE_USAGE_SAMPLED_BIT                                , 
        storage                                 = VK_IMAGE_USAGE_STORAGE_BIT                                , 
        color_attachment                        = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT                       , 
        depth_stencil_attachment                = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT               , 
        transient_attachment                    = VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT                   , 
        input_attachment                        = VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT                       , 
        host_transfer                           = VK_IMAGE_USAGE_HOST_TRANSFER_BIT                          , 
        video_decode_destination                = VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR                   , 
        video_decode_source                     = VK_IMAGE_USAGE_VIDEO_DECODE_SRC_BIT_KHR                   , 
        video_decode_buffer                     = VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR                   , 
        fragment_density_map                    = VK_IMAGE_USAGE_FRAGMENT_DENSITY_MAP_BIT_EXT               , 
        fragment_shading_rate_attachment        = VK_IMAGE_USAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR   , 
        video_encode_destination                = VK_IMAGE_USAGE_VIDEO_ENCODE_DST_BIT_KHR                   , 
        video_encode_source                     = VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR                   , 
        video_encode_buffer                     = VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_BIT_KHR                   , 
        attachment_feedback_loop                = VK_IMAGE_USAGE_ATTACHMENT_FEEDBACK_LOOP_BIT_EXT           , 
        invocation_mask                         = VK_IMAGE_USAGE_INVOCATION_MASK_BIT_HUAWEI                 , 
        sample_weight                           = VK_IMAGE_USAGE_SAMPLE_WEIGHT_BIT_QCOM                     , 
        sample_block_match                      = VK_IMAGE_USAGE_SAMPLE_BLOCK_MATCH_BIT_QCOM                , 
        tensor_aliasing                         = VK_IMAGE_USAGE_TENSOR_ALIASING_BIT_ARM                    , 
        tile_memory                             = VK_IMAGE_USAGE_TILE_MEMORY_BIT_QCOM                       , 
        video_encode_quantization_delta_map     = VK_IMAGE_USAGE_VIDEO_ENCODE_QUANTIZATION_DELTA_MAP_BIT_KHR, 
        video_encode_emphasis_map               = VK_IMAGE_USAGE_VIDEO_ENCODE_EMPHASIS_MAP_BIT_KHR          , 
        shading_rate_image                      = VK_IMAGE_USAGE_SHADING_RATE_IMAGE_BIT_NV                  , 

        _maximum                                = VK_IMAGE_USAGE_FLAG_BITS_MAX_ENUM                         , 
    };
    enum class format_e : std::underlying_type_t<VkFormat>
    {
        undefined                                         = VK_FORMAT_UNDEFINED,
        r4g4_unorm_pack8                                  = VK_FORMAT_R4G4_UNORM_PACK8,
        r4g4b4a4_unorm_pack16                             = VK_FORMAT_R4G4B4A4_UNORM_PACK16,
        b4g4r4a4_unorm_pack16                             = VK_FORMAT_B4G4R4A4_UNORM_PACK16,
        r5g6b5_unorm_pack16                               = VK_FORMAT_R5G6B5_UNORM_PACK16,
        b5g6r5_unorm_pack16                               = VK_FORMAT_B5G6R5_UNORM_PACK16,
        r5g5b5a1_unorm_pack16                             = VK_FORMAT_R5G5B5A1_UNORM_PACK16,
        b5g5r5a1_unorm_pack16                             = VK_FORMAT_B5G5R5A1_UNORM_PACK16,
        a1r5g5b5_unorm_pack16                             = VK_FORMAT_A1R5G5B5_UNORM_PACK16,
        r8_unorm                                          = VK_FORMAT_R8_UNORM,
        r8_snorm                                          = VK_FORMAT_R8_SNORM,
        r8_uscaled                                        = VK_FORMAT_R8_USCALED,
        r8_sscaled                                        = VK_FORMAT_R8_SSCALED,
        r8_uint                                           = VK_FORMAT_R8_UINT,
        r8_sint                                           = VK_FORMAT_R8_SINT,
        r8_srgb                                           = VK_FORMAT_R8_SRGB,
        r8g8_unorm                                        = VK_FORMAT_R8G8_UNORM,
        r8g8_snorm                                        = VK_FORMAT_R8G8_SNORM,
        r8g8_uscaled                                      = VK_FORMAT_R8G8_USCALED,
        r8g8_sscaled                                      = VK_FORMAT_R8G8_SSCALED,
        r8g8_uint                                         = VK_FORMAT_R8G8_UINT,
        r8g8_sint                                         = VK_FORMAT_R8G8_SINT,
        r8g8_srgb                                         = VK_FORMAT_R8G8_SRGB,
        r8g8b8_unorm                                      = VK_FORMAT_R8G8B8_UNORM,
        r8g8b8_snorm                                      = VK_FORMAT_R8G8B8_SNORM,
        r8g8b8_uscaled                                    = VK_FORMAT_R8G8B8_USCALED,
        r8g8b8_sscaled                                    = VK_FORMAT_R8G8B8_SSCALED,
        r8g8b8_uint                                       = VK_FORMAT_R8G8B8_UINT,
        r8g8b8_sint                                       = VK_FORMAT_R8G8B8_SINT,
        r8g8b8_srgb                                       = VK_FORMAT_R8G8B8_SRGB,
        b8g8r8_unorm                                      = VK_FORMAT_B8G8R8_UNORM,
        b8g8r8_snorm                                      = VK_FORMAT_B8G8R8_SNORM,
        b8g8r8_uscaled                                    = VK_FORMAT_B8G8R8_USCALED,
        b8g8r8_sscaled                                    = VK_FORMAT_B8G8R8_SSCALED,
        b8g8r8_uint                                       = VK_FORMAT_B8G8R8_UINT,
        b8g8r8_sint                                       = VK_FORMAT_B8G8R8_SINT,
        b8g8r8_srgb                                       = VK_FORMAT_B8G8R8_SRGB,
        r8g8b8a8_unorm                                    = VK_FORMAT_R8G8B8A8_UNORM,
        r8g8b8a8_snorm                                    = VK_FORMAT_R8G8B8A8_SNORM,
        r8g8b8a8_uscaled                                  = VK_FORMAT_R8G8B8A8_USCALED,
        r8g8b8a8_sscaled                                  = VK_FORMAT_R8G8B8A8_SSCALED,
        r8g8b8a8_uint                                     = VK_FORMAT_R8G8B8A8_UINT,
        r8g8b8a8_sint                                     = VK_FORMAT_R8G8B8A8_SINT,
        r8g8b8a8_srgb                                     = VK_FORMAT_R8G8B8A8_SRGB,
        b8g8r8a8_unorm                                    = VK_FORMAT_B8G8R8A8_UNORM,
        b8g8r8a8_snorm                                    = VK_FORMAT_B8G8R8A8_SNORM,
        b8g8r8a8_uscaled                                  = VK_FORMAT_B8G8R8A8_USCALED,
        b8g8r8a8_sscaled                                  = VK_FORMAT_B8G8R8A8_SSCALED,
        b8g8r8a8_uint                                     = VK_FORMAT_B8G8R8A8_UINT,
        b8g8r8a8_sint                                     = VK_FORMAT_B8G8R8A8_SINT,
        b8g8r8a8_srgb                                     = VK_FORMAT_B8G8R8A8_SRGB,
        a8b8g8r8_unorm_pack32                             = VK_FORMAT_A8B8G8R8_UNORM_PACK32,
        a8b8g8r8_snorm_pack32                             = VK_FORMAT_A8B8G8R8_SNORM_PACK32,
        a8b8g8r8_uscaled_pack32                           = VK_FORMAT_A8B8G8R8_USCALED_PACK32,
        a8b8g8r8_sscaled_pack32                           = VK_FORMAT_A8B8G8R8_SSCALED_PACK32,
        a8b8g8r8_uint_pack32                              = VK_FORMAT_A8B8G8R8_UINT_PACK32,
        a8b8g8r8_sint_pack32                              = VK_FORMAT_A8B8G8R8_SINT_PACK32,
        a8b8g8r8_srgb_pack32                              = VK_FORMAT_A8B8G8R8_SRGB_PACK32,
        a2r10g10b10_unorm_pack32                          = VK_FORMAT_A2R10G10B10_UNORM_PACK32,
        a2r10g10b10_snorm_pack32                          = VK_FORMAT_A2R10G10B10_SNORM_PACK32,
        a2r10g10b10_uscaled_pack32                        = VK_FORMAT_A2R10G10B10_USCALED_PACK32,
        a2r10g10b10_sscaled_pack32                        = VK_FORMAT_A2R10G10B10_SSCALED_PACK32,
        a2r10g10b10_uint_pack32                           = VK_FORMAT_A2R10G10B10_UINT_PACK32,
        a2r10g10b10_sint_pack32                           = VK_FORMAT_A2R10G10B10_SINT_PACK32,
        a2b10g10r10_unorm_pack32                          = VK_FORMAT_A2B10G10R10_UNORM_PACK32,
        a2b10g10r10_snorm_pack32                          = VK_FORMAT_A2B10G10R10_SNORM_PACK32,
        a2b10g10r10_uscaled_pack32                        = VK_FORMAT_A2B10G10R10_USCALED_PACK32,
        a2b10g10r10_sscaled_pack32                        = VK_FORMAT_A2B10G10R10_SSCALED_PACK32,
        a2b10g10r10_uint_pack32                           = VK_FORMAT_A2B10G10R10_UINT_PACK32,
        a2b10g10r10_sint_pack32                           = VK_FORMAT_A2B10G10R10_SINT_PACK32,
        r16_unorm                                         = VK_FORMAT_R16_UNORM,
        r16_snorm                                         = VK_FORMAT_R16_SNORM,
        r16_uscaled                                       = VK_FORMAT_R16_USCALED,
        r16_sscaled                                       = VK_FORMAT_R16_SSCALED,
        r16_uint                                          = VK_FORMAT_R16_UINT,
        r16_sint                                          = VK_FORMAT_R16_SINT,
        r16_sfloat                                        = VK_FORMAT_R16_SFLOAT,
        r16g16_unorm                                      = VK_FORMAT_R16G16_UNORM,
        r16g16_snorm                                      = VK_FORMAT_R16G16_SNORM,
        r16g16_uscaled                                    = VK_FORMAT_R16G16_USCALED,
        r16g16_sscaled                                    = VK_FORMAT_R16G16_SSCALED,
        r16g16_uint                                       = VK_FORMAT_R16G16_UINT,
        r16g16_sint                                       = VK_FORMAT_R16G16_SINT,
        r16g16_sfloat                                     = VK_FORMAT_R16G16_SFLOAT,
        r16g16b16_unorm                                   = VK_FORMAT_R16G16B16_UNORM,
        r16g16b16_snorm                                   = VK_FORMAT_R16G16B16_SNORM,
        r16g16b16_uscaled                                 = VK_FORMAT_R16G16B16_USCALED,
        r16g16b16_sscaled                                 = VK_FORMAT_R16G16B16_SSCALED,
        r16g16b16_uint                                    = VK_FORMAT_R16G16B16_UINT,
        r16g16b16_sint                                    = VK_FORMAT_R16G16B16_SINT,
        r16g16b16_sfloat                                  = VK_FORMAT_R16G16B16_SFLOAT,
        r16g16b16a16_unorm                                = VK_FORMAT_R16G16B16A16_UNORM,
        r16g16b16a16_snorm                                = VK_FORMAT_R16G16B16A16_SNORM,
        r16g16b16a16_uscaled                              = VK_FORMAT_R16G16B16A16_USCALED,
        r16g16b16a16_sscaled                              = VK_FORMAT_R16G16B16A16_SSCALED,
        r16g16b16a16_uint                                 = VK_FORMAT_R16G16B16A16_UINT,
        r16g16b16a16_sint                                 = VK_FORMAT_R16G16B16A16_SINT,
        r16g16b16a16_sfloat                               = VK_FORMAT_R16G16B16A16_SFLOAT,
        r32_uint                                          = VK_FORMAT_R32_UINT,
        r32_sint                                          = VK_FORMAT_R32_SINT,
        r32_sfloat                                        = VK_FORMAT_R32_SFLOAT,
        r32g32_uint                                       = VK_FORMAT_R32G32_UINT,
        r32g32_sint                                       = VK_FORMAT_R32G32_SINT,
        r32g32_sfloat                                     = VK_FORMAT_R32G32_SFLOAT,
        r32g32b32_uint                                    = VK_FORMAT_R32G32B32_UINT,
        r32g32b32_sint                                    = VK_FORMAT_R32G32B32_SINT,
        r32g32b32_sfloat                                  = VK_FORMAT_R32G32B32_SFLOAT,
        r32g32b32a32_uint                                 = VK_FORMAT_R32G32B32A32_UINT,
        r32g32b32a32_sint                                 = VK_FORMAT_R32G32B32A32_SINT,
        r32g32b32a32_sfloat                               = VK_FORMAT_R32G32B32A32_SFLOAT,
        r64_uint                                          = VK_FORMAT_R64_UINT,
        r64_sint                                          = VK_FORMAT_R64_SINT,
        r64_sfloat                                        = VK_FORMAT_R64_SFLOAT,
        r64g64_uint                                       = VK_FORMAT_R64G64_UINT,
        r64g64_sint                                       = VK_FORMAT_R64G64_SINT,
        r64g64_sfloat                                     = VK_FORMAT_R64G64_SFLOAT,
        r64g64b64_uint                                    = VK_FORMAT_R64G64B64_UINT,
        r64g64b64_sint                                    = VK_FORMAT_R64G64B64_SINT,
        r64g64b64_sfloat                                  = VK_FORMAT_R64G64B64_SFLOAT,
        r64g64b64a64_uint                                 = VK_FORMAT_R64G64B64A64_UINT,
        r64g64b64a64_sint                                 = VK_FORMAT_R64G64B64A64_SINT,
        r64g64b64a64_sfloat                               = VK_FORMAT_R64G64B64A64_SFLOAT,
        b10g11r11_ufloat_pack32                           = VK_FORMAT_B10G11R11_UFLOAT_PACK32,
        e5b9g9r9_ufloat_pack32                            = VK_FORMAT_E5B9G9R9_UFLOAT_PACK32,
        d16_unorm                                         = VK_FORMAT_D16_UNORM,
        x8_d24_unorm_pack32                               = VK_FORMAT_X8_D24_UNORM_PACK32,
        d32_sfloat                                        = VK_FORMAT_D32_SFLOAT,
        s8_uint                                           = VK_FORMAT_S8_UINT,
        d16_unorm_s8_uint                                 = VK_FORMAT_D16_UNORM_S8_UINT,
        d24_unorm_s8_uint                                 = VK_FORMAT_D24_UNORM_S8_UINT,
        d32_sfloat_s8_uint                                = VK_FORMAT_D32_SFLOAT_S8_UINT,
        bc1_rgb_unorm_block                               = VK_FORMAT_BC1_RGB_UNORM_BLOCK,
        bc1_rgb_srgb_block                                = VK_FORMAT_BC1_RGB_SRGB_BLOCK,
        bc1_rgba_unorm_block                              = VK_FORMAT_BC1_RGBA_UNORM_BLOCK,
        bc1_rgba_srgb_block                               = VK_FORMAT_BC1_RGBA_SRGB_BLOCK,
        bc2_unorm_block                                   = VK_FORMAT_BC2_UNORM_BLOCK,
        bc2_srgb_block                                    = VK_FORMAT_BC2_SRGB_BLOCK,
        bc3_unorm_block                                   = VK_FORMAT_BC3_UNORM_BLOCK,
        bc3_srgb_block                                    = VK_FORMAT_BC3_SRGB_BLOCK,
        bc4_unorm_block                                   = VK_FORMAT_BC4_UNORM_BLOCK,
        bc4_snorm_block                                   = VK_FORMAT_BC4_SNORM_BLOCK,
        bc5_unorm_block                                   = VK_FORMAT_BC5_UNORM_BLOCK,
        bc5_snorm_block                                   = VK_FORMAT_BC5_SNORM_BLOCK,
        bc6h_ufloat_block                                 = VK_FORMAT_BC6H_UFLOAT_BLOCK,
        bc6h_sfloat_block                                 = VK_FORMAT_BC6H_SFLOAT_BLOCK,
        bc7_unorm_block                                   = VK_FORMAT_BC7_UNORM_BLOCK,
        bc7_srgb_block                                    = VK_FORMAT_BC7_SRGB_BLOCK,
        etc2_r8g8b8_unorm_block                           = VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK,
        etc2_r8g8b8_srgb_block                            = VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK,
        etc2_r8g8b8a1_unorm_block                         = VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK,
        etc2_r8g8b8a1_srgb_block                          = VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK,
        etc2_r8g8b8a8_unorm_block                         = VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK,
        etc2_r8g8b8a8_srgb_block                          = VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK,
        eac_r11_unorm_block                               = VK_FORMAT_EAC_R11_UNORM_BLOCK,
        eac_r11_snorm_block                               = VK_FORMAT_EAC_R11_SNORM_BLOCK,
        eac_r11g11_unorm_block                            = VK_FORMAT_EAC_R11G11_UNORM_BLOCK,
        eac_r11g11_snorm_block                            = VK_FORMAT_EAC_R11G11_SNORM_BLOCK,
        astc_4x4_unorm_block                              = VK_FORMAT_ASTC_4x4_UNORM_BLOCK,
        astc_4x4_srgb_block                               = VK_FORMAT_ASTC_4x4_SRGB_BLOCK,
        astc_5x4_unorm_block                              = VK_FORMAT_ASTC_5x4_UNORM_BLOCK,
        astc_5x4_srgb_block                               = VK_FORMAT_ASTC_5x4_SRGB_BLOCK,
        astc_5x5_unorm_block                              = VK_FORMAT_ASTC_5x5_UNORM_BLOCK,
        astc_5x5_srgb_block                               = VK_FORMAT_ASTC_5x5_SRGB_BLOCK,
        astc_6x5_unorm_block                              = VK_FORMAT_ASTC_6x5_UNORM_BLOCK,
        astc_6x5_srgb_block                               = VK_FORMAT_ASTC_6x5_SRGB_BLOCK,
        astc_6x6_unorm_block                              = VK_FORMAT_ASTC_6x6_UNORM_BLOCK,
        astc_6x6_srgb_block                               = VK_FORMAT_ASTC_6x6_SRGB_BLOCK,
        astc_8x5_unorm_block                              = VK_FORMAT_ASTC_8x5_UNORM_BLOCK,
        astc_8x5_srgb_block                               = VK_FORMAT_ASTC_8x5_SRGB_BLOCK,
        astc_8x6_unorm_block                              = VK_FORMAT_ASTC_8x6_UNORM_BLOCK,
        astc_8x6_srgb_block                               = VK_FORMAT_ASTC_8x6_SRGB_BLOCK,
        astc_8x8_unorm_block                              = VK_FORMAT_ASTC_8x8_UNORM_BLOCK,
        astc_8x8_srgb_block                               = VK_FORMAT_ASTC_8x8_SRGB_BLOCK,
        astc_10x5_unorm_block                             = VK_FORMAT_ASTC_10x5_UNORM_BLOCK,
        astc_10x5_srgb_block                              = VK_FORMAT_ASTC_10x5_SRGB_BLOCK,
        astc_10x6_unorm_block                             = VK_FORMAT_ASTC_10x6_UNORM_BLOCK,
        astc_10x6_srgb_block                              = VK_FORMAT_ASTC_10x6_SRGB_BLOCK,
        astc_10x8_unorm_block                             = VK_FORMAT_ASTC_10x8_UNORM_BLOCK,
        astc_10x8_srgb_block                              = VK_FORMAT_ASTC_10x8_SRGB_BLOCK,
        astc_10x10_unorm_block                            = VK_FORMAT_ASTC_10x10_UNORM_BLOCK,
        astc_10x10_srgb_block                             = VK_FORMAT_ASTC_10x10_SRGB_BLOCK,
        astc_12x10_unorm_block                            = VK_FORMAT_ASTC_12x10_UNORM_BLOCK,
        astc_12x10_srgb_block                             = VK_FORMAT_ASTC_12x10_SRGB_BLOCK,
        astc_12x12_unorm_block                            = VK_FORMAT_ASTC_12x12_UNORM_BLOCK,
        astc_12x12_srgb_block                             = VK_FORMAT_ASTC_12x12_SRGB_BLOCK,
        g8b8g8r8_422_unorm                                = VK_FORMAT_G8B8G8R8_422_UNORM,
        b8g8r8g8_422_unorm                                = VK_FORMAT_B8G8R8G8_422_UNORM,
        g8_b8_r8_3plane_420_unorm                         = VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM,
        g8_b8r8_2plane_420_unorm                          = VK_FORMAT_G8_B8R8_2PLANE_420_UNORM,
        g8_b8_r8_3plane_422_unorm                         = VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM,
        g8_b8r8_2plane_422_unorm                          = VK_FORMAT_G8_B8R8_2PLANE_422_UNORM,
        g8_b8_r8_3plane_444_unorm                         = VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM,
        r10x6_unorm_pack16                                = VK_FORMAT_R10X6_UNORM_PACK16,
        r10x6g10x6_unorm_2pack16                          = VK_FORMAT_R10X6G10X6_UNORM_2PACK16,
        r10x6g10x6b10x6a10x6_unorm_4pack16                = VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16,
        g10x6b10x6g10x6r10x6_422_unorm_4pack16            = VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16,
        b10x6g10x6r10x6g10x6_422_unorm_4pack16            = VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16,
        g10x6_b10x6_r10x6_3plane_420_unorm_3pack16        = VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16,
        g10x6_b10x6r10x6_2plane_420_unorm_3pack16         = VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16,
        g10x6_b10x6_r10x6_3plane_422_unorm_3pack16        = VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16,
        g10x6_b10x6r10x6_2plane_422_unorm_3pack16         = VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16,
        g10x6_b10x6_r10x6_3plane_444_unorm_3pack16        = VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16,
        r12x4_unorm_pack16                                = VK_FORMAT_R12X4_UNORM_PACK16,
        r12x4g12x4_unorm_2pack16                          = VK_FORMAT_R12X4G12X4_UNORM_2PACK16,
        r12x4g12x4b12x4a12x4_unorm_4pack16                = VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16,
        g12x4b12x4g12x4r12x4_422_unorm_4pack16            = VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16,
        b12x4g12x4r12x4g12x4_422_unorm_4pack16            = VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16,
        g12x4_b12x4_r12x4_3plane_420_unorm_3pack16        = VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16,
        g12x4_b12x4r12x4_2plane_420_unorm_3pack16         = VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16,
        g12x4_b12x4_r12x4_3plane_422_unorm_3pack16        = VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16,
        g12x4_b12x4r12x4_2plane_422_unorm_3pack16         = VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16,
        g12x4_b12x4_r12x4_3plane_444_unorm_3pack16        = VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16,
        g16b16g16r16_422_unorm                            = VK_FORMAT_G16B16G16R16_422_UNORM,
        b16g16r16g16_422_unorm                            = VK_FORMAT_B16G16R16G16_422_UNORM,
        g16_b16_r16_3plane_420_unorm                      = VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM,
        g16_b16r16_2plane_420_unorm                       = VK_FORMAT_G16_B16R16_2PLANE_420_UNORM,
        g16_b16_r16_3plane_422_unorm                      = VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM,
        g16_b16r16_2plane_422_unorm                       = VK_FORMAT_G16_B16R16_2PLANE_422_UNORM,
        g16_b16_r16_3plane_444_unorm                      = VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM,
        g8_b8r8_2plane_444_unorm                          = VK_FORMAT_G8_B8R8_2PLANE_444_UNORM,
        g10x6_b10x6r10x6_2plane_444_unorm_3pack16         = VK_FORMAT_G10X6_B10X6R10X6_2PLANE_444_UNORM_3PACK16,
        g12x4_b12x4r12x4_2plane_444_unorm_3pack16         = VK_FORMAT_G12X4_B12X4R12X4_2PLANE_444_UNORM_3PACK16,
        g16_b16r16_2plane_444_unorm                       = VK_FORMAT_G16_B16R16_2PLANE_444_UNORM,
        a4r4g4b4_unorm_pack16                             = VK_FORMAT_A4R4G4B4_UNORM_PACK16,
        a4b4g4r4_unorm_pack16                             = VK_FORMAT_A4B4G4R4_UNORM_PACK16,
        astc_4x4_sfloat_block                             = VK_FORMAT_ASTC_4x4_SFLOAT_BLOCK,
        astc_5x4_sfloat_block                             = VK_FORMAT_ASTC_5x4_SFLOAT_BLOCK,
        astc_5x5_sfloat_block                             = VK_FORMAT_ASTC_5x5_SFLOAT_BLOCK,
        astc_6x5_sfloat_block                             = VK_FORMAT_ASTC_6x5_SFLOAT_BLOCK,
        astc_6x6_sfloat_block                             = VK_FORMAT_ASTC_6x6_SFLOAT_BLOCK,
        astc_8x5_sfloat_block                             = VK_FORMAT_ASTC_8x5_SFLOAT_BLOCK,
        astc_8x6_sfloat_block                             = VK_FORMAT_ASTC_8x6_SFLOAT_BLOCK,
        astc_8x8_sfloat_block                             = VK_FORMAT_ASTC_8x8_SFLOAT_BLOCK,
        astc_10x5_sfloat_block                            = VK_FORMAT_ASTC_10x5_SFLOAT_BLOCK,
        astc_10x6_sfloat_block                            = VK_FORMAT_ASTC_10x6_SFLOAT_BLOCK,
        astc_10x8_sfloat_block                            = VK_FORMAT_ASTC_10x8_SFLOAT_BLOCK,
        astc_10x10_sfloat_block                           = VK_FORMAT_ASTC_10x10_SFLOAT_BLOCK,
        astc_12x10_sfloat_block                           = VK_FORMAT_ASTC_12x10_SFLOAT_BLOCK,
        astc_12x12_sfloat_block                           = VK_FORMAT_ASTC_12x12_SFLOAT_BLOCK,
        a1b5g5r5_unorm_pack16                             = VK_FORMAT_A1B5G5R5_UNORM_PACK16,
        a8_unorm                                          = VK_FORMAT_A8_UNORM,
        pvrtc1_2bpp_unorm_block_img                       = VK_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG,
        pvrtc1_4bpp_unorm_block_img                       = VK_FORMAT_PVRTC1_4BPP_UNORM_BLOCK_IMG,
        pvrtc2_2bpp_unorm_block_img                       = VK_FORMAT_PVRTC2_2BPP_UNORM_BLOCK_IMG,
        pvrtc2_4bpp_unorm_block_img                       = VK_FORMAT_PVRTC2_4BPP_UNORM_BLOCK_IMG,
        pvrtc1_2bpp_srgb_block_img                        = VK_FORMAT_PVRTC1_2BPP_SRGB_BLOCK_IMG,
        pvrtc1_4bpp_srgb_block_img                        = VK_FORMAT_PVRTC1_4BPP_SRGB_BLOCK_IMG,
        pvrtc2_2bpp_srgb_block_img                        = VK_FORMAT_PVRTC2_2BPP_SRGB_BLOCK_IMG,
        pvrtc2_4bpp_srgb_block_img                        = VK_FORMAT_PVRTC2_4BPP_SRGB_BLOCK_IMG,
        r8_bool_arm                                       = VK_FORMAT_R8_BOOL_ARM,
        r16g16_sfixed5_nv                                 = VK_FORMAT_R16G16_SFIXED5_NV,
        r10x6_uint_pack16_arm                             = VK_FORMAT_R10X6_UINT_PACK16_ARM,
        r10x6g10x6_uint_2pack16_arm                       = VK_FORMAT_R10X6G10X6_UINT_2PACK16_ARM,
        r10x6g10x6b10x6a10x6_uint_4pack16_arm             = VK_FORMAT_R10X6G10X6B10X6A10X6_UINT_4PACK16_ARM,
        r12x4_uint_pack16_arm                             = VK_FORMAT_R12X4_UINT_PACK16_ARM,
        r12x4g12x4_uint_2pack16_arm                       = VK_FORMAT_R12X4G12X4_UINT_2PACK16_ARM,
        r12x4g12x4b12x4a12x4_uint_4pack16_arm             = VK_FORMAT_R12X4G12X4B12X4A12X4_UINT_4PACK16_ARM,
        r14x2_uint_pack16_arm                             = VK_FORMAT_R14X2_UINT_PACK16_ARM,
        r14x2g14x2_uint_2pack16_arm                       = VK_FORMAT_R14X2G14X2_UINT_2PACK16_ARM,
        r14x2g14x2b14x2a14x2_uint_4pack16_arm             = VK_FORMAT_R14X2G14X2B14X2A14X2_UINT_4PACK16_ARM,
        r14x2_unorm_pack16_arm                            = VK_FORMAT_R14X2_UNORM_PACK16_ARM,
        r14x2g14x2_unorm_2pack16_arm                      = VK_FORMAT_R14X2G14X2_UNORM_2PACK16_ARM,
        r14x2g14x2b14x2a14x2_unorm_4pack16_arm            = VK_FORMAT_R14X2G14X2B14X2A14X2_UNORM_4PACK16_ARM,
        g14x2_b14x2r14x2_2plane_420_unorm_3pack16_arm     = VK_FORMAT_G14X2_B14X2R14X2_2PLANE_420_UNORM_3PACK16_ARM,
        g14x2_b14x2r14x2_2plane_422_unorm_3pack16_arm     = VK_FORMAT_G14X2_B14X2R14X2_2PLANE_422_UNORM_3PACK16_ARM,
        astc_4x4_sfloat_block_ext                         = VK_FORMAT_ASTC_4x4_SFLOAT_BLOCK_EXT,
        astc_5x4_sfloat_block_ext                         = VK_FORMAT_ASTC_5x4_SFLOAT_BLOCK_EXT,
        astc_5x5_sfloat_block_ext                         = VK_FORMAT_ASTC_5x5_SFLOAT_BLOCK_EXT,
        astc_6x5_sfloat_block_ext                         = VK_FORMAT_ASTC_6x5_SFLOAT_BLOCK_EXT,
        astc_6x6_sfloat_block_ext                         = VK_FORMAT_ASTC_6x6_SFLOAT_BLOCK_EXT,
        astc_8x5_sfloat_block_ext                         = VK_FORMAT_ASTC_8x5_SFLOAT_BLOCK_EXT,
        astc_8x6_sfloat_block_ext                         = VK_FORMAT_ASTC_8x6_SFLOAT_BLOCK_EXT,
        astc_8x8_sfloat_block_ext                         = VK_FORMAT_ASTC_8x8_SFLOAT_BLOCK_EXT,
        astc_10x5_sfloat_block_ext                        = VK_FORMAT_ASTC_10x5_SFLOAT_BLOCK_EXT,
        astc_10x6_sfloat_block_ext                        = VK_FORMAT_ASTC_10x6_SFLOAT_BLOCK_EXT,
        astc_10x8_sfloat_block_ext                        = VK_FORMAT_ASTC_10x8_SFLOAT_BLOCK_EXT,
        astc_10x10_sfloat_block_ext                       = VK_FORMAT_ASTC_10x10_SFLOAT_BLOCK_EXT,
        astc_12x10_sfloat_block_ext                       = VK_FORMAT_ASTC_12x10_SFLOAT_BLOCK_EXT,
        astc_12x12_sfloat_block_ext                       = VK_FORMAT_ASTC_12x12_SFLOAT_BLOCK_EXT,
        g8b8g8r8_422_unorm_khr                            = VK_FORMAT_G8B8G8R8_422_UNORM_KHR,
        b8g8r8g8_422_unorm_khr                            = VK_FORMAT_B8G8R8G8_422_UNORM_KHR,
        g8_b8_r8_3plane_420_unorm_khr                     = VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM_KHR,
        g8_b8r8_2plane_420_unorm_khr                      = VK_FORMAT_G8_B8R8_2PLANE_420_UNORM_KHR,
        g8_b8_r8_3plane_422_unorm_khr                     = VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM_KHR,
        g8_b8r8_2plane_422_unorm_khr                      = VK_FORMAT_G8_B8R8_2PLANE_422_UNORM_KHR,
        g8_b8_r8_3plane_444_unorm_khr                     = VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM_KHR,
        r10x6_unorm_pack16_khr                            = VK_FORMAT_R10X6_UNORM_PACK16_KHR,
        r10x6g10x6_unorm_2pack16_khr                      = VK_FORMAT_R10X6G10X6_UNORM_2PACK16_KHR,
        r10x6g10x6b10x6a10x6_unorm_4pack16_khr            = VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16_KHR,
        g10x6b10x6g10x6r10x6_422_unorm_4pack16_khr        = VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16_KHR,
        b10x6g10x6r10x6g10x6_422_unorm_4pack16_khr        = VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16_KHR,
        g10x6_b10x6_r10x6_3plane_420_unorm_3pack16_khr    = VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16_KHR,
        g10x6_b10x6r10x6_2plane_420_unorm_3pack16_khr     = VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16_KHR,
        g10x6_b10x6_r10x6_3plane_422_unorm_3pack16_khr    = VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16_KHR,
        g10x6_b10x6r10x6_2plane_422_unorm_3pack16_khr     = VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16_KHR,
        g10x6_b10x6_r10x6_3plane_444_unorm_3pack16_khr    = VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16_KHR,
        r12x4_unorm_pack16_khr                            = VK_FORMAT_R12X4_UNORM_PACK16_KHR,
        r12x4g12x4_unorm_2pack16_khr                      = VK_FORMAT_R12X4G12X4_UNORM_2PACK16_KHR,
        r12x4g12x4b12x4a12x4_unorm_4pack16_khr            = VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16_KHR,
        g12x4b12x4g12x4r12x4_422_unorm_4pack16_khr        = VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16_KHR,
        b12x4g12x4r12x4g12x4_422_unorm_4pack16_khr        = VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16_KHR,
        g12x4_b12x4_r12x4_3plane_420_unorm_3pack16_khr    = VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16_KHR,
        g12x4_b12x4r12x4_2plane_420_unorm_3pack16_khr     = VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16_KHR,
        g12x4_b12x4_r12x4_3plane_422_unorm_3pack16_khr    = VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16_KHR,
        g12x4_b12x4r12x4_2plane_422_unorm_3pack16_khr     = VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16_KHR,
        g12x4_b12x4_r12x4_3plane_444_unorm_3pack16_khr    = VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16_KHR,
        g16b16g16r16_422_unorm_khr                        = VK_FORMAT_G16B16G16R16_422_UNORM_KHR,
        b16g16r16g16_422_unorm_khr                        = VK_FORMAT_B16G16R16G16_422_UNORM_KHR,
        g16_b16_r16_3plane_420_unorm_khr                  = VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM_KHR,
        g16_b16r16_2plane_420_unorm_khr                   = VK_FORMAT_G16_B16R16_2PLANE_420_UNORM_KHR,
        g16_b16_r16_3plane_422_unorm_khr                  = VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM_KHR,
        g16_b16r16_2plane_422_unorm_khr                   = VK_FORMAT_G16_B16R16_2PLANE_422_UNORM_KHR,
        g16_b16_r16_3plane_444_unorm_khr                  = VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM_KHR,
        g8_b8r8_2plane_444_unorm_ext                      = VK_FORMAT_G8_B8R8_2PLANE_444_UNORM_EXT,
        g10x6_b10x6r10x6_2plane_444_unorm_3pack16_ext     = VK_FORMAT_G10X6_B10X6R10X6_2PLANE_444_UNORM_3PACK16_EXT,
        g12x4_b12x4r12x4_2plane_444_unorm_3pack16_ext     = VK_FORMAT_G12X4_B12X4R12X4_2PLANE_444_UNORM_3PACK16_EXT,
        g16_b16r16_2plane_444_unorm_ext                   = VK_FORMAT_G16_B16R16_2PLANE_444_UNORM_EXT,
        a4r4g4b4_unorm_pack16_ext                         = VK_FORMAT_A4R4G4B4_UNORM_PACK16_EXT,
        a4b4g4r4_unorm_pack16_ext                         = VK_FORMAT_A4B4G4R4_UNORM_PACK16_EXT,
        r16g16_s10_5_nv                                   = VK_FORMAT_R16G16_S10_5_NV,
        a1b5g5r5_unorm_pack16_khr                         = VK_FORMAT_A1B5G5R5_UNORM_PACK16_KHR,
        a8_unorm_khr                                      = VK_FORMAT_A8_UNORM_KHR,
        
        _maximum                                          = VK_FORMAT_MAX_ENUM,
    };
    enum class color_space_e : std::underlying_type_t<VkColorSpaceKHR>
    {
        srgb_nonlinear          = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR         , 
        display_p3_nonlinear    = VK_COLOR_SPACE_DISPLAY_P3_NONLINEAR_EXT   , 
        extended_srgb_linear    = VK_COLOR_SPACE_EXTENDED_SRGB_LINEAR_EXT   , 
        display_p3_linear       = VK_COLOR_SPACE_DISPLAY_P3_LINEAR_EXT      , 
        dci_p3_nonlinear        = VK_COLOR_SPACE_DCI_P3_NONLINEAR_EXT       , 
        bt709_linear            = VK_COLOR_SPACE_BT709_LINEAR_EXT           , 
        bt709_nonlinear         = VK_COLOR_SPACE_BT709_NONLINEAR_EXT        , 
        bt2020_linear           = VK_COLOR_SPACE_BT2020_LINEAR_EXT          , 
        hdr10_st2084            = VK_COLOR_SPACE_HDR10_ST2084_EXT           , 
        dolbyvision             = VK_COLOR_SPACE_DOLBYVISION_EXT            , 
        hdr10_hlg               = VK_COLOR_SPACE_HDR10_HLG_EXT              , 
        adobergb_linear         = VK_COLOR_SPACE_ADOBERGB_LINEAR_EXT        , 
        adobergb_nonlinear      = VK_COLOR_SPACE_ADOBERGB_NONLINEAR_EXT     , 
        pass_through            = VK_COLOR_SPACE_PASS_THROUGH_EXT           , 
        extended_srgb_nonlinear = VK_COLOR_SPACE_EXTENDED_SRGB_NONLINEAR_EXT, 
        display_native          = VK_COLOR_SPACE_DISPLAY_NATIVE_AMD         , 
        dci_p3_linear           = VK_COLOR_SPACE_DCI_P3_LINEAR_EXT          , 
        
        _maximum                = VK_COLOR_SPACE_MAX_ENUM_KHR               , 
    };
    enum class presentation_mode_e : std::underlying_type_t<VkPresentModeKHR>
    {
        immediate                 = VK_PRESENT_MODE_IMMEDIATE_KHR                , 
        mailbox                   = VK_PRESENT_MODE_MAILBOX_KHR                  , 
        fifo                      = VK_PRESENT_MODE_FIFO_KHR                     , 
        fifo_relaxed              = VK_PRESENT_MODE_FIFO_RELAXED_KHR             , 
        shared_demand_refresh     = VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR    , 
        shared_continuous_refresh = VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR, 
        fifo_latest_ready         = VK_PRESENT_MODE_FIFO_LATEST_READY_KHR        , 

        _maximum                  = VK_PRESENT_MODE_MAX_ENUM_KHR                 , 
    };
    enum class swap_chain_create_flags_e : std::underlying_type_t<VkSwapchainCreateFlagBitsKHR>
    {
        split_instance_bind_regions_bit = VK_SWAPCHAIN_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT_KHR, 
        protected_bit                   = VK_SWAPCHAIN_CREATE_PROTECTED_BIT_KHR                  , 
        mutable_format_bit              = VK_SWAPCHAIN_CREATE_MUTABLE_FORMAT_BIT_KHR             , 
        present_id_2_bit                = VK_SWAPCHAIN_CREATE_PRESENT_ID_2_BIT_KHR               , 
        present_wait_2_bit              = VK_SWAPCHAIN_CREATE_PRESENT_WAIT_2_BIT_KHR             , 
        deferred_memory_allocation_bit  = VK_SWAPCHAIN_CREATE_DEFERRED_MEMORY_ALLOCATION_BIT_KHR , 
        maximum                         = VK_SWAPCHAIN_CREATE_FLAG_BITS_MAX_ENUM_KHR             , 
    };
    enum class sharing_mode_e : std::underlying_type_t<VkSharingMode>
    {
        exclusive  = VK_SHARING_MODE_EXCLUSIVE , 
        concurrent = VK_SHARING_MODE_CONCURRENT, 
        maximum    = VK_SHARING_MODE_MAX_ENUM  , 
    };

    enum class device_size : vx::uint64_t;


    
    enum class enum_operation : vx::uint32_t
    {
        none         = 0u << 0u                                             , 
        
        addition     = 1u << 0u                                             , 
        subtraction  = 1u << 1u                                             , 
        
        bitwise_and  = 1u << 2u                                             , 
        bitwise_or   = 1u << 3u                                             , 
        bitwise_xor  = 1u << 4u                                             , 
        bitwise_not  = 1u << 5u                                             , 

        compare      = 1u << 6u                                             , 

        arithmetic   = addition    | subtraction                            , 
        bitwise      = bitwise_and | bitwise_or  | bitwise_xor | bitwise_not, 
        all          = arithmetic  | bitwise                                , 
    };
    
    constexpr auto operator&              (vx::enum_operation lhs    , vx::enum_operation rhs  ) -> vx::enum_operation { return std::bit_cast<vx::enum_operation>(std::to_underlying(lhs) & std::to_underlying(rhs)); }
    constexpr auto operator|              (vx::enum_operation lhs    , vx::enum_operation rhs  ) -> vx::enum_operation { return std::bit_cast<vx::enum_operation>(std::to_underlying(lhs) | std::to_underlying(rhs)); }
    constexpr auto supports_enum_operation(vx::enum_operation enabled, vx::enum_operation check) -> vx::bool_t         { return (enabled & check) == check; }

    template<typename T> struct enum_operations { static constexpr auto value = vx::enum_operation::none; };

    template<typename T> concept has_addition    = std::is_enum_v<T> && vx::supports_enum_operation(vx::enum_operations<T>::value, vx::enum_operation::addition   );
    template<typename T> concept has_subtraction = std::is_enum_v<T> && vx::supports_enum_operation(vx::enum_operations<T>::value, vx::enum_operation::subtraction);
    template<typename T> concept has_bitwise_and = std::is_enum_v<T> && vx::supports_enum_operation(vx::enum_operations<T>::value, vx::enum_operation::bitwise_and);
    template<typename T> concept has_bitwise_or  = std::is_enum_v<T> && vx::supports_enum_operation(vx::enum_operations<T>::value, vx::enum_operation::bitwise_or );
    template<typename T> concept has_bitwise_xor = std::is_enum_v<T> && vx::supports_enum_operation(vx::enum_operations<T>::value, vx::enum_operation::bitwise_xor);
    template<typename T> concept has_bitwise_not = std::is_enum_v<T> && vx::supports_enum_operation(vx::enum_operations<T>::value, vx::enum_operation::bitwise_not);
    template<typename T> concept has_compare     = std::is_enum_v<T> && vx::supports_enum_operation(vx::enum_operations<T>::value, vx::enum_operation::compare    );

    template<vx::has_addition    T> constexpr auto operator+ (T  lhs, T rhs) noexcept -> T          { return std::bit_cast<T>(std::to_underlying(lhs) +  std::to_underlying(rhs)); }
    template<vx::has_subtraction T> constexpr auto operator- (T  lhs, T rhs) noexcept -> T          { return std::bit_cast<T>(std::to_underlying(lhs) -  std::to_underlying(rhs)); }
    template<vx::has_bitwise_and T> constexpr auto operator& (T  lhs, T rhs) noexcept -> T          { return std::bit_cast<T>(std::to_underlying(lhs) &  std::to_underlying(rhs)); }
    template<vx::has_bitwise_or  T> constexpr auto operator| (T  lhs, T rhs) noexcept -> T          { return std::bit_cast<T>(std::to_underlying(lhs) |  std::to_underlying(rhs)); }
    template<vx::has_bitwise_xor T> constexpr auto operator^ (T  lhs, T rhs) noexcept -> T          { return std::bit_cast<T>(std::to_underlying(lhs) ^  std::to_underlying(rhs)); }
    template<vx::has_bitwise_not T> constexpr auto operator~ (        T rhs) noexcept -> T          { return std::bit_cast<T>(                        ~  std::to_underlying(rhs)); }
     
    template<vx::has_addition    T> constexpr auto operator+=(T& lhs, T rhs) noexcept -> T&         { return lhs = lhs + rhs; }
    template<vx::has_subtraction T> constexpr auto operator-=(T& lhs, T rhs) noexcept -> T&         { return lhs = lhs - rhs; }
    template<vx::has_bitwise_and T> constexpr auto operator&=(T& lhs, T rhs) noexcept -> T&         { return lhs = lhs & rhs; }
    template<vx::has_bitwise_or  T> constexpr auto operator|=(T& lhs, T rhs) noexcept -> T&         { return lhs = lhs | rhs; }
    template<vx::has_bitwise_xor T> constexpr auto operator^=(T& lhs, T rhs) noexcept -> T&         { return lhs = lhs ^ rhs; }
    
    template<vx::has_compare     T> constexpr auto operator< (T  lhs, T rhs) noexcept -> vx::bool_t { return                  std::to_underlying(lhs) <  std::to_underlying(rhs);  }
    template<vx::has_compare     T> constexpr auto operator> (T  lhs, T rhs) noexcept -> vx::bool_t { return                  std::to_underlying(lhs) >  std::to_underlying(rhs);  }
    template<vx::has_compare     T> constexpr auto operator<=(T  lhs, T rhs) noexcept -> vx::bool_t { return                  std::to_underlying(lhs) <= std::to_underlying(rhs);  }
    template<vx::has_compare     T> constexpr auto operator>=(T  lhs, T rhs) noexcept -> vx::bool_t { return                  std::to_underlying(lhs) >= std::to_underlying(rhs);  }



    template<> struct vx::enum_operations<vx::api_version_e                 > { static constexpr auto value = vx::enum_operation::compare; };
    template<> struct vx::enum_operations<vx::debug_utils_message_severity_e> { static constexpr auto value = vx::enum_operation::bitwise; };
    template<> struct vx::enum_operations<vx::debug_utils_message_type_e    > { static constexpr auto value = vx::enum_operation::bitwise; };
    template<> struct vx::enum_operations<vx::memory_property_flags_e       > { static constexpr auto value = vx::enum_operation::bitwise; };
    template<> struct vx::enum_operations<vx::memory_heap_flags_e           > { static constexpr auto value = vx::enum_operation::bitwise; };
    template<> struct vx::enum_operations<vx::queue_flags_e                 > { static constexpr auto value = vx::enum_operation::bitwise; };
    template<> struct vx::enum_operations<vx::device_size                   > { static constexpr auto value = vx::enum_operation::compare; };
}
