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
    ~OperatingWindow();


private slots:
    void on_PushButtonAddNew_clicked();

    void on_PushButtonDeleteAbonemet_clicked();

    void on_PushButtonSaveDataToFile_clicked();

    void on_PushButtonFIndAdditionalServices_clicked();

    void on_PushButtonSaveAdditionalServices_clicked();
    
    void on_PushButtonLessThanMonthDurationAndHasWaterpark_clicked();

    void on_PushButtonMaxVisitsPerMonthAndFamily_clicked();

    void on_PushButtonFindMaxAdditionalServicesAndMinDurationPerDay_clicked();

    void on_PushButtonFindByName_clicked();

    void on_PushButtonFindByDuration_clicked();

    void on_PushButtonfindByVisits_clicked();

    void on_centralwidget_customContextMenuRequested();

    void on_actionSave_triggered();

    void on_actionUpload_table_triggered();

    void on_actionInfo_triggered();

private:
    void CheckTableOutput() const;
    void HasData() const;
    void ReadDataFromFile();
    void SaveDataToFile() const;
    void UpdateTable();
    void UpdateTable(const SwimmingPoolSeasonTicket& season_ticket, const int row);
    void setToolTips();

    Ui::OperatingWindow *ui;
    std::list<SwimmingPoolSeasonTicket> m_season_tickets;
    const int DEFAULT_ROW_COUNT= 0;
    const int DEFAULT_COLUMN_COUNT = 7;
    const std::string FILE_NAME = "waterpark.dat";
   // bool can_be_operated;
};


#endif // OPERATINGWINDOW_H
