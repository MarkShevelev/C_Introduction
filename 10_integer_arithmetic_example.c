#include <stdio.h>

/**
 * Задача #1
 * Одна морковка стоит 10 рублей 50 копеек
 * У зайца в наличии 100 рублей 5 копек
 * Какое максимальное количество морковок он может купить?
 * Сколько денег останется у зайца?
 * Дополнительно: напишите программу так, чтобы цену и количество наличных денег можно было легко изменить в одном месте.
 */
void rabbit() {
    //определим константы для исходных данных
    int const price_rub = 10, price_kop = 50;
    int const rabbit_rub = 100, rabbit_kop = 5;

    //количество денежных средств удобно перевести в копейки
    int price_in_kop = price_rub*100 + price_kop, rabbit_in_kop = rabbit_rub*100 + rabbit_kop;
    int carrots_count = rabbit_in_kop/price_in_kop; //очевидно, средства делить на цену - число единиц
    printf("Number of carrots is %d\n",carrots_count);

    //количество оставшихся копеек можно легко вычислить при помощи остатка от деления
    int residual_amount_in_kop = rabbit_in_kop%price_in_kop;
    //чтобы вычислить количество денежных средств в рублях и копейках, необходимо выделить целое число рублей целочисленным делением
    printf("Rabbit still has %d rub and %d kop\n\n",residual_amount_in_kop/100,residual_amount_in_kop%100);
}

/**
 * Задача #2
 * Расстояние от дуба Совы, эффективного менеджера, до дачи Филина Филипповича 286 км.
 * Шишкомобиль совы расходует 12 шишек на 100 км.
 * Сколько минимально необходимо заправить шишек в шишкомобиль, чтобы доехать от дуба до Филина?
 * Дополнительно: вычислите в целочисленной арифметике, не используя условных конструкций.
 */
void sova() {
    //определим константы для исходных данных
    int const distance = 286, rate = 12;
    int number_of_cones;

    /**
     * Если distance*rate делится на 100 нацело, то ответ можно было бы выразить как distance*rate/100.
     * Если distance*rate/100 не целое, то остаток означает, что необходимо добавить топлива, иначе не доедем.
     * Этот вопрос можно решить без условий, уменьшив на единицу число distance*rate и добавив недостающую шишку
     */
    number_of_cones = (distance*rate-1)/100 + 1;
    printf("number of cones is %d\n\n",number_of_cones);
}

#include <stdbool.h>
int main() {
    if (false) rabbit(); //это код для вызова кода задачи #1, поставить true вместо false
    if (false) sova(); //это код для вызова кода задачи #2
}