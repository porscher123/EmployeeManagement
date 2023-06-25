#include "adminWindow.h"


MainScene::MainScene(QWidget *parent)
    : QWidget{parent}
{
    this->set_windowBase();
    this->setComboBoxDept();
    this->setLabel();
    this->setLineEdit();
    this->set_btn();
    this->set_table();
    this->table->setRowCount(1);
    this->update_table();
}

void MainScene::set_windowBase()
{
    // 设置窗口大小
    this->setFixedSize(700,740);
    this->move(400, 40);
    //设置图标
    this->setWindowIcon(QIcon(":/1/resource/employeesIcon.png"));
    //设置标题
    this->setWindowTitle("三人行员工信息管理系统");

}
void MainScene::update_table() {
    QSqlQuery q1;
    QString sql1 = "SELECT count(1) FROM emp_viw;";
    q1.exec(sql1);
    q1.next();
    this->table->setRowCount(q1.value(0).toInt());
    int rowIdx = 0;
    QSqlQuery q;
    QString sql = "SELECT * FROM emp_viw;";
    if (q.exec(sql)) {
        qDebug() << "查询视图成功";
        while (q.next()) {
            table->setItem(rowIdx,0,new QTableWidgetItem(q.value(0).toString()));
            table->setItem(rowIdx,1,new QTableWidgetItem(q.value(1).toString()));
            table->setItem(rowIdx,2,new QTableWidgetItem(q.value(2).toString()));
            table->setItem(rowIdx,3,new QTableWidgetItem(q.value(3).toString()));
            table->setItem(rowIdx,4,new QTableWidgetItem(q.value(4).toString()));
            table->setItem(rowIdx,5,new QTableWidgetItem(q.value(5).toString()));
            table->setItem(rowIdx,6,new QTableWidgetItem(q.value(6).toString()));
            table->setItem(rowIdx,7,new QTableWidgetItem(q.value(7).toString()));
            table->setItem(rowIdx,8,new QTableWidgetItem(q.value(8).toString()));
            table->setItem(rowIdx,9,new QTableWidgetItem(q.value(9).toString()));
            rowIdx++;
        }
        table->update();
    } else {
        qDebug() << "false";
    }
}


void MainScene::search() {
    QSqlQuery q;
    QString name = this->lineEditName->text();
    QString lowSal = this->lineEditLowSal->text();
    QString HigSal = this->lineEditHighSal->text();
    QString deptName = this->combBoxDept->currentText();
    if (name.isEmpty()) name = "NULL";
    else name.push_front('\''), name.push_back('\'');
    if (lowSal.isEmpty()) lowSal = "99999999.99";
    if (HigSal.isEmpty()) HigSal = "0";
    if (this->combBoxDept->currentIndex() == -1) deptName = "NULL";
    else deptName.push_front('\''), deptName.push_back('\'');
    QString sql0 = QString("CALL query_employee_count(%1, %2, %3, %4);").arg(name).arg(lowSal).arg(HigSal).arg(deptName);
    q.exec(sql0);
    q.next();
    qDebug() << sql0;
    qDebug() << q.value(0).toInt();
    this->table->setRowCount(q.value(0).toInt());


    int rowIdx = 0;
    QString sql = QString("CALL query_employee(%1, %2, %3, %4);").arg(name).arg(lowSal).arg(HigSal).arg(deptName);
    if (q.exec(sql)) {
        while (q.next()) {
            table->setItem(rowIdx,0,new QTableWidgetItem(q.value(0).toString()));
            table->setItem(rowIdx,1,new QTableWidgetItem(q.value(1).toString()));
            table->setItem(rowIdx,2,new QTableWidgetItem(q.value(2).toString()));
            table->setItem(rowIdx,3,new QTableWidgetItem(q.value(3).toString()));
            table->setItem(rowIdx,4,new QTableWidgetItem(q.value(4).toString()));
            table->setItem(rowIdx,5,new QTableWidgetItem(q.value(5).toString()));
            table->setItem(rowIdx,6,new QTableWidgetItem(q.value(6).toString()));
            table->setItem(rowIdx,7,new QTableWidgetItem(q.value(7).toString()));
            table->setItem(rowIdx,8,new QTableWidgetItem(q.value(8).toString()));
            table->setItem(rowIdx,9,new QTableWidgetItem(q.value(9).toString()));
            rowIdx++;
        }
        table->update();
    }
}
void MainScene::set_btn()
{
    this->setBtnReset();
    this->setBtnQuery();
    this->setBtnSave();
    this->set_btnChange();
    this->set_btnAdd();
    this->set_btnBack();
    this->set_btnDelete();
}
void MainScene::set_btnBack()
{
    this->btn_back = new MyPushButton(":/1/resource/back1.png");
    this->btn_back->setParent(this);
    this->btn_back->move(60, this->height() - 60);

    connect(this->btn_back, &QPushButton::clicked, this, [=](){
        this->btn_back->zoom_leftRight();
        this->move(400, 40);
        QTimer::singleShot(280,this,[=](){

            emit this->back();   //给登录界面发送返回信号
        });
    });
}
void MainScene::setBtnSave() {
    this->btnSave = new MyPushButton(":/1/resource/saveBtn50.png");
    this->btnSave->setParent(this);
    this->btnSave->move(this->width() - 100, this->height() - 60);
    connect(this->btnSave, &QPushButton::clicked, this, [=](){
        this->btnSave->zoom_upDown();
        QSqlQuery q;
        QString sql = "COMMIT;";
        qDebug() << sql;
        if (q.exec(sql)) {
            qDebug() << "事务已提交";
            QMessageBox::information(this,"提示","本次操作已保存");

        }
    });

}
void MainScene::setBtnQuery() {
    this->btnQuery = new MyPushButton(":/1/resource/searchBtn2_50.png");
    this->btnQuery->setParent(this);
    this->btnQuery->move(this->width() / 3 * 2 + 150, 37);

    connect(this->btnQuery, &QPushButton::clicked, this, [=](){
        QString name = this->lineEditName->text();
        QString lowSal = this->lineEditLowSal->text();
        QString HigSal = this->lineEditHighSal->text();
        QString deptName = this->combBoxDept->currentText();
        if (name.isEmpty() && lowSal.isEmpty() && HigSal.isEmpty() && deptName.isEmpty()) return;
        this->btnQuery->zoom_upDown();
        QTimer::singleShot(320,this,[=](){
            this->search();
        });

    });

}
void MainScene::setBtnReset() {
    this->btnReset = new MyPushButton(":/1/resource/resetBtn50.png");
    this->btnReset->setParent(this);
    this->btnReset->move(20, 30);
    connect(this->btnReset, &QPushButton::clicked, this, [&](){
        QString name = this->lineEditName->text();
        QString lowSal = this->lineEditLowSal->text();
        QString HigSal = this->lineEditHighSal->text();
        QString deptName = this->combBoxDept->currentText();
        if (name.isEmpty() && lowSal.isEmpty() && HigSal.isEmpty() && deptName.isEmpty()) return;
        this->btnReset->zoom_upDown();
        this->clear();
        this->update_table();
        QTimer::singleShot(320,this,[=](){

        });

    });
}




