#include "Change.h"

QString Change::StrtoQstr(std::string str)
{
    return QString::fromLocal8Bit(str.data());
}

std::string Change::QstrtoStr(QString qstr)
{
    QByteArray cdata = qstr.toLocal8Bit();
    return std::string(cdata);
}
