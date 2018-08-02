/*****************************************************************************
 * Includes <Header Files>
 *****************************************************************************/
#include "drv.h"

/*****************************************************************************
 * Macro definitions
 *****************************************************************************/
#define GPIO_PORT_NUM    2
#define GPIO_PIN_NUM     8

/*****************************************************************************
 * Typedef definitions
 *****************************************************************************/
typedef enum
{
    /* Pin P1.x */
    GPIO_PIN_10 = 0,  /* Pin 0 */
    GPIO_PIN_11,      /* Pin 1 */
    GPIO_PIN_12,      /* Pin 2 */
    GPIO_PIN_13,      /* Pin 3 */
    GPIO_PIN_14,      /* Pin 4 */
    GPIO_PIN_15,      /* Pin 5 */
    GPIO_PIN_16,      /* Pin 6 */
    GPIO_PIN_17,      /* Pin 7 */

    /* Pin P2.x */
    GPIO_PIN_20,      /* Pin 0 */
    GPIO_PIN_21,      /* Pin 1 */
    GPIO_PIN_22,      /* Pin 2 */
    GPIO_PIN_23,      /* Pin 3 */
    GPIO_PIN_24,      /* Pin 4 */
    GPIO_PIN_25,      /* Pin 5 */
    GPIO_PIN_26,      /* Pin 6 */
    GPIO_PIN_27       /* Pin 7 */
} GPIO_Pin_t;

typedef enum
{
    GPIO_DIR_IN = 0, /* The port pin is switched to input direction */
    GPIO_DIR_OUT     /* The port pin is switched to output direction */
} GPIO_Direction_t;

typedef enum
{
    GPIO_EDGE_RISE = 0, /* The PxIFGx flag is set with a low-to-high transition */
    GPIO_EDGE_FALL      /* The PxIFGx flag is set with a hogh-to-low transition */
} GPIO_Edge_t;

typedef enum
{
    GPIO_IO_FUNC = 0,   /* I/O function is selected. */
    GPIO_PRIMARY_FUNC,  /* Primary peripheral module function is selected. */
    GPIO_SECONDARY_FUNC /* Secondary peripheral module function is selected. */
} GPIO_FunctionSel_t;

typedef void (*GPIO_Callback_t)(GPIO_Pin_t aPin, uint8_t aResult);

/*****************************************************************************
 * Function prototypes
 *****************************************************************************/
extern void    GPIO_Initialize(GPIO_Pin_t aPin, GPIO_Direction_t aDir);
extern void    GPIO_ConfigInterrupt(GPIO_Pin_t aPin, GPIO_Edge_t aEdge, GPIO_Callback_t aCallBackFunc);
extern bool    GPIO_ReadPin(GPIO_Pin_t aPin);
extern uint8_t GPIO_ReadPort(GPIO_Pin_t aPin);
extern void    GPIO_WritePin(GPIO_Pin_t aPin, bool aValue);
extern void    GPIO_WritePort(GPIO_Pin_t aPin, uint8_t aValue);
extern void    GPIO_SelectFunc(GPIO_Pin_t aPin, GPIO_FunctionSel_t aFuncSel);
/*****************************************************************************
 * End of File.
 *****************************************************************************/