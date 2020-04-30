#pragma once

#include <QObject>
#include <QPixmap>

#include "label.h"

class LabelStatus : public QWidget
{
    Q_OBJECT
public:
    explicit LabelStatus(QWidget *parent = nullptr);
    void setLabel(const QString &label);
    void setStatus(const bool &status);

private:
    Label m_label;
    Label m_status;
    QPixmap m_iconTrue;
    QPixmap m_iconFalse;

};
