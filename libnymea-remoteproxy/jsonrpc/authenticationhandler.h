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

#ifndef AUTHENTICATIONHANDLER_H
#define AUTHENTICATIONHANDLER_H

#include <QObject>

#include "jsonhandler.h"
#include "authentication/authenticationreply.h"

namespace remoteproxy {

class TransportClient;

class AuthenticationHandler : public JsonHandler
{
    Q_OBJECT
public:
    explicit AuthenticationHandler(QObject *parent = nullptr);
    ~AuthenticationHandler() override = default;

    QString name() const override;

    Q_INVOKABLE JsonReply *Authenticate(const QVariantMap &params, TransportClient *transportClient);

private:
    QHash<AuthenticationReply *, JsonReply *> m_runningAuthentications;

private slots:
    void onAuthenticationFinished();


};

}

#endif // AUTHENTICATIONHANDLER_H
