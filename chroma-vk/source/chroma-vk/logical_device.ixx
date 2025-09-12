export module vx.logical_device;

import std;
import vx;
import vx.instance;
import vx.surface;
import vx.physical_device;

export namespace vx
{
    class queue
    {
    public:
        queue(vx::queue_t queue, vx::uint32_t index)
            : queue_{ queue }, index_{ index } {}

        operator       vx::queue_t&()
        {
            return queue_;
        }
        operator const vx::queue_t&() const
        {
            return queue_;
        }

        auto index() const
        {
            return index_;
        }

    private:
        vx::queue_t  queue_;
        vx::uint32_t index_;
    };
    class logical_device
    {
    public:
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

            const auto queue_priority                          = std::float_t{};
            const auto required_logical_device_extensions      = std::vector{
                vx::extension::swap_chain            , 
                vx::extension::spirv_1_4             , 
                vx::extension::synchronization       , 
                vx::extension::renderpass            , 
                vx::extension::shader_draw_parameters, 
            };
            const auto logical_device_queue_create_info        = vx::device_queue_create_info{ 
                .queue_family_index = queue_index_                                   , 
                .queue_priorities   = vx::span{ &queue_priority, vx::uint32_t{ 1u } }, 
            };

            const auto structure_chain                         = vx::structure_chain<vx::physical_device_features, vx::physical_device_vulkan_1_3_features, vx::physical_device_extended_dynamic_state_features>{
                vx::physical_device_features                       {                                                                     }, 
                vx::physical_device_vulkan_1_3_features            { .synchronization        = vx::true_, .dynamic_rendering = vx::true_ }, 
                vx::physical_device_extended_dynamic_state_features{ .extended_dynamic_state = vx::true_,                                }, 
            };
            const auto logical_device_create_info              = vx::logical_device_create_info{
                .queue_create_info       = vx::span{ &logical_device_queue_create_info , 1u }, 
                .enabled_extension_names = vx::span{ required_logical_device_extensions,    }, 
                .enabled_features        = &structure_chain.get<vx::physical_device_features>(), 
            };

            logical_device_ = vx::create_logical_device      (physical_device, logical_device_create_info);
            queue_          = vx::create_logical_device_queue(logical_device_, queue_index_              );
        }

        auto queue_index() const -> vx::uint32_t
        {
            return queue_index_;
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
