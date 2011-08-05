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
#include "BlackBerryBus.h"
#include <QWebFrame>

using namespace BlackBerry::Starbuck;

QMap<QString, QList<CallbackInfo>*> BlackBerryBus::_listener;

BlackBerryBus::BlackBerryBus(QObject *parent, QWebFrame *webFrame)
  : QObject(parent), m_pWebFrame(webFrame)
{
    // seed the random generator
    qsrand(QTime::currentTime().msec());
}

BlackBerryBus::~BlackBerryBus()
{

}

QString BlackBerryBus::generateRandomFunctionName()
{
    const char *alphaSet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    QString name;

    name = "z"; // needs to start with a character so lets make everything start with z

    for (int i = 0; i < 20; i++)
    {
        name += alphaSet[qrand() % strlen(alphaSet) + 0];
    }

    return name;
}

// async version of trigger function
void BlackBerryBus::trigger(QString eventName, QString jsonData, bool async)
{
    if (async)
    {
      if (_listener[eventName]) 
      {
        QList<CallbackInfo>* info = _listener[eventName];
        for(int i = 0; i < (*info).length(); i++)
        {
          CallbackInfo callback = (*info)[i];
          QString evalString("eventbus.trigger('" + eventName + "', '" + jsonData + "')");
          QVariant res = callback.frame->evaluateJavaScript("setTimeout(\"" + evalString + "\", 1)");
        }
      }
    }
    else
        trigger(eventName, jsonData);
}

void BlackBerryBus::trigger(QString eventName, QString jsonData)
{
  if (_listener.contains(eventName)) 
  {
    QList<CallbackInfo>* info = _listener[eventName];
    for(int i = 0; i < (*info).length(); i++)
    {
      CallbackInfo callback = (*info)[i];
      QString evalString("eventbus.trigger('" + eventName + "', '" + jsonData + "')");
      QVariant res = callback.frame->evaluateJavaScript(evalString);
    }
  }
}

QString BlackBerryBus::on(QString eventName, QString jsonCallback)
{
  QList<CallbackInfo>* info = 0;

  if (_listener.contains(eventName) )
    info = _listener[eventName];
  else
    info = new QList<CallbackInfo>();
  
  CallbackInfo callback;
  callback.function = generateRandomFunctionName();
  callback.frame = this->m_pWebFrame;

  info->append(callback);

  _listener.insert(eventName, info);

  return callback.function;
}

QString BlackBerryBus::getFunctionName(QString input)
{
    QList<CallbackInfo>* info = 0;
    QString result;

    if (_listener.contains(input) )
    {
        info = _listener[input];
        for (int i = 0; i<info->length(); i++)
        {
            if (!result.isEmpty())
                result += ";";

            result += (*info)[i].function;
        }
    }
    
    return result;
}
