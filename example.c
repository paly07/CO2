#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/types.h>
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>
              ….
    char devname[20];
    int dev = 1;
    snprintf(devname, 19, "/dev/i2c-%d", dev);
    int fd = open(devname, O_RDWR);
   ioctl(i2c_fd, I2C_SLAVE, XENSIV_PASCO2_I2C_ADDR);
   close(fd); //Close I2C
