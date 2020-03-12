/**
 * Инкрементная компиляция - это способ создавать программу 
 * не единым файлом исходного кода, а из нескольких небольших 
 * файлов исходного кода, которые могут быть написаны разными 
 * людьми в разное время.
 * */

/**
 * Наиболее простой способ при использовании компилятора gcc 
 * скомпилировать программу из нескольких файлов исходного кода
 * - это выписать их подряд
 * Например есть два файла main.c  и sum.c
 * */

/*-------------- main.c -------------------*/
#include <stdio.h>

int sum(int,int); //декларация функции sum, функцию можно вызывать не имея её исходного кода

int main() {
    int x, y;
    scanf("%d%d",&x,&y);
    printf("%d + %d = %d\n",sum(x,y));
}
/*-----------------------------------------*/

/*--------------- sum.c -------------------*/
int sum(int x, int y) {
    return x + y;
}
/*-----------------------------------------*/

/**
 * В файле main.c не содержится кода функции sum.
 * Файл sum.c не содержит функции main.
 * Если попытаться скомпилировать эти файлы отдельно 
 * один от другого, возникнут ошибки.
 * gcc main.c -o main -std=c99 //возникнет ошибка undefined reference to function sum
 * gcc sum.c -o main -std=c99  //возникнет ошибка underined reference to function main
 * gcc main.c sum.c -o main -std=c99 //ОК!
 * */

/**
 * В одном файле может быть несколько функций.
 * Тогда нам необходимо прописать в main.c декларации 
 * для всех используемых функций.
 * Например есть два файла main.c и arithmetic.c
 * */

/*---------------- main.c -------------------*/
#include <stdio.h>

int sum(int,int);
int mul(int,int);
int sum(int,int);
int divv(int,int);

int main() {
    int x, y;
    scanf("%d%d",&x,&y);

    printf("Choose operation:\n1) sum\n2) sub\n3) mul\n4) div\n"); fflush(stdout);
    int choice;
    scanf("%d",&choice);
    switch(choice) {
        case 1:
            printf("%d + %d = %d\n",x,y,sum(x,y));
            break;

        case 2:
            printf("%d - %d = %d\n",x,y,sub(x,y));
            break;

        case 3:
            printf("%d * %d = %d\n",x,y,mul(x,y));
            break;

        case 4:
            printf("%d / %d = %d\n",x,y,divv(x,y));
            break;

        default:
            printf("Unknown operation...\n");
    }

    return 0;
}
/*-------------------------------------------*/

/*---------------- arithmetic.c -------------*/
int sum(int x, int y) {
    return x + y;
}

int sub(int x, int y) {
    return x - y;
}

int mul(int x, int y) {
    return x * y;
}

int divv(int x, int y) {
    return x / y;
}
/*-------------------------------------------*/

/**
 * Если функций много, то каждый раз прописывать 
 * полный список всех деклараций вручную неудобно.
 * Для этого удобно использовать дерективу препроцессора
 * #include
 * Необходимо создать дополнительный файл с заголовками функций.
 * Такой файл называется 'заголовочным' или 'header'. 
 * */

/*---------------- arithmetic.h -------------*/
int sum(int,int);
int mul(int,int);
int sum(int,int);
int divv(int,int);
/*-------------------------------------------*/

/**
 * Теперь его необходимо добавить в main.c
 * */

/*------------------ main.c -----------------*/
#include <stdio.h>

#include "arithmetic.h"

int main() {
    int x, y;
    scanf("%d%d",&x,&y);

    printf("Choose operation:\n1) sum\n2) sub\n3) mul\n4) div\n"); fflush(stdout);
    int choice;
    scanf("%d",&choice);
    switch(choice) {
        case 1:
            printf("%d + %d = %d\n",x,y,sum(x,y));
            break;

        case 2:
            printf("%d - %d = %d\n",x,y,sub(x,y));
            break;

        case 3:
            printf("%d * %d = %d\n",x,y,mul(x,y));
            break;

        case 4:
            printf("%d / %d = %d\n",x,y,divv(x,y));
            break;

        default:
            printf("Unknown operation...\n");
    }

    return 0;
}
/*-------------------------------------------*/

/**
 * Компиляция происходит так же:
 * gcc main.c arithmetic.c -o main -std=c99
 * */

/**
 * Однако наиболее важным является то, что файлы main.c и arithmetic.c 
 * можно компилировать раздельно!
 * gcc -c main.c -o main.o -std=c99
 * gcc -c arithmetic.c -o arithmetic.o -std=c99
 * 
 * Добавление ключа -c в команду компиляции говорит gcc, что 
 * не следует создавать исполняемый файл, но только скомпилировать 
 * исходный код в машинный.
 * Теперь у нас есть два файла main.o и arithmetic.o, эти файлы 
 * называются объектными.
 * Их можно скомпоновать в исполняемый
 * 
 * gcc main.o arithmetic.o -o main -std=c99
 * */

/**
 * Раздельная компиляция файлов позволяет ускорить компиляцию за счёт того, 
 * что перекомпилировать необходимо только тот файл, который изменился.
 * Если же файлов очень много, то прописывать их все в командную строку 
 * сложно. Кроме того, увеличивается время линковки, потому что линкер 
 * проходится линейным поиском по машинному коду в поисках адреса функции 
 * при каждом обнаружении вызова функции.
 * 
 * Последняя проблема разрешается с помощью статических библиотек 
 * static library
 * 
 * Статические библиотеки создаются утилитой ar.
 * 
 * Пусть у нас есть четыре файла
 * one.c two.c three.c four.c
 * 
 * И файл main.c, в котором используются функции из первых четырёх.
 * 
 * Скомпилируем четыре файла
 * gcc -c one.c -o one.o
 * gcc -c two.c -o two.o
 * gcc -c three.c -o three.o
 * gcc -c four.c -o four.o
 * 
 * Соберём файлы в библиотеку
 * ar rcs libmylib.a one.o two.o three.o four.o
 * 
 * Обратите внимание на название библиотеке
 * libmylib.a 
 * 
 * Все статические библиотеки должны называться lib*.a
 * Начинаться с lib и заканчиваться .a
 * Вместо * вписывается название библиотеки.
 * 
 * При компиляции библиотека добавляется через название с ключом -l
 * gcc main.c -lmylib -o main -stc=c99
 * 
 * Если библиотека находится не в стандартном каталоге, то 
 * путь до неё можно указать через ключ -L
 * 
 * gcc main.c -L /home/usr/lib -lmylib -o main -std=c99
 * */