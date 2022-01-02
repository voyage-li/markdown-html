#include "TranslateText.h"
#include"Change.h"
#include "widget.h"
#include "ui_widget.h"

void TranslateText::tr_text(std::string s)
{
    std::string temp, temp2;
    const std::regex re_i1("\\*([^\\*]+)\\*");
    const std::regex re_i2("\\_([^\\_]+)\\_");
    const std::regex re_S("\\~\\~([^\\~\\~]+)\\~\\~");
    const std::regex re_b1("\\*\\*([^\\*\\*]+)\\*\\*");
    const std::regex re_b2("\\_\\_([^\\_\\_]+)\\_\\_");
    const std::regex re_code("\\`([^\\`]+)\\`");
    const std::regex re_mark("\\=\\=([^\\=\\=]+)\\=\\=");
    temp = s;
    temp.insert(temp.begin(), ' ');
    temp2.clear();
    std::regex_replace(std::back_inserter(temp2), temp.begin(), temp.end(), re_b1, "<b>$1</b>");
    temp.clear();
    std::regex_replace(std::back_inserter(temp), temp2.begin(), temp2.end(), re_b2, "<b>$1</b>");
    temp2.clear();
    std::regex_replace(std::back_inserter(temp2), temp.begin(), temp.end(), re_S, "<s>$1</s>");
    temp.clear();
    std::regex_replace(std::back_inserter(temp), temp2.begin(), temp2.end(), re_i1, "<i>$1</i>");
    temp2.clear();
    std::regex_replace(std::back_inserter(temp2), temp.begin(), temp.end(), re_i2, "<i>$1</i>");
    temp.clear();
    std::regex_replace(std::back_inserter(temp), temp2.begin(), temp2.end(), re_code, "<code>$1</code>");
    temp2.clear();
    std::regex_replace(std::back_inserter(temp2), temp.begin(), temp.end(), re_mark, "<mark>$1</mark>");
    temp2.erase(temp2.begin());
    ui->textEdit_2->insertPlainText(Change::StrtoQstr(temp2));
}
