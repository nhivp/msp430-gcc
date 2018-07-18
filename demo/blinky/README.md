# Blinky Prj

## Without Makefile

* Compile

  ```shell
  $ cd blinky
  $ msp430-elf-gcc -I ~/tools/msp430-elf/include -L ~/tools/msp430-elf/lib/ldscripts -T ~/tools/msp430-elf/lib/ldscripts/msp430g2553.ld -mmcu=msp430g2553 -O2 -g blink.c -o blink.o
  ```

* Flash

  ```shell
  $ mspdebug rf2500
  (mspdebug) prog blink.o
  (mspdebug) run
  ```
