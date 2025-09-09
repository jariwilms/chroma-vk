export module vx.logical_device;

import std;
import <vulkan/vulkan.h>;
import vx;
import vx.instance;
import vx.surface;
import vx.physical_device;

export namespace vx
{
    namespace extension
    {
        constexpr auto swap_chain             = VK_KHR_SWAPCHAIN_EXTENSION_NAME;
        constexpr auto spirv_1_4              = VK_KHR_SPIRV_1_4_EXTENSION_NAME;
        constexpr auto synchronization        = VK_KHR_SYNCHRONIZATION_2_EXTENSION_NAME;
        constexpr auto renderpass             = VK_KHR_CREATE_RENDERPASS_2_EXTENSION_NAME;
        constexpr auto shader_draw_parameters = VK_KHR_SHADER_DRAW_PARAMETERS_EXTENSION_NAME;
    };






    template<std::convertible_to<VkPhysicalDevice> T, std::convertible_to<VkSurfaceKHR> U>
    auto get_physical_device_surface_support(T physical_device, U surface, vx::uint32_t index) -> vx::bool_t
    {
        auto supported = vx::bool32_t{};
        const auto result = static_cast<vx::result_e>(::vkGetPhysicalDeviceSurfaceSupportKHR(physical_device, index, surface, &supported));

        if (result != vx::result_e::success)
        {
            switch (result)
            {
                using enum vx::result_e;

                case out_of_device_memory: throw std::runtime_error{ "Out of device memory!" };
                case out_of_host_memory  : throw std::runtime_error{ "Out of host memory!"   };
                case surface_lost        : throw std::runtime_error{ "Surface lost!"         };
                case validation_failed   : throw std::runtime_error{ "Validation failed!"    };
                
                default                  : throw std::runtime_error{ "Unknown error!"        };
            }
        }

        return supported != vx::bool32_t{};
    }





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
    
    template<> struct vx::chain_link<vx::physical_device_features           , vx::physical_device_vulkan_1_3_features            > : std::true_type {};
    template<> struct vx::chain_link<vx::physical_device_vulkan_1_3_features, vx::physical_device_extended_dynamic_state_features> : std::true_type {};

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



    struct logical_device_create_info
    {
        using native_t = VkDeviceCreateInfo;

        operator       VkDeviceCreateInfo*()
        {
            return std::bit_cast<VkDeviceCreateInfo*>(this);
        }
        operator const VkDeviceCreateInfo*() const
        {
            return std::bit_cast<const VkDeviceCreateInfo*>(this);
        }

        vx::structure_type_e                                 structure_type          = vx::structure_type_e::logical_device_create_info;
        vx::next_t                                           next                    = {};
        vx::logical_device_create_flags_e                    flags                   = {};
        vx::aligned_span<const vx::device_queue_create_info> queue_create_info       = {};
        vx::padded_span <const vx::string_view>              enabled_layer_names     = {}; //deprecated
        vx::padded_span <const vx::string_view>              enabled_extension_names = {};
        vx::pointer_t   <const vx::physical_device_features> enabled_features        = {};
    };

    template<std::convertible_to<VkDevice&> T>
    void create_logical_device      (vx::physical_device physical_device, T& logical_device, const vx::logical_device_create_info& logical_device_create_info)
    {
              auto& vk_logical_device = static_cast<VkDevice&>(logical_device);
        const auto  result            = std::bit_cast<vx::result_e>(::vkCreateDevice(physical_device, logical_device_create_info, nullptr, &vk_logical_device));
        if (result != vx::result_e::success) throw std::runtime_error{ "" };
    }
    template<std::convertible_to<VkQueue&> T>
    void create_logical_device_queue(T& logical_device, vx::uint32_t queue_index)
    {
        auto vk_queue    = static_cast<VkQueue&>(logical_device);
        ::vkGetDeviceQueue(logical_device, queue_index, vx::uint32_t{ 0u }, &vk_queue);
    }

    class queue
    {
    public:
        using native_t = VkQueue;

        queue() = default;

        operator       vx::queue_t&()
        {
            return queue_;
        }
        operator const vx::queue_t&() const
        {
            return queue_;
        }

    private:
        vx::queue_t queue_;
    };
    class logical_device
    {
    public:
        using native_t = VkDevice;

        logical_device() = default;
        logical_device(vx::physical_device physical_device, vx::surface surface)
        {
            queue_index_ = std::numeric_limits<std::uint32_t>::max();

            for (const auto [index, queue_family_properties] : std::views::enumerate(vx::get_physical_device_queue_family_properties(physical_device)))
            {
                if ((queue_family_properties.queue_flags & vx::queue_flags_e::graphics) != vx::queue_flags_e{}          ) break;
                if (!vx::get_physical_device_surface_support(physical_device, surface, static_cast<vx::uint32_t>(index))) break;

                queue_index_ = static_cast<vx::uint32_t>(index);
            }

            if (queue_index_ == std::numeric_limits<std::uint32_t>::max()) throw std::runtime_error{ "No queue present that supports both graphics and presentation!" };

                  auto queue_priority                          = std::float_t{};
            const auto required_logical_device_extensions      = std::vector{
                extension::swap_chain, 
                extension::spirv_1_4, 
                extension::synchronization, 
                extension::renderpass, 
                extension::shader_draw_parameters, 
            };
            const auto logical_device_queue_create_info        = vx::device_queue_create_info{ 
                .queue_family_index = queue_index_      , 
                .queue_count        = vx::uint32_t{ 1u }, 
                .queue_priorities   = &queue_priority   , 
            };

            const auto structure_chain                         = vx::structure_chain<vx::physical_device_features, vx::physical_device_vulkan_1_3_features, vx::physical_device_extended_dynamic_state_features>{
                vx::physical_device_features                       {                                                                     }, 
                vx::physical_device_vulkan_1_3_features            { .synchronization        = vx::true_, .dynamic_rendering = vx::true_ }, 
                vx::physical_device_extended_dynamic_state_features{ .extended_dynamic_state = vx::true_,                                }, 
            };
            const auto logical_device_create_info              = vx::logical_device_create_info{
                .queue_create_info       = vx::span                       { &logical_device_queue_create_info, 1u                                 }, 
                .enabled_extension_names = vx::span<const vx::string_view>{ std::from_range                  , required_logical_device_extensions }, 
                .enabled_features        = &structure_chain.get<vx::physical_device_features>(), 
            };

            vx::create_logical_device      (physical_device, *this, logical_device_create_info);
            vx::create_logical_device_queue(*this, queue_index_);
        }

        operator       vx::logical_device_t&()
        {
            return logical_device_;
        }
        operator const vx::logical_device_t&() const
        {
            return logical_device_;
        }
        operator       vx::queue_t         &()
        {
            return queue_;
        }
        operator const vx::queue_t         &() const
        {
            return queue_;
        }

    private:
        vx::logical_device_t logical_device_;
        vx::queue_t          queue_;
        vx::uint32_t         queue_index_;
    };
}
