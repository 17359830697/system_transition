#ifndef WIDGET_H
#define WIDGET_H
#pragma execution_character_set("utf-8")
#include <QWidget>
#include<QStack>
#include<QQueue>
#include<QDebug>
#include<qmath.h>
#include<QMessageBox>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void two_transition(QString texts);
    void eight_transition(QString texts);
    void ten_transition(QString texts);
    void sixteen_transition(QString texts);
    int twoToeight(QString str);
    int twoTosixteen(QString str);
    QString eightTotwo(int num);
    QString sixteenTotwo(int num);
    QString delete_zero(QString ret);
    void error_tip();

private slots:
    void on_btn_transition_clicked();

    void on_radio_2_clicked();

    void on_radio_8_clicked();

    void on_radio_10_clicked();

    void on_radio_16_clicked();

private:
    Ui::Widget *ui;
    int system_flag = 2;//进制变量
    bool is_minus = false; //判断是否为负数
    bool is_float = false;//判断是否带小数
};
#endif // WIDGET_H
