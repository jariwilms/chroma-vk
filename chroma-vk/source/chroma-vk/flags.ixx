export module vx.flags;

import std;
import <vulkan/vulkan.h>;
import vx.types;

export namespace vx
{
    enum class result_e : std::underlying_type_t<VkResult>
    {
        success               = VkResult::VK_SUCCESS, 
        not_ready             = VkResult::VK_NOT_READY, 
        timeout               = VkResult::VK_TIMEOUT, 
        event_set             = VkResult::VK_EVENT_SET,
        event_reset           = VkResult::VK_EVENT_RESET,
        incomplete            = VkResult::VK_INCOMPLETE,
        out_of_host_memory    = VkResult::VK_ERROR_OUT_OF_HOST_MEMORY,
        out_of_device_memory  = VkResult::VK_ERROR_OUT_OF_DEVICE_MEMORY,
        initialization_failed = VkResult::VK_ERROR_INITIALIZATION_FAILED,
        device_lost           = VkResult::VK_ERROR_DEVICE_LOST,
        memory_map_failed     = VkResult::VK_ERROR_MEMORY_MAP_FAILED,
        layer_not_present     = VkResult::VK_ERROR_LAYER_NOT_PRESENT,
        extension_not_present = VkResult::VK_ERROR_EXTENSION_NOT_PRESENT, 
        feature_not_present   = VkResult::VK_ERROR_FEATURE_NOT_PRESENT, 
        incompatible_driver   = VkResult::VK_ERROR_INCOMPATIBLE_DRIVER, 
        too_many_objects      = VkResult::VK_ERROR_TOO_MANY_OBJECTS, 
        format_not_supported  = VkResult::VK_ERROR_FORMAT_NOT_SUPPORTED, 
        surface_lost          = VkResult::VK_ERROR_SURFACE_LOST_KHR, 
        suboptimal            = VkResult::VK_SUBOPTIMAL_KHR, 
        out_of_date           = VkResult::VK_ERROR_OUT_OF_DATE_KHR, 
        incompatible_display  = VkResult::VK_ERROR_INCOMPATIBLE_DISPLAY_KHR, 
        native_window_in_use  = VkResult::VK_ERROR_NATIVE_WINDOW_IN_USE_KHR, 
        validation_failed     = VkResult::VK_ERROR_VALIDATION_FAILED_EXT, 
        maximum_enum          = VkResult::VK_RESULT_MAX_ENUM, 
    };

    enum class structure_type_e : std::underlying_type_t<VkStructureType>
    {
        application_info           = VkStructureType::VK_STRUCTURE_TYPE_APPLICATION_INFO                     , 
        debug_messenger            = VkStructureType::VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT, 
        instance_create_info       = VkStructureType::VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO                 , 
        physical_device_properties = VkStructureType::VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2         , 
        physical_device_features   = VkStructureType::VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2           ,
    };
    enum class debug_utils_messenger_create_flags_e : VkDebugUtilsMessageTypeFlagsEXT
    {

    };
    enum class debug_utils_message_severity_e : VkDebugUtilsMessageSeverityFlagsEXT
    {
        verbose = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT       , 
        info    = VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT          , 
        warning = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT       , 
        error   = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT         , 
        maximum = VK_DEBUG_UTILS_MESSAGE_SEVERITY_FLAG_BITS_MAX_ENUM_EXT, 
    };
    enum class debug_utils_message_type_e : VkDebugUtilsMessageTypeFlagsEXT
    {
        general         = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT               , 
        validation      = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT            , 
        performance     = VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT           , 
        address_binding = VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT, 
        maximum         = VK_DEBUG_UTILS_MESSAGE_TYPE_FLAG_BITS_MAX_ENUM_EXT        , 
    };
    enum class instance_create_flags_e : VkInstanceCreateFlags
    {

    };

    using debug_utils_messenger_callback = PFN_vkDebugUtilsMessengerCallbackEXT;



    template<typename T> struct flag_trait_all      { static constexpr auto enable = vx::bool_t{ vx::false_ }; };
    template<typename T> struct flag_trait_add      { static constexpr auto enable = vx::bool_t{ vx::false_ }; };
    template<typename T> struct flag_trait_subtract { static constexpr auto enable = vx::bool_t{ vx::false_ }; };
    template<typename T> struct flag_trait_and      { static constexpr auto enable = vx::bool_t{ vx::false_ }; };
    template<typename T> struct flag_trait_or       { static constexpr auto enable = vx::bool_t{ vx::false_ }; };

    template<typename T> concept flag_trait_add_c      = vx::flag_trait_add     <T>::enable || vx::flag_trait_all<T>::enable;
    template<typename T> concept flag_trait_subtract_c = vx::flag_trait_subtract<T>::enable || vx::flag_trait_all<T>::enable;
    template<typename T> concept flag_trait_and_c      = vx::flag_trait_and     <T>::enable || vx::flag_trait_all<T>::enable;
    template<typename T> concept flag_trait_or_c       = vx::flag_trait_or      <T>::enable || vx::flag_trait_all<T>::enable;

    template<vx::flag_trait_add_c      T> constexpr auto operator+ (T first, T second) -> T { return static_cast<T>(std::to_underlying(first) + std::to_underlying(second)); }
    template<vx::flag_trait_subtract_c T> constexpr auto operator- (T first, T second) -> T { return static_cast<T>(std::to_underlying(first) - std::to_underlying(second)); }
    template<vx::flag_trait_and_c      T> constexpr auto operator& (T first, T second) -> T { return static_cast<T>(std::to_underlying(first) & std::to_underlying(second)); }
    template<vx::flag_trait_or_c       T> constexpr auto operator| (T first, T second) -> T { return static_cast<T>(std::to_underlying(first) | std::to_underlying(second)); }

    template<> struct flag_trait_or<vx::debug_utils_message_severity_e> { static constexpr auto enable = vx::bool_t{ vx::true_ }; };
    template<> struct flag_trait_or<vx::debug_utils_message_type_e    > { static constexpr auto enable = vx::bool_t{ vx::true_ }; };

}
