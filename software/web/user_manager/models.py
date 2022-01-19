from django.db import models


# Create your models here.
class user(models.Model):
    obj = models.Manager()
    user = models.CharField(max_length=32, verbose_name="用户", unique=True)
    passwd = models.CharField(max_length=16, verbose_name="密码")
    email = models.EmailField(verbose_name="邮箱", unique=True, default="")


class user_rule(models.Model):
    obj = models.Manager()
    rule_choices = ((1, '订单管理'), (2, '订单管理,管理员管理'), (3, '订单管理,管理员管理,权限修改'))
    status_choices = ((0, '停用'), (1, '启用'))
    user = models.CharField(max_length=32, verbose_name="用户", unique=True)
    rule = models.IntegerField(verbose_name='权限', choices=rule_choices)
    status = models.IntegerField(verbose_name='状态', choices=status_choices)
