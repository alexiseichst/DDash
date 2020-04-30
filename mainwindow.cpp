#include "mainwindow.h"
#include "svgrender.h"
#include "button.h"

#include <QVBoxLayout>
#include <QFrame>
#include <QHBoxLayout>
#include <QSizePolicy>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_settingsBar(nullptr),
      m_widgetList(nullptr)
{
    SvgRender speed("SPEEDOMETER");
    setWindowIcon(speed.svgToIcon(100,100,this));
    setCentralWidget(new QWidget(this));
    centralWidget()->setLayout(new QVBoxLayout);
    setStyleSheet("QMainWindow { background: white; }");
    resize(500,500);
    setMinimumSize(500,500);

    m_widgetList = new QListWidget(this);
    m_widgetList->setDragDropMode(QAbstractItemView::InternalMove);
    dynamic_cast<QVBoxLayout*>(centralWidget()->layout())->addWidget(m_widgetList);

    m_settingsBar = new QWidget(this);
    m_settingsBar->setFixedHeight(60);
    m_settingsBar->setLayout(new QHBoxLayout);
    dynamic_cast<QVBoxLayout*>(centralWidget()->layout())->addWidget(m_settingsBar,Qt::AlignBottom);

    addSettingsButton("ADD","ADD");
    m_buttonAction.insert("ADD",std::bind(&MainWindow::addClicked,this));
}

void MainWindow::addActionWidget(QWidget *action)
{
    QListWidgetItem *item = new QListWidgetItem(m_widgetList);
    item->setSizeHint(QSize(item->sizeHint().width(), 60));
    m_widgetList->addItem(item);
    action->setFixedHeight(60);
    m_widgetList->setItemWidget(item,action);
}

void MainWindow::addSettingsButton(const QString & name,
                       const QString & icon)
{
    Button* button = new Button(this);
    SvgRender svgicon(icon);
    connect(button,&Button::clicked,this,&MainWindow::buttonSettingsBarClicked);
    button->setObjectName(name);
    button->setFixedSize(50,50);
    button->setIcon(svgicon.svgToIcon(50,50,this));
    button->setIconSize(QSize(50,50));
    m_settingsBar->layout()->addWidget(button);
}

void MainWindow::buttonSettingsBarClicked()
{
    Button* button = dynamic_cast<Button*>(sender());
    m_buttonAction[button->objectName()]();
}
