#include "pico/stdlib.h"
#include "hardware/gpio.h"

const uint LED_PIN = 25;


int main()
{
stdio_init_all();
gpio_init(LED_PIN); // инициализация
gpio_set_dir(LED_PIN, GPIO_OUT); // инициализация на выходное напряжение
while (1) // логика
{
gpio_put(LED_PIN, 1); // подать 1
sleep_ms(250);
gpio_put(LED_PIN, 0); // подать 0
sleep_ms(1000);
}
}