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
#include "irimstagewebview.h"

using namespace BlackBerry::Starbuck::IPCChannel;

class QtStageWebView :	public QWebView, public IStarbuckWebView
{
	Q_OBJECT

public:
	QtStageWebView(QWidget *parent = 0);
	~QtStageWebView(void);

  /**
	 * Loads the page at the specified URL.
	 * @param url The URL of the content to display.
     */
	void loadURL(QString url);
	
	/**
     * Halts the current load operation.
     */
	void stop();

	/**
     * Reloads the current page.
     */
	void reload();

	/**
     * Determines whether there is a previous page in the browsing history.
     *
     * @return <code>true</code> if a page is available in history, otherwise <code>false</code>. 
     */
	bool isHistoryBackEnabled();
	
	/**
     * Navigates to the previous page in the browsing history.
     */
	void historyBack();

	/**
     * Determines whether there is a next page in the browsing history.
     *
     * @return <code>true</code> if there is a next page in the browser history, otherwise <code>false</code>.
     */
	bool isHistoryForwardEnabled();
	
	/**
     * Navigates to the next page in the browsing history.
     */
	void historyForward();

	/**
     * The URL of the current location.
     */
	QString location();

    void setWindowGeometry(int x, int y, int w, int h)
    {
        setGeometry(x,y,w,h);
    }

	/**
     * The HTML title value.
     */
	QString title();

	/**
     * The area on the stage in which the <code>QtStageWebView</code> object is displayed.     
     */
	QRect viewPort();

	/**
     * Set the area on the stage in which the <code>QtStageWebView</code> object is displayed.   
	 * @param rect The area to set the view port to
     */
	void  viewPort(QRect rect);	
	
	/**
     * The URL of the originally entered location before any redirects.
     */
	QString originalLocation();

	/**
     * The length of the history list.
     */
	int historyLength();

	/**
     * The position of the currently active page in the history list. Note that 0 is the back of
     * the list.
     */
	int historyPosition();

	/**
     * Set the position of the currently active page in the history list. Note that 0 is the back of
     * the list.
     */
	void historyPosition(int position);

	
	/**
     * The private browsing flag tells the <code>QtStageWebView</code> object to enable private browsing mode.
     * Existing cookies are not used and no browsing information is saved. 
     *
     * <p>The default value of this property is <code>false</code>.</p>
     */
	bool privateBrowsing();
	void privateBrowsing(bool p);

	/**
     * The current scroll position of the content. If you set a value that extends past the edge of the
     * content, the value will be clamped to the proper value.
     */
	QPoint scrollPosition();

	/**
     * Set the current scroll position of the content. If you set a value that extends past the edge of the
     * content, the value will be clamped to the proper value.
	 * @param position The position to scroll to.
     */
	void scrollPosition(QPoint position);

	/**
     * Scroll the content by the specified amount (in pixels). 
     *
     * <p>
     * You may pass negative amounts here. If the amount
     * passed exceeds the edge of the content, the scroll will stop at the edge of the content automatically.
     * This function does not animate the scroll, scroll is moved to the new position as soon as possible.
     * </p>
     *
     * @param dx The distance to scroll horizontally.
     * @param dy The distance to scroll vertically.
     */
	void scrollBy(int dx, int dy);

	/**
     * The current text encoding of the content on the page.
     * <p> If you have not set a forced text encoding, this value will be either the auto-detected text encoding,
     * or the default text encoding. Otherwise, it is the forced text encoding.</p>
     */
	QString textEncoding();

	/**
	 * The default text encoding if the browser cannot auto-detect the encoding of the page.
	 *
	 * <p>The default value of this property is <code>utf-8</code>.</p>
	 */
	QString defaultTextEncoding();
	void defaultTextEncoding(QString textEncoding);

	/**
     * Forced text encoding is applied.
     *
     * <p>
     * This is used to override
     * a possibly incorrect decision by the browser about the encoding of a page. Set this value to nul
     * to cancel <code>forcedTextEncoding</code>.
     * </p>
     *
     * @default Nul
     */
	QString forcedTextEncoding();
	void forcedTextEncoding(QString textEncoding);

	/**
	 * Default font size is applied.
	 *
	 * <p>
	 * This is used to override the default font size for the browser. The range is 1 to 120.
	 * </p>
	 *
	 * @default 16
	 */
    int defaultFontSize();    
    void defaultFontSize(int fontSize);

