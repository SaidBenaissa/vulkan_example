#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class HelloTriangleApplication {
public:
    void run() {
        initWindow(); // Initialize the GLFW library and create a window,
        initVulkan(); // Initialize the Vulkan library
        mainLoop(); // Main loop of the application
        cleanup(); // Cleanup of the Vulkan library,
    }

private:
    GLFWwindow *window; // The window of the application
    VkInstance instance; // The instance of the Vulkan library

    void initWindow() {
        glfwInit(); // Initialize the GLFW library

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // Tell GLFW not to create an OpenGL context
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // Tell GLFW not to allow the window to be resized

        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr,
                                  nullptr); // Create a window, the last two parameters are for the monitor and the share parameter, which we don't need
    }

    void initVulkan() {
        createInstance(); // Create an instance of the Vulkan library, which is the main object of the library, and is responsible for the initialization and cleanup of the library
    }

    void createInstance() {
        VkApplicationInfo appInfo = {}; // The VkApplicationInfo structure contains information about the application, which is used by the Vulkan library to optimize the application for the specific hardware
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO; // The sType member is a required member of all Vulkan structures, and is used to tell Vulkan the type of the structure
        appInfo.pApplicationName = "Vulkan Triangle example"; // The pApplicationName member is a pointer to a null-terminated string containing the name of the application
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0,
                                                     0); // The applicationVersion member is a 32-bit integer containing the application's version number, encoded as described in the API Version Numbers and Semantics section
        appInfo.pEngineName = "No Engine"; // The pEngineName member is a pointer to a null-terminated string containing the name of the engine used to create the application
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo = {}; // The VkInstanceCreateInfo structure contains information about the instance of the Vulkan library
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO; // The sType member is a required member of all Vulkan structures, and is used to tell Vulkan the type of the structure
        createInfo.pApplicationInfo = &appInfo;

        uint32_t glfwExtensionCount = 0;
        const char **glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(
                &glfwExtensionCount); // Get the required extensions for the Vulkan library

        createInfo.enabledExtensionCount = glfwExtensionCount; // The enabledExtensionCount member is the number of extensions to enable
        createInfo.ppEnabledExtensionNames = glfwExtensions; // The ppEnabledExtensionNames member is a pointer to an array of enabledExtensionCount null-terminated UTF-8 strings containing the names of extensions to enable

        createInfo.enabledLayerCount = 0;

        if (vkCreateInstance(&createInfo, nullptr, &instance) !=
            VK_SUCCESS) { // Create an instance of the Vulkan library
            throw std::runtime_error(
                    "failed to create instance!"); // If the instance of the Vulkan library cannot be created, throw an exception
        }
    }


//    The mainLoop() function is the main loop of the application
    void mainLoop() {
        while (!glfwWindowShouldClose(window)) { // Check if the window should be closed
            glfwPollEvents(); // Poll for and process events
        }
    }

//    The cleanup() function is responsible for the cleanup of the Vulkan library
    void cleanup() { // Destroy the instance of the Vulkan library
        vkDestroyInstance(instance,
                          nullptr); // The first parameter is the instance of the Vulkan library, and the second parameter is a pointer to a custom allocator callback

        glfwDestroyWindow(
                window); // Destroy the window, the second parameter is a pointer to a custom allocator callback

        glfwTerminate(); // Terminate the GLFW library, freeing any resources allocated by GLFW, and closing any open windows
    }
};


int main() {
    HelloTriangleApplication app; // Create an instance of the HelloTriangleApplication class

    try {
        app.run(); // Run the application
    } catch (const std::exception &e) { // If an exception is thrown, print the exception message
        std::cerr << e.what() << std::endl; // Print the exception message to the standard error stream
        return EXIT_FAILURE; // Return an error code, indicating that the application has failed, and the operating system should return an error code, indicating that the application has failed
    }

    return EXIT_SUCCESS; // Return a success code, indicating that the application has succeeded, and the operating system should return a success code, indicating that the application has succeeded
}
