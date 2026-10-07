#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>

LOG_MODULE_REGISTER(our_driver, LOG_LEVEL_INF);

#define DT_DRV_COMPAT our_driver
#define LED_NODE DT_ALIAS(app_led)


static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

static int our_driver_channel_get(const struct device *dev, enum sensor_channel chan, struct sensor_value *val)
{


    gpio_pin_set_dt(&led, 1);
    LOG_INF("Hello from our driver channel get");
    return 0;
}

static int our_driver_sample_fetch(const struct device *dev, enum sensor_channel chan)
{

    gpio_pin_set_dt(&led, 0);
    LOG_INF("Hello from our_driver_channel_fetch");
    return 0;
}



static DEVICE_API(sensor, api_iomico_lecture) = {
    .sample_fetch = our_driver_sample_fetch,
    .channel_get = our_driver_channel_get,
};

static int init(const struct device *dev)
{
    if (!gpio_is_ready_dt(&led)) return 0;

    if (gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE) < 0) return 0;


    LOG_INF("device initialized");
    return 0;
}


DEVICE_DT_INST_DEFINE(0, init, NULL, NULL, NULL, POST_KERNEL, 80, &api_iomico_lecture);
//#define DEV_INST(inst) DEVICE_DT_INST_DEFINE(inst,init,NULL,NULL,NULL, POST_KERNEL, 80, &api_iomico_lecture);

//DT_INST_FOREACH_STATUS_OKAY(DEV_INST)