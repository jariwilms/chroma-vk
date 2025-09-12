export module vx.constants;

import <vulkan/vulkan.h>;
import vx.types;

export namespace vx
{
    constexpr auto maximum_extension_name_size       = vx::uint32_t{ VK_MAX_EXTENSION_NAME_SIZE       };
    constexpr auto maximum_description_size          = vx::uint32_t{ VK_MAX_DESCRIPTION_SIZE          };
    constexpr auto maximum_physical_device_name_size = vx::uint32_t{ VK_MAX_PHYSICAL_DEVICE_NAME_SIZE };
    constexpr auto uuid_size                         = vx::uint32_t{ VK_UUID_SIZE                     };
    constexpr auto maximum_memory_types              = vx::uint32_t{ VK_MAX_MEMORY_TYPES };
    constexpr auto maximum_memory_heaps              = vx::uint32_t{ VK_MAX_MEMORY_HEAPS };
}
