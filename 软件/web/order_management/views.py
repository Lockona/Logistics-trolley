from django.shortcuts import render
from order_management.models import order
from django.http import HttpResponse


# Create your views here.
def login(request):
    return render(request, 'login.html')


def welcome(request):
    return render(request, 'welcome.html')


def index(request):
    return render(request, "index.html")


def order_list(request):
    all = order.obj.all()
    len = all.count()
    return render(request, 'order-list.html', {'all': all, 'len': len})


def echarts(request):
    return render(request, 'echarts1.html')


def search_order(request):
    data = request.GET
    print(data)
    obj = order.obj.all()
    if len(data):
        date = data['date']
        order_status = data['order_status']
        destination = data['destination']
        if len(date):
            obj = obj.filter(time=date)
        if len(order_status):
            obj = obj.filter(order_status=order_status)
        if len(destination):
            obj = obj.filter(destination=destination)
    length = len(obj)
    return render(request, 'order-list.html', {'all': obj, 'len': length})

