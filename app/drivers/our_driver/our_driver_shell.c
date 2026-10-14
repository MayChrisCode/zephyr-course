#include <zephyr/shell/shell.h>
#include <zephyr/drivers/sensor.h>
#include <our_driver.h>

#define MINIMUM 10
#define MAXIMUM 100

static const struct device *dev = DEVICE_DT_GET_ANY(our_driver);


static int cmd_fetch_handler(const struct shell *shell, int argc, char **argv)
{
    sensor_sample_fetch(dev);
    shell_print(shell, "hello from fetch handler");
    return 0;
}

static int cmd_read_handler(const struct shell *shell, int argc, char **argv)
{
    sensor_channel_get(dev, SENSOR_CHAN_ALL, NULL);
    shell_print(shell, "hello from get handler");
    return 0;
}

static int cmd_set_param_handler(const struct shell *shell, int argc, char **argv)
{

    //comment for new commit for task 02 as I forgot to commit it for task 01
    int new_value = atoi(argv[1]);

    if (new_value < MINIMUM || new_value > MAXIMUM)
    {
        shell_print(shell, "Value must be between %d and %d", MINIMUM, MAXIMUM);
        return -EINVAL;
    }
    else
    {
        shell_print(shell, "Value is valid: %d", new_value);
        our_driver_set_param(dev, 42);
    }

    return 0;
}

static int cmd_info_handler(const struct shell *shell, int argc, char **argv)
{

    if(dev == NULL)
    {
        shell_print(shell, "Device not found");
        return -ENODEV;
    }

    shell_print(shell, "Device name: %s", dev->name);
    shell_print(shell, "Device state: %s", device_is_ready(dev) ? "ready" : "not ready");
    shell_print(shell, "hello from info handler");




    return 0;
}


SHELL_STATIC_SUBCMD_SET_CREATE(sub_sensorroot,
    SHELL_CMD_ARG(fetch, NULL, "Get Sample value for our driver", cmd_fetch_handler,1,0),
    SHELL_CMD_ARG(read, NULL, "Get Channel for our driver", cmd_read_handler,1,0),
    SHELL_CMD_ARG(info, NULL, "Info about our driver", cmd_info_handler,1,0),
    SHELL_CMD_ARG(set_param, NULL, "Set parameter for our driver", cmd_set_param_handler,2,0),
    SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(sensorroot, &sub_sensorroot, "Sensor commands", NULL);