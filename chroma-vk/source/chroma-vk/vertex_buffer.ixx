export module vx.vertex_buffer;

import std;
import <vulkan/vulkan.h>;
import vx;
import vx.logical_device;

export namespace vx
{
    class vertex_buffer
    {
    public:
        vertex_buffer()
        {
            //auto find_memory_type     = [&](std::uint32_t type_filter, vk::MemoryPropertyFlags property_flags) -> std::optional<std::uint32_t>
            //    {
            //        const auto memory_properties = physical_device_->getMemoryProperties();
            //        for (auto index : std::views::iota(0u, memory_properties.memoryTypeCount))
            //        {
            //            if ((type_filter & (1 << index)) && (memory_properties.memoryTypes[index].propertyFlags & property_flags) == property_flags) return index;
            //        };

            //        return std::nullopt;
            //    };

            //const auto buffer_create_info   = vk::BufferCreateInfo{
            //    vk::BufferCreateFlags{}                    , 
            //    sizeof(my_vertices[0]) * my_vertices.size(), 
            //    vk::BufferUsageFlagBits::eVertexBuffer     , 
            //    vk::SharingMode        ::eExclusive        , 
            //};
            //
            //vertex_buffer_                  = std::make_unique<vk::raii::Buffer>(*logical_device_, buffer_create_info);
            //
            //const auto memory_requirements  = vertex_buffer_->getMemoryRequirements();
            //const auto memory_type          = find_memory_type(memory_requirements.memoryTypeBits, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent);
            //if (!memory_type.has_value()) throw std::runtime_error{ "Valid memory type was not found!" };
            //
            //const auto memory_allocate_info = vk::MemoryAllocateInfo{
            //    memory_requirements.size, 
            //    memory_type.value()     , 
            //};

            //vertex_buffer_memory_           = std::make_unique<vk::raii::DeviceMemory>(*logical_device_, memory_allocate_info);
            //vertex_buffer_->bindMemory(*vertex_buffer_memory_, vk::DeviceSize{});

            //void* data                      = vertex_buffer_memory_->mapMemory(0, buffer_create_info.size);
            //memcpy(data, my_vertices.data(), buffer_create_info.size);
            //vertex_buffer_memory_->unmapMemory();
        }

    private:
        //vx::vertex_buffer_t vertex_buffer_;
    };
}
