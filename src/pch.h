#pragma once

// Precompiled header file for the Vulkaniser project

// Vulkan headers
#define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_raii.hpp>

// stdlib headers
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Qt headers
#include <QApplication>
#include <QVulkanWindow>
#include <QVulkanInstance>
#include <QWidget>

// Project headers
#include "Utilities/VulkanUtility.h"
#include "Global/VulkanManager.h"