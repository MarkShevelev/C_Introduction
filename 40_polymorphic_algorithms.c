#include <stdio.h>
#include <stdbool.h>

/**
 * Существует ряд алгоритмов, которые не зависят от того,
 * какими именно объектами они оперируют, а полагаются 
 * только на определённые свойства этих объектов.
 * Рассмотрим алгоритм опосредованного копирования данных 
 * из одной переменной в другую.
 * */

void int_copy(int const *src, int *dst) {
    *dst = *src;
}

/**
 * Функция int_copy копирует данные из области памяти с адресом src в область памяти с адресом *dst.
 * Но делает она это исключительно для типа int.
 * Функция, которая делает тоже самое для типа double будет отличаться 
 * только именем типа в сигнатуре.
 */

void double_copy(double const *src, double *dst) {
    *dst = *src;
}

/**
 * Функции int_copy и double_copy так похожи, потому что они выполняют 
 * некоторое действие, которое, на самом деле, не зависит от типа данных, 
 * хранящегося по указанным адресам.
 * Для выполнения алгоритма важно количество байт для копирования, 
 * но совершенно не имеет значения, что именно скрывается за этими адресами.
 * Т.е. алгоритм опосредованного копирования данных не зависит от того 
 * с какими именно данными он работает, а только от определённых свойств - 
 * размер в байтах, в нашем случае.
 * Мы можем написать универсальную функцию опосредованного копирования, 
 * которая будет способна копировать данные из одной области памяти в другую 
 * вне зависимости от типа этих данных. 
 */

void universal_copy(void const *vsrc, void *vdst, unsigned byte_size) {
    /*
     * Мы не можем напрямую работать с типом указателей void их нельзя разыменовать, 
     * придётся привести всё к типу unsigned char.
     */ 
    unsigned char const *src = vsrc;
    unsigned char *dst = vdst; 
    for (unsigned counter = 0; counter != byte_size; ++counter)
        dst[counter] = src[counter];
}

void universal_copy_test() {
    //тест на простейшем типе данных
    int a = 3, b = 5;
    printf("Before copy: a = %d and b = %d\n",a,b);
    universal_copy(&a,&b,sizeof(a)); //from a to b
    printf("After copy: a = %d and b = %d\n",a,b);

    double da = 3.1, db = -5.7;
    printf("Before copy: da = %f and db = %f\n",da,db);
    universal_copy(&da,&db,sizeof(da));
    printf("After copy: da = %f and db = %f\n",da,db);

    //тест на структурах
    struct simple {
        int a;
        double d;
    };
    struct simple s1 = {1,1.1}, s2 = {-1,-1.1};
    printf("Before copy: s1 = {%d,%f}, s2 = {%d,%f}\n",s1.a,s1.d,s2.a,s2.d);
    universal_copy(&s1,&s2,sizeof(s1));
    printf("After copy: s1 = {%d,%f}, s2 = {%d,%f}\n",s1.a,s1.d,s2.a,s2.d);
}

/**
 * Подобные алгоритмы могут включать не только данные в качестве параметров, 
 * но и функции.
 * Рассмотрим функцию, которая решает нелинейное уравнение методом дихотомии. 
 * */

//функция, представляющая уравнение
#include <math.h> //содержит заголовки математических функций, требуется ключ -lm при компиляции в командной строке
float f(float x) {
    return sin(x) - 0.5;
}

//поиск корня уравнения на отрезке между a и b (a < b), причём f(a)*f(b) < 0; tollerance - точность решения
float sinx_solve(float a, float b, float tollerance) {
    float fa = f(a), fb = f(b), c = (a+b)/2.f, fc = f(c);
    while (fabs(fc) > tollerance) {
        if (fc*fa < 0.f) { b = c; fb = fc; } else { a = c; fa = fc; }
        c = (a+b)/2.f;
        fc = f(c);
    }
    return c;
}

void sinx_solve_test() {
    //решение уравнения sin(x) - 0.5 = 0; находится между 0 и pi/2
    float res = sinx_solve(0.f,3.14159265f/2.f,1.e-5); //помните, что точность не может быть лучше машинного эпсилон! FLT_EPSILON
    printf("sin(%f) about 0.5\n",res);
}

/**
 * К сожалению функция sinx_solve позволяет нам решать уравнение только для функции f, 
 * которая строго задана.
 * Если нам потребуется решить уравнение для другой функции g, то придётся скопировать 
 * код sinx_solve в другую функцию g_solve, где изменится только вызов целевой 
 * функции при вычислении fa, fb и fc.
 * Такой подход делает нашу программу "хрупкой" - при необходимости внести изменения в 
 * сам процесс решения, например для устранения ранее не найденной ошибки, 
 * придётся изменить один и тот же код в различных местах.
 * Пригодность программы к внесению изменений называется 'maintainability'.
 * Чем меньше нужно изменить кода и приложить усилий для внесеня изменений, 
 * тем выше 'maintainability' вашей программы.
 * 
 * В случае решения уравнения повысить пригодность к внесению изменений в программу 
 * можно, если целевая функция, для которой мы решаем уравнение, тоже будет 
 * передаваться в функцию решения уравения в качестве параметра.
 * Это можно сделать, используя 'указатели на функции'.
 * */

/**
 * Обратите внимание на последний параметр.
 * Это объявление указателя на функцию.
 * Его имя p
 * Звёздочка перед именем означает, что p - это указатель
 * Но это не указатель на данные, потому мы заключили *p в круглые скобки
 * Объявление p очень похоже на объявлении функции, что не случайно!
 * Для того, чтобы вызвать функцию нам необходимо знать три вещи:
 * i) Что нужно положить на стек ДО передачи управления?
 * ii) Что нужно взять со стека ПОСЛЕ передачи уравления?
 * iii) Где находится эта функция?
 * 
 * Ключевое слово float в круглых скобках отвечает на первый вопрос - это входящий параметр.
 * Ключевое слово float слева от объявления (*p) отвечает на второй вопрос - это исходящие данные.
 * А на последний вопрос отвечает сам p, он хранит адрес функции, которую нужно будет запустить.
 * */
float universal_dichotomy_solve(float a, float b, float tollerance, float (*p) (float)) {
    float fa = p(a), fb = p(b), c = (a+b)/2.f, fc = p(c);
    while (fabs(fc) > tollerance) {
        if (fc*fa < 0.f) { b = c; fb = fc; } else { a = c; fa = fc; }
        c = (a+b)/2.f;
        fc = p(c);
    }
    return c;
}

//ноль функции между 1 и 2 - корень квардратный из 2
float g(float x) {
    return x * x - 2.f;
}

void universal_dichotomy_solve_test() {
    //обратите внимание, что в обоих случая вызывается функция universal_dichotomy_solve
    //для того чтобы передать интересующую вас функцию в качестве параметра p, достаточно указать имя этой функции
    float f_root = universal_dichotomy_solve(0.f,3.14159265/2.f,1.e-5f,f);
    printf("sin(%f) = 0.5\n",f_root);
    float g_root = universal_dichotomy_solve(1.f,2.f,1.e-5f,g);
    printf("(%f)^2 = 2\n", g_root);
}

int main() {
    if (false) universal_copy_test();
    if (false) sinx_solve_test();
    if (false) universal_dichotomy_solve_test();
    return 0;
}