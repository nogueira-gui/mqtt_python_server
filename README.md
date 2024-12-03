# Servidor IoT com Python, Flask e Mosquitto

Este projeto demonstra como configurar um servidor IoT com Flask para exibir dados de sensores em tempo real, usando MQTT para comunicação e WebSockets para atualização da interface.

## **Estrutura do Projeto**

```
├── app
│   ├── app.py               # Aplicação Flask
│   ├── Dockerfile           # Configuração do Docker para o servidor Flask
│   ├── requirements.txt     # Dependências do projeto
│   ├── templates
│   │   └── index.html       # Interface do usuário
├── docker-compose.yml       # Arquivo de orquestração Docker
├── esp32
│   └── leitor_de_temperatura
│       └── leitor_de_temperatura.ino # Código para o ESP32
├── mosquitto
│   └── mosquitto.conf       # Configuração do servidor Mosquitto
```

## **Pré-requisitos**

- Docker e Docker Compose instalados.
- Placa ESP32 com sensor de temperatura configurado (Dallas DS18B20, por exemplo).
- Rede Wi-Fi para comunicação com o ESP32 e servidor MQTT.

---

## **Instalação e Configuração**

### 1. Configurar o Servidor MQTT (Mosquitto)
O arquivo `mosquitto.conf` já está configurado para permitir conexões anônimas na porta 1883.

---

#Aqui está uma versão aprimorada do tópico sobre **Instalação e Configuração das Bibliotecas** para o seu projeto de servidor IoT com Python, Flask e Mosquitto. Eu inclui explicações detalhadas de como instalar as bibliotecas e como elas funcionam no projeto:

---

### 2. Bibliotecas Necessárias

Para que o seu projeto funcione corretamente com o ESP32, MQTT e o sensor de temperatura, você precisará instalar algumas bibliotecas específicas. Abaixo estão as instruções para instalação e uma breve descrição de como cada uma delas funciona no contexto do seu projeto.

#### 1. **WiFi.h**
   - **Descrição**: A biblioteca `WiFi.h` é usada para conectar o ESP32 a uma rede Wi-Fi. Ela fornece os métodos necessários para configurar a conexão Wi-Fi, conectar-se à rede, e obter o endereço IP do dispositivo.
   - **Instalação**:
     - No Arduino IDE, vá até **Sketch > Incluir Biblioteca > Gerenciar Bibliotecas**.
     - Pesquise por **WiFi** e instale a versão compatível com o ESP32.
   - **Como funciona no projeto**: A `WiFi.h` permite que o ESP32 se conecte à sua rede Wi-Fi para comunicar-se com o servidor MQTT (Mosquitto). O código utiliza essa biblioteca para conectar o ESP32 à rede e garantir que ele tenha acesso à Internet e ao servidor MQTT.
   - **Referência**: [Documentação Oficial do WiFi.h para ESP32](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/network/wifi.html)

