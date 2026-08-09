#pragma once

#include <QAbstractListModel>

class VulkanExtensionListModel : public QAbstractListModel {
    Q_OBJECT
public:
    explicit VulkanExtensionListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    void initialize();

    VulkanManager &m_vm;
    std::vector<vk::ExtensionProperties> m_extensionProperties;
    std::mutex m_mutex;
};