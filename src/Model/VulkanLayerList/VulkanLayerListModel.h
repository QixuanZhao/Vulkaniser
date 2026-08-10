#pragma once

class VulkanLayerListModel : public QAbstractListModel {
    Q_OBJECT
public:
    explicit VulkanLayerListModel(const std::vector<vk::LayerProperties>& layers, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    
private:
    std::vector<vk::LayerProperties> m_layerProperties;
};