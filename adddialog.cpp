#include "adddialog.h"
#include "action.h"

#include <QVBoxLayout>

AddDialog::AddDialog(QWidget *parent,QMap<QString,std::function<Action*(const QString & name,
                                                                        const QString & uuid,
                                                                        QObject* parent)>> str_to_action) :
    QDialog(parent),
    m_strToAction(str_to_action)
{
    setStyleSheet("QDialog { background: white; }");
    setLayout(new QVBoxLayout);
    dynamic_cast<QVBoxLayout*>(layout())->setAlignment(Qt::AlignTop);
    resize(400,400);
    setMinimumSize(400,400);

    m_typeCombo.setParent(this);
    dynamic_cast<QVBoxLayout*>(layout())->addWidget(&m_typeCombo,Qt::AlignTop);
    for (const QString k : m_strToAction.keys())
    {
        m_typeCombo.addItem(k,k);
    }
}
