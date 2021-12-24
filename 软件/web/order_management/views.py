import json
import time

from django.http import HttpResponse
from django.shortcuts import render

from order_management.models import order
from user_manager.views import check_verify, set_verify, get_user_name


# Create your views here.
def login(request):
    set_verify()
    return render(request, 'login.html')


def welcome(request):
    if not check_verify():
        return render(request, 'login.html')
    user_name = get_user_name()
    date = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())
    return render(request, 'welcome.html', {'user_name': user_name, 'date': date})


def index(request):
    if not check_verify():
        return render(request, 'login.html')
    return render(request, "index.html")


def order_list(request):
    if not check_verify():
        return render(request, 'login.html')
    title = 'list'
    all = order.obj.all()
    length = all.count()
    return render(request, 'order-list.html', {'title': title, 'all': all, 'len': length})


def search_page(request):
    if not check_verify():
        return render(request, 'login.html')
    title = 'search'
    length = 0
    return render(request, 'order-list.html', {'title': title, 'len': length})


def echarts(request):
    if not check_verify():
        return render(request, 'login.html')
    return render(request, 'echarts1.html')


def search_order(request):
    if not check_verify():
        return render(request, 'login.html')
    title = 'search'
    data = request.GET
    print(data)
    obj = order.obj.all()
    if len(data):
        date = data['date']
        order_status = data['order_status']
        destination = data['destination']
        if len(date):
            date = str(date).split('-')
            print(date)
            obj = obj.filter(time__day=int(date[2]))
            if len(obj):
                obj = obj.filter(time__month=int(date[1]))
                if len(obj):
                    obj = obj.filter(time__year=int(date[0]))
        if len(order_status):
            obj = obj.filter(order_status=order_status)
            print(order_status)
        if len(destination):
            obj = obj.filter(destination=destination)
            print(destination)
    length = len(obj)
    return render(request, 'order-list.html', {'title': title, 'all': obj, 'len': length})


def del_order(request):
    if not check_verify():
        return render(request, 'login.html')
    data = request.GET.get('order_id')
    data = json.loads(data)
    print(data)
    for i in data:
        obj = order.obj.get(id=i)
        obj.delete()
    return HttpResponse(data)
