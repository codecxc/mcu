#include "stdio.h"
#include "stdlib.h"
#include "pico/stdlib.h"

#define DEVICE_VRSN "v0.0.1"

const uint LED_PIN = 25;

int main() {
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while(1) {
        char symbol=getchar();
        if(symbol=='e') {gpio_put(LED_PIN, 1);printf("received char: %c [ ASCII code: %d ]\n", symbol, symbol);}
        else if(symbol=='d') {gpio_put(LED_PIN, 0);printf("received char: %c [ ASCII code: %d ]\n", symbol, symbol);}
        else if(symbol=='v') {printf(DEVICE_VRSN);printf("received char: %c [ ASCII code: %d ]\n", symbol, symbol);} 
        else  {
            printf("received char: %c [ ASCII code: %d ]\n", symbol, symbol);
        }
    }
}
/*
int main() {
    stdio_init_all();
    while(1) {
        char symbol = getchar();
        printf("received char: %c [ ASCII code: %d ]\n", symbol, symbol);
    }

}*/