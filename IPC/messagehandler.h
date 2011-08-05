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

#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <QObject>
#include "message.h"
#include "irimstagewebview.h"

namespace BlackBerry { 
namespace Starbuck {
namespace IPCChannel {

class MessageHandler : public QObject
{
  Q_OBJECT
public:
    MessageHandler(QObject *parent);
    virtual ~MessageHandler(); 

    void EmitMessage(Message* pMsg)
    {
       emit messageSent(pMsg);
    }

    void Register(IStarbuckWebView* pWebView)
    {
      m_pWebView = pWebView;
      registerEvents();
    }

public slots:
    virtual void processMessage(Message* pMsg) = 0;

protected:
  virtual void registerEvents() = 0;
  virtual void sendMessage(int id, const QString& msg);
  
signals:
    void messageProcessed(Message* pMsg);
    void messageSent(Message*);

protected:
  IStarbuckWebView* m_pWebView;

private:

};
}}}
#endif // MESSAGEHANDLER_H
