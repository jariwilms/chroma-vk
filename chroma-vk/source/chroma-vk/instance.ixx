export module vx.instance;

import std;
import <vulkan/vulkan.h>;
import vx;

export namespace vx
{
    struct application_info
    {
        using native_t = VkApplicationInfo;

        operator vx::pointer_t<const VkApplicationInfo>() const
        {
            return std::bit_cast<const VkApplicationInfo*>(this);
        }

        vx::structure_type_e structure_type = vx::structure_type_e::application_info;
        vx::next_t           next           = {};
        vx::string_view      name           = {};
        vx::uint32_t         version        = {};
        vx::string_view      engine_name    = {};
        vx::uint32_t         engine_version = {};
        vx::api_version_e    api_version    = {};
    };
    struct debug_utils_messenger_create_info
    {
        using native_t = VkDebugUtilsMessengerCreateInfoEXT;

        operator vx::pointer_t<const VkDebugUtilsMessengerCreateInfoEXT>() const
        {
            return std::bit_cast<const VkDebugUtilsMessengerCreateInfoEXT*>(this);
        }

        vx::structure_type_e                     structure_type = vx::structure_type_e::debug_messenger;
        vx::next_t                               next           = {};
        vx::debug_utils_messenger_create_flags_e flags          = {};
        vx::debug_utils_message_severity_e       severity       = {};
        vx::debug_utils_message_type_e           type           = {};
        vx::debug_utils_messenger_callback_t     callback       = {};
        vx::next_t                               user_data      = {};
    };
    struct instance_create_info
    {
        using native_t = VkInstanceCreateInfo;

        operator vx::pointer_t<const VkInstanceCreateInfo>() const
        {
            return std::bit_cast<const VkInstanceCreateInfo*>(this);
        }

        vx::structure_type_e                      structure_type   = vx::structure_type_e::instance_create_info;
        vx::next_t                                next             = {};
        vx::instance_create_flags_e               flags            = {};
        vx::pointer_t<const vx::application_info> application_info = {};
        vx::span<const vx::string_view>           layer_names      = {};
        vx::span<const vx::string_view>           extension_names  = {};
    };

    class instance
    {
    public:
        using native_t = VkInstance;

        instance(vx::string_view application_name, vx::string_view engine_name)
        {
            const auto application_info               = vx::application_info{
                .name        = application_name       , .version        = vx::uint32_t{ 0u }, 
                .engine_name = engine_name            , .engine_version = vx::uint32_t{ 0u }, 
                .api_version = vx::api_version_e::_1_4, 
            };
            
            const auto required_layers                = vx::get_required_layers_or_smth            ();
            const auto required_extensions            = vx::get_required_extensions_or_smth        ();
            const auto instance_layer_properties      = vx::enumerate_instance_layer_properties    ();
            const auto instance_extension_properties  = vx::enumerate_instance_extension_properties();
            
            if (!std::ranges::all_of(required_layers, [&](const vx::string_view name) -> vx::bool_t
                {
                    return std::ranges::any_of(instance_layer_properties, [&](const vx::layer_properties& layer_properties) -> vx::bool_t
                        {
                            return std::strcmp(layer_properties.name.data(), name) != vx::int32_t{ 0u };
                        });
                })) throw std::runtime_error{ "Missing one or more required layers!" };
                
            const auto debug_messenger_create_info    = vx::debug_utils_messenger_create_info{
                .flags    = vx::debug_utils_messenger_create_flags_e{},
                .severity = vx::debug_utils_message_severity_e{
                    vx::debug_utils_message_severity_e::verbose      | 
                    vx::debug_utils_message_severity_e::warning      | 
                    vx::debug_utils_message_severity_e::error        }, 
                .type     = vx::debug_utils_message_type_e{
                    vx::debug_utils_message_type_e    ::general      | 
                    vx::debug_utils_message_type_e    ::validation   | 
                    vx::debug_utils_message_type_e    ::performance  }, 
                .callback = &vx::debug_callback                       , 
            };
            const auto instance_create_info           = vx::instance_create_info{
                .next             =  debug_messenger_create_info                    , 
                .application_info = &application_info                               , 
                .layer_names      = vx::span<const vx::string_view>{ std::from_range, required_layers     }, 
                .extension_names  = vx::span<const vx::string_view>{ std::from_range, required_extensions }, 
            };
            
            ::vkCreateInstance(instance_create_info, nullptr, &instance_);
            const auto vkCreateDebugUtilsMessengerEXT = std::bit_cast<PFN_vkCreateDebugUtilsMessengerEXT>(::vkGetInstanceProcAddr(instance_, "vkCreateDebugUtilsMessengerEXT"));
            vkCreateDebugUtilsMessengerEXT(instance_, debug_messenger_create_info, nullptr, &debug_messenger_);
        }

        operator       VkInstance              &() 
        {
            return instance_;
        }
        operator const VkInstance              &() const
        {
            return instance_;
        }
        operator const VkDebugUtilsMessengerEXT&() const
        {
            return debug_messenger_;
        }

    private:
        VkInstance               instance_;
        VkDebugUtilsMessengerEXT debug_messenger_;
    };
}
