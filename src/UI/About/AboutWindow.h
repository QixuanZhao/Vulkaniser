#pragma once
#include "Model/VulkanExtensionList/VulkanExtensionListModel.h"
#include "Model/VulkanLayerList/VulkanLayerListModel.h"
#include "Model/PhysicalDeviceList.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
    class AboutWindow;
}
QT_END_NAMESPACE

class AboutWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AboutWindow(QWidget *parent = nullptr);
    ~AboutWindow();

private:
    Ui::AboutWindow *ui;
    VulkanExtensionListModel m_extensionModel;
    VulkanLayerListModel m_layerModel;
    PhysicalDeviceList m_physicalDeviceModel;
};