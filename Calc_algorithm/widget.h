#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStack>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void getChar();//将QString转换为QByteArray
    void getSuffix();//获取后缀表达式
    void Calc_Suffix();//计算后缀表达式
    void m_init();//初始化
    void m_out();//测试输出（软件成型，没用了）

private slots:
    void on_pushButton_clicked();//"="功能：获取输入中缀表达式，输出计算结果

    void on_pushButton_2_clicked();//获取输入的内容，并显示，以下未注释的槽函数同理

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_16_clicked();//"C"功能：清空输入框内容，并执行m_init函数进行初始化

    void on_pushButton_17_clicked();//"<-"功能：退格删除

private:
    Ui::Widget *ui;
    QString in;//输入的表达式
    QByteArray ba;//输入表达式转换为字节数组
    QStack<char> s1;//中缀表达式转换为后缀表达式时用到的栈
    QVector<QString> out;//后缀表达式
    QStack<QString> s2;//后缀表达式计算结果时用到的栈
    QString result;//计算结果
};

#endif // WIDGET_H
