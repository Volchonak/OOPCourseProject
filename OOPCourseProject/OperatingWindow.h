#ifndef OPERATINGWINDOW_H
#define OPERATINGWINDOW_H

#include <QMainWindow>
#include <vector>
#include <list>
#include "SwimmingPoolSeasonTicket.h"


namespace Ui {
class OperatingWindow;
}

class OperatingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit OperatingWindow(const bool read_from_file, QWidget *parent = nullptr);
    void UpdateTable();
    ~OperatingWindow();


private slots:
    void on_PushButtonAddNew_clicked();

    void on_PushButtonFIndAbonement_clicked();

    void on_PushButtonDeleteAbonemet_clicked();

    void on_PushButtonSaveDataToFile_clicked();

private:
    void ReadDataFromFile();
    void SaveDataToFile() const;

    Ui::OperatingWindow *ui;
    std::list<SwimmingPoolSeasonTicket> m_season_tickets;
    const int DEFAULT_ROW_COUNT= 0;
    const int DEFAULT_COLUMN_COUNT = 7;
    const std::string FILE_NAME = "waterpark.dat";
};


#endif // OPERATINGWINDOW_H
