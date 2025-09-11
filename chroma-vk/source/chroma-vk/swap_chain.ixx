module;

#include <glfw/glfw3.h>

export module vx.swap_chain;

import std;
import <vulkan/vulkan.h>;
import <vulkan/vulkan_raii.hpp>;
import vx;
import vx.instance;
import vx.surface;
import vx.physical_device;
import vx.logical_device;

export namespace vx
{
    template<std::convertible_to<vx::physical_device_t> T, std::convertible_to<vx::surface_t> U>
    auto get_physical_device_surface_capabilities(T physical_device, U surface) -> vx::surface_capabilities
    {
        auto surface_capabilities = vx::surface_capabilities{};
        const auto result = std::bit_cast<vx::result_e>(::vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physical_device, surface, surface_capabilities));
        if (result != vx::result_e::success) throw std::invalid_argument{ "" };

        return surface_capabilities;
    }
    template<std::convertible_to<vx::physical_device_t> T, std::convertible_to<vx::surface_t> U>
    auto get_physical_device_surface_formats(T physical_device, U surface) -> std::vector<vx::surface_format>
    {
        const auto physical_device_surface_info = vx::physical_device_surface_info{ .surface = surface };
        return vx::query_and_retrieve<::vkGetPhysicalDeviceSurfaceFormats2KHR, vx::surface_format>(physical_device, physical_device_surface_info);
    }
    template<std::convertible_to<vx::physical_device_t> T, std::convertible_to<vx::surface_t> U>
    auto get_physical_device_surface_presentation_modes(T physical_device, U surface) -> std::vector<vx::presentation_mode_e>
    {
              auto count        = vx::uint32_t{};
        const auto count_result = std::bit_cast<vx::result_e>(::vkGetPhysicalDeviceSurfacePresentModesKHR(physical_device, surface, &count, nullptr));
        if (count_result != vx::result_e::success) throw std::runtime_error{ "" };

              auto data         = std::vector<vx::presentation_mode_e>(count);
        const auto data_result  = std::bit_cast<vx::result_e>(::vkGetPhysicalDeviceSurfacePresentModesKHR(physical_device, surface, &count, std::bit_cast<VkPresentModeKHR*>(data.data())));
        if (data_result != vx::result_e::success) throw std::runtime_error{ "" };
        
        return data;
    }

    template<std::convertible_to<vx::logical_device_t> T>
    auto create_swap_chain(T logical_device, const vx::swap_chain_create_info& swap_chain_create_info) -> vx::swap_chain_t
    {
              auto vk_swap_chain = vx::swap_chain_t{};
        const auto result        = std::bit_cast<vx::result_e>(::vkCreateSwapchainKHR(logical_device, swap_chain_create_info, nullptr, &vk_swap_chain));
        if (result != vx::result_e::success) throw std::runtime_error{ "" };

        return vk_swap_chain;
    }
    template<std::convertible_to<vx::image_t> T, std::convertible_to<vx::logical_device_t> U, std::convertible_to<vx::swap_chain_t> V>
    auto get_swap_chain_images(U logical_device, V swap_chain) -> std::vector<T>
    {
        return vx::query_and_retrieve<::vkGetSwapchainImagesKHR, T>(logical_device, swap_chain);
    }

    template<std::convertible_to<vx::logical_device_t> T>
    auto create_image_view(T logical_device, const vx::image_view_create_info& image_view_create_info) -> vx::image_view_t
    {
        auto vk_image_view = vx::image_view_t{};
        const auto result = std::bit_cast<vx::result_e>(::vkCreateImageView(logical_device, image_view_create_info, nullptr, &vk_image_view));
        if (result != vx::result_e::success) throw std::runtime_error{ "" };

        return vk_image_view;
    }



    class swap_chain
    {
    public:
        swap_chain(vx::physical_device physical_device, vx::logical_device logical_device, vx::surface surface)
        {
            const auto surface_capabilities     = vx::get_physical_device_surface_capabilities      (physical_device, surface);
            const auto surface_formats          = vx::get_physical_device_surface_formats           (physical_device, surface);
            const auto presentation_modes       = vx::get_physical_device_surface_presentation_modes(physical_device, surface);

            image_format_ = std::invoke([&]() -> vx::format_e
                {
                    const auto iterator = std::ranges::find_if(surface_formats, [](const vx::surface_format& surface_format) 
                        {
                            return surface_format.format == vx::format_e::b8g8r8a8_srgb && surface_format.color_space == vx::color_space_e::srgb_nonlinear;
                        });
                        
                    return iterator != surface_formats.end() ? iterator->format : surface_formats.at(0u).format;
                    return {};
                });
            extent_       = std::invoke([&]() -> vx::extent_2d
                {
                    if (surface_capabilities.current_extent.width != std::numeric_limits<uint32_t>::max()) return surface_capabilities.current_extent;
    
                    auto width  = vx::int32_t{};
                    auto height = vx::int32_t{};
                    //::glfwGetFramebufferSize(window_, &width, &height); //TODO
    
                    return vx::extent_2d
                    {
                        .width  = std::clamp<vx::uint32_t>(width , surface_capabilities.min_image_extent.width , surface_capabilities.max_image_extent.width ), 
                        .height = std::clamp<vx::uint32_t>(height, surface_capabilities.min_image_extent.height, surface_capabilities.max_image_extent.height), 
                    };
                });
    
            const auto maximum_image_count      = std::max   (3u, surface_capabilities.min_image_count);
            const auto minimum_image_count      = vx::ternary(surface_capabilities.max_image_count, std::min(maximum_image_count, surface_capabilities.max_image_count), maximum_image_count);
            const auto supports_mailbox         = std::ranges::any_of(presentation_modes, [](const vx::presentation_mode_e presentation_mode)
                {
                    return presentation_mode == vx::presentation_mode_e::mailbox;
                });
            const auto presentation_mode        = vx::ternary(supports_mailbox, vx::presentation_mode_e::mailbox, vx::presentation_mode_e::fifo);

            const auto swap_chain_create_info   = vx::swap_chain_create_info
            {
                .surface             = surface                                  , 
                .minimum_image_count = minimum_image_count                      , 
                .image_format        = image_format_                            , 
                .image_color_space   = vx::color_space_e::srgb_nonlinear        , 
                .image_extent        = extent_                                  , 
                .image_array_layers  = vx::uint32_t{ 1u }                       , 
                .image_usage         = vx::image_usage_flags_e::color_attachment, 
                .image_sharing_mode  = vx::sharing_mode_e::exclusive            , 
                .pre_transform       = surface_capabilities.current_transform   , 
                .composite_alpha     = vx::composite_alpha_flags_e::opaque      , 
                .presentation_mode   = presentation_mode                        , 
                .clipped             = vx::true_                                , 
            };
    
            swap_chain_                         = vx::create_swap_chain               (logical_device, swap_chain_create_info);
            images_                             = vx::get_swap_chain_images<vx::image>(logical_device, *this                 );

            const auto image_sub_resource_range = vx::image_sub_resource_range
            {
                .aspect_flags     = vx::image_aspect_flags_e::color, 
                .base_mip_level   = vx::uint32_t{ 0u }             , 
                .level_count      = vx::uint32_t{ 1u }             , 
                .base_array_layer = vx::uint32_t{ 0u }             , 
                .layer_count      = vx::uint32_t{ 1u }             , 
            };
            const auto image_view_create_info   = vx::image_view_create_info
            {
                .view_type          = vx::image_view_type_e::_2d, 
                .format             = image_format_             , 
                .sub_resource_range = image_sub_resource_range  , 
            };
            std::ranges::for_each(images_, [&](const vx::image image)
                {
                    auto current_image_view_create_info  = image_view_create_info;
                    current_image_view_create_info.image = image;

                    image_views_.emplace_back(vx::create_image_view(logical_device, current_image_view_create_info));
                });
        }

        auto image_format() const -> vx::format_e
        {
            return image_format_;
        }
        auto extent      () const -> vx::extent_2d
        {
            return extent_;
        }
        auto images      () const -> const std::vector<vx::image>&
        {
            return images_;
        }

        operator       vx::swap_chain_t&()
        {
            return swap_chain_;
        }
        operator const vx::swap_chain_t&() const
        {
            return swap_chain_;
        }

    private:
        vx::swap_chain_t              swap_chain_;
        vx::format_e                  image_format_;
        vx::extent_2d                 extent_;
        std::vector<vx::image>        images_;
        std::vector<vx::image_view_t> image_views_;
    };
}
