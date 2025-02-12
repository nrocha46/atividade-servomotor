<div align="center">
    <img src="https://moodle.embarcatech.cepedi.org.br/pluginfile.php/1/theme_moove/logo/1733422525/Group%20658.png" alt="Logo Embarcatech" height="100">
</div>

<br>

# Controle de um servo motor
  
## Descrição

Este projeto implementa um sistema de controle PWM para um servomotor e um LED utilizando o microcontrolador Raspberry Pi Pico W. O objetivo principal é testar o comportamento de um LED ao seguir uma transição suave de brilho sincronizada com o movimento do servo.

## Funcionalidades Implementadas

1. Controle de um servomotor via PWM:

   - Controle de posições específicas: 0°, 90° e 180°.
   - Movimento suave e gradual entre 0 e 180 graus.
   - Ajuste de duty cycle via incrementos progressivos.

2. Controle de um LED via PWM:

   - Ajuste dinâmico do brilho sincronizado com o movimento do servo.
   - Intensidade do LED varia proporcionalmente ao ângulo do servo.

## Ferramentas utilizadas

- **Simulador de eletrônica wokwi**: Ambiente utilizado para simular o hardware e validar o funcionamento do sistema.
- **Microcontrolador Raspberry Pi Pico W**: Responsável pelo controle do servomotor e do LED.
- **Pico SDK**: Kit de desenvolvimento para programação do Raspberry Pi Pico W em C.
- **LED**: Utilizado para testes de variação de intensidade luminosa via PWM.
- **Servo Motor**: Dispositivo controlado pelo PWM para movimentação.
- **Visual Studio Code (VS Code)**: IDE utilizada para o desenvolvimento do código com integração ao Pico SDK.

## Objetivos

1. Implementar um controle de PWM eficiente para movimentação precisa do servomotor.
2. Sincronizar a variação do brilho do LED com o movimento do servo.
3. Criar uma transição gradual e suave entre as posições do servomotor.

## Instruções de uso

1. **Clonar o Repositório**:

```bash
git clone https://github.com/nrocha46/atividade-servomotor
```

2. **Compilar e Carregar o Código**:
   No VS Code, configure o ambiente e compile o projeto com os comandos:

```bash	
cmake -G Ninja ..
ninja
```

3. **Interação com o Sistema**:
   - Execute o programa usando a extensão do Raspberry Pi Pico.
   - Observe o comportamento do servo e do LED conforme o PWM é ajustado automaticamente.