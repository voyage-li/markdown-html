#ifndef TRANSLATEIMAGES_H
#define TRANSLATEIMAGES_H

#include<bits/stdc++.h>
#include <QWidget>
#include "widget.h"
#include "ui_widget.h"

class TranslateImages: public QWidget
{
public:
    void tr_image(std::string s);
    Ui::Widget *ui = Widget::mywidget->ui;
};

#endif // TRANSLATEIMAGES_H
