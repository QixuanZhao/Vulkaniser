#pragma once

#include "Global/PhysicalDeviceProperty.h"
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
    std::shared_ptr<PhysicalDeviceProperty> m_physicalDeviceProperty{nullptr};
public:
    inline static VulkanManager& shared() {
        return VulkanManager::vulkanManagerInstance;
    }

    void setInstance(const VkInstance& instance);

    inline vk::raii::Instance& instance() { return m_instance; }
    inline const vk::raii::Instance& instance() const { return m_instance; }
    inline vk::raii::Context& context() { return m_context; }
    inline const vk::raii::Context& context() const { return m_context; }
    inline vk::raii::PhysicalDevices& physicalDevices() { return m_physicalDevices; }
    inline const vk::raii::PhysicalDevices& physicalDevices() const { return m_physicalDevices; }
    inline std::shared_ptr<const PhysicalDeviceProperty> physicalDeviceProperty() const { return m_physicalDeviceProperty; }

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