//module;
//
//#include <vulkan/vulkan_raii.hpp>
//#include <glfw/glfw3.h>
//
//export module vulkan.tutorial;
//
//import std;
//
//constexpr auto enable_validation_layers = _DEBUG;
//
//template<bool B>
//constexpr auto select(auto true_result, auto false_result) -> auto
//{
//    if   constexpr (B) return true_result ;
//    else               return false_result;
//}
//
//static VKAPI_ATTR vk::Bool32 VKAPI_CALL debugCallback(
//    vk::DebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
//    vk::DebugUtilsMessageTypeFlagsEXT messageType,
//    const vk::DebugUtilsMessengerCallbackDataEXT* pCallbackData,
//    void* pUserData) {
//
//    std::cerr << "Validation layer: " << pCallbackData->pMessage << std::endl;
//    return vk::False;
//}
//
//export namespace vk
//{
//    class HelloTriangleApplication
//    {
//    public:
//        auto run() -> int
//        {
//            initVulkan();
//            initWindow();
//            mainLoop  ();
//            cleanup   ();
//
//            return 0;
//        }
//
//    private:
//        void initVulkan()
//        {
//            createInstance();
//            createDebugMessenger();
//        }
//        
//        void createInstance() 
//        {
//            const auto requested_validation_layers = std::vector<const char*>{
//                "VK_LAYER_KHRONOS_validation"
//            };
//            const auto layer_properties            = vk::enumerateInstanceLayerProperties    ();
//            const auto extension_properties        = vk::enumerateInstanceExtensionProperties();
//            const auto contains_all_layers         = std::ranges::all_of(requested_validation_layers, [&](const auto& value) -> bool
//                {
//                    for (const auto& e : layer_properties)
//                        if (std::strcmp(e.layerName.data(), value)) return true;
//
//                    return false;
//                });
//            if (!contains_all_layers) throw std::runtime_error{ "Not all layers are supported!" };
//            
//            const auto required_extensions         = std::invoke([&]() ->std::vector<const char*>
//                {
//                    auto glfw_extension_count              = std::uint32_t{ 0u };
//                    auto required_glfw_instance_extensions = std::span<const char*>{ glfwGetRequiredInstanceExtensions(&glfw_extension_count), glfw_extension_count };
//                    
//                    auto extensions = std::vector<const char*>{ std::from_range, required_glfw_instance_extensions };
//                    if constexpr (enable_validation_layers) extensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
//
//                    return extensions;
//                });
//            const auto application_info            = vk::ApplicationInfo{
//                "Hello Triangle", VK_VERSION_1_4, 
//                "Fox"           , VK_VERSION_1_4, 
//                VK_API_VERSION_1_4, 
//            };
//                  auto create_info                 = vk::InstanceCreateInfo{
//                vk::InstanceCreateFlags{}, &application_info, 
//                std::uint32_t{ 0u }, nullptr, 
//                static_cast<std::uint32_t>(required_extensions.size()), required_extensions.data()
//            };
//            if constexpr (enable_validation_layers)
//            {
//                create_info.enabledLayerCount   = static_cast<std::uint32_t>(requested_validation_layers.size());
//                create_info.ppEnabledLayerNames = requested_validation_layers.data();
//            }
//            
//            instance_ = vk::createInstance(create_info);
//            if (!instance_) throw std::runtime_error{ "Failed to create instance!" };
//        }
//        void createDebugMessenger()
//        {
//            
//            auto debug_messenger_create_info = vk::DebugUtilsMessengerCreateInfoEXT(
//                vk::DebugUtilsMessengerCreateFlagBitsEXT{}, 
//                vk::DebugUtilsMessageSeverityFlagsEXT{ 
//                    vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose | 
//                    vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning | 
//                    vk::DebugUtilsMessageSeverityFlagBitsEXT::eError   }, 
//                vk::DebugUtilsMessageTypeFlagsEXT{ 
//                    vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral     | 
//                    vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation  | 
//                    vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance }, 
//                debugCallback, 
//                nullptr 
//            );
//
//            debug_messenger_ = instance_.createDebugUtilsMessengerEXT(debug_messenger_create_info);
//        }
//
//        void initWindow() 
//        {
//            glfwInit();
//
//            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
//            glfwWindowHint(GLFW_RESIZABLE , GLFW_FALSE );
//
//            window_ = glfwCreateWindow(800, 600, "Vulkan", nullptr, nullptr);
//        }
//
//        void mainLoop()
//        {
//            while (!glfwWindowShouldClose(window_)) 
//            {
//                glfwPollEvents();
//            }
//        }
//
//        void cleanup()
//        {
//            instance_.destroy(nullptr, VULKAN_HPP_DEFAULT_DISPATCHER);
//
//            glfwDestroyWindow(window_);
//            glfwTerminate();
//        }
//
//        GLFWwindow*                window_;
//        vk::Instance               instance_;
//        vk::DebugUtilsMessengerEXT debug_messenger_;
//    };
//}
