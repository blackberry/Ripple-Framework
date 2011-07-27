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

  if ( webView != NULL )
    delete webView;
}

void Starbuck::init(void)
{
  _config = ConfigData::getInstance();
  setAttribute(Qt::WA_DeleteOnClose);
  webView = new QWebView(); 

#ifdef NDEBUG //cmake definition for relase build
  webView->setContextMenuPolicy(Qt::NoContextMenu);
#else
	webView->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
#endif

  //Enable local persistent storage for local database
  webView->settings()->enablePersistentStorage(_config->localStoragePath());

  QSize size = _config->windowSize();

  webViewInternal = new QtStageWebView(webView);

  //Progress bar-------------------------
  progressBar = new QProgressBar(webView);
  progressBar->setObjectName(QString::fromUtf8("progressBar"));
  //When the loading of a new page has started, show and reset the progress bar
  connect(webView, SIGNAL(loadStarted()), progressBar, SLOT( show() ));
  connect(webView, SIGNAL(loadStarted()), progressBar, SLOT( reset()));
  //Increment the progress bar as the page loads
  connect(webView, SIGNAL(loadProgress(int)), progressBar, SLOT(setValue(int))); 
  //When page is finished loading, hide the progress bar
  connect(webView, SIGNAL(loadFinished(bool)), progressBar, SLOT( hide() ));
  //--------------------------------------
  resize(size);
  //Set geometry for progressbar
  progressBar->setGeometry(QRect(0, (size.height() - PROGRESS_BAR_HEIGHT), size.width(), PROGRESS_BAR_HEIGHT));

  move(_config->windowPosition());

  webView->load(QUrl(_config->toolingContent()));

  setCentralWidget(webView);

  //register webview
  connect(webView->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(registerAPIs()));
  connect(webViewInternal->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(registerInternalAPIs()));
  
  //stagewebview interfaces
  m_pStageViewHandler = new StageViewMsgHandler(this);
  m_pStageViewHandler->Register(webViewInternal);

  //XHR message handler
  //m_pXHRHandler = new XHRMsgHandler(this, webView);
  //m_pXHRHandler->Register(webViewInternal);
  //initialize IPCBridge and register XHRHandler
  //QString ssm = QString("StarbuckSM");
  //m_pBridge = new IPCBridge(ssm, this);
  //m_pBridge->RegisterMessageHandler(m_pXHRHandler);
  //m_pBridge->Start();
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
  QWebFrame* frame = webView->page()->mainFrame();
  frame->addToJavaScriptWindowObject(QString("stagewebview"), m_pStageViewHandler);
  frame->addToJavaScriptWindowObject(QString("eventbus"), new BlackBerryBus(this, frame));
}

void Starbuck::registerInternalAPIs()
{
  QWebFrame* frame = webViewInternal->page()->mainFrame();
  frame->addToJavaScriptWindowObject(QString("eventbus"), new BlackBerryBus(this, frame));

  // check for iframes, if found add to window object
  for(int i = 0; i < frame->childFrames().length(); i++)
      frame->childFrames()[i]->addToJavaScriptWindowObject(QString("eventbus"), new BlackBerryBus(this, frame->childFrames()[i]));
}

void Starbuck::resizeEvent(QResizeEvent * e )
{
   e->accept();
}
