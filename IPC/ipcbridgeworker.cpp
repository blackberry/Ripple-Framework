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

#include "StdAfx.h"
#include "ipcbridgeworker.h"

using namespace BlackBerry::Starbuck::IPCChannel;

IPCBridgeworker::IPCBridgeworker(QString& name, MessageHandler* pHandler, QObject* parent) 
    : QThread(parent), m_name(name), m_pMsgHandler(pHandler), m_pMsgQueue(0)
{
}

IPCBridgeworker::~IPCBridgeworker()
{
}

void IPCBridgeworker::run()
{
  m_pMsgQueue = new MessageQueue(m_name.toStdString());
  if ( m_pMsgQueue != 0 )
  {
    connect(m_pMsgQueue, SIGNAL(messageRemoved(Message*)), m_pMsgHandler, SLOT(processMessage(Message*)));
    QTimer timer;
    connect(&timer, SIGNAL(timeout()), m_pMsgQueue, SLOT(removeMessage()));
    timer.start(0); //interval = 0, fires timeout event whenever system allows;
    exec();
    //not sure if this works
    qDebug() << " worker thread exits, delete m_pMsgQueue ";
    delete m_pMsgQueue;
  }
  else
    qDebug() << "IPCBridgeworker::run(): memory allocation error";
}
