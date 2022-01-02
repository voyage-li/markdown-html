#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    static Widget *mywidget;
    Ui::Widget *ui;
    std::vector<std::string> content;
    int islist(int i);//判断转换列表
    int blankjudge(int a);
    int handlelist(int i, int blanklast);
    int now=0;//记录判断的位置
    void handlequote(int i,int last);
    int isquote(int i);

protected:
    void closeEvent(QCloseEvent *event);

private:
    bool issave=false;
    bool isrun=false;
};
#endif // WIDGET_H
