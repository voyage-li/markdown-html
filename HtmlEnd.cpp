#include "HtmlEnd.h"
#include "widget.h"
#include "ui_widget.h"

void HtmlEnd::End()
{
    ui->textEdit_2->insertPlainText("</body>\n");
    ui->textEdit_2->insertPlainText("</html>\n");
}
