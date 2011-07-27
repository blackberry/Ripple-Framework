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
#include "message.h"

using namespace BlackBerry::Starbuck::IPCChannel;

Message::Message(int id, int size, QByteArray* pData)
  : m_iID(id), m_iSize(size), m_pData(pData)
{
}

Message::Message( const Message& m)
{
  m_iID = m.ID();
  m_iSize = m.Size();
  m_pData = new QByteArray(*m.Data()); 
}

Message::~Message() 
{
  //if ( m_pData != 0 )
  //  delete m_pData; must be released outside the class after the data was used, in processMessage() of the messagehandler
}

int Message::ID() const
{
    return m_iID;
}
int Message::Size() const
{
    return m_iSize;
}
QByteArray* Message::Data() const
{
    return m_pData;
}
