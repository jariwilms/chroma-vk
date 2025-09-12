export module vx;
export import vx.extensions;
export import vx.flags;
export import vx.functions;
export import vx.structures;
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




    template<typename T>
    auto ternary(vx::bool_t result, T true_result, T false_result) -> T
    {
        if   (result) return true_result ;
        else          return false_result;
    }
    template<vx::bool32_t R, typename T>
    auto ternary(T true_result, T false_result) -> T
    {
        if   constexpr (R) return true_result ;
        else               return false_result;
    }
     
    auto to_c_strings(std::span<const std::string> span) -> std::vector<const vx::char_t*>
    {
        return span
            | std::views::transform([](const std::string& string) { return string.c_str(); })
            | std::ranges::to<std::vector>();
    }
    
    auto get_required_layers_or_smth    () -> std::vector<vx::string_view>
    {
        auto layers = std::vector<vx::string_view>{};
        if constexpr (is_debug_build) layers.emplace_back("VK_LAYER_KHRONOS_validation");

        return layers;
    }
    auto get_required_extensions_or_smth() -> std::vector<vx::string_view>
    {
        auto glfw_extension_count              = vx::uint32_t{ 0u };
        auto required_glfw_instance_extensions = std::span  <const vx::string_view>{ ::glfwGetRequiredInstanceExtensions(&glfw_extension_count), glfw_extension_count };
        auto extensions                        = std::vector<      vx::string_view>{ std::from_range, required_glfw_instance_extensions };
        if constexpr (is_debug_build) extensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

        return extensions;
    }
    auto debug_callback(VkDebugUtilsMessageSeverityFlagBitsEXT vk_message_severity, VkDebugUtilsMessageTypeFlagsEXT, const VkDebugUtilsMessengerCallbackDataEXT* vk_callback_data, void*) -> vx::uint32_t
    {
        if (vk_message_severity > VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) std::println("{}", vk_callback_data->pMessage);

        return vx::false_;
    }
}
