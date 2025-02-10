# Projeto: Controle de Servomotor e LED via PWM no RP2040

## Descrição Geral

Este projeto tem como objetivo implementar e simular o controle de um **servomotor** e de um **LED** utilizando **Modulação por Largura de Pulso (PWM)** no microcontrolador **RP2040** da placa **Raspberry Pi Pico W**. A simulação ocorre na plataforma **Wokwi** e o projeto foi desenvolvido utilizando o **Pico SDK** no **VS Code**.

O programa permite ao usuário selecionar se deseja visualizar o ciclo de PWM no **LED (GPIO 13)** ou no **Servomotor (GPIO 22)**. Além disso, exibe mensagens correspondentes às posições do servomotor ou à intensidade do LED e repete o ciclo duas vezes antes de solicitar uma nova escolha do periférico.

## Objetivos

- Implementar o controle de um **servomotor** utilizando **PWM**.
- Implementar o controle de **intensidade de um LED** via **PWM**.
- Permitir que o usuário escolha entre **LED** e **Servomotor**.
- Exibir mensagens de status do sistema conforme o periférico escolhido.
- Utilizar a plataforma **Wokwi** para simulação do funcionamento.

## Componentes Utilizados

- **Microcontrolador**: RP2040 (Raspberry Pi Pico W)
- **LED**: Conectado ao GPIO **13**
- **Servomotor**: Conectado ao GPIO **22**

## Funcionalidades Implementadas

### 1. Seleção do Periférico via Entrada do Usuário
- O programa solicita ao usuário que escolha onde deseja visualizar o ciclo PWM:
  - `1 - LED`
  - `2 - Servomotor`
- Caso a entrada seja inválida, uma mensagem de erro é exibida e a escolha é solicitada novamente.

### 2. Controle do Servomotor via PWM
- Posicionamento do servomotor em:
  - **0°** (**500µs** de duty cycle)
  - **90°** (**1470µs** de duty cycle)
  - **180°** (**2400µs** de duty cycle)
- Movimentação **suave** entre as posições utilizando incrementos de **5µs** e pausas de **10ms**.
- Exibe mensagens informando a posição atual do servo:
  - **"Posicao 0 graus"**
  - **"Posicao 90 graus"**
  - **"Posicao 180 graus"**
  - **"Voltando a posicao inicial"**

### 3. Controle de Intensidade do LED via PWM
- Se o LED for selecionado, os duty cycles correspondem a:
  - **Baixa intensidade** (equivalente a 0° do servo)
  - **Média intensidade** (equivalente a 90° do servo)
  - **Alta intensidade** (equivalente a 180° do servo)
- Exibe mensagens informando o estado do LED:
  - **"Menor Intensidade"**
  - **"Média Intensidade"**
  - **"Maior Intensidade"**
  - **"Voltando intensidade inicial"**

### 4. Estrutura do Loop Principal
- O ciclo **se repete apenas duas vezes** antes de solicitar uma nova escolha do periférico ao usuário.

## Como Executar o Projeto

### 1. Configuração do Ambiente
- Instale o **VS Code** e configure o **Pico SDK**.
- Baixe e instale o simulador **Wokwi**.

### 2. Compilação e Execução
- Compile o código e gere um arquivo `.uf2`.
- Transfira o arquivo para a placa **Raspberry Pi Pico W**.
- Utilize o **Serial Monitor** do VS Code para interagir com o programa.

### 3. Testes e Depuração
- Escolha **LED** ou **Servomotor** quando solicitado.
- Observe as mensagens e a movimentação do servo ou a variação de intensidade do LED.
- Após duas repetições, selecione novamente o periférico.
- **Os testes e depuração também podem ser realizados no simulador Wokwi.**

## Estrutura do Projeto

- `controle_pwm.c`: Código principal do projeto.
- `diagram.json`: Arquivo de simulação para o **Wokwi**.
- `README.md`: Documentação do projeto.

## Espaço para Vídeo de Demonstração

(Adicione aqui o link do vídeo demonstrativo quando estiver pronto)

