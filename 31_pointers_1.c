/**
 * Существует определённый ряд задач, которые 
 * требуют опосредованного доступа в память. 
 * Например, задача обмена значениями между 
 * двумя переменными. Кроме того, для создания 
 * ссылочных структур данных необходим механизм 
 * хранения не самих данных, а их расположения.
 * Все эти задачи решаются в языке C с помощью
 * указателей.
 */

#include <stdio.h>
#include <stdbool.h>

/**
 * Рассмотрим задачу обмена значениями между 
 * двумя переменными. Мы бы могли решить её 
 * в основной функции main.
 */

/* данный код можно запустить для проверки в основной функции main ниже[<65;11;9M
int main() {
    int a = 3, b = 5;
    printf("a = %d; b = %d;\n",a,b);
    {
        int tmp = a;
        a = b;
        b = tmp;
    } //простейший алгоритм обмена через третье, временное значение    
    printf("a = %d; b = %d;\n",a,b);

    return 0;
}
*/

/**
 * Если перестановка данных встречается в коде часто, 
 * например, мы хотим написать несколько сортировок,
 * работающих по принципу compare-and-swap, то хотелось 
 * бы иметь функцию для выполнения обмена.
 * Однако наивный вариант такой функции не будет работать
 */

void naive_swap(int a, int b) {
    int tmp = a;
    a = b;
    b = tmp;
}

/**
 * Проблема состоит в том, что функция меняет значения в 
 * той памяти, которая выделена ей. Переменные a и b не 
 * имеют прямого отношения к той памяти, которая выделена в 
 * основной функции main. Входящие параметры функции 
 * хранят копии данных из main. 
 */

/**
 * Специальная функция via_pointer_swap позволяет двум 
 * переменным типа int обменяться значениями опосредовано, т.е.
 * будет перезаписана память не принадлежащая самой функции.
 */
void via_pointer_swap(int *a_ptr, int *b_ptr) {
    int tmp = *a_ptr; //читаем данные, которые хранятся по адресу a_ptr
    *a_ptr = *b_ptr; //записываем в память по адресу a_ptr данные из памяти по адресу b_ptr
    *b_ptr = tmp; //изменяем данные по адресу b_ptr
}

