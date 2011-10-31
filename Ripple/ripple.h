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

#ifndef RIPPLE_H
#define RIPPLE_H

#include <QMainWindow>
#include <QWebPage>
#include <QProgressBar>
#include <QGLWidget>
#include "ConfigData.h"
#include <qwebinspector.h>
#include "StageViewMsgHandler.h"
#include "QtStageWebView.h"

using namespace BlackBerry::Ripple::IPCChannel;

namespace BlackBerry 
{
  namespace Ripple 
  {
    class Ripple : public QMainWindow
    {
        Q_OBJECT

    public:
      Ripple(QWidget *parent = 0, Qt::WFlags flags = 0);
      ~Ripple();

    protected:
        void closeEvent(QCloseEvent *event);
        void resizeEvent(QResizeEvent * e );

    private slots:
        void registerAPIs();
        void urlChanged(QUrl &url);

    private:
        QGLWidget *_GLWidget;
        ScrollHandler *_scrollHandler;
        static const int PROGRESS_BAR_HEIGHT;
        QtGraphicsStageWebView* webViewInternal;
        QProgressBar* progressBar;
        ConfigData *_config;
        StageViewMsgHandler* m_pStageViewHandler;

        void init(void);    
    };
  }
}
#endif // RIPPLE_H
