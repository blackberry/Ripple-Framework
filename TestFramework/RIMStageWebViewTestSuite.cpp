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

#include "RIMStageWebViewTestSuite.h"

RIMStageWebViewTestSuite::RIMStageWebViewTestSuite(QObject *parent) {
}

RIMStageWebViewTestSuite::~RIMStageWebViewTestSuite(void) {
}

void RIMStageWebViewTestSuite::initTestCase() {
  qDebug("RIMStageWebViewTestSuite Init Test Case");
}

void RIMStageWebViewTestSuite::cleanupTestCase() {
  qDebug("RIMStageWebViewTestSuite Cleanup Test Case");
}

void RIMStageWebViewTestSuite::init() {
  _pageLoaded = false;
  _pageLoadedSignal = false;
  QSize size(360,480);
  _webView = new RIMStageWebView(size);
}

void RIMStageWebViewTestSuite::cleanup() {
  delete _webView;
}
void RIMStageWebViewTestSuite::loadURLTest() {

  //_webView needs a QT container to show, so this test case did not go through <stu:06/03/2011>
  //TODO: create a QMainWindow ...
  QString site = "http://www.google.com";
  qDebug("loading http://www.google.com");

  connect(_webView, SIGNAL(loadFinished()), this, SLOT(loadedWebView()));

  _webView->loadURL(site);

  int i = 0;

  // Wait for the signal or 10s
  while (!_pageLoadedSignal && i++ < 50) {
    QTest::qWait(200);
  };

  if (!_pageLoaded)
    QFAIL("No Page was loaded");
}

void RIMStageWebViewTestSuite::crossOriginTest() {
  if ( _pageLoaded )
  {
    qDebug("enabling crossSiteXHR");
    _webView->enableCrossSiteXHR(true);

    qDebug("disabling crossSiteXHR");
    _webView->enableCrossSiteXHR(false);
  }
}

void RIMStageWebViewTestSuite::executeJavaScriptTest() {
  qDebug("Attempting to execute javascript");
  int result = _webView->executeJavaScript("a=3+4").toInt();
  QVERIFY(result == 7);
}

void RIMStageWebViewTestSuite::setGeometryTest()
{
  QRect original = _webView->geometry();
  int x = 100, y = 100, w = original.width(), h = original.height();
  _webView->setGeometry(x,y,w,h);
  QRect newpos = _webView->geometry();
  QVERIFY( x == newpos.x());
  QVERIFY( y == newpos.y());
}

void RIMStageWebViewTestSuite::loadedWebView() {
  _pageLoadedSignal = true;
  _pageLoaded = true;
}


