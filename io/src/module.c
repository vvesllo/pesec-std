#include "../include/module.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

PESEC_SDK_FUNCTION_DEFINE(read)
{
    const value_t fd_value = PESEC_SDK_FUNCTION_ARG("fd");
    const value_t size_value = PESEC_SDK_FUNCTION_ARG("size");

    if (!pesec_sdk_is_number(fd_value)) return pesec_sdk_null_value_cf(CONTROL_FLOW_RETURN);
    if (!pesec_sdk_is_number(size_value)) return pesec_sdk_null_value_cf(CONTROL_FLOW_RETURN);

    const int fd = (int)number_value_to_long_double(fd_value.data.as_number);
    const auto size = (ull_t)number_value_to_long_double(size_value.data.as_number);

    if (size == 0)
        return pesec_sdk_to_string_value_from_cstr("");

    const auto buffer = (char*)malloc(size + 1);
    if (!buffer)
        return pesec_sdk_null_value_cf(CONTROL_FLOW_RETURN);

    const ssize_t bytes_read = read(fd, buffer, size);
    if (bytes_read < 0)
    {
        free(buffer);
        return pesec_sdk_null_value_cf(CONTROL_FLOW_RETURN);
    }

    buffer[bytes_read] = '\0';

    const value_t result = pesec_sdk_to_string_value(buffer, size);

    free(buffer);
    return result;
}

PESEC_SDK_FUNCTION_DEFINE(read_line)
{
    const value_t fd_value = PESEC_SDK_FUNCTION_ARG("fd");

    if (!pesec_sdk_is_number(fd_value)) return pesec_sdk_null_value_cf(CONTROL_FLOW_RETURN);

    const int fd = (int)number_value_to_long_double(fd_value.data.as_number);

    size_t capacity = 256;
    size_t length = 0;
    auto buffer = (char*)malloc(capacity);

    if (!buffer)
        return pesec_sdk_null_value_cf(CONTROL_FLOW_RETURN);

    char c;
    ssize_t bytes_read;

    while ((bytes_read = read(fd, &c, 1)) == 1)
    {
        if (length >= capacity - 1)
        {
            capacity *= 2;
            const auto new_buffer = (char*)realloc(buffer, capacity);
            if (!new_buffer)
            {
                free(buffer);
                return pesec_sdk_null_value_cf(CONTROL_FLOW_RETURN);
            }
            buffer = new_buffer;
        }

        buffer[length++] = c;
        if (c == '\n')
            break;
    }

    if (length == 0 && bytes_read == 0)
    {
        free(buffer);
        return pesec_sdk_null_value_cf(CONTROL_FLOW_RETURN);
    }

    buffer[length] = '\0';

    return pesec_sdk_to_string_value_cf(buffer, length, CONTROL_FLOW_RETURN);
}

PESEC_SDK_FUNCTION_DEFINE(write)
{
    const value_t fd_value = PESEC_SDK_FUNCTION_ARG("fd");
    const value_t data_value = PESEC_SDK_FUNCTION_ARG("data");

    if (!pesec_sdk_is_number(fd_value)) return pesec_sdk_null_value_cf(CONTROL_FLOW_RETURN);

    const int fd_value_int = (int)number_value_to_long_double(fd_value.data.as_number);

    FILE *stream = fdopen(fd_value_int, "w");
    value_print(stream, data_value);
    fflush(stream);

    return pesec_sdk_null_value_cf(CONTROL_FLOW_RETURN);
}

PESEC_SDK_FUNCTION_DEFINE(open)
{
    const value_t filename_value = PESEC_SDK_FUNCTION_ARG("filename");
    const value_t mode_value = PESEC_SDK_FUNCTION_ARG("mode");

    if (!pesec_sdk_is_string(filename_value)) return pesec_sdk_null_value_cf(CONTROL_FLOW_RETURN);
    if (!pesec_sdk_is_string(mode_value)) return pesec_sdk_null_value_cf(CONTROL_FLOW_RETURN);

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
        return pesec_sdk_null_value_cf(CONTROL_FLOW_RETURN);

    const int fd = open(filename_value_string->data, flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    return pesec_sdk_to_number_value_cf(fd, CONTROL_FLOW_RETURN);
}

PESEC_SDK_FUNCTION_DEFINE(close)
{
    const value_t fd_value = PESEC_SDK_FUNCTION_ARG("fd");

    if (!pesec_sdk_is_number(fd_value)) return pesec_sdk_null_value_cf(CONTROL_FLOW_RETURN);

    const int fd_value_int = (int)number_value_to_long_double(fd_value.data.as_number);

    close(fd_value_int);

    return pesec_sdk_to_boolean_value_cf(true, CONTROL_FLOW_RETURN);
}

__attribute__((visibility("default")))
void pesec_module_init(context_t *context)
{
    PESEC_SDK_FUNCTION_REGISTER(read, "fd", "size");
    PESEC_SDK_FUNCTION_REGISTER(read_line, "fd");
    PESEC_SDK_FUNCTION_REGISTER(write, "fd", "data");
    PESEC_SDK_FUNCTION_REGISTER(open, "filename", "mode");
    PESEC_SDK_FUNCTION_REGISTER(close, "fd");
}