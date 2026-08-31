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

PESEC_SDK_FUNCTION_DEFINE(open)
{
    const value_t filename_value = PESEC_SDK_FUNCTION_ARG("filename");
    const value_t mode_value = PESEC_SDK_FUNCTION_ARG("mode");

    if (!pesec_sdk_is_string(filename_value)) return pesec_sdk_to_number_value(-1.f);
    if (!pesec_sdk_is_string(mode_value)) return pesec_sdk_to_number_value(-1.f);

    const string_value_t* filename_value_string = filename_value.data.as_string;
    const string_value_t* mode_value_string = mode_value.data.as_string;

    int flags = O_RDONLY;

    if (strcmp(mode_value_string->data, "w") == 0 ||
        strcmp(mode_value_string->data, "w+") == 0 ||
        strcmp(mode_value_string->data, "a") == 0 ||
        strcmp(mode_value_string->data, "a+") == 0)
        flags = O_WRONLY | O_CREAT | (
            strcmp(mode_value_string->data, "a") == 0 ||
            strcmp(mode_value_string->data, "a+") == 0 ? O_APPEND : O_TRUNC);
    else if (strcmp(mode_value_string->data, "r+") == 0)
        flags = O_RDWR;
    else
        return pesec_sdk_to_number_value(-1);

    const int fd = open(filename_value_string->data, flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    return pesec_sdk_to_number_value(fd);
}

PESEC_SDK_FUNCTION_DEFINE(close)
{
    const value_t fd_value = PESEC_SDK_FUNCTION_ARG("fd");

    if (!pesec_sdk_is_number(fd_value)) return pesec_sdk_to_boolean_value(false);

    const int fd_value_int = (int)number_value_to_long_double(fd_value.data.as_number);

    close(fd_value_int);

    return pesec_sdk_to_boolean_value(true);
}

__attribute__((visibility("default")))
void pesec_module_init(context_t *context)
{
    PESEC_SDK_FUNCTION_REGISTER(write, "fd", "data");
    PESEC_SDK_FUNCTION_REGISTER(open, "filename", "mode");
    PESEC_SDK_FUNCTION_REGISTER(close, "fd");
}