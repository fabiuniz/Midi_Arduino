
# Controlador MIDI com Arduino

## Introdução

A inteligência artificial tem o potencial de transformar e potêncializar a forma como interagimos com a música e a tecnologia, está aí uma oportunidade de levar um projeto como esse ao próximo nível. Com o uso de controladores MIDI personalizados, como este projeto baseado em Arduino, podemos não apenas criar música, mas também aperfeiçoar nosso processo criativo. Este controlador MIDI permite que você interaja com sua DAW (Digital Audio Workstation) ou outros instrumentos, facilitando a criação musical em novas e empolgantes maneiras.

## O que é este projeto?

Este projeto é um controlador MIDI que utiliza um Arduino (Leonardo ATmega32U4 ou similar) e um teclado matricial 7x8 ou uma conexão com DB15 fêmea e macho usando fios. Com este controlador, você poderá tocar notas e enviar comandos MIDI para qualquer software ou hardware compatível, proporcionando uma experiência musical mais dinâmica e interativa.

## Recursos

- Teclado matricial 7x8
- Comunicação MIDI via USB
- Interface simples para interação
- Feedback serial para monitorar as interações

## Instruções de Configuração

### Pré-requisitos

1. **Arduino IDE**: Certifique-se de ter a Arduino IDE instalada. Você pode baixá-la [aqui](https://www.arduino.cc/en/software).
2. **Biblioteca `MIDIUSB`**: A biblioteca `MIDIUSB` é necessária para fazer a comunicação MIDI. Você pode instalá-la através do gerenciador de bibliotecas da Arduino IDE.

### Instalação do Arduino

1. **Baixar o repositório**: Clone ou baixe este repositório em seu computador.
    ```bash
    git clone https://github.com/seu_usuario/Midi_Arduino.git
    ```

2. **Instalar os drivers**: Você precisará instalar o driver `CH341SER.EXE` para a comunicação USB. Você pode encontrá-lo [neste link](http://arduino.esp8266.com/stable/package_esp8266com_index.json).

3. **Conectar o hardware**: Conecte o seu Arduino ao computador e ao teclado matricial conforme o esquema abaixo:
   - As linhas e colunas do teclado matricial devem ser conectadas às portas digitais do Arduino, conforme especificado no código.

### Upload do Código

1. **Abrir o código**: Abra o arquivo principal do projeto na Arduino IDE.

2. **Selecionar a placa**:
   - Vá para `Ferramentas` > `Placa` e selecione `Arduino Leonardo` se você estiver usando um Arduino Leonardo, ou a placa correspondente.

3. **Upload do código**:
   - Pressione o botão de Upload na Arduino IDE.
   - Caso apareça a mensagem "Carregando", pressione 4 vezes o botão de RESET enquanto mantém o pino GND conectado para iniciar o upload.

### Testando o Controlador MIDI

1. **Monitor Serial**:
   - Abra o Monitor Serial na IDE (Ctrl + Shift + M) para visualizar a saída de debug.

2. **Interação com o MIDI**:
   - Conecte o controlador a um software de música ou sintetizador compatível via USB como o "FL Studio 20" e comece a tocar as notas!

## Mídia do Projeto

Aqui estão algumas imagens e vídeos do projeto, incluindo o case caseiro feito de resina e as conexões do projeto.

### Imagens

- **Construção do Case**
  [Case do Controlador](media/IMG-20200920-WA0009.jpg)

- **Conexões do Projeto**
  [Conexões](media/IMG_20220213_170032090_HDR.jpg)
  
- **Visão Geral do Projeto**
  [Visão Geral](media/IMG_20220213_170316879.jpg)

- **Molde para o Case**
  [Molde para o Case](media/IMG_20201024_174952174.jpg)

- **Arquivo do PCB**
  [Baixar PCB](media/PCB_PrintAll_2023-07-09.pdf)

### Vídeo

- **Demonstração do Controlador MIDI**
  [Assista ao Vídeo](media/VID_20200827_105800033.mp4)

## Contribuindo

Se você quiser contribuir para este projeto, sinta-se à vontade para abrir uma issue ou enviar um pull request. Agradecemos pelo apoio e suas sugestões!


### Considerações finais:
- Sinta-se à vontade para ajustar o conteúdo para que se adequem melhor ao seu projeto e à sua visão.

## 👨‍💻 Autor

[Fabiano Rocha/Fabiuniz]

## Licença

Este projeto está licenciado sob a [MIT License](LICENSE).
