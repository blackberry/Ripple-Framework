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

#ifndef TESTFRAMEWORK_RIMSTAGEWEBVIEWTESTSUITE_H_
#define TESTFRAMEWORK_RIMSTAGEWEBVIEWTESTSUITE_H_

#include <QObject>
#include <QtGui>
#include <QTest>
#include "RIMStageWebView.h"

class RIMStageWebViewTestSuite : public QObject {
  Q_OBJECT

 public:
  RIMStageWebViewTestSuite(QObject *parent = 0);
  ~RIMStageWebViewTestSuite(void);

 public slots:
  void loadedWebView();

 private:
  // was the page loaded
  bool _pageLoaded;
  // was the page loaded signal received
  bool _pageLoadedSignal;

  RIMStageWebView *_webView;

 private slots:
  // run one time before all test cases
  void initTestCase();

  // run for before each test case
  void init();

  // test methods...
  void setGeometryTest();
  void loadURLTest();
  void crossOriginTest();
  void executeJavaScriptTest();

  // run after each test case
  void cleanup();

  // run one time after all test cases
  void cleanupTestCase();
};

#endif  // TESTFRAMEWORK_RIMSTAGEWEBVIEWTESTSUITE_H_
