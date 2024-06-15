#include "temp_function.h"
#define SIZE 30

int main(int argc, char *argv[])
{
    sensor info[SIZE];
    FILE *fptr;
    int rez = 0;
    char *file_name;
    uint8_t month_number = 0;
    int count = 0;
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
                break;
            case 'f':
                file_name = optarg;
                //printf("%s\n", file_name);
                break;
            case 'm':
                month_number = atoi(optarg); // преобразуем строку с аргументом в число
                //printf("%d\n", month_number);
                break;
            default:
                printf("Error found!\n");
                break;
        }
    }

    open_file(&fptr, file_name);
    count = read_data_file(&fptr, info);
    fclose(fptr);
    //print(info, count);
    year_statistic(info, count);
    //month_statistic(info, count, month_number);
    return 0;
}