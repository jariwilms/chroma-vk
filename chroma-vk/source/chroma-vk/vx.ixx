export module vx;
export import vx.flags;
export import vx.types;

import std;
import glm;
import <vulkan/vulkan.h>;
import <glfw/glfw3.h>;

export namespace rm
{
    auto read_file(const std::filesystem::path& path) -> std::vector<std::uint8_t>
    {
        auto file = std::ifstream{ path, std::ios::binary };
        if (!file) throw std::invalid_argument{ "Could not open file!" };

        file.seekg(0, std::ios::end);
        const auto file_size = static_cast<std::size_t>(file.tellg());
        file.seekg(0, std::ios::beg);

        auto buffer = std::vector<vx::uint8_t>(file_size);
        file.read(reinterpret_cast<char*>(buffer.data()), file_size);
        if (!file) throw std::runtime_error{ "Could not read file!" };

        return buffer;
    };
}
export namespace vx
{
#ifndef _DEBUG
#define _DEBUG 0
#endif

    constexpr auto is_debug_build                      = vx::bool_t{ _DEBUG };
    constexpr auto maximum_frames_in_flight            = vx::uint32_t{ 2u };
    const     auto required_physical_device_extensions = std::vector{
        VK_KHR_CREATE_RENDERPASS_2_EXTENSION_NAME, 
        VK_KHR_SPIRV_1_4_EXTENSION_NAME          , 
        VK_KHR_SWAPCHAIN_EXTENSION_NAME          , 
        VK_KHR_SYNCHRONIZATION_2_EXTENSION_NAME  , 
    };
    const     auto required_logical_device_extensions  = std::vector{
        VK_KHR_CREATE_RENDERPASS_2_EXTENSION_NAME   , 
        VK_KHR_SHADER_DRAW_PARAMETERS_EXTENSION_NAME, 
        VK_KHR_SPIRV_1_4_EXTENSION_NAME             , 
        VK_KHR_SWAPCHAIN_EXTENSION_NAME             , 
        VK_KHR_SYNCHRONIZATION_2_EXTENSION_NAME     , 
    };

    constexpr auto maximum_extension_name_size         = VK_MAX_EXTENSION_NAME_SIZE;
    constexpr auto maximum_description_size            = VK_MAX_DESCRIPTION_SIZE;



              auto to_c_strings    (std::span<const std::string> span) -> std::vector<const vx::char_t*>
    {
        return span
            | std::views::transform([](const auto& string) { return string.c_str(); })
            | std::ranges::to<std::vector>();
    }

    


    

    template<typename T, vx::uint32_t S>
    using array = std::array<T, S>;
    //template<typename T, vx::uint32_t S>
    //class array
    //{
    //public:
    //    array() = default;
    //    array(vx::pointer_t<T> pointer)
    //        : pointer_{ pointer } {}
    //    auto size() const -> vx::uint32_t
    //    {
    //        return S;
    //    }
    //    auto data(this auto&& self) -> auto&&
    //    {
    //        return self.pointer_;
    //    }
    //private:
    //    T pointer_[S];
    //};
    template<typename T>
    class span
    {
    public:
        span() = default;
        span(vx::pointer_t<T> pointer, vx::uint64_t size)
            : pointer_{ pointer }, size_{ static_cast<vx::uint32_t>(size) } {}
        template<std::ranges::contiguous_range R>
        span(std::from_range_t, R&& range)
            : pointer_(std::ranges::data(range)), size_(static_cast<vx::uint32_t>(std::ranges::size(range))) {}

        auto size() const -> vx::uint32_t
        {
            return size_;
        }
        auto data(this auto&& self) -> auto&&
        {
            return self.pointer_;
        }

    private:
        vx::uint32_t     size_   ;
        vx::pointer_t<T> pointer_;
    };
    using string_view = vx::pointer_t<const vx::char_t>;
    //class string_view
    //{
    //public:
    //    string_view() = default;
    //    string_view(const std::string&              value)
    //        : pointer_{ value.c_str() } {}
    //    string_view(vx::pointer_t<const vx::char_t> value)
    //        : pointer_{ value } {}
    //    
    //    auto data(this auto&& self) -> auto&&
    //    {
    //        return self.pointer_;
    //    }
    //    
    //    constexpr operator vx::pointer_t<const vx::char_t>() const
    //    {
    //        return pointer_;
    //    }
    //private:
    //    vx::pointer_t<const vx::char_t> pointer_ = nullptr;
    //};