#### 2. **PubSubClient.h**
   - **Descrição**: A biblioteca `PubSubClient` é um cliente MQTT utilizado para facilitar a comunicação entre o ESP32 e o servidor MQTT (Mosquitto). Com ela, o ESP32 pode publicar e assinar tópicos MQTT para enviar e receber dados em tempo real.
   - **Instalação**:
     - No Arduino IDE, vá até **Sketch > Incluir Biblioteca > Gerenciar Bibliotecas**.
     - Pesquise por **PubSubClient** e instale a versão mais recente.
   - **Como funciona no projeto**: Esta biblioteca permite que o ESP32 se comunique com o servidor MQTT. O código do ESP32 utiliza o `PubSubClient` para publicar os dados de temperatura no tópico MQTT `test`, que será consumido pelo servidor Flask.
   - **Referência**: [PubSubClient GitHub](https://github.com/knolleary/pubsubclient)

#### 3. **OneWire.h**
   - **Descrição**: A biblioteca `OneWire` permite a comunicação com sensores que utilizam o protocolo de comunicação OneWire, como o sensor de temperatura Dallas DS18B20.
   - **Instalação**:
     - No Arduino IDE, vá até **Sketch > Incluir Biblioteca > Gerenciar Bibliotecas**.
     - Pesquise por **OneWire** e instale a versão mais recente.
   - **Como funciona no projeto**: O ESP32 usa a biblioteca `OneWire` para ler os dados do sensor de temperatura Dallas DS18B20. Ela configura a comunicação no barramento OneWire, permitindo que o sensor envie suas leituras para o ESP32.
   - **Referência**: [OneWire Arduino Library - GitHub](https://github.com/PaulStoffregen/OneWire)

#### 4. **DallasTemperature.h**
   - **Descrição**: A biblioteca `DallasTemperature` foi projetada para facilitar a leitura de sensores de temperatura da família Dallas (como o DS18B20), que comunicam-se usando o protocolo OneWire.
   - **Instalação**:
     - No Arduino IDE, vá até **Sketch > Incluir Biblioteca > Gerenciar Bibliotecas**.
     - Pesquise por **DallasTemperature** e instale a versão mais recente.
   - **Como funciona no projeto**: O ESP32 usa essa biblioteca para ler as temperaturas enviadas pelo sensor DS18B20. Ela lida com as conversões e leituras de temperatura, simplificando o processo de obtenção de dados do sensor.
   - **Referência**: [DallasTemperature Arduino Library - GitHub](https://github.com/milesburton/Arduino-Temperature-Control-Library)

### Como Instalar as Bibliotecas no Arduino IDE

Para instalar as bibliotecas no Arduino IDE, siga os passos abaixo:

1. **Abra o Arduino IDE**.
2. Vá para o menu **Sketch > Incluir Biblioteca > Gerenciar Bibliotecas**.
3. Na janela que se abre, digite o nome da biblioteca desejada na caixa de pesquisa.
4. Clique sobre o botão **Instalar** ao lado de cada biblioteca para instalar a versão mais recente.

### Como Elas Funcionam no Projeto

- **WiFi.h**: A conexão Wi-Fi é fundamental para que o ESP32 se conecte ao servidor MQTT (Mosquitto), possibilitando a comunicação entre o dispositivo e o servidor.
- **PubSubClient**: Essa biblioteca faz a ponte entre o ESP32 e o servidor MQTT, permitindo que o ESP32 envie dados de temperatura para o servidor.
- **OneWire e DallasTemperature**: Juntas, essas bibliotecas permitem ao ESP32 ler a temperatura do sensor Dallas DS18B20 e transmitir essas leituras via MQTT para o servidor, garantindo que o servidor Flask receba dados em tempo real.

Com as bibliotecas instaladas e configuradas, o ESP32 estará pronto para se comunicar com o servidor Flask e o Mosquitto, tornando o fluxo de dados entre os dispositivos eficiente e contínuo.

---

### 3. Configurar o ESP32
Atualize o código no arquivo `leitor_de_temperatura.ino` com as configurações da sua rede Wi-Fi e o IP do servidor MQTT:

```cpp
const char* ssid = "SUA_REDE_WIFI";
const char* password = "SUA_SENHA";
const char* mqtt_server = "IP_DO_SERVIDOR_MQTT";
```

Carregue o código no ESP32 usando o Arduino IDE.

---

### 4. Executar o Projeto com Docker Compose
Suba os serviços com o comando:

```bash
docker-compose up --build
```

Isso iniciará:
- Servidor Flask acessível em [http://localhost:5000](http://localhost:5000).
- Servidor Mosquitto na porta 1883.

---

## **Fluxo de Funcionamento**

1. **ESP32**
   - Lê a temperatura via sensor Dallas DS18B20.
   - Publica os dados formatados em JSON no tópico MQTT `test`.

2. **Mosquitto**
   - Recebe os dados publicados pelo ESP32 e os encaminha para os clientes subscritos.

3. **Servidor Flask**
   - Escuta o tópico MQTT usando o cliente Paho.
   - Atualiza a interface em tempo real via Socket.IO.

4. **Interface Web**
   - Mostra os dados do sensor (temperatura em °C e °F e pino do sensor).

---

## **Personalização**
- Alterar o tópico MQTT: Modifique `MQTT_TOPIC` nos arquivos `app.py` e `leitor_de_temperatura.ino`.
- Alterar o design da interface: Edite `index.html` com TailwindCSS.

---

## **Problemas Conhecidos**
- Certifique-se de que o ESP32 esteja na mesma rede que o servidor Mosquitto.
- Conexões falhando podem ser causadas por configurações incorretas no Mosquitto.

---

## **Licença**
Este projeto está sob a licença MIT. Sinta-se à vontade para contribuir e expandir as funcionalidades.