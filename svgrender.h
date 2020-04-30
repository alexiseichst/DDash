#pragma once

#include <QString>
#include <QMap>
#include <QPixmap>
#include <QIcon>

class QObject;

class SvgRender
{
private:
    QMap<QString,const char *> m_svg;
    const QString m_name;

public:
    explicit SvgRender(const QString &name);
    QIcon svgToIcon(const int &w,
                    const int &h,
                    QObject *parent = nullptr) const;
    QPixmap svgToPixamp(const int &w,
                        const int &h,
                        QObject *parent = nullptr) const;
};
