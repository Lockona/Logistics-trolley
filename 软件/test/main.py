import os
import time
import socket
import json


def test():
    while True:
        for root, dirs, files in os.walk("F:\\飞鸟"):
            for file in files:
                str0 = "" + "F:\\飞鸟\\" + file
                with open(str0, 'rb') as f:
                    size = os.path.getsize(str0)
                    ret = f.read(size)
                yield str(size).encode()
                yield (b'--frame\r\n'
                       b'Content-Type: image/jpeg\r\n\r\n' + ret)


client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
host = socket.gethostname()
port = 5001
client.connect((host, port))
g = test()
try:
    while True:
        for root, dirs, files in os.walk("F:\\飞鸟"):
            for file in files:
                str0 = "" + "F:\\飞鸟\\" + file
                with open(str0, 'rb') as f:
                    size = os.path.getsize(str0)
                    ret = f.read(size)
                client.send(str(size).encode())
                time.sleep(0.2)
                client.send(ret)
except socket.error:
    client.close()
