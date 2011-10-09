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
#include "QtStageWebView.h"
#include "ScrollHandler.h"
#include <QMenu> 
#include <QAction>
#include "remotedebugger.h"

using namespace BlackBerry::Starbuck;

QtStageWebView::QtStageWebView(QWidget *p) : waitForJsLoad(false)
{	
    //Turn off context menu's (i.e. menu when right clicking, you will need to uncommment this if you want to use web inspector,
    //there is currently a conflict between the context menus when using two QWebView's
    //this->setContextMenuPolicy(Qt::NoContextMenu);

	// Connect signals for events
	connect(this, SIGNAL(urlChanged(const QUrl&)), this, SLOT(notifyUrlChanged(const QUrl&)));

	if (page() && page()->mainFrame())
    {
        connect(page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(notifyJavaScriptWindowObjectCleared()));
    }

	//Initialize headers to 0
	_headersSize = 0;

	//enable web inspector
	this->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    
    m_pScrollHandler = new ScrollHandler(this);
    m_pRemoteDebugger = new RemoteDebugger();
    this->installEventFilter(m_pScrollHandler);
}

QtStageWebView::~QtStageWebView(void)
{
}
void QtStageWebView::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;
    QAction *inspectAction = menu.addAction("Inspector Gadget");
    QAction *selectedAction = menu.exec(event->screenPos());
    if (inspectAction == selectedAction) {
        //TODO: Create a new window that has a seperate JS context
        //Point that window to 'http://localhost:9292/webkit/inspector/inspector.html?page=1'
        //QEventLoop loop;
        m_pRemoteDebugger->show();
        //loop.exec();
    }
}
void QtStageWebView::paintEvent(QPaintEvent *pe)
{
    //lock.unlock();
    //QGraphicsWebView::paintEvent(pe);
}

void QtStageWebView::loadURL(QString url)
{
	QNetworkRequest request(url);

	//Add custom headers
	for (unsigned int i = 0; i + 1 < _headersSize; i += 2)
		request.setRawHeader(_headers[i], _headers[i + 1]);

	load(request);
}

void QtStageWebView::reload()
{
	QGraphicsWebView::reload();
}

void QtStageWebView::notifyUrlChanged(const QUrl& url)
{
	emit urlChanged(url.toString());
}

void QtStageWebView::notifyJavaScriptWindowObjectCleared()
{
//  registerEventbus();
  QEventLoop loop;
  QObject::connect(this, SIGNAL(jsLoaded()), &loop, SLOT(quit()));
    emit javaScriptWindowObjectCleared();

  if (waitForJsLoad)
      loop.exec();
}

#if 0
void QtStageWebView::registerEventbus()
{
    QWebFrame* frame = page()->mainFrame();
    frame->addToJavaScriptWindowObject(QString("eventbus2"), new BlackBerryBus(this, frame));
    frame->evaluateJavaScript(BlackBerry::Starbuck::eventbusSource);

    // check for iframes, if found add to window object
    for(int i = 0; i < frame->childFrames().length(); i++)
    {
        frame->childFrames()[i]->addToJavaScriptWindowObject(QString("eventbus2"), new BlackBerryBus(this, frame->childFrames()[i]));
        frame->childFrames()[i]->evaluateJavaScript(BlackBerry::Starbuck::eventbusSource);
  }
}
#endif

void QtStageWebView::continueLoad()
{
    emit jsLoaded();
    waitForJsLoad = false;
}

bool QtStageWebView::enableCrossSiteXHR()
{
	return this->settings()->testAttribute(QWebSettings::LocalContentCanAccessRemoteUrls);
}

void QtStageWebView::enableCrossSiteXHR(bool xhr)
{
    return this->settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, xhr);
}

QVariant QtStageWebView::executeJavaScript(QString script)
{
	return page()->mainFrame()->evaluateJavaScript(script);
}

QString QtStageWebView::location()
{
	return url().toString();
}

bool QtStageWebView::isHistoryBackEnabled()
{
	return history() ? history()->canGoBack() : false;
}

bool QtStageWebView::isHistoryForwardEnabled()
{
	return history() ? history()->canGoForward() : false;
}

void QtStageWebView::historyBack()
{
	back();
}

void QtStageWebView::historyForward()
{
	forward();
}

int QtStageWebView::historyLength()
{
	return history() ? history()->count() : 0;
}

int QtStageWebView::historyPosition()
{
	return history() ? history()->currentItemIndex() : -1;
}

void QtStageWebView::historyPosition(int position)
{
	if (history() && position >= 0 && position < history()->count())
	{
		history()->goToItem(history()->itemAt(position));
	}
}

char** QtStageWebView::customHTTPHeaders()
{
	return _headers;
}

void QtStageWebView::customHTTPHeaders(char *headers[], unsigned int headersSize)
{
	_headers = new char*[headersSize];
	
	for (unsigned int i = 0; i < headersSize; i++)
    {
        _headers[i] = new char[strlen(headers[i]) + 1];
		strcpy(_headers[i], headers[i]);
	}

	_headersSize = headersSize;
}

void QtStageWebView::customHTTPHeaders(QString key, QString value)
{
	QByteArray mKey = key.toAscii();
	QByteArray mValue = value.toAscii();
	
	char *headersArray[2];
	headersArray[0] = mKey.data();
	headersArray[1] = mValue.data();
	
	customHTTPHeaders( headersArray, 2);
}

void QtStageWebView::visible(bool enable)
{
	if (this->isVisible() == enable)
		return;

	(enable) ? this->show():this->hide();
}

void QtStageWebView::setZoom(float zoom) {
  this->setZoomFactor(zoom);
}

float QtStageWebView::zoom() {
  return this->zoomFactor();
}