	/**
     * The unique ID of the window.    
	 */
	QString windowUniqueId();

	/**
     * The user-agent that is currently reported by the browser to servers during HTTP requests and to web content
     * in scripts.
     */
	QString userAgent();
	void userAgent(QString userAgent);

	/**
     * Determines whether or not to enable the standard browser popup-blocking engine for generic <code>window.open</code> calls from
     * Javascript. When this is enabled, only user requested popups will be allowed.
     *
     * <p>The default value for this property is <code>true</code>.</p>
     */
	bool blockPopups();
	void blockPopups(bool block);

	/**
     * Determines whether or not to load images when the page is loading. If this value is set to <code>false</code> and you decide to
     * to load images, then you must set this flag to <code>true</code> and then reload the page.
     *
     * <p>The default value for this property is <code>true</code>.</p>
     */
	bool loadImages();
	void loadImages(bool loadImage);

	/**
     * Determines whether or not to execute Javascript.
     *
     * <p>The default value of this property is <code>true</code>.</p>
     */
	bool enableJavaScript();
	void enableJavaScript(bool javaScript);

	/**
     * Determines whether or not plugins should be enabled.
     *
     * <p>The default value of this property is <code>true</code>.</p>
     */
	bool enablePlugins();
	void enablePlugins(bool plugins);

	 /**
     * Determines whether or not cookies should be saved and sent back to pages.
     *
     * <p>The default value of this property is <code>true</code>.</p>
     */
	bool enableCookies();
	void enableCookies(bool cookies);

	/**
     * Determines whether or not web sockets should be available to pages.
     *
     * <p>The default value of this property is <code>true</code>.</p>
     */
	bool enableWebSockets();
	void enableWebSockets(bool webSockets);

	/**
     * Determines whether or not web inspector should be enabled.
     *
     * <p>The default value of this property is <code>false</code>.</p>
     */
	bool enableWebInspector();
	void enableWebInspector(bool webInspector);

	/**
     * Determines whether or not geolocation APIs should be enabled.
     *
     * <p>The default value of this property is <code>true</code>.</p>
     */
	bool enableGeolocation();
	void enableGeolocation(bool location);

	/**
    * Set whether a url is allowed access to geolocation information.
    * If a filter is not set for a site the user is prompted.
    */
	void updateGeolocationFilter(QString url, bool allow);
	
	/**
    * Remove the filter associated with a url.  This will cause the
    * user to be prompted if the site requests geolocation information.
    */
	void removeGeolocationFilter(QString url);

	/**
     * Determines whether or not to allow cross site XHR (XMLHttpRequest).
     *
     * <p>The default value of this property is <code>true</code>.</p>
     */
	bool enableCrossSiteXHR();
	void enableCrossSiteXHR(bool crossSiteXHR);

	/**
	 * Defines custom HTTP headers that are sent in addition to the standard headers.
	 *
	 * <p>The default value of this property is <code>nul</code>.</p>
	 */
	void customHTTPHeaders(char *headers[], unsigned int headersSize);
	void customHTTPHeaders(QString key, QString value);
	char** customHTTPHeaders();
	
	/**
     * Clears the following browsing data:
     * <ul>
     *   <li>Cookies</li>
     *   <li>Back-forward history</li>
     *   <li>Page-cache</li>
     *   <li>Authorizations</li>
     *   <li>Local Storage</li>
     *   <li>Password data<FIXME/></li>
     *   <li>Form data<FIXME/></li>
     * </ul>
     */
	void clearBrowsingData();
	void clearHistory();
	void clearCookies();
	void clearCache();
	void clearLocalStorage();

	/**
     * Executes the JavaScript code that is specified by <code>script</code> asynchronously.
     * <p>
     * This function will immediately return the result for this <code>executeJavaScript()</code> call.
     * @param script Specifies the block of JavaScript that will be executed.
     */
	QVariant executeJavaScript(QString script);

	/**
     * Specifies the timeout period (in seconds) after which a long running piece of JavaScript 
     * is interrupted. When JavaScript is interrupted, a <code>WebViewEvent.JAVASCRIPT_INTERRUPTED</code>
     * event is fired.
     *
     * <p>The default value for this property is <code>0</code> (seconds).</p>
     *
     */
	int javaScriptInterruptTimeout();
	void javaScriptInterruptTimeout(int timeout);

