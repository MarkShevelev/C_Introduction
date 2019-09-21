/**
 * Над целыми числами в языке C можно совершать арифметические операции + - * / и %.
 * Все эти операции возвращают в качестве результата целые числа!
 * Перечисленные арифметические операции не требуют никаких дополнительных заголовков.
 */

#include <stdio.h>
#include <limits.h>

int main() {
    //примеры простейших операций
    int a = 5, b = 4;
    printf("%d + %d = %d\n",a,b,a+b);  //сложение
    printf("%d - %d = %d\n",a,b,a-b);  //вычитание
    printf("%d * %d = %d\n",a,b,a*b);  //умножение
    printf("%d / %d = %d\n",a,b,a/b);  //целая часть от деления
    printf("%d %% %d = %d\n\n",a,b,a%b); //остаток от деления

    /**
     * обратите внимание, что 5 / 4 = 1, это целая часть от деления
     * 5 % 4 - это остаток от деления и 5 % 4 = 1
     * (a/b)*b НЕ равно a | 5 / 4 = 1 => (5/4)*4 = 4 
     * для деления действует правило: a = (a/b)*b + a%b
     */
    int div = a/b, res = a%b;
    printf("div = %d\nres = %d\ndiv*4 + res = %d\n\n",div,res,div*b + res);

    //не обязательно выделять отдельную операцию в промежуточный результат
    int expression_res = a*b + a/b;
    printf("a*b + a/b = %d\n\n",expression_res);

    /**
     * В случае большого выражения операции выполняются по приоритету,
     * т.е. сначала умножение и деление, а затем сложение и вычитание.
     * Операции одинакового приоритета выполняются слева направо.
     * Изменить порядок операций можно с помощью круглых скобок.
     */
    int complex_expression_a = a - b * a + b, complex_expression_b = (a - b) * (a + b), complex_expression_c = a * a - b * b;
    printf("a - b * a + b = %d\n",complex_expression_a);
    printf("(a - b) * (a + b) = %d\n",complex_expression_b);
    printf("a * a - b * b = %d\n\n",complex_expression_c);
    
    /**
     * При работе с целыми числами возможны переполнения,
     * т.е. выход за границы максимального и минимального значений.
     * Однако такая ситуация не будет ошибкой при работе программы,
     * получится новое число из диапазона типа.
     */
    int next_max = INT_MAX + 1;
    printf("max = %d\nnext_max = %d\n\n",INT_MAX,next_max);
    /**
     * Из-за особенностей задания отрицательных чисел,
     * на большинстве платформ мы получим большое отрицательное число.
     */

    unsigned next_umax = UINT_MAX + 1u;
    printf("max = %u\nnext_max = %u\n\n", UINT_MAX, next_umax);
    /**
     * В случае с беззнаковым числом мы получаем ноль.
     */

    /**
     * Помните! В переменную сохраняется вычисленное выражение,
     * в котором все переменные имеют текущие значения!
     * Нельзя сначала написать выражение, а затем дать значения переменным.
     * Значение в переменной не изменится после вычисления, если даже 
     * изменятся значения переменных, входивших в выражение!
    */
    int var1, var2; //переменные содержат неопределённое значение!
    int bad_expression_var = var1 + var2; //bad_expression содержит неопределённое значение!
    printf("bad expression! var1 + var2 = %d\n",bad_expression_var);
    var1 = 0; var2 = 1; //теперь значения var1 и var2 определены, но bad_expression по-прежнему неверное!
    printf("var1 = %d and var2 = %d\n",var1,var2);
    printf("expression is still bad! %d\n",bad_expression_var);
    bad_expression_var = var1 + var2; //здесь выражение будет пересчитано с новыми значениями var1 и var2
    printf("now expression is good! %d\n",bad_expression_var);
    var1 = -1; var2 = -2; //эти действия не повлияют на выражение bad_expression_var
    printf("var1 = %d and var2 = %d\n",var1,var2);
    printf("expression is the same! %d\n\n",bad_expression_var);

    return 0;
}
