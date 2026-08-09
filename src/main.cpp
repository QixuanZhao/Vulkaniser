#include "mainwindow.h"
#include "UI/TrialVulkanWindow/TrialVulkanWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QVulkanWindow * vulkanWindow = new TrialVulkanWindow();
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
        VulkanUtility::print(result, std::cerr);
        return EXIT_FAILURE;
    }
    VulkanManager::instance().setInstance(vulkanInstance->vkInstance());
#endif
    vulkanWindow->setVulkanInstance(vulkanInstance);

    QWidget * container = QWidget::createWindowContainer(vulkanWindow);
    MainWindow mainWindow;
    mainWindow.setCentralWidget(container);

    mainWindow.resize(800, 600);
    mainWindow.show();

    return a.exec();
}
