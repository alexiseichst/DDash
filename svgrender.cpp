#include "svgrender.h"
#include "svgicon.h"

#include <QSvgRenderer>
#include <QObject>
#include <QPixmap>
#include <QIcon>
#include <QPainter>
#include <QByteArray>

SvgRender::SvgRender(const QString &name):
    m_name(name)
{
    m_svg.insert("SPEEDOMETER",SPEEDOMETER);
    m_svg.insert("ERROR",ERROR);
    m_svg.insert("SUCCESS",SUCCESS);
    m_svg.insert("ADD",ADD);
}

QIcon SvgRender::svgToIcon(const int &w,
                const int &h,
                QObject *parent) const
{
    return QIcon(svgToPixamp(w,h,parent));
}

QPixmap SvgRender::svgToPixamp(const int &w,
                    const int &h,
                    QObject *parent) const
{
    QSvgRenderer svg(QByteArray(m_svg[m_name]),parent);
    QPixmap pm(w,h);
    pm.fill(Qt::transparent);
    QPainter painter(&pm);
    svg.render(&painter, pm.rect());
    return pm;
}
