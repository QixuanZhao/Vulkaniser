#pragma once

class VulkanExtensionListModel : public QAbstractListModel {
    Q_OBJECT
public:
    explicit VulkanExtensionListModel(const std::vector<vk::ExtensionProperties>& extensions, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    std::vector<vk::ExtensionProperties> m_extensionProperties;
};