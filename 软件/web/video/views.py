import os
import socket
import time
from django.http import StreamingHttpResponse, Http404
from django.shortcuts import render
import threading


# Create your views here.
def index(request):
    return render(request, "index.html")


client = 0
start_flag = False


class mythread(threading.Thread):
    def __init__(self, host, port):
        threading.Thread.__init__(self)
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server.bind((host, port))
        self.server.listen(5)

    def run(self) -> None:
        global client, start_flag
        while True:
            try:
                client, addr = self.server.accept()
                start_flag = True
            except socket.error:
                client.close()
                start_flag = False
                pass

    def isAlive(self) -> bool:
        threading.Thread.is_alive(self)


host = '192.168.137.1'
port = 5000
m = mythread(host, port)


def test():
    global client, start_flag
    try:
        if not m.isAlive():
            m.start()
    except RuntimeError:
        pass
    while True:
        try:
            if start_flag:
                size = client.recv(8)
                time.sleep(0.005)
                print(size)
                try:
                    size = int(size)
                except ValueError or TypeError:
                    pass
                ret = client.recv(size)
                yield (b'--frame\r\n'
                       b'Content-Type: image/jpeg\r\n\r\n' + ret)
        except socket.error:
            client.close()
            start_flag = False
            continue
        except TypeError:
            continue


def video(request):
    # ret = next(g)
    # return HttpResponse(ret, content_type='image/jpeg')
    return StreamingHttpResponse(test(), content_type='multipart/x-mixed-replace; boundary=frame')
