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

using namespace BlackBerry::Starbuck;

const int Starbuck::PROGRESS_BAR_HEIGHT = 23;

Starbuck::Starbuck(QWidget *parent, Qt::WFlags flags) : QMainWindow(parent, flags)
{
    init();
}

Starbuck::~Starbuck()
{
    if (_config != NULL)
    delete _config;

    if ( progressBar != NULL )
    delete progressBar;

    if ( webViewInternal != NULL )
    delete webViewInternal;
}

void Starbuck::init(void)
{
    _config = ConfigData::getInstance();
    setAttribute(Qt::WA_DeleteOnClose);

    QSize size = _config->windowSize();

    webViewInternal = new QtStageWebView;
	webViewInternal->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
	webViewInternal->settings()->enablePersistentStorage(_config->localStoragePath());

    //Progress bar-------------------------
    progressBar = new QProgressBar(webViewInternal);
    progressBar->setObjectName(QString::fromUtf8("progressBar"));
    //When the loading of a new page has started, show and reset the progress bar
    connect(webViewInternal, SIGNAL(loadStarted()), progressBar, SLOT( show() ));
    connect(webViewInternal, SIGNAL(loadStarted()), progressBar, SLOT( reset()));
    //Increment the progress bar as the page loads
    connect(webViewInternal, SIGNAL(loadProgress(int)), progressBar, SLOT(setValue(int))); 
    //When page is finished loading, hide the progress bar
    connect(webViewInternal, SIGNAL(loadFinished(bool)), progressBar, SLOT( hide() ));
    //--------------------------------------
    resize(size);
    //Set geometry for progressbar
    progressBar->setGeometry(QRect(0, (size.height() - PROGRESS_BAR_HEIGHT), size.width(), PROGRESS_BAR_HEIGHT));

    move(_config->windowPosition());

    webViewInternal->load(QUrl(_config->toolingContent()));

    setCentralWidget(webViewInternal);

    //register webview
    connect(webViewInternal->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(registerAPIs()));
  
    //stagewebview interfaces
    m_pStageViewHandler = new StageViewMsgHandler(this);
    m_pStageViewHandler->Register(webViewInternal);
}

void Starbuck::closeEvent(QCloseEvent *event)
{
    _config->windowPosition(pos());
    _config->windowSize(size());
    event->accept();
}

void Starbuck::registerAPIs()
{
    //register StageWebViewMsgHandler as JS object named stagewebview
    QWebFrame* frame = webViewInternal->page()->mainFrame();
    frame->addToJavaScriptWindowObject(QString("stagewebview"), m_pStageViewHandler);
}

void Starbuck::resizeEvent(QResizeEvent * e )
{
    e->accept();
}
