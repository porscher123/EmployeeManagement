#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QWidget>
#include <QIcon>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QComboBox>
#include <QMessageBox>
#include <QLabel>
#include <QFile>
#include <QFont>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDialog>
#include <QLineEdit>
#include "myPushButton.h"
#include "addEmployee.h"
#include "changeEmployee.h"
class AddEmployee;


class MainScene : public QWidget
{
    Q_OBJECT

public:
    explicit MainScene(QWidget *parent = nullptr);
    ~MainScene();

    void set_windowBase();
    void paintEvent(QPaintEvent*) override ;

    void set_btn();
    void set_label();
    void set_lineEdit();
    void set_table();

    void get_name(QString name);
    void get_position(QString position);
    void get_account(QString account);
    void update_table();
signals:
    void closed();

protected:
    void closeEvent(QCloseEvent *event) override
    {
        emit closed();
        QWidget::closeEvent(event);
    }
private:

    void set_btnAdd();
    void set_btnChange();
    void set_btnPrint();
    void set_btnBack();
    void set_btnDelete();


    QPushButton* btn_add;
    QPushButton* btn_save;
    QPushButton* btn_change;
    QPushButton* btn_delete;
    MyPushButton* btn_back;

    MyPushButton* btnQuery;
    void setBtnQuery();

    MyPushButton* btnReset;
    void setBtnReset();

    MyPushButton *btnSave;
    void setBtnSave();


    QTableWidget* table;
    //连接两个窗口
    AddEmployee* window_addEmployee;
    ChangeEmployee* window_change;

    QLabel *labelName, *labelDept, *labelSal, *labelTo;
    void setLabel();


    QLineEdit *lineEditName, *lineEditLowSal, *lineEditHighSal;
    void setLineEdit();

    QComboBox *combBoxDept;
    void setComboBoxDept();

    void clear();
    void search();
    QString picture;

//    PrintUI *printUI;
private slots:


signals:
    void info_changed();
    void back();
};

#endif // ADMINWINDOW_H
