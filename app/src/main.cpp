#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <stdio.h>
#include <our_driver.h>



#define SLEEP_TIME_MS 1000

/* The devicetree node identifier for the "app_led" alias. */




const struct device *dev = DEVICE_DT_GET_ANY(our_driver);



LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

int main(void)
{
    bool led_state = true;
    int set_value = 0;


    if (!device_is_ready(dev)) {
        LOG_ERR("Device not ready");
        return -ENODEV;
    }


    while (1) {

        if (led_state)
        {
            our_driver_set_param(dev, set_value);
            sensor_sample_fetch(dev);
            led_state = false;
        }
        else
        {
            our_driver_set_param(dev, set_value);
            sensor_channel_get(dev, SENSOR_CHAN_ALL, NULL);
            led_state = true;
        }

        set_value += 1;

        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);
;
    }
    return 0;
}
