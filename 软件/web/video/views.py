import os
import time
from django.http import StreamingHttpResponse, Http404
from django.shortcuts import render


# Create your views here.
def index(request):
    return render(request, "index.html")


def test():
    try:
        while True:
            for root, dirs, files in os.walk("F:\\飞鸟"):
                for file in files:
                    time.sleep(0.1)
                    str = "" + "F:\\飞鸟\\" + file
                    with open(str, 'rb') as f:
                        ret = f.read(os.path.getsize(str))
                    yield (b'--frame\r\n'
                           b'Content-Type: image/jpeg\r\n\r\n' + ret)
    except Exception:
        raise Http404


def video(request):
    # ret = next(g)
    # return HttpResponse(ret, content_type='image/jpeg')
    return StreamingHttpResponse(test(), content_type='multipart/x-mixed-replace; boundary=frame')
