#include "widget.h"
#include "ui_widget.h"
#include<QFileDialog>
#include<QString>
#include<QDebug>
#include<QTextStream>
#include<QProcess>
#include<QDesktopServices>
#include<QUrl>
#include<bits/stdc++.h>
#include<QMessageBox>
#include <QCloseEvent>
#include "Change.h"
#include "HtmlBegin.h"
#include "HtmlEnd.h"
#include "Translate.h"
#include "TranslateHeaders.h"
#include "TranslateImages.h"
#include "TranslateLinks.h"
#include "TranslateText.h"
#include <QDir>

Widget* Widget::mywidget = nullptr;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mywidget = this;
    connect(ui->pushButton,&QPushButton::clicked,[=](){
        //打开markdown文件
        QString fileName=QFileDialog::getOpenFileName(this,"打开文件夹","D:\\");
        if (!fileName.isEmpty())
        {
            QFile f(fileName);
            if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                ui->textEdit->setText("Fail！！");
                return;
            }
            QTextStream txtInput(&f);
            txtInput.setCodec("utf-8");
            ui->textEdit->clear();
            while(!txtInput.atEnd())
            {
                ui->textEdit->insertPlainText(txtInput.readLine());
                ui->textEdit->insertPlainText("\n");
            }
        }
    });
    connect(ui->pushButton_2,&QPushButton::clicked,[=](){
        //转化部分
        QString name = ui->textEdit->toPlainText();
        std::string con=Change::QstrtoStr(name);
        //由于cmd版本是对std::vector<std::string>类型进行操作 所以QString类型转换成std::vector<std::string>
        int index = 0;
        content.clear();
        while (1)
        {
            char temp[500];
            int i = 0;
            while (con[index + i] != '\n')
            {
                temp[i] = con[index + i];
                i++;
                if (index + i >= (int)con.size())
                break;
            }
            temp[i] = '\0';
            std::string tmp = temp;
            content.push_back(tmp);
            index = index + i + 1;
            if (index >= (int)con.size())
                break;
         }
        content.push_back("");
        for (int i = 0; i < (int)content.size(); i++)
        {
            int temp = now;
            handlelist(i, -1);
            if (temp != now)
                i = now;
        }
        now=0;
        for (int i = 0; i < (int)content.size(); i++)
        {
            int temp = now;
            handlequote(i,0);
            if (temp != now)
                i = now;
        }
        ui->textEdit_2->clear();//清空输出框内容
        HtmlBegin a;
        a.Begin();
        Translate tr;
        tr.translate(content);
        HtmlEnd b;
        b.End();
        isrun=true;
    });
    connect(ui->pushButton_3,&QPushButton::clicked,[=](){
        //保存文件
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),"./index.html",tr("out(*.html)"));
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            QMessageBox::critical(this, "critical", tr("文件保存失败！"),QMessageBox::Yes, QMessageBox::Yes);
        }
        else
        {
            issave=true;
            QTextStream stream(&file);
            stream << ui->textEdit_2->toPlainText();
            stream.flush();
            file.close();
        }
    });
    connect(ui->pushButton_4,&QPushButton::clicked,[=](){
        //预览文件效果
        QString curPath = QDir::currentPath();
        QString fileName=curPath+"/index.html";
        QFile file2(fileName);
        if (!file2.open(QIODevice::WriteOnly|QIODevice::Text))
        {
        }
        else
        {
            QTextStream stream(&file2);
            stream << ui->textEdit_2->toPlainText();
            stream.flush();
            file2.close();
        }
        this->ui->axWidget->setControl(QString::fromUtf8("{8856F961-340A-11D0-A96B-00C04FD705A2}"));//注册组件ID
        this->ui->axWidget->setProperty("DisplayAlerts",false);//不显示警告信息
        this->ui->axWidget->setProperty("DisplayScrollBars",true);//不显示滚动条
        QString webstr=QString(fileName);//设置要打开的网页
        this->ui->axWidget->dynamicCall("Navigate(const QString&)",webstr);//显示网页
    });
}

