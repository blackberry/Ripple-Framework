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

#include "messagesendthread.h"
#include "message.h"
#include <QDebug>
#include <QTimer>
#include <QBuffer>

MessageSendThread::MessageSendThread(MessageHandler* pHandler, QObject *parent)
  : QThread(parent), m_pHandler(pHandler)
{
}

MessageSendThread::~MessageSendThread()
{
}

void MessageSendThread::run()
{
  sendMessage();
}

void MessageSendThread::sendMessage()
{
  Message* pMsg = 0;
  char * msg[] = {"Hello0","Hello1","Hello2","Hello3","Hello4","Hello5","Hello6","Hello7","Hello8","Hello9"};
  if ( m_pHandler != 0 )
  {
    for ( int i = 0; i < 10; i++)
    {
      QByteArray a;
      QBuffer b(&a);
      b.open(QIODevice::WriteOnly);
      QDataStream out(&b);
      out << msg[i];
      int size = a.size();
      Message* m_pMsg = new Message(i, size, &a);
      m_pHandler->EmitMessage(m_pMsg);
      qDebug() << "Message:" << i << ":" << msg[i] << " sent!";
      //delete m_pMsg;
    }
  }
}
