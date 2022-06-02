#ifndef CO2SENSOR_H
#define CO2SENSOR_H

#include <QObject>
#include "xensivco2.h"
#include <QTimer>
#include <QVector>

class CO2Sensor : public QObject
{
    Q_OBJECT
public:
    CO2Sensor();
    ~CO2Sensor();
    QVector<uint16_t> co2ppm_trend;
    void initCO2(int fd);
    void deinitCO2();

signals:
    void newValue();

private slots:
    void getValue();

private:
    XensivCO2 *co2hdl;
    QTimer *measuretime;
    uint16_t co2ppm;
};

#endif // CO2SENSOR_H
