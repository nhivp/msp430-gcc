# Serial Console

## To-Do

Implement tiny printf in c

* using alias attribute https://gcc.gnu.org/onlinedocs/gcc-4.0.2/gcc/Function-Attributes.html#Function-Attributes
* or re-define the printf

  ```c
  #ifdef printf
  # undef printf
  # define printf			rcar_printf
  #endif	/* printf */
    ```

* test performance
  * Performance profiling
  *

## Reference

* [tiny_printf](https://github.com/andersy005/embedded-systems-programming/blob/master/MicroComputer-Based-Lock/src/tiny_printf.c)
* [xil_printf](https://github.com/cjlano/freertos/blob/master/FreeRTOS/Demo/MicroBlaze_Kintex7_EthernetLite/BSP/microblaze_0/libsrc/standalone_v5_4/src/xil_printf.c)
