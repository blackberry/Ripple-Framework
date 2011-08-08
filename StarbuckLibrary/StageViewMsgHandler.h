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

#ifndef STAGEVIEWMSGHANDLER_H
#define STAGEVIEWMSGHANDLER_H
#include "messagehandler.h"
#include "QtStageWebView.h"
#include "RequestObject.h"
#include <QNetworkRequest>
#include <QNetworkReply>

using namespace BlackBerry::Starbuck::IPCChannel;

namespace BlackBerry {
namespace Starbuck {

class StageViewMsgHandler : public MessageHandler
{
  Q_OBJECT

public:
    StageViewMsgHandler(QObject *parent = 0);
    ~StageViewMsgHandler();
   
//stagewebview APIs
public slots:
	void loadUrl(const QString& url);
	void executeJavaScript(const QString& script);
	void crossOrigin(const bool allow);
	void customHTTPHeader(const QString& key, const QString& value);
	void setVisable(const bool isVisible);
	void setWindowGeometry(int x, int y, int w, int h);
	QString location();
	void historyBack();
	void historyForward();
	bool isHistoryBackEnabled();
	bool isHistoryForwardEnabled();
	int historyLength();
	int historyPosition();
	void historyPosition(int position);
    //following slots are used internal for emit signals which will be connected from js side
        void urlChanged(const QString& url);
	void javaScriptWindowObjectCleared();
	void processMessage(Message* pMsg);
        void resourceRequest(QNetworkRequest* request);
        void resourceReply(QNetworkReply* reply);
  	void resourceRequest(QNetworkRequest* request);
  	void resourceReply(QNetworkReply* reply);
	void reload();

//stagewebview events
signals:
	void locationChanged(const QString& url);
    void javaScriptWindowCleared();
    void javaScriptInjected();
    void onRequest(QObject* request);
    void onResponse(QObject* response);

protected:
    void registerEvents();

private:
    RequestObject* m_pRequest;

	virtual IStarbuckWebView* stageWebview()
	{
		return dynamic_cast<IStarbuckWebView*>(m_pWebView);
	}

	virtual QtStageWebView* rimStageWebview()
	{
		return dynamic_cast<QtStageWebView*>(m_pWebView);
	}
};
}}
#endif // STAGEVIEWMSGHANDLER_H
