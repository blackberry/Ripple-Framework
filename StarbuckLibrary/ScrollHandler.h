//
//  ScrollHandler.h
//  Starbuck
//
//  Created by User on 9/27/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef Starbuck_ScrollHandler_h
#define Starbuck_ScrollHandler_h

#include <QObject>
#include <QTimer>
#include <QMutex>
#include <QEvent>
#include "QtStageWebView.h"

class ScrollHandler : public QObject {
    Q_OBJECT
    QtStageWebView *m_pWebView;
    QTimer *m_pTimer;
    QMutex *m_pMutex;
    bool m_flag;
public:
    ScrollHandler(QtStageWebView *parent);
    ~ScrollHandler();
public slots:
    void unlock();
    
protected:
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif
