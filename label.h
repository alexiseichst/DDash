#ifndef LABEL_H
#define LABEL_H

#include <QLabel>

class Label : public QLabel
{
    Q_OBJECT
public:
    explicit Label(QWidget *parent = nullptr);
    void setColor(const QString & color);

private:
    const QString m_style;

signals:

};

#endif // LABEL_H
