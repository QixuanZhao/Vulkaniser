#pragma once

class VulkanUtility
{
public:
    static void print(VkResult result, std::ostream &outStream = std::cout);
};