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

using namespace BlackBerry::Starbuck;


RemoteDebugger::RemoteDebugger(QWidget *parent, Qt::WFlags flags) : QMainWindow(parent, flags)
{
    init();
}

RemoteDebugger::~RemoteDebugger()
{
    if ( debugerView != NULL )
    delete debugerView;
}

void RemoteDebugger::init(void)
{
    setAttribute(Qt::WA_DeleteOnClose);
    debugerView = new QWebView(this);
	debugerView->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    debugerView->settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);
    debugerView->settings()->setAttribute(QWebSettings::LocalContentCanAccessFileUrls, true);
    debugerView->settings()->setWebSecurityEnabled(false);
    debugerView->load(QUrl("http://localhost:9292/webkit/inspector/inspector.html?page=1"));
    setCentralWidget(debugerView);
}

void RemoteDebugger::closeEvent(QCloseEvent *event)
{
}

void RemoteDebugger::resizeEvent(QResizeEvent * e )
{
    e->accept();
}