Widget::~Widget()
{
    QString curPath = QDir::currentPath();
    QString filen=curPath+"/index.html";
    QFile file3(filen);
    if (!file3.open(QIODevice::WriteOnly|QIODevice::Text))
    {
    }
    else
    {
        file3.remove();
    }
    delete ui;
}

int Widget::isquote(int i)
{
    std::regex a("^\\>+(.+)$");
    if (std::regex_match(content[i], a))
    {
        int index = 0;
        while (content[i][index] == '>')
            index++;
        content[i] = std::regex_replace(content[i], a, "<p>$1</p>");
        return index;
    }
    else
        return 0;
}

void Widget::handlequote(int i, int last)
{
    now = i;
    int number = isquote(i);
    if(number==0)
        return;
    else if (number >= last)
    {
        for (int j = 0; j < number - last; j++)
            content[i].insert(0, "<blockquote>");
        handlequote(now + 1, number);
        for (int j = 0; j < number - last; j++)
            content[now - 1] += "</blockquote>";
    }
}


int Widget::islist(int i)//判断是否为列表
{
    int index = 0;
    std::regex a("^[ ]*[-*+] (.+)$");
    std::regex e("^[ ]*\\d+[.] (.+)$");
    if (std::regex_search(content[i], e))
    {
        for (int j = 0; content[i][j] == ' '; j++)
        {
            index++;
        }
        if (index % 4 == 0)
        {
            content[i] = std::regex_replace(content[i], e, "<li>$1</li>");
        }
        else
            return -1;
        return 2 * index;
    }
    else if (std::regex_search(content[i], a))
    {
        for (int j = 0; content[i][j] == ' '; j++)
        {
            index++;
        }
        if (index % 4 == 0)
            content[i] = std::regex_replace(content[i], a, "<li>$1</li>");
        else
            return -1;
        return 2 * index + 1;
    }
    else
        return -1;
}

int Widget::blankjudge(int a)//判断空格无序还是有序
{
    if (a % 2 == 0)
        return a / 2;
    else
        return (a - 1) / 2;
}

int Widget::handlelist(int i, int blanklast)
{
    now = i;
    int blankthis = islist(i);
    if (blankthis == -1)
    {
        return -1;
    }
    else
    {
        int blankthis_temp = blankjudge(blankthis);
        int blanklast_temp = blankjudge(blanklast);
        if (blankthis % 2 == 0)
        {

            if (blankthis_temp > blanklast_temp || (blankthis_temp == blanklast_temp && blankthis != blanklast))//新的一层列表
            {
                content[i].insert(0, "<ol>");
                int tmp = handlelist(i + 1, blankthis);
                if (tmp == blankthis_temp)
                {
                    tmp = handlelist(now + 1, blankthis);
                }
                content[now - 1] += "</ol>";
                return tmp;
            }
            else if (blankthis_temp == blanklast_temp && blankthis == blanklast)//和上级相同
            {
                int tmp = handlelist(i + 1, blankthis);
                return tmp;
            }
            else//上一级列表结束
            {
                return blankthis_temp;
            }
        }
        else//同理
        {
            if (blankthis_temp > blanklast_temp || (blankthis_temp == blanklast_temp && blankthis != blanklast))
            {
                content[i].insert(0, "<ul>");
                int tmp = handlelist(i + 1, blankthis);
                if (tmp == blankthis_temp)
                {
                    tmp = handlelist(now + 1, blankthis);
                }
                content[now - 1] += "</ul>";
                return tmp;
            }
            else if (blankthis_temp == blanklast_temp && blankthis == blanklast)
            {
                int tmp = handlelist(i + 1, blankthis);
                return tmp;
            }
            else
                return blankthis_temp;
        }
    }
    return 0;
}


void Widget::closeEvent(QCloseEvent *event)//判断程序结束运行
{
    if(issave==false&&isrun==true)
    {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),"./index.html",tr("out(*.html)"));
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            QMessageBox::critical(this, "critical", tr("文件保存失败！"),QMessageBox::Yes, QMessageBox::Yes);
        }
        else
        {
            issave=true;
            QTextStream stream(&file);
            stream << ui->textEdit_2->toPlainText();
            stream.flush();
            file.close();
        }
    }
}
