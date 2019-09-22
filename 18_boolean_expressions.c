/**
 * Во многих ситуациях бывает удобнее выразить сложное условие отдельно от действий, 
 * которые должны быть выполнены в случае верного или неверного условия.
 * Это повышает гибкость программы в сопровождении, так как нет необходимости 
 * бегать по коду и исправлять утверждения в различных его частях.
 * С другой стороны, сложные вложенные условия могут быть упрощены с использованием 
 * специальных логических, "булевых" операторов выражений.
 */

#include <stdio.h>

int main() {
    /**
     * Рассмотрим задачу о попадании точки с заданными координатами в кольцо.
     * Мы использовали два вложенных условия:
     * if ((x*x+y*y) >= r*r) -- условие попадания во внешнюю область малого круга
     * if ((x*x+y*y) <= R*R) -- условие попадания во внутреннюю область большого круга
     * На самом же деле эти условия по отдельности нам не интересны. Важно, чтобы 
     * эти условия выполнялись вместе, т.е. одновременно. Такая ситуация описывается 
     * логической операцией "конъюнкция", иначе "логическое И". Мы хотим, чтобы 
     * (x*x+y*y) >= r*r 'И' (x*x+y*y) <= R*R
     * В языке C есть специальный оператор, который позволяет соединить два таких условия:
     * && - логическое 'И'.
     */
    int r = 5, R = 12, x = 1, y = 5;
    if ((x*x+y*y) >= r*r && (x*x+y*y) <= R*R)
        printf("The point (%d,%d) is insed the ring [%d,%d]\n",x,y,r,R);
    else
        printf("The point (%d,%d) is not inside the ring [%d,%d]\n",x,y,r,R);
    //код легче прочитать, наши намерения становятся более ясными, а дублирование кода снижается

    /**
     * Если обратиться к задаче о високосном годе, то одним оператором && не обойтись.
     * Год будет не високосным, если он не кратен 4 ЛИБО кратен 100 И не кратен 400.
     * Наличие двух разных вариантов, каждый из которых в отдельности приводит к верному
     * условию, называется "дизъюнкция", логическое 'ИЛИ'. В это случае могут выполняться 
     * оба варианта или только один, но этого достаточно, чтобы всё условие стало верным.
     * В языке C такая логическая операция выражается оператором ||
     */
    int year = 1900;
    if (year%4 || (0 == year%100 && year%400))
        printf("The year %d is not leap\n", year);
    else
        printf("The year %d is leap\n", year);

    /**
     * Таким образом с помощью операторов && и || можно составлять очень сложные условия.
     * Рассмотрим задачу о пересечении двух отрезков.
     * Даны координаты двух отрезков на оси: begin_a, end_a, begin_b, end_b. Требуется узнать 
     * есть ли общая часть у этих отрезков.
     */
    int begin_a = 1, end_a = 10, begin_b = -1, end_b = 5;
    //у отрезков будет общая часть, если начало ЛИБО конец одного отрезка находится внутри другого
    if ( (begin_a >= begin_b && begin_a <= end_b) || (end_a >= begin_b && end_a <= end_b) )
        printf("The segments are overlapping\n");
    else
        printf("The segments are not overlapping\n");
    
    /**
     * Приоритет операций сравнения больше, чем у логических операций, 
     * потому брать операции сравнения или арифметические операции в скобки не требуется.
     * Однако между собой операции && (логическое И) и || (логическое ИЛИ) различаются по приоритету.
     * Оператор && имеет более высокий приоритет, потому скобки, 
     * окружающие логические связки на строках 41 и 54 не требуются.
     */
    /**
     * Логические операции также применимы и в условиях для тернарного оператора.
     */

    /**
     * Конструкция if ожидает в круглых скобках некоторого выражения, которое можно вычислить, 
     * затем сравнивает результат с нулём. Так происходит не только с арифметическими операциями, 
     * но и с операциями сравнения. Операции сравнения тоже генерируют числовые значения по принципу:
     * 0 - если неверно, 1 - если верно. Эти значения можно сохранять и выводить на экран.
     */
    int a = 3, b = -3;
    printf("The boolean operation 'a > b' value is %d\n", a > b); //1 для верного
    printf("The boolean operation 'a < b' value is %d\n", a < b); //0 для неверного

    int boolean_result = a == b; //сравнение иммет более высокий приоритет, чем присваивание
    printf("The boolean operation 'a == b' value is %d\n", boolean_result);

    /**
     * Используя механизм условных выражений и переменных, мы можем предварительно расчитывать 
     * значения сложных выражений, а затем использовать результаты в дальнейших вычислениях.
     * Преобразуем задачу о високосном годе.
     */
    int is_not_leap_year = year%4 || 0 == year%100 && year%400; //скобки убраны, т.к. приоритет && выше ||
    printf("The year %d %s leap\n", year, is_not_leap_year ? "is not" : "is");

    /**
     * Рассмотрим задачу.
     * Напишите булевое выражение для проверки трёх длин отрезков на неравенство треугольника
     */
    int l1 = 3, l2 = 4, l3 = 5;
    //приоритет арифметических операций выше, чем сравнения и логических
    int is_triangle = l1 + l2 > l3 && l2 + l3 > l1 && l1 + l3 > l2;
    printf("%d, %d and %d %s form a triangle\n",l1,l2,l3, is_triangle ? "can" : "can't");

    /**
     * Пользуясь законами обратности операций сравнения (например a <= b является отрицанием к a > b)
     * и законами де Моргана мы всегда можем выписать отрицания к булевым выражениями.
     * Например выпишем условие того, что год високосный.
     * is_lear => (отрицание)(is_not_leap) => (отрицание)(year%4 || 0 == year%100 && year%400) => 
     * 0 == year%4 && (отрицание)(0 == year%100 && year%400) => 0 == year%4 && (year%100 || 0 == year%400) =>
     * 0 == year%4 && year%100 || 0 == year%400
     * 
     * Тем не менее бывает удобнее написать отрицание к более простому утвреждению. 
     * Для этого в языке C определён специальный оператор !
     * Оператор ! превращает правду в ложь, а ложь в правду.
     */
    //воспользуемся отрицанием, чтобы выразить условие непопадания точки в кольцо
    int outside_the_ring = !(x*x + y*y >= r*r && x*x + y*y <= R*R);

    /**
     * Оператор отрицания имеет самый приоритет выше, даже чем у арифметических операций!
     * Это может привести к неожиданному результату при неаккуратном использовании.
     */
    int good_number = 3;
    int bad_logic = !good_number/4; //поставьте скобки вокруг goold_number/4 и результат вывода изменится
    printf(bad_logic ? "good" : "bad");

    return 0;
}