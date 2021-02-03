/*################################################################################
#   TargomanCommon: Primitive but usefull tools for Targoman
#
#   Copyright 2014-2021 by ITRC <http://itrc.ac.ir>
#
#   This file is part of Targoman.
#
#   Targoman is free software: you can redistribute it and/or modify
#   it under the terms of the GNU Lesser General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   Targoman is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU Lesser General Public License for more details.
#
#   You should have received a copy of the GNU Lesser General Public License
#   along with Targoman. If not, see <http://www.gnu.org/licenses/>.
################################################################################*/
/**
 * @author S. Mohammad M. Ziabary <ziabary@targoman.com>
 */

#ifndef TARGOMAN_COMMON_CONFIGURATION_PRIVATE_CLSLEGACYCONFIGOVERTCP_H
#define TARGOMAN_COMMON_CONFIGURATION_PRIVATE_CLSLEGACYCONFIGOVERTCP_H

#include <QThread>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QTime>
#include "Configuration/tmplConfigurable.h"
#include "clsConfigManager_p.h"
#include "clsBaseConfigOverNet.h"
#include "intfConfigManagerOverNet.hpp"

namespace Targoman {
namespace Common {
namespace Configuration {
namespace Private {


/******************************************************************************/
class clsLegacyConfigOverTCP : public intfConfigManagerOverNet
{
    Q_OBJECT
public:
    clsLegacyConfigOverTCP(clsConfigManagerPrivate& _configManager);
    ~clsLegacyConfigOverTCP();
};

/******************************************************************************/
class clsLegacyConfigOverTCPServer : public QTcpServer
{
    Q_OBJECT
public:
    clsLegacyConfigOverTCPServer(clsConfigManagerPrivate& _configManager);

private:
    void incomingConnection(qintptr _socketDescriptor);

private slots:
    void slotClientDisconnected();

private:
    clsConfigManagerPrivate&          ConfigManagerPrivate;
    quint16                           ConnectedClients;
};

/******************************************************************************/
class clsClientThread : public QThread, public clsBaseConfigOverNet
{
  Q_OBJECT
public:
  clsClientThread(qintptr _socketDescriptor,
                  clsConfigManagerPrivate& _configManager,
                  QObject* _parent);

private:
  void run();
  void sendError(enuReturnType::Type _type, const QString& _message);
  void sendResult(const QString &_data);

private slots:
  void slotReadyRead();
  void slotDisconnected();

signals:
  void error(QTcpSocket::SocketError socketerror);

private:
  qintptr                    SocketDescriptor;
  QTcpSocket*                Socket;
};

}
}
}
}
#endif // TARGOMAN_COMMON_CONFIGURATION_PRIVATE_CLSLEGACYCONFIGOVERTCP_H
