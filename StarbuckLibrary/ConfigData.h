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

#include <QSettings>

class ConfigData
{

public:
	static ConfigData* getInstance();	
	~ConfigData(void);
	
	void writeSettings();
	
	QString toolingContent();
	void toolingContent(QString content);

	QSize windowSize();
	void windowSize(QSize size);

	QPoint windowPosition();
	void windowPosition(QPoint position);

    QString localStoragePath();
    void localStoragePath(QString path);

    QString buildServiceCommand();
    void buildServiceCommmand(QString cmd);

    unsigned short buildServicePort();
    void buildServicePort(unsigned short port);

private:

	ConfigData(void);	
	void readSettings();

	static const QString CONFIGURATION_FILE_NAME;
	static const QString APPLICATION_NAME_IN_SETTINGS;
	static const QString TOOLING_CONTENT_NAME_IN_SETTINGS;
	static const QString TOOLING_CONTENT_DEFAULT;
	static const QString MAIN_WINDOW_SIZE_NAME_IN_SETTINGS;
    static const QString LOCAL_STORAGE_PATH_IN_SETTINGS;
	static const QSize MAIN_WINDOW_SIZE_DEFAULT;
	static const QString MAIN_WINDOW_POSITION_NAME_IN_SETTINGS;
	static const QPoint MAIN_WINDOW_POSITION_DEFAULT;
    static const QString LOCAL_STORAGE_PATH_DEFAULT;
    static const QString BUILD_SERVICE_COMMAND_IN_SETTINGS;
    static const QString BUILD_SERVICE_COMMAND_DEFAULT;
    static const QString BUILD_SERVICE_PORT_IN_SETTINGS;
    static const QString BUILD_SERVICE_PORT_DEFAULT;

	static ConfigData* _instance;
	static bool _instanceFlag;
	QSettings *_settings;

	QString _toolingContent;
	QSize _mainWindowSize;
	QPoint _mainWindowPosition;	
    QString _localStoragePath;
    QString _buildServiceCommand;
    QString _buildServicePort;
};
