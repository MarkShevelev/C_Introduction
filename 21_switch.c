/**
 * Иногда есть необходимость выполнить выбор не из двух вариантов,
 * а из нескольких. Например, если пользователь вводит номер 
 * варианта ответа и на каждый из этих вариантов нужно напечатать 
 * отдельный комментарий. В этой ситуации сложную структуру 
 * последовательных if () { } else { } конструкций можно заменить 
 * конструкцией switch.
 */

#include <stdio.h>
#include <stdbool.h>

int main() {
    /**
     * Пользователю задаётся вопрос: How many legs does cat have?
     * И несколько вариантов ответа, каждый из которых может быть 
     * выбран по номеру. Необходимо снабдить каждый выбранный ответ 
     * комментарием от программы.
     */

    //решаем последовательными if () { } else { } конструкциями
    if (false) //измените на true или 1, чтобы запустить этот блок кода
    {
        printf("How many legs does cat have?\n");
        printf("1) One leg\n");
        printf("2) Two legs\n");
        printf("3) Four paws\n");
        printf("4) There's no cat!\n");
        fflush(stdout);//это важно сделать прежде, чем запрашивать данные от пользователя

        int answ; //переменная, в которую мы положим ответ
        scanf("%d",&answ); //считываение числа с клавиатуры

        if (1 == answ) //комментарий на ответ 1
            printf("Poor cat with one leg...\n");
        else if (2 == answ) //такая конструкция допустима! т.к. if () { } else { } - это единый statement
            printf("The cat is not a human!\n");
        else if (3 == answ) //конструкция означает, что при неудаче в первом if мы переходим к следующему условию
            printf("That's it!\n");
        else if (4 == answ) //в некоторых языках есть даже специальная конструкция elseif, в C есть #elif для препроцессора
            printf("Wake up, Neo!\n");
        else //завершающий else не имеет последующего условия, оно выполнится, если не одно предыдущее условния не сработало
            //это позолит отследить ситуацию, когда пользователь выбрал несуществующий вариант
            printf("No such choice %d\n", answ);
    }

    /**
     * При использовании "лесенки" if / else мы написали много повторяющегося кода - сравнения с константами.
     * Именно это можно упростить при использовании switch.
     */

    //решаем через switch
    if (false) //измените на true или 1, чтобы запустить этот блок кода
    {
        //эта часть не меняется
        printf("How many legs does cat have?\n");
        printf("1) One leg\n");
        printf("2) Two legs\n");
        printf("3) Four paws\n");
        printf("4) There's no cat!\n");
        fflush(stdout);

        int answ; 
        scanf("%d",&answ);

        switch(answ) { //switch открывает блок кода, в круглых скобках указыавется выражение или переменная, которые нужно сравнить с константами
        case 1: //каждое сравнение предваряется словом case и указанием литеральной константы для сравнения, переменные не допускаются!
            printf("Poor cat with one leg...\n");            
            break; //break немедленно прекращает работу switch и выбрасывает за пределы блока кода

        case 2: //программа последовательно сравнивает значения констант с переменной в заголовке блока switch
            printf("The cat is not a human!\n");
            break;

        case 3: //если совпадение найдено, то программа переходит к исполнению этой части блока
            printf("That's it!\n"); 
            break;

        case 4:
            printf("Wake up, Neo!\n");
            break;
        
        default: //если ни один case не сработал, то исполнение переходит к default
            printf("No such choice %d\n", answ);
        }
    }

    /**
     * Важным свойством switch является свойство fall-through или провал
     * Такая ситуация возникает, когда case не заканчивается break.
     * Если это происходит, то исполнение не останавливается, продолжается дальше.
     */
    if (false) //измените на true или 1, чтобы запустить этот блок кода
    {
        //в зависимости от того какое число будет введено, столько раз напечатается слово Fallthrough
        printf("Fall-through test\n");
        fflush(stdout);

        int answ;
        scanf("%d",&answ);

        switch (answ) {
            case 4:
                printf("Fallthrough\n");
            case 3:
                printf("Fallthrough\n");
            case 2:
                printf("Fallthrough\n");
            case 1:
                printf("Fallthrough\n");
        } //случай default может отсутствовать
    }

    if (false) //измените на true или 1, чтобы запустить этот блок кода
    {
        /**
         * Рассмотрим такую задачу:
         * пользователь вводит номер месяца от 1 до 12 (январь, февраль, март и т.д.),
         * программа в ответ печатает какое количество дней прошло с начала года (в феврале 28 дней).
         */

        printf("Please, enter the month number 1 -- 12: ");
        fflush(stdout);

        int month;
        scanf("%d",&month);

        int days_passed = 0;
        switch(month) {
            case 12: days_passed += 31; //каждый раз переходя к следующему case, программа прибавляет кол-во дней в прошедшем месяце
            case 11: days_passed += 30;
            case 10: days_passed += 31;
            case 9: days_passed += 30;
            case 8: days_passed += 31;
            case 7: days_passed += 31;
            case 6: days_passed += 30;
            case 5: days_passed += 31; //если пользователь выбрал пятый месяц (май), то будут сложены все дни прошедших месяцев
            case 4: days_passed + 30;
            case 3: days_passed += 31;
            case 2: days_passed += 28;
            case 1: days_passed += 31;
            printf("From the begining of the year %d days passed!\n",days_passed);
            break;
            default:
                printf("No such month...\n");
        }
    }

    return 0;
}