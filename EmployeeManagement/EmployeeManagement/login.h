#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QString>
#include <QMessageBox>
#include <QIcon>
#include <QFile>
#include <QVBoxLayout>
#include <QTextStream>
#include <QTimer>
#include <QAction>
#include <QPainter>
#include <QPixmap>
#include <QMainWindow>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QSqlQuery>
#include "myPushButton.h"
#include "adminWindow.h"





class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

    void paintEvent(QPaintEvent*);   //绘图事件,设置背景
    void set_windowBase();    // 初始化主界面（登录后的首个界面）
    void set_adminWindow();
    void set_employeeWindow();
    void set_lineEdit();
    void set_label();
    void set_btn();


private:
    QLabel* label_coopername;
    QString eye_path1 = ":/1/resource/eye27.png";
    QString eye_path2 = ":/1/resource/eyeHiden27.png";
    QString backgroud1 = ":/1/resource/p3.jpg";
    void set_lineEditAccount();
    void set_lineEditPassword();
    void set_lineEditSearch();

    void set_btnLogin();
    void set_btnEye();
    void set_btnSignIn();

    void set_labelAccount();
    void set_labelPassword();
    void set_labelCoopername();


private:
    bool btnEyeClicked;

    //  按钮
    MyPushButton* btn_login;
    MyPushButton* btn_eye;
    QPushButton* btn_signIn;
    MyPushButton* btn_search;

    // 信息提示相关
    QMessageBox* box;

    // 登录部分的标签和输入框
    QLineEdit* lineEdit_account;
    QLabel* label_account_pix;
    QLabel* label_account;
    QLineEdit* lineEdit_password;
    QLabel* label_password;
    QLabel* label_password_pix;
    QLineEdit* lineEdit_search;


    // 此界面连接的两个窗口
    MainScene* addmin_window;
//    SignIn* window_signIn; // 注册界面


};

#endif // DIALOG_H
