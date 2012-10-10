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
#include "StageViewMsgHandler.h"

using namespace BlackBerry::Ripple;
using namespace BlackBerry::Ripple::IPCChannel;

StageViewMsgHandler::StageViewMsgHandler(QObject *parent)
	: QObject(parent),m_pWebView(0), _buildServerPort(0)
{
}

StageViewMsgHandler::~StageViewMsgHandler()
{
}

void StageViewMsgHandler::registerEvents()
{
	connect(rimStageWebview(), SIGNAL(urlChanged(QString)), this, SLOT(urlChanged(QString)));
	connect(rimStageWebview(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(javaScriptWindowObjectCleared()));
//	connect(rimStageWebview()->page()->mainFrame(), SIGNAL(networkResourceRequest(QNetworkRequest*)), this, SLOT(resourceRequest(QNetworkRequest*)));
//	connect(rimStageWebview()->page()->mainFrame(), SIGNAL(networkResourceReply(QNetworkReply*)), this, SLOT(resourceReply(QNetworkReply*)));
    connect(this, SIGNAL(javaScriptInjected()), rimStageWebview(), SLOT(continueLoad()));
}

void StageViewMsgHandler::loadUrl(const QString& url)
{
	stageWebview()->loadURL(url);
}

void StageViewMsgHandler::executeJavaScript(const QString& script)
{
	stageWebview()->executeJavaScript(script);
}

void StageViewMsgHandler::crossOrigin(const bool allow)
{
	QString allowString;
	if (allow) {
		allowString = "true";
	} else {
		allowString = "false";
	}
	stageWebview()->enableCrossSiteXHR(allow);
}

void StageViewMsgHandler::customHTTPHeader(const QString& key, const QString& value)
{
  rimStageWebview()->customHTTPHeaders(key, value);
}

void StageViewMsgHandler::setVisible(const bool isVisible)
{
	rimStageWebview()->visible(isVisible);
}

void StageViewMsgHandler::setWindowGeometry(int x, int y, int w, int h)
{
	stageWebview()->setWindowGeometry(x,y,w,h);
}

QString StageViewMsgHandler::location()
{
	return stageWebview()->location();
}

void StageViewMsgHandler::historyBack()
{
	return stageWebview()->historyBack();
}

void StageViewMsgHandler::historyForward()
{
	return stageWebview()->historyForward();
}

bool StageViewMsgHandler::isHistoryBackEnabled()
{
	return stageWebview()->isHistoryBackEnabled();
}

bool StageViewMsgHandler::isHistoryForwardEnabled()
{
	return stageWebview()->isHistoryForwardEnabled();
}

int StageViewMsgHandler::historyLength()
{
	return stageWebview()->historyLength();
}

int StageViewMsgHandler::historyPosition()
{
	return stageWebview()->historyPosition();
}

void StageViewMsgHandler::reload()
{
    stageWebview()->reload();
}

void StageViewMsgHandler::historyPosition(int position)
{
	return stageWebview()->historyPosition(position);
}

void StageViewMsgHandler::urlChanged(const QString& url)
{
    emit locationChanged(url);
}

void StageViewMsgHandler::javaScriptWindowObjectCleared()
{
	emit javaScriptWindowCleared();
}

void StageViewMsgHandler::setZoomFactor(float zoom){
  stageWebview()->setZoom(zoom);
}

float StageViewMsgHandler::zoomFactor(){
  return stageWebview()->zoom();
}

#if 0
void StageViewMsgHandler::processMessage(Message* pMsg)
{
	emit messageProcessed(pMsg);
}

void StageViewMsgHandler::resourceRequest(QNetworkRequest* request)
{
  //qDebug() << "emit stagewebview.OnRequest(), url:" << request->url().toString();
  QString request_string(request->url().toString());
  m_pRequest->setUrl(request_string);
  m_pRequest->setWebFrame(rimStageWebview()->page()->mainFrame());
  emit onRequest(m_pRequest);
  //qDebug() << " stagewebview.OnRequest() emitted";
}
void StageViewMsgHandler::resourceReply(QNetworkReply* reply)
{
  //qDebug() << "emit stagewebview.OnResponse(), url:" << reply->url().toString();
  emit onResponse(this);
  //qDebug() << " stagewebview.onResponse() emitted";
}
#endif

void StageViewMsgHandler::setServerPort(int port)
{
    _buildServerPort = port;
}