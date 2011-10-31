/*
* Copyright 2010-2011 Research In Motion Limited.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include <QTime>
#include "PortScanner.h"

PortScanner::PortScanner()
{
    // random number generator init
    qsrand(QTime::currentTime().msec());
}

PortScanner::~PortScanner()
{

}

// simple function to find open port on system
unsigned short PortScanner::findUsablePort(unsigned short port)
{
    bool portFound = false;

    QTcpServer *server = new QTcpServer();

    while (!portFound)
    {
        if (!server->listen(QHostAddress::LocalHost, port))
        {
            qDebug() << "Cannot start server, port" << port << "in use.";
            // try a random port
            port = qrand() % 65535;
        }
        else
            portFound = true;
    }

    if (server) delete server;

    return port;
}
