from django.db import models


# Create your models here.

class order(models.Model):
    obj = models.Manager()
    destination = models.CharField(max_length=32, verbose_name="目的地")
    order_status = models.IntegerField(verbose_name="订单状态", default=-1)
    cargo_status = models.IntegerField(verbose_name="货物状态", default=-1)
    time = models.DateTimeField(verbose_name="下单时间")



