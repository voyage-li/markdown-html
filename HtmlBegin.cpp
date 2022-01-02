#include "HtmlBegin.h"
#include "widget.h"
#include "ui_widget.h"
#include<QFile>
#include<QTextStream>
#include<QFileDialog>

void HtmlBegin::Begin()
{
    ui->textEdit_2->insertPlainText("<!DOCTYPE html>\n");
    ui->textEdit_2->insertPlainText("<html>\n");
    ui->textEdit_2->insertPlainText("<head>\n");
    ui->textEdit_2->insertPlainText("<title>output</title>\n");
    ui->textEdit_2->insertPlainText("<style>\n");
    QString fename=QFileDialog::getOpenFileName(this,"选择导入样式表","D:\\");
    QFile f(fename);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
    }
    QTextStream txtInput(&f);
    txtInput.setCodec("utf-8");
    QString lineStr;
    while(!txtInput.atEnd())
    {
        lineStr = lineStr + txtInput.readLine() + "\n";
    }
    ui->textEdit_2->insertPlainText(lineStr);//显示txt文件内容
    ui->textEdit_2->insertPlainText("</style>\n");
    ui->textEdit_2->insertPlainText("<meta http-equiv=\"Content-Type\" content=\"text/html\"; charset=\"gbk\">\n");
    ui->textEdit_2->insertPlainText("</head>\n");
    ui->textEdit_2->insertPlainText("<body>\n");
}
