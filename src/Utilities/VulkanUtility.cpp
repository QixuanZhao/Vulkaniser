#include "VulkanUtility.h"

void VulkanUtility::print(VkResult result, std::ostream &outStream)
{
    switch (result) {
    case VK_SUCCESS:
        outStream << "VK_SUCCESS";
        break;
    case VK_NOT_READY:
        outStream << "VK_NOT_READY";
        break;
    case VK_TIMEOUT:
        outStream << "VK_TIMEOUT";
        break;
    case VK_EVENT_SET:
        outStream << "VK_EVENT_SET";
        break;
    case VK_EVENT_RESET:
        outStream << "VK_EVENT_RESET";
        break;
    case VK_INCOMPLETE:
        outStream << "VK_INCOMPLETE";
        break;
    case VK_ERROR_OUT_OF_HOST_MEMORY:
        outStream << "VK_ERROR_OUT_OF_HOST_MEMORY";
        break;
    case VK_ERROR_OUT_OF_DEVICE_MEMORY:
        outStream << "VK_ERROR_OUT_OF_DEVICE_MEMORY";
        break;
    case VK_ERROR_INITIALIZATION_FAILED:
        outStream << "VK_ERROR_INITIALIZATION_FAILED";
        break;
    case VK_ERROR_DEVICE_LOST:
        outStream << "VK_ERROR_DEVICE_LOST";
        break;
    case VK_ERROR_MEMORY_MAP_FAILED:
        outStream << "VK_ERROR_MEMORY_MAP_FAILED";
        break;
    case VK_ERROR_LAYER_NOT_PRESENT:
        outStream << "VK_ERROR_LAYER_NOT_PRESENT";
        break;
    case VK_ERROR_EXTENSION_NOT_PRESENT:
        outStream << "VK_ERROR_EXTENSION_NOT_PRESENT";
        break;
    case VK_ERROR_FEATURE_NOT_PRESENT:
        outStream << "VK_ERROR_FEATURE_NOT_PRESENT";
        break;
    case VK_ERROR_INCOMPATIBLE_DRIVER:
        outStream << "VK_ERROR_INCOMPATIBLE_DRIVER";
        break;
    case VK_ERROR_TOO_MANY_OBJECTS:
        outStream << "VK_ERROR_TOO_MANY_OBJECTS";
        break;
    case VK_ERROR_FORMAT_NOT_SUPPORTED:
        outStream << "VK_ERROR_FORMAT_NOT_SUPPORTED";
        break;
    case VK_ERROR_FRAGMENTED_POOL:
        outStream << "VK_ERROR_FRAGMENTED_POOL";
        break;
    default:
        outStream << "Unknown VkResult: " << result;
    }
}