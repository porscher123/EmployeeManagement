#include "login.h"

Login::Login(QWidget *parent)
    : QWidget(parent)
{
    this->set_windowBase();
    this->set_adminWindow();
    this->set_btn();
    this->set_label();
    this->set_lineEdit();

}
// 设置窗体基础
void Login::set_windowBase()
{
    this->setFixedSize(400,325);
    this->move(560, 140);
    this->setWindowIcon(QIcon(":/1/resource/employeesIcon.png"));
    this->setWindowTitle("三人行员工管理系统");

}
void Login::set_btn()
{
    this->set_btnLogin();
//    this->set_btnSignIn();
    this->set_btnEye();
}
void Login::set_btnLogin()
{
    btn_login = new MyPushButton(":/1/resource/loginBtn150.png");
    btn_login->setParent(this);
    btn_login->move(this->width()*0.5 - btn_login->width()*0.5, this->height()*0.8);
    btn_login->setFocus();
    btn_login->setDefault(true);
    // 连接登录按钮的点击事件
    connect(this->btn_login, &MyPushButton::clicked, this, [=](){
        QString username = this->lineEdit_account->text();
        QString password = this->lineEdit_password->text();
        if(username.isEmpty()){
            QMessageBox::information(this,"提示","请输入用户名");
        } else if(password.isEmpty()) {
            QMessageBox::information(this,"提示","请输入密码");
        } else {

            this->btn_login->zoom_upDown();
            QTimer::singleShot(320,this,[=](){
                QSqlQuery query;
                QString sql = QString("SELECT check_login('%1', '%2');").arg(username).arg(password);
                qDebug() << sql;
                query.exec(sql);
                if (query.next()) {
                    if (query.value(0).toBool() == 1) {
                        qDebug() << "登录成功";
                        this->hide();
                        addmin_window->show();

                        QSqlQuery query;
                        sql = "START TRANSACTION;";
                        qDebug() << sql;
                        if (query.exec(sql)) {
                            qDebug() << "开启事务成功";

                        }
                    } else {
                        QMessageBox::information(this,"提示","用户名或密码不正确");
                    }
                }

            });

        }
    });
}

//密码可视按钮
void Login::set_btnEye()
{
    btnEyeClicked = false;

    btn_eye = new MyPushButton(this->eye_path2);
    btn_eye->setParent(this);
    btn_eye->move(330, 157);
    connect(this->btn_eye, &MyPushButton::clicked, this, [=](){   //点击后显示已输入的密码
        if(this->btnEyeClicked) {
            this->btn_eye->setIcon(QIcon(this->eye_path2));
            lineEdit_password->setEchoMode(QLineEdit::Password);//显示掩码字符
            btnEyeClicked = false;
        } else {//false
            lineEdit_password->setEchoMode(QLineEdit::Normal);//显示输入的字符
            this->btn_eye->setIcon(QIcon(this->eye_path1));
            btnEyeClicked = true;
        }
    });
}

//主界面“注册”按钮


void Login::set_label()
{
    this->set_labelAccount();
    this->set_labelPassword();
}
void Login::set_labelAccount()
{
    QFont font;
    font.setPixelSize(18);
    font.setBold(true);

    this->label_account = new QLabel(tr("username : "), this);
    this->label_account->setFont(font);
    this->label_account->move(80, 115);

    this->label_account_pix = new QLabel(this);
    this->label_account_pix->setPixmap(QPixmap(":/1/resource/user30.png"));
    this->label_account_pix->move(30, 108);
}
void Login::set_labelPassword()
{
    QFont font;
    font.setPixelSize(18);
    font.setBold(true);
    this->label_password = new QLabel(tr("password : "), this);
    this->label_password->setFont(font);
    this->label_password->move(80, 160);

    this->label_password_pix = new QLabel(this);
    this->label_password_pix->setPixmap(QPixmap(":/1/resource/password30.png"));
    this->label_password_pix->move(30, 158);
}

void Login::set_lineEdit()
{
    this->set_lineEditAccount();
    this->set_lineEditPassword();
}
void Login::set_lineEditAccount()
{
    this->lineEdit_account = new QLineEdit(this);

    this->lineEdit_account->setFixedHeight(this->label_account->height());
    this->lineEdit_account->setPlaceholderText(tr("input username"));
    this->lineEdit_account->move(190, 115);

}

void Login::set_lineEditPassword()
{
    this->lineEdit_password = new QLineEdit(this);
    this->lineEdit_password->setFixedHeight(this->label_password->height());
    this->lineEdit_password->setEchoMode(QLineEdit::Password);
    this->lineEdit_password->setPlaceholderText(tr("input password"));
    this->lineEdit_password->move(190, 155);

    connect(this->lineEdit_password, &QLineEdit::returnPressed, this->btn_login, &QPushButton::click);
}




void Login::set_adminWindow()
{
    this->addmin_window = new MainScene;
    connect(addmin_window, &MainScene::back, this, [=](){
        lineEdit_account->clear();
        lineEdit_password->clear();
        addmin_window->hide();
        QSqlQuery q;
        QString sql = "ROLLBACK;";
        qDebug() << sql;
        if (q.exec(sql)) {
            qDebug() << "事务已回滚";
            this->addmin_window->update_table();

        }
        this->show();
    });
    connect(this->addmin_window, &MainScene::closed, this, [=]() {
        lineEdit_account->clear();
        lineEdit_password->clear();
        addmin_window->hide();
        this->show();
        QSqlQuery q;
        QString sql = "ROLLBACK;";
        qDebug() << sql;
        if (q.exec(sql)) {
            qDebug() << "事务已回滚";
            this->addmin_window->update_table();

        }
    });
}


// 给背景初始化
void Login::paintEvent(QPaintEvent*)
{
    QPalette palette(this->palette());
    palette.setColor(QPalette::Window, Qt::white);
    this->setPalette(palette);
    QPainter painter(this);
    QPixmap pixmap(":/1/resource/loginBkg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(),pixmap);
    painter.setOpacity(0.4);
}

Login::~Login()
{
}

