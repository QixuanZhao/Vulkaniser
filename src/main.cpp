#include "UI/TrialVulkanWindow/TrialVulkanWindow.h"
#include <QApplication>
#include <QVulkanWindow>
#include <QVulkanInstance>
#include <QWidget>
#include "mainwindow.h"
#include <vulkan/vulkan.h>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QVulkanWindow * vulkanWindow = new TrialVulkanWindow();
    QVulkanInstance * vulkanInstance = new QVulkanInstance();
    if (vulkanInstance->create()) {
        vulkanWindow->setVulkanInstance(vulkanInstance);
    }

    QWidget *container = QWidget::createWindowContainer(vulkanWindow);
    container->setMinimumSize(800, 600);

    MainWindow mainWindow;
    mainWindow.setCentralWidget(container);

    mainWindow.resize(800, 600);
    mainWindow.show();

    return a.exec();
}