int main() {
    if (false) //прямой обмен в той же функции, где и объявлены переменные
    {
        int a = 3, b = 5;
        printf("a = %d; b = %d;\n",a,b);
        {
            int tmp = a;
            a = b;
            b = tmp;
        } //простейший алгоритм обмена через третье, временное значение    
        printf("a = %d; b = %d;\n",a,b);
    }

    if (false) //безуспешная попытка обменять значения функцией naive_swap
    {
        int a = 3, b = 5;
        printf("a = %d; b = %d;\n",a,b);
        naive_swap(a,b);
        printf("a = %d; b = %d;\n",a,b);
    }

    /**
     * Для решения проблемы, возникшей выше, в языке C можно 
     * использовать указатели! Указатели - это специальный тип 
     * данных, который позволяет сохранять не сами данные, а их 
     * адреса - положение в памяти.
     * Каждый байт в оперативной памяти (Random Access Memory) 
     * имеет свой уникальный номер. Указатель позволяет нам 
     * сохранить такой номер.
     */
    if (false) //взятие адреса
    {
        //специальная операция & позволяет нам получить номер ячейки памяти, где хранится значение
        int a = 3;
        printf("a: %d -->> %p\n",a,&a); //&a - взятие адреса, для вывода адреса используется заместитель %p

        //различные переменные имеют различные адреса
        int b = 3;
        printf("b: %d -->> %p\n",b,&b);
        /**
         * Если запустить этот фрагмент кода несколько раз, то
         * можно заменить, что результат вывода операции взятия адреса
         * всегда разный. Это связано с тем, что Операционная Система 
         * размещает нашу программу в различных местах в оперативной 
         * памяти, оптимизируя ресурсы. Даже если этого не происходит 
         * для нашей маленькой программы, никогда не стоит полагаться
         * на то, что адрес переменной равен чему-либо конкретному!
         */
    }

    if (false) //указатель - переменная для сохранения адреса
    {
        //адрес можно сохранить в специальной переменной - указателе
        int *pointer; //при объявление символ '*' возле имени переменной означает, что переменная хранит адрес
        int a = 3; //а это обычная переменная, которая хранит целое число
        pointer = &a; //сохраняем в pointer адрес переменной а

        int* another_pointer; //это тоже верное объявление указателя
        int*next_ptr; //и это
        int * more_ptr; //и это тоже =) положение символа '*' не имеет значения

        /**
         * Сложность может представлять объявление нескольких переменных
         * типа указатели в одной строке.
         */

        int* a_ptr, b, *c_ptr, c;
        /**
         * a_ptr - это указатель
         * b - просто целое число
         * c_ptr - тоже указатель
         * c - снова целое число
         * Указателем будет только та переменная, для которой в 
         * момент объявления между типом и именем (идентификатором)
         * стоит символ '*'!
         */
    }

    /**
     * Зачем указывать int слева от '*' и может ли там стоять 
     * другой тип, например float?
     * Да, может.
     * Тип, скоторым связан указатель необходим для операции 
     * разыменования - получения значения по адресу.
     */
    if (false)
    {
        /**
         * Указатели не представляли бы из себя ничего интересного,
         * если зная адреса данных, мы бы не смогли узнать или изменить 
         * эти данные. Для того, чтобы получить доступ к данным, нужно
         * указатель разыменовать.
         */
        int a = 3;
        int *a_ptr = &a;
        printf("a = %d\n",*a_ptr); //чтобы получить доступ к данным, хранящимся по адресу, необходимо поставить символ '*' перед именем указателя

        //используя указатель можно не только прочесть, но и изменить данные
        *a_ptr = 5;
        printf("a = %d\n",a); //значение переменной а изменится, хотя операция деструктивного присваивания над a не производилась!
        //использование адреса для изменения и чтения данных и есть опосредованный, косвенный доступ к данным
    }

    /**
     * Так как чтение данных связано с их интерпретацией, то компилятору
     * необходимо знать сколько байт прочесть и как именно их расшифровать.
     * Будут ли это данные целые или число с плавающей точкой, а может быть 
     * просто символ? На этот вопрос и отвечает тип данных, указанный слева
     * от символа '*'.
     */
    if (false) //указатели различных типов
    {
        float *f_ptr;
        int *i_ptr;
        int i = 3;
        float f = 3.f;

        /**
         * Если мы произведём неверное присваивание между данными 
         * и указателем на данные, то компилятор нас предупредит.
         */
        i_ptr = &i; //всё отлично, типы указателя и данных совпадают
        f_ptr = &f; //здесь типы тоже совпадают
        //i_ptr = &f; //здесь проблема: assignmet to int* from incompatible pointer type float*
        //f_ptr = &i; //и здесь типы не совпадают
        //f_ptr = i_ptr; //также не следует присваивать указатели разных типов друг другу
        /**
         * Хотя типы указателей и разные, int и float, но хранят 
         * эти переменные одинаковые по сути данные - адреса.
         * Это выражается ещё и в том, что размер указателя как 
         * переменной в байтах не зависит от связанного типа.
         */
        char ch = 'a'; //символ, размер 1 байт
        char *ch_ptr = &ch; //указатель, размер 4 или 8 байт
        printf("sizeof(char) = %u\nsizeof(char*) = %u\nsizeof(int) = %u\nsizeof(int*) = %u\nsizeof(double) = %u\nsizeof(double*) = %u\n",sizeof(char),sizeof(char*),sizeof(int),sizeof(int*),sizeof(double),sizeof(double*));
    }

    /**
     * Связанный тип нужен указателю, чтобы верно интерпретировать 
     * данные, которые хранятся в памяти. Связанный тип не влияет
     * на количество байт, которые указатель занимает в памяти как 
     * переменная.
     */

    /**
     * Теперь мы понимаем, как работает функция via_pointer_swap!
     * Она принимает пару адресов, читает данные по этим адресам и 
     * косвенно перезаписывает память, которая не принадлежит самой 
     * функции via_pointer_swap. Такие функции мы называем - функции 
     * с побочными эффектами.
     * Посмотрим, как правильно вызвать функцию via_pointer_swap.
     */
    if (false)
    {
        int a = 3, b = 5;
        printf("a = %d; b = %d;\n",a,b);
        via_pointer_swap(&a,&b);//мы не можем передать сами переменные, нужны их адреса, адреса можно получить оператором '&'
        printf("a = %d; b = %d;\n",a,b);
    }

}

