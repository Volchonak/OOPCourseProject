#ifndef ADDNEWABONEMENT_H
#define ADDNEWABONEMENT_H

#include <QDialog>
#include "SwimmingPoolSeasonTicket.h"

#define STYLESHEETERROR "QLineEdit{background-color:white;margin-right:3%;\
margin-top:5px;border-width:1px;border-style:solid;border-color:rgb(255, 0, 0);\
border-radius:10px;padding: 5px 9px;font: italic 12pt \"Times New Roman\";color:rgb(255, 0, 0);\
}QLineEdit:hover {border-bottom: 3px solid rgb(255, 0, 0);}"
#define STYLESHEETDEFAULT "QLineEdit{background-color:white;margin-right:3%;\
margin-top:5px;border-width:1px;border-style:solid;border-color:rgb(204, 204, 204);\
border-radius:10px;padding: 5px 9px;font: italic 12pt \"Times New Roman\";color:rgb(64, 65, 66);\
}QLineEdit:hover {border-bottom: 3px solid rgb(204, 204, 204);}"

namespace Ui {
class AddNewAbonement;
}

class AddNewAbonement : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewAbonement(SwimmingPoolSeasonTicket& season_ticket, QWidget *parent = nullptr);
    ~AddNewAbonement();

private slots:
    void on_LineEditLastName_textChanged();

    void on_LineEditFirstName_textChanged();

    void on_LineEditFathersName_textChanged();

    void on_LineEditDurationPerDay_textChanged();

    void on_LineEditVisitsPerMonth_textChanged();

    void on_LineEditEndDay_textChanged();

    void on_LineEditEndMonth_textChanged();

    void on_LineEditEndYear_textChanged();

    void on_PushButtonAddAbonement_clicked();

private:
    Ui::AddNewAbonement *ui;
    SwimmingPoolSeasonTicket& m_season_ticket;
};

#endif // ADDNEWABONEMENT_H
