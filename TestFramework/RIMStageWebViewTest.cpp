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

#include "RIMStageWebViewTest.h"

TEST(RIMStageWebView, CanRetrieveEmptyLocation)
{
	QString location("");
	
	QSize size(100, 100);
	RIMStageWebView webview(size);
	webview.setGeometry(0, 0, 100, 100);

	// Create an event loop to wait for the loadFinished when loading webpages
	QEventLoop loop;
	QObject::connect(&webview, SIGNAL(loadFinished()), &loop, SLOT(quit()));
	QObject::connect(&webview, SIGNAL(loadFailed()), &loop, SLOT(quit()));

	webview.loadURL(location);
	QTimer::singleShot(5000, &loop, SLOT(quit()));
	loop.exec();
	EXPECT_EQ(location.toStdString(), webview.location().toStdString());
}

TEST(RIMStageWebView, CanRetrieveValidLocation)
{
	QString location("http://www.google.ca/");
	
	QSize size(100, 100);
	RIMStageWebView webview(size);
	webview.setGeometry(0, 0, 100, 100);

	// Create an event loop to wait for the loadFinished when loading webpages
	QEventLoop loop;
	QObject::connect(&webview, SIGNAL(loadFinished()), &loop, SLOT(quit()));
	QObject::connect(&webview, SIGNAL(loadFailed()), &loop, SLOT(quit()));

	webview.loadURL(location);
	QTimer::singleShot(5000, &loop, SLOT(quit()));
	loop.exec();
	EXPECT_EQ(location.toStdString(), webview.location().toStdString());
}

TEST(RIMStageWebView, CanRetrieveInvalidLocation)
{
	QString location = "http://ace/";
	QString blank_location = "";
	
	QSize size(100, 100);
	RIMStageWebView webview(size);
	webview.setGeometry(0, 0, 100, 100);

	// Create an event loop to wait for the loadFinished when loading webpages
	QEventLoop loop;
	QObject::connect(&webview, SIGNAL(loadFinished()), &loop, SLOT(quit()));
	QObject::connect(&webview, SIGNAL(loadFailed()), &loop, SLOT(quit()));

	webview.loadURL(location);
	QTimer::singleShot(5000, &loop, SLOT(quit()));
	loop.exec();
	EXPECT_EQ(blank_location.toStdString(), webview.location().toStdString());
}

TEST(RIMStageWebView, CannotGoBackWhenOnePageLoaded)
{
	QString location = "http://www.google.ca/";

	QSize size(360, 480);
	RIMStageWebView webview(size);
	webview.setGeometry(0, 0, 360, 480);

	// Create an event loop to wait for the loadFinished when loading webpages
	QEventLoop loop;
	QObject::connect(&webview, SIGNAL(loadFinished()), &loop, SLOT(quit()));
	QObject::connect(&webview, SIGNAL(loadFailed()), &loop, SLOT(quit()));

	// Execute the event loop here, now we will wait here until loadFinished() signal is emitted
	// which in turn will trigger event loop quit.
	webview.loadURL(location);
	QTimer::singleShot(5000, &loop, SLOT(quit()));
	loop.exec();
	EXPECT_EQ(location.toStdString(), webview.location().toStdString());

	EXPECT_FALSE(webview.isHistoryBackEnabled());
}

TEST(RIMStageWebView, CanGoBackWhenMultiplePagesLoaded)
{
	QString location_0 = "http://www.google.ca/";
	QString location_1 = "http://www.thestar.com/mobile";
	
	QSize size(360, 480);
	RIMStageWebView webview(size);
	webview.setGeometry(0, 0, 360, 480);

	// Create an event loop to wait for the loadFinished when loading webpages
	QEventLoop loop;
	QObject::connect(&webview, SIGNAL(loadFinished()), &loop, SLOT(quit()));
	QObject::connect(&webview, SIGNAL(loadFailed()), &loop, SLOT(quit()));
 
	// Create a timer to ensure the event loop quits
	QTimer timer;
	QObject::connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));

	webview.loadURL(location_0);
	timer.start(5000);
	loop.exec();
	timer.stop();
	EXPECT_EQ(location_0.toStdString(), webview.location().toStdString());

	webview.loadURL(location_1);
	timer.start(5000);
	loop.exec();
	timer.stop();
	EXPECT_EQ(location_1.toStdString(), webview.location().toStdString());

	EXPECT_TRUE(webview.isHistoryBackEnabled());
	webview.historyBack();
	timer.start(5000);
	loop.exec();
	timer.stop();
	EXPECT_EQ(location_0.toStdString(), webview.location().toStdString());
}

