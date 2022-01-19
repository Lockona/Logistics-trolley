from django.shortcuts import render
from django.http import HttpResponse
from user_manager.models import user, user_rule
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
    global user_name
    if not check_verify():
        return render(request, 'login.html')
    all = user.obj.all()
    len = all.count()
    rule = user_rule.obj.get(user=user_name).rule
    return render(request, "user_list.html", {'all': all, 'len': len, 'user_name': user_name, 'rule': rule})


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


def user_rule_page(request):
    all = user_rule.obj.all()
    length = all.count()
    return render(request, "user-rule.html", {'all': all, 'len': length})


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
        user_rule.obj.create(user=name, rule=1, status=1)
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
        obj0 = user.obj.get(id=i)
        obj1 = user_rule.obj.get(user=obj0.user)
        obj0.delete()
        obj1.delete()
    return HttpResponse(data)


def search_user(request):
    data = request.GET.get('user_name')
    all = user_rule.obj.filter(user__contains=data)
    length = all.count()
    return render(request, "user-rule.html", {'all': all, 'len': length})


def user_status(request):
    data = json.loads(request.GET.get('user_status'))
    print(data)
    status = data['status']
    user_id = data['id']
    user_rule.obj.filter(id=user_id).update(status=status)
    data = '1'
    return HttpResponse(data)


def check_user(request):
    global verify, user_name
    data = json.loads(request.GET.get('data'))
    name = data['name']
    passwd = data['passwd']
    obj = user.obj.filter(user=name)
    status = user_rule.obj.get(user=name).status
    data = '0'
    if status:
        if len(obj) != 0:
            print(obj[0].passwd)
            if passwd == obj[0].passwd:
                data = '1'
                verify = True
                user_name = name
    return HttpResponse(data)
