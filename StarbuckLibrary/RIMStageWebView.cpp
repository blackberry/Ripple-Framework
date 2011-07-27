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
#include "RIMStageWebView.h"

RIMStageWebView::RIMStageWebView(QSize viewsize, QWidget *p) : WebView(viewsize, p)
{	
    //Olympia webview requires that userAgent is set
    const char* str = "Mozilla/5.0 (BlackBerry; U; BlackBerry 9800; en-US) AppleWebKit/534.1+ (KHTML, like Gecko) Version/6.0.0.246 Mobile Safari/534.1+";
    Olympia::WebKit::WebSettings::globalSettings()->setUserAgentString(str);

    //Turn off context menu's (i.e. menu when right clicking)
	this->setContextMenuPolicy(Qt::NoContextMenu);
	locationChangeListenerObj = 0;

    //Setup idle timer to render content
    idleTimer = new QTimer(this);
    connect(idleTimer, SIGNAL(timeout()), this, SLOT(idleUpdate()));
    idleTimer->start(100);

	//Initialize headers to 0
	_headersSize = 0;
}

RIMStageWebView::~RIMStageWebView(void)
{
}

void RIMStageWebView::idleUpdate()
{
    this->triggerRender();
}

void RIMStageWebView::loadURL(QString url)
{
	if (_headersSize != 0){
		loadWithHeaders(QUrl(url).toEncoded().data(), "", _headers, _headersSize);
	}else{
		load(QUrl(url).toEncoded().data(), "", false);
	}
}

void RIMStageWebView::reload()
{
    if ( webPage())
        webPage()->reload();
}

void RIMStageWebView::injectJavaScriptObj(const QObject* jsObj)
{

}

//RIMStageWebView* RIMStageWebView::createWindow(WebPage::WebWindowType type)
//{
//	/*
//    switch(type)
//    {
//    case QWebPage::WebBrowserWindow: // The window is a regular web browser window
//        //QMessageBox::information(NULL, "Type", "WebBrowserWindow:");
//        break;
//    case QWebPage::WebModalDialog: // The window acts as modal dialog.
//       // QMessageBox::information(NULL, "Type", "WebModalDialog");
//        break;
//    default:
//        break;
//    }
//	return new RIMStageWebView(NULL);
// */
//
//	//Do not allow any new windows to be opened
//	//This might have to figure out if it was clicked inside the emulation frame and open a new tab...
//	return NULL;
//    
//}

//void RIMStageWebView::mouseReleaseEvent ( QMouseEvent * ev )
//{
//	QWebView::mouseReleaseEvent(ev);
//}

//bool RIMStageWebView::LocationChanging(const QNetworkRequest &request, WebPage::NavigationType type)
//{
//	bool retVal;
//	
//	//Using this mechanism instead of the signal/slot mechanism since we need a sync call
//	bool success = QMetaObject::invokeMethod(locationChangeListenerObj, 
//			locationChangeListenerMethod,  
//			Qt::DirectConnection,
//			Q_RETURN_ARG(bool, retVal),
//			Q_ARG(QNetworkRequest, request),
//			Q_ARG(QWebPage::NavigationType, type));
//
//	return success ? retVal : true;
//}

void RIMStageWebView::notifyDocumentCreatedForFrame(const WebFrame frame, const bool isMainFrame, const WebDOMDocument& document, const JSContextRef context, const JSValueRef window)
{
	emit documentCreatedForFrame();
}

void RIMStageWebView::registerLocationChangeLisenter(QObject *obj, char *method)
{
	locationChangeListenerObj = obj;
	locationChangeListenerMethod = method;
}

bool RIMStageWebView::enableCrossSiteXHR()
{
	return webPage()->settings()->allowCrossSiteRequests();
}

void RIMStageWebView::enableCrossSiteXHR(bool xhr)
{
    webPage()->settings()->setAllowCrossSiteRequests(xhr);
}

QVariant RIMStageWebView::executeJavaScript(QString script)
{
    return this->evaluateJavaScript(script);
}

QString RIMStageWebView::location()
{
	return url();
}

bool RIMStageWebView::isHistoryBackEnabled()
{
	return (WebView::currentHistoryIndex() > 0);
}

bool RIMStageWebView::isHistoryForwardEnabled()
{
	return (WebView::currentHistoryIndex() < WebView::historyLength() - 1);
}

void RIMStageWebView::historyBack()
{
	if (isHistoryBackEnabled())
	{
		goBack();
	}
}

void RIMStageWebView::historyForward()
{
	if (isHistoryForwardEnabled())
	{
		goForward();
	}
}

int RIMStageWebView::historyLength()
{
	return WebView::historyLength();
}

int RIMStageWebView::historyPosition()
{
	return WebView::currentHistoryIndex();
}

void RIMStageWebView::historyPosition(int position)
{
	if (position >= 0 && position < WebView::historyLength() && WebView::webPage())
	{
		WebView::webPage()->goBackOrForward(position - WebView::currentHistoryIndex());
	}
}

char** RIMStageWebView::customHTTPHeaders()
{
	return _headers;
}

void RIMStageWebView::customHTTPHeaders(char *headers[], unsigned int headersSize)
{
	_headers = new char*[headersSize];
	
	for (int i = 0; i < headersSize; i++){
        _headers[i] = new char[strlen(headers[i]) + 1];
		strcpy(_headers[i], headers[i]);
	}

	_headersSize = headersSize;
}

void RIMStageWebView::customHTTPHeaders(QString key, QString value)
{
	QByteArray mKey = key.toAscii();
	QByteArray mValue = value.toAscii();
	
	char *headersArray[2];
	headersArray[0] = mKey.data();
	headersArray[1] = mValue.data();
	
	customHTTPHeaders( headersArray, 2);
}

void RIMStageWebView::visible(bool enable)
{
	if (this->isVisible() == enable)
		return;

	(enable)? this->show():this->hide();

}
