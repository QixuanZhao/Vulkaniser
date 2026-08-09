#pragma once
#include <QVulkanWindow>

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