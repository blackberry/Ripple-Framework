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
#include "ripple.h"
#include "BuildServerManager.h"
#include <QGLWidget>
#include "ScrollHandler.h"

using namespace BlackBerry::Ripple;

const int Ripple::PROGRESS_BAR_HEIGHT = 23;

Ripple::Ripple(QWidget *parent, Qt::WFlags flags) : QMainWindow(parent, flags)
{
    init();
}

Ripple::~Ripple()
{
    if (_config != NULL)
    delete _config;

    if ( progressBar != NULL )
    delete progressBar;

    if ( webViewInternal != NULL )
    delete webViewInternal;
}

void Ripple::init(void)
{
    _config = ConfigData::getInstance();
    setAttribute(Qt::WA_DeleteOnClose);

    webViewInternal = new QtGraphicsStageWebView(this);
    webViewInternal->qtStageWebView()->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    webViewInternal->qtStageWebView()->settings()->enablePersistentStorage(_config->localStoragePath());
    webViewInternal->qtStageWebView()->settings()->setOfflineStoragePath(_config->localStoragePath());
    webViewInternal->qtStageWebView()->settings()->setOfflineWebApplicationCachePath(_config->localStoragePath());
    webViewInternal->qtStageWebView()->settings()->setOfflineStorageDefaultQuota(512000000);
    webViewInternal->qtStageWebView()->settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);
    webViewInternal->qtStageWebView()->settings()->setAttribute(QWebSettings::LocalContentCanAccessFileUrls, true);
    webViewInternal->qtStageWebView()->settings()->setAttribute(QWebSettings::LocalContentCanAccessFileUrls, true);
    webViewInternal->qtStageWebView()->settings()->setAttribute(QWebSettings::LocalContentCanAccessFileUrls, true);
#if QT_VERSION >= 0x040800
    webViewInternal->qtStageWebView()->settings()->setAttribute(QWebSettings::AcceleratedCompositingEnabled, true);
#endif    
    webViewInternal->qtStageWebView()->settings()->setWebSecurityEnabled(false);

    if (QGLFormat::hasOpenGL())
    {
        if (_config->webGLEnabled() == 1)
        {
            webViewInternal->qtStageWebView()->settings()->setAttribute(QWebSettings::WebGLEnabled, true);
        }
        
        if (_config->hardwareAccelerationEnabled() == 1)
        {
            QGLFormat format;
            format.setSampleBuffers(true);
            webViewInternal->setViewport(new QGLWidget(format));
            webViewInternal->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
            
            // init scroll handler
            _scrollHandler = new ScrollHandler(webViewInternal->qtStageWebView());
            webViewInternal->viewport()->installEventFilter(_scrollHandler);
        }
    }
    //Progress bar-------------------------
    progressBar = new QProgressBar(this);
    progressBar->setVisible(false);
    progressBar->setObjectName(QString::fromUtf8("progressBar"));
    //When the loading of a new page has started, show and reset the progress bar
    connect(webViewInternal, SIGNAL(loadStarted()), progressBar, SLOT( show() ));
    connect(webViewInternal, SIGNAL(loadStarted()), progressBar, SLOT( reset()));
    //Increment the progress bar as the page loads
    connect(webViewInternal, SIGNAL(loadProgress(int)), progressBar, SLOT(setValue(int))); 
    //When page is finished loading, hide the progress bar
    connect(webViewInternal, SIGNAL(loadFinished(bool)), progressBar, SLOT( hide() ));
    //--------------------------------------
    // init window

    QCoreApplication::setAttribute(Qt::AA_DontShowIconsInMenus);
    QSize size = _config->windowSize();
    resize(size);

    if (_config->windowState() == 1)
        setWindowState(Qt::WindowMaximized);

    //Set geometry for progressbar
    progressBar->setGeometry(QRect(0, (size.height() - PROGRESS_BAR_HEIGHT), size.width(), PROGRESS_BAR_HEIGHT));

    move(_config->windowPosition());

    webViewInternal->qtStageWebView()->load(QUrl(_config->toolingContent()));
    
    setCentralWidget(webViewInternal);

    //register webview
    connect(webViewInternal->qtStageWebView()->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(registerAPIs()));
  
    //stagewebview interfaces
    m_pStageViewHandler = new StageViewMsgHandler(this);
    m_pStageViewHandler->Register(webViewInternal->qtStageWebView());
    
    //start build server
    connect(BuildServerManager::getInstance(), SIGNAL(findUsablePort(int)), m_pStageViewHandler, SLOT(setServerPort(int))); 

    QFile cmd(_config->buildServiceCommand());
    if (cmd.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&cmd);
        m_pStageViewHandler->setServerPort(BuildServerManager::getInstance()->start(in.readLine(), _config->buildServicePort()));
        cmd.close();
    }
    else
    {
        qDebug() << "Can not open file:" << cmd.fileName() << "Error:" << cmd.error();
        cmd.close();
    }

}

void Ripple::closeEvent(QCloseEvent *event)
{
    _config->windowPosition(pos());
    if (this->windowState() != Qt::WindowMaximized)
        _config->windowSize(size());
    _config->windowState((this->windowState() == Qt::WindowMaximized) ? 1 : 0);
    _config->writeSettings();
    event->accept();
    BuildServerManager::getInstance()->stop();
}

void Ripple::registerAPIs()
{
    //register StageWebViewMsgHandler as JS object named stagewebview
    QWebFrame* frame = webViewInternal->qtStageWebView()->page()->mainFrame();
    frame->addToJavaScriptWindowObject(QString("stagewebview"), m_pStageViewHandler);
}

void Ripple::resizeEvent(QResizeEvent * e )
{
    QRect vRect(QPoint(0, 0), size());
    webViewInternal->scene()->setSceneRect(vRect);
    webViewInternal->qtStageWebView()->setGeometry(vRect);
	progressBar->setGeometry(QRect(0, (e->size().height() - PROGRESS_BAR_HEIGHT), e->size().width(), PROGRESS_BAR_HEIGHT));
    e->accept();
}

void Ripple::urlChanged(QUrl &url)
{
  
}