    struct extension_properties
    {
        vx::string_view name;
        vx::uint32_t    specification_version;
    };
    struct layer_properties
    {
        vx::string_view name;
        vx::uint32_t    specification_version;
        vx::uint32_t    implementation_version;
        vx::string_view description;
    };
    struct extension_properties2
    {
        using native_t = VkExtensionProperties;

        vx::array<vx::char_t, vx::maximum_extension_name_size> name;
        vx::uint32_t                                           specification_version;
    };
    struct layer_properties2
    {
        using native_t = VkLayerProperties;

        vx::array<vx::char_t, vx::maximum_extension_name_size> name;
        vx::uint32_t                                           specification_version;
        vx::uint32_t                                           implementation_version;
        vx::array<vx::char_t, vx::maximum_description_size>    description;
    };

    

    auto get_required_layers_or_smth    () -> std::vector<vx::string_view>
    {
        auto layers = std::vector<vx::string_view>{};
        if constexpr (is_debug_build) layers.emplace_back("VK_LAYER_KHRONOS_validation");

        return layers;
    }
    auto get_required_extensions_or_smth() -> std::vector<vx::string_view>
    {
        auto glfw_extension_count              = vx::uint32_t{ 0u };
        auto required_glfw_instance_extensions = std::span  <const vx::char_t*>{ glfwGetRequiredInstanceExtensions(&glfw_extension_count), glfw_extension_count };
        auto extensions                        = std::vector<vx::string_view  >{ std::from_range, required_glfw_instance_extensions };
        if constexpr (is_debug_build) extensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

        return extensions;
    }



    auto debug_callback(VkDebugUtilsMessageSeverityFlagBitsEXT vk_message_severity, VkDebugUtilsMessageTypeFlagsEXT, const VkDebugUtilsMessengerCallbackDataEXT* vk_callback_data, void*) -> vx::uint32_t
    {
        if (vk_message_severity > VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) std::println("{}", vk_callback_data->pMessage);

        return vx::false_;
    }



    //template<auto Fn, typename T, typename... Args>
    //auto query_and_retrieve(Args&&... args)
    //{
    //    auto result = vx::result_e {};
    //    auto count  = vx::uint32_t {};

    //    result = std::bit_cast<vx::result_e>(Fn(args..., &count, nullptr));
    //    if (result != vx::result_e::success) throw std::runtime_error{ "Failed to retrieve data count!" };

    //    auto data   = std::vector<T>(count);

    //    result = std::bit_cast<vx::result_e>(Fn(args..., &count, std::bit_cast<typename T::native_t*>(data.data())));
    //    if (result != vx::result_e::success) throw std::runtime_error{ "Failed to retrieve data!" };

    //    return data;
    //}
    //template<auto Fn, typename T, typename... Args>
    //auto query_and_retrieve_nr(Args&&... args)
    //{
    //    auto count  = vx::uint32_t {};

    //    Fn(args..., &count, nullptr);

    //    auto data   = std::vector<T>(count);

    //    Fn(args..., &count, std::bit_cast<typename T::native_t*>(data.data()));

    //    return data;
    //}
    template<auto Fn, typename T, typename... Args>
    auto query_and_retrieve(Args&&... args)
    {
        if constexpr (std::is_same_v<std::invoke_result_t<decltype(Fn), Args..., vx::uint32_t*, typename T::native_t*>, VkResult>)
        {
            auto count        = vx::uint32_t {};
            auto count_result = std::bit_cast<vx::result_e>(Fn(args..., &count, nullptr));
            if (count_result != vx::result_e::success) throw std::runtime_error{ "Failed to retrieve data count!" };

            auto data         = std::vector<T>(count);

            auto data_result  = std::bit_cast<vx::result_e>(Fn(args..., &count, std::bit_cast<typename T::native_t*>(data.data())));
            if (data_result != vx::result_e::success) throw std::runtime_error{ "Failed to retrieve data!" };

            return data;
        }
        else
        {
            auto count = vx::uint32_t{};
            Fn(args..., &count, nullptr);
            auto data  = std::vector<T>(count);
            Fn(args..., &count, std::bit_cast<typename T::native_t*>(data.data()));

            return data;
        }
    }

    auto enumerate_instance_layer_properties() -> std::vector<vx::layer_properties2>
    {
        return vx::query_and_retrieve<vkEnumerateInstanceLayerProperties, vx::layer_properties2>();
    }
    auto enumerate_instance_extension_properties(vx::string_view layer_name = {}) -> std::vector<vx::extension_properties2>
    {
        return vx::query_and_retrieve<vkEnumerateInstanceExtensionProperties, vx::extension_properties2>(layer_name);
    }
}
