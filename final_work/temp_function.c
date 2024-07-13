#include <stdio.h>
#include "temp_function.h"

int num_line_month[12];

// Открыть файл
int open_file(FILE **fptr, char *name_file)
{
    if ((*fptr = fopen(name_file, "r")) == NULL)
    {
        perror("Error opening file");
        return 1;
    }
    return 0;
}

// Добавление записей
void add_record(sensor info[], int number, uint16_t year, uint8_t month,
                uint8_t day, uint8_t hour, uint8_t minute, int8_t temp)
{
    info[number].year = year;
    info[number].month = month;
    info[number].day = day;
    info[number].hour = hour;
    info[number].minute = minute;
    info[number].temp = temp;
}

// Вывод информации о приложении
void print_info(void)
{
    STR_LINE;
    puts("\tConsole application \"Temperature Statistics\"");
    puts("Developer Muraviev A.A.");
    puts("Group EE_IUS #1 02");
    puts("For help with the program, use the -h argument");
    STR_LINE;
    system("pause");
}

// Считываем данные из файла
int read_data_file(FILE **fptr, sensor info[])
{
    int n_scan, year, month, day, hour, minute, temp;
    int error_num[ERROR_NUM] = {0}; // массив для номеров строк c ошибкой
    int count = 0;
    int err_count = 0;
    //int count_month = 1;
    STR_LINE;
    while ((n_scan = fscanf(*fptr, "%d;%d;%d;%d;%d;%d", &year, &month, &day, &hour, &minute, &temp)) > 0)
    {
        num_month_row(month);
        if (n_scan < 6)
        {
            char s[10]; // массив ошибки
            fscanf(*fptr, "%[^\n]", s);
            for (int i = err_count; i < ERROR_NUM; i++)
                error_num[i] = count;
            printf("Line number from the file with the error %d. Error is %s. "
                   "The row will be excluded from the calculation.\n", count + 1, s);
            err_count++;
        } else
            add_record(info, count, year, month, day, hour, minute, temp);
        count++;
    }
    printf("!!! Number of errors in the file is %d !!!\n", err_count);
    return count;
}

// Среднемесячная температура
double average_month_temp(sensor info[], int number, int month)
{
    int sum_temp = 0;
    int count = 0;
    for (int i = 0; i < number; i++)
    {
        if (info[i].month == month)
        {
            sum_temp += info[i].temp;
            count++;
        }
    }
    if (!count)
        return 0;
    return (double) sum_temp / count;
}

// Минимальная температура в текущем месяце
int8_t min_month_temp(sensor info[], int number, int month)
{
    int8_t min_temp = 99;
    for (int i = 0; i < number; i++)
    {
        if (info[i].month == month && info[i].temp < min_temp)
            min_temp = info[i].temp;
    }
    return min_temp;
}

// Максимальная температура в текущем месяце
int8_t max_month_temp(sensor info[], int number, int month)
{
    int8_t max_temp = -99;
    for (int i = 0; i < number; i++)
    {
        if (info[i].month == month && info[i].temp > max_temp)
            max_temp = info[i].temp;
    }
    return max_temp;
}

// Минимальная температура за год
int8_t min_year_temp(sensor info[], int number)
{
    int8_t min_temp = 99;
    for (int i = 0; i < number; i++)
    {
        if (info[i].temp < min_temp)
            min_temp = info[i].temp;
    }
    return min_temp;
}

// Максимальная температура за год
int8_t max_year_temp(sensor info[], int number)
{
    int8_t max_temp = -99;
    for (int i = 0; i < number; i++)
    {
        if (info[i].temp > max_temp)
            max_temp = info[i].temp;
    }
    return max_temp;
}

// Отчет за год
void year_statistic(sensor info[], int number)
{
    double sum_month_avg = 0.0;
    double avg_year_temp;
    STR_LINE;
    printf("%2s%8s%9s%10s%10s%11s%11s%11s\n", "#", "Year", "Month", "NuValue", "ErValue", "MonthAvg",
           "MonthMax", "MonthMin");
    for (int i = 1; i <= 12; i++)
    {
        int count_line_fact = num_month_row_without_err(info, number, i);
        int count_line = num_to_month(i);
        double month_avg = average_month_temp(info, number, i);
        int8_t month_max = max_month_temp(info, number, i);
        int8_t month_min = min_month_temp(info, number, i);
        printf("%2d%8d%9d%10d%10d%11.1f%11d%11d\n", i - 1, info[1].year, i, count_line_fact,
               count_line - count_line_fact, month_avg, month_max, month_min);
        sum_month_avg += month_avg;
    }
    avg_year_temp = sum_month_avg / 12;
    STR_LINE;
    int8_t year_max = max_year_temp(info, number);
    int8_t year_min = min_year_temp(info, number);
    printf("Year statistic: average is %.2f, max is %d, min is %d\n", avg_year_temp, year_max, year_min);
    STR_LINE;
}

// Отчет за месяц
void month_statistic(sensor info[], int number, uint8_t month_number)
{
    int count_line = num_to_month(month_number);
    int count_line_fact = num_month_row_without_err(info, number, month_number);
    double month_avg = average_month_temp(info, number, month_number);
    int8_t month_max = max_month_temp(info, number, month_number);
    int8_t month_min = min_month_temp(info, number, month_number);
    STR_LINE;
    printf("%2s%8s%9s%10s%10s%11s%11s%11s\n", "#", "Year", "Month", "NuValue", "ErValue", "MonthAvg",
           "MonthMax", "MonthMin");
    printf("%2s%8d%9d%10d%10d%11.1f%11d%11d\n", "1", info[1].year, month_number, count_line_fact,
           count_line - count_line_fact, month_avg, month_max, month_min);
    STR_LINE;
}

// Определяем фактическое число строк в файле по номеру месяца включая строки с ошибками
void num_month_row(int month)
{
    if (month == 1)
        num_line_month[0]++;
    else if (month == 2)
        num_line_month[1]++;
    else if (month == 3)
        num_line_month[2]++;
    else if (month == 4)
        num_line_month[3]++;
    else if (month == 5)
        num_line_month[4]++;
    else if (month == 6)
        num_line_month[5]++;
    else if (month == 7)
        num_line_month[6]++;
    else if (month == 8)
        num_line_month[7]++;
    else if (month == 9)
        num_line_month[8]++;
    else if (month == 10)
        num_line_month[9]++;
    else if (month == 11)
        num_line_month[10]++;
    else if (month == 12)
        num_line_month[11]++;
}

// Перевод номера месяца в количество строк
int num_to_month(int month_number)
{
    if (month_number == 1)
        return num_line_month[0];
    else if (month_number == 2)
        return num_line_month[1];
    else if (month_number == 3)
        return num_line_month[2];
    else if (month_number == 4)
        return num_line_month[3];
    else if (month_number == 5)
        return num_line_month[4];
    else if (month_number == 6)
        return num_line_month[5];
    else if (month_number == 7)
        return num_line_month[6];
    else if (month_number == 8)
        return num_line_month[7];
    else if (month_number == 9)
        return num_line_month[8];
    else if (month_number == 10)
        return num_line_month[9];
    else if (month_number == 11)
        return num_line_month[10];
    else if (month_number == 12)
        return num_line_month[11];
    return 0;
}

// Определяем количество строк без ошибок для указанного месяца
int num_month_row_without_err(sensor info[], int number, uint8_t month_number)
{
    int num = 0;
    for (int i = 0; i < number; i++)
    {
        if (info[i].month == month_number)
            num++;
    }
    return num;
}