#ifndef IPUTILS_H
#define IPUTILS_H

#include <QHostInfo>
#include <QNetworkInterface>
#include <QString>

namespace SoundTest {

class IpUtils
{
public:
    IpUtils();

    static QList<QHostAddress> getIPAddresses();
    static QString ipToQString(QHostAddress addr);
};

} // namespace SoundTest

#endif // IPUTILS_H
