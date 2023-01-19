#include <Arduino.h>
#include "CommandProcessor.h"
#include "ComponentCommands.h"

const char *words[] = {
    "jedan",
    "dva",
};

void commandQueueProcessorTask(void *param)
{
    CommandProcessor *commandProcessor = (CommandProcessor *)param;
    while (true)
    {
        uint16_t commandIndex = 0;
        if (xQueueReceive(commandProcessor->m_command_queue_handle, &commandIndex, portMAX_DELAY) == pdTRUE)
        {
            Serial.println("COMMANDQUEUEPROCESSORTASK");
            commandProcessor->processCommand(commandIndex);
       }
    }
}

void CommandProcessor::processCommand(uint16_t commandIndex)
{
    Serial.println(commandIndex);
    switch (commandIndex)
    {
    case 0:
        analogWrite(15, 255);
        Serial.println("TUSAM");
        //engageAction(); // Activate "servo"
        //controlRGB(255, 255, 255);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        break;
    case 1:
        analogWrite(15, 0);
        //controlRGB(0, 0, 0);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        break;
    /*case 2:
        analogWrite(14, 255);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        break;
    case 3:
        analogWrite(14, 0);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        break;*/
    default:
        disengageAction(); // turn the "servo" off
        controlRGB(0, 0, 0);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        break;
    }
}

CommandProcessor::CommandProcessor()
{
    pinMode(13, OUTPUT);
    pinMode(14, OUTPUT);
    // allow up to 5 commands to be in flight at once
    m_command_queue_handle = xQueueCreate(5, sizeof(uint16_t));
    if (!m_command_queue_handle)
    {
        Serial.println("Failed to create command queue");
    }
    // kick off the command processor task
    TaskHandle_t command_queue_task_handle;
    xTaskCreate(commandQueueProcessorTask, "Command Queue Processor", 1024, this, 1, &command_queue_task_handle);
}

void CommandProcessor::queueCommand(uint16_t commandIndex, float best_score)
{
    // unsigned long now = millis();
    if (commandIndex != 5 && commandIndex != -1)
    {
        Serial.printf("***** %ld Detected command %s(%f)\n", millis(), words[commandIndex], best_score);
        if (xQueueSendToBack(m_command_queue_handle, &commandIndex, 0) != pdTRUE)
        {
            Serial.println("No more space for command");
        }
    }
}
