#pragma once

#include <QWidget>
#include "label.h"

class LabelText : public QWidget
{
    Q_OBJECT
public:
    explicit LabelText(QWidget *parent = nullptr);

public:
    void setText(const QString & text,const QString & color = "black");
    void setLabel(const QString & label);

private:
    Label m_label;
    Label m_text;

signals:

};
