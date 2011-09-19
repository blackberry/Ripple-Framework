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
#ifdef Q_WS_WIN
#include <windows.h>
#endif

BuildServerManager* BuildServerManager::_instance = 0;

BuildServerManager::BuildServerManager() : _serverProcess(0)
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

unsigned short BuildServerManager::start(QString server, int port)
{
    qDebug() << " command text:" << server << "port:" << port;
    unsigned short serverPort = 0;
    QStringList arguments = server.split(" ");
    QString portStr;

    portStr.setNum(validatePort(port));
    arguments.replaceInStrings(QString("$PORT"), portStr);

    server = "services/bin/" + arguments[0];
    arguments.removeAt(0);
    arguments.replaceInStrings("..", "services/bin/..");
#ifdef Q_WS_WIN
    server.append(".exe");
#endif
    QString tempDir = "/tmp";
#ifdef Q_WS_WIN
    tempDir = getenv("TEMP");
#endif
    QFile pidFile(tempDir + QString("/rbd_service.pid"));
    if (pidFile.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QString s_pidInfo = pidFile.readLine();
        if (s_pidInfo.split(";").length() > 1)
            serverPort = s_pidInfo.split(";")[1].toUInt();
        unsigned int pid = s_pidInfo.split(";")[0].toUInt();
#ifdef Q_WS_WIN
        HANDLE process = OpenProcess(SYNCHRONIZE, FALSE, pid);
        CloseHandle(process);
#else
        int process = 0;
        // run shell script to check if process is running
        QString psString("ps acx | grep " + QString(pid) + " 2>&1");
        if (system(psString.toAscii()) != 256)
            process = 1;
#endif
        if (process == 0)
        {
            qDebug() << "server:" << server << "arguments:" << arguments;
            _serverProcess->start(server, arguments);
            pidFile.close();
            pidFile.open(QIODevice::WriteOnly | QIODevice::Text);
            QString pidInfo = QString::number((int)_serverProcess->pid()) + ";" + portStr;
            pidFile.write(pidInfo.toAscii());
            pidFile.close();
        }
    }

    return serverPort;
}

void BuildServerManager::stop()
{
    if ( _serverProcess )
    {
        _serverProcess->close();
    }
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