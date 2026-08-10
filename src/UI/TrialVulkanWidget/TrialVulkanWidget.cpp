#include "TrialVulkanWidget.h"

#include <QMessageBox>

TrialVulkanWidget::TrialVulkanWidget(QWidget *parent)
    : TrialVulkanWidget(new TrialVulkanWindow(), parent)
{
}

TrialVulkanWidget::TrialVulkanWidget(TrialVulkanWindow *window, QWidget *parent)
    : QWidget(parent)
    , m_window(window)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    QVulkanInstance * vulkanInstance = new QVulkanInstance();
    if (!vulkanInstance->create()) {
        VkResult result = vulkanInstance->errorCode();
        std::cerr << vk::to_string(vk::Result(result)) << std::endl;
        QMessageBox::critical(this, tr("Vulkan"), tr("Failed to create a Vulkan instance."));
        return;
    }

    VulkanManager::shared().setInstance(vulkanInstance->vkInstance());

    m_window->setVulkanInstance(vulkanInstance);
    m_container = QWidget::createWindowContainer(m_window, this);
    layout->addWidget(m_container);
}

TrialVulkanWidget::~TrialVulkanWidget()
{
    if (m_window) {
        m_window->deleteLater();
    }
}