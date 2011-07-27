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

#ifndef REQUESTOBJECT_H
#define REQUESTOBJECT_H

#include <QObject>
#include <QWebFrame>
#include <QWebPage>

namespace BlackBerry {
namespace Starbuck {

class RequestObject : public QObject
{
    Q_OBJECT
public:
    RequestObject(QString& url, QObject *parent = 0, QWebFrame* frame = 0 );
    ~RequestObject();
    Q_PROPERTY(QString url READ getUrl WRITE setUrl)

    void setUrl(QString& url);
    void setWebFrame(QWebFrame* frame);
public slots:
  void allow();
  void deny();
  void respond(QString code, QString url);


private:
  QString m_url;
  QWebFrame* m_pWebFrame;
  QString getUrl() const { return m_url; }
};

}
}

#endif
