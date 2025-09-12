module;

#include <vulkan/vulkan.h>
#include <glfw/glfw3.h>

export module vx.surface;

import std;
import vx;
import vx.instance;

export namespace vx
{
    GLFWwindow* window;

    class surface
    {
    public:
        surface(vx::instance instance)
        {
            vx::handle_result(::glfwCreateWindowSurface(instance, window, nullptr, &surface_));
        }

        operator       vx::surface_t&()
        {
            return surface_;
        }
        operator const vx::surface_t&() const
        {
            return surface_;
        }

    private:
        vx::surface_t surface_;
    };
}
