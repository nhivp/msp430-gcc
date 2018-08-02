# Serial Console

## To-Do

Implement tiny printf in c

* using alias attribute

  ```c
  /* Create aliases for *printf to integer variants *iprintf */
  __attribute__ ((alias("mcu_printf"))) int printf(const char *fmt, ...);
  ```

* or re-define the printf

  ```c
  #ifdef printf
  # undef printf
  # define printf			mcu_printf
  #endif	/* printf */
    ```

* test performance

  * Performance profiling
  * memory footprint

## Reference

* [tiny_printf](https://github.com/andersy005/embedded-systems-programming/blob/master/MicroComputer-Based-Lock/src/tiny_printf.c)
* [xil_printf](https://github.com/cjlano/freertos/blob/master/FreeRTOS/Demo/MicroBlaze_Kintex7_EthernetLite/BSP/microblaze_0/libsrc/standalone_v5_4/src/xil_printf.c)
* [A tiny printf for embedded applications](http://www.sparetimelabs.com/tinyprintf/tinyprintf.php)
* [__attribute__((alias)) function attribute](http://www.keil.com/support/man/docs/armcc/armcc_chr1359124973698.htm)
* [gcc- Function-Attributes](https://gcc.gnu.org/onlinedocs/gcc-4.0.2/gcc/Function-Attributes.html#Function-Attributes)
* [Embedded System Text Formatting](https://github.com/pabigot/embtextf)