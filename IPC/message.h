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

#ifndef MESSAGE_H
#define MESSAGE_H

#include <QByteArray>

namespace BlackBerry {
namespace Starbuck {
namespace IPCChannel {

class Message 
{
public:
  Message(int id, int size, QByteArray* pData);
  Message(const Message& m);
  virtual ~Message();

public:
  int ID() const;
  int Size() const;
  QByteArray* Data() const;

private:  

  int m_iID;
  int m_iSize;
  QByteArray* m_pData; 
};

}
}
}
#endif // MESSAGE_H
