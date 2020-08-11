#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <iostream>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->lineEdit->setReadOnly(true);//只读模式
    ui->lineEdit->move(QPoint(0,0));//设置lineEdit位置
    ui->lineEdit->setAlignment(Qt::AlignRight);//从右侧显示

    setWindowTitle(QString("布尔运算-计算器"));//设置标题
    setWindowIcon(QIcon(":/new/prefix1/icon/title.ico"));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::getChar()
{
    ba=in.toLatin1();
}

void Widget::getSuffix()
{
  for(int i=0;i<ba.size();i++)
  {
      if(ba[i]=='T'||ba[i]=='F')//1,T,F直接输出
      {
          QString str;
          char x=ba[i];
          str=QString(x);
          out.append(str);
      }else if(s1.isEmpty())//2,遇见非T,F时, 如果堆栈为空，则直接放入堆栈
      {
          s1.push(ba[i]);
      }else if(ba[i]=='|')
          //2.1,如果是或，那么遍历堆栈栈顶元素 一直输出优先级>=或的 即输出栈顶的与，或，非
          //当遇到其他字符时（如左括号）或堆栈空时break
      {
          while(!s1.empty()){
              if(s1.top()=='&' || s1.top()=='|'||s1.top()=='!' ){
                  //把字符转换为字符串输出
                  QString str=QString(s1.pop());
                  out.append(str);
               }else break;
          }
          s1.push(ba[i]);
      }else if(ba[i]=='&')
          //2.2,如果是与，那么遍历堆栈栈顶元素 一直输出优先级>=与的 即输出栈顶的与，非
          //当遇到其他字符时（如左括号）或堆栈空时break
      {
          while(!s1.empty()){
              if(s1.top()=='&' || s1.top()=='!'){
                  //把字符转换为字符串输出
                  QString str=QString(s1.pop());
                  out.append(str);
               }else break;
          }
          s1.push(ba[i]);
      }else if(ba[i]==')')
          //2.3,如果该字符是右括号时，一直输出栈顶元素，直到遇见左括号为止break:
      {
          while(!s1.empty()){
              if(s1.top()=='('){
                  s1.pop();
                  break;
              }
              //把字符转换为字符串输出
              QString str=QString(s1.pop());
              out.append(str);
          }
      }else if(ba[i]=='(')
          //2.4,如果该字符是左括号时，直接放入堆栈
      {
          s1.push(ba[i]);
      }
  }
  //字符串循环结束后 再输出堆栈中剩余的数据
  while(!s1.empty()){
      //把字符转换为字符串输出
      QString str=QString(s1.pop());
      out.append(str);
  }
  //输出后缀表达式
  qDebug()<<out;
}

void Widget::Calc_Suffix()
{
  for(int i=0;i<out.size();i++)
  {
      if(out[i]=="T"||out[i]=="F")//如果是T,F，直接入栈
      {
          s2.push(out[i]);
      }else if(out[i]=="&"||out[i]=="|")//如果是双目运算符，弹栈两次，并进行运算，运算后，结果入栈
      {
          QString x=s2.pop();
          QString y=s2.pop();
          if(out[i]=="&")
          {
             if(x=="T"&&y=="T")
             {
                 s2.push("T");
             }else{
                 s2.push("F");
             }
          }else if(out[i]=="|"){
              if(x=="F"&&y=="F")
              {
                  s2.push("F");
              }else{
                  s2.push("T");
              }
          }
      }else if(out[i]=="!")//如果是单目运算符，弹栈一次，并进行运算，运算后，结果入栈
          {
          QString x=s2.pop();
          if(x=="T")
          {
              s2.push("F");
          }else{
              s2.push("T");
          }
      }
  }
  result = s2.pop();
  qDebug()<<result;
}

void Widget::m_init()
{
    ba.clear();
    out.clear();
}

void Widget::m_out()
{

}


void Widget::on_pushButton_clicked()
{
    in=ui->lineEdit->text();//获取表达式
    getChar();
    getSuffix();
    Calc_Suffix();
    ui->lineEdit->clear();//清空文本编辑框
    ui->lineEdit->setText(QString("%1").arg(result));//显示结果
    m_init();
}

void Widget::on_pushButton_2_clicked()
{
    QString str=ui->lineEdit->text();
    ui->lineEdit->setText(QString("%1%2").arg(str).arg("T"));
}

void Widget::on_pushButton_3_clicked()
{
    QString str=ui->lineEdit->text();
    ui->lineEdit->setText(QString("%1%2").arg(str).arg("F"));
}

void Widget::on_pushButton_4_clicked()
{
    QString str=ui->lineEdit->text();
    ui->lineEdit->setText(QString("%1%2").arg(str).arg("!"));
}

void Widget::on_pushButton_5_clicked()
{
    QString str=ui->lineEdit->text();
    ui->lineEdit->setText(QString("%1%2").arg(str).arg("&"));
}

void Widget::on_pushButton_6_clicked()
{
    QString str=ui->lineEdit->text();
    ui->lineEdit->setText(QString("%1%2").arg(str).arg("|"));
}



void Widget::on_pushButton_18_clicked()
{
    QString str=ui->lineEdit->text();
    ui->lineEdit->setText(QString("%1%2").arg(str).arg("("));
}

void Widget::on_pushButton_19_clicked()
{
    QString str=ui->lineEdit->text();
    ui->lineEdit->setText(QString("%1%2").arg(str).arg(")"));
}

void Widget::on_pushButton_16_clicked()
{
    //清空所有内容，并初始化
    ui->lineEdit->clear();
    m_init();
}

void Widget::on_pushButton_17_clicked()
{
    //退格删除一个字符
    ui->lineEdit->backspace();
}

