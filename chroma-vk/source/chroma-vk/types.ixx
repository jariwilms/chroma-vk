export module vx.types;

import std;
import glm;
import <vulkan/vulkan.h>;

export namespace vx
{
    using void_t    =          void     ;
    using bool_t    =          bool     ;
    using char_t    =          char     ;
    using schar_t   =   signed char     ;
    using uchar_t   = unsigned char     ;
    using int8_t    =   signed char     ;
    using uint8_t   = unsigned char     ;
    using int16_t   =   signed short    ;
    using uint16_t  = unsigned short    ;
    using int32_t   =   signed int      ;
    using uint32_t  = unsigned int      ;
    using int64_t   =   signed long long;
    using uint64_t  = unsigned long long;
    using float32_t =          float    ;
    using float64_t =          double   ;

    using bool32_t  = vx::uint32_t;
    using byte_t    = vx::uint8_t;
    using size_t    = vx::uint64_t;

    using buffer_t                = VkBuffer;
    using buffer_view_t           = VkBufferView;
    using command_buffer_t        = VkCommandBuffer;
    using command_pool_t          = VkCommandPool;
    using descriptor_pool_t       = VkDescriptorPool;
    using descriptor_set_layout_t = VkDescriptorSetLayout;
    using descriptor_set_t        = VkDescriptorSet;
    using device_memory_t         = VkDeviceMemory;
    using event_t                 = VkEvent;
    using fence_t                 = VkFence;
    using frame_buffer_t          = VkFramebuffer;
    using image_t                 = VkImage;
    using image_view_t            = VkImageView;
    using instance_t              = VkInstance;
    using logical_device_t        = VkDevice;
    using physical_device_t       = VkPhysicalDevice;
    using pipeline_cache_t        = VkPipelineCache;
    using pipeline_layout_t       = VkPipelineLayout;
    using pipeline_t              = VkPipeline;
    using query_pool_t            = VkQueryPool;
    using queue_t                 = VkQueue;
    using render_pass_t           = VkRenderPass;
    using sampler_t               = VkSampler;
    using semaphore_t             = VkSemaphore;
    using shader_module_t         = VkShaderModule;
    using surface_t               = VkSurfaceKHR;
    using swap_chain_t            = VkSwapchainKHR;

    using debug_utils_messenger_callback_t = PFN_vkDebugUtilsMessengerCallbackEXT;

    enum : vx::bool_t
    {
        false_ = false, 
        true_  = true , 
    };



    template<typename T> using pointer_t   = T*;
    template<typename T> using reference_t = T&;
                         using next_t      = vx::pointer_t<const vx::void_t>;





    template<typename T, typename U>
    struct enable_conversion
    {
        using native_t = U;

        enable_conversion()
        {
            static_assert(sizeof(std::remove_cvref_t<std::remove_pointer_t<T>>) == sizeof(std::remove_cvref_t<std::remove_pointer_t<U>>));
        }

        operator vx::pointer_t<      U>()
        {
            return std::bit_cast<vx::pointer_t<U>>(this);
        }
        operator vx::pointer_t<const U>() const
        {
            return std::bit_cast<vx::pointer_t<const U>>(this);
        }
    };





    template<typename T, vx::uint32_t S>
    using array = std::array<T, S>;
    template<typename T>
    class span
    {
    public:
        span()
            : size_{ 0u }, pointer_{} {}
        span(vx::pointer_t<T> pointer, vx::uint64_t size)
            : size_{ static_cast<vx::uint32_t>(size) }, pointer_{ pointer } {}
        template<std::ranges::contiguous_range R>
        span(std::from_range_t, R&& range)
            : size_{ static_cast<vx::uint32_t>(std::ranges::size(range)) }, pointer_{ std::ranges::data(range) } {}

        auto size() const -> vx::uint32_t
        {
            return size_;
        }
        auto data(this auto&& self) -> auto&&
        {
            return self.pointer_;
        }

    private:
        vx::uint32_t size_;
        T*           pointer_;
    };
    template<typename T>
    struct padded_span
    {
    public:
        padded_span()
            : size_{}, padding_{}, pointer_{} {}
        padded_span(vx::span<T> span)
            : size_{span.size()}, pointer_{ span.data() } {}

        auto size() const -> vx::uint32_t
        {
            return size_;
        }
        auto data(this auto&& self) -> auto&&
        {
            return self.pointer_;
        }

    private:
        vx::uint32_t size_;
        vx::uint32_t padding_;
        T*           pointer_;
    };
    template<typename T>
    struct aligned_span
    {
    public:
        aligned_span()
            : size_{}, pointer_{} {}
        aligned_span(vx::span<T> span)
            : size_{ span.size() }, pointer_{ from_pointer(span.data()) } {}

        auto size() const -> vx::uint32_t
        {
            return size_;
        }
        auto data(this auto&& self) -> auto&&
        {
            return reinterpret_cast<T*>(self.pointer_.data());
        }

    private:
        static auto from_pointer(vx::pointer_t<T> pointer) -> vx::array<vx::int32_t, 2u>
        {
            const auto value = reinterpret_cast<vx::int64_t>(pointer);
            return vx::array<vx::int32_t, 2u>
            {
                static_cast<std::int32_t>(value       ), 
                static_cast<std::int32_t>(value >> 32u), 
            };
        }

        vx::uint32_t                size_;
        std::array<vx::int32_t, 2u> pointer_;
    };
    using string_view = vx::pointer_t<const vx::char_t>;





    template<typename T, vx::uint32_t N>
    using vector_t = glm::vec<N, T, glm::packed_highp>;

    using vector1u = vx::vector_t<vx::uint32_t , 1u>;
    using vector2u = vx::vector_t<vx::uint32_t , 2u>;
    using vector3u = vx::vector_t<vx::uint32_t , 3u>;
    using vector4u = vx::vector_t<vx::uint32_t , 4u>;

    using vector1f = vx::vector_t<vx::float32_t, 1u>;
    using vector2f = vx::vector_t<vx::float32_t, 2u>;
    using vector3f = vx::vector_t<vx::float32_t, 3u>;
    using vector4f = vx::vector_t<vx::float32_t, 4u>;
}
