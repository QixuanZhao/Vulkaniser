#include "TrialVulkanWidget.h"

#include <QVBoxLayout>
#include <QSizePolicy>
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
#if CREATE_VULKAN_MANUALLY
    VulkanManager::instance().initialize();
    vulkanInstance->setVkInstance(*(VulkanManager::instance().getVkInstance()));
#else
#if defined(Q_OS_MACOS) || defined(Q_OS_DARWIN)
    vulkanInstance->setFlags(QVulkanInstance::Flags(VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR));
#endif
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
#endif
}

TrialVulkanWidget::~TrialVulkanWidget()
{
    if (m_window) {
        m_window->deleteLater();
    }
}