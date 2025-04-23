# UnoJoy 3 Eixos + Célula de Carga (Load Cell + HX711) 

Este fork do projeto UnoJoy adapta o firmware original para funcionar exclusivamente com 3 eixos analógicos (Rx, Ry, Rz), ideal para pedais de simulação (acelerador, freio e embreagem).

## Sobre o projeto original

UnoJoy transforma o Arduino em um joystick HID USB, com suporte a múltiplos botões e eixos. Este fork simplifica o código, removendo botões e eixos extras, mantendo apenas o essencial para simulação automotiva.

## Recursos

- Compatível com padrão HID (joystick USB);
- Suporte a 3 eixos analógicos: Rx (acelerador), Ry (embreagem) e Rz (freio);
- Leitura de freio via célula de carga com módulo HX711;
- Filtro de suavização aplicado ao freio para leitura mais estável;
- Código leve e focado em simulação automotiva;
- Compatível com Arduino Uno (ATmega328P + ATmega16U2) - Não testado com outras versões.

## Uso

Todas essas ferramentas são descritas com links e detalhes no projeto original UnoJoy. Recomenda-se seguir o passo a passo original antes de prosseguir com a modificação.

1. Instale os programas e dependências necessárias:

   - **Java Runtime Environment (JRE)** – necessário para executar o FLIP;
   - **FLIP (Atmel FLIP)** – utilizado para gravar o firmware no chip ATmega16U2;
   - **Arduino IDE** – para compilar e enviar o código ao ATmega328P;
   - **Drivers USB** – o Windows geralmente instala automaticamente, mas certifique-se de que o Arduino Uno esteja sendo reconhecido corretamente.

2. Crie a pasta `UnoJoy` em: `X:\Users\(User)\Documents\Arduino\libraries\UnoJoy`. Coloque o arquivo `UnoJoy.h` dentro dessa pasta.
3. Baixe o sketch `UnoJoy-Pedals.ino` e abra na IDE do Arduino.
4. Se necessário, altere os pinos no código ou ajuste a calibração da célula de carga (HX711) conforme seu setup.
5. Envie o código para o Arduino Uno (ATmega328P) normalmente via IDE.
6. Para gravar o firmware (UnoJoy.hex) no ATmega16U2 (USB), entre em **modo DFU** (Faça um curto nos dois pinos próximos à porta USB) 
   - Execute o arquivo `TurnIntoAnArduino.bat` que está na pasta `UnoJoy` do projeto original.

 Após isso, o Arduino será reconhecido como joystick USB (HID) no Windows. 


 ## Imagens

Demonstração do joystick sendo reconhecido corretamente como dispositivo HID:

![{B991766D-2B5D-448D-B603-DD83E1C0B9A0}](https://github.com/user-attachments/assets/2f94209f-c370-415c-8666-3c0d94c03941)

Hardware utilizado: 

![image](https://github.com/user-attachments/assets/54854844-1a2a-4ecb-9374-29954c4d1745)


Esquema utilizado: 

![{9A015F92-6CE8-4FF5-8040-074FB9583A30}](https://github.com/user-attachments/assets/6f47fa68-6ad2-4f87-b896-93669e07b906)

OBS: Para obter uma leitura mais rápida e responsiva do freio, o módulo HX711 pode ser modificado para operar a 80Hz (em vez dos 10Hz padrão). Isso é feito alterando a conexão do pino **RATE** do CI para **VCC** (normalmente ele vem conectado ao GND). Essa modificação é opcional, mas recomendada para simulação, pois reduz a latência da leitura da célula de carga. A modificação pode ser feita como demonstrando nesse vídeo: https://www.youtube.com/watch?v=0cxS-a837bY




## Créditos

Baseado no projeto [UnoJoy](https://github.com/AlanChatham/UnoJoy) de Alan Chatham.
