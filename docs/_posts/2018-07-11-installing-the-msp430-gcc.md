---
layout: post
title: "Installing the GCC - Open Source Compiler for MSP Microcontrollers"
author: "Nhi Pham"
---

The MSP430 GCC compiler is owned by TI and maintained by Mitto Systems Limited.
Features:

* Available standalone or integrated within Code Composer Studio™
* No code size limitation
* Free and open source code
* CC and GDB binaries for Windows, Linux and Mac OS X
* MSP430 header and linker files
* GBD agent configuration based on MSP-FET debugger
* MSP430 debug stack support

For more information: [MSP430-GCC-OPENSOURCE](http://www.ti.com/tool/MSP430-GCC-OPENSOURCE)

Download the full source at [MSP430-GCC  6_0_1_0](http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSPGCC/latest/index_FDS.html)

Take a look at _MSP430-GCC Product downloads_ table, and downloading required files:

* msp430-gcc-7.3.1.24-source-full.tar.bz2
* msp430-gcc-support-files-1.205.zip

And now we are installing together.

* Step 1: Unzip the source at somewhere. And installing some pre-requisites

  ```shell
  $ tar xvf msp430-gcc-7.3.1.24-source-full.tar.bz2
  $ sudo apt-get install build-essential flex bison texinfo curl
  ```

* Step 2: Move into the source and install.

  ```shell
  $ cd msp430-gcc-7.3.1.24-source-full
  $ chmod u+x README-build.sh
  $ ./README-build.sh
  ```

* Step 3: Make a coffe and waitting for installing successfully. :clock7:

  Relax! :notes:

* Step 4: Enjoy your result.

  ```shell
  $ msp430-elf-gcc --version
  ```

End! :trollface: Good luck!