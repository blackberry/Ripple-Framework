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

#ifndef IPCTESTSUIT_H
#define IPCTESTSUIT_H

#include <QObject>
#include <QTest>
#include <QMutex>
#include <QThread>
#include "ipcbridge.h"

using namespace BlackBerry::Ripple::IPCChannel;

class IPCTestSuit : public QObject
{
  Q_OBJECT

public:
    IPCTestSuit(QObject *parent = 0);
    ~IPCTestSuit();
 private slots:
     //run one time before all test cases
     void initTestCase();
     //run for before each test case
     //void init();

     //test methods...
     void producerTest();
     void consumerTest();
     
     
     //run after each test case
     //void cleanup();
     //run one time after all test cases
     void cleanupTestCase();    
     public slots:
       void ProcessedMessage(Message* pMsg);

private:
  void sendMessage(const int& id, QString msg);

private:
   IPCBridge* m_bridge;
   MessageHandler* m_pHandler;
};

#endif // IPCTESTSUIT_H
