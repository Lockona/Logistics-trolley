from django.contrib import admin
from django.urls import path, re_path
from user_manager.views import *

urlpatterns = [
    path('all', user_list),
    path('add_page', add_page),
    re_path(r'edit_page/$', edit_page),
    re_path(r'add/$', add_user),
    re_path(r'edit/$', edit_user),
    re_path(r'del/$', del_user),
    re_path(r'check/$', check_user)
]
