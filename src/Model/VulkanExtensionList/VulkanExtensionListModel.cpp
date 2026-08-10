#include "VulkanExtensionListModel.h"

VulkanExtensionListModel::VulkanExtensionListModel(
    const std::vector<vk::ExtensionProperties>& extensions, 
    QObject *parent
) : QAbstractListModel(parent), 
    m_extensionProperties(extensions)
{
}

int VulkanExtensionListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return static_cast<int>(m_extensionProperties.size());
}

QVariant VulkanExtensionListModel::data(const QModelIndex &index, int role) const {
    const int row = index.row();
    if (row < 0 || row >= m_extensionProperties.size()) {
        return QVariant();
    }

    const auto &extension = m_extensionProperties[row];

    if (role == Qt::DisplayRole) {
        QString result;
        for (char c : extension.extensionName) {
            if (c == '\0') break;
            result += c;
        }
        
        return result;
    } else if (role == Qt::ToolTipRole) {
        return QString("Version: %1").arg(extension.specVersion);
    } else return QVariant();
}