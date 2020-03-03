/**
 * В языке C в стандартную библиотеку входит ряд функций для работы 
 * с файлами. Существует два способа работы: символьный, в кодировке 
 * ASCII, и бинарный, запись байтов в файл.
 * Рассмотрим символьные или текстовые файлы.
 * */

#include <stdio.h> //функции для работы с файлами находятся в этом заголовочном файле
#include <stdbool.h>


void new_file_test() {
    /**
     * Основные функции для работы с файлами:
     * fopen - открыть файл, запросить доступ к файлу
     * fclose - закрыть файл, вернуть ресурс операционной системе
     * fprintf - запись в файл
     * fscanf - чтение из файла
     * */

   FILE *descriptor = fopen("./new_file.txt","w");
   /**
    * Параметры вызова fopen:
    * 1) имя файла
    * 2) режим работы с файлом
    * "w" означает, что файл будет заново создан, если 
    * файл уже существует, то он будет очищен.
    * 
    * Возвращает функция адрес на 'дескриптор' файла.
    * Что за структура FILE несущественно. 
    * Важно, что это некие данные контекста, которые 
    * используются другими функциями для работы с файлами.
    * */

   /**
    * Так как файл - это ресурс операционной системы, то 
    * он может оказаться недоступен. Либо у программы 
    * недостаточно прав для открытия файла, либо нет связи 
    * с выбранным диском, либо файл уже занят другой программой.
    * Мы должны проверить, что дескриптор успешно получен.
    * Если произойдёт какая-либо ошибка, то fopen вернёт 
    * NULL.
    * */
   if (NULL == descriptor) {
       printf("Can't open file!\n");
       return;
   }

   fprintf(descriptor,"Hello file!\n"); //fprintf работает аналогично функции printf, только не выводит данные на экран, а записывает в файл
   /**
    * Первым параметром функция fprintf принимает адрес, ранее полученный от функции fopen.
    * Это обязательно должен быть верный адрес, на действительную область памяти со структурой FILE.
    * В противном случае возникнет неопределённое поведение.
    * */

   fclose(descriptor); //'отпускаем файл', теперь операционная система может передать файл другой программе
}

/**
 * Операции с файлами - это удалённые операции. Т.е. они происходят 
 * не в рамках памяти, выделенной программе, а с обращением к другой 
 * памяти и даже физическим устройствам.
 * Любая операция при работе с файлом может быть неудачной.
 * Следует проверять успешность каждой операции!
 * В частности, функция fprintf возвращает целое число, которое означает 
 * количество успешно записанных символов. Можно проверять это число 
 * на совпадение с ожидаемым количеством.
 * */
void fprintf_error_test() {
    FILE *descriptor = fopen("./new_file.txt","w");
    if (NULL == descriptor) {
        printf("Can't open file!\n");
        return;
    }

    int resA = fprintf(descriptor,"Hello File!\n");
    int resB = fprintf(descriptor,"Hello number %d!\n", 5);
    int resC = fprintf(descriptor,"Hello string %s and number %f\n","\"World\"",5);
    printf("Results: %d %d %d\n",resA,resB,resC);

    fclose(descriptor);
}

/**
 * Представленный выше подход не очень удобен, особенно учитывая то факт, 
 * что данные вряд ли будут иметь заранее известную длину в символах.
 * Для проверки корректности работы с файлом 
 * можно использовать функцию ferror().
 * ferror принимает дескриптор и возвращает 0, если всё хорошо.
 * */
void ferror_test() {
    FILE *descriptor = fopen("./new_file.txt","w");
    if (NULL == descriptor) {
        printf("Can't open file!\n");
        return;
    }

    fprintf(descriptor,"Hello File!");
    if (ferror(descriptor)) {
        fclose(descriptor);
        printf("Error in writing to file!\n");
        return;
    }

    fclose(descriptor);
}

/**
 * Пример программы, которая записывает в файл случайный числа.
 * Количество чисел задаёт пользователь с клавиатуры.
*/
#include <stdlib.h> //srand rand

void random_numbers_file_write_test() {
    srand(23);

    FILE *descriptor = fopen("./new_file.txt","w");
    if (NULL == descriptor) {
        printf("Can't open file!\n");
        return;
    }

    int how_many;
    scanf("%d",&how_many);

    for (int count = 0; count != how_many; ++count) {
        fprintf(descriptor,"%d\n",rand()%100);
        if (ferror(descriptor)) {
            printf("Error in printing data to file!\n");
            goto CLEAR;
        }
    }

CLEAR:
    fclose(descriptor);
}

int main() {
    if (false) new_file_test();
    if (false) fprintf_error_test();
    if (false) ferror_test();
    if (false) random_numbers_file_write_test();

    return 0;
}