#include "VulkanLayerListModel.h"

VulkanLayerListModel::VulkanLayerListModel(const std::vector<vk::LayerProperties>& layers, QObject *parent)
    : QAbstractListModel(parent)
    , m_layerProperties(layers)
{
}

int VulkanLayerListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return static_cast<int>(m_layerProperties.size());
}

QVariant VulkanLayerListModel::data(const QModelIndex &index, int role) const {
    const int row = index.row();
    if (row < 0 || row >= m_layerProperties.size()) {
        return QVariant();
    }

    const auto &layer = m_layerProperties[row];

    if (role == Qt::DisplayRole) {
        QString result;
        for (char c : layer.layerName) {
            if (c == '\0') break;
            result += c;
        }
        return result;
    } else if (role == Qt::ToolTipRole) {
        return QString("Version: %1").arg(layer.specVersion);
    } else return QVariant();
}