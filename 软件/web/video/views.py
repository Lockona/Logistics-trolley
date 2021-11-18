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
        self.server.setsockopt(socket.SOL_SOCKET, socket.SO_RCVBUF, 150 * 1024)
        self.server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.server.setsockopt(socket.SOL_SOCKET, socket.SO_RCVTIMEO, 1000)

    def run(self) -> None:
        global client, start_flag
        self.server.listen(5)
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


# host = socket.gethostname()
host = '192.168.137.1'
port = 5002
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
                # while True:
                #     t = client.recv(1024*1024)
                #     if len(t):
                #         head = t.find(b'image:')
                #         tail = t.find(b'end!')
                #         if head != -1:
                #             ret = t[head + 6:-1]
                #         elif tail == -1:
                #             ret = ret + t
                #         else:
                #             ret = ret + t[:tail]
                #             break
                # t = client.recv(120 * 1024)
                # ret = t
                # while len(ret) < 120 * 1024:
                #     t = client.recv(120 * 1024)
                #     ret = ret + t
                # head = ret.find(b'\xff\xd8')
                # tail = ret.find(b'\xff\xd9')
                # if head != -1:
                #     ret = t[head:-1]
                # elif tail == -1:
                #     ret = ret + t
                # else:
                #     ret = ret + t[:tail + 2]
                #     break
                # if tail != -1:
                #     ret = ret[:tail+2]
                #     break
                while True:
                    t = client.recv(120 * 1024)
                    head = t.find(b'\xff\xd8')
                    tail = t.find(b'\xff\xd9')
                    if head != -1:
                        ret = t[head:-1]
                    elif tail == -1:
                        ret = ret + t
                    else:
                        ret = ret + t[:tail + 2]
                        break
                    if tail != -1:
                        ret = ret[:tail+2]
                        break
                time.sleep(0.01)
                yield (b'--frame\r\n'
                       b'Content-Type: image/jpg\r\n\r\n' + ret)
        except socket.error:
            client.close()
            start_flag = False
            continue


def video(request):
    # ret = next(g)
    # return HttpResponse(ret, content_type='image/jpeg')
    return StreamingHttpResponse(test(), content_type='multipart/x-mixed-replace; boundary=frame')
