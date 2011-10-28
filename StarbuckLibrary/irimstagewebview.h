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

#pragma once

namespace BlackBerry {
namespace Starbuck {
namespace IPCChannel {
class IStarbuckWebView
{
public:
	virtual void loadURL(QString url) = 0;
	virtual void enableCrossSiteXHR(bool crossSiteXHR) = 0;
	virtual QVariant executeJavaScript(QString script) = 0;
	virtual QString location() = 0;
	virtual void historyBack() = 0;
	virtual void historyForward() = 0;
	virtual bool isHistoryBackEnabled() = 0;
	virtual bool isHistoryForwardEnabled() = 0;
	virtual int historyLength() = 0;
	virtual int historyPosition() = 0;
	virtual void historyPosition(int position) = 0;
	virtual void setWindowGeometry(int x, int y, int w, int h) = 0;
    virtual void reload() = 0;
  virtual void setZoom(float zoom) = 0;
  virtual float zoom() = 0;
};
}}}
