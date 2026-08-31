#include "../include/sdk.h"



string_view_t pesec_sdk_to_string_view(const char* value)
{
    return string_view_from(value);
}

value_t pesec_sdk_get_value(const context_t* context, const string_view_t name)
{
    return context_get(context, name)->value;
}

value_t pesec_sdk_to_boolean_value(const bool value)
{
    return value_new_boolean(value);
}

value_t pesec_sdk_to_number_value(const long double value)
{
    return value_new_number(number_value_from_long_double(value));
}

value_t pesec_sdk_to_string_value(char* data, const ull_t size)
{
    return value_new_string(string_value_from(data, size));
}

value_t pesec_sdk_to_string_value_from_cstr(const char* data)
{
    return value_new_string(string_value_from_cstr(data));
}

value_t pesec_sdk_to_function_value(
    parameter_t* parameter,
    const function_value_value_t body,
    const function_value_type_t type,
    context_t* parent_context)
{
    return value_new_function(function_value_new(parameter, body, type, parent_context));
}

value_t pesec_sdk_to_array_value(value_t* data, const ull_t size)
{
    return value_new_array(array_value_new(data, size));
}

value_t pesec_sdk_to_structure_value(context_t *context)
{
    return value_new_structure(structure_value_new(context));
}

value_t pesec_sdk_to_module_value(context_t* context)
{
    return value_new_module(module_value_new(context));
}


bool pesec_sdk_is_boolean(const value_t value) { return value.type == VALUE_TYPE_BOOLEAN; }

bool pesec_sdk_is_number(const value_t value) { return value.type == VALUE_TYPE_NUMBER; }

bool pesec_sdk_is_string(const value_t value) { return value.type == VALUE_TYPE_STRING; }

bool pesec_sdk_is_function(const value_t value) { return value.type == VALUE_TYPE_FUNCTION; }

bool pesec_sdk_is_array(const value_t value) { return value.type == VALUE_TYPE_ARRAY; }

bool pesec_sdk_is_structure(const value_t value) { return value.type == VALUE_TYPE_STRUCTURE; }

bool pesec_sdk_is_module(const value_t value) { return value.type == VALUE_TYPE_MODULE; }
