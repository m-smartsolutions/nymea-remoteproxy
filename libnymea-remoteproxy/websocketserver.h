/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*  Copyright 2013 - 2020, nymea GmbH
*  Contact: contact@nymea.io
*
*  This file is part of nymea.
*  This project including source code and documentation is protected by copyright law, and
*  remains the property of nymea GmbH. All rights, including reproduction, publication,
*  editing and translation, are reserved. The use of this project is subject to the terms of a
*  license agreement to be concluded with nymea GmbH in accordance with the terms
*  of use of nymea GmbH, available under https://nymea.io/license
*
*  GNU General Public License Usage
*  Alternatively, this project may be redistributed and/or modified under
*  the terms of the GNU General Public License as published by the Free Software Foundation,
*  GNU version 3. this project is distributed in the hope that it will be useful, but WITHOUT ANY
*  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
*  PURPOSE. See the GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License along with this project.
*  If not, see <https://www.gnu.org/licenses/>.
*
*  For any further details and any questions please contact us under contact@nymea.io
*  or see our FAQ/Licensing Information on https://nymea.io/license/faq
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QUrl>
#include <QUuid>
#include <QObject>
#include <QWebSocket>
#include <QWebSocketServer>
#include <QSslConfiguration>

#include "transportinterface.h"

namespace remoteproxy {

class WebSocketServer : public TransportInterface
{
    Q_OBJECT
public:
    explicit WebSocketServer(bool sslEnabled, const QSslConfiguration &sslConfiguration, QObject *parent = nullptr);
    ~WebSocketServer() override;

    QUrl serverUrl() const;
    void setServerUrl(const QUrl &serverUrl);

    bool running() const;

    QSslConfiguration sslConfiguration() const;

    void sendData(const QUuid &clientId, const QByteArray &data) override;
    void killClientConnection(const QUuid &clientId, const QString &killReason) override;

private:
    QUrl m_serverUrl;
    QWebSocketServer *m_server = nullptr;
    bool m_sslEnabled;
    QSslConfiguration m_sslConfiguration;
    bool m_enabled = false;

    QHash<QUuid, QWebSocket *> m_clientList;

private slots:
    void onClientConnected();
    void onClientDisconnected();
    void onTextMessageReceived(const QString &message);
    void onBinaryMessageReceived(const QByteArray &data);
    void onClientError(QAbstractSocket::SocketError error);
    void onAcceptError(QAbstractSocket::SocketError error);
    void onServerError(QWebSocketProtocol::CloseCode closeCode);

public slots:
    bool startServer() override;
    bool stopServer() override;

};

}

#endif // WEBSOCKETSERVER_H
