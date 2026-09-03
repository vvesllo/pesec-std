#ifndef PESEC_SDK_SDK_H
#define PESEC_SDK_SDK_H

#include <include/context.h>
#include <include/value.h>
#include <include/array_value.h>
#include <include/structure_value.h>
#include <include/string_value.h>
#include <include/module_value.h>
#include <include/number_value.h>
#include <include/function_value.h>
#include <include/array_value.h>
#include <stdlib.h>


#ifdef __cplusplus
extern "C" {
#endif


#define PESEC_THROW(...) \
    do { \
        fprintf(stderr, __VA_ARGS__); \
        exit(EXIT_FAILURE);\
    } while (0)

// functions with argument
#define PESEC_SDK_FUNCTION_REGISTER(function_name, ...) \
    context_push( \
        context, \
        string_view_from(#function_name), \
        value_new_function( \
            function_value_new( \
                parameter_new_from_cstr((const char *[]){__VA_ARGS__, nullptr}), \
                (function_value_value_t){ \
                    .as_c_function = pesec_impl_##function_name \
                }, \
                FUNCTION_VALUE_TYPE_C_FUNCTION, \
                context \
            ) \
        ), \
        true \
    )

// functions without argument
#define PESEC_SDK_FUNCTION_REGISTER_0(function_name) \
    PESEC_SDK_FUNCTION_REGISTER(function_name, nullptr)

#define PESEC_SDK_FUNCTION_DEFINE(function_name) \
    static value_t pesec_impl_##function_name(context_t *context)

#define PESEC_SDK_FUNCTION_ARG(name) \
    pesec_sdk_get_value(context, pesec_sdk_to_string_view(name))

string_view_t pesec_sdk_to_string_view(const char* value);

value_t pesec_sdk_get_value(const context_t* context, string_view_t name);

value_t pesec_sdk_to_boolean_value(bool value);
value_t pesec_sdk_to_number_value(long double value);
value_t pesec_sdk_to_string_value(char* data, ull_t size);
value_t pesec_sdk_to_string_value_from_cstr(const char* data);
value_t pesec_sdk_to_function_value(
    parameter_t* parameter,
    function_value_value_t body,
    function_value_type_t type,
    context_t* parent_context);
value_t pesec_sdk_to_array_value(value_t* data, ull_t size);
value_t pesec_sdk_to_structure_value(context_t* context);
value_t pesec_sdk_to_module_value(context_t* context);

value_t pesec_sdk_to_boolean_value_cf(bool value, control_flow_t control_flow);
value_t pesec_sdk_to_number_value_cf(long double value, control_flow_t control_flow);
value_t pesec_sdk_to_string_value_cf(char* data, ull_t size, control_flow_t control_flow);
value_t pesec_sdk_to_string_value_from_cstr_cf(const char* data, control_flow_t control_flow);
value_t pesec_sdk_to_function_value_cf(
    parameter_t* parameter,
    function_value_value_t body,
    function_value_type_t type,
    context_t* parent_context,
    control_flow_t control_flow);
value_t pesec_sdk_to_array_value_cf(value_t* data, ull_t size, control_flow_t control_flow);
value_t pesec_sdk_to_structure_value_cf(context_t* context, control_flow_t control_flow);
value_t pesec_sdk_to_module_value_cf(context_t* context, control_flow_t control_flow);

value_t pesec_sdk_null_value();
value_t pesec_sdk_null_value_cf(control_flow_t control_flow);

bool pesec_sdk_is_boolean(value_t value);
bool pesec_sdk_is_number(value_t value);
bool pesec_sdk_is_string(value_t value);
bool pesec_sdk_is_function(value_t value);
bool pesec_sdk_is_array(value_t value);
bool pesec_sdk_is_structure(value_t value);
bool pesec_sdk_is_module(value_t value);
bool pesec_sdk_is_null(value_t value);


typedef void (*module_init_t)(context_t* module_context);

#ifdef __cplusplus
}
#endif

#endif // PESEC_SDK_SDK_H