	/**
	 * Loads and displays the specified HTML string.
	 *
	 * <p>When the <code>loadString()</code> method is used, the <code>location</code>
	 * is reported as "about:blank." Only standard URI schemes can be used in URLs within
	 * the HTML string.
	 *
	 * <p>The HTML content cannot load local resources, such as image files. XMLHttpRequests
	 * are not allowed.</p>
	 *
	 * <p>Only the "text/html" and "application/xhtml+xml" MIME types are supported.</p>
	 *
	 * @param text The string of HTML or XHTML content to display.
	 * @param mimeType The MIME type of the content, either "text/html" or "application/xhtml+xml".
	 */
	void loadString(QString text, QString mimeType = "text/html");

	/**
     *
     * Loads and displays the specified HTML string with the specified baseURL.
     *
     * @param text The String of HTML or XHTML content to display.
     * @param baseURL The String of the URL that this content is reported to come from.
     * @param mimeType The MIME type of the content.
     */
	void loadStringWithBase(QString text, QString baseURL, QString mimeType = "text/html");

	/**
     * Retrieves the loading progress of the current page. If the page is fully loaded, this value will
     * remain at 100.
     */
	int loadProgress();

	/**
     * Specifies the <code>z</code>-order of the <code>QNXStageWebView</code> instance with respect to other windows that are children 
     * of the main applicaiton.
     * <p>
     * The stage always has a <code>z</code>-order of 0 with respect to children. Windows are painted by
     * the window manager from lowest <code>z</code>-order (backmost) to highest <code>z</code>-order (frontmost). Thus, specifying a value
     * less than 0 will move the <code>QNXStageWebView</code> instance behind the stage (and can be seen through the stage if the
     * stage is not opaque where the <code>QNXStageWebView</code> instance is being displayed). Specifying a value greater than or
     * equal to 0 will move the <code>QNXStageWebView</code> in front of the stage. You must manage the <code>z</code>-order of <code>QNXStageWebView</code>
     * objects if you have more than one, or need to use a special case such as moving behind the stage.
     * </p>
     * <p>The default value for this property is <code>0</code>.</p>
     *
     * <p>In the following listing, the <code>zOrder</code> property of a <code>QNXStageWebView</code> instance is set to -1 (hidden behind the stage) while the
     * class is loading an external URL. When the external content is loaded, the <code>onLoad</code> function is called and the <code>zOrder</code> property is set
     * to 0, which causes the <code>QNXStageWebView</code> to appear in front of the stage and visible to the user.
     * </p>
	 */
	int zOrder();
	void zOrder(int zed);

	/**
     * Specifies the visibility property for this <code>QNXStageWebView</code> instance.
     *
     * <p>The default value for this property is <code>false</code>.</p>
     */
	bool visible();
	void visible(bool enable);

	/**
     * Determines if the browser is active or inactive. 
     *
     * <p>The default value for this property is <code>true</code>.</p>
     */
	bool active();
	void active(bool isActive);

	/**
     * Determines if the browser will automatically zoom the page to fit the width of the viewport on load.
     *
     * <p>The default value for this property is <code>true</code>.</p>
     */
	bool zoomToFitWidthOnLoad();
	void zoomToFitWidthOnLoad(bool zoom);

	/**
     * Gets the current tool-tip.
     */
	QString tooltip();

	/**
     * Gets the current status bar content.
     */
	QString status();

	/**
     * Gets the favicon for the current page.
     */
	QBitmap favicon();
	
	// Set this to handle all dialogs
	void displayDefaultDialogs(bool display);
	
	/**
     * Specifies a user stylesheet which overrides the stylesheet that is set by the page.
     * To specify the stylesheet inline, use a <code>data://</code> URL. Set the <code>url</code> argument to nul to clear the user
     * stylesheet.
     *
     * @param url The String specifying the url to the stylesheet.
     */
	QString userStyleSheet();
	void userStyleSheet(QString url);

	/**
     * Finds and selects the next/last string that is a case-insensitive
     * match in the web page. It will wrap the web page if it reaches
     * the end. An empty String will result in no match and no selection.
     *
     * <p>This event will fire a <code>FindStringEvent</code> event after the search iss complete.</p>
     *
     * @param string The String specifying the text to find.
     * @param forward <code>true</code> if searching forward, or <code>false</code> if backwards.
     * @return <code>true</code> if the string matched and <code>false</code> if not.
     *
     * @see qnx.events.FindStringEvent FindStringEvent
     */
	void findString( QString string, bool forward = true);

