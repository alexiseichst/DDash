#include "adddialog.h"
#include "action.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>

AddDialog::AddDialog(QWidget *parent,QMap<QString,std::function<Action*(const QString &name,
                                                                        const QString &uuid,
                                                                        QObject* parent)>> str_to_action) :
    QDialog(parent),
    m_strToAction(str_to_action),
    m_editWidget(nullptr)
{
    setStyleSheet("QDialog { background: white; }");
    setLayout(new QVBoxLayout);
    dynamic_cast<QVBoxLayout*>(layout())->setAlignment(Qt::AlignTop);
    resize(400,200);
    setMinimumSize(400,200);

    m_typeCombo.setParent(this);
    connect(&m_typeCombo,SIGNAL(currentIndexChanged(const QString)),this,SLOT(currentIndexChanged(const QString)));
    dynamic_cast<QVBoxLayout*>(layout())->addWidget(&m_typeCombo,Qt::AlignTop);
    for (const QString k : m_strToAction.keys())
    {
        m_typeCombo.addItem(k,k);
    }

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Save
                                        | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    dynamic_cast<QVBoxLayout*>(layout())->addWidget(buttonBox);
}

void AddDialog::currentIndexChanged(const QString &text)
{
    const Action* a = m_strToAction[text]("name","uuid",nullptr);
    QVariantMap map = a->getConfigMap();
    QGridLayout* layout = nullptr;

    map.remove("application");
    map.remove("uuid");
    map.remove("type");

    if (m_editWidget) delete m_editWidget;
    m_editWidget = new QWidget(this);
    layout = new QGridLayout(m_editWidget);
    m_editWidget->setLayout(layout);
    for (QString k :map.keys())
    {
        QWidget* w = new QLabel(QString("%1: ").arg(k),this);
        layout->addWidget(w,layout->rowCount(),0);

        w = new QLineEdit(this);
        w->setObjectName(k);
        layout->addWidget(w,layout->rowCount()-1,1);
    }
    dynamic_cast<QVBoxLayout*>(this->layout())->addWidget(m_editWidget);

    delete a;
    a = nullptr;
}

QVariantMap AddDialog::getActionMap() const
{
    QVariantMap rt;
    QLayout* layout = m_editWidget->layout();
    for (int i=0;i<layout->count();i++)
    {
        QWidget* widget = layout->itemAt(i)->widget();
        QLineEdit* line_edit = dynamic_cast<QLineEdit*>(widget);
        if (line_edit) rt.insert(line_edit->objectName(),line_edit->text());
    }
    rt.insert("type",m_typeCombo.currentText());
    return rt;
}
