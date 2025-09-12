export module vx.functions;

import std;
import <vulkan/vulkan.h>;
import vx.types;
import vx.flags;
import vx.structures;

export namespace vx
{
    template<typename Fn, std::convertible_to<vx::instance_t> T>
    auto function_address_of(T instance, vx::string_view identifier)
    {
        return std::bit_cast<Fn>(::vkGetInstanceProcAddr(instance, identifier));
    }

    void handle_result(const vx::result_e result)
    {
        //The results from "success" to "incomplete" (and "suboptimal") are "success codes", even though they throw
        //All others are error codes

        switch (result)
        {
            using enum vx::result_e;

            case success              : break;
            case not_ready            : throw std::runtime_error{ "A fence or query has not yet completed!"                                                                                          };
            case timeout              : throw std::runtime_error{ "A wait operation has not completed in the specified time!"                                                                        };
            case event_set            : throw std::runtime_error{ "An event is signaled!"                                                                                                            };
            case event_reset          : throw std::runtime_error{ "An event is unsignaled!"                                                                                                          };
            case incomplete           : throw std::runtime_error{ "A return array was too small for the result!"                                                                                     };
            case out_of_host_memory   : throw std::runtime_error{ "A host memory allocation has failed!"                                                                                             };
            case out_of_device_memory : throw std::runtime_error{ "A device memory allocation has failed!"                                                                                           };
            case initialization_failed: throw std::runtime_error{ "Initialization of an object could not be completed for implementation-specific reasons!"                                          };
            case device_lost          : throw std::runtime_error{ "The logical or physical device has been lost!"                                                                                    };
            case memory_map_failed    : throw std::runtime_error{ "Mapping of a memory object has failed!"                                                                                           };
            case layer_not_present    : throw std::runtime_error{ "A requested layer is not present or could not be loaded!"                                                                         };
            case extension_not_present: throw std::runtime_error{ "A requested extension is not supported!"                                                                                          };
            case feature_not_present  : throw std::runtime_error{ "A requested feature is not supported!"                                                                                            };
            case incompatible_driver  : throw std::runtime_error{ "The requested version of Vulkan is not supported by the driver or is otherwise incompatible for implementation-specific reasons!" }; 
            case too_many_objects     : throw std::runtime_error{ "Too many objects of the type have already been created!"                                                                          };
            case format_not_supported : throw std::runtime_error{ "A requested format is not supported on this device!"                                                                              };
            case surface_lost         : throw std::runtime_error{ "A surface is no longer available!"                                                                                                };
            case suboptimal           : throw std::runtime_error{ "A swapchain no longer matches the surface properties exactly!"                                                                    };
            case out_of_date          : throw std::runtime_error{ "A surface has changed in such a way that it is no longer compatible with the swapchain!"                                          };
            case incompatible_display : throw std::runtime_error{ "The display used by a swapchain does not use the same presentable image layout!"                                                  };
            case native_window_in_use : throw std::runtime_error{ "The requested window is already in use by Vulkan or another API in a manner which prevents it from being used again!"             };
            case validation_failed    : throw std::runtime_error{ "A command failed because invalid usage was detected by the implementation or a validation layer!"                                 };

            default                   : throw std::runtime_error{ "Invalid result!"                                                                                                                  };
        }
    }
    void handle_result(const vx::result_t result)
    {
        vx::handle_result(std::bit_cast<vx::result_e>(result));
    }

    template<auto Fn, typename T, typename... Args>
    auto enumerate   (Args&&... args) -> std::vector<T>
    {
        if constexpr (std::is_same_v<std::invoke_result_t<decltype(Fn), Args..., vx::uint32_t*, T*>, vx::result_t>)
        {
            auto count = vx::uint32_t{};
            vx::handle_result(Fn(args..., &count, nullptr    ));
            
            auto data  = std::vector<T>(count);
            vx::handle_result(Fn(args..., &count, data.data()));
            
            return data;
        }
        else
        {
            auto count = vx::uint32_t{};
            Fn(args..., &count, nullptr    );
        
            auto data  = std::vector<T>(count);
            Fn(args..., &count, data.data());
            
            return data;
        }
    }
    template<auto Fn, typename T, typename... Args> 
    auto enumerate_as(Args&&... args) -> std::vector<T>
    {
        using native_t = typename T::native_t;
        
        const auto native_data = vx::enumerate<Fn, native_t>(std::forward<Args>(args)...);
              auto result      = std::vector<T>{};
        
        std::memcpy(&result, &native_data, sizeof(result));

        return result;
    }



