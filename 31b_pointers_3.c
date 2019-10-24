/**
 * Примеры использования указателей для решения задач, 
 * требующих косвенного доступа.
 */

#include <stdio.h>
#include <stdbool.h>


/**
 * Задание 1.
 * Напишите функцию, которая обменивает значения двух 
 * указателей со связанным типом int.
 */

/**
 * Функция swap, которую мы писали ранее, обменивала 
 * значения между двумя переменными типа int.
 */
void swap(int *a, int *b) {
    int tmp = *a; //сохраняем значение, хранящееся по адресу 'a', во временную переменную
    *a = *b; //перезаписываем данные, хранящиеся по адресу 'a', данными, хранящимися по адресу 'b'
    *b = tmp; //и перезаписываем данные, хранящиеся по адресу 'b'
}
/**
 * Функция swap реализует обычный обмен через временную 
 * ячейку, но обращение к данным происходит косвенно.
 * Использование этой функции для обмена данными между 
 * двумя указателями невозможно.
 * Однако основные шаги алгоритма общие для любого 
 * обмена! Следует вспомнить, что указатели - это 
 * тоже переменные и у них тоже есть адреса. Типы 
 * переменных, которые представляют собой указатели 
 * на адреса определяется как int**.
 */
void swap_ptr(int **a, int **b) { //следует только поменять типы входящих параметров
    int *tmp = *a; //и временной переменной
    *a = *b;
    *b = tmp;
}

/**
 * Пример использования функции swap_ptr.
 */
void swap_ptr_test() {
    int a = 3, *a_ptr, b = 5, *b_ptr;
    a_ptr = &a;
    b_ptr = &b;

    printf("a = %d b = %d | *a_ptr = %d *b_ptr = %d\n",a,b,*a_ptr,*b_ptr);

    swap_ptr(&a_ptr,&b_ptr);
    
    //обратите внимание, что значения переменных a и b не изменились, т.е. мы обменяли данные именно переменных a_ptr и b_ptr    
    printf("a = %d b = %d | *a_ptr = %d *b_ptr = %d\n",a,b,*a_ptr,*b_ptr);
} 


/**
 * Задание 2.
 * Функция может возвращать только одно значение 
 * через стек, которое можно указать при вызове 
 * ключевого слова. Если функция должна вернуть 
 * пару значений, то это ограничение можно обойти 
 * используя косвенный доступ.
 * Напишите функцию, которая принимает два числа, 
 * производит деление с остатком и косвенно 
 * возвращает частное и остаток.
 */

void div2(int a, int b) {
    int q = a/b;
    int r = a%b;
}

/**
 * Функция выше не производит полезных действий, 
 * но показывает, что процедура деления с остатком 
 * пораждает два значения: q(частное) и r(остаток).
 * Нельзя вернуть посредством return сразу два 
 * значения. Но можно получить пару адресов. 
 * Зная адреса, мы можем записать данные косвенно, 
 * без необходимости явно возвращать значения.
 */
void div2_ptr(int a, int b, int *q_ptr, int *r_ptr) {
/**
 * Здесь q_ptr - это адрес памяти, куда следует записать частное,
 * а r_ptr - это адрес памяти, куда следует записать остаток.
 */
    int q = a/b;
    int r = a%b;
    *q_ptr = q; //записываем результат деления по адресу
    *r_ptr = r; //Записываем остаток от дления
}

/**
 * Пример использования функции div2_ptr.
 */
void div2_ptr_test() {
    int a = 5, b = 2; //хотим поделить a на b с остатком
    int q, r; //эти переменные нам нужны, чтобы функция div2_ptr могла в их память записать данные
    div2_ptr(a,b,&q,&r); //не забываем, что функция ожидает адреса
    printf("%d/%d = %d and %d\n",a,b,q,r);
}


/**
 * Задание 3.
 * Очень часто функция не может быть успешно 
 * выполнена для некоторых значений аргументов.
 * Простейший пример такой функции - деление.
 * Функция деления не может быть выполнена, 
 * если делитель равен нулю. В подобной ситуации 
 * функция должна сообщить об ошибке. Получается, 
 * что функция должна венуть два значения: 
 * результат вычисления (например частное) и 
 * данные об успешности вычисления (статус вычисления).
 * Функция не может вернуть два значения посредством 
 * return. Выход - это использование косвенного 
 * доступа к памяти для записи одно из параметров.
 * В таких случаях принято, чтобы функция возвращала 
 * статус посредством return: 0 - всё хорошо, 
 * 1 - деление на ноль.Напишите функцию деления, 
 * которая проверяет возможность проведения операции
 * деления и перезаписывает результат косвенно в  
 * целочисленную переменную, а возвращает статус 
 * посредством return. 
 */

//из описания сразу понятно, как именно должен выглядить список параметров и возвращаемые данные
int div_with_status(int a, int b, int *result) {
    //если b не равно нулю, то функция отрабатывает по обычному сценарию
    if (0 != b) {
        *result = a/b; //результат перезаписываем косвенно
        return 0; //возвращаем статус 0 - деление успешно
    }
    return 1; //ничего не делаем, возвращаем статус - деление на ноль
}

/**
 * Пример использования функции div_with_status.
 */

void div_with_status_test() {
    {
        int a = 5, b = 2, res;
        int status = div_with_status(a,b,&res); //для результата передаём адрес, он будет перезаписан косвенно
        if (0 == status) //если статус равен нулю, то деление прошло успешно
            printf("%d/%d = %d\n",a,b,res);
        else
            printf("Division by zero!"); //деление на ноль (только если b равно 0)
    }

    //вызывает ошибку деления на ноль
    {
        int a = 5, b = 0, res;
        int status = div_with_status(a,b,&res);
        if (0 == status)
            printf("%d/%d = %d\n",a,b,res);
        else
            printf("Division by zero!");
    }
}


int main() {
    if (false) swap_ptr_test();
    if (false) div2_ptr_test();
    if (false) div_with_status_test();
    return 0;
}

        
