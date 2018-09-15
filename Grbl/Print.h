#ifndef PRINT_H_INCLUDED
#define PRINT_H_INCLUDED


#ifdef __cplusplus
extern "C" {
#endif

#include "Serial.h"

void Print_Init(void);
int Printf(const char *str, ...);
void PrintFloat(float n, uint8_t decimal_places);
void PrintFloat_CoordValue(float n);
void PrintFloat_RateValue(float n);


#ifdef __cplusplus
}
#endif


#endif /* PRINT_H_INCLUDED */
