#ifndef LOG_ON_H//防止一个源文件两次包含同一个头文件
#define LOG_ON_H//宏定义

#include <QWidget>

//QT利用Pimpl手法分离了类的接口及实现
namespace Ui {class log_on;}

class log_on : public QWidget
{
    Q_OBJECT//Q对象宏必须出现在类定义的私有部分，它声明自己的信号和插槽，或者使用Qt元对象系统提供的其他服务。

public:
    explicit log_on(QWidget *parent = nullptr);//有参显式构造函数

    ~log_on();//析构函数

private slots:
    void on_lineEdit_1_useName_textChanged(const QString &arg1);

    void on_lineEdit_1_password_textChanged(const QString &arg1);

private:
    Ui::log_on *ui_logOn;//UI下的log_on类的私有指针指向隐藏的实现类
};

#endif // LOG_ON_H


/*#ifndef 在头文件中的作用
在一个大的软件工程里面，可能会有多个文件同时包含一个头文件，当这些文件编译链接成一个可执行文件时
，就会出现大量“重定义”的错误。在头文件中实用#ifndef #define #endif能避免头文件的重定义。
*/

/*C++中的explicit关键字
 * 只能用于修饰只有一个参数的类构造函数, 它的作用是表明该构造函数是显式的,
而非隐式的, 跟它相对应的另一个关键字是implicit, 意思是隐藏的,类构造函数默认情况下即声明为implicit(隐式)
explicit关键字的作用就是防止类构造函数的隐式自动转换.
*/

/*在类中使用 Pimpl 惯用法，具有如下优点：
降低耦合
信息隐藏
降低编译依赖，提高编译速度
接口与实现分离

C++的编译模式为“分离式编译”，即不同的源文件是分开编译的。
也就是说，不同的源文件之间有一道天然的防火墙，一个源文件“失火”并不会影响到另一个源文件。
但是，这里我们考虑的是头文件，如果头文件“失火”又当如何呢？
头文件是不能直接编译的，它包含于源文件中，并作为源文件的一部分被一起编译。
*/

