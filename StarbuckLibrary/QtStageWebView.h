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

#ifndef QTSTAGEWEBVIEW_H
#define QTSTAGEWEBVIEW_H

#include <QWidget>
#include <QString>
#include <QRect>
#include <QPoint>
#include <QNetworkRequest>
#include <QTimer>
#include <QObject>
#include <QWebView>
#include <QWebHistory>
#include <QWebFrame>
#include <QMutex>
#include <QGraphicsWebView>
#include <QGraphicsView>
#include <QGraphicsSceneContextMenuEvent>
#include <QPaintEvent>
#include <QWebInspector>
#include "irimstagewebview.h"

class ScrollHandler;
class RemoteDebugger;

using namespace BlackBerry::Starbuck::IPCChannel;

class QtStageWebView :	public QGraphicsWebView, public IStarbuckWebView
{
	Q_OBJECT
    ScrollHandler *m_pScrollHandler;
    RemoteDebugger *m_pRemoteDebugger;
    QWebInspector *m_inspector;
protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
public:
	QtStageWebView(QWidget *parent = 0);
	~QtStageWebView(void);
    QMutex lock;
	void loadURL(QString url);
	void reload();
	bool isHistoryBackEnabled();
	void historyBack();
	bool isHistoryForwardEnabled();
	void historyForward();
	QString location();
    void setWindowGeometry(int x, int y, int w, int h)
    {
        QGraphicsWidget::setGeometry(x, y, w, h);
    }
	QString title();	
	int historyLength();
	int historyPosition();
	void historyPosition(int position);
	bool enableCrossSiteXHR();
	void enableCrossSiteXHR(bool crossSiteXHR);
	void customHTTPHeaders(char *headers[], unsigned int headersSize);
	void customHTTPHeaders(QString key, QString value);
	char** customHTTPHeaders();
	QVariant executeJavaScript(QString script);
	bool visible();
	void visible(bool enable);
  void setZoom(float zoom);
  float zoom ();

	//certificateInfo
	//fullscreenClientGet
	//fullscreenClientRelease
	//fullscreenNativeInit
	//fullscreenExited
signals:
	void urlChanged(QString);
	void javaScriptWindowObjectCleared();
    void jsLoaded();
private:
//	QObject *locationChangeListenerObj;
//	char *locationChangeListenerMethod;
    char **_headers;
    unsigned int _headersSize;
    bool waitForJsLoad;
  
//  void registerEventbus();

  public slots:
    void continueLoad();
private slots:
	void notifyUrlChanged(const QUrl& url);
	void notifyJavaScriptWindowObjectCleared();
};

class QtGraphicsStageWebView : public QGraphicsView
{
    Q_OBJECT
public:
    QtGraphicsStageWebView(QWidget *parent) : QGraphicsView(parent)
    {
        m_pWebView = new QtStageWebView;
        setScene(new QGraphicsScene());
        scene()->addItem(m_pWebView);
        scene()->setFocusItem(m_pWebView);
        setFrameShape(QFrame::NoFrame);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    
    };
    QtStageWebView *qtStageWebView() const { return m_pWebView; };
    void paintEvent(QPaintEvent *pe) { QGraphicsView::paintEvent(pe); qtStageWebView()->lock.unlock(); };
private:
    QtStageWebView *m_pWebView;
};

#endif //QTSTAGEWEBVIEW_H
