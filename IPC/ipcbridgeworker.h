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

#ifndef IPCBRIDGEWORKER_H
#define IPCBRIDGEWORKER_H

#include <QThread>
#include "messagequeue.h"
#include "messagehandler.h"

namespace BlackBerry { 
namespace Starbuck {
namespace IPCChannel {

class IPCBridgeworker :	public QThread
{
  Q_OBJECT
  public:
      IPCBridgeworker(QString& name, MessageHandler* pHandler, QObject* parent = 0);
      virtual ~IPCBridgeworker();

protected:
     void run();
             
  private:
    QString& m_name;
    MessageHandler* m_pMsgHandler;
    MessageQueue* m_pMsgQueue;
};
}}}
#endif // IPCBRIDGEWORKER_H
