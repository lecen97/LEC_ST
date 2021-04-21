/*模态与非模态：
    Qt 支持模态对话框和非模态对话框。
    模态与非模态的实现：

	使用QDialog::exec()实现应用程序级别的模态对话框
	使用QDialog::open()实现窗口级别的模态对话框
	使用QDialog::show()实现非模态对话框。

	应用程序级别的模态
    当该种模态的对话框出现时，用户必须首先对对话框进行交互，直到关闭对话框，然后才能访问程序中其他的窗口。

    窗口级别的模态
    该模态仅仅阻塞与对话框关联的窗口，但是依然允许用户与程序中其它窗口交互。窗口级别的模态尤其适用于多窗口模式。
    一般默认是应用程序级别的模态。

    注意，如果widget是建立在栈上的，show()函数返回，函数结束，widget超出作用域被析构，对话框会消失。
    建立到堆上可以避免这个问题。建立到堆上需要注意内存泄漏问题，如果对内存占用有严格限制的话，当我们将主窗口作为parent时，
    主窗口不关闭，子窗口就不会被销毁，所以会一直占用内存。在这种情景下，我们可以设置dialog的WindowAttribute。
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "log_on.h"
#include "ui_log_on.h"

#include <QEvent>
#include <QWheelEvent>
#include <QDebug>
#include <QTabBar>
#include <QAction>
#include <QString>
#include <QSqlDatabase>
#include <QStringList>

//构造函数初始化列表以一个冒号开始，接着是以逗号分隔的数据成员列表，每个数据成员后面跟一个放在括号中的初始化式
MainWindow::MainWindow(QWidget *parent)//MainWindow的构造函数
    : QMainWindow(parent)//MainWindow继承的父类构造函数的初始化列表操作（析构和构造无法继承）
    , ui(new Ui::MainWindow)//MainWindow成员初始化，ui=new Ui::MainWindow
{
    MainWindow::ChuShiHua ();
    MainWindow::TcpFunction();
}

//初始化函数
void MainWindow::ChuShiHua ()
{
    ui->setupUi(this);
    this->setWindowTitle("LEC Selection Tool");
    ui->widget_6_pictrue->installEventFilter(this);
    ui->label_8_shrink_1->installEventFilter(this);
    ui->label_8_shrink_2->installEventFilter(this);
    ui->label_8_shrink_3->installEventFilter(this);
    ui->tabWidget_5_newStruct->setTabEnabled(1,false);    
    QAction *searchAction = new QAction(this);
    searchAction->setIcon(QIcon(":/new/prefix_icon/icon/search1.png"));
    ui->lineEdit_3_sourch->addAction(searchAction,QLineEdit::TrailingPosition);
    ui->lineEdit_9_sourch->addAction(searchAction,QLineEdit::TrailingPosition);
    ui->lineEdit_3_sourch->addAction(searchAction,QLineEdit::TrailingPosition);
    ui->lineEdit_9_sourch->addAction(searchAction,QLineEdit::TrailingPosition);
}

void MainWindow::TcpFunction()
{
    tcpserver = new QTcpServer(this);
    int num_port = 8888;
    tcpserver->listen(QHostAddress::Any,num_port);

    connect(tcpserver,&QTcpServer::newConnection,
            [=]()
            {
                tcpsocket = tcpserver->nextPendingConnection();
                QString ip = tcpsocket->peerAddress().toString();
                qint16 port = tcpsocket->peerPort();
                QString temp = QString("[%1:%2]:成功连接").arg(ip).arg(port);
                //ui->label_7_network->setText(temp);
            }

            );
}
//析构函数
MainWindow::~MainWindow()
{
    delete ui;
}

//事件过滤函数--保持欢迎页的图片尺寸与承载的窗口尺寸一致
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->widget_6_pictrue)
    {
        if (event->type() == QEvent::Resize)
        {
            ui->label_7_picture->resize( ui->widget_6_pictrue->size());
            return false;//继续传递事件
        }
        else
        {
            return false;//继续传递事件
        }
    }
    else
    {
        return MainWindow::eventFilter1(obj, event);
    }
}

//QLabel事件过滤函数1--QLabel鼠标点击事件切换欢迎页展示的图片
bool MainWindow::eventFilter1(QObject *obj, QEvent *event)
{
    if (obj == ui->label_8_shrink_1)
    {
        if (event->type() == QEvent::MouseButtonRelease)
        {
            ui->label_7_picture->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix_photo/photo/picture1.jpeg")));
            return false;//继续传递事件
        }
        else
        {
            return false;//继续传递事件
        }
    }
    else
    {
        return MainWindow::eventFilter2(obj, event);//将事件传递给父类
    }
}

//QLabel事件过滤函数2--QLabel鼠标点击事件切换欢迎页展示的图片
bool MainWindow::eventFilter2(QObject *obj, QEvent *event)
{
    if (obj == ui->label_8_shrink_2)
    {
        if (event->type() == QEvent::MouseButtonRelease)
        {
            ui->label_7_picture->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix_photo/photo/picture2.jpeg")));
            return false;//继续传递事件
        }
        else
        {
            return false;//继续传递事件
        }
    }
    else
    {
        return MainWindow::eventFilter3(obj, event);//将事件传递给父类
    }
}

//QLabel事件过滤函数3--QLabel鼠标点击事件切换欢迎页展示的图片
bool MainWindow::eventFilter3(QObject *obj, QEvent *event)
{
    if (obj == ui->label_8_shrink_3)
    {
        if (event->type() == QEvent::MouseButtonRelease)
        {
            ui->label_7_picture->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix_photo/photo/picture3.jpeg")));
            return true;//忽略掉事件
        }
        else
        {
            return false;//继续传递事件
        }
    }
    else
    {
        return QMainWindow::eventFilter(obj, event);//将事件传递给父类
    }
}

//登录按钮槽函数--建立并初始化登录页面
void MainWindow::on_pushButton_3_logOn_clicked()
{
    log_on *log_on_widget = new log_on;//建立在堆上
    log_on_widget->setWindowTitle(QString("登陆界面"));
    log_on_widget->setAttribute(Qt::WA_DeleteOnClose);//设置窗体关闭时自动释放。
    log_on_widget->show();//如果不new将建立在栈上，show()函数不会阻塞当前线程，窗口会显示出来，然后函数立即返回，窗口消失，代码继续执行。
}

//搜索框槽函数--页面跳转到搜索结果页
void MainWindow::on_lineEdit_3_sourch_returnPressed()
{
    ui->tabWidget_2_central->setCurrentWidget(ui->tab_4_search);

//后续增加连接到数据库并展示搜索的数据的功能

}

//新建设备页面标签页变化槽函数
void MainWindow::on_tabWidget_5_newStruct_currentChanged(int index)
{
    if(index == 0)
    {
        ui->tabWidget_5_newStruct->setTabEnabled(1,false);
        ui->tabWidget_5_newStruct->setTabText(1,QString(" "));
    }
}

//新建设备页系列选择跳转按钮槽函数--系列1
void MainWindow::on_pushButton_7_1_clicked()
{
    ui->tabWidget_5_newStruct->setCurrentWidget(ui->widget_6_defined);
    ui->tabWidget_5_newStruct->setTabEnabled(1,true);
    QString searis1 = ui->pushButton_7_1->text();
    ui->tabWidget_5_newStruct->setTabText(1,searis1);
    ui->stackedWidget_7_defined->setCurrentIndex(0);
}

//新建设备页系列选择跳转按钮槽函数--系列2
void MainWindow::on_pushButton_7_7_clicked()
{
    ui->tabWidget_5_newStruct->setCurrentWidget(ui->widget_6_defined);
    ui->tabWidget_5_newStruct->setTabEnabled(1,true);
    QString searis2 = ui->pushButton_7_7->text();
    ui->tabWidget_5_newStruct->setTabText(1,searis2);
    ui->stackedWidget_7_defined->setCurrentIndex(1);

}

//新建设备页系列选择跳转按钮槽函数--系列3
void MainWindow::on_pushButton_7_3_clicked()
{
    ui->tabWidget_5_newStruct->setCurrentWidget(ui->widget_6_defined);
    ui->tabWidget_5_newStruct->setTabEnabled(1,true);
    QString searis3 = ui->pushButton_7_3->text();
    ui->tabWidget_5_newStruct->setTabText(1,searis3);
    ui->stackedWidget_7_defined->setCurrentIndex(2);

}

//新建设备页系列选择跳转按钮槽函数--系列4
void MainWindow::on_pushButton_7_5_clicked()
{
    ui->tabWidget_5_newStruct->setCurrentWidget(ui->widget_6_defined);
    ui->tabWidget_5_newStruct->setTabEnabled(1,true);
    QString searis4 = ui->pushButton_7_5->text();
    ui->tabWidget_5_newStruct->setTabText(1,searis4);
    ui->stackedWidget_7_defined->setCurrentIndex(3);

}

//新建设备页系列选择跳转按钮槽函数--系列5
void MainWindow::on_pushButton_7_9_clicked()
{
    ui->tabWidget_5_newStruct->setCurrentWidget(ui->widget_6_defined);
    ui->tabWidget_5_newStruct->setTabEnabled(1,true);
    QString searis5 = ui->pushButton_7_9->text();
    ui->tabWidget_5_newStruct->setTabText(1,searis5);
    ui->stackedWidget_7_defined->setCurrentIndex(4);
}

//新建设备页系列选择跳转按钮槽函数--系列6
void MainWindow::on_pushButton_7_11_clicked()
{
    ui->tabWidget_5_newStruct->setCurrentWidget(ui->widget_6_defined);
    ui->tabWidget_5_newStruct->setTabEnabled(1,true);
    QString searis6 = ui->pushButton_7_11->text();
    ui->tabWidget_5_newStruct->setTabText(1,searis6);
    ui->stackedWidget_7_defined->setCurrentIndex(5);
}

//logo按钮槽函数--跳转到欢迎页
void MainWindow::on_pushButton_3_home_clicked()
{
    ui->tabWidget_2_central->setCurrentIndex(0);
}


void MainWindow::on_lineEdit_3_sourch_textChanged(const QString &arg1)
{
    if (!arg1.isEmpty())
    {
        ui->lineEdit_3_sourch->setStyleSheet("QLineEdit{color:rgba(0, 0, 0,1);"
                                             "background-color:#FFFFFF;border-radius:5px;}");
    }
    else
    {
        ui->lineEdit_3_sourch->setStyleSheet("QLineEdit{color :rgba(120, 120, 120,0.8);"
                                             "background-color :#FFFFFF;border-radius:5px;}");
    }
}

void MainWindow::on_lineEdit_9_sourch_textChanged(const QString &arg1)
{
    if (!arg1.isEmpty())
    {
        ui->lineEdit_9_sourch->setStyleSheet("QLineEdit{color:rgba(0, 0, 0,1);"
                                             "border: 2px solid #5DAFE6;border-radius:5px;}");
    }
    else
    {
        ui->lineEdit_9_sourch->setStyleSheet("QLineEdit{color :rgba(120, 120, 120,0.8);"
                                             "border: 2px solid #5DAFE6;border-radius:5px;}");
    }

}

void MainWindow::on_lineEdit_9_sourch_2_textChanged(const QString &arg1)
{
    if (!arg1.isEmpty())
    {
        ui->lineEdit_9_sourch_2->setStyleSheet("QLineEdit{color:rgba(0, 0, 0,1);"
                                             "border: 2px solid #5DAFE6;border-radius:5px;}");
    }
    else
    {
        ui->lineEdit_9_sourch_2->setStyleSheet("QLineEdit{color :rgba(120, 120, 120,0.8);"
                                             "border: 2px solid #5DAFE6;border-radius:5px;}");
    }

}

void MainWindow::on_pushButton_9_2_clicked()
{
    for(int i=0;i<21;i++)
    {
        ui->tableWidget_11_1->setRowHidden(i,0);
    }
    for(int i=0;i<16;i++)
    {
        if(i==7||i==8){continue;}
        else{ui->tableWidget_11_1->setRowHidden(i,1);}
    }
}

void MainWindow::on_pushButton_9_3_clicked()
{
    for(int i=0;i<21;i++)
    {
        ui->tableWidget_11_1->setRowHidden(i,0);
    }
    for(int i=7;i<16;i++)
    {
        ui->tableWidget_11_1->setRowHidden(i,1);
    }
}

void MainWindow::on_pushButton_9_4_clicked()
{
    for(int i=0;i<21;i++)
    {
        ui->tableWidget_11_1->setRowHidden(i,0);
    }
    for(int i=0;i<16;i++)
    {
        if(i>8&&i<13){continue;}
        else{ui->tableWidget_11_1->setRowHidden(i,1);}
    }
}

void MainWindow::on_pushButton_9_5_clicked()
{
    for(int i=0;i<21;i++)
    {
        ui->tableWidget_11_1->setRowHidden(i,0);
    }
    for(int i=0;i<13;i++)
    {
        ui->tableWidget_11_1->setRowHidden(i,1);
    }
}

void MainWindow::on_pushButton_9_1_clicked()
{
    for(int i=0;i<21;i++)
    {
     ui->tableWidget_11_1->setRowHidden(i,0);
    }
}
