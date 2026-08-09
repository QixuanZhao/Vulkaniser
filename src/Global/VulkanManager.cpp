#include "VulkanManager.h"

VulkanManager VulkanManager::vulkanManagerInstance = VulkanManager();

VulkanManager::~VulkanManager() {
    cleanup();
}