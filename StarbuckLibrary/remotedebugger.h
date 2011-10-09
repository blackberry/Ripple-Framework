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

#ifndef RMOTEDEBUGGER_H
#define RMOTEDEBUGGER_H

#include <QMainWindow>
#include <QWebView>


class RemoteDebugger : public QMainWindow
{
    Q_OBJECT
public:
    RemoteDebugger(QString port);
    ~RemoteDebugger();
    void show(void);
protected:
    void closeEvent(QCloseEvent *event);
    void resizeEvent(QResizeEvent * e );
private:
    QWebView *debuggerView;
    QString m_port;
    void init(void);
};

#endif // REMOTEDEBUGGER_H
