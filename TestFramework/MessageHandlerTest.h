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

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "MessageSignalSpy.h"
#include "StageViewMsgHandler.h"
#include "irimstagewebview.h"
#include <QSignalSpy>

using ::testing::Return;
using ::testing::Invoke;

using namespace BlackBerry::Starbuck;
using namespace BlackBerry::Starbuck::IPCChannel;

//Q_DECLARE_METATYPE(Message *);

class MockRIMStageWebView : public IStarbuckWebView
{
public:
	MockRIMStageWebView() {}
	virtual ~MockRIMStageWebView() {}

	MOCK_METHOD1(loadURL, void(QString));
	MOCK_METHOD1(enableCrossSiteXHR, void(bool));
	MOCK_METHOD1(executeJavaScript, QVariant(QString));
	MOCK_METHOD0(location, QString());
	MOCK_METHOD0(historyBack, void());
	MOCK_METHOD0(historyForward, void());
	MOCK_METHOD0(isHistoryBackEnabled, bool());
	MOCK_METHOD0(isHistoryForwardEnabled, bool());
	MOCK_METHOD0(historyLength, int());
	MOCK_METHOD0(historyPosition, int());
	MOCK_METHOD1(historyPosition, void(int));
	MOCK_METHOD4(setWindowGeometry, void(int,int,int,int));
//	MOCK_METHOD1(injectJavaScriptObj, void(const QObject *jsObj));
};

class TestStageViewMsgHandler : public StageViewMsgHandler
{
public:
	TestStageViewMsgHandler() {}
	virtual ~TestStageViewMsgHandler() {}

	MOCK_METHOD0(stageWebview, IStarbuckWebView*());
};
