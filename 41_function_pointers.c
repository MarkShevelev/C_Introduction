#include <stdio.h>
#include <stdbool.h>

/**
 * Указатели на функции весьма эффективны для повышения гибкости кода.
 * Познакомимся подробнее с тем, как их объявлять и использовать.
 * */

void f() {
    printf("Hello function pointer!\n");
}

void h() {
    printf("Another function called!\n");
}

void print_int(int i) {
    printf("%d ",i);
}

void print_double(double d) {
    printf("%f ", d);
}

void function_pointer_declaration() {
    /**
     * Для того чтобы вызвать функцию, нужно знать где находится её код, 
     * какие у неё входящие и исходящие параметры.
     * Адрес функции выражается непосредственно именем 
     * переменной, входящие и исходящие параметры - связанные с указателем свойства,
     * они указываются справа и слева от имени, соответственно.
     * */

    void (*f_ptr) (void); //объявление указателя на функцию, которая ничего не принимает и ничего не возвращает
    f_ptr = f; //присваиваем указателю f_ptr адрес функции f
    f_ptr(); //вызываем функцию, которая расположена по адресу f_ptr
    (*f_ptr)(); //обе записи вызова верны: и без явного разыменования, и с явным разыменованием

    /**
     * Как и обычные переменные, указатели на функции можно инициализировать,
     * т.е. давать им значения прямо при объявлении.
     * */

    void (*g_ptr) (void) = f; //объявляем и инициализируем указатель на функцию g_ptr
    g_ptr();
    //обратите внимание, что у нас есть два указателя на одну и ту же функцию, это не запрещено, так же как и два указателя на одну переменную

    void (*const e_ptr) (void) = f; //указатели на функции могут быть неизменяемыми
    e_ptr(); //неизменяемые указатели можно использовать для вызова функций и необходимо инициализировать
    //e_ptr = h; //но нельзя изменить посредством деструктивного присваивания!
    g_ptr = h;
    g_ptr();

    //как и обычные указатели, указатели на функции нельзя разыменовывать, если они не инициализированы, не связаны с функцией!!!
    void (*danger_ptr)(void);
    //danger_ptr(); //неопределённое поведение!!! undefined behavior

    /**
     * Указатель на функцию должен быть присвоен только такой функции, 
     * которая совпадает с ним по набору входящих и исходящих параметров.
     * Иначе возникнет неопределённое поведение из-за ошибок снятия и 
     * добавления данных на стек.
     * */
    //danger_ptr = print_int; //warning или error
    //danger_ptr(); //UB, если предыдущая строка прошла компиляцию
}

void function_pointers_aliases() {
    /**
     * Если требуется определить несколько указателей на функции с общей сигнатурой, 
     * то это может оказаться затратно, хотя код будет выглядить чрезвычайно похожим.
     * */

    void (*f_ptr) (void) = f;
    void (*g_ptr) (void) = f;
    void (*h_ptr) (void) = f;

    /** 
     * Повысить удобочитаемость кода можно с помощью ключевого слова typedef, 
     * которое мы уже использовали со структурами.
     * */
    typedef void (*action_t) (void);
    /**
     * Строкой выше мы создали специальный псевдоним для типа 
     * указатель на функцию, не возвращающую и не принимающую данных.
     * */

    action_t f_act = f, g_act = f, h_act = f; //доступно даже объявление нескольких указателей в одной строке!!!
    f_act();
    g_act();
    h_act();

    /**
     * Переименование типов указателей на функции можно делать как внутри других функций, 
     * так и в глобальном пространстве.
     * */
}


/**
 * Массивы указателей на функции.
 * */

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

/**
 * Предположим, что нам нужно выбирать в зависимости от введённого пользователем 
 * числа операцию над двумя целыми числами.
 * Мы бы могли это сделать через switch, например.
 * */
void switch_choose_operation() {
    
    int a , b;
    printf("Please enter two integer numbers:"); fflush(stdout);
    scanf("%d%d", &a, &b);

    int user_input;
    printf("Please, enter operation:\n1) summation\n2) subtraction\n3) multiplication\n4) division\n"); fflush(stdout);
    scanf("%d",&user_input);

    int res = 0;
    switch(user_input) {
        case 1:
            res = sum(a,b);
            break;
        case 2:
            res = sub(a,b);
            break;
        case 3:
            res = mul(a,b);
            break;
        case 4:
            res = divv(a,b);
            break;
        default:
            printf("Unknown command!\n");
    }
        
    printf("res = %d\n",res);
}

/**
 * Код выше содержит множество повторяющихся фрагментов.
 * По существу, мы выполнили простой перебор вариантов.
 * Мы бы могли выполнить его более компактным кодом, 
 * если бы у нас был массив из операций, каждый элемент 
 * которого представлял бы собой нужную функцию.
 * С указателями на функции это несложно сделать. 
 * */

