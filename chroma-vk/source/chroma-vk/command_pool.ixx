export module vx.command_pool;

import std;
import <vulkan/vulkan.h>;
import vx;
import vx.logical_device;

export namespace vx
{
    template<std::convertible_to<vx::logical_device_t> T>
    auto create_command_pool(T logical_device, const vx::command_pool_create_info& command_pool_create_info) -> vx::command_pool_t
    {
              auto vk_command_pool = vx::command_pool_t{};
        const auto result          = std::bit_cast<vx::result_e>(::vkCreateCommandPool(logical_device, command_pool_create_info, nullptr, &vk_command_pool));
        if (result != vx::result_e::success) throw std::runtime_error{ "" };

        return vk_command_pool;
    }

    class command_pool
    {
    public:
        command_pool(vx::logical_device logical_device)
        {
            const auto command_pool_create_info = vx::command_pool_create_info
            {
                .flags              = vx::command_pool_create_flags_e::reset_command_buffer, 
                .queue_family_index = logical_device.queue_index()                         , 
            };

            command_pool_ = vx::create_command_pool(logical_device, command_pool_create_info);
        }

    private:
        vx::command_pool_t command_pool_;
    };
}
