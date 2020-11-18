#ifndef OPERATINGWINDOW_H
#define OPERATINGWINDOW_H

#include <QMainWindow>

namespace Ui {
class OperatingWindow;
}

class OperatingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit OperatingWindow(QWidget *parent = nullptr);
    ~OperatingWindow();

private slots:
    void on_PushButtonAddNew_clicked();

private:
    Ui::OperatingWindow *ui;
};

#endif // OPERATINGWINDOW_H
