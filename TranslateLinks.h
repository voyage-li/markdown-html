#ifndef TRANSLATELINKS_H
#define TRANSLATELINKS_H
#include<bits/stdc++.h>
#include<QString>
#include <QWidget>
#include "widget.h"
#include "ui_widget.h"

class TranslateLinks: public QWidget
{
public:
    void tr_link(std::string s);
    Ui::Widget *ui = Widget::mywidget->ui;
};

#endif // TRANSLATELINKS_H
