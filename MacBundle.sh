#!/bin/bash

echo Cleaning up Starbuck.app
cd build/bin/Starbuck.app/Contents/MacOS

echo Moving libpng
cp /Library/Frameworks/libpng.framework/Versions/1.4.5/libpng ../Frameworks/libpng.framework/Versions/1.4.5/

echo Changing reference paths using install_name_tool
install_name_tool -change /Users/jasscott/QtSDK/Desktop/Qt/473/gcc/lib/QtGui.framework/Versions/Current/QtGui @executable_path/../Frameworks/QtGui.framework/Versions/4/QtGui libwebkit.dylib
install_name_tool -change /Users/jasscott/QtSDK/Desktop/Qt/473/gcc/lib/QtSql.framework/Versions/Current/QtSql @executable_path/../Frameworks/QtSql.framework/Versions/Current/QtSql libwebkit.dylib
install_name_tool -change /Users/jasscott/QtSDK/Desktop/Qt/473/gcc/lib/QtNetwork.framework/Versions/Current/QtNetwork @executable_path/../Frameworks/QtNetwork.framework/Versions/4/QtNetwork libwebkit.dylib
install_name_tool -change /Users/jasscott/QtSDK/Desktop/Qt/473/gcc/lib/QtCore.framework/Versions/Current/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/4/QtCore libwebkit.dylib
install_name_tool -change /Users/jasscott/QtSDK/Desktop/Qt/473/gcc/lib/QtXml.framework/Versions/Current/QtXml @executable_path/../Frameworks/QtXml.framework/Versions/Current/QtXml libwebkit.dylib

install_name_tool -change libwebkit.dylib @executable_path/../MacOS/libwebkit.dylib libwebkit.dylib
install_name_tool -change libAmanithVG_SRE.dylib @executable_path/../MacOS/libAmanithVG_SRE.dylib libwebkit.dylib

install_name_tool -change libAmanithVG_SRE.dylib @executable_path/../MacOS/libAmanithVG_SRE.dylib libEGL_AM.dylib
install_name_tool -change libEGL_AM.dylib @executable_path/../MacOS/libEGL_AM.dylib libEGL_AM.dylib


echo Done cleaning up Starbuck.app
