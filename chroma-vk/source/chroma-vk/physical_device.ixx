export module vx.physical_device;

import std;
import vx;
import vx.instance;

export namespace vx
{
    class physical_device
    {
    public:
        physical_device(vx::physical_device_t physical_device)
            : physical_device_{ physical_device } {}

        operator       vx::physical_device_t&()
        {
            return physical_device_;
        }
        operator const vx::physical_device_t&() const
        {
            return physical_device_;
        }

    private:
        vx::physical_device_t physical_device_;
    };

    auto select_default_physical_device(vx::instance instance, std::vector<vx::string_view> required_extensions) -> vx::physical_device
    {
              auto physical_devices = vx::enumerate_physical_devices(instance);
        const auto candidates       = std::invoke([&]() -> std::map<vx::uint32_t, vx::physical_device_t>
            {
                auto result = std::map<vx::uint32_t, vx::physical_device_t>{};
                std::ranges::for_each(physical_devices, [&](vx::physical_device_t& physical_device)
                    {
                        const auto features                 = vx::get_physical_device_features                  (physical_device);
                        const auto properties               = vx::get_physical_device_properties                (physical_device);
                        const auto memory_properties        = vx::get_physical_device_memory_properties         (physical_device);
                        const auto queue_family_properties  = vx::get_physical_device_queue_family_properties   (physical_device);
                        const auto extension_properties     = vx::enumerate_physical_device_extension_properties(physical_device);
                            
                        if (properties.api_version < vx::api_version_e::_1_4) return;

                        const auto has_graphics_queue       = std::ranges::any_of(queue_family_properties, [ ](const vx::queue_family_properties& queue_family_properties) -> vx::bool_t
                            {
                                return static_cast<vx::bool_t>(queue_family_properties.queue_flags & vx::queue_flags_e::graphics);
                            });
                        if (!has_graphics_queue)       return;

                        const auto all_extensions_supported = std::ranges::all_of(required_extensions    , [&](const vx::string_view required_name) -> vx::bool_t
                            {
                                return std::ranges::any_of(extension_properties, [required_name](const vx::extension_properties& property) -> vx::bool_t
                                    {
                                        return std::strcmp(property.name.data(), required_name) == vx::int32_t{0};
                                    });
                            });
                        if (!all_extensions_supported) return;

                        const auto score                    = std::invoke([&]() -> vx::uint32_t
                            {
                                const auto device_type_score  = std::invoke([&]() -> vx::uint32_t
                                    {
                                        switch (properties.device_type)
                                        {
                                            case vx::physical_device_type_e::discrete_gpu  : return 8u;
                                            case vx::physical_device_type_e::integrated_gpu: return 2u;

                                            default                                        : return 1u;
                                        }
                                    });
                                const auto video_memory_score = std::invoke([&]() -> vx::uint32_t
                                    {
                                        const auto local_heaps = std::views::iota(vx::uint32_t{ 0u }, memory_properties.memory_heap_count)
                                            | std::views::transform([&](      vx::uint32_t     index      ) { return memory_properties.memory_heaps[index];                                                    })
                                            | std::views::filter   ([ ](const vx::memory_heap& memory_heap) { return (memory_heap.flags & vx::memory_heap_flags_e::device_local) != vx::memory_heap_flags_e{}; })
                                            | std::ranges::to<std::vector>();
                                            
                                        const auto max_video_memory = std::ranges::max_element(local_heaps, std::less{}, &vx::memory_heap::size);
                                        if (max_video_memory == local_heaps.end()) return vx::uint32_t{ 0u };
                                            
                                        const auto gigabyte = static_cast<vx::uint32_t>(std::pow(2u, 30u));
                                        return static_cast<vx::uint32_t>(std::to_underlying(max_video_memory->size) / gigabyte);
                                    });

                                return device_type_score + video_memory_score;
                            });
                        result.emplace(score, physical_device);
                    });

                return result;
            });
        if (candidates.empty()) throw std::runtime_error{ "No suitable physical device found!" };

        return vx::physical_device{ candidates.rbegin()->second };
    }
}
