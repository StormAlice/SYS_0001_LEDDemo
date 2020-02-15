
#define LOG_TAG "LedHal"

/*	1.实现一个名为HMI的hw_module结构体	*/

/*	2.实现一个open函数，它返回led_device_t结构体	*/

/*	3.实现led_device_t结构体	*/


/*	参考	vibrator.c	G:\SharedFile\git\Android\android_system_code\android-5.0.2\hardware\libhardware_legacy\vibrator	1604	2015/3/25	32	*/

#include <hardware/vibrator.h>
#include <hardware/hardware.h>

#include <cutils/log.h>

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>
#include "Led_hal.h"

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <android/log.h>  /* liblog */
 

static jint fd;

static int led_close(struct led_device_t *dev){
	ALOGI("led_close fd=%d", fd);
	close(fd);
	return 0;
}
static int led_open(struct led_device_t *dev){
	fd = open("/dev/leds", O_RDWR);
	ALOGI("led_Open fd=%d", fd);
	if(fd>=0)
		return 0;
	else
		return -1;

}
static int led_ctrl(struct led_device_t *dev,  int which, int status){
	int ret = ioctl(fd, status, which);
	ALOGI("led_ctrl :%d, %d, %d",which, status, ret);

	return ret;

}


static struct led_device_t led_dev{
	.common = {
		.close	=	led_close,
	},
	.led_open	=	led_open,
	.led_ctrl = 	led_ctrl,
};

static int led_device_open(const hw_module_t* module,
                      hw_device_t** device) {
	
	*device		=	&led_dev;
	
    return 0;
}


static struct hw_module_methods_t led_module_methods = {
    .open = led_device_open,
};


/*	实现一个名为HMI的hw_module_t结构体				*/
struct hw_module_t HAL_MODULE_INFO_SYM = {
    .id = "led",
    .methods = &led_module_methods,
};


