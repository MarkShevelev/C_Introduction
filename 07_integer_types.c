/**
 * В языке C есть несколько целочисленных типов, которые различаются
 * количеством занимаемых байт и диапазоном значений 
 */

#include <stdio.h>
#include <limits.h> //в этом файле находятся константы, хранящие значения диапазонов различных целочисленных типов

int main() {
    //char - один из самых маленьких типов данных, занимает строго! 1 байт
    char charachter = 'a'; //char хранит символы, символы в литеральных константах записываются в одинарных ковычках

    /**
     * Целочисленные типы бывают знаковыми (signed) и беззнаковыми (unsigned)
     * signed позволяют хранить как положительные, так и отрицательные числа
     * unsigned позволяет хранить только! положительные
    */
    signed char sch_num = -1; //однобайтовое число со знаком
    unsigned char uch_num = 2; //однобайтовое число без знака
    //тип char может быть как знаковым, так и беззнаковым - это зависит от поставщика компилятора

    signed short int ssh_num = -32000; //двухбайтовое целое число со знаком, сокращённое название signed short или short
    unsigned short int ush_num = 65000; //двухбайтовое целое число без знака, скоращённое название unsigned short

    signed int si_num = 2000000000; //четырёхбайтовое целое число со знаком, сокращённое название int
    unsigned int usi_num = 4000000000u; //четырёхбайтовое целое число со знаком, коращённое название unsigned

    signed long int sl_num = 2000000000l; //размер и диапазон зависят от системы и компилятора, сокращённое название long
    unsigned long int usl_num = 4000000000lu; //размер и диапазон зависят от системы и компилятора, сокращённое название unsigned long

    signed long long int sll_num = 2000000000ll; //размер и диапазон зависят от системы и компилятора, сокращённое название long long
    unsigned long long int usll_num = 4000000000llu; //размер и диапазон зависят от системы и компилятора, сокращённое название unsigned long long

    /**
     * Обратите внимание, что литеральные константы при инициализации типов unsigned, long и т.д.
     * снабжены суффиксами. По умолчанию целочисленные литеральные константы имеют тип int,
     * чтобы выписать литеральную константу для типа с большим диапазоном, необходимо добавить суффикс.
     * unsigned - u
     * long - l
     * unsigned long - lu
     * long long - ll
     * unsigned long long - llu
     */

    /**
     * Так как типы могут зависеть от системы и компилятора,
     * полезно знать, как выяснять размеры типов на заданной платформе
     */
    printf("signed types:\n");
    printf("char        %d %d\n", SCHAR_MIN, SCHAR_MAX);
    printf("short       %d %d\n", SHRT_MIN, SHRT_MAX);
    printf("int         %d %d\n",INT_MIN,INT_MAX);
    printf("long        %ld %ld\n",LONG_MIN,LONG_MAX); //при выводе чисел long нужно использовать местозаместитель %ld
    printf("long long   %lld %lld\n\n",LLONG_MIN,LLONG_MAX); //при выводе чисел long long нужно использовать местозаместитель %lld

    printf("unsigned types:\n"); //минимальные значения всех беззнаковых типов = 0
    printf("char        %u\n", UCHAR_MAX);
    printf("short       %u\n", USHRT_MAX);
    printf("int         %u\n", UINT_MAX);
    printf("long        %lu\n", ULONG_MAX); //при выводе чисел unsigned long нужно использовать местозаместитель %lu
    printf("long long   %llu\n\n", ULLONG_MAX); //при выводе чисел unsigned long long нужно использовать местозаместитель %llu
  
    //количество байт для определённого типа можно найти с помощью операции sizeof
    printf("long occupies %llu bytes\n",sizeof(long)); //можно подставить как имя типа
    printf("long long occupies %llu bytes\n\n", sizeof(sll_num)); //так и имя переменной

    return 0;
}