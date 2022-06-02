#include "co2sensor.h"
#include <QDebug>

CO2Sensor::CO2Sensor()
{
    measuretime = new QTimer(this);
    connect(measuretime, &QTimer::timeout, this,  &CO2Sensor::getValue);
}

CO2Sensor::~CO2Sensor()
{    
    delete measuretime;
}

void CO2Sensor::initCO2(int fd)
{
    co2ppm_trend.clear();
    co2hdl = new XensivCO2();
    co2hdl->i2c_fd = fd;
    if(XENSIV_PASCO2_OK != co2hdl->begin(true, false))
    {
        qDebug()<<"Initialization error";
    }
    else
    {
        qDebug()<<"Pressure reference: "<<co2hdl->setPressRef(900);
        qDebug()<<"Start measure: "<<co2hdl->startMeasure(10);
        measuretime->start(1000);
    }
}

void CO2Sensor::deinitCO2()
{
    measuretime->stop();
    if(XENSIV_PASCO2_OK != co2hdl->end(true, false))
    {
        qDebug()<<"DeInitialization error";
    }
    delete co2hdl;
}

void CO2Sensor::getValue()
{    
    uint16_t co2ppm_l;
    Error_t ret;
    ret = co2hdl->getCO2(co2ppm_l);
    if(ret == XENSIV_PASCO2_OK)
    {
        co2ppm = co2ppm_l;
        qDebug()<<"Value: "<<co2ppm;
        co2ppm_trend.append(co2ppm);
        emit newValue();
    }
}

