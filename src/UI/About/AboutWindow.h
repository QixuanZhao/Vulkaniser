#pragma once
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
    class AboutWindow;
}
QT_END_NAMESPACE

class AboutWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AboutWindow(QWidget *parent = nullptr);
    ~AboutWindow();

private:
    Ui::AboutWindow *ui;
};