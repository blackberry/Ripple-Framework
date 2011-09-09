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

#include "stdafx.h"
#include "ConfigData.h"

bool ConfigData::_instanceFlag = false;
ConfigData* ConfigData::_instance = NULL;

const QString ConfigData::CONFIGURATION_FILE_NAME = "config.ini";

const QString ConfigData::APPLICATION_NAME_IN_SETTINGS = "Ripple";
const QString ConfigData::TOOLING_CONTENT_NAME_IN_SETTINGS = "windowContent";
const QString ConfigData::MAIN_WINDOW_SIZE_NAME_IN_SETTINGS = "windowSize";
const QString ConfigData::MAIN_WINDOW_POSITION_NAME_IN_SETTINGS = "windowPos"; 
const QString ConfigData::LOCAL_STORAGE_PATH_IN_SETTINGS = "localStoragePath";
const QString ConfigData::BUILD_SERVICE_COMMAND_IN_SETTINGS = "buildServiceCommand";
const QString ConfigData::BUILD_SERVICE_PORT_IN_SETTINGS = "buildServicePort";
const QString ConfigData::TOOLING_CONTENT_DEFAULT = "index.html";
const QSize ConfigData::MAIN_WINDOW_SIZE_DEFAULT = QSize(400, 400);
const QPoint ConfigData::MAIN_WINDOW_POSITION_DEFAULT = QPoint(200, 200);
const QString ConfigData::LOCAL_STORAGE_PATH_DEFAULT = "";
const QString ConfigData::BUILD_SERVICE_COMMAND_DEFAULT = "services/bin/rbd_service.command";
const QString ConfigData::BUILD_SERVICE_PORT_DEFAULT = "9900";

ConfigData::ConfigData(void)
{
#ifdef Q_WS_WIN
	_applicationStoragePath = QString(getenv("APPDATA"));
	_applicationStoragePath += (QDir::separator() + QCoreApplication::organizationName());
	_applicationStoragePath += (QDir::separator() + QCoreApplication::applicationName());
#else
	_applicationStoragePath = QCoreApplication::applicationDirPath();
#endif

	QString config_path(_applicationStoragePath + QDir::separator() + CONFIGURATION_FILE_NAME);
	_settings = new QSettings(config_path, QSettings::IniFormat);

    readSettings();
}

ConfigData::~ConfigData(void)
{
	_instanceFlag = false;	
	_instance = NULL;

	delete _settings;
}

ConfigData* ConfigData::getInstance(void)
{
    if (!_instanceFlag)
    {
        _instance = new ConfigData();
        _instanceFlag = true;
        return _instance;
    }
    else
    {
        return _instance;
    }
}

void ConfigData::writeSettings()
{
	_settings->beginGroup(APPLICATION_NAME_IN_SETTINGS);
	_settings->setValue(MAIN_WINDOW_SIZE_NAME_IN_SETTINGS, _mainWindowSize);
	_settings->setValue(MAIN_WINDOW_POSITION_NAME_IN_SETTINGS, _mainWindowPosition);
	_settings->setValue(TOOLING_CONTENT_NAME_IN_SETTINGS, _toolingContent);
	_settings->setValue(LOCAL_STORAGE_PATH_IN_SETTINGS, _localStoragePath);
    _settings->setValue(BUILD_SERVICE_COMMAND_IN_SETTINGS, _buildServiceCommand);
    _settings->setValue(BUILD_SERVICE_PORT_IN_SETTINGS, _buildServicePort);
	_settings->endGroup();
}

void ConfigData::readSettings()
{
	_settings->beginGroup(APPLICATION_NAME_IN_SETTINGS);
	_mainWindowSize = _settings->value(MAIN_WINDOW_SIZE_NAME_IN_SETTINGS, MAIN_WINDOW_SIZE_DEFAULT).toSize();
	_mainWindowPosition = _settings->value(MAIN_WINDOW_POSITION_NAME_IN_SETTINGS, MAIN_WINDOW_POSITION_DEFAULT).toPoint();    
	_toolingContent = _settings->value(TOOLING_CONTENT_NAME_IN_SETTINGS, TOOLING_CONTENT_DEFAULT).toString();
	_localStoragePath = _settings->value(LOCAL_STORAGE_PATH_IN_SETTINGS, LOCAL_STORAGE_PATH_DEFAULT).toString();
	_buildServiceCommand = _settings->value(BUILD_SERVICE_COMMAND_IN_SETTINGS, BUILD_SERVICE_COMMAND_DEFAULT).toString();
	_buildServicePort = _settings->value(BUILD_SERVICE_PORT_IN_SETTINGS, BUILD_SERVICE_PORT_DEFAULT).toString();
	_settings->endGroup();
}

QString ConfigData::toolingContent()
{
    return _toolingContent;
}

void ConfigData::toolingContent(QString content)
{
    _toolingContent = content;
    writeSettings();
}

QSize ConfigData::windowSize()
{
    return _mainWindowSize;
}

void ConfigData::windowSize(QSize size)
{
    _mainWindowSize = size;
    writeSettings();
}

QPoint ConfigData::windowPosition()
{
    return _mainWindowPosition;
}

void ConfigData::windowPosition(QPoint position)
{
    _mainWindowPosition = position;
    writeSettings();
}

QString ConfigData::localStoragePath()
{
    if (_localStoragePath == "")
        return _applicationStoragePath;
    else
        return _localStoragePath;
}

void ConfigData::localStoragePath(QString path)
{
    _localStoragePath = path;
    writeSettings();
}

QString ConfigData::buildServiceCommand()
{
    return _buildServiceCommand;
}

void ConfigData::buildServiceCommmand(QString cmd)
{
    _buildServiceCommand = cmd;
}

unsigned short ConfigData::buildServicePort()
{
    return _buildServicePort.toUInt();
}

void ConfigData::buildServicePort(unsigned short port)
{
    _buildServicePort = QString::number(port);
}
