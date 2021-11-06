/**
  ******************************************************************************
  * File Name          : JSON.h
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TERMINAL_JSON_H
#define __TERMINAL_JSON_H
#ifdef __cplusplus
 extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
//#include <jansson.h>

     class JSONClass
     {


     public:
         int JSONClass::Test(char* json_string);
         //json_t* load_json(const char* text);

         ///* forward refs */
         //void print_json(json_t* root);
         //void print_json_aux(json_t* element, int indent);
         //void print_json_indent(int indent);
         //const char* json_plural(int count);
         //void print_json_object(json_t* element, int indent);
         //void print_json_array(json_t* element, int indent);
         //void print_json_string(json_t* element, int indent);
         //void print_json_integer(json_t* element, int indent);
         //void print_json_real(json_t* element, int indent);
         //void print_json_true(json_t* element, int indent);
         //void print_json_false(json_t* element, int indent);
         //void print_json_null(json_t* element, int indent);
     };

/* Exported constants --------------------------------------------------------*/
/* Exported Macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/




     extern JSONClass JSON;
#ifdef __cplusplus
}
#endif
#endif /*__TERMINAL_JSON_H*/