    auto create_instance(const vx::instance_create_info& instance_create_info) -> vx::instance_t
    {
        auto vk_instance = vx::instance_t{};
        vx::handle_result(::vkCreateInstance(instance_create_info, nullptr, &vk_instance));

        return vk_instance;
    }
    template<std::convertible_to<vx::instance_t> T>
    auto create_debug_messenger(T instance, const vx::debug_messenger_create_info& debug_messenger_create_info) -> vx::debug_messenger_t
    {
              auto vk_debug_messenger     = vx::debug_messenger_t{};
        const auto create_debug_messenger = vx::function_address_of<vx::create_debug_messenger_f>(instance, "vkCreateDebugUtilsMessengerEXT"); //TODO: constant/loader?
        create_debug_messenger(instance, debug_messenger_create_info, nullptr, &vk_debug_messenger);

        return vk_debug_messenger;
    }
    template<std::convertible_to<vx::logical_device_t> T>
    auto create_command_pool(T logical_device, const vx::command_pool_create_info& command_pool_create_info) -> vx::command_pool_t
    {
        auto vk_command_pool = vx::command_pool_t{};
        vx::handle_result(::vkCreateCommandPool(logical_device, command_pool_create_info, nullptr, &vk_command_pool));

        return vk_command_pool;
    }

    auto enumerate_instance_layer_properties() -> std::vector<vx::layer_properties>
    {
        return vx::enumerate_as<vkEnumerateInstanceLayerProperties, vx::layer_properties>();
    }
    auto enumerate_instance_extension_properties(vx::string_view layer_name = {}) -> std::vector<vx::extension_properties>
    {
        return vx::enumerate_as<vkEnumerateInstanceExtensionProperties, vx::extension_properties>(layer_name);
    }

    template<std::convertible_to<vx::instance_t> T>
    auto enumerate_physical_devices(T instance) -> std::vector<vx::physical_device_t>
    {
        return vx::enumerate<::vkEnumeratePhysicalDevices, vx::physical_device_t>(instance);
    }

    template<std::convertible_to<vx::physical_device_t> T, std::convertible_to<vx::surface_t> U>
    auto get_physical_device_surface_support(T physical_device, U surface, vx::uint32_t index) -> vx::bool_t
    {
        auto supported = vx::bool32_t{};
        vx::handle_result(::vkGetPhysicalDeviceSurfaceSupportKHR(physical_device, index, surface, &supported));

        return supported != vx::bool32_t{};
    }
    template<std::convertible_to<vx::physical_device_t> T>
    auto get_physical_device_features               (T& physical_device) -> vx::physical_device_features
    {
        auto physical_device_features = vx::physical_device_features{};
        ::vkGetPhysicalDeviceFeatures2(physical_device, physical_device_features);

        return physical_device_features;
    }
    template<std::convertible_to<vx::physical_device_t> T>
    auto get_physical_device_properties             (T& physical_device) -> vx::physical_device_properties
    {
        auto physical_device_properties = vx::physical_device_properties{};
        ::vkGetPhysicalDeviceProperties2(physical_device, physical_device_properties);

        return physical_device_properties;
    }
    template<std::convertible_to<vx::physical_device_t> T>
    auto get_physical_device_memory_properties      (T& physical_device) -> vx::physical_device_memory_properties
    {
        auto physical_device_memory_properties = vx::physical_device_memory_properties{};
        ::vkGetPhysicalDeviceMemoryProperties2(physical_device, physical_device_memory_properties);

        return physical_device_memory_properties;
    }
    template<std::convertible_to<vx::physical_device_t> T>
    auto get_physical_device_queue_family_properties(T physical_device) -> std::vector<vx::queue_family_properties>
    {
        return vx::enumerate_as<::vkGetPhysicalDeviceQueueFamilyProperties2, vx::queue_family_properties>(physical_device);
    }
    template<std::convertible_to<vx::physical_device_t> T>
    auto enumerate_physical_device_extension_properties      (T physical_device, vx::string_view layer_name = {}) -> std::vector<vx::extension_properties>
    {
        return vx::enumerate_as<::vkEnumerateDeviceExtensionProperties, vx::extension_properties>(physical_device, layer_name);
    }

    template<std::convertible_to<vx::physical_device_t> T>
    auto create_logical_device      (T physical_device, const vx::logical_device_create_info& logical_device_create_info) -> vx::logical_device_t
    {
        auto vk_logical_device = vx::logical_device_t{};
        vx::handle_result(::vkCreateDevice(physical_device, logical_device_create_info, nullptr, &vk_logical_device));
        
        return vk_logical_device;
    }
    template<std::convertible_to<vx::logical_device_t> T>
    auto create_logical_device_queue(T logical_device, vx::uint32_t queue_index) -> vx::queue_t
    {
        auto vk_queue = vx::queue_t{};
        ::vkGetDeviceQueue(logical_device, queue_index, vx::uint32_t{ 0u }, &vk_queue);

        return vk_queue;
    }
}
