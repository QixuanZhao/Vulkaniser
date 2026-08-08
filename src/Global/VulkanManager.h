#pragma once

class VulkanManager {
protected:
    VulkanManager() = default;
    static VulkanManager vulkanManagerInstance;

    vk::raii::Context vkRaiiContext;
    vk::raii::Instance vkInstance = nullptr;

    constexpr static vk::ApplicationInfo appInfo = {
        .pApplicationName = "Vulkaniser",
        .applicationVersion = VK_MAKE_VERSION(0, 0, 0),
        .pEngineName = "No Engine",
        .engineVersion = VK_MAKE_VERSION(0, 0, 0),
        .apiVersion = vk::ApiVersion14
    };

    void createInstance() {
        if (vkInstance != nullptr) { return; }

        std::vector<const char*> instanceExtensions = {
            VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME
        };

        vk::InstanceCreateInfo instanceCreateInfo = {
            .pApplicationInfo = &appInfo,
        };

        instanceCreateInfo.setFlags(vk::InstanceCreateFlagBits::eEnumeratePortabilityKHR);
        instanceCreateInfo.setPEnabledExtensionNames(instanceExtensions);

        vkInstance = vk::raii::Instance(vkRaiiContext, instanceCreateInfo);
    }

    ~VulkanManager() {
        cleanup();
    }
public:
    static VulkanManager& instance() {
        return VulkanManager::vulkanManagerInstance;
    }

    void setInstance(VkInstance* instance) {
        vkInstance = vk::raii::Instance(vkRaiiContext, vk::Instance(*instance));
    }

    void initialize() {
        createInstance();
    }

    vk::raii::Instance& getVkInstance() {
        return vkInstance;
    }

    void cleanup() {
        vkInstance.release();
    }
};