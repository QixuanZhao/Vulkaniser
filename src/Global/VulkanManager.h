#pragma once

#ifndef VULKAN_MANAGER_H
#define VULKAN_MANAGER_H

class VulkanManager {
    static VulkanManager vulkanManagerInstance;
protected:
    VulkanManager() = default;
    ~VulkanManager();

    vk::raii::Context m_context;
    vk::raii::Instance m_instance{nullptr};
    vk::raii::PhysicalDevices m_physicalDevices{nullptr};
public:
    inline static VulkanManager& shared() {
        return VulkanManager::vulkanManagerInstance;
    }

    inline void setInstance(const VkInstance& instance) {
        m_instance = vk::raii::Instance(m_context, vk::Instance(instance));
        m_physicalDevices = vk::raii::PhysicalDevices(m_instance);
        
        if (m_physicalDevices.empty()) {
            throw std::runtime_error("No physical devices found.");
        }
    }

    inline vk::raii::Instance& instance() { return m_instance; }
    inline const vk::raii::Instance& instance() const { return m_instance; }
    inline vk::raii::Context& context() { return m_context; }
    inline const vk::raii::Context& context() const { return m_context; }
    inline vk::raii::PhysicalDevices& physicalDevices() { return m_physicalDevices; }
    inline const vk::raii::PhysicalDevices& physicalDevices() const { return m_physicalDevices; }

    void cleanup() {
#if !CREATE_VULKAN_MANUALLY
        m_instance.release();
#endif
    }

#if NDEBUG
    constexpr static bool enableValidationLayers = false;
#else
    constexpr static bool enableValidationLayers = true;
#endif
};

#endif // VULKAN_MANAGER_H