//
//  ScrollHandler.cpp
//  Starbuck
//
//  Created by User on 9/27/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <ScrollHandler.h>
#include <QApplication>
#include "stdafx.h"

ScrollHandler::ScrollHandler(QtStageWebView *parent)
{
    m_pWebView = parent;
    m_pTimer = new QTimer(this);
    m_pMutex = new QMutex();
    m_flag = true;
}

ScrollHandler::~ScrollHandler()
{

}

void ScrollHandler::unlock()
{
    if (m_pWebView->page()->currentFrame()->scrollBarValue(Qt::Vertical) > m_pWebView->page()->currentFrame()->scrollBarMinimum(Qt::Vertical) &&m_pWebView->page()->currentFrame()->scrollBarValue(Qt::Vertical) < m_pWebView->page()->currentFrame()->scrollBarMaximum(Qt::Vertical))
    {
         m_pWebView->lock.lock();
        m_flag = true;
    }
    else
    {
        m_flag = true;
    }
}

bool ScrollHandler::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::Wheel) {
        if (m_flag)
        {
            QObject::eventFilter(obj, event);
            m_flag = false;
            m_pTimer->singleShot(20, this, SLOT(unlock()));
            return false;
        }
        else
            return true;
    } else {
        // standard event processing
        //qDebug() << event->type();
        
        return QObject::eventFilter(obj, event);
    }    
    
}
