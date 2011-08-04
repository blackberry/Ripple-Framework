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

#ifndef STARBUCK_H
#define STARBUCK_H

#include <QMainWindow>
#include <QWebPage>
#include <QProgressBar>
#include <QWebView>
#include "ConfigData.h"
#include "ipcbridge.h"
#include "stageviewmsghandler.h"
#include "xhrmsghandler.h"
#include "blackberrybus.h"
#include "RequestObject.h"

using namespace BlackBerry::Starbuck::IPCChannel;

namespace BlackBerry 
{
  namespace Starbuck 
  {
    class Starbuck : public QMainWindow
    {
        Q_OBJECT

    public:
      Starbuck(QWidget *parent = 0, Qt::WFlags flags = 0);
      ~Starbuck();

    protected:
        void closeEvent(QCloseEvent *event);
        void resizeEvent(QResizeEvent * e );

    private slots:
        void registerAPIs();
        void registerInternalAPIs();

    private:
        static const int PROGRESS_BAR_HEIGHT;
        QWebView* webView;
        QtStageWebView* webViewInternal;
        QProgressBar* progressBar;
        ConfigData *_config;
        IPCBridge* m_pBridge;
        StageViewMsgHandler* m_pStageViewHandler;
        XHRMsgHandler* m_pXHRHandler;

        void init(void);    
    };
  }
}
#endif // STARBUCK_H
