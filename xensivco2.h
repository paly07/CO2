#ifndef XENSIVCO2_H
#define XENSIVCO2_H

#include<QObject>
#include "xensiv_pasco2.h"

typedef int32_t Error_t;
typedef xensiv_pasco2_status_t Diag_t;
typedef xensiv_pasco2_boc_cfg_t ABOC_t;

class XensivCO2 : public QObject
{
    Q_OBJECT
public:
    XensivCO2();
    ~XensivCO2();

    Error_t begin           (bool i2c, bool uart);
    Error_t end             (bool i2c, bool uart);
    Error_t startMeasure    (int16_t  periodInSec = 0, int16_t alarmTh = 0, void (*cback) (void *) = nullptr);
    Error_t stopMeasure     ();
    Error_t getCO2          (uint16_t & CO2PPM);
    Error_t getDiagnosis    (Diag_t & diagnosis);
    Error_t setABOC         (ABOC_t aboc, int16_t abocRef);
    Error_t setPressRef     (uint16_t pressRef);
    Error_t reset           ();
    Error_t getDeviceID     (uint8_t & prodID, uint8_t & revID);
    int i2c_fd;          /**< I2C interface*/

private:
    int  uart_fd;         /**< UART interface */
    uint8_t           intPin;       /**< Interrupt pin */

    static constexpr uint16_t baudrateBps = 9600;      /**< UART baud rate in bps */
    static constexpr uint32_t freqHz      = 100000;    /**< I2C frequency in Hz*/
    static constexpr uint8_t       unusedPin = 0xFFU; /**< Unused pin */
    xensiv_pasco2_t   dev;          /**< XENSIV™ PAS CO2 corelib object */
};

#endif // XENSIVCO2_H
