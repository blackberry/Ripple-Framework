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
#include "QtStageWebView.h"

using namespace BlackBerry::Starbuck::IPCChannel;

namespace BlackBerry {
namespace Starbuck {

class StageViewMsgHandler : public QObject
{
  Q_OBJECT
  Q_PROPERTY(int serverPort READ getServerPort)

public:
    StageViewMsgHandler(QObject *parent = 0);
    ~StageViewMsgHandler();
   
    void Register(IStarbuckWebView* pWebView)
    {
      m_pWebView = pWebView;
      registerEvents();
    }

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
  void setServerPort(int port);
  void setZoomFactor(float zoom);
  float zoomFactor();
 
    //following slots are used internal for emit signals which will be connected from js side
private slots:
    void urlChanged(const QString& url);
	void javaScriptWindowObjectCleared();
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
	virtual IStarbuckWebView* stageWebview()
	{
		return dynamic_cast<IStarbuckWebView*>(m_pWebView);
	}

	virtual QtStageWebView* rimStageWebview()
	{
		return dynamic_cast<QtStageWebView*>(m_pWebView);
	}

    int getServerPort()
    {
        return _buildServerPort;
    }

private:
	IStarbuckWebView* m_pWebView;
    int _buildServerPort;
};
}}
#endif // STAGEVIEWMSGHANDLER_H