void function_pointers_choose_operation() {
    typedef int (*operation_t) (int,int); //объявим новое имя для типа 'указатель на функцию, принимающую два инта и возвращающую один инт'
    operation_t ops[4]; //объявляем массив из 4-х указателей на функции операций
    ops[0] = sum;
    ops[1] = sub;
    ops[2] = mul;
    ops[3] = divv;
    //присваиваем адреса операций элементам массива

    //данная часть кода получает данные от пользователя аналогично предыдущему 
    int a , b;
    printf("Please enter two integer numbers:"); fflush(stdout);
    scanf("%d%d", &a, &b);

    int user_input;
    printf("Please, enter operation:\n1) summation\n2) subtraction\n3) multiplication\n4) division\n"); fflush(stdout);
    scanf("%d",&user_input);

    if (1 > user_input || 4 < user_input) //если введено неверное число, то сообщаем об ошибке
        printf("Unknown operation\n");
    else
        printf("res = %d\n",ops[user_input-1](a,b)); //если число верное, то просто вызываем операцию из набора по номеру
}

/**
 * Указатели на функции могут быть параметрами других функций, 
 * что повышает гибкость кода.
 * Например, если нам надо заполнить массив случайными числами, 
 * то мы бы написали следующий код:
 * */
#include <stdlib.h> //srand rand
void random_int_array(int *arr, unsigned size) {
    for (unsigned idx = 0; idx != size; ++idx)
        arr[idx] = rand();
}

void random_int_array_testA() {
    int arr[10];
    srand(10);
    random_int_array(arr,10);
    for (unsigned idx = 0; idx != 10; ++idx) {
        printf("%d ",arr[idx]);
    }
    printf("\n");
} 

/**
 * При таком подходе нам потребуется создавать множество 
 * разных функций, которые заполняют массив.
 * Например, если нам потребуется заполнить массив единицами, 
 * то мы напишем:
 * */
void unit_int_array(int *arr, unsigned size) {
    for (unsigned idx = 0; idx != size; ++idx)
        arr[idx] = 1;
}

/**
 * Большая часть кода функций random_int_array и unit_int_array повторяется.
 * Изменяется только небольшая деталь - вызываемая для каждого элемента функций.
 * Если мы сделаем эту функцию параметром, то сможем написать универсальный 
 * алгоритм заполнения.
 * */
void universal_int_array_generator(int *arr, unsigned size, int (*generator)(void)) {
    /**
     * Последний параметр этой функции - указатель generator, который 
     * хранит адрес некой функции, генерирующей целые числа.
    */
    for (unsigned idx = 0; idx != size; ++idx)
        arr[idx] = generator(); //вызываем функцию по адресу
}

void random_int_array_testB() {
    int arr[10];
    srand(10);
    universal_int_array_generator(arr,10,rand); //обратите внимание, что мы указываем имя функции без круглых скобок!!! Скобки обозначают вызов, а мы хотим получить адрес, а не вызвать функцию.
    for (unsigned idx = 0; idx != 10; ++idx) {
        printf("%d ",arr[idx]);
    }
    printf("\n");
}
/**
 * Работа с функцией universal_int_array_generator не сложнее, чем с функцией random_int_array.
 * Но теперь эта функций достаточно гибкая, чтобы её можно было использовать для 
 * заполнения массива единицами не переписывая код функции universal_int_array_generator полностью.
 * Достаточно написать 'деталь' - небольшую функцию, которая будет возвращать единицу.
 * */
int unit_int() { //простая функция, которая возвращает единицу
    return 1;
}

void unit_int_array_test() {
    int arr[10];
    srand(10);
    universal_int_array_generator(arr,10,unit_int);
    for (unsigned idx = 0; idx != 10; ++idx) {
        printf("%d ",arr[idx]);
    }
    printf("\n");
}

/**
 * Печать массива также может быть представлена универсальным алгоритмом.
 * Печать массива есть печать всех его элементов.
 * Т.е. к каждому элементу массива применяется функция печати.
 * Давайте напишем такой алгоритм, где применяемая функция будет параметром.
 * */
void for_each(int *arr, unsigned size, void (*action)(int)) {
    for (unsigned idx = 0; idx != size; ++idx)
        action(arr[idx]);
}

/**
 * Заполняем массив случайными числами и печатаем его.
 * */
void for_each_int_array_test() {
    int arr[10];
    srand(10);
    universal_int_array_generator(arr,10,rand);
    for_each(arr,10,print_int);
}

/**
 * Ещё один важный пример алгоритма, который может быть параметризован функцией - 
 * это алгоритм сортировки.
 * Если мы напишем пузырьковую сортировку, то она будет работать только для 
 * того типа данных, который мы определим в качестве элемента массива.
 * */
void int_swap(int *a_ptr, int *b_ptr) {
    int tmp = *a_ptr;
    *a_ptr = *b_ptr;
    *b_ptr = tmp;
}

