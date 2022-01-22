# Generated by Django 3.2.7 on 2021-12-23 09:15

from django.db import migrations, models
import django.db.models.manager


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='order',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('destination', models.CharField(max_length=32, verbose_name='目的地')),
                ('order_status', models.IntegerField(default=-1, verbose_name='订单状态')),
                ('cargo_status', models.IntegerField(default=-1, verbose_name='货物状态')),
                ('time', models.DateTimeField(verbose_name='下单时间')),
            ],
            managers=[
                ('obj', django.db.models.manager.Manager()),
            ],
        ),
    ]