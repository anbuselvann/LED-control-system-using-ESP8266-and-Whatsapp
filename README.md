# ESP8266 LED Control Using Flask Webhook

## Overview

This project demonstrates how to control an **ESP8266 (NodeMCU) LED** using a **Python Flask server**.

The ESP8266 hosts a simple web server with ON and OFF routes.
A Flask application receives incoming messages (for example from messaging services like WhatsApp/Twilio webhook) and sends HTTP requests to the ESP8266 to control the LED.

This is a simple example of communication between:

* IoT Device (ESP8266)
* Local Web Server (Flask)
* External Message Trigger

---

## System Architecture

```
User Message
      ↓
Webhook → Flask Server (Python)
      ↓
HTTP Request
      ↓
ESP8266 Web Server
      ↓
LED ON / OFF
```

---

## How It Works

### 1. ESP8266 Web Server

The ESP8266 connects to WiFi and runs a web server on port 80.

It exposes two URL endpoints:

* `/on`  → Turn LED ON
* `/off` → Turn LED OFF

When these URLs are accessed, the ESP8266 changes the LED state.

Example:

```
http://ESP_IP_ADDRESS/on
http://ESP_IP_ADDRESS/off
```

---

### 2. Flask Server

The Flask application acts as a webhook receiver.

Main tasks:

1. Receives incoming POST requests.
2. Reads message content.
3. Checks commands such as:

```
led on
led off
```

4. Sends HTTP request to ESP8266 using Python `requests` library.

Example:

```python
requests.get('http://ESP_IP/on')
```

---

## ESP8266 Code Explanation

### WiFi Connection

```cpp
WiFi.begin(ssid, password);
```

Connects ESP8266 to local WiFi network.

---

### Web Server Setup

```cpp
ESP8266WebServer server(80);
```

Creates a web server running on port 80.

---

### Routes

#### Turn LED ON

```cpp
server.on("/on", []() {
  digitalWrite(LED_BUILTIN, LOW);
});
```

#### Turn LED OFF

```cpp
server.on("/off", []() {
  digitalWrite(LED_BUILTIN, HIGH);
});
```

Note: Built-in LED uses **active LOW logic**.

---

### Main Loop

```cpp
server.handleClient();
```

Continuously listens for incoming HTTP requests.

---

## Flask Code Explanation

### Webhook Endpoint

```python
@app.route('/', methods=['POST'])
```

Receives POST data from an external service.

---

### Message Processing

```python
message_body = data.get('Body')
```

Reads incoming text message.

---

### Command Handling

```python
if 'led on' in message_body.lower():
```

Checks message and triggers corresponding ESP8266 URL.

---

## Required Software & Libraries

### Arduino IDE Libraries

* ESP8266WiFi
* ESP8266WebServer

### Python Libraries

Install using pip:

```
pip install flask requests
```

---

## Hardware Required

* ESP8266 NodeMCU
* USB cable
* WiFi connection
* Computer running Flask server

---

## Running the Project

### Step 1 – Upload ESP8266 Code

* Add WiFi credentials.
* Upload sketch using Arduino IDE.
* Note the ESP8266 IP address from Serial Monitor.

### Step 2 – Run Flask Server

```
python app.py
```

Server starts on:

```
http://localhost:5000
```

### Step 3 – Send Message

When a message containing:

```
led on
```

or

```
led off
```

is received, Flask sends command to ESP8266.

---