void int_bubble_sort(int *arr, unsigned size) {
    for (unsigned count = 0; count != size-1; ++count)
        for (unsigned idx = 0; idx != size-1-count; ++idx)
            if (arr[idx] > arr[idx+1])
                int_swap(arr+idx,arr+idx+1);
}

void double_swap(double *a_ptr, double *b_ptr) {
    double tmp = *a_ptr;
    *a_ptr = *b_ptr;
    *b_ptr = tmp;
}

void double_bubble_sort(double *arr, unsigned size) {
    for (unsigned count = 0; count != size-1; ++count)
        for (unsigned idx = 0; idx != size-1-count; ++idx)
            if (arr[idx] > arr[idx+1])
                double_swap(arr+idx,arr+idx+1);
}

/**
 * Функции int_bubble_sort и double_bubble_sort ничем не отличаются, 
 * кроме входящих параметров и вызова функции _swap.
 * Последний может быть сделан универсальным.
 * */
void uniswap(void *a_ptr, void *b_ptr, unsigned byte_size) {
    //a_ptr - адрес первого элемента
    //b_ptr - адрес второго элемента
    //byte_size - количество байт в элементе
    unsigned char *a_char = a_ptr, *b_char = b_ptr;
    for (unsigned count = 0; count != byte_size; ++count) {
        unsigned char tmp = *(a_char + count);
        *(a_char + count) = *(b_char + count);
        *(b_char + count) = tmp;
    }
}

/**
 * Даже если мы передадим дополнительный параметр, 
 * отражающий количество байт в элементе массива, 
 * то мы не сможем избавиться от типа параметре в 
 * объявлении функции, т.е. сравниваем элементы через 
 * операцию >.
 * Давайте напишем такую операцию сравнения, 
 * которая бы, наподобие uniswap, имела бы сигнатуру, 
 * не зависящую от типа данных. 
 * */

bool int_greater_than(void const *a_ptr, void const *b_ptr) {
    int const *a_int_ptr = a_ptr, *b_int_ptr = b_ptr;
    //мы ожидаем, что в такую функцию передадут пару адресов на int, хотя сигнатура никак не указывает на тип, кроме названия
    return *a_int_ptr > *b_int_ptr;
}

bool double_greater_than(void const *a_ptr, void const *b_ptr) {
    double const *a_double_ptr = a_ptr, *b_double_ptr = b_ptr;
    //мы ожидаем, что в такую функцию передадут пару адресов на int, хотя сигнатура никак не указывает на тип, кроме названия
    return *a_double_ptr > *b_double_ptr;
}

/**
 * Когда у нас есть две функции сравнения с одинаковой сигнатурой, 
 * мы можем передавать их в качестве параметра в основной алгоритм 
 * сортировки.
 * Давайте перепишем наш алгоритм в универсальный вид.
 * */
void universal_bubble_sort(void *arr, unsigned element_size, unsigned element_count, bool (*greater_than) (void const*, void const*)) {
    /**
     * Чтобы вызывать функцию сравнения, нам необходимо передавать адреса элементов.
     * Так как мы теперь не знаем, какие именно это элементы, то нам необходимо знать 
     * не только их количество, но и размер в байтах, чтобы правильно сдвигать адреса.
     * Размер элемента также необходим для вызова универсального обмена.
     */
    unsigned char *arr_char = arr; //мы не можем сдвигать указатель без связанного типа, потому создаём указатель на элемент размером в один байт
    for (unsigned count = 0; count != element_count-1; ++count) //этот цикл повторяет обход массива заданное число раз - столько, сколько в массиве элементов
        for (unsigned idx = 0; idx != element_count-1-count; ++idx) //этот цикл обходим элементы массива
            if (greater_than(arr_char + idx * element_size, arr_char + (idx + 1) * element_size) ) //мы не можем разыменовать адреса, мы должны вычислить адреса текущих элементов и передать их в функцию greater_than, она лучше знает :)
                uniswap(arr_char + idx * element_size, arr_char + (idx + 1) * element_size, element_size);

}

void universal_bubble_sort_test() {
    int arri[5] = {2, 3, 4, 1, -4};
    double arrd[5] = {2.1, 2.3, -1.2, 0., 5.};
    universal_bubble_sort(arri,sizeof(int),5,int_greater_than);
    for_each(arri,5,print_int);
    printf("\n");

    universal_bubble_sort(arrd,sizeof(double),5,double_greater_than);
    for (unsigned idx = 0; idx != 5; ++idx) 
        print_double(arrd[idx]);
    printf("\n");
}



int main() {
    if (false) function_pointer_declaration();
    if (false) function_pointers_aliases();
    if (false) switch_choose_operation();
    if (false) function_pointers_choose_operation();
    if (false) random_int_array_testA();
    if (false) random_int_array_testB();
    if (false) unit_int_array_test();
    if (false) for_each_int_array_test();
    if (false) universal_bubble_sort_test();

}