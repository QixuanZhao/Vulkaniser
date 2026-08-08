#include "UI/TrialVulkanWindow/TrialVulkanWindow.h"
#include <QApplication>
#include <QVulkanWindow>
#include <QVulkanInstance>
#include <QWidget>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QVulkanWindow * vulkanWindow = new TrialVulkanWindow();
    QVulkanInstance * vulkanInstance = new QVulkanInstance();
#if defined(Q_OS_MACOS) || defined(Q_OS_DARWIN)
    vulkanInstance->setFlags(QVulkanInstance::Flags(VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR));
#endif
    if (vulkanInstance->create()) {
        vulkanWindow->setVulkanInstance(vulkanInstance);
    }

    QWidget *container = QWidget::createWindowContainer(vulkanWindow);

    MainWindow mainWindow;
    mainWindow.setCentralWidget(container);

    mainWindow.resize(800, 600);
    mainWindow.show();

    return a.exec();
}
