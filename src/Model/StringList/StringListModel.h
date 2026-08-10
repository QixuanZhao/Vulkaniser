#pragma once
#include <QAbstractListModel>

class StringListModel : public QAbstractListModel {
    Q_OBJECT
public:
    explicit StringListModel(std::vector<QString>& data, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    std::vector<QString>& m_stringList;
};