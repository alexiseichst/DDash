#pragma once

#include <QMainWindow>
#include <QListWidget>
#include <QMap>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    void addActionWidget(QWidget *action);

signals:
    void addClicked();

private:
    void addSettingsButton(const QString & name,
                           const QString & icon);
    QWidget* m_settingsBar;
    QListWidget* m_widgetList;
    QMap<QString,std::function<void(void)>> m_buttonAction;

private slots:
    void buttonSettingsBarClicked();

};