TEST(RIMStageWebView, CannotGoForwardWhenOnePageLoaded)
{
	QString location_0 = "http://www.thestar.com/mobile";

	QSize size(100, 100);
	RIMStageWebView webview(size);
	webview.setGeometry(0, 0, 100, 100);

	// Create an event loop to wait for the loadFinished when loading webpages
	QEventLoop loop;
	QObject::connect(&webview, SIGNAL(loadFinished()), &loop, SLOT(quit()));
	QObject::connect(&webview, SIGNAL(loadFailed()), &loop, SLOT(quit()));

	webview.loadURL(location_0);
	QTimer::singleShot(5000, &loop, SLOT(quit()));
	loop.exec();
	EXPECT_EQ(location_0.toStdString(), webview.location().toStdString());

	EXPECT_FALSE(webview.isHistoryForwardEnabled());
}

TEST(RIMStageWebView, CanGoForwardWhenMultiplePagesLoaded)
{
	QString location_0 = "http://www.thestar.com/mobile";
	QString location_1 = "http://www.google.ca/";
	
	QSize size(360, 480);
	RIMStageWebView webview(size);
	webview.setGeometry(0, 0, 360, 480);

	// Create an event loop to wait for the loadFinished when loading webpages
	QEventLoop loop;
	QObject::connect(&webview, SIGNAL(loadFinished()), &loop, SLOT(quit()));
	QObject::connect(&webview, SIGNAL(loadFailed()), &loop, SLOT(quit()));

	// Create a timer to ensure the event loop quits
	QTimer timer;
	QObject::connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));

	webview.loadURL(location_0);
	timer.start(5000);
	loop.exec();
	timer.stop();
	EXPECT_EQ(location_0.toStdString(), webview.location().toStdString());

	webview.loadURL(location_1);
	timer.start(5000);
	loop.exec();
	timer.stop();
	EXPECT_EQ(location_1.toStdString(), webview.location().toStdString());

	EXPECT_TRUE(webview.isHistoryBackEnabled());
	webview.historyBack();
	timer.start(5000);
	loop.exec();
	timer.stop();
	EXPECT_EQ(location_0.toStdString(), webview.location().toStdString());

	EXPECT_TRUE(webview.isHistoryForwardEnabled());
	webview.historyForward();
	timer.start(5000);
	loop.exec();
	timer.stop();
	EXPECT_EQ(location_1.toStdString(), webview.location().toStdString());
}

TEST(RIMStageWebView, CanRetrieveHistoryLength)
{
	QString location_0 = "http://www.thestar.com/mobile";
	QString location_1 = "http://www.google.ca/";
	
	QSize size(360, 480);
	RIMStageWebView webview(size);
	webview.setGeometry(0, 0, 360, 480);

	// Create an event loop to wait for the loadFinished when loading webpages
	QEventLoop loop;
	QObject::connect(&webview, SIGNAL(loadFinished()), &loop, SLOT(quit()));
	QObject::connect(&webview, SIGNAL(loadFailed()), &loop, SLOT(quit()));

	QTimer timer;
	QObject::connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));

	webview.loadURL(location_0);
	timer.start(5000);
	loop.exec();
	timer.stop();
	EXPECT_EQ(1, webview.historyLength());

	webview.loadURL(location_1);
	timer.start(5000);
	loop.exec();
	timer.stop();
	EXPECT_EQ(2, webview.historyLength());
}

TEST(RIMStageWebView, CanRetrieveHistoryPosition)
{
	QString location_0 = "http://www.thestar.com/mobile";
	QString location_1 = "http://www.google.ca/";
	QString location_2 = "http://www.wikipedia.org/";
	
	QSize size(360, 480);
	RIMStageWebView webview(size);
	webview.setGeometry(0, 0, 360, 480);

	// Create an event loop to wait for the loadFinished when loading webpages
	QEventLoop loop;
	QObject::connect(&webview, SIGNAL(loadFinished()), &loop, SLOT(quit()));
	QObject::connect(&webview, SIGNAL(loadFailed()), &loop, SLOT(quit()));

	QTimer timer;
	QObject::connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));

	webview.loadURL(location_0);
	timer.start(5000);
	loop.exec();
	timer.stop();
	EXPECT_EQ(0, webview.historyPosition());

	webview.loadURL(location_1);
	timer.start(5000);
	loop.exec();
	timer.stop();
	EXPECT_EQ(1, webview.historyPosition());

	webview.loadURL(location_2);
	timer.start(5000);
	loop.exec();
	timer.stop();
	EXPECT_EQ(2, webview.historyPosition());

	EXPECT_TRUE(webview.isHistoryBackEnabled());
	webview.historyBack();
	timer.start(5000);
	loop.exec();
	timer.stop();
	EXPECT_EQ(1, webview.historyPosition());
}

