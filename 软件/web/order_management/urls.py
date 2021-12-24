from django.contrib import admin
from django.urls import path, re_path
from order_management.views import *

urlpatterns = [
    path('', login),
    path('index', index),
    path('welcome', welcome),
    path('order-list', order_list),
    path('echarts1', echarts),
    re_path(r'order/search/$', search_order),
]
