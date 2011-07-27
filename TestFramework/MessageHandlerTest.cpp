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

#include "MessageHandlerTest.h"

TEST(StageViewMsgHandler, CanLoadURL)
{
	TestStageViewMsgHandler test_handler;
	MockRIMStageWebView mock_webview;
	QString url("http://www.google.ca/");

	EXPECT_CALL(test_handler, stageWebview())
		.WillRepeatedly(Return(&mock_webview));

	EXPECT_CALL(mock_webview, loadURL(url))
		.Times(1);

	test_handler.loadUrl(url);
}

TEST(StageViewMsgHandler, CanExecuteJavaScript)
{
	TestStageViewMsgHandler test_handler;
	MockRIMStageWebView mock_webview;
	QString script("7+5+6");
	QVariant js_return("18");

	EXPECT_CALL(test_handler, stageWebview())
		.WillRepeatedly(Return(&mock_webview));

	EXPECT_CALL(mock_webview, executeJavaScript(script))
		.Times(1)
		.WillOnce(Return(js_return));

	test_handler.executeJavaScript(script);
}

TEST(StageViewMsgHandler, CanEnableCrossOrigin)
{
	TestStageViewMsgHandler test_handler;
	MockRIMStageWebView mock_webview;
	bool allow = true;

	EXPECT_CALL(test_handler, stageWebview())
		.WillRepeatedly(Return(&mock_webview));

	EXPECT_CALL(mock_webview, enableCrossSiteXHR(allow))
		.Times(1);

	test_handler.crossOrigin(allow);
}

TEST(StageViewMsgHandler, CanDisableCrossOrigin)
{
	TestStageViewMsgHandler test_handler;
	MockRIMStageWebView mock_webview;
	bool allow = false;

	EXPECT_CALL(test_handler, stageWebview())
		.WillRepeatedly(Return(&mock_webview));

	EXPECT_CALL(mock_webview, enableCrossSiteXHR(allow))
		.Times(1);

	test_handler.crossOrigin(allow);
}

TEST(StageViewMsgHandler, CanSignalLocationChange)
{
	StageViewMsgHandler test_handler;
	QSignalSpy spy(&test_handler, SIGNAL(locationChanged(const QString&)));
	QString url("http://www.blackberry.com");

	test_handler.urlChanged(url);

	ASSERT_EQ(1, spy.count());

	QList<QVariant> arguments = spy.takeFirst();
	QString sent_url = qvariant_cast<QString>(arguments.at(0));
	EXPECT_EQ(url.toStdString(), sent_url.toStdString());
}

TEST(StageViewMsgHandler, CanRetrieveCurrentLocation)
{
	TestStageViewMsgHandler test_handler;
	MockRIMStageWebView mock_webview;
	QString location("http://www.google.ca/");

	EXPECT_CALL(test_handler, stageWebview())
		.WillRepeatedly(Return(&mock_webview));

	EXPECT_CALL(mock_webview, location())
		.Times(1)
		.WillOnce(Return(location));

	EXPECT_EQ(location.toStdString(), test_handler.location().toStdString());
}

TEST(StageViewMsgHandler, CanGoBackToPreviousPage)
{
	TestStageViewMsgHandler test_handler;
	MockRIMStageWebView mock_webview;

	EXPECT_CALL(test_handler, stageWebview())
		.WillRepeatedly(Return(&mock_webview));

	EXPECT_CALL(mock_webview, historyBack())
		.Times(1);

	test_handler.historyBack();
}

TEST(StageViewMsgHandler, CanGoForwardToNextPage)
{
	TestStageViewMsgHandler test_handler;
	MockRIMStageWebView mock_webview;

	EXPECT_CALL(test_handler, stageWebview())
		.WillRepeatedly(Return(&mock_webview));

	EXPECT_CALL(mock_webview, historyForward())
		.Times(1);

	test_handler.historyForward();
}

TEST(StageViewMsgHandler, CanCheckIfHistoryBackEnabled)
{
	TestStageViewMsgHandler test_handler;
	MockRIMStageWebView mock_webview;

	EXPECT_CALL(test_handler, stageWebview())
		.WillRepeatedly(Return(&mock_webview));

	EXPECT_CALL(mock_webview, isHistoryBackEnabled())
		.Times(2)
		.WillOnce(Return(true))
		.WillOnce(Return(false));

	EXPECT_TRUE(test_handler.isHistoryBackEnabled());
	EXPECT_FALSE(test_handler.isHistoryBackEnabled());
}

TEST(StageViewMsgHandler, CanCheckIfHistoryForwardEnabled)
{
	TestStageViewMsgHandler test_handler;
	MockRIMStageWebView mock_webview;

	EXPECT_CALL(test_handler, stageWebview())
		.WillRepeatedly(Return(&mock_webview));

	EXPECT_CALL(mock_webview, isHistoryForwardEnabled())
		.Times(2)
		.WillOnce(Return(false))
		.WillOnce(Return(true));

	EXPECT_FALSE(test_handler.isHistoryForwardEnabled());
	EXPECT_TRUE(test_handler.isHistoryForwardEnabled());
}

TEST(StageViewMsgHandler, CanRetrieveHistoryLength)
{
	TestStageViewMsgHandler test_handler;
	MockRIMStageWebView mock_webview;
	int history_length = 5;

	EXPECT_CALL(test_handler, stageWebview())
		.WillRepeatedly(Return(&mock_webview));

	EXPECT_CALL(mock_webview, historyLength())
		.Times(1)
		.WillOnce(Return(history_length));

	EXPECT_EQ(history_length, test_handler.historyLength());
}

TEST(StageViewMsgHandler, CanRetrieveHistoryPosition)
{
	TestStageViewMsgHandler test_handler;
	MockRIMStageWebView mock_webview;
	int history_position = 3;

	EXPECT_CALL(test_handler, stageWebview())
		.WillRepeatedly(Return(&mock_webview));

	EXPECT_CALL(mock_webview, historyPosition())
		.Times(1)
		.WillOnce(Return(history_position));

	EXPECT_EQ(history_position, test_handler.historyPosition());
}

TEST(StageViewMsgHandler, CanGoBackToSpecificPage)
{
	TestStageViewMsgHandler test_handler;
	MockRIMStageWebView mock_webview;
	int history_position = -3;

	EXPECT_CALL(test_handler, stageWebview())
		.WillRepeatedly(Return(&mock_webview));

	EXPECT_CALL(mock_webview, historyPosition(history_position))
		.Times(1);

	test_handler.historyPosition(history_position);
}

TEST(StageViewMsgHandler, CanGoForwardToSpecificPage)
{
	TestStageViewMsgHandler test_handler;
	MockRIMStageWebView mock_webview;
	int history_position = 4;

	EXPECT_CALL(test_handler, stageWebview())
		.WillRepeatedly(Return(&mock_webview));

	EXPECT_CALL(mock_webview, historyPosition(history_position))
		.Times(1);

	test_handler.historyPosition(history_position);
}

TEST(StageViewMsgHandler, CanSignalJavaScriptWindowCleared)
{
	StageViewMsgHandler test_handler;
	QSignalSpy spy(&test_handler, SIGNAL(javaScriptWindowCleared()));

	test_handler.javaScriptWindowObjectCleared();

	EXPECT_EQ(1, spy.count());
}
