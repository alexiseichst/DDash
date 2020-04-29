#include "mainwindow.h"
#include "svgrender.h"
#include "button.h"

#include <QVBoxLayout>
#include <QFrame>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_settingsBar(nullptr)
{
    SvgRender speed("SPEEDOMETER");
    setWindowIcon(speed.svgToIcon(100,100,this));
    setCentralWidget(new QWidget(this));
    centralWidget()->setLayout(new QVBoxLayout);
    setStyleSheet("QMainWindow { background: white; }");
    resize(500,200);

    m_settingsBar = new QWidget(this);
    m_settingsBar->setLayout(new QHBoxLayout);
    centralWidget()->layout()->addWidget(m_settingsBar);
    //addSettingsButton("ADD","ADD");
}

void MainWindow::addActionWidget(QWidget *action)
{
    static bool first = true;
    QVBoxLayout* layout = dynamic_cast<QVBoxLayout*>(centralWidget()->layout());
    if (!first)
    {
        QFrame* hFrame = new QFrame;
        hFrame->setFrameShape(QFrame::HLine);
        layout->insertWidget(0,hFrame);
    }
    layout->insertWidget(0,action);
    first = false;
}

void MainWindow::addSettingsButton(const QString & name,
                       const QString & icon)
{
    Button* button = new Button(this);
    SvgRender svgicon(icon);
    button->setObjectName(name);
    button->setFixedSize(100,100);
    button->setIcon(svgicon.svgToIcon(100,100,this));
    button->setIconSize(QSize(100,100));
    m_settingsBar->layout()->addWidget(button);
}
