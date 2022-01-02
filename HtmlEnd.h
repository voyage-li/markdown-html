#ifndef HTMLEND_H
#define HTMLEND_H

#include<bits/stdc++.h>
#include<QWidget>
#include "widget.h"
#include "ui_widget.h"

class HtmlEnd:public QWidget
{
public:
    void End();
    Ui::Widget *ui = Widget::mywidget->ui;
};

#endif // HTMLEND_H
