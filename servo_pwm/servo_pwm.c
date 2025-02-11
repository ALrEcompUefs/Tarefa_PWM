#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

// PARAMÊTROS PAR PWM
const uint16_t WRAP_PERIOD = 10000; //valor máximo do contador - WRAP
const float PWM_DIVISER = 250; //divisor do clock para o PWM
// prótotipo de funções
void pwm_setup(uint8_t PINO);

int main()
{
    stdio_init_all();
    pwm_setup(22);
    while (true) {
        sleep_ms(1000);
    }
}

//função para configurar o módulo PWM
void pwm_setup(uint8_t PINO)
{
    gpio_set_function(PINO, GPIO_FUNC_PWM); //habilitar o pino GPIO como PWM

    uint slice = pwm_gpio_to_slice_num(PINO); //obter o canal PWM da GPIO

    pwm_set_clkdiv(slice, PWM_DIVISER); //define o divisor de clock do PWM

    pwm_set_wrap(slice, WRAP_PERIOD); //definir o valor de wrap

    pwm_set_gpio_level(PINO, 1000); //definir o cico de trabalho (duty cycle) do pwm

    pwm_set_enabled(slice, false); //habilita o pwm no slice correspondente
}