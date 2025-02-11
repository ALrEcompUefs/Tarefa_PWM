# Tarefa_PWM

Este repositório é destinado para o desenvolvimento da tarefa de PWM da unidade de microcontroladores do curso de formação básica em software embarcado da embarcatech

## Diagrama do circuito

No diagrama abaixo tem-se o diagrama do circuito imlpementado no wokwi

![circuito](https://github.com/ALrEcompUefs/Tarefa_PWM/blob/main/img/img1.png?raw=true "Diagrama do circuito")

## Requisitos e funcionalidades

* Utilizar o módulo pwm do microcontrolador raspberrypi pico para controlar a posição do servo motor conectado a GPIO 22
* Configuração da frequência do PWM para 50Hz
* Posicionamento do servo motor em 180º,90º e 0º
* Movimentação do servo motor de 0º a 180º e 180º para 0º

## Configuração do PWM

Para esta tarefa a frequência especificada para o PWM é de 50Hz.

A seguinte equação é utilizada para determinar o clock do pwm:

$$
\frac{f_{clock}}{\left ( Divisor\_inteiro +\frac{Divisor\_fracional}{16}\right )WRAP+1}
$$

Onde a frequência de clock base da pico w é 125MHz.

Poderiamos obter a frequência de 50Hz com diferentes combinações dos paramêtros de WRAP e Divisor mas, como foi solicitado utilizar os correspondentes ciclo ativos e duty cycle de 2400us- 0,12% 1470us- 0,0735% e 500us-0,025% o parâmetro WRAP foi restrito ao valor de 20000 e o divisor definido como 125.0.

$$
DC=\frac{Ciclo\_Ativo}{Periodo}*100
$$

Para configurar o pwm na pico w foi imlpementada a função `pwm_setup()`

```c
//função para configurar o módulo PWM
void pwm_setup()
{
    // Com o clock base de 125Mhz WRAP de 10000 e divisor de 125
    // O clock calculado para o pwm é de 50Hz
    // outras configurações de parâmetro poderiam ser utilizadas para obter esta mesma frequência
    // Mas os requisitos da tarefa limitaram a escolha do valor do wrap

    gpio_set_function(PINO, GPIO_FUNC_PWM); //habilitar o pino GPIO como PWM

    uint slice = pwm_gpio_to_slice_num(PINO); //obter o canal PWM da GPIO

    pwm_set_wrap(slice, WRAP_PERIOD); //definir o valor de wrap
    pwm_set_clkdiv(slice, PWM_DIVISER); //define o divisor de clock do PWM
    pwm_set_enabled(slice, true); //habilita o pwm no slice correspondente
}
```

Primeiro o pino do GPIO que vai utilizado é configurado para a função pwm, em seguida o slice associado ao pino é obtido.

Para configurar a frequência do pwm são definidos o divisor e wrap e após o pwm é ativado

A função `set_pwm_dc(uint16_t duty_cycle)` é utilizada para configurar o ciclo ativo do pwm.

```c
/*
|   Função set_pwm_dc
|   Configura o nível do duty cycle para o pwm
*/
void set_pwm_dc(uint16_t duty_cycle){
    uint slice = pwm_gpio_to_slice_num(PINO);
    pwm_set_gpio_level(PINO, duty_cycle); //definir o cico de trabalho (duty cycle) do pwm
}
```

### Função main

Na main é feita a chamada da função de configuração do pwm e o ciclo ativo é ajustado para o servo motor mudar de posição

```c
    stdio_init_all();
    pwm_setup();

    // rotaciona servo para 180 graus
    set_pwm_dc(2400);
    sleep_ms(5000);
    // rotaciona servo para 90 graus
    set_pwm_dc(1470);
    sleep_ms(5000);
    // rotaciona servo para 0 graus
    set_pwm_dc(500);
    sleep_ms(5000);
```

No super laço as funções para rotação do motor são alternadas para o movimento do servo motor

```c
while (true) {
        // Dentro do laço vai fazer o movimento de rotação do servo motor
        printf("Nova rotação de 0 a 180\n");
        rotacionar_servo_0_a_180();
        printf("Nova rotação de 180 a 0\n");
        rotacionar_servo_180_a_0();
    }
```

## VÍDEO

Link para o vídeo de demonstração: https://drive.google.com/file/d/1yGhyz90R2BhTrKpMuaMyU3V71e2Wb5N-/view?usp=sharing
