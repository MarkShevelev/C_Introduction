/**
 * Некоторые задачи удобно решать, если можно направить программу по разному пути 
 * в зависимости от каких-либо значений. В некоторых случаях это необходимо. 
 * Основным инструментом для подобных задач в языке C является условная конструкция
 * if () { } else { }
 * if - ключевое слово, начало конструкции
 * () - в круглых скобках помещается условие
 * if () { } - блок кода, следующий за if (), исполняется в случае, если условие верно
 * else { } - блок кода, следующий за else, исполняется в случае, если условие ложно
 * Для использования этой конструкции не нужно включать никаких заголовочных файлов,
 * она доступна "из коробки". 
 */

#include <stdio.h>

int main() {
    /**
     * Рассмотрим задачу.
     * Расстояние от дуба Совы, эффективного менеджера, до дачи Филина Филипповича
     * составляет 286 км. Шишкомобиль Совы расходует 12 шишек на 100 км.
     * Сколько минимально нужно заправить шишек в шишкомобиль, чтобы Сова добралась
     * до Филина.
     * Эту задачу можно решить не прибегая к условным конструкциям, но мы рассмтрим 
     * её решение с их использованием.
     */
    int distance = 286, rate = 12;
    int cones_count = (distance*rate)/100;
    //если distance*rate делится на 100 нацело, то cones_count - это ответ
    //инаце нужно добавить одну шишку
    if (distance*rate%100 == 0) { //точное сравнение выражается операцией ==
        printf("The answer is %d cones\n", cones_count);
    }
    else { //данная ветвь срабатывает, если distance*rate не делится на 100
        printf("The answer is %d cones\n", cones_count + 1);
    }

    /**
     * Для решения задачи выше мы использовали проверку на точное совпадение.
     * Число делится на 100, если остаток от деления этого числа на 100 в точности равен 0.
     * Точное равенство выражается операцией ==.
     */
    //проверим, что три переменные равны между собой
    int a = 1, b = 1, c = 1; //поменяйте значения и результат вывода изменится
    if (a == b) { //первые два числа должны быть равны между собой
        if (b == c) { //т.к. a уже равно b, то равенство между b и c по транзитивности даст нам совпадение всех трёх!
            printf("The numbers are the same!\n");
        }
        else {
            printf("The numbers are not the same!\n");
        }
    }
    else { //если первые два числа не совпали, то и все три не одинаковы
        printf("The numbers are not the same!\n");
    }

    /**
     * Кроме проверки на точное совпадение в языке C есть возможность проверить порядок следования чисел:
     * a > b - a больше b
     * a < b - a меньше b
     * a >= b - a больше или равно b
     * a <= b - a меньше или равно b
     * a != b - a неравно b (a отлично от b)
     * 
     * Рассмотрим задачу
     * Даны два концентрических круга радиусами 12 и 5 и центром в начале координат.
     * Напишите программу, которая определит попадание точки в кольцо, 
     * образованное вычитанием малого круга из большого.
     */
    int r = 5, R = 12;
    int x = 1, y = 5; //измените значения для иного результата
    if ((x*x + y*y) >= r*r) { //расстояние от точки до центра не менее малого радиуса
        if ((x*x + y*y) <= R*R) { //одновременно с этим расстояние от точки до центра не превосходит большой радиус
            printf("The point (%d,%d) is inside the ring [%d,%d]!\n",x,y,r,R);
        }
        else {
            printf("The point (%d,%d) is not inside the ring [%d,%d]!\n",x,y,r,R);
        }
    }
    else {
        printf("The point (%d,%d) is not iside the ring [%d,%d]!\n",x,y,r,R);
    }
    //обратите внимание, что, как и любые другие блоки, условные блоки могут вкладываться один в другой!

    /**
     * Сравнивать можно не только целые числа, но и действительные числа.
     * Рассмотрим задачу о попадании точки в интервал.
     * Даны координаты начала и конца интервала (begin,end).
     * Определите, попадает ли точка с заданной координатой p в указанный интервал.
     */
    float begin = -5.12f, end = 10.18f;
    float p = -1.2f;
    if (p > begin) { //строгое неравенство для интервала
        if (p < end) {
            printf("The point %f is insed interval (%f,%f)!\n",p,begin,end);
        }
        else {
            printf("The point %f is not insed interval (%f,%f)!\n",p,begin,end);
        }
    }
    else {
        printf("The point %f is not insed interval (%f,%f)!\n",p,begin,end);
    }

    /**
     * Сравнивать можно даже символы! Их сравнение будет происходить по числовому коду ASCII.
     * Так любая заглавная буква меньше любой строчной, а любая буква или цифра больше символа пробела.
     * Латинские буквы в кодировки ASCII расположены по алфавиту, так что буквы, которые идут раньше по алфавиту 
     * будут меньше букв, идущих позже по алфавиту. Но заглавные буквы имеют меньшие коды, чем строчные, так что 
     * они всё равно идут раньше. Между собой заглавные буквы упорядочены по алфавиту.
     * Такой порядок называют "лексикографическим".
     */
    char space = ' '; //символ пробела
    char a_symbol = 'a'; //строчная 'a'
    char A_symbol = 'A'; //заглавная 'A'
    char B_symbol = 'B'; //заглавная 'B'
    if (space < A_symbol) { printf("space goes before 'a'\n"); } else { printf("space goes after 'a'\n"); }
    if (a_symbol > A_symbol) { printf("'a' goes after 'A'\n"); } else { printf("'a' goes before 'A'\n"); }
    if (A_symbol < B_symbol) { printf("'A' goes before 'B'\n"); } else { printf("'A' goes after 'B'\n"); }
    if (A_symbol != B_symbol) { printf("'A' and 'B' have different ASCII codes\n"); } else { printf("'A' and 'B' have identical ASCII codes\n"); }

    return 0;
}