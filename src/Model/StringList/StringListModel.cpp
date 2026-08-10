#include "StringListModel.h"

StringListModel::StringListModel(std::vector<QString>& data, QObject *parent)
    : QAbstractListModel(parent)
    , m_stringList(data)
{
}

int StringListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return static_cast<int>(m_stringList.size());
}

QVariant StringListModel::data(const QModelIndex &index, int role) const {
    const int row = index.row();
    if (row < 0 || row >= m_stringList.size()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole) {
        return m_stringList[row];
    } else return QVariant();
}