#include "AboutWindow.h"
#include "ui_AboutWindow.h"

AboutWindow::AboutWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AboutWindow)
    , m_extensionModel(VulkanManager::shared().context().enumerateInstanceExtensionProperties(), this)
    , m_layerModel(VulkanManager::shared().context().enumerateInstanceLayerProperties(), this)
    , m_physicalDeviceModel(this)
{
    ui->setupUi(this);
    ui->vkExtList->setModel(&m_extensionModel);
    ui->vkLayerList->setModel(&m_layerModel);
    ui->vkPDeviceTree->setModel(&m_physicalDeviceModel);
}

AboutWindow::~AboutWindow()
{
    delete ui;
}
