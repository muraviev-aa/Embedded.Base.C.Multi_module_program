<a name="readme-top"></a>

![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
![GitHub](https://img.shields.io/badge/github-%23121011.svg?style=for-the-badge&logo=github&logoColor=white)
![CLion](https://img.shields.io/badge/CLion-black?style=for-the-badge&logo=clion&logoColor=white)

## Многомодульная программа
### Консольное приложение "Статистика температуры"

<p align="center">
<img src="images/multi.png" alt="drawing" width="300"/>
</p>

#### Приложение позволяет вывести следующие данные по температуре за месяц и год:

* среднемесячная температура;
* минимальная температура в текущем месяце;
* максимальная температура в текущем месяце;
* среднегодовая температура;
* минимальная температура за год;
* максимальная температура за год.

#### Приложение позволяет выявить ошибки в файле. Выводится следующая информация:

* номер строки файла с ошибкой;
* какие символы являются ошибочными;
* общее число ошибок в файле.

#### Приложение обрабатывает следующие аргументы командной строки:

* -h Описание функционала приложения;
* -m <номер месяца> Выводится статистика только за указанный месяц;
* -f <filename.csv> Указание входного файла *.csv для обработки.

#### Сборка приложения осуществляется при помощи утилиты make.

#### Файлы для тестирования работы приложения:

* temperature_small.csv
* temperature_big.csv

#### Примеры работы приложения:

* обработка показаний датчика температуры за год

<p align="center">
<img src="images/big1.png" alt="drawing" width="800"/>
</p>

* обработка показаний датчика температуры за указанный месяц

<p align="center">
<img src="images/big2.png" alt="drawing" width="800"/>
</p>

#### Предусмотрен запуск программы с ярлыка с указанием аргументов командной строки:

<p align="center">
<img src="images/shortcut.png" alt="drawing" width="350"/>
</p>

#### Состав репозитория:
<url> &#128194; final_work </url> - файлы проекта

<url> &#128194; images </url> - файлы *.png для README.md

<url> &#128194; report </url> - отчет по работе

<p align="right">(<a href="#readme-top">вверх</a>)</p>
