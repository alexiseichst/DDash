#include "labelstatus.h"
#include "svgrender.h"

#include <QByteArray>
#include <QHBoxLayout>
#include <QIcon>

LabelStatus::LabelStatus(QWidget *parent) :
    QWidget(parent)
{
    setLayout(new QHBoxLayout(this));
    layout()->addWidget(&m_label);
    layout()->addWidget(&m_status);

    SvgRender svgTrue("SUCCESS");
    m_iconTrue = svgTrue.svgToPixamp(40,40,this);

    SvgRender svgFalse("ERROR");
    m_iconFalse = svgFalse.svgToPixamp(40,40,this);
}

void LabelStatus::setLabel(const QString &label)
{
    m_label.setText(label);
}

void LabelStatus::setStatus(const bool &status)
{
    m_status.setPixmap(status ? m_iconTrue : m_iconFalse);
}
