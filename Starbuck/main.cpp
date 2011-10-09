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
#include "starbuck.h"
#include <QtGui/QApplication>
#include "RemoteDebugger.h"
#ifdef Q_WS_WIN
#include <windows.h>
#include <tchar.h>
#endif

using namespace BlackBerry::Starbuck;


void write(const char * msg, QString type)
{
    QString tempDir = "/tmp";
#ifdef Q_WS_WIN
    tempDir = getenv("TEMP");
#endif
    QString fn("ripple_log_" + QDate::currentDate().toString(Qt::ISODate) + ".txt");
    QFile file(QString(tempDir + QDir::separator()) + fn);
    if (!file.open(QIODevice::Append | QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&file);
    out << QDateTime::currentDateTime().toString() << ":" << type << ":" << msg << "\n";
    file.close();
}

void fileDbgMsgOutput(QtMsgType type, const char *msg)
{
    switch (type) {
    case QtDebugMsg:
        write(msg, "Debug");
        break;
    case QtWarningMsg:
        write(msg, "Warning");
        break;
    case QtCriticalMsg:
        write(msg, "Critical");
        break;
    case QtFatalMsg:
        write(msg, "Fatal");
        abort();
   }
}

#ifdef Q_WS_WIN
int CALLBACK WinMain(
  __in  HINSTANCE hInstance,
  __in  HINSTANCE hPrevInstance,
  __in  LPSTR lpCmdLine,
  __in  int nCmdShow
)
#else
int main(int argc, char *argv[])
#endif
{
    qInstallMsgHandler(fileDbgMsgOutput);
#ifdef Q_WS_WIN
    TCHAR cmdline[4096];
    TCHAR* argv[4096];
    int argc = 0;
    _tcscpy(cmdline, GetCommandLine());
    argv[argc] = _tcstok(cmdline, TEXT(" \t"));
    while(argv[argc] != 0)
    {
        argc++ ;
        argv[argc] = _tcstok(0, TEXT(" \t"));
    }
#endif    
    QApplication app(argc, argv);
    app.setApplicationName("Ripple");
    app.setOrganizationName("Research in Motion");
    app.setOrganizationDomain("blackberry.com");
    
    RemoteDebugger *remoteDebugger = new RemoteDebugger();
    
    if (argc == 3)
    {
        QString paramName = argv[1];
        QString paramVal = argv[2];
        
        if (paramName == "-inspect")
        {
            remoteDebugger->show(paramVal);
        }
    }
    else
    {
        Starbuck *mainWin = new Starbuck;
        mainWin->show();
    }
    return app.exec();
}