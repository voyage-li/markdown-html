#ifndef TRANSLATE_H
#define TRANSLATE_H

#include<bits/stdc++.h>
#include <QWidget>
#include "widget.h"
#include "ui_widget.h"

class Translate:public QWidget
{
public:
    void translate(std::vector<std::string> s);
    Ui::Widget *ui = Widget::mywidget->ui;
};

#endif // TRANSLATE_H
