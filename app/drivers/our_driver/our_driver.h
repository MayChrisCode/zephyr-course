#include <zephyr/device.h>

#ifdef __cplusplus
extern "C" {
#endif

int our_driver_set_param(const struct device *dev, int new_value);


#ifdef __cplusplus
}
#endif
