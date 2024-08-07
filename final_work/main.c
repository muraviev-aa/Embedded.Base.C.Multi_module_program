#include "temp_function.h"
#define SIZE 600000

int main(int argc, char *argv[])
{
    sensor *info = (sensor *) malloc(SIZE * sizeof(sensor));
    if (!info)
        printf("Error while allocating memory!\n");
    FILE *fptr;
    int rez;
    char *file_name;
    uint8_t month_number;
    int count;
    int flag_f = 0;
    int flag_m = 0;
    opterr = 0; // cообщение об ошибках не появляется
    if (argc == 1)
        print_info();
    // Работа с аргументами командной строки
    while ((rez = getopt(argc, argv, "hf:m:")) != -1)
    {
        switch (rez)
        {
            case 'h':
                STR_LINE;
                puts("\t\t\t\tHELP");
                puts("List keys:");
                puts("-h\t\t\thelp application;");
                puts("-f file_name.csv\tspecify a file to display statistics for the year;");
                puts("-m month_number\t\tdisplay statistics for the specified month.");
                STR_LINE;
                system("pause");
                break;
            case 'f':
                file_name = optarg;
                flag_f = 1;
                break;
            case 'm':
                month_number = atoi(optarg); // преобразуем строку с аргументом в число
                flag_m = 1;
                break;
            default:
                printf("Error found!\n");
                break;
        }
    }

    open_file(&fptr, file_name);
    count = read_data_file(&fptr, info);
    fclose(fptr);
    if (flag_f == 1 && flag_m == 1)
        month_statistic(info, count, month_number);
    else
        year_statistic(info, count);
    free(info);
    system("pause");
    return 0;
}