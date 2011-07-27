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

#pragma once
#include <QNetworkRequest>
#include <webpage.h>
#include "RIMStageWebView.h"
#include <QObject>

using namespace Olympia::WebKit;

class RIMWebPage : public WebPage, QObject
{
public:
	RIMWebPage(QObject *parent = 0);
	~RIMWebPage(void);
	
	void SetWebView(RIMStageWebView *webView);

protected:
	//bool	acceptNavigationRequest ( QWebFrame * frame, const QNetworkRequest & request, NavigationType type );

private:
	
	RIMStageWebView *_webView;
};
