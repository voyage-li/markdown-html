#include "TranslateHeaders.h"
#include "TranslateText.h"
#include "widget.h"
#include "ui_widget.h"
void TranslateHeaders::tr_head(std::string s)
{
    int index = 0;
    for (index = 0; s.at(index) == '#'; index++)
        ;
    std::smatch answer;
    std::regex_match(s, answer, std::regex("^#{1,6} (.+)$"));
    ui->textEdit_2->insertPlainText("<h");
    ui->textEdit_2->insertPlainText(QString::number(index));
    ui->textEdit_2->insertPlainText(">");
    TranslateText trht;
    trht.tr_text(answer[1]);
    ui->textEdit_2->insertPlainText("</h");
    ui->textEdit_2->insertPlainText(QString::number(index));
    ui->textEdit_2->insertPlainText(">\n");
}
