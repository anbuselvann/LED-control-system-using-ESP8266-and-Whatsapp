from flask import Flask, request
import requests

app = Flask(__name__)

@app.route('/', methods=['POST'])  # <-- Make sure it's root '/'
def receive_message():
    data = request.form
    message_body = data.get('Body')
    sender = data.get('From')
    print(f'Message from {sender}: {message_body}')

    # Example: trigger LED via ESP8266
    if 'led on' in message_body.lower():
        requests.get('http://10.67.46.210/on')  # ESP8266 IP
    elif 'led off' in message_body.lower():
        requests.get('http://10.67.46.210/off')

    return 'OK', 200

if __name__ == '__main__':
    app.run(port=5000)
