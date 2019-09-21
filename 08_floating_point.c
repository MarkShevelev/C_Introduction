/**
 * Кроме целочисленных типов в языке C есть специальные типы, которые позволяют сохранять большой диапазон действительных чисел
 * В отличие от целых чисел с арифметикой абсолютной точности, с точностью до 1, типы действительных чисел
 * обеспечивают относительную точность. Иначе говоря, расстояние между двумя отсечками ни числовой прямой между двумя 
 * целыми числами всегда равно одному, а расстояние между двумя соседними действительными числами растёт. 
 * Действительные числа назваются в языке C типами с плавающей точкой (floating point types).
*/

#include <stdio.h>
#include <float.h> //в этом заголовке определены константы, связанные с типами с плавающей точкой

int main() {
    //В языке C есть три типа с плавающей точкой
    float f; //одинарная точность
    printf("float type occupies %llu bytes\n", sizeof(float));

    double d; //двойная точность
    printf("double type occupies %llu bytes\n", sizeof(double));

    //в зависимости от компилятора и платформы возможно наличие типов увеличенной двойной точности
    long double ld; //увеличенная двойная точность
    printf("long double type occupies %llu bytes\n\n", sizeof(double));

    //числа с плавающей точкой всегда со знаком
    //пределы чисел с плавающей точкой можно узнать с помощью специальных констант
    //FLT_MAX - максимальное число типа float
    //FLT_MIN - минимальное положительное число типа float
    //DBL_MAX, DBL_MIN - максимальное и минимальное положительное числа типа double
    printf("float min %e, max %e\n",FLT_MIN,FLT_MAX);
    printf("double min %e, max %e\n\n",DBL_MIN,DBL_MAX);

    /**
     * Числа с плавающей точкой обладают необычным свойством.
     * Из-за того, что промежутки между числами растут, можно прибавить к большому числу настолько маленькое,
     * что значение не изменится.
     */
    float large_number = 1.f; //если мы хотим определить число типа float, нужно поставить точку и суффикс f
    float small_number = 1.e-8f; //приписка e-8 означает, что мы домножаем число на 10^(-8)
    float sum = large_number + small_number;
    printf("The effect of the machine epsilon\n");
    printf("%e + %e = %e\n",large_number,small_number,sum);
    if (large_number == sum) printf("The sum is the same as the large number\n\n");

    /**
     * Минимальное число, которое необходимо прибавить к 1.f, чтобы получить новое число, называется "машинное эпсилон".
     * Эти числа для типов float и double также есть среди предопределённых констант.
     * float - FLT_EPSILON
     * double - DBL_EPSILON
     */
    printf("float epsilon is %e\n",FLT_EPSILON);
    printf("double epsilong is %e\n\n",DBL_EPSILON);

    /**
     * Можно узнать кол-во значащих цифр можно использовать константы
     * float - FLT_DIG
     * double - DBL_DIG
     */
    printf("float significant digits %u\n",FLT_DIG);
    printf("double significant digits %u\n\n",DBL_DIG);

    /**
     * при выводе чисел с плавающей точкой на экран можно ипользовать два формата:
     * i) %f - десятичная дробь, например 0.01234;
     * ii) %e - формат с экспоненциальной записью, например 1.234e-2;
     * iii) %g - автоматический выбор между типами i и ii
     * iV) %a - экспоненциальный формат с шестнадцатиричной записью
     */

    float float_number = 0.000123;
    printf("%f = %e = %g = %a\n",float_number,float_number,float_number,float_number);
    
    return 0;
}