#include "Translate.h"
#include "TranslateHeaders.h"
#include "TranslateImages.h"
#include "TranslateLinks.h"
#include "TranslateText.h"
#include "Change.h"
#include "widget.h"
#include "ui_widget.h"

void Translate::translate(std::vector<std::string> s)
{
    int length = s.size();
    for (int i = 0; i < length; i++)
    {
        if (std::regex_search(s.at(i), std::regex("^#{1,6} (.+)$"))) //head
        {
            TranslateHeaders trh;
            trh.tr_head(s.at(i));
        }
        else if (std::regex_search(s.at(i), std::regex("^!\\[.+\\]\\((.+)\\)$"))) //image
        {
            TranslateImages tri;
            tri.tr_image(s.at(i));
        }
        else if (std::regex_search(s.at(i), std::regex("^\\[(.+)\\]\\((.+)\\)$"))) //link
        {
            TranslateLinks trl;
            trl.tr_link(s.at(i));
        }
        else if (std::regex_search(s.at(i), std::regex("^\\-{3,}$")))
        {
            ui->textEdit_2->insertPlainText("<hr/>\n");
        }
        else if (std::regex_search(s.at(i), std::regex("^\\*{3,}$")))
        {
            ui->textEdit_2->insertPlainText("<hr/>\n");
        }
        else
        {
            TranslateText trt;
            trt.tr_text(s.at(i));
            ui->textEdit_2->insertPlainText("<br/>\n");
        }
    }
}
