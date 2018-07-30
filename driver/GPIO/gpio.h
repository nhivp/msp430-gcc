
#include <stdint.h>

typedef enum
{
    PORT_1 = 0,
    PORT_2

} GPIO_Port_t;

typedef enum
{
    PIN_0 = 0,
    PIN_1,
    PIN_2,
    PIN_3,
    PIN_4,
    PIN_5,
    PIN_6,
    PIN_7
} GPIO_Pin_t;

typedef struct
{
    GPIO_Port_t    Port;
    GPIO_Pin_t     Pin;
} GPIO_t;

typedef enum
{

} GPIO_Direction_t;

typedef enum
{

} GPIO_Edge_t;

typedef void (*GPIO_Callback_t)(GPIO_Port_t aPort, uint8_t aResult);

extern uint8_t GPIO_Initialize(GPIO_Port_t aPort, GPIO_Direction_t aDir);
extern uint8_t GPIO_ConfigInterrupt(GPIO_Port_t aPort, GPIO_Edge_t aEdge, GPIO_Callback_t aCallBackFunc);
extern bool    GPIO_ReadPin(GPIO_Port_t aPort);
extern uint8_t GPIO_ReadPort(GPIO_Port_t aPort);
extern uint8_t GPIO_WritePin(GPIO_Port_t aPort, bool aValue);
extern uint8_t GPIO_WritePort(GPIO_Port_t aPort, uint8_t aValue);
