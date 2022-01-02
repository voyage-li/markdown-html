#ifndef TRANSLATETEXT_H
#define TRANSLATETEXT_H
#include<bits/stdc++.h>
#include<QString>
#include <QWidget>
#include "widget.h"
#include "ui_widget.h"

class TranslateText: public QWidget
{
public:
    void tr_text(std::string s);
    Ui::Widget *ui = Widget::mywidget->ui;
};

#endif // TRANSLATETEXT_H
