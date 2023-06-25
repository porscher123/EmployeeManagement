#ifndef CHANGEEMPLOYEE_H
#define CHANGEEMPLOYEE_H

#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>
#include "myPushButton.h"
#include <QTimer>
namespace Ui {
class ChangeEmployee;
}

class ChangeEmployee : public QDialog
{
    Q_OBJECT
signals:
    void back();
public:
    explicit ChangeEmployee(QWidget *parent = nullptr);
    void setBtn();
    void setLineEdit();
    void setCombBox();
    void init(int empId, QString name, QString sex, int age, QString phoneNumber,
              QString eduBkg, QString jobTitle, QString dept, QString salary);
    bool check();
    void clear();
    int empId, age;
    QString name, sex, phoneNumber, eduBkg, jobTitle, deptName, salary;
    MyPushButton *btnBack, *btnConfirm;
private:
    Ui::ChangeEmployee *ui;
};

#endif // CHANGEEMPLOYEE_H
