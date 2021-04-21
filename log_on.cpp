#include "log_on.h"
#include "ui_log_on.h"

#include <QDebug>

log_on::log_on(QWidget *parent)
    :QWidget(parent),
    ui_logOn(new Ui::log_on)
{
    ui_logOn->setupUi(this);
}

log_on::~log_on()
{
    delete ui_logOn;
}

//实现搜索框提示信息灰色和输入信息黑色切换的效果
void log_on::on_lineEdit_1_useName_textChanged(const QString &arg1)
{    
    if (!arg1.isEmpty())
    {
        ui_logOn->lineEdit_1_useName->setStyleSheet("QLineEdit{font:13pt;color:rgba(0, 0, 0, 1); background-color :white;}");
    }
    else
    {
        ui_logOn->lineEdit_1_useName->setStyleSheet("QLineEdit{color:rgba(120, 120, 120,0.8);background-color :white;}");
    }

}

//实现搜索框提示信息灰色和输入信息黑色切换的效果
void log_on::on_lineEdit_1_password_textChanged(const QString &arg1)
{
    if (!arg1.isEmpty())
    {
        ui_logOn->lineEdit_1_password->setStyleSheet("QLineEdit{font:13pt;color :rgba(0, 0, 0,1);background-color :white;}");
    }
    else
    {
        ui_logOn->lineEdit_1_password->setStyleSheet("QLineEdit{color:rgba(120, 120, 120,0.8);background-color :white;}");
    }
}
