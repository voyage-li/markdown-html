#include "TranslateImages.h"
#include"Change.h"
#include "widget.h"
#include "ui_widget.h"

void TranslateImages::tr_image(std::string s)
{
    ui->textEdit_2->insertPlainText("<img src=\"");
    std::smatch url;
    std::regex_match(s, url, std::regex("!\\[.+\\]\\((.+)\\)"));
    ui->textEdit_2->insertPlainText(Change::StrtoQstr(url[1]));
    ui->textEdit_2->insertPlainText("\">\n");
}
