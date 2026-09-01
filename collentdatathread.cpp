#include "collentdatathread.h"
#include <QDebug>

CollentDataThread::CollentDataThread()
{

}

void CollentDataThread::run()
{
    int ret_int=0;
    float ret_float=0.00;
    int temp_raw = 0;
    int temp_offset = 0;
    float temp_scale = 0;
    int hum_raw = 0;
    int hum_offset = 0;
    float hum_scale = 0;
    float tem_float =0;
    float hum_float =0;
    float ill_float =0;
    QString hum;
    QString tem;
    QString ill;
    const char *device1 ="iio:device0";//温湿度
    const char *device2 ="iio:device1";//光照
    while (1)
    {
        /*read temp data*/
        ret_int=read_sysfs_int(device1, "in_temp_raw", &temp_raw);//6869
        if (ret_int < 0)
        {
            qDebug() << "读取温度 raw 失败:" << ret_int;
            QThread::sleep(2);
            continue;
        }
        ret_int=read_sysfs_int(device1, "in_temp_offset", &temp_offset);//-4368
        if (ret_int < 0)
        {
            qDebug() << "读取温度 offset 失败:" << ret_int;
            QThread::sleep(2);
            continue;
        }
        ret_float=read_sysfs_float(device1, "in_temp_scale", &temp_scale);//10.725097656
        if (ret_float < 0)
        {
            qDebug() << "读取温度 scale 失败:" << ret_float;
            QThread::sleep(2);
            continue;
        }
        tem_float =(temp_raw + temp_offset) * temp_scale / 1000;//（6869-4368）*10.725097656/1000
        tem =QString::number(tem_float,'f', 2);//26.81
        ret_int=read_sysfs_int(device1, "in_humidityrelative_raw", &hum_raw);//9499
        if (ret_int < 0)
        {
            qDebug() << "读取湿度 raw 失败:" << ret_int;
            QThread::sleep(2);
            continue;
        }
        ret_int=read_sysfs_int(device1, "in_humidityrelative_offset", &hum_offset);//-786
        if (ret_int < 0)
        {
            qDebug() << "读取湿度 offset 失败:" << ret_int;
            QThread::sleep(2);
            continue;
        }
        ret_float=read_sysfs_float(device1, "in_humidityrelative_scale", &hum_scale);//7.629394531
        if (ret_float < 0)
        {
            qDebug() << "读取湿度 scale 失败:" << ret_float;
            QThread::sleep(2);
            continue;
        }
        hum_float = (hum_raw + hum_offset) * hum_scale / 1000;//（9499-786）*7.629394531/1000
        hum =QString::number(hum_float,'f', 2);//66.47
        ret_float=read_sysfs_float(device2, "in_illuminance_input", &ill_float);//2.8
        if (ret_float < 0)
        {
            qDebug() << "读取光照失败:" << ret_float;
            QThread::sleep(2);
            continue;
        }
        ill =QString::number(ill_float,'f', 2);//2.8
        emit send(tem,hum,ill);//发送温湿度和光照
        QThread::sleep(2);
    }
}

int CollentDataThread::read_sysfs_float(const char *device, const char *filename, float *val)
{
    int ret = 0;
    FILE *sysfsfp;
    char temp[128];
    memset(temp, 0, sizeof(temp));
    ret = snprintf(temp, sizeof(temp),"/sys/bus/iio/devices/%s/%s",device, filename);
    if (ret < 0)
        goto error;
    sysfsfp = fopen(temp, "r");
    if (!sysfsfp)
    {
        ret = -errno;
        goto error;
    }
    errno = 0;
    if (fscanf(sysfsfp, "%f\n", val) != 1)
    {
        ret = errno ? -errno : -ENODATA;
        if (fclose(sysfsfp))
            perror("read_sysfs_float(): Failed to close dir");
        goto error;
    }
    if (fclose(sysfsfp))
        ret = -errno;
error:
    return ret;
}

int CollentDataThread::read_sysfs_int(const char *device, const char *filename, int *val)
{
    int ret = 0;
    FILE *sysfsfp;
    char temp[128];
    memset(temp, 0, sizeof(temp));
    ret = snprintf(temp, sizeof(temp),"/sys/bus/iio/devices/%s/%s",device, filename);
    if (ret < 0)
        goto error;
    sysfsfp = fopen(temp, "r");
    if (!sysfsfp)
    {
        ret = -errno;
        goto error;
    }
    errno = 0;
    if (fscanf(sysfsfp, "%d\n", val) != 1)
    {
        ret = errno ? -errno : -ENODATA;
        if (fclose(sysfsfp))
            perror("read_sysfs_float(): Failed to close dir");
        goto error;
    }
    if (fclose(sysfsfp))
        ret = -errno;
error:
    return ret;
}
