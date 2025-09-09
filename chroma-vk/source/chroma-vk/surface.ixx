module;

#include <vulkan/vulkan.h>
#include <glfw/glfw3.h>

export module vx.surface;

import std;
import vx;
import vx.types;
import vx.instance;

export namespace vx
{
    GLFWwindow* window;

    class surface
    {
    public:
        using native_t = VkSurfaceKHR;

        surface(vx::instance instance)
        {
            const auto result = std::bit_cast<vx::result_e>(glfwCreateWindowSurface(instance, window, nullptr, &surface_));
            if (result != vx::result_e::success) throw std::runtime_error{ "Failed to create surface!" };
        }

        operator       VkSurfaceKHR&()
        {
            return surface_;
        }
        operator const VkSurfaceKHR&() const
        {
            return surface_;
        }

    private:
        VkSurfaceKHR surface_;
    };
}
