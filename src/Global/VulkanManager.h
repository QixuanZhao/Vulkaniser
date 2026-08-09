#pragma once

#include <cstdlib>
#include <vulkan/vulkan_to_string.hpp>
class VulkanManager {
protected:
    VulkanManager() = default;
    static VulkanManager vulkanManagerInstance;

    vk::raii::Context m_context;
    vk::raii::Instance m_instance = nullptr;

    void createInstance() {
        if (m_instance != nullptr) { return; }
        
        std::vector<const char*> extensionNames = {
            vk::KHRPortabilityEnumerationExtensionName
        };

        constexpr vk::ApplicationInfo appInfo = {
            .pApplicationName = "Vulkaniser",
            .applicationVersion = VK_MAKE_VERSION(0, 0, 0),
            .pEngineName = "No Engine",
            .engineVersion = VK_MAKE_VERSION(0, 0, 0),
            .apiVersion = vk::ApiVersion14
        };

        vk::InstanceCreateInfo instanceCreateInfo = {
            .flags = vk::InstanceCreateFlagBits::eEnumeratePortabilityKHR,
            .pApplicationInfo = &appInfo,
            .enabledExtensionCount = static_cast<uint32_t>(extensionNames.size()),
            .ppEnabledExtensionNames = extensionNames.data()
        };

        try {
            m_instance = vk::raii::Instance(m_context, instanceCreateInfo);
        } catch (const vk::SystemError& err) {
            std::cerr << "Vulkan error: " << err.what() << std::endl;
            std::exit(EXIT_FAILURE);
        } catch (const std::exception& err) {
            std::cerr << "Error: " << err.what() << std::endl;
            std::exit(EXIT_FAILURE);
        } catch (...) {
            std::cerr << "Unknown error" << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }

    ~VulkanManager() {
        cleanup();
    }
public:
    static VulkanManager& instance() {
        return VulkanManager::vulkanManagerInstance;
    }

    void setInstance(const VkInstance& instance) {
        m_instance = vk::raii::Instance(m_context, vk::Instance(instance));
    }

    void initialize() {
        createInstance();
    }

    vk::raii::Instance& getVkInstance() {
        return m_instance;
    }

    void cleanup() {
#if !CREATE_VULKAN_MANUALLY
        m_instance.release();
#endif
    }
};