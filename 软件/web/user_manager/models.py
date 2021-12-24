from django.db import models


# Create your models here.
class user(models.Model):
    obj = models.Manager()
    user = models.CharField(max_length=32, verbose_name="用户", unique=True)
    passwd = models.CharField(max_length=16, verbose_name="密码")
    email = models.EmailField(verbose_name="邮箱", unique=True, default="")
