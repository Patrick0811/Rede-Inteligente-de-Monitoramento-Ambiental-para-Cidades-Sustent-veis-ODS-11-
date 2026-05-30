# Rede Inteligente de Monitoramento Ambiental para Cidades Sustentáveis (ODS 11)

Este projeto consiste em um sistema de monitoramento em tempo real de temperatura, umidade e qualidade do ar utilizando o microcontrolador ESP32 e o protocolo de comunicação MQTT. O projeto está alinhado com o Objetivo de Desenvolvimento Sustentável 11 da ONU.

## 📋 Descrição do Funcionamento
O sistema realiza leituras periódicas de sensores ambientais e processa os dados localmente. Dependendo dos níveis detectados, o sistema aciona alertas visuais (LEDs) e sonoros (Buzzer). Todos os dados são publicados em um broker MQTT para monitoramento remoto.

- **Status Normal:** LED Verde ativo.
- **Status Atenção:** LED Amarelo ativo (Temp > 32°C ou Gás > 1800).
- **Status Crítico:** LED Vermelho e Buzzer ativos (Temp > 38°C ou Gás > 3000).

## 🛠️ Hardware Utilizado
- [cite_start]**Microcontrolador:** ESP32 [cite: 11, 44]
- [cite_start]**Sensor de Temperatura e Umidade:** DHT22 [cite: 51, 147]
- [cite_start]**Sensor de Gases e Poluição:** MQ-135 [cite: 55, 148]
- [cite_start]**Atuadores:** LEDs (Verde, Amarelo, Vermelho) e Buzzer Ativo [cite: 69, 74, 150-153]

## 🌐 Comunicação e Protocolos
- [cite_start]**Protocolo:** MQTT (Message Queuing Telemetry Transport) [cite: 11, 77]
- [cite_start]**Broker:** HiveMQ (broker.hivemq.com) [cite: 79, 143]
- **Tópicos:**
  - `cidade/temperatura`
  - `cidade/umidade`
  - `cidade/qualidade_ar`
  - [cite_start]`cidade/alerta` [cite: 145-146]

## 🚀 Como Reproduzir
1. Realize a montagem conforme o esquema elétrico disponível na pasta `/hardware`.
2. Configure o ambiente de desenvolvimento para MicroPython (Thonny IDE ou VS Code).
3. Instale a biblioteca `umqtt.simple` no ESP32.
4. Carregue o arquivo `main.py` disponível na pasta `/software`.
5. Monitore os dados através de um cliente MQTT ou Dashboard compatível.
