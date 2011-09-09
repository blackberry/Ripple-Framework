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

#include "stdafx.h"
#include "BuildServerManager.h"
#include "PortScanner.h"

BuildServerManager* BuildServerManager::_instance = 0;

BuildServerManager::BuildServerManager()
{
    _serverProcess = new QProcess(this);
    connect(_serverProcess, SIGNAL(started()), this, SLOT(serverStarted()));
    connect(_serverProcess, SIGNAL(error(QProcess::ProcessError)), this, SLOT(onError(QProcess::ProcessError)));
    connect(_serverProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(readStdOutput()));
    connect(_serverProcess, SIGNAL(readyReadStandardError()), this, SLOT(readStdError()));
}

BuildServerManager::~BuildServerManager(void)
{
}

BuildServerManager* BuildServerManager::getInstance()
{
    if ( _instance == 0 )
        _instance = new BuildServerManager();
    return _instance;
}

void BuildServerManager::start(QString server, int port)
{
    QStringList arguments = server.split(" ");
    QString str;

    str.setNum(validatePort(port));
    arguments.replaceInStrings(QString("$PORT"), str);

    QFile command(server);

    server = arguments[0];
    QDir dir = server;
    server = dir.absolutePath();
    arguments.removeAt(0);
    arguments.join("");
#ifdef Q_WS_WIN
    server.append(".exe");
#endif
    _serverProcess->start(server, arguments);
}

void BuildServerManager::stop()
{
    if ( _serverProcess )
        _serverProcess->close();
    delete _instance;
    _instance = 0;
}

int BuildServerManager::validatePort(int port)
{
    PortScanner scanner;
    int usablePort = scanner.findUsablePort( (unsigned short)port);
    emit findUsablePort(usablePort);
    return usablePort;
}

void BuildServerManager::serverStarted()
{
    qDebug() << "Build Server started";
}

void BuildServerManager::onError(QProcess::ProcessError err)
{
    if ( err == QProcess::Crashed )
        qDebug() << "Server is killed by Ripple";
    else
        qDebug() << "Build Server can not be started. Error code: " << err;
}

void BuildServerManager::readStdOutput()
{
    qDebug() << _serverProcess->readAllStandardOutput();
}

void BuildServerManager::readStdError()
{
    qDebug() << _serverProcess->readAllStandardError();
}