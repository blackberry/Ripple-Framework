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
#include "samplemessagehandler.h"

using namespace BlackBerry::Starbuck::IPCChannel;

SampleMessagehandler::SampleMessagehandler(QObject *parent)
  : MessageHandler(parent)
{

}

SampleMessagehandler::~SampleMessagehandler()
{

}

void SampleMessagehandler::processMessage(Message* pMsg)
{
   //Process message
   int msgID = pMsg->ID();
   
   switch(msgID)
   {
   case IPCChannel_MESSAGE_TEST1:
     {
       QString data;
       QBuffer b(pMsg->Data());
       b.open(QIODevice::ReadOnly);
       QDataStream in(&b);
       in >> data;
       qDebug() << "Message TEST1 received, ID:" << msgID << "Data:" << data << " received!";
       break;
     }
   case IPCChannel_MESSAGE_TEST2:
     {
       QString data;
       QBuffer b(pMsg->Data());
       b.open(QIODevice::ReadOnly);
       QDataStream in(&b);
       in >> data;
       qDebug() << "Message TEST2 received, ID:" << msgID << "Data:" << data << " received!";
       break;
     }
   }   
   emit messageProcessed(pMsg);
}
