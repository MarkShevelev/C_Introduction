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
 * */
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
            printf("Error in printing data to file!\nProcess terminated!\n");
            goto CLEAR;
        }
    }

CLEAR:
    fclose(descriptor);
}

/**
 * Для чтения символов кодировки ASCII из файла используется 
 * функция fscanf. Она работает также, как и функция scanf, 
 * за тем исключением, что принимает в качестве первого параметра 
 * дескриптор файла.
 * Пример программы, которая читае из файла 10 целых чисел.
 * */

void fscanf_test() {
    FILE *descriptor = fopen("./new_file.txt","r");
    /**
     * Если мы собираемся читать данные из файла, то 
     * при вызове функции fopen во втором параметре
     * мы указываем режим "r" (read). В этом случае 
     * мы сможем читать форматированные данные из 
     * файла, но не сможем в него ничего записывать.
     * Кроме того, если файл не существует, дескриптор 
     * не будет создан.
     * */
    
    //необходимая проверка на успешное открытие файла
    if (NULL == descriptor) {
        printf("Can't open file to read!\n");
        return;
    }

    for (unsigned counter = 0; counter != 10; ++counter) {
        int num;
        fscanf(descriptor,"%d",&num);
        printf("%d\n",num);
        if (ferror(descriptor)) {
            printf("Error while reading the file!\nProcess terminated!\n");
            goto CLEAR;

        }
    }
CLEAR:
    fclose(descriptor);
}

/**
 * При использовании функции fscanf успешность её завершения можно 
 * проверить не только вызовом ferror, но и анализом числа, которое 
 * она возвращает. fscanf возвращает количество успешно прочитанных 
 * элементов. Например, вызов fscanf(descriptor,"%d %d",&a,&b) вернёт 
 * 2, если оба числа будут успешно прочитаны, 1 - прочитано только одно,
 * 0 - ничего не прочитано, константу EOF, если не удалось начать чтение.
 * В отличие от функции fprintf, использование возвращаемого параметра 
 * для fscanf значительно удобнее.
 * ferror вернёт не ноль только в том случае, если произойдёт ошибка, 
 * не допускающая дальнейшего чтения. Однако при чтении форматированных 
 * данных ошибка чтения може быть не связана с проблемами самого файла, 
 * а только с неверным форматом.
 * Например, если в файле встретится буква, а fscanf ожидает целое число, 
 * то ferror вернёт 0, т.к. проблем с чтением из файла нет, но fscanf 
 * не сработает, т.к. буква - это не число.
 * Ниже приведён лучший вариант чтения набора целых чисел из файла.
 * */

void fscanf_return_value_test() {
    FILE *descriptor = fopen("./new_file.txt","r");
    if (NULL == descriptor) {
        printf("Can't open file to read!\n");
        return;
    }

    for (unsigned counter = 0; counter != 10; ++counter) {
        int num;
        if ( 1 != fscanf(descriptor,"%d",&num)) {
            if (ferror(descriptor))
                printf("Error while reading the file!\nProcess terminated!\n");
            else
                printf("Input format error!\n");
            
            goto CLEAR;
        }
        printf("%d\n",num);
    }

CLEAR:
    fclose(descriptor);
}

/**
 * В предыдущем примере мы читали данные, зная количество элементов.
 * Однако не всегда количество данных в файле известно.
 * Например, если мы открываем текстовый файл, то не знаем заранее 
 * сколько именно символов в нём содержится.
 * Для того чтобы прочитать файл до самого конца, нам требуется 
 * читать файл и каждый раз проверять успешность чтения. Как только 
 * чтение оборвётся - данные кончились. Но если данные в файле ещё 
 * содержатся, а мы просто не смогли получить доступ к нему? Например,
 * если в процессе чтения файл был удалён.
 * Для диагностики достижения конца файла используется функция feof, 
 * она возвращает не ноль в том случае, когда конец файла был достигнут.
 * Следовательно, если после чтения файла до первой ошибки мы обнаружим, 
 * что feof возвращает ненулевое значение, значит мы считали файл полностью.
 * Ниже приведён пример программы, которая читает целые числа до конца файла.
 * */

void read_file_to_the_end() {
    FILE *descriptor = fopen("./new_file.txt","r");
    if (NULL == descriptor) {
        printf("Can't open file to read!\n");
        return;
    }

    int num; unsigned counter = 0;
    while (1 == fscanf(descriptor,"%d",&num)) {
        ++counter;
        printf("%d\n",num);
    }
    printf("%d numbers been read\n",counter);

    if (!feof(descriptor)) //проверка на достижение конца файла, если проверка провалена, мы не дочитали до конца
        printf("File hasn't been read to the end!\n");

CLEAR:
    fclose(descriptor);
}


/**
 * Пример чтения и записи табулированной функции в виде ascii символов.
 * */

#include <math.h> //математические функции

void function_infile_tabulation_test() {
    { //записывам данные в файл
        FILE *out_stream = fopen("./sin_tab.txt","w");
        if (NULL == out_stream) {
            printf("Can't open file to write!\n");
            goto END;
        }

        float arg_begin = 0.f, step = 3.14159265f/100.f;
        for (unsigned counter = 0; counter != 101; ++counter) {
            fprintf(out_stream,"%f %e\n",arg_begin + step*counter, sin(arg_begin + step*counter));
            if (ferror(out_stream)) {
                printf("File stream error!\n");
                goto CLEAR_PRINT;
            }
        }
    CLEAR_PRINT:
        fclose(out_stream);
    }

    {
        FILE *in_stream = fopen("./sin_tab.txt","r");
        if (NULL == in_stream) {
            printf("Can't open file to read!\n");
            goto END;
        }

        float arg, val;
        while(2 == fscanf(in_stream,"%f %e",&arg, &val)) {
            printf("sin(%f) = %e\n",arg,val);
        }

        if (!feof(in_stream)) {
            printf("File wasn't read to the end!\n");
        }
        
        fclose(in_stream);
    }

END:;
}


/**
 * Для универсализации работы с потоками данных в стандартной 
 * библиотеке языка C есть специальные глобальные константы 
 * которые отвечают потокам ввода и вывода в консоль.
 * Для поток вывода используется константа stdout, а для 
 * потока ввода stdin.
 * */

void console_io_via_file_streams() {
    //считываение чисел из консоли
    int num[10];
    for (unsigned count = 0; count != 10; ++count) {
        fscanf(stdin,"%d",num + count);
    }

    //печать чисел в консоль
    for (unsigned count = 0; count != 10; ++count)
        fprintf(stdout,"%d ",num[9 - count]);
    fprintf(stdout,"\n");
}



int main() {
    if (false) new_file_test();
    if (false) fprintf_error_test();
    if (false) ferror_test();
    if (false) random_numbers_file_write_test();
    if (false) fscanf_test();
    if (false) fscanf_return_value_test();
    if (false) read_file_to_the_end();
    if (false) function_infile_tabulation_test();
    if (false) console_io_via_file_streams();

    return 0;
}