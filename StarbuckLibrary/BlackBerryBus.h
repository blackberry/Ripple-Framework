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

#ifndef BLACKBERRYBUS_H
#define BLACKBERRYBUS_H

#include <QWebView>
#include <QObject>
#include "QtStageWebView.h"

namespace BlackBerry {
namespace Starbuck {

struct CallbackInfo
{
    QString function;
    QWebFrame *frame;
};

class BlackBerryBus : public QObject
{
  Q_OBJECT
public:
  BlackBerryBus(QObject *parent, QWebFrame *webFrame);
  ~BlackBerryBus();
private:
  static QMap<QString, QList<CallbackInfo>*> _listener;
  QWebFrame *m_pWebFrame;
  QtStageWebView *m_pInternalWebView;
  QString generateRandomFunctionName();

public slots:
  void trigger(QString eventName, QString jsonData, bool async);
  void trigger(QString eventName, QString jsonData);
  void on(QString eventName, QString jsonCallback);
};

}
}

#endif
