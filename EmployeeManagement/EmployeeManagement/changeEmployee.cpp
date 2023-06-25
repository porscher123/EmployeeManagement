#include "changeEmployee.h"
#include "ui_changeEmployee.h"

ChangeEmployee::ChangeEmployee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeEmployee)
{
    this->move(480, 40);
    ui->setupUi(this);
    setBtn();
}
void ChangeEmployee::init(int empId, QString name, QString sex, int age,
    QString phoneNumber, QString eduBkg, QString jobTitle, QString dept, QString salary) {
    this->empId = empId;
    this->name = name;
    this->sex = sex;
    this->phoneNumber = phoneNumber;
    this->eduBkg = eduBkg;
    this->jobTitle = jobTitle;
    this->deptName = dept;
    this->salary = salary;
    setLineEdit();
    this->ui->comboBox_age->setCurrentText(QString::number(age));
    this->ui->comboBox_edubkg->setCurrentText(this->eduBkg);
    this->ui->comboBox_jobTitile->setCurrentText(this->jobTitle);
    this->ui->comboBox_jobTitile->setCurrentText(this->jobTitle);
    if (sex == "男") {
        this->ui->radioButton_man->setChecked(true);
    } else {
        this->ui->radioButton_woman->setChecked(true);
    }
}
bool ChangeEmployee::check() {

    bool isMan = this->ui->radioButton_man->isChecked();
    bool isWoman = this->ui->radioButton_woman->isChecked();
    this->name = this->ui->lineEdit_name->text();
    if (isMan && !isWoman) sex = "男";
    else sex = "女";
    this->age = this->ui->comboBox_age->currentText().toInt();
    this->phoneNumber = this->ui->lineEdit_phonenumber->text();
    this->eduBkg = this->ui->comboBox_edubkg->currentText();
    this->jobTitle = this->ui->comboBox_jobTitile->currentText();
    this->deptName = this->ui->comboBox_dept->currentText();
    this->salary = this->ui->lineEdit_salary->text();





    if (!isWoman && !isMan) {
        QMessageBox::information(this,"提示","请选择性别");
    } else if (name.isEmpty()) {
        QMessageBox::information(this,"提示","请输入姓名");
    } else if (this->ui->comboBox_age->currentIndex() == -1) {
        QMessageBox::information(this,"提示","请选择年龄");
    } else if (name.isEmpty()) {
        QMessageBox::information(this,"提示","请输入姓名");
    } else if (phoneNumber.isEmpty()) {
        QMessageBox::information(this,"提示","请输入手机号");
    } else if (phoneNumber.size() < 11) {
        QMessageBox::information(this,"提示","请输入有效手机号");
    } else if (deptName.isEmpty()) {
        QMessageBox::information(this,"提示","请选择部门");
    } else if (jobTitle.isEmpty()) {
        QMessageBox::information(this,"提示","请选择职称");
    } else if (eduBkg.isEmpty()) {
        QMessageBox::information(this,"提示","请选择学历");
    } else if (this->ui->lineEdit_salary->text().isEmpty()) {
        QMessageBox::information(this,"提示","请输入工资");
    } else {
        return true;
    }
    return false;
}
void ChangeEmployee::setBtn() {
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
    connect(this->btnConfirm, &QPushButton::clicked, this, [&](){
        if (check()) {
            int dept_id;
            QSqlQuery q1;
            q1.exec(QString("SELECT * FROM department WHERE department_name = '%1';").arg(deptName));
            q1.next();
            dept_id = q1.value(0).toInt();

            QSqlQuery update;
            QString sql = QString("CALL update_employee(%1,'%2','%3',%4,'%5','%6','%7',%8, %9);")
                               .arg(empId).arg(name).arg(sex).arg(age).
                          arg(phoneNumber).arg(eduBkg).arg(jobTitle).arg(dept_id).arg(salary);
            qDebug() << sql;
            if (update.exec(sql)) {
                qDebug() << "修改成功";
                QMessageBox::information(this,"提示","修改成功");

                emit this->back();
            } else {
                qDebug() << "修改失败";
            }
        }

    });
}
void ChangeEmployee::setLineEdit() {
    this->ui->lineEdit_name->setMaxLength(10);
    this->ui->lineEdit_name->setText(this->name);
    QRegularExpression regx1 ("^\\d{1,8}(\\.\\d{1,2})?$");
    QValidator* validator1 = new QRegularExpressionValidator(regx1);
    this->ui->lineEdit_salary->setValidator(validator1);
    this->ui->lineEdit_salary->setMaxLength(12);
    this->ui->lineEdit_salary->setText(this->salary);


    QRegularExpression regx2 ("^\\d{11}$");
    QValidator* validator2 = new QRegularExpressionValidator(regx2);
    this->ui->lineEdit_phonenumber->setText(this->phoneNumber);
    this->ui->lineEdit_phonenumber->setValidator(validator2);
}
void ChangeEmployee::setCombBox() {
    for (int i = 18; i <= 80; i++) {
        this->ui->comboBox_age->addItem(QString::number(i));
    }
    this->ui->comboBox_age->setCurrentText(QString::number(this->age));

    QStringList qls;
    qls << "专科" << "本科" << "研究生";
    this->ui->comboBox_edubkg->addItems(qls);
    this->ui->comboBox_edubkg->setCurrentText(this->eduBkg);
    qls.clear();

    qls << "普通员工" << "组长" << "经理" << "CEO" << "董事长";
    this->ui->comboBox_jobTitile->addItems(qls);
    this->ui->comboBox_jobTitile->setCurrentText(this->jobTitle);
    qls.clear();

    qls << "IT" << "行政部" << "人力资源部" << "市场部" << "会计部";
    this->ui->comboBox_dept->addItems(qls);
    this->ui->comboBox_dept->setCurrentText(this->deptName);
}
