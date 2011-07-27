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
#include "xhrmsghandler.h"

using namespace BlackBerry::Starbuck;
using namespace BlackBerry::Starbuck::IPCChannel;

XHRMsgHandler::XHRMsgHandler(QObject *parent, QWebView *webView)
  : MessageHandler(parent), m_pQtWebView(webView)
{
}

XHRMsgHandler::~XHRMsgHandler()
{
}

void XHRMsgHandler::processMessage(Message* pMsg)
{
  int msgID = pMsg->ID();  
  qDebug() << "Message:" << msgID << "Data:" ;
  switch(msgID)
  {
  case XHR_OPEN:
    //QString data;
    //QBuffer b(pMsg->Data());
    //b.open(QIODevice::ReadOnly);
    //QDataStream in(&b);
    //in >> data;
    //jsObj = new JavaScriptObject(data);
    //qDebug() << "Message TEST1 received, ID:" << msgID << "Data:" << data << " received!";
    ////TODO deserialize pMsg->Data to object and add to java script windows
    //QWebFrame* frame = m_pQtWebView->page()->mainFrame();
    //frame->addToJavaScriptWindowObject(QString("XHROpen"), jsObj);
    break;
  }   
  emit messageProcessed(pMsg);
}


void XHRMsgHandler::sendMessageOpen()
{
    sendMessage(XHR_OPEN, QString("hello"));
}

void XHRMsgHandler::registerEvents()
{
  //connect(reinterpret_cast<QtStageWebView*>(m_pWebView), SIGNAL(xhrOpened()), this, SLOT(sendMessageOpen()));
}
