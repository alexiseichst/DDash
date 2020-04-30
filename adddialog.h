#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <QMap>
#include <QString>
#include <QComboBox>

class Action;

class AddDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddDialog(QWidget *parent,QMap<QString,std::function<Action*(const QString & name,
                                                                          const QString & uuid,
                                                                          QObject* parent)>> str_to_action);

private:
    const QMap<QString,std::function<Action*(const QString & name,
                                             const QString & uuid,
                                             QObject* parent)>> m_strToAction;
    QComboBox m_typeCombo;

signals:

};

#endif // ADDDIALOG_H
