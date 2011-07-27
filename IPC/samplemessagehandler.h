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

#ifndef SAMPLEMESSAGEHANDLER_H
#define SAMPLEMESSAGEHANDLER_H

#include "messagehandler.h"

namespace BlackBerry { 
namespace Starbuck {
namespace IPCChannel {

static const int IPCChannel_MESSAGE_TEST1                 = 0x0100;
static const int IPCChannel_MESSAGE_TEST2                 = 0x0101;

class SampleMessagehandler : public MessageHandler
{
  Q_OBJECT

public:
    SampleMessagehandler(QObject *parent);
    ~SampleMessagehandler();

  void processMessage(Message* pMsg);
protected:
  void registerEvents(){};

private:
    
};
}}}
#endif // SAMPLEMESSAGEHANDLER_H
