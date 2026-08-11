#pragma once

class PhysicalDeviceDetailList : public QAbstractItemModel {
    Q_OBJECT
public:
    PhysicalDeviceDetailList(QObject *parent = nullptr) : QAbstractItemModel(parent) {}

    QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const override {
        if (!hasIndex(row, column, parent)) return {};

        if (parent.isValid()) {
            if (const auto* pointer = static_cast<const PhysicalDeviceProperty*>(parent.constInternalPointer())->childAt(row).get()) {
                return createIndex(row, column, pointer);
            } else return {};
        } else {
            if (const auto* pointer = m_physicalDeviceProperties->childAt(row).get()) {
                return createIndex(row, column, pointer);
            } else return {};
        }
    }

    QModelIndex parent(const QModelIndex &index) const override {
        if (!index.isValid()) return {};

        const auto parentNode = static_cast<const PhysicalDeviceProperty*>(index.constInternalPointer())->parent();
        if (parentNode == nullptr || parentNode == m_physicalDeviceProperties) return {};

        const auto grandParentNode = parentNode->parent();
        if (grandParentNode == nullptr) return {};

        const int row = grandParentNode->childIndex(parentNode);
        if (row < 0) return {};

        return createIndex(row, 0, parentNode.get());
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        Q_UNUSED(parent);
        return 2;
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        if (!parent.isValid()) return m_physicalDeviceProperties->childCount();

        return static_cast<int>(static_cast<const PhysicalDeviceProperty*>(parent.constInternalPointer())->childCount());
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if (index.isValid()) {
            const auto* node = static_cast<const PhysicalDeviceProperty*>(index.constInternalPointer());
            if (role == Qt::DisplayRole) {
                return index.column() == 0 ? QString::fromStdString(node->name()) : QString::fromStdString(node->value());
            } else {
                return QVariant();
            }
        } else {
            return QVariant();
        }
    }
    
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            return section == 0 ? QString("Name") : QString("Value");
        }
        return QVariant();
    }
private:
    const std::shared_ptr<const PhysicalDeviceProperty> m_physicalDeviceProperties = vmShared.physicalDeviceProperty();
};