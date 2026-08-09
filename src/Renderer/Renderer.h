#pragma once
#include <QVulkanWindowRenderer>

class Renderer: public QVulkanWindowRenderer
{
public:
    Renderer(QVulkanWindow *window);
    ~Renderer();

    void initResources() override;
    void initSwapChainResources() override;
    void releaseSwapChainResources() override;
    void releaseResources() override;

    void startNextFrame() override;
protected:
    QVulkanWindow * m_window;
    QVulkanDeviceFunctions * m_devFuncs;
    const VulkanManager& vulkanManager = VulkanManager::shared();
};