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
#include "RemoteDebugger.h"



RemoteDebugger::RemoteDebugger(QWidget *parent, Qt::WFlags flags) : QMainWindow(parent, flags)
{
    init();
}

RemoteDebugger::~RemoteDebugger()
{
    if ( debuggerView != NULL )
    delete debuggerView;
}

void RemoteDebugger::init(void)
{
    setAttribute(Qt::WA_DeleteOnClose);
    debuggerView = new QWebView(this);
	debuggerView->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, false);
    debuggerView->settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);
    debuggerView->settings()->setAttribute(QWebSettings::LocalContentCanAccessFileUrls, true);
    debuggerView->settings()->setAttribute(QWebSettings::OfflineStorageDatabaseEnabled, false);
    debuggerView->settings()->enablePersistentStorage("/tmp");
    debuggerView->settings()->setOfflineStoragePath("/tmp");
    
    debuggerView->settings()->setWebSecurityEnabled(false);
    setCentralWidget(debuggerView);
}

void RemoteDebugger::show()
{
    debuggerView->load(QUrl("http://localhost:9292/webkit/inspector/inspector.html?page=1"));
    QWidget::show();
}

void RemoteDebugger::closeEvent(QCloseEvent *event)
{
}

void RemoteDebugger::resizeEvent(QResizeEvent * e )
{
    e->accept();
}
