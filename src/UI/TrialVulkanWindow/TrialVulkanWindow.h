#pragma once
#include <QVulkanWindow>
#include <QVulkanWindowRenderer>

class TrialVulkanRenderer: public QVulkanWindowRenderer
{
public:
    TrialVulkanRenderer(QVulkanWindow *window);
    ~TrialVulkanRenderer();

    void initResources() override;
    void initSwapChainResources() override;
    void releaseSwapChainResources() override;
    void releaseResources() override;

    void startNextFrame() override;
protected:
    QVulkanWindow * m_window;
    QVulkanDeviceFunctions * m_devFuncs;
    const VulkanManager& vulkanManager = VulkanManager::instance();
};

class TrialVulkanWindow : public QVulkanWindow
{
    Q_OBJECT
public:
    TrialVulkanWindow(QWindow *parent = nullptr);

    QVulkanWindowRenderer *createRenderer() override;

    ~TrialVulkanWindow();
protected:
    const VulkanManager& vulkanManager = VulkanManager::instance();
};