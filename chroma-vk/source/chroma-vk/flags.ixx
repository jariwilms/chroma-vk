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
        application_info                  = VkStructureType::VK_STRUCTURE_TYPE_APPLICATION_INFO                     , 
        debug_messenger                   = VkStructureType::VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT, 
        instance_create_info              = VkStructureType::VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO                 , 
        physical_device_properties        = VkStructureType::VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2         , 
        physical_device_features          = VkStructureType::VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2           , 
        physical_device_memory_properties = VkStructureType::VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PROPERTIES_2  , 
        queue_family_properties           = VkStructureType::VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2            , 
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



    template<> struct vx::enum_operations<vx::api_version_e                 > { static constexpr vx::enum_operation value = vx::enum_operation::compare; };
    template<> struct vx::enum_operations<vx::debug_utils_message_severity_e> { static constexpr vx::enum_operation value = vx::enum_operation::bitwise_and | vx::enum_operation::bitwise_or; };
    template<> struct vx::enum_operations<vx::debug_utils_message_type_e    > { static constexpr vx::enum_operation value = vx::enum_operation::bitwise; };
    template<> struct vx::enum_operations<vx::memory_property_flags_e       > { static constexpr vx::enum_operation value = vx::enum_operation::bitwise; };
    template<> struct vx::enum_operations<vx::memory_heap_flags_e           > { static constexpr vx::enum_operation value = vx::enum_operation::bitwise; };
    template<> struct vx::enum_operations<vx::queue_flags_e                 > { static constexpr vx::enum_operation value = vx::enum_operation::bitwise; };
    template<> struct vx::enum_operations<vx::device_size                   > { static constexpr vx::enum_operation value = vx::enum_operation::compare; };
}
