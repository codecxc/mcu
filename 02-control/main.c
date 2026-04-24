#include "protocol-task/protocol-task.h"
#include "stdio-task/stdio-task.h"
#include "led-task/led-task.h"
#include "pico/stdio.h"
#include <stdio.h>
#include "adc-task/adc-task.h"
#define DEVICE_VRSN "v0.0.1"
#define DEVICE_NAME "pico"
void version_callback(const char* args)
{
	printf("device name: '%s', firmware version: %s\n", DEVICE_NAME, DEVICE_VRSN);
}
void led_on_callback(const char* args) {
    printf("state: '%s'\n", "ON");
    led_task_state_set(LED_STATE_ON);
}
void led_off_callback(const char* args) {
    printf("state: '%s'\n", "OFF");
    led_task_state_set(LED_STATE_OFF);
}
void led_blink_callback(const char* args) {
    printf("state: '%s'\n", "BLINK");
    led_task_state_set(LED_STATE_BLINK);
}
void led_blink_set_period_ms_callback(const char* args) {
    uint period_ms = 0;
    sscanf(args, "%u", &period_ms);
    if(period_ms==0) printf("error");
    led_task_set_blink_period_ms(period_ms);


}
void mem_callback(const char* args) {

    
    uint32_t addr = 0;

    mem(addr);
}

void wmem_callback(const char* args) {

    
    uint32_t addr = 0;
    uint32_t value = 0;
    

    
    wmem(addr, value);
}
void help(const char* args);


api_t device_api[] =
{
	{"version", version_callback, "get device name and firmware version"},
    {"on", led_on_callback, "switch on led"},
    {"off", led_off_callback, "switch off led"},
    {"blink", led_blink_callback, "provide unblocking"},
    {"set_period", led_blink_set_period_ms_callback, "blinking with arguments"},
    {"mem", mem_callback, "read from memory"},
    {"wmem", wmem_callback, "write in memory"},
    {"help", help, "print commands description"},
	{NULL, NULL, NULL},
};

int device_api_size=8;

void help(const char* args) {
    for(int i=0;i<device_api_size;++i) {
        printf("Команда %s : %s\n", device_api[i].command_name,device_api[i].command_help);
    }
}

int main() {
    stdio_init_all();
    protocol_task_init(device_api);
    stdio_task_init();
    init_led_task();
    while(1) {
        char* t=stdio_task_handle();
        if(t!=NULL) {
            protocol_task_handle(t); 
        }
        handle_led_task();
        
        
    }

} 

