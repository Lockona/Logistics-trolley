from django.conf import settings
from django.contrib import admin
from django.templatetags.static import static
from django.urls import path, re_path
from order_management.views import *

urlpatterns = \
    [

                  re_path(r'search/$', search_order),
                  re_path(r'del/$', del_order),
    ]
