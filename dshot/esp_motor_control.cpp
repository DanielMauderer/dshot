#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "systeminfo.h"

extern "C" {
   void app_main();
}
 
void app_main()
{
    printf("Hello world!\n");
 
    /* Print chip information */
    esp_systeminfo info;
    info.print();
 
    for (int i = 10; i >= 0; i--) {
        printf("Restarting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    printf("Restarting now.\n");
    fflush(stdout);
    esp_restart();
}