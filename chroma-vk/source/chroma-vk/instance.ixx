export module vx.instance;

import std;
import <vulkan/vulkan.h>;
import vx;

export namespace vx
{
    using create_debug_messenger_f = PFN_vkCreateDebugUtilsMessengerEXT;

    template<typename Fn, std::convertible_to<vx::instance_t> T>
    auto get_function_address(T instance, vx::string_view identifier)
    {
        return std::bit_cast<Fn>(::vkGetInstanceProcAddr(instance, identifier));
    }
    auto create_instance(const vx::instance_create_info& instance_create_info) -> vx::instance_t
    {
              auto vk_instance = vx::instance_t{};
        const auto result      = std::bit_cast<vx::result_e>(::vkCreateInstance(instance_create_info, nullptr, &vk_instance));
        if (result != vx::result_e::success) throw std::runtime_error{ "" };

        return vk_instance;
    }
    template<std::convertible_to<vx::instance_t> T>
    auto create_debug_messenger(T instance, const vx::debug_messenger_create_info& debug_messenger_create_info) -> vx::debug_messenger_t
    {
              auto debug_messenger        = vx::debug_messenger_t{};
        const auto create_debug_messenger = vx::get_function_address<vx::create_debug_messenger_f>(instance, "vkCreateDebugUtilsMessengerEXT");
        create_debug_messenger(instance, debug_messenger_create_info, nullptr, &debug_messenger);

        return debug_messenger;
    }

    class instance
    {
    public:
        using native_t = vx::instance_t;

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
                
            const auto debug_messenger_create_info    = vx::debug_messenger_create_info{
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
                .next             = debug_messenger_create_info    , 
                .application_info = application_info               , 
                .layer_names      = vx::span{ required_layers     }, 
                .extension_names  = vx::span{ required_extensions }, 
            };
            
            instance_                                 = vx::create_instance       (           instance_create_info       );
            debug_messenger_                          = vx::create_debug_messenger(instance_, debug_messenger_create_info);
        }

        operator       vx::instance_t       &() 
        {
            return instance_;
        }
        operator const vx::instance_t       &() const
        {
            return instance_;
        }
        operator       vx::debug_messenger_t&()
        {
            return debug_messenger_;
        }
        operator const vx::debug_messenger_t&() const
        {
            return debug_messenger_;
        }

    private:
        vx::instance_t        instance_;
        vx::debug_messenger_t debug_messenger_;
    };
}
