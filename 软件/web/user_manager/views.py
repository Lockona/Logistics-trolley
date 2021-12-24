from django.shortcuts import render
from django.http import HttpResponse
from user_manager.models import user
import json

verify = False
user_name = ''


def check_verify() -> bool:
    return verify


def set_verify():
    global verify
    verify = False


def get_user_name() -> str:
    global user_name
    return user_name


# Create your views here.
def user_list(request):
    if not check_verify():
        return render(request, 'login.html')
    all = user.obj.all()
    len = all.count()
    return render(request, "user_list.html", {'all': all, 'len': len})


def edit_page(request):
    if not check_verify():
        return render(request, 'login.html')
    id = request.GET.get('user_id')
    data = user.obj.get(id=id)
    return render(request, "user-edit.html", {'data': data})


def add_page(request):
    if not check_verify():
        return render(request, 'login.html')
    return render(request, "user_add.html")


def add_user(request):
    if not check_verify():
        return render(request, 'login.html')
    data = json.loads(request.GET.get('user_data'))
    name = data['name']
    passwd = data['passwd']
    email = data['email']
    print(name, passwd, email)
    try:
        user.obj.create(user=name, passwd=passwd, email=email)
        data = '1'
    except:
        data = '0'
    print(data)
    return HttpResponse(data)


def edit_user(request):
    if not check_verify():
        return render(request, 'login.html')
    data = request.GET
    id = data['user_id']
    data = json.loads(data['user_data'])
    name = data['name']
    passwd = data['passwd']
    email = data['email']
    print(id, name, passwd, email)
    try:
        user.obj.filter(id=id).update(user=name, passwd=passwd, email=email)
        data = '1'
    except:
        data = '0'
    print(data)
    return HttpResponse(data)


def del_user(request):
    if not check_verify():
        return render(request, 'login.html')
    data = request.GET.get('user_id')
    data = json.loads(data)
    print(data)
    for i in data:
        obj = user.obj.get(id=i)
        obj.delete()
    return HttpResponse(data)


def check_user(request):
    global verify, user_name
    data = request.GET
    name = data['name']
    passwd = data['passwd']
    obj = user.obj.filter(user=name)
    data = '0'
    if len(obj) != 0:
        print(obj[0].passwd)
        if passwd == obj[0].passwd:
            data = '1'
            verify = True
            user_name = name
    return HttpResponse(data)
