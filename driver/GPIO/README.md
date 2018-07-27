# GPIO

* Implementation of GPIO module.

## Functional Requirement

* [REQ-01] Config directions
  * Input
  * Output

* [REQ-02] Edge interrupt
  * Rise
  * Fall

* [REQ-03] State of driver
  * Unused
  * Used

* [REQ-04] Interrupt callback function

## _Restriction of the GPIO driver_

* Pin Oscillator: This feature should be implement separately as driver for touch pad.
* Function Select Registers: This setting will be configured by environment when other functions are used, due to the GPIO driver don't use this setting.

## API Design

Below are prototype of APIs function:

* ```uint8_t GPIO_Initialize(GPIO_Port_t aPort, GPIO_Pin_t aPin, GPIO_Direction_t aDir)```
* ```uint8_t GPIO_ConfigInterrupt(GPIO_Port_t aPort, GPIO_Pin_t aPin, GPIO_Edge_t aEdge, GPIO_Callback_t aCallBackFunc)```
* ```bool GPIO_ReadPin(GPIO_Port_t aPort, GPIO_Pin_t aPin)```
* ```uint8_t GPIO_ReadPort(GPIO_Port_t aPort)```
* ```uint8_t GPIO_WritePin(GPIO_Port_t aPort, GPIO_Pin_t aPin, bool aValue)```
* ```uint8_t GPIO_WritePort(GPIO_Port_t aPort, uint8_t aValue)```

## Detail design

| API Function         | Detail Function                                                           |||| Return |
|:---------------------|:--------------------------|:----------------|:--------------------|:---------|:------:|
| GPIO_Initialize      | GPIO_InitializeCheckParam |                 |                     | n/a      | NG     |
|                      |                           | GPIO_CheckState |                     | n/a      | NG     |
|                      |                           |                 | GPIO_CtrlInitialize | n/a      | OK     |
| GPIO_ConfigInterrupt |                           |                 |                     |          |        |
| GPIO_ReadPin         |                           |                 |                     |          |        |
| GPIO_ReadPort        |                           |                 |                     |          |        |
| GPIO_WritePin        |                           |                 |                     |          |        |
| GPIO_WritePort       |                           |                 |                     |          |        |