TEST(RIMStageWebView, CanGoToSpecificHistoryLocation)
{
	QString location_0 = "http://www.thestar.com/mobile";
	QString location_1 = "http://www.google.ca/";
	QString location_2 = "http://www.wikipedia.org/";
	QString location_3 = "http://www.thestar.com/mobile";
	
	QSize size(360, 480);
	RIMStageWebView webview(size);
	webview.setGeometry(0, 0, 360, 480);

	// Create an event loop to wait for the loadFinished when loading webpages
	QEventLoop loop;
	QObject::connect(&webview, SIGNAL(loadFinished()), &loop, SLOT(quit()));
	QObject::connect(&webview, SIGNAL(loadFailed()), &loop, SLOT(quit()));
	
	QTimer timer;
	QObject::connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));

	webview.loadURL(location_0);
	timer.start(5000);
	loop.exec();
	timer.stop();
	EXPECT_EQ(location_0.toStdString(), webview.location().toStdString());
	EXPECT_EQ(0, webview.historyPosition());

	webview.loadURL(location_1);
	timer.start(5000);
	loop.exec();
	timer.stop();
	EXPECT_EQ(location_1.toStdString(), webview.location().toStdString());
	EXPECT_EQ(1, webview.historyPosition());

	webview.loadURL(location_2);
	timer.start(5000);
	loop.exec();
	timer.stop();
	EXPECT_EQ(location_2.toStdString(), webview.location().toStdString());
	EXPECT_EQ(2, webview.historyPosition());

	webview.loadURL(location_3);
	timer.start(5000);
	loop.exec();
	timer.stop();
	EXPECT_EQ(location_3.toStdString(), webview.location().toStdString());
	EXPECT_EQ(3, webview.historyPosition());

	webview.historyPosition(1);
	timer.start(5000);
	loop.exec();
	timer.stop();
	EXPECT_EQ(location_1.toStdString(), webview.location().toStdString());
	EXPECT_EQ(1, webview.historyPosition());
}

TEST (RIMStageWebView, AddCustomHeader){
	QSize size(100, 100);
	RIMStageWebView rim_web_view(size);
	char* key = "MyHeaderKey";
	char* value = "MyHeaderValue";

	rim_web_view.customHTTPHeaders(QString::fromStdString(key), QString::fromStdString(value));

	char** returnArray = rim_web_view.customHTTPHeaders();
	
	EXPECT_EQ(*returnArray[0], *key);
	EXPECT_EQ(*returnArray[1], *value);
}

TEST (RIMStageWebView, AddCustomHeaderArray){
	QSize size(100, 100);
	RIMStageWebView rim_web_view(size);
	char *headersArray[2];
	headersArray[0] = "MyHeaderKey";
	headersArray[1] = "MyHeaderValue";
	
	rim_web_view.customHTTPHeaders(headersArray, 2);
	char** returnArray = rim_web_view.customHTTPHeaders();
	
	EXPECT_EQ(*returnArray[0], *headersArray[0]);
	EXPECT_EQ(*returnArray[1], *headersArray[1]);
}

TEST(RIMStageWebView, CanSignalDocumentLoaded)
{
	QString location("http://www.google.ca/");

	QSize size(360, 480);
	RIMStageWebView webview(size);
	webview.setGeometry(0, 0, 360, 480);

	QSignalSpy spy(&webview, SIGNAL(documentCreatedForFrame()));
		
	// Create an event loop to wait for the loadFinished when loading webpages
	QEventLoop loop;
	QObject::connect(&webview, SIGNAL(loadFinished()), &loop, SLOT(quit()));
	QObject::connect(&webview, SIGNAL(loadFailed()), &loop, SLOT(quit()));

	webview.loadURL(location);
	QTimer::singleShot(5000, &loop, SLOT(quit()));
	loop.exec();

	EXPECT_EQ(1, spy.count());
}

TEST (RIMStageWebView, CanSetVisable){
	QSize size(360, 480);
	RIMStageWebView webview(size);
	webview.setGeometry(0, 0, 360, 480);

	webview.loadURL("http://www.google.ca");
	
	webview.visible( true );
	EXPECT_TRUE(webview.isVisible());
}

TEST (RIMStageWebView, CanSetInvisable){
	QSize size(360, 480);
	RIMStageWebView webview(size);
	webview.setGeometry(0, 0, 360, 480);

	webview.loadURL("http://www.google.ca");

	webview.visible( false );
	EXPECT_FALSE(webview.isVisible());
}

TEST(RIMStageWebView, CanEnableCrossOrigin)
{
	QSize size(360, 480);
	RIMStageWebView webview(size);
	webview.setGeometry(0, 0, 360, 480);
	webview.loadURL("http://www.google.ca");

	webview.enableCrossSiteXHR(true);
	EXPECT_TRUE(webview.enableCrossSiteXHR());
}

TEST(RIMStageWebView, CanDisableCrossOrigin)
{
	QSize size(360, 480);
	RIMStageWebView webview(size);
	webview.setGeometry(0, 0, 360, 480);
	webview.loadURL("http://www.google.ca");

	webview.enableCrossSiteXHR(false);
	EXPECT_FALSE(webview.enableCrossSiteXHR());
}

TEST(RIMStageWebView, ExecuteJavaScript)
{
	QSize size(360, 480);
	RIMStageWebView webview(size);
	webview.setGeometry(0, 0, 360, 480);
	webview.loadURL("http://www.google.ca");

	EXPECT_EQ(7, webview.executeJavaScript("a=3+4").toInt());
}