//点击修改个人信息
void MainScene::set_btnChange()
{
    QFont font;
    font.setPixelSize(20);
    this->btn_change = new QPushButton(tr("修改员工信息"), this);
    this->btn_change->setFont(font);
//    this->btn_change->setFixedSize(60, 40);
    this->btn_change->setStyleSheet("QPushButton{color:black}"
                                   "QPushButton:hover{color:rgb(78,255,255)}"
                                   "QPushButton{background-color:rgb(255,192,225)}"
                                   "QPushButton{border:2px}"
                                   "QPushButton{border-radius:10px}"
                                   "QPushButton{padding:2px 4px}");
    this->btn_change->move(85, 12);
    this->window_change = new ChangeEmployee(this);
    connect(this->window_change, &ChangeEmployee::back, this, [&](){
        this->window_change->hide();
        this->show();
        this->update_table();
    });
    connect(window_change, &QDialog::rejected, this, [=]() {
        this->window_change->hide();
        this->show();
        this->update_table();
    });
    connect(this->btn_change, &QPushButton::clicked, this, [&](){

        int curRow = table->currentRow();
        if (curRow == -1) return;
        int empId = table->item(curRow, 0)->text().toInt();
        QString name = table->item(curRow, 1)->text();
        QString sex = table->item(curRow, 2)->text();
        int age = table->item(curRow, 3)->text().toInt();
        QString phoneNumber = table->item(curRow, 4)->text();
        QString eduBkg = table->item(curRow, 5)->text();
        QString jobTitle = table->item(curRow, 6)->text();
        QString deptName = table->item(curRow, 8)->text();
        QString salary= table->item(curRow, 9)->text();
        qDebug() << empId << " " << name << " " << sex
                 << age << " " << phoneNumber << " " << eduBkg << " " << jobTitle
                 << deptName << " " << salary;
//        this->window_change->clear();
        this->window_change->init(empId, name, sex, age, phoneNumber, eduBkg, jobTitle, deptName, salary);
        this->hide();
        this->window_change->show();
        window_change->setWindowTitle("强盛集团员工管理系统");
    });

}

//点击删除
void MainScene::set_btnDelete()
{
    QFont font;
    font.setPixelSize(20);
    this->btn_delete = new QPushButton(tr("删除员工信息"), this);
    this->btn_delete->setFont(font);
    this->btn_delete->setStyleSheet("QPushButton{color:black}"
                                   "QPushButton:hover{color:rgb(78,255,255)}"
                                   "QPushButton{background-color:rgb(255,192,225)}"
                                   "QPushButton{border:2px}"
                                   "QPushButton{border-radius:10px}"
                                   "QPushButton{padding:2px 4px}");
    this->btn_delete->move(this->width() / 3 + 57, 12);
    connect(this->btn_delete, &QPushButton::clicked, this, [&](){
        int rowIndex = table->currentRow();
//        qDebug() << rowIndex;
        if (rowIndex == -1) return;
        int curRow = table->currentRow();
        int emp_id = table->item(curRow, 0)->text().toInt();
        table->removeRow(rowIndex);
        qDebug() << emp_id;
        QSqlQuery q;
        QString sql = QString("DELETE FROM employee WHERE employee_id = %1;").arg(emp_id);
        qDebug() << sql;
        if (q.exec(sql)) {
            qDebug() << "删除成功";
        } else {
            qDebug() << "删除失败";
        }
    });

}


