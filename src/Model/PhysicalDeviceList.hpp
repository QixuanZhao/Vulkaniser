#pragma once

class PhysicalDeviceList : public QAbstractListModel {
    Q_OBJECT
public:
    PhysicalDeviceList(QObject *parent = nullptr) : QAbstractListModel(parent) {};

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        Q_UNUSED(parent);
        const VulkanManager &vm = VulkanManager::shared();
        return static_cast<int>(vm.physicalDevices().size());
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        const VulkanManager &vm = VulkanManager::shared();
        const int row = index.row();
        if (row < 0 || row >= vm.physicalDevices().size()) {
            return QVariant();
        }

        if (role == Qt::DisplayRole) {
            return QString("Physical Device %1").arg(row);
        } else return QVariant();
    }
};