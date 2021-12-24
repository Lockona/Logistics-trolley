"""web URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/3.2/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path, include
from video.views import video
from order_management.views import login, index, welcome, echarts, order_list, search_page

urlpatterns = [
    path('admin/', admin.site.urls),
    path('', login),
    path('index', index),
    path('welcome', welcome),
    path('echarts1', echarts),
    path('order-list', order_list),
    path('search_page', search_page),
    path('user/', include('user_manager.urls')),
    path('order/', include('order_management.urls')),
    path('video', video)
]
