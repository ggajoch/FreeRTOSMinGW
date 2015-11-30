#include <cstdio>

extern "C" {
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
}

xQueueHandle queue;

void TxTask(void *pvParameters) {
    float x = 0;
    while (true) {
        printf("sending %f...\n", x);
        xQueueSend(queue, &x, portMAX_DELAY);
        x += 0.1;
        vTaskDelay(1000); // 1 second
    }
}


void RxTask(void *pvParameters) {
    while (true) {
        float received;
        if (xQueueReceive(queue, &received, portMAX_DELAY) == pdTRUE) {
            printf("received: %f\n", received);
        }
    }
}

int main() {
    queue = xQueueCreate(1000, sizeof(float));

    xTaskCreate(RxTask, "Rx", 1000, NULL, 1, NULL);
    xTaskCreate(TxTask, "Tx", 1000, NULL, 1, NULL);

    vTaskStartScheduler();
    return 0;
}