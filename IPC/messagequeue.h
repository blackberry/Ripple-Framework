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

#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include <QObject>
#include <message.h>
#include "messagehandler.h"
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/deque.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>

using namespace boost::interprocess;

namespace BlackBerry { 
namespace Starbuck {
namespace IPCChannel {

static const int MAX_MEMORY_SIZE = 512*1024;
static const int MAX_QUEUE_SIZE = 1000;

class MessageQueue : public QObject
{
  Q_OBJECT

public:
  MessageQueue(const std::string& name, QObject *parent = 0);
    virtual ~MessageQueue();

public:
    void Add(Message* pMsg);
    void Remove();
    void RemoveSharedMemory()
    {
      shared_memory_object::remove(m_name.c_str());
    }

public slots:
    void addMessage(Message*);
    void removeMessage();
    
signals:
    void messageAdded(Message* pMsg);
    void messageRemoved(Message* pMsg);
    
private:
  std::string m_name;
  //a boost deque on shared memory
  typedef managed_shared_memory::segment_manager segment_manager_t; 
  typedef allocator<QByteArray, segment_manager_t> ByteArray_allocator; 
  typedef allocator<Message, segment_manager_t> MessageAllocator;      
  typedef deque<Message, MessageAllocator> MessageDeque;
  managed_shared_memory shm;
  MessageAllocator msgAllocator;
  ByteArray_allocator baAllocator;
  struct Data{
    interprocess_mutex mutex;
    interprocess_condition full;
    interprocess_condition empty;
    MessageDeque deq;
    Data(const MessageAllocator &ref): deq(ref){}
  };
  Data *m_pMsgDeque; 
};
}
}
}
#endif // MESSAGEQUEUE_H