	/**
     * Enables the following events on this webview.
     *
     * <ul>
     * <li><code>rim.events.NetworkResourceDataReceivedEvent</code></li>
     * <li><code>rim.events.NetworkResourceDoneEvent</code></li>
     * <li><code>rim.events.NetworkResourceHeaderReceivedEvent</code></li>
     * <li><code>rim.events.NetworkResourceOpenedEvent</code></li>
     * <li><code>rim.events.NetworkResourceRequestedEvent</code></li>
     * </ul>
     *
     * The default value of this property is <code>false</code>.
     */
	bool enableResourceFiltering();
	void enableResourceFiltering(bool enable);
	
	/**
     * Used in conjunction with the <code>NetworkResourceDataRequested</code> event to substitute the network
     * stream with a custom response code. Call this function first when substituting.
     *
     * This function simulates the result response from the server.
     *
     * @param streamId The stream specified in the event.
     * @param status The HTTP status code to return to the browser.
     * @param message The message to return to the browser.
     */
	void notifyResourceOpened(int streamId, int status, QString message);

	/**
     * Used in conjunction with the <code>NetworkResourceDataRequested</code> event to substitute the network
     * stream with custom data and headers. Send all headers before <code>notifyResourceDataReceived</code>
     * and <code>notifyResourceDone</code>, but after <code>notifyResourceOpened</code>.
     *
     * This function simulates the result response from the server.
     *
     * @param streamId The stream specified in the event.
     * @param key The name of the header property.
     * @param value The value of the header property.
     */
	void notifyResourceHeaderReceived(int streamId, QString key, QString value);

	/**
     * Used in conjunction with the <code>NetworkResourceDataRequested</code> event to substitute the network
     * stream with custom data and headers. Send all data before <code>notifyResourceDone</code>, but after 
     * <code>notifyResourceOpened</code> and <code>notifyResourceHeaderReceived</code>.
     *
     * This function simulates data being received from the server.
     *
     * @param streamId The stream specified in the event.
     * @param data The raw stream of bytes to be loaded by the browser.
     */
    void notifyResourceDataReceived(int streamId, QByteArray data);

	/**
     * Used in conjunction with the <code>NetworkResourceDataRequested</code> event to substitue the network
     * stream with custom data and headers. Should only be called last, after <code>notifyResourceOpened</code>
     * <code>notifyResourceHeaderReceived</code> and <code>notifyResourceDataReceived</code>. After this function is called
     * the streamId is no longer valid and should be discarded.
     *
     * This function simulates data being received from the server.
     *
     * @param streamId The stream specified in the event.
     */
    void notifyResourceDone(int streamId);

	/**
     * Used in conjunction with the Download* events. Call this function to remove a
     * download from the download manager. If the download is still in progress it will
     * be cancelled.
     *
     * @param downloadId The download specified in the event.
     */
    void downloadRemove(unsigned int downloadId);

	/**
     * Used in conjunction with the Download* events. Call this function to cancel a
     * download in the download manager. The download will remain in the download manager
     * until removed.
     *
     * @param downloadId The download specified in the event.
     */
    void downloadCancel(unsigned int downloadId);


	/**
     * Used in conjunction with the Download* events. Call this function to pause a
     * download in the download manager.
     *
     * @param downloadId The download specified in the event.
     */
    void downloadPause(unsigned int downloadId);

	/**
     * Used in conjunction with the Download* events. Call this function to resume a
     * paused download in the download manager.
     *
     * @param downloadId The download specified in the event.
     */
    void downloadResume(unsigned int downloadId);

	 /**
     * Used in conjunction with the Download* events. Call this function to set the
     * download action to take for a pending download.
     *
     * @param downloadId The download specified in the event.
     * @param action The action to take from WebDownloadRequestEvent::ACTION_*
     * @param filename The name to save the file as if the aciton is save. Must not be null or empty.
     */
    void downloadUpdate(unsigned int downloadId, QString action, QString filename);
	
	/**
     * Retrieves the security type for the currently displayed page.
     */
    QString secureType();

	/**
     * Retrieves the encryption info for the currently displayed page.
     */
    QString encryptionInfo();

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
  
  void registerEventbus();

  public slots:
    void continueLoad();
private slots:
	void notifyUrlChanged(const QUrl& url);
	void notifyJavaScriptWindowObjectCleared();
};
#endif //QTSTAGEWEBVIEW_H
