#include "../include/module.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

PESEC_SDK_FUNCTION_DEFINE(write)
{
    const value_t fd_value = PESEC_SDK_FUNCTION_ARG("fd");
    const value_t data_value = PESEC_SDK_FUNCTION_ARG("data");

    if (!pesec_sdk_is_number(fd_value)) return pesec_sdk_to_boolean_value(false);

    const int fd_value_int = (int)number_value_to_long_double(fd_value.data.as_number);

    FILE *stream = fdopen(fd_value_int, "w");
    value_print(stream, data_value);
    fflush(stream);

    return pesec_sdk_to_boolean_value(true);
}

__attribute__((visibility("default")))
void pesec_module_init(context_t *context)
{
    PESEC_SDK_FUNCTION_REGISTER(write, "fd", "data");
}