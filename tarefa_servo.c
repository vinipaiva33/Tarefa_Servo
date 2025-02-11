#include <stdio.h> 
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define PWM_SERVO 22 // Pino para o Servomotor
#define PWM_LED 12 // Pino para o LED


const uint16_t WRAP_PERIOD = 35175; // Valor máximo do contador (PWM 50 Hz)
const float PWM_DIVISER = 71.071184899; // Divisor do clock do PWM

// Definição dos valores de duty cycle para cada nível
const uint16_t DUTY_0 = 879;    // 500µs → 0° - Feito manualmente
const uint16_t DUTY_90 = 2582;  // 1470µs → 90° - Feito manualmente
const uint16_t DUTY_180 = 4218; // 2400µs → 180° - Feito manualmente

const uint16_t STEP = (5 * WRAP_PERIOD / 20000); // Incremento de 5µs convertido para PWM

uint pwm_pin; // Variável para armazenar o pino escolhido pelo usuário
char *desc_0, *desc_90, *desc_180, *desc_reset; // Mensagens dinâmicas

// Configuração do PWM
void pwm_setup(uint pin) {
    gpio_set_function(pin, GPIO_FUNC_PWM); // Define GPIO como PWM
    uint slice = pwm_gpio_to_slice_num(pin); // Obtém o slice PWM do GPIO
    pwm_set_clkdiv(slice, PWM_DIVISER); // Configura o divisor de clock
    pwm_set_wrap(slice, WRAP_PERIOD); // Define o valor máximo do contador
    pwm_set_enabled(slice, true); // Habilita o PWM no slice correspondente
}

// Função para mover o servo suavemente até um ângulo específico
void move_servo(uint16_t start, uint16_t end) {
    if (start < end) {
        for (uint16_t duty = start; duty <= end; duty += STEP) {
            pwm_set_gpio_level(pwm_pin, duty);
            sleep_ms(10);
        }
    } else {
        for (uint16_t duty = start; duty >= end; duty -= STEP) {
            pwm_set_gpio_level(pwm_pin, duty);
            sleep_ms(10);
        }
    }
}

// Função para solicitar escolha do usuário
void escolher_periferico() {
    char escolha;
    
    while (1) {
        printf("Onde deseja ver o ciclo?\n 1- LED\n 2- Servomotor\n");
        scanf("%c", &escolha);

        if (escolha == '1') {
            pwm_pin = PWM_LED;
            desc_0 = "Menor Intensidade";
            desc_90 = "Média Intensidade";
            desc_180 = "Maior Intensidade";
            desc_reset = "Voltando intensidade inicial";
            printf("Ciclo será exibido no LED (GPIO %d)\n", PWM_LED);
            break;
        } 
        else if (escolha == '2') {
            pwm_pin = PWM_SERVO;
            desc_0 = "Posicao 0 graus";
            desc_90 = "Posicao 90 graus";
            desc_180 = "Posicao 180 graus";
            desc_reset = "Voltando a posicao inicial";
            printf("Ciclo será exibido no Servomotor (GPIO %d)\n", PWM_SERVO);
            break;
        } 
        else {
            printf("Comando invalido. Escolha 1 para LED ou 2 para Servomotor.\n");
        }
    }
}

// Função principal
int main() {
    stdio_init_all();

    while (true) {
        escolher_periferico(); // Pergunta ao usuário onde deseja ver o ciclo
        pwm_setup(pwm_pin); // Configura PWM no pino escolhido

        //  Posições iniciais com 5 segundos de pausa cada
        pwm_set_gpio_level(pwm_pin, DUTY_0);
        printf("%s\n", desc_0);
        sleep_ms(5000);

        move_servo(DUTY_0, DUTY_90);
        printf("%s\n", desc_90);
        sleep_ms(5000);

        move_servo(DUTY_90, DUTY_180);
        printf("%s\n", desc_180);
        sleep_ms(5000);

        //  Movimentação contínua entre 0° e 180° por 30 segundos
        printf("Alternando entre 0° e 180° por 30 segundos...\n");
        uint32_t start_time = to_ms_since_boot(get_absolute_time());

        while (to_ms_since_boot(get_absolute_time()) - start_time < 30000) {
            move_servo(DUTY_180, DUTY_0);
            move_servo(DUTY_0, DUTY_180);
        }
    }
}
