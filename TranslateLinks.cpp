#include "TranslateLinks.h"
#include "TranslateText.h"
#include"change.h"
#include "widget.h"
#include "ui_widget.h"

void TranslateLinks::tr_link(std::string s)
{
    std::smatch answer;
    std::regex_match(s, answer, std::regex("^\\[(.+)\\]\\((.+)\\)$"));
    ui->textEdit_2->insertPlainText("<a href=\"");
    ui->textEdit_2->insertPlainText(Change::StrtoQstr(answer[2]));
    ui->textEdit_2->insertPlainText("\"target=\"_blank\">");
    TranslateText trlt;
    trlt.tr_text(answer[1]);
    ui->textEdit_2->insertPlainText("</a>\n");
}
