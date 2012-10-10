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

#include "ipctestsuit.h"
#include <QDebug>
#include <QBuffer>
#include "messagesendthread.h"

IPCTestSuit::IPCTestSuit(QObject *parent)
  : QObject(parent) 
{
}

IPCTestSuit::~IPCTestSuit()
{
}

void IPCTestSuit::initTestCase()
{
  qDebug("create a IPCBridge instance");
	QString ssm = QString("RippleSM");
  m_bridge = new IPCBridge(ssm,this); //one way communication
  m_pHandler = new SampleMessagehandler(this);  
  m_bridge->RegisterMessageHandler(m_pHandler);
}

void IPCTestSuit::producerTest()
{
  //connect(m_pHandler, SIGNAL(messageSent(Message*)), this, SLOT(ProcessedMessage(Message*)));
  sendMessage(IPCChannel_MESSAGE_TEST1, QString("hello"));
  sendMessage(IPCChannel_MESSAGE_TEST2, QString("world!"));

  //send messages in a new thread
  //MessageSendThread* pMsgSend = new MessageSendThread(m_pHandler, this);
  //pMsgSend->start();
}

void IPCTestSuit::consumerTest()
{
  connect(m_pHandler, SIGNAL(messageProcessed(Message*)), this, SLOT(ProcessedMessage(Message*)));
  qDebug("starting receiving thread");
  m_bridge->Start();
}

void IPCTestSuit::cleanupTestCase()
{
  qDebug("cleanup test case");
}

void IPCTestSuit::ProcessedMessage(Message* pMsg)
{
  if ( pMsg->ID() == IPCChannel_MESSAGE_TEST2 ) //last message processed, then quit the test app
  {
    qDebug() << "Last message processed. ID: " << pMsg->ID();
    m_bridge->Stop();
    m_bridge->CleanSharedMemory();
    exit(0);
  }
}

void IPCTestSuit::sendMessage(const int& id, QString msg)
{
  QByteArray a;
  QBuffer b(&a);
  b.open(QIODevice::WriteOnly);
  QDataStream out(&b);
  out << msg;
  int size = a.size();
  Message* pMsg = new Message(id, size, &a);
  m_pHandler->EmitMessage(pMsg);
  qDebug() << "Message:" << msg << " sent!";
  delete pMsg;
}
