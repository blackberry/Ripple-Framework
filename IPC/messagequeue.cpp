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
#include "messagequeue.h"

using namespace BlackBerry::Starbuck::IPCChannel;

MessageQueue::MessageQueue(const std::string& name, QObject *parent) : QObject(parent), m_name(name),
  shm(open_or_create, m_name.c_str(), MAX_MEMORY_SIZE), 
  msgAllocator(shm.get_segment_manager()), 
  baAllocator(shm.get_segment_manager()),
  m_pMsgDeque(0)
{ 
  m_pMsgDeque = shm.find_or_construct<Data>("messageDequeue", std::nothrow)(msgAllocator);
}

MessageQueue::~MessageQueue()
{
  shm.destroy_ptr(m_pMsgDeque);
  shared_memory_object::remove(m_name.c_str());
  m_pMsgDeque = 0;
}

void MessageQueue::Add(Message* pMsg)
{
  if ( m_pMsgDeque == 0 )
    return;
  qDebug() << "Add() Thread:" << QThread::currentThreadId();
  scoped_lock<interprocess_mutex> lock(m_pMsgDeque->mutex);
  if ( m_pMsgDeque->deq.size() == MAX_QUEUE_SIZE )
  {
    qDebug() << "waiting for pop...";
    m_pMsgDeque->full.wait(lock);
  }
  m_pMsgDeque->deq.push_back(*pMsg);
  m_pMsgDeque->empty.notify_one();
  emit messageAdded(pMsg);
}

void MessageQueue::addMessage(Message* pMsg)
{
  Add(pMsg);
}

void MessageQueue::removeMessage()
{
  Remove();
}

void MessageQueue::Remove()
{
  if ( m_pMsgDeque == 0 )
    return;
  qDebug() << "Remove() Thread:" << QThread::currentThreadId();
  scoped_lock<interprocess_mutex> lock(m_pMsgDeque->mutex);
  Message* pMsg = 0;
  if ( m_pMsgDeque->deq.empty())
  {
    qDebug() << "waiting for add...";
    m_pMsgDeque->empty.wait(lock);
  }
  pMsg = &m_pMsgDeque->deq.front();
  m_pMsgDeque->deq.pop_front();
  m_pMsgDeque->full.notify_one();
  emit messageRemoved(pMsg);
}
