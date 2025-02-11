#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

// PARAMÊTROS PAR PWM
#define WRAP_PERIOD  20000 //valor máximo do contador - WRAP
#define PWM_DIVISER  125.0f //divisor do clock para o PWM
const uint8_t PINO = 22;

// prótotipo de funções
void pwm_setup();
void set_pwm_dc(uint16_t duty_cycle);
void rotacionar_servo_0_a_180();
void rotacionar_servo_180_a_0();

int main()
{
    stdio_init_all();
    pwm_setup();

    // rotaciona servo para 180 graus
    set_pwm_dc(2400);
    sleep_ms(3000);
    // rotaciona servo para 90 graus
    set_pwm_dc(1470);
    sleep_ms(3000);
    // rotaciona servo para 0 graus
    set_pwm_dc(500);
    sleep_ms(3000);

    while (true) {
        printf("Nova rotação de 0 a 180\n");
        rotacionar_servo_0_a_180();
        printf("Nova rotação de 180 a 0\n");
        rotacionar_servo_180_a_0();
    }
}

//função para configurar o módulo PWM
void pwm_setup()
{
    gpio_set_function(PINO, GPIO_FUNC_PWM); //habilitar o pino GPIO como PWM

    uint slice = pwm_gpio_to_slice_num(PINO); //obter o canal PWM da GPIO

    pwm_set_wrap(slice, WRAP_PERIOD); //definir o valor de wrap
    pwm_set_clkdiv(slice, PWM_DIVISER); //define o divisor de clock do PWM
    pwm_set_enabled(slice, true); //habilita o pwm no slice correspondente
}

void set_pwm_dc(uint16_t duty_cycle){
    uint slice = pwm_gpio_to_slice_num(PINO);
    pwm_set_gpio_level(PINO, duty_cycle); //definir o cico de trabalho (duty cycle) do pwm
}

void rotacionar_servo_0_a_180(){

    for(uint16_t passo=500;passo<=2400;passo+=5){
        set_pwm_dc(passo);
        sleep_ms(5);
    }
}

void rotacionar_servo_180_a_0(){

    for(uint16_t passo=2400;passo>=500;passo-=5){
        set_pwm_dc(passo);
        sleep_ms(5);
    }
}