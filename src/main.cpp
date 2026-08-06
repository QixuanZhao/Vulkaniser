#include <QApplication>
#include "mainwindow.h"
#include <vulkan/vulkan.h>
#include <iostream>

int main(int argc, char *argv[])
{
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::cout << "Available Vulkan extensions: " << extensionCount << std::endl;

    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
