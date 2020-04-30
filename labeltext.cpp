#include "labeltext.h"

#include <QHBoxLayout>

LabelText::LabelText(QWidget *parent) : QWidget(parent)
{
    setLayout(new QHBoxLayout(this));
    layout()->addWidget(&m_label);
    layout()->addWidget(&m_text);
}

void LabelText::setText(const QString & text,const QString & color)
{
    m_text.setColor(color);
    m_text.setText(text);
}

void LabelText::setLabel(const QString & label)
{
    m_label.setText(label);
}
