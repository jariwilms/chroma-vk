export module fox.graphics;

import std;

export namespace gl
{
    struct texture2d
    {
        texture2d(int n) : n{ n } {}

        void my_func()
        {
            std::println("derived: {}", n);
        }

        int n;
    };
}
export namespace vk
{
    struct texture2d
    {
        texture2d(float f) : f{ f } {}

        void my_func()
        {
            std::println("derived2: {}", f);
        }
        void specific_vulkan_func()
        {

        }

        float f;
        float g;
        float h;
    };
}
namespace gfx::api
{
    struct A {};

    template<typename T>
    concept valid_texture = requires (T instance)
    {
        { instance.my_func() } -> std::convertible_to<void>;
    };

    template<api::valid_texture T>
    struct texture2d
    {
        static auto create(float f) -> std::shared_ptr<api::texture2d<T>>
        {
            return std::make_shared<api::texture2d<T>>(f);
        }

        void my_func()
        {
            if constexpr (std::is_same_v<T, vk::texture2d>) std::println("Same as vulkan");

            instance_->my_func();
        }

        auto to_underlying() -> std::shared_ptr<T>
        {
            return instance_;
        }

        template<typename... Args>
        texture2d(Args&&... args) : instance_{ std::make_shared<T>(std::forward<Args>(args)...) } {}

    private:
        std::shared_ptr<T> instance_;
    };
}
export namespace gfx
{
    using texture2d = api::texture2d<gl::texture2d>;

    void do_thing(std::shared_ptr<gl::texture2d> texture)
    {
        std::println("Called opengltexture");
        texture->my_func();
    }
    void do_thing(std::shared_ptr<vk::texture2d> texture)
    {
        std::println("Called vulkantexture");
        texture->my_func();
        texture->specific_vulkan_func();
    }
    void do_thing(std::shared_ptr<gfx::texture2d> texture)
    {
        texture->my_func();
        do_thing(texture->to_underlying());
    }
}
