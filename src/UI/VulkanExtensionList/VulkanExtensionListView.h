#pragma once

#include "VulkanExtensionListModel.h"

class VulkanExtensionListView : public QListView {
    Q_OBJECT
public:
    explicit VulkanExtensionListView(QWidget *parent = nullptr);

private:
    VulkanExtensionListModel *m_model = nullptr;
};
