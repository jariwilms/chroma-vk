export module vx.extensions;

import <vulkan/vulkan.h>;

export namespace vx::extension
{
    constexpr auto swap_chain             = VK_KHR_SWAPCHAIN_EXTENSION_NAME;
    constexpr auto spirv_1_4              = VK_KHR_SPIRV_1_4_EXTENSION_NAME;
    constexpr auto synchronization        = VK_KHR_SYNCHRONIZATION_2_EXTENSION_NAME;
    constexpr auto renderpass             = VK_KHR_CREATE_RENDERPASS_2_EXTENSION_NAME;
    constexpr auto shader_draw_parameters = VK_KHR_SHADER_DRAW_PARAMETERS_EXTENSION_NAME;
}
