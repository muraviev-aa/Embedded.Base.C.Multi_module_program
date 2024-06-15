#ifndef MULTI_MODULE_TEMP_FUNCTION_H
#define MULTI_MODULE_TEMP_FUNCTION_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#define ERROR_NUM 10
#define STR_LINE puts("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")

extern int january;
extern int february;
extern int march;
extern int april;
extern int may;
extern int june;
extern int july;
extern int august;
extern int september;
extern int october;
extern int november;
extern int december;

typedef struct
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    int8_t temp;
} sensor;

void print_info(void);
int open_file(FILE **fptr, char *name_file);
void print(sensor info[], int number);
void add_record(sensor info[], int number, uint16_t year, uint8_t month,
                uint8_t day, uint8_t hour, uint8_t minute, int8_t temp);
int read_data_file(FILE **fptr, sensor info[]);
double average_month_temp(sensor info[], int number, int month);
int8_t min_month_temp(sensor info[], int number, int month);
int8_t max_month_temp(sensor info[], int number, int month);
double average_year_temp(sensor info[], int number);
int8_t min_year_temp(sensor info[], int number);
int8_t max_year_temp(sensor info[], int number);
void year_statistic(sensor info[], int number);
void month_statistic(sensor info[], int number, uint8_t month_number);
void num_month_row(int month);
int num_to_month(int month_number);
int num_month_row_without_err(sensor info[], int number, uint8_t month_number);

#endif //MULTI_MODULE_TEMP_FUNCTION_H