//点击添加资产内容
void MainScene::set_btnAdd()
{
    QFont font;
    font.setPixelSize(20);
    this->btn_add = new QPushButton(tr("添加新员工"), this);
    this->btn_add->setFont(font);
//    this->btn_add->setFixedSize(60, 40);
    this->btn_add->setStyleSheet("QPushButton{color:black}"
                                   "QPushButton:hover{color:rgb(78,255,255)}"
                                   "QPushButton{background-color:rgb(255,192,225)}"
                                   "QPushButton{border:2px}"
                                   "QPushButton{border-radius:10px}"
                                   "QPushButton{padding:2px 4px}");
    this->btn_add->move(this->width() / 3 + 248, 12);
    window_addEmployee = new AddEmployee(this);
    connect(window_addEmployee, &QDialog::rejected, this, [=]() {
        window_addEmployee->hide();
        this->show();
    });
    window_addEmployee->setWindowTitle("强盛集团员工管理系统");
    connect(this->btn_add, &QPushButton::clicked, this, [=](){
        this->window_addEmployee->clear();
        this->hide();
        window_addEmployee->show();

        //接受window_addasset信号，以调用getData槽函数接受传递的资产信息
        connect(window_addEmployee, &AddEmployee::back,this,[&](){

           window_addEmployee->hide();
           this->show();
        });
        connect(window_addEmployee, &AddEmployee::add_successfully,this,[&](){
            window_addEmployee->hide();

            this->update_table();
            this->show();

        });
    });
}
void MainScene::setComboBoxDept() {
    this->combBoxDept = new QComboBox(this);
    this->combBoxDept->setFixedSize(85, 27);
    this->combBoxDept->move(505, 55);
    QStringList qls;
    qls << "IT" << "行政部" << "人力资源部" << "市场部" << "会计部";
    this->combBoxDept->addItems(qls);
    this->combBoxDept->setCurrentIndex(-1);
}
void MainScene::setLineEdit() {
    int height = 55;
    this->lineEditName = new QLineEdit(this);
    this->lineEditName->setFixedSize(65, 27);
    this->lineEditName->move(140, height);

    QRegularExpression regx1 ("^\\d{1,8}(\\.\\d{1,2})?$");
    QValidator* validator1 = new QRegularExpressionValidator(regx1);
    this->lineEditLowSal = new QLineEdit(this);
    this->lineEditLowSal->setValidator(validator1);
    this->lineEditLowSal->setMaxLength(10);
    this->lineEditLowSal->setFixedSize(65, 27);
    this->lineEditLowSal->move(265, height);

    QFont font;
    font.setPixelSize(20);
    this->labelTo = new QLabel("~", this);
    this->labelTo->setFont(font);
    this->labelTo->move(265+65+5, height);

    this->lineEditHighSal = new QLineEdit(this);
    this->lineEditHighSal->setFixedSize(65, 27);
    this->lineEditHighSal->move(355, height);
    this->lineEditHighSal->setValidator(validator1);
    this->lineEditHighSal->setMaxLength(10);

}
void MainScene::clear() {
    this->lineEditName->clear();
    this->lineEditLowSal->clear();
    this->lineEditHighSal->clear();
    this->combBoxDept->setCurrentIndex(-1);
}
void MainScene::setLabel() {
    QFont font;
    font.setPixelSize(20);
    font.setBold(true);
    int height = 55;
    this->labelName = new QLabel("姓名:", this);
    this->labelName->setFont(font);
    this->labelName->move(85, height);

    this->labelSal = new QLabel("工资:", this);
    this->labelSal->setFont(font);
    this->labelSal->move(215, height);


    this->labelDept = new QLabel("部门:", this);
    this->labelDept->setFont(font);
    this->labelDept->move(445, height);


}



void MainScene::set_table()
{
    this->table = new QTableWidget(this);
    table->setColumnCount(10);
    QStringList header;
    header << "员工编号" << "姓名" << "性别" << "年龄"<< "电话号码" << "雇佣日期" << "学历" << "职称" << "部门" << "工资" ;
    table->setHorizontalHeaderLabels(header);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    table->move(0, 100);
    table->setFixedSize(this->width(), this->height() - 165);
    table->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);
    table->setRowHeight(0, 25);
    table->horizontalHeader()->setFont(QFont("宋体", 12));
    table->setSelectionMode(QAbstractItemView::SingleSelection);
}



void MainScene::paintEvent(QPaintEvent*)
{
    picture = ":/1/resource/mainBkg2.jpg";
    QPainter painter(this);
    QPixmap pixmap(picture);
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
}

MainScene::~MainScene()
{

}
