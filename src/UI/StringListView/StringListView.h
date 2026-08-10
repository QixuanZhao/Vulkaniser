#pragma once

class StringListView : public QListView {
    Q_OBJECT
public:
    explicit StringListView(QWidget *parent = nullptr);
    ~StringListView() override;
};
