#pragma once

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    void addActionWidget(QWidget *action);

private:
    void addSettingsButton(const QString & name,
                           const QString & icon);
    QWidget* m_settingsBar;

signals:

};
