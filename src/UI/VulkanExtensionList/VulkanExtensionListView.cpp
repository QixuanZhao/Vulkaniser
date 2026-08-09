#include "VulkanExtensionListView.h"

VulkanExtensionListView::VulkanExtensionListView(QWidget *parent)
    : QListView(parent)
{
    m_model = new VulkanExtensionListModel(this);
    setModel(m_model);
}