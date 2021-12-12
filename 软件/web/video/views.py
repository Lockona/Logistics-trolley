import os
import socket
import time
from django.http import StreamingHttpResponse, Http404
from django.shortcuts import render
import threading
import base64


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
        # self.server.setsockopt(socket.SOL_SOCKET, socket.SO_RCVBUF, 150 * 1024)
        # self.server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        # self.server.setsockopt(socket.SOL_SOCKET, socket.SO_RCVTIMEO, 1000)

    def run(self) -> None:
        global client, start_flag
        self.server.listen(5)
        while True:
            try:
                client, addr = self.server.accept()
                client.setsockopt(socket.SOL_SOCKET, socket.SO_RCVBUF, 150 * 1024)
                client.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
                start_flag = True
            except socket.error:
                client.close()
                start_flag = False
                pass

    def isAlive(self) -> bool:
        threading.Thread.is_alive(self)


host = socket.gethostname()
# host = '192.168.137.1'
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
                ret = b'\x00'
                while True:
                    t = client.recv(1024 * 1024)
                    if len(t):
                        head = t.find(b'image:')
                        tail = t.find(b'end!')
                        if head != -1:
                            ret = t[head + 6:-1]
                        elif tail == -1:
                            ret = ret + t
                        else:
                            ret = ret + t[:tail]
                            break

                # while True:
                #     t = client.recv(1024)
                #     if (t[0] == 0xff) and (t[1] == 0xd8):
                #         ret = t
                #         break
                # while True:
                #     t = client.recv(1024)
                #     tail = len(t)
                #     ret = ret + t
                #     if (t[tail - 2] == 0xff) and (t[tail - 1] == 0xd9):
                #         break

                # with open("1.jpg", 'wb') as f:
                #     f.write(ret)
                #     f.close()
                yield (b'--frame\r\n'
                       b'Content-Type: image/jpg\r\n\r\n' + ret)
        except socket.error:
            client.close()
            start_flag = False
            continue


def login(request):
    return render(request, 'login.html')


def welcome(request):
    return render(request, 'welcome.html')


def video(request):
    # ret = next(g)
    # return HttpResponse(ret, content_type='image/jpeg')
    return StreamingHttpResponse(test(), content_type='multipart/x-mixed-replace; boundary=frame')


def order_list(request):
    return render(request, 'order-list.html')


def echarts(request):
    return render(request, 'echarts1.html')
