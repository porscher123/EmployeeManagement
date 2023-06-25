#include "addEmployee.h"
#include "ui_addEmployee.h"
#include <QDebug>
AddEmployee::AddEmployee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addasset)
{
    this->move(480, 40);
    ui->setupUi(this);
    this->set_combBox();
    this->set_lineEdit();
    this->setBtn();
}
void AddEmployee::set_combBox() {
    for (int i = 18; i <= 80; i++) {
        this->ui->comboBox_age->addItem(QString::number(i));
    }
    this->ui->comboBox_age->setCurrentIndex(-1);

    QStringList qls;
    qls << "专科" << "本科" << "研究生";
    this->ui->comboBox_edubkg->addItems(qls);
    this->ui->comboBox_edubkg->setCurrentIndex(-1);
    qls.clear();

    qls << "普通员工" << "组长" << "经理" << "CEO" << "董事长";
    this->ui->comboBox_jobTitile->addItems(qls);
    this->ui->comboBox_jobTitile->setCurrentIndex(-1);
    qls.clear();

    qls << "IT" << "行政部" << "人力资源部" << "市场部" << "会计部";
    this->ui->comboBox_dept->addItems(qls);
    this->ui->comboBox_dept->setCurrentIndex(-1);
}
void AddEmployee::set_lineEdit() {

    this->ui->lineEdit_name->setMaxLength(10);

    QRegularExpression regx1 ("^\\d{1,8}(\\.\\d{1,2})?$");
    QValidator* validator1 = new QRegularExpressionValidator(regx1);
    this->ui->lineEdit_salary->setValidator(validator1);
    this->ui->lineEdit_salary->setMaxLength(10);


    QRegularExpression regx2 ("^\\d{11}$");
    QValidator* validator2 = new QRegularExpressionValidator(regx2);
    this->ui->lineEdit_phonenumber->setValidator(validator2);
}


void AddEmployee::clear() {
    this->ui->radioButton_3->setChecked(true);
    this->ui->lineEdit_name->clear();
    this->ui->lineEdit_phonenumber->clear();
    this->ui->lineEdit_salary->clear();
    this->ui->comboBox_age->setCurrentIndex(-1);
    this->ui->comboBox_dept->setCurrentIndex(-1);
    this->ui->comboBox_edubkg->setCurrentIndex(-1);
    this->ui->comboBox_jobTitile->setCurrentIndex(-1);
}
void AddEmployee::setBtn()
{
    this->ui->radioButton_3->setVisible(false);
    btnBack = new MyPushButton(":/1/resource/back1.png");
    btnBack->setParent(this);
    connect(btnBack, &QPushButton::clicked, this, [&](){
        this->btnBack->zoom_leftRight();
        QTimer::singleShot(320,this,[=](){
            emit this->back();
        });
    });
    btnBack->move(35, this->height() - 85);


    btnConfirm = new MyPushButton(":/1/resource/confirm.png");
    btnConfirm->setParent(this);
    btnConfirm->move(this->width() / 2 - 30, this->height() - 90);
    connect(btnConfirm, &QPushButton::clicked, this, [&](){
        this->btnConfirm->zoom_upDown();
        if (!check()) return;
        QTimer::singleShot(320,this,[=](){
            int dept_id;
            QSqlQuery q1;
            QString sql = QString("SELECT * FROM department WHERE department_name = '%1';").arg(dept_name);
            q1.exec(sql);
            q1.next();
            dept_id = q1.value(0).toInt();
            QSqlQuery insert;
            sql = QString("CALL insert_employee('%1','%2',%3,'%4','%5','%6',%7,%8);")
                              .arg(name).arg(sex).arg(age).arg(phonenumber).
                          arg(edubkg).arg(jobtitle).arg(dept_id).arg(salary);
            qDebug() << sql;
            if (insert.exec(sql)) {
                qDebug() << "ok";
                QMessageBox::information(this,"提示","添加成功");

                emit this->add_successfully();
            } else {
                qDebug() << "false";
            }
            clear();
        });
    });
}

bool AddEmployee::check() {

    bool isMan = this->ui->radioButton->isChecked();
    bool isWoman = this->ui->radioButton_2->isChecked();
    this->name = this->ui->lineEdit_name->text();
    if (isMan && !isWoman) sex = "男";
    else sex = "女";
    this->age = this->ui->comboBox_age->currentText().toInt();
    this->phonenumber = this->ui->lineEdit_phonenumber->text();
    this->edubkg = this->ui->comboBox_edubkg->currentText();
    this->jobtitle = this->ui->comboBox_jobTitile->currentText();
    this->dept_name = this->ui->comboBox_dept->currentText();
    this->salary = this->ui->lineEdit_salary->text().toDouble();





    if (!isWoman && !isMan) {
        QMessageBox::information(this,"提示","请选择性别");
    } else if (name.isEmpty()) {
        QMessageBox::information(this,"提示","请输入姓名");
    } else if (this->ui->comboBox_age->currentIndex() == -1) {
        QMessageBox::information(this,"提示","请选择年龄");
    } else if (name.isEmpty()) {
        QMessageBox::information(this,"提示","请输入姓名");
    } else if (phonenumber.isEmpty()) {
        QMessageBox::information(this,"提示","请输入手机号");
    } else if (phonenumber.size() < 11) {
        QMessageBox::information(this,"提示","请输入有效手机号");
    } else if (dept_name.isEmpty()) {
        QMessageBox::information(this,"提示","请选择部门");
    } else if (jobtitle.isEmpty()) {
        QMessageBox::information(this,"提示","请选择职称");
    } else if (edubkg.isEmpty()) {
        QMessageBox::information(this,"提示","请选择学历");
    } else if (this->ui->lineEdit_salary->text().isEmpty()) {
        QMessageBox::information(this,"提示","请输入工资");
    } else {
        return true;
    }
    return false;
}
void AddEmployee::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pixmap(":/1/resource/addasset.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
}

