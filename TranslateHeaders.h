#ifndef TRANSLATEHEADERS_H
#define TRANSLATEHEADERS_H

#include<bits/stdc++.h>
#include <QWidget>
#include "widget.h"
#include "ui_widget.h"

class TranslateHeaders:public QWidget
{
public:
    void tr_head(std::string s);
    Ui::Widget *ui = Widget::mywidget->ui;
};

#endif // TRANSLATEHEADERS_H
