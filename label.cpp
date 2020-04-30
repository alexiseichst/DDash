#include "label.h"

Label::Label(QWidget *parent) :
    QLabel(parent),
    m_style("font: 10pt;")
{
    setStyleSheet(m_style);
}

void Label::setColor(const QString &color)
{
    setStyleSheet(QString("%1 ; color:%2;").arg(m_style,color));
}
