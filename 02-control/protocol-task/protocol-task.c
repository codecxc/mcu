#include "protocol-task.h"
#include <string.h>
#include <stdio.h>

static api_t* api = NULL;
static int commands_count = 0;

void protocol_task_init(api_t* device_api) {
    api = device_api;
    int c = 0;
    if (api != NULL) {
        while (api[c].command_name != NULL) {
            c++;
        }
    }
    commands_count = c;
}

void protocol_task_handle(char* command_string) {
    // Добавляем в обработчик проверку на то, что `command_string` не равно `NULL`.
    // Если `command_string` равно `NULL`, то выйти из обработчика: строка команды
    // еще не получена;
    if (command_string == NULL) {printf("ошибка");return;}
    
    // логика обработки полученной строки. Делим ее на команду и аргументы:
    const char* command_name = command_string;
    const char* command_args = NULL;
    
    char* space_symbol = strchr(command_string, ' ');
    
    if (space_symbol) {
        *space_symbol = '\0';
        command_args = space_symbol + 1;
    } else {
        command_args = "";
    }
    
    // Добавляем вывод найденных имени команды и ее аргументов;
    printf("Command: %s, Args: %s\n", command_name, command_args);
    
    // в цикле проходим по массиву команд `api` и ищем совпадение имени команды;
    for (int i = 0; i < commands_count; i++) {

        if (strcmp(api[i].command_name, command_name) == 0) {
            // ваш код

            api[i].command_callback(command_args);
            return;
        }
    }
    
    printf("не найдено: %s\n", command_name);
    return;
}


void mem(uint32_t addr) {
    volatile uint32_t* ptr = (volatile uint32_t*)addr;
    uint32_t value = *ptr;
    printf("Address: 0x%08X, Value: 0x%08X (%u)\n", addr, value, value);
}

void wmem(uint32_t addr, uint32_t value) {
    volatile uint32_t* ptr = (volatile uint32_t*)addr;
    *ptr = value;
    printf("Written 0x%08X to address 0x%08X\n", value, addr);
}