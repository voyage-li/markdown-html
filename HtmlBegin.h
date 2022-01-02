#ifndef HTMLBEGIN_H
#define HTMLBEGIN_H

#include<bits/stdc++.h>
#include <QWidget>
#include<QFile>
#include "widget.h"
#include "ui_widget.h"

class HtmlBegin: public QWidget
{
public:
    void Begin();
    Ui::Widget *ui = Widget::mywidget->ui;

private:
};

#endif
