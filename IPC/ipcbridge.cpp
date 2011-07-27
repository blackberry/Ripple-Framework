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
#include "ipcbridge.h"
#include "messagehandler.h"
#include "ipcbridgeworker.h"

using namespace BlackBerry::Starbuck::IPCChannel;

IPCBridge::IPCBridge(QString& smname, QObject* parent) 
    : QObject(parent), m_name(smname),m_pWorker(0), m_pMsgQueue(new MessageQueue(m_name.toStdString(), this)) 
{
  if ( m_pMsgQueue == 0 )
  {
    //log error
    qDebug() << "IPCBridge::IPBridge():Can not allocate memory for the message queue."; 
    throw std::exception();
  }
}

IPCBridge::~IPCBridge()
{
  Stop();
  CleanSharedMemory();
}

void IPCBridge::Start()
{
  m_pWorker = new IPCBridgeworker(m_name, m_pMsgHandler, this);    
  m_pWorker->start();
}

void IPCBridge::Stop()
{
  if ( m_pWorker->isRunning())
  {
    qDebug() << "Stop monitoring thread";
    m_pWorker->exit();
  }
}

void IPCBridge::RegisterMessageHandler(MessageHandler* pHandler)
{
    connect(pHandler, SIGNAL(messageSent(Message*)), m_pMsgQueue, SLOT(addMessage(Message*)));
    m_pMsgHandler = pHandler;
}

void IPCBridge::CleanSharedMemory()
{
  if ( m_pMsgQueue != 0 )
  {
    m_pMsgQueue->RemoveSharedMemory();
  }
}
