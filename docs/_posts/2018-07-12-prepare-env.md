---
layout: post
title: "Preparing the environment"
author: "Nhi Pham"
---

The following are required tools for the MSP430 programming.

## gcc-msp430

* Installing
  >$ sudo apt install gcc-msp430
* Make sure we installed successfully
  >$ msp430-gcc --version

## mspdebug

* Install libraries dependecy:
  >$ sudo apt-get install libusb-dev sudo apt-get install libreadline-dev
* Get a latest version at https://github.com/dlbeer/mspdebug/releases
* Unzip this source to somewhere: ```tar xvfz mspdebug-0.25.tar.gz```
* Go to its source code: ```cd mspdebug-0.25/```
* Compiling .. ```make```
* And finally install it ```make install```
* Make sure we installed successfully
    ```mspdebug --version```