#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

static void TaskBlinkGreenLED(void* pvParameters);

//-----------------------------------------------------------

int main()
{
  xTaskCreate(TaskBlinkGreenLED, (const portCHAR*) "GreenLED", 256, NULL, 3, NULL);
  vTaskStartScheduler();

  while(1);

  return 0;
}

//-----------------------------------------------------------

// Main Green LED Flash
static void TaskBlinkGreenLED(void* pvParameters)
{
  // set pin 5 of PORTB for output
  DDRB |= _BV(DDB5);

  TickType_t xLastWakeTime = xTaskGetTickCount();
  while (1)
  {
    // LED on
    PORTB |= _BV(PORTB5);
    vTaskDelayUntil(&xLastWakeTime, (1000 / portTICK_PERIOD_MS));

    // LED off
    PORTB &= ~_BV(PORTB5);
    vTaskDelayUntil(&xLastWakeTime, (1000 / portTICK_PERIOD_MS));
  }

  vTaskDelete(NULL);
}
