#include "VulkanExtensionListModel.h"

#include <QByteArray>

VulkanExtensionListModel::VulkanExtensionListModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_vm(VulkanManager::shared())
{
    initialize();
}

void VulkanExtensionListModel::initialize()
{
    if (!m_mutex.try_lock()) {
        return;
    }

    if (m_extensionProperties.empty()) {
        try {
            m_extensionProperties = m_vm.context().enumerateInstanceExtensionProperties();
        } catch (...) {
            m_extensionProperties.clear();
        }
    }

    m_mutex.unlock();
}

int VulkanExtensionListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return static_cast<int>(m_extensionProperties.size());
}

QVariant VulkanExtensionListModel::data(const QModelIndex &index, int role) const {
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    const int row = index.row();
    if (row < 0 || row >= static_cast<int>(m_extensionProperties.size())) {
        return QVariant();
    }

    const auto &extension = m_extensionProperties[row];
    QString result;
    
    for (char c : extension.extensionName) {
        if (c == '\0') break;
        result += c;
    }
    
    return result;
}