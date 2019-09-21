/**
 * В языке C код организуется с помощью трёх основных элементов:
 * i) выражение (expression) - это синтаксическая конструкция, которая конструирует значение;
 * ii) утверждение (statement) - это одна из последовательно исполняемых команд, состоит из выражений;
 * iii) блок - набор statement'ов.
 */

#include <stdio.h>

int main() {
    /**
     * Арифметические выражения - это один из самых распространённых видов выражений,
     * такие выражения генерируют числовые значения за счёт выполнения арифметических операций.
     */
    int a = 1, b = 2, c = 3;
    int result = a*b + b*c + c*a; //правая часть инициализации - арифметическое выражение
    //такое выражение можно напрямую использовать в вызовах печати
    printf("a*a + b*b + c*c = %d\n",a*a + b*b + c*c);
    //деструктивное присваивание тоже является выражением
    printf("new value of 'a' is %d\n",a = -1); //печатает: new value of 'a' is -1
    //выражения можно объединять в более сложные с помощью вызовов функций или операторов (арифметических, логических, побитовых и т.п.)

    /**
     * Внутри отдельного выражения операции могут быть переставлены для оптимизации.
     * Подобные действия возможны, если логически структура выражения не изменна.
     * Например в выражении a + 2*a + b - 2*a компилятор может преобразовать его в a + b, т.к. 2*a  и -2*a взаимоуничтожаются.
     */

    /**
     * В отличие от выражений утверждения выполняются строго слева направо и сверху вниз.
     * Утверждение отделяется в коде точкой с запятой (;).
     * В одном утверждении может оказться несколько выражений.
     */
    //Утверждение (statement) определяющее три переменных, каждая инициализируется своим выражением
    int a_sqr = a*a, b_sqr = b*b, c_sqr = c*c;
    //в вызове функции printf участвуют три выражения и сам вызов, все они составляют единый statement
    printf("double squares are %d %d %d\n",2*a_sqr,2*b_sqr,2*c_sqr);

    /**
     * При необходимости можно несколько утверждений выделить в блок кода.
     * Блок кода ограничивается фигурными скобками и может содержать внутренние переменные.
     */
    { //начало блока
        int inner_variable = 5;
        printf("inner_variable = %d\n",inner_variable);
    } //конец блока
    //переменные, определённые в блоке, видны только внутри блока, т.е. вне блока переменная inner_value не определена
    //printf("inner_variable = %d\n",inner_variable);//ошибка при компиляции, unknown variable inner_variable

    //однако переменные, определённые во внешнем блоке до блока, будут видны и внутри него
    {
        int another_inner_variable = a + b + c;//a b c известны, т.к. определены до блока во внешнем блоке
        //another_inner_variable = inner_variable; //ошибка, переменная inner_variable видна ТОЛЬКО в том блоке, где объявлена
    }

    //переменные с одинаковыми именами, но объявленные в разных блоках - разные переменные
    {
        int inner_variable = 3; //это совершенно новая переменная, которая не зависит от переменной, объявленной в строке 44
        printf("inner_variable = %d\n",inner_variable);
    }

    //внутри блока могут быть объявлены переменные с такими же именами, как и внешние переменные
    {
        int a = -1, b = -2, c = -3; //эти три переменные никак не связаны с переменными a b и с из строки 15
        //при обращении к переменным a, b или c в блоке будут использованы данные внутренних переменных из строки 64
        printf("a,b and c been declared inside the block, a = %d, b = %d, c = %d\n", a, b, c);
        //обратиться к внешним переменным со строки 15 невозможно!
        //это называется затенением (shadowing) переменных
        //не рекомендуется использовать без особой необходимости
    }

    //блоки могут быть многократно вложены друг в друга
    {
        int first_order_block = 1;
        printf("\t%d\n",first_order_block);
        {
            int second_order_block = 2;
            printf("\t\t%d\n",second_order_block);
            {
                int third_order_block = 3;
                printf("\t\t\t%d",third_order_block);
            }
        }
    }
    return 0;
}