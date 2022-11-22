#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("进制转换器");
    this->setFixedSize(QSize(this->width(),this->height()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::two_transition(QString texts) //二进制
{
    QStack<int> stack;
    QQueue<int> queue;
    QString text = texts; //整数部分
    QString f_text; //小数部分
    if(is_float)//如果是小数，整数部分和小数部分分开计算
    {
        text = texts.section(".",0,0);
        f_text = texts.section(".",1,1);
    }

  //转二进制
    QString text2 = text;
    if(is_minus)
        text2 = "-"+text2;
    if(is_float)
        text2 = text2 + "."+ f_text;
    text2 = delete_zero(text2);
    ui->le_2->setText(text2);

  //转八进制
    QString text_clone = text; //拷贝
    int len = text_clone.length();
   while(len)
   {
       if(len<3)//若当前位数小于3位，则补0
       {
           while(len!=3)
           {
               text_clone = "0" + text_clone;
               len = text_clone.length();
           }
       }
       QString temp = text_clone.mid(len-3,3);
       int tem_len = temp.length();
       int num = twoToeight(temp);
       stack.push(num); //入栈
      text_clone.remove(len-tem_len,tem_len);//更新字符串
      len = text_clone.length();
   }
   QString num8;//整数部分
   QString f_num8;//小数部分
   while(!stack.empty())
   {
       QString str = QString::number(stack.pop());
       num8 += str;
   }
   if(is_float) //处理小数
   {
       QString f_text_clone = f_text;//拷贝
       int len = f_text_clone.length();
       if(len<3) //长度小于3后位补0
       {
           while(len!=3)
           {
                f_text_clone += "0";
                len = f_text_clone.length();
           }

       }
       while(len)
       {
           QString temp = f_text_clone.mid(0,3);
           if(temp.length()<3)
           {
               while(temp.length()!=3)
               {
                   temp += "0";
               }

           }
           int res = twoToeight(temp);
           queue.enqueue(res);
           f_text_clone.remove(0,3);
           len =  f_text_clone.length();
       }
       while(!queue.empty())
       {
           QString ret = QString::number(queue.dequeue());//出队
           f_num8 += ret;
       }
   }
   if(is_minus)
    num8 = "-"+num8;
   if(is_float)
    num8 = num8 + "." +f_num8;
   num8 = delete_zero(num8);
   ui->le_8->setText(num8);
   //转十进制
   QString text_clone1 = text; //拷贝
   int sum = 0;
   double f_sum = 0; //小数部分和
   int len1 = text_clone1.length();
   for(int i = len1 - 1,k = 0;i>=0;i--,k++)
   {
       QString n = text_clone1.at(i);
       int num = n.toInt();
       int p = num * qPow(2,k);
       sum = sum + p;
   }
   if(is_float) //处理小数
   {
       QString f_text_clone = f_text;//拷贝
       int len = f_text_clone.length();
       for(int i = 0,k = -1;i<len;i++,k--)
       {
           QString num = f_text_clone.at(i);
           double ret = num.toDouble();
           double df = ret * qPow(2,k);
           f_sum+=df;
       }
       //去除头部的0.
       QString t_f_sum = QString::number(f_sum).section(".",1,1);
       f_sum = t_f_sum.toDouble();
   }
   QString temp_sum = QString::number(sum);
   if(is_minus)
   temp_sum = "-" + temp_sum;
   if(is_float)
   temp_sum = temp_sum + "." + QString::number(f_sum);
   temp_sum = delete_zero(temp_sum);
   ui->le_10->setText(temp_sum);
   //转十六进制
   QString text_clone2 = text; //拷贝
   int len2 = text_clone2.length();
  while(len2)
  {
      if(len2<4)//若当前位数小于4位，则补0
      {
          while(len2!=4)
          {
              text_clone2 = "0" + text_clone2;
              len2 = text_clone2.length();
          }
      }
      QString temp = text_clone2.mid(len2-4,4);
      int tem_len = temp.length();
      int num = twoTosixteen(temp);
      stack.push(num); //入栈
     text_clone2.remove(len2-tem_len,tem_len);//更新字符串
     len2 = text_clone2.length();
  }
  QString num16;
  QString f_num16;
  while(!stack.empty())
  {
      QString n = QString::number(stack.pop());
      if(n=="10")
      num16 += "A";
      else if(n=="11")
      num16 += "B";
      else if(n=="12")
      num16 += "C";
      else if(n=="13")
      num16 += "D";
      else if(n=="14")
      num16 += "E";
      else if(n=="15")
      num16 += "F";
      else
      num16 += n;
  }
  if(is_float)//处理小数部分
  {
      QString f_text_clone = f_text;//拷贝
      int len = f_text_clone.length();
      if(len<4) //长度小于4后位补0
      {
          while(len!=4)
          {
               f_text_clone += "0";
               len = f_text_clone.length();
          }

      }
      while(len)
      {
          QString temp = f_text_clone.mid(0,4);
          if(temp.length()<4)
          {
              while(temp.length()!=4)
              {
                  temp += "0";
              }

          }
          int res = twoTosixteen(temp);
          queue.enqueue(res);
          f_text_clone.remove(0,4);
          len =  f_text_clone.length();
      }
      while(!queue.empty())
      {

          QString ret = QString::number(queue.dequeue());//出队
          if(ret=="10")
          f_num16 += "A";
          else if(ret=="11")
          f_num16 += "B";
          else if(ret=="12")
          f_num16 += "C";
          else if(ret=="13")
          f_num16 += "D";
          else if(ret=="14")
          f_num16 += "E";
          else if(ret=="15")
          f_num16 += "F";
          else
          f_num16 += ret;
      }
  }
   if(is_minus)
   num16 = "-"+num16;
   if(is_float)
   num16 = num16 + "." + f_num16;
   num16 = delete_zero(num16);
  ui->le_16->setText(num16);
}

void Widget::eight_transition(QString texts)//八进制
{
    QStack<int> stack;
    QQueue<int> queue;
    QString text = texts;
    QString f_text; //小数部分
    if(is_float)//如果是小数，整数部分和小数部分分开计算
    {
        text = texts.section(".",0,0);
        f_text = texts.section(".",1,1);
    }
   //转二进制
    QStack<QString> qstr_stack;
    QString text_clone = text; //拷贝
    int len = text_clone.length();
    for(int i = len - 1;i>=0;i--)
    {
        QString str = text_clone.at(i);
        int num = str.toInt();
        QString res = eightTotwo(num);
        qstr_stack.push(res);
    }
    QString num2;
    QString f_num2;
    while(!qstr_stack.empty())
    {
        QString tem = qstr_stack.pop();
        num2 += tem;
    }
    if(is_float)//处理小数
    {
        QString f_text_clone = f_text;//拷贝
        int len = f_text_clone.length();
        for(int i = 0;i<len;i++)
         {
            QString ret = f_text_clone.at(i);
            int num = ret.toInt();
            QString str = eightTotwo(num);
            f_num2 += str;
        }
    }
    QString num3 = num2;
    if(is_minus)
        num2 = "-"+num2;
    if(is_float)
        num2 = num2 + "." +f_num2;
    num2 = delete_zero(num2);
    ui->le_2->setText(num2);
    //转八进制
    QString tem_text = text;
    if(is_minus)
    tem_text = "-"+tem_text;
    if(is_float)
    tem_text = tem_text + "." + f_text;
    tem_text = delete_zero(tem_text);
     ui->le_8->setText(tem_text);
    //转十进制
    QString text_clone2 = text; //拷贝
    int len2 = text_clone2.length();
    int sum = 0;
    double f_sum = 0;
    for(int i = len2 - 1,k = 0;i>=0;i--,k++)
    {
        QString str = text_clone2.at(i);
        int num = str.toInt();
        int p = num * qPow(8,k);
        sum += p;
    }
    if(is_float)//处理小数部分
    {
        QString f_text_clone = f_text;//拷贝
        int len = f_text_clone.length();
        for(int i = 0,k = -1;i<len;i++,k--)
        {
            QString num = f_text_clone.at(i);
            double ret = num.toDouble();
            double df = ret * qPow(8,k);
            f_sum+=df;
        }
        //去除头部的0.
        QString t_f_sum = QString::number(f_sum).section(".",1,1);
        f_sum = t_f_sum.toDouble();
    }
    QString tem_sum = QString::number(sum);
    if(is_minus)
        tem_sum = "-" + tem_sum;
    if(is_float)
        tem_sum = tem_sum + "." + QString::number(f_sum);
    tem_sum = delete_zero(tem_sum);
    ui->le_10->setText(tem_sum);
    //转十六
    QString text_clone3 = num3; //拷贝
    int len3 = text_clone3.length();
   while(len3)
   {
       if(len3<4)//若当前位数小于4位，则补0
       {
           while(len3!=4)
           {
               text_clone3 = "0" + text_clone3;
               len3 = text_clone3.length();
           }
       }
       QString temp = text_clone3.mid(len3-4,4);
       int tem_len = temp.length();
       int num = twoTosixteen(temp);
       stack.push(num); //入栈
      text_clone3.remove(len3-tem_len,tem_len);//更新字符串
      len3 = text_clone3.length();
   }
   QString num16;
   QString f_num16;
   while(!stack.empty())
   {
       QString n = QString::number(stack.pop());
       if(n=="10")
       num16 += "A";
       else if(n=="11")
       num16 += "B";
       else if(n=="12")
       num16 += "C";
       else if(n=="13")
       num16 += "D";
       else if(n=="14")
       num16 += "E";
       else if(n=="15")
       num16 += "F";
       else
       num16 += n;
   }
   if(is_float)//处理小数部分
   {
       QString f_text_clone = f_num2;//拷贝
       int len = f_text_clone.length();
       if(len<4) //长度小于4后位补0
       {
           while(len!=4)
           {
                f_text_clone += "0";
                len = f_text_clone.length();
           }

       }
       while(len)
       {
           QString temp = f_text_clone.mid(0,4);
           if(temp.length()<4)
           {
               while(temp.length()!=4)
               {
                   temp += "0";
               }

           }
           int res = twoTosixteen(temp);
           queue.enqueue(res);
           f_text_clone.remove(0,4);
           len =  f_text_clone.length();
       }
       while(!queue.empty())
       {

           QString ret = QString::number(queue.dequeue());//出队
           if(ret=="10")
           f_num16 += "A";
           else if(ret=="11")
           f_num16 += "B";
           else if(ret=="12")
           f_num16 += "C";
           else if(ret=="13")
           f_num16 += "D";
           else if(ret=="14")
           f_num16 += "E";
           else if(ret=="15")
           f_num16 += "F";
           else
           f_num16 += ret;
       }
   }
   if(is_minus)
   num16="-"+num16;
   if(is_float)
   num16 = num16 +"." +f_num16;
   num16 = delete_zero(num16);
   ui->le_16->setText(num16);
}

void Widget::ten_transition(QString texts) //十进制
{
    QStack<int> stack;
    QQueue<int> queue;
    QString text = texts;
    QString f_text; //小数部分
    if(is_float)//如果是小数，整数部分和小数部分分开计算
    {
        text = texts.section(".",0,0);
        f_text = texts.section(".",1,1);
    }
    //转二进制
    int num = text.toInt();
    while(num)
    {
        int temp = num%2;
        stack.push(temp);//余数入栈
        num = num/2;
    }
    QString str;
    QString f_str;
    int count = 0;//计数器(保留10位小数)
    while(!stack.empty())
    {
        QString n = QString::number(stack.pop());
        str += n;
    }
    if(is_float)//处理小数部分
    {
        QString f_text_clone = f_text;//拷贝
        int len = f_text_clone.length();
         f_text_clone = "0."+f_text_clone;
        double num = f_text_clone.toDouble();
        double ret = num;
        while(ret&&count!=10)
        {
            ret = ret*2;
            if(ret>=1)
            {
                queue.enqueue(1);
                ret -= 1;
            }
            else
            {
                queue.enqueue(0);
            }
            count++;
        }
        while (!queue.empty())
        {
            QString s = QString::number(queue.dequeue());
            f_str += s;
        }
    }
    if(is_minus)
        str = "-"+str;
    if(is_float)
        str = str + "." +f_str;
    str = delete_zero(str);
    ui->le_2->setText(str);
    //转八进制
    int num8 = text.toInt();
    while(num8)
    {
        int temp = num8%8;
        stack.push(temp);//余数入栈
        num8 = num8/8;
    }
    QString str8;
    QString f_str8;//小数部分
    count = 0;//计数器清0
    while(!stack.empty())
    {
        QString n = QString::number(stack.pop());
        str8 += n;
    }
    if(is_float)//处理小数部分
    {
        QString f_text_clone = f_text;//拷贝
        int len = f_text_clone.length();
         f_text_clone = "0."+f_text_clone;
        double num = f_text_clone.toDouble();
        double ret = num;
        while(ret&&count!=10)
        {
            ret = ret*8;
            if(ret>=1)
            {
                QString tem = QString::number(ret);
                int rs = tem.section(".",0,0).toInt();
                ret -= rs;
                queue.enqueue(rs);
            }
            else
            {
                queue.enqueue(0);
            }
            count++;
        }
        while (!queue.empty())
        {
            QString s = QString::number(queue.dequeue());
            f_str8 += s;
        }
    }
    if(is_minus)
        str8 = "-"+str8;
    if(is_float)
        str8 = str8 +"."+f_str8;
     str8 = delete_zero(str8);
     ui->le_8->setText(str8);
      //转十进制
     QString tem_t = text;
     if(is_minus)
         tem_t = "-"+tem_t;
     if(is_float)
         tem_t = tem_t +"."+ f_text;
      tem_t = delete_zero(tem_t);
         ui->le_10->setText(tem_t);
     //转十六
     int num16 = text.toInt();
     while(num16)
     {
         int temp = num16%16;
         stack.push(temp);//余数入栈
         num16 = num16/16;
     }
     QString str16;
     QString f_str16;//小数部分
     count = 0;//计数器清0
     while(!stack.empty())
     {
         QString n = QString::number(stack.pop());
         if(n=="10")
         str16 += "A";
         else if(n=="11")
         str16 += "B";
         else if(n=="12")
         str16 += "C";
         else if(n=="13")
         str16 += "D";
         else if(n=="14")
         str16 += "E";
         else if(n=="15")
         str16 += "F";
         else
         str16 += n;
     }
     if(is_float)//处理小数部分
     {
         QString f_text_clone = f_text;//拷贝
         int len = f_text_clone.length();
          f_text_clone = "0."+f_text_clone;
         double num = f_text_clone.toDouble();
         double ret = num;
         while(ret&&count!=10)
         {
             ret = ret*16;
             if(ret>=1)
             {
                 QString tem = QString::number(ret);
                 int rs = tem.section(".",0,0).toInt();
                 ret -= rs;
                 queue.enqueue(rs);
             }
             else
             {
                 queue.enqueue(0);
             }
             count++;
         }
         while (!queue.empty())
         {
             QString n = QString::number(queue.dequeue());
             if(n=="10")
             f_str16 += "A";
             else if(n=="11")
             f_str16 += "B";
             else if(n=="12")
             f_str16 += "C";
             else if(n=="13")
             f_str16 += "D";
             else if(n=="14")
             f_str16 += "E";
             else if(n=="15")
             f_str16 += "F";
             else
             f_str16 += n;
         }
     }
     if(is_minus)
         str16 = "-" + str16;
     if(is_float)
         str16 = str16 +"."+f_str16;
     str16 = delete_zero(str16);
     ui->le_16->setText(str16);
}

void Widget::sixteen_transition(QString texts)//十六进制
{

    QStack<int> stack;
    QQueue<int> queue;
    QStack<QString> qstr_stack;
    QQueue<QString> qstr_queue;
    QString text = texts;
    QString f_text;
    if(is_float)//如果是小数，整数部分和小数部分分开计算
    {
        text = texts.section(".",0,0);
        f_text = texts.section(".",1,1);
    }
   //转二进制
    QString text_clone = text;
    int len = text_clone.length();
    for(int i = len-1;i>=0;i--)
    {
        int num;
        QString str = text_clone.at(i);
        if(str=="A"||str=="a")
            num=65;
        else if(str=="B"||str=="b")
            num=66;
        else if(str=="C"||str=="c")
            num=67;
        else if(str=="D"||str=="d")
            num=68;
        else if(str=="E"||str=="e")
            num=69;
        else if(str=="F"||str=="f")
            num=70;
        else
         num = str.toInt();
        QString res = sixteenTotwo(num);
        qstr_stack.push(res);
    }
    QString num2;
    QString f_num2;
    while(!qstr_stack.empty())
    {
        QString str = qstr_stack.pop();
        num2 += str;
    }
    QString num3 = num2;
    if(is_float)//处理小数部分
    {
        QString f_text_clone = f_text;//拷贝
        int len = f_text_clone.length();
        for(int i = 0;i<len;i++)
        {
            QString ret = f_text_clone.at(i);
            int num =ret.toInt();
            QString res = sixteenTotwo(num);
            qstr_queue.enqueue(res);
        }
        while(!qstr_queue.empty())
        {
            QString s = qstr_queue.dequeue();
            f_num2 += s;
        }
    }
    if(is_minus)
        num2 = "-"+num2;
    if(is_float)
        num2 = num2 +"."+f_num2;
    num2 = delete_zero(num2);
    ui->le_2->setText(num2);
    //转八进制
    QString text_clone1 = num3; //拷贝
    int len1 = text_clone1.length();
   while(len1)
   {
       if(len1<3)//若当前位数小于3位，则补0
       {
           while(len1!=3)
           {
               text_clone1 = "0" + text_clone1;
               len1 = text_clone1.length();
           }
       }
       QString temp = text_clone1.mid(len1-3,3);
       int tem_len = temp.length();
       int num = twoToeight(temp);
       stack.push(num); //入栈
      text_clone1.remove(len1-tem_len,tem_len);//更新字符串
      len1 = text_clone1.length();
   }
   QString num8;
   QString f_num8;
   while(!stack.empty())
   {
       QString str = QString::number(stack.pop());
       num8 += str;
   }
   if(is_float) //处理小数
   {
       QString f_text_clone = f_num2;//拷贝
       int len = f_text_clone.length();
       if(len<3) //长度小于3后位补0
       {
           while(len!=3)
           {
                f_text_clone += "0";
                len = f_text_clone.length();
           }

       }
       while(len)
       {
           QString temp = f_text_clone.mid(0,3);
           if(temp.length()<3)
           {
               while(temp.length()!=3)
               {
                   temp += "0";
               }

           }
           int res = twoToeight(temp);
           queue.enqueue(res);
           f_text_clone.remove(0,3);
           len =  f_text_clone.length();
       }
       while(!queue.empty())
       {
           QString ret = QString::number(queue.dequeue());//出队
           f_num8 += ret;
       }
   }
   if(is_minus)
       num8 = "-"+num8;
   if(is_float)
       num8 = num8+"."+f_num8;
   num8 = delete_zero(num8);
   ui->le_8->setText(num8);
   //转十进制
   QString text_clone2 = num3; //拷贝
   int sum = 0;
   double f_sum = 0;
   int len2 = text_clone2.length();
   for(int i = len2 - 1,k = 0;i>=0;i--,k++)
   {
       QString n = text_clone2.at(i);
       int num = n.toInt();
       int p = num * qPow(2,k);
       sum = sum + p;
   }
   if(is_float) //处理小数
   {
       QString f_text_clone = f_num2;//拷贝
       int len = f_text_clone.length();
       for(int i = 0,k = -1;i<len;i++,k--)
       {
           QString num = f_text_clone.at(i);
           double ret = num.toDouble();
           double df = ret * qPow(2,k);
           f_sum+=df;
       }
       //去除头部的0.
       QString t_f_sum = QString::number(f_sum).section(".",1,1);
       f_sum = t_f_sum.toDouble();
   }
   QString tem_sum = QString::number(sum);
   if(is_minus)
       tem_sum = "-"+tem_sum;
   if(is_float)
       tem_sum =  tem_sum +"." +QString::number(f_sum);
    tem_sum = delete_zero(tem_sum);
   ui->le_10->setText(tem_sum);
   //转十六进制
   QString t_text = text;
   if(is_minus)
       t_text = "-"+t_text;
   if(is_float)
       t_text = t_text+"."+f_text;
    t_text = delete_zero(t_text);
   ui->le_16->setText(t_text);
}

int Widget::twoToeight(QString str) //2转8
{
    if(str == "000")
        return 0;
    else if(str == "001")
        return 1;
    else if(str == "010")
        return 2;
    else if(str == "011")
        return 3;
    else if(str == "100")
        return 4;
    else if(str == "101")
        return 5;
    else if(str == "110")
        return 6;
    else if(str == "111")
        return 7;
}

int Widget::twoTosixteen(QString str)//2转16
{
    if(str == "0000")
        return 0;
    else if(str == "0001")
        return 1;
    else if(str == "0010")
        return 2;
    else if(str == "0011")
        return 3;
    else if(str == "0100")
        return 4;
    else if(str == "0101")
        return 5;
    else if(str == "0110")
        return 6;
    else if(str == "0111")
        return 7;
    else if(str == "1000")
        return 8;
    else if(str == "1001")
        return 9;
    else if(str == "1010")
        return 10;
    else if(str == "1011")
        return 11;
    else if(str == "1100")
        return 12;
    else if(str == "1101")
        return 13;
    else if(str == "1110")
        return 14;
    else if(str == "1111")
        return 15;
}

QString Widget::eightTotwo(int num)//8转2
{
    switch(num)
    {
        case 0:return "000";
        case 1:return "001";
        case 2:return "010";
        case 3:return "011";
        case 4:return "100";
        case 5:return "101";
        case 6:return "110";
        case 7:return "111";
    default:return 0;
    }
}

QString Widget::sixteenTotwo(int num)//16转2
{
    switch (num)
    {
         case 0:return "0000";
         case 1:return "0001";
         case 2:return "0010";
         case 3:return "0011";
         case 4:return "0100";
         case 5:return "0101";
         case 6:return "0110";
         case 7:return "0111";
         case 8:return "1000";
         case 9:return "1001";
         case 65:return "1010";
         case 66:return "1011";
         case 67:return "1100";
         case 68:return "1101";
         case 69:return "1110";
         case 70:return "1111";
    default:return 0;
    }
}

QString Widget::delete_zero(QString ret)
{
    //无效无用0
    QString str = ret;
    //删除头部无效0
    QString s = str.at(0);
    while(s=="0")
    {
        str.remove(0,1);
        s = str.at(0);
    }
    return str;
}

void Widget::error_tip()
{
    QMessageBox::warning(this,"警告","输入数值格式不正确,不支持转换!");
}


void Widget::on_btn_transition_clicked()//转换
{
    //获取用户输入
    QString texts = ui->le_cin->text();
    int len = texts.length();
    if(texts.at(0)=="-") //判断是否为负数
    {
        is_minus = true;
        texts = texts.remove(0,1);
    }
    else
        is_minus = false;
    if(texts.contains("."))//判断是否带小数
    {
        is_float = true;
    }
    else
        is_float = false;
    switch (system_flag)
    {
    case 2:
    {
        for(int i = 0;i<len;i++)
        {
            QString str = texts.at(i);
            if(str=="0"||str=="1"||str==".")
                continue;
            else
            {
                error_tip();
                return;
            }
        }
        two_transition(texts);
    }
      break;
    case 8:
    {
        for(int i = 0;i<len;i++)
        {
            QString str = texts.at(i);
            if(str=="0"||str=="1"||str=="2"||str=="3"||str=="4"||str=="5"||str=="6"||str=="7"||str==".")
                continue;
            else
            {
                error_tip();
                return;
            }
        }
        eight_transition(texts);
    }
      break;
    case 10:
    {
        for(int i = 0;i<len;i++)
        {
            QString str = texts.at(i);
            if(str=="0"||str=="1"||str=="2"||str=="3"||str=="4"||str=="5"||str=="6"||str=="7"||
                    str=="8"||str=="9"||str==".")
                continue;
            else
            {
                error_tip();
                return;
            }
        }
        ten_transition(texts);
    }
      break;
    case 16:
    {
        for(int i = 0;i<len;i++)
        {
            QString str = texts.at(i);
            if(str=="0"||str=="1"||str=="2"||str=="3"||str=="4"||str=="5"||str=="6"||str=="7"||
               str=="8"||str=="9"||str=="."||str=="A"||str=="B"||str=="C"||str=="D"||str=="E"||str=="F"||
               str=="a"||str=="b"||str=="c"||str=="d"||str=="e"||str=="f")
                continue;
            else
            {
                error_tip();
                return;
            }
        }
        sixteen_transition(texts);
    }
      break;
    default:
        return;
    }
}

void Widget::on_radio_2_clicked()
{
    system_flag = 2;
}

void Widget::on_radio_8_clicked()
{
    system_flag = 8;
}

void Widget::on_radio_10_clicked()
{
    system_flag = 10;
}

void Widget::on_radio_16_clicked()
{
    system_flag = 16;
}
