# Rede Inteligente de Monitoramento Ambiental para Cidades Sustentáveis (ODS 11)

Este repositório contém o código-fonte e a documentação técnica para um sistema de monitoramento ambiental baseado em IoT, desenvolvido como requisito para a disciplina na Universidade Presbiteriana Mackenzie. O projeto foca no monitoramento de temperatura e umidade em tempo real, utilizando o protocolo MQTT para promover a sustentabilidade urbana (ODS 11).

## 🚀 Demonstração Direta
- **Simulador Wokwi:** [Acesse o Projeto aqui](https://wokwi.com/projects/465458630027840513)
- **Visualização MQTT:** [Console HiveMQ](https://www.hivemq.com/demos/websocket-client/) (Tópico: `patrick/monitoramento`)

## 🛠️ Tecnologias e Componentes
- **Hardware:** Microcontrolador ESP32.
- **Sensores:** DHT22 (Temperatura e Umidade).
- **Atuadores:** LEDs (Verde, Amarelo e Vermelho) e Buzzer Ativo.
- **Protocolo de Comunicação:** MQTT (Message Queuing Telemetry Transport).
- **Broker:** HiveMQ (`broker.hivemq.com`).
- **Linguagem:** C++ (Framework Arduino).

## 📋 Lógica de Funcionamento e Alertas
O sistema monitora as condições ambientais e toma decisões locais baseadas na temperatura, além de publicar os dados em formato JSON para a nuvem:

| Faixa de Temperatura | Status | Sinalização Visual | Sinalização Sonora |
| :--- | :--- | :--- | :--- |
| Até 35°C | **NORMAL** | LED Verde | Silencioso |
| 35,1°C a 60°C | **ATENÇÃO** | LED Amarelo | Silencioso |
| Acima de 60°C | **ALERTA CRÍTICO** | LED Vermelho | Buzzer (1kHz) |

## 📂 Estrutura do Código
O arquivo principal executa:
1. Conexão estável com a rede Wi-Fi `Wokwi-GUEST`.
2. Autenticação e conexão com o Broker MQTT com ID de cliente dinâmico.
3. Leitura dos dados via sensor DHT22.
4. Processamento da lógica de segurança e acionamento de GPIOS.
5. Publicação de payload JSON no tópico `patrick/monitoramento`.

## ⚙️ Como Reproduzir
1. Instale as bibliotecas `PubSubClient` e `DHT sensor library` na sua IDE (Arduino ou VS Code).
2. Carregue o código disponível no arquivo `.ino` deste repositório para o seu ESP32.
3. Certifique-se de que a fiação segue os pinos:
   - DHT22: Pin 4
   - LED Verde: Pin 18 | Amarelo: Pin 19 | Vermelho: Pin 21
   - Buzzer: Pin 23
4. Use um cliente MQTT para assinar o tópico `patrick/monitoramento` e visualizar os dados.

---
**Autor:** Patrick Ribeiro Feitosa  
**Instituição:** Universidade Presbiteriana Mackenzie
