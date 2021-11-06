/**
  ******************************************************************************
  * File Name          : JSON.cpp
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "Terminal/Terminal.h"
#include "JSON.h"
//#include <jansson.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef TERMINAL_USE_STM
#include "cmsis_os2.h"
#include <stdlib.h>
#elif defined(TERMINAL_USE_WINDOWS)
#include "..\Threads.h"
#include <Windows.h>
#endif /*TERMINAL_USE_STM*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
//used when debugging, declared in the file Terminal.h
#ifdef DEBUG_TERMINAL_JSON
#undef DEBUG /* DEBUG */
#undef DEBUG_PRINT /* DEBUG_PRINT */
#define DEBUG(...)		do {debug_header("JSON: ", __VA_ARGS__);} while (0)
#define DEBUG_PRINT(...)		debug_print(__VA_ARGS__);
#else
#define DEBUG(...)
#define DEBUG_PRINT(...)
#endif // DEBUG_TERMINAL_JSON
JSONClass JSON;


/* Private variables ---------------------------------------------------------*/



/* Private function prototypes -----------------------------------------------*/

//void JSONClass::print_json(json_t* root) { print_json_aux(root, 0); }

//void JSONClass::print_json_aux(json_t* element, int indent) {
    //switch (json_typeof(element)) {
    //case JSON_OBJECT:
    //    print_json_object(element, indent);
    //    break;
    //case JSON_ARRAY:
    //    print_json_array(element, indent);
    //    break;
    //case JSON_STRING:
    //    print_json_string(element, indent);
    //    break;
    //case JSON_INTEGER:
    //    print_json_integer(element, indent);
    //    break;
    //case JSON_REAL:
    //    print_json_real(element, indent);
    //    break;
    //case JSON_TRUE:
    //    print_json_true(element, indent);
    //    break;
    //case JSON_FALSE:
    //    print_json_false(element, indent);
    //    break;
    //case JSON_NULL:
    //    print_json_null(element, indent);
    //    break;
    //default:
    //    fprintf(stderr, "unrecognized JSON type %d\n", json_typeof(element));
    //}
//}

//void JSONClass::print_json_indent(int indent) {
//    int i;
//    for (i = 0; i < indent; i++) {
//        putchar(' ');
//    }
//}
//
//const char* JSONClass::json_plural(int count) { return count == 1 ? "" : "s"; }
//
//void JSONClass::print_json_object(json_t* element, int indent) {
//    size_t size;
//    const char* key;
//    json_t* value;
//
//    print_json_indent(indent);
//    size = json_object_size(element);
//
//    DEBUG_PRINT("JSON Object of %ld pair%s:\n", size, json_plural(size));
//    json_object_foreach(element, key, value) {
//        print_json_indent(indent + 2);
//        DEBUG_PRINT("JSON Key: \"%s\"\n", key);
//        print_json_aux(value, indent + 2);
//    }
//}

//void JSONClass::print_json_array(json_t* element, int indent) {
//    size_t i;
//    size_t size = json_array_size(element);
//    print_json_indent(indent);
//
//    DEBUG_PRINT("JSON Array of %ld element%s:\n", size, json_plural(size));
//    for (i = 0; i < size; i++) {
//        print_json_aux(json_array_get(element, i), indent + 2);
//    }
//}
//
//void JSONClass::print_json_string(json_t* element, int indent) {
//    print_json_indent(indent);
//    DEBUG_PRINT("JSON String: \"%s\"\n", json_string_value(element));
//}
//
//void JSONClass::print_json_integer(json_t* element, int indent) {
//    print_json_indent(indent);
//    DEBUG_PRINT("JSON Integer: \"%" JSON_INTEGER_FORMAT "\"\n", json_integer_value(element));
//}
//
//void JSONClass::print_json_real(json_t* element, int indent) {
//    print_json_indent(indent);
//    DEBUG_PRINT("JSON Real: %f\n", json_real_value(element));
//}
//
//void JSONClass::print_json_true(json_t* element, int indent) {
//    (void)element;
//    print_json_indent(indent);
//    DEBUG_PRINT("JSON True\n");
//}
//
//void JSONClass::print_json_false(json_t* element, int indent) {
//    (void)element;
//    print_json_indent(indent);
//    DEBUG_PRINT("JSON False\n");
//}
//
//void JSONClass::print_json_null(json_t* element, int indent) {
//    (void)element;
//    print_json_indent(indent);
//    DEBUG_PRINT("JSON Null\n");
//}
//
///*
// * Parse text into a JSON object. If text is valid JSON, returns a
// * json_t structure, otherwise prints and error and returns null.
// */
//json_t* JSONClass::load_json(const char* text) {
//    json_t* root;
//    json_error_t error;
//
//    root = json_loads(text, 0, &error);
//
//    if (root) {
//        return root;
//    }
//    else {
//        DEBUG_PRINT("json error on line %d: %s\n", error.line, error.text);
//        return (json_t*)0;
//    }
//}
//
///* ================================================================
// * main
// */
//
//#define MAX_CHARS 4096
//
//int JSONClass::Test(char *json_string) {
//    static char line[MAX_CHARS];
//
//    /* parse text into JSON structure */
//    json_t* root = load_json(line);
//
//    if (root) {
//        /* print and release the JSON structure */
//        print_json(root);
//        json_decref(root);
//    }
//
//    return 0;
//}


