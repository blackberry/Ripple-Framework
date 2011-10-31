# Ripple - Framework

**THIS REPOSITORY IS CONSIDERED A WORK IN PROGRESS**

Ripple is a browser based, platform agnostic mobile application development and testing tool.  This specific repository contains the Qt framework portion of the Ripple product.

Currently Ripple is a Chrome Extension that will soon be migrating to this Qt framework to provide further enhanced emulation.
 
The project is Open Sourced under the Apache 2.0 license 
 
[Read more about Ripple](http://developer.blackberry.com/html5/download/ripple) 

## Build Requirements
 
* Qt Framework

## Downloads
* Coming Soon

## Reference Material &amp; Community
You can also find associated reference material for the Ripple tool as well as contributor forums at the following locations.

* [Contributor Forums](http://supportforums.blackberry.com/t5/Ripple-Contributions/bd-p/ripple)
* [Documentation](http://developer.blackberry.com/html5/documentation)

## Getting Started
* Coming Soon

## Building the Source Code

# Windows (QtWebKit)
* Make sure Qt 4.7.3 is setup on your system and configured properly.
* Use the provided qmake projects to compile.
* Once compiled add reference to custom QtWebKit in Ripple project.

# Windows (framework only)
* Create a build directory in your root folder (mkdir build).
* cd build
* cmake ..
* Open resulting solution file in Visual Studio and build.

# Linux (Ubuntu) (QtWebKit)
* Be sure you have all the necessary packages to build: libqt4-dev, libxrender-dev, libsqlite3-dev
* Run qmake in root folder.
* make
* Copy custom lib.so files into Ripple folder to be linked.

# Linux (Ubuntu) (framework only)
* Be sure you have all the necessary packages to build: cmake, libqt4-dev
* cmake .
* make

# MacOS X
* Coming soon

## Testing the Source Code
*Coming Soon*
