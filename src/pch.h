#pragma once

// Precompiled header file for the Vulkaniser project

// Vulkan headers
#define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
// #define VULKAN_HPP_NO_EXCEPTIONS
#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_raii.hpp>

// stdlib headers
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <tuple>
#include <mutex>
#include <thread>

// Qt headers
#include <QApplication>
#include <QVulkanWindow>
#include <QVulkanInstance>
#include <QWidget>
#include <QLayout>
#include <QListView>
#include <QAbstractListModel>
#include <QPointer>
#include <QDialog>

// Project headers
#include "Global/VulkanManager.h"

// Projection Macros

// Create a Vulkan instance manually or let QVulkanInstance handle it
// Please let it be false for now, as it is not working properly on macOS
#define CREATE_VULKAN_MANUALLY false