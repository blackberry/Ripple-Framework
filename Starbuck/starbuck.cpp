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
#include "BuildServerManager.h"
#include <QGLWidget>
#include "ScrollHandler.h"

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

void Starbuck::enableHardwareAcceleration()
{
    if (!_hwToggleMenuItem->isChecked())
    {
        _config->hardwareAccelerationEnabled(0);
        _hwToggleMenuItem->setChecked(false);
    }
    else
    {
        _config->hardwareAccelerationEnabled(1);        
        _hwToggleMenuItem->setChecked(true);
    }
    
    QMessageBox::information(this, "Restart Ripple", "Please restart Ripple for changes to take effect");
}

void Starbuck::enableWebGL()
{
    if (!_webGLToggleMenuItem->isChecked())
    {
        _config->webGLEnabled(0);        
        _webGLToggleMenuItem->setChecked(false);
        webViewInternal->qtStageWebView()->settings()->setAttribute(QWebSettings::WebGLEnabled, false);
    }
    else
    {
        _config->webGLEnabled(1);
        _webGLToggleMenuItem->setChecked(true);
        webViewInternal->qtStageWebView()->settings()->setAttribute(QWebSettings::WebGLEnabled, true);
    }
}

void Starbuck::init(void)
{
    
    // create menu items
    _optionsMenu = menuBar()->addMenu("Options");
    _hwToggleMenuItem = _optionsMenu->addAction("Enable Hardware Acceleration", this, SLOT(enableHardwareAcceleration()));
    _hwToggleMenuItem->setCheckable(true);
    _webGLToggleMenuItem = _optionsMenu->addAction("Enable WebGL", this, SLOT(enableWebGL()));
    _webGLToggleMenuItem->setCheckable(true);
    
    _config = ConfigData::getInstance();
    setAttribute(Qt::WA_DeleteOnClose);

    webViewInternal = new QtGraphicsStageWebView(this);
	webViewInternal->qtStageWebView()->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
	webViewInternal->qtStageWebView()->settings()->enablePersistentStorage(_config->localStoragePath());
    webViewInternal->qtStageWebView()->settings()->setOfflineStorageDefaultQuota(512000000);
    webViewInternal->qtStageWebView()->settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);
    webViewInternal->qtStageWebView()->settings()->setAttribute(QWebSettings::LocalContentCanAccessFileUrls, true);
#if QT_VERSION >= 0x040800
    webViewInternal->qtStageWebView()->settings()->setAttribute(QWebSettings::AcceleratedCompositingEnabled, true);
#endif    
    webViewInternal->qtStageWebView()->settings()->setWebSecurityEnabled(false);

    if (_config->webGLEnabled() == 1)
    {
        _webGLToggleMenuItem->setChecked(true);
        webViewInternal->qtStageWebView()->settings()->setAttribute(QWebSettings::WebGLEnabled, true);
    }
    
    if (_config->hardwareAccelerationEnabled() == 1)
    {
        _hwToggleMenuItem->setChecked(true);
        _GLWidget = new QGLWidget;
        QGLFormat format;
        format.setSampleBuffers(2);
        format.setRgba(true);
        format.setDoubleBuffer(true);
        _GLWidget->setFormat(format);
        webViewInternal->setViewport(_GLWidget);
        webViewInternal->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
        _GLWidget->makeCurrent();
        
        // init scroll handler
        _scrollHandler = new ScrollHandler(webViewInternal->qtStageWebView());
        _GLWidget->installEventFilter(_scrollHandler);

    }
    
    //Progress bar-------------------------
    progressBar = new QProgressBar(this);
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

    webViewInternal->qtStageWebView()->load(QUrl("http://www.joystiq.com"));
    
    webViewInternal->qtStageWebView()->setGeometry(this->geometry());
    
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

void Starbuck::closeEvent(QCloseEvent *event)
{
    _config->windowPosition(pos());
    if (this->windowState() != Qt::WindowMaximized)
        _config->windowSize(size());
    _config->windowState((this->windowState() == Qt::WindowMaximized) ? 1 : 0);
    _config->writeSettings();
    event->accept();
    BuildServerManager::getInstance()->stop();
}

void Starbuck::registerAPIs()
{
    //register StageWebViewMsgHandler as JS object named stagewebview
    QWebFrame* frame = webViewInternal->qtStageWebView()->page()->mainFrame();
    frame->addToJavaScriptWindowObject(QString("stagewebview"), m_pStageViewHandler);
}

void Starbuck::resizeEvent(QResizeEvent * e )
{
	progressBar->setGeometry(QRect(0, (e->size().height() - PROGRESS_BAR_HEIGHT), e->size().width(), PROGRESS_BAR_HEIGHT));
    e->accept();
}
