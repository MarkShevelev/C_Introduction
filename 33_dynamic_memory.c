/**
 * Статическая и автоматическая память обладают тем недостатком,
 * что количество байт памяти, необходимое для решения задачи 
 * должно быть известно заранее.
 * Для некоторых задач сложно оценить заранее количество необходимой 
 * памяти. Например, если бы мы хотели сохранить все значения 
 * "Сиракузской последовательности" для некоторого начального 
 * числа, то это оказалось бы затруднительно...
 * В подобной ситуации либо следует ограничить работу программы 
 * некоторым заранее заданным, априорно известным количеством 
 * памяти, либо использовать специальный механизм выделения 
 * памяти во время работы программы - динамическое выделение памяти.
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> //malloc calloc realloc free - функции для работы с динамическим выделением памяти

/**
 * Наиболее очевидная ситуация, когда динамическая память 
 * необходима - это задача, в которой сложно (почти невозможно) 
 * рассчитать заранее количество необходимой памяти.
 *
 * Рассмотрим задачу.
 * Пользователь вводит в консоль числа. Как только пользователь 
 * вводит ноль, программа прекращает запрашивать числа далее и 
 * выводит данные пользователя в обратном порядке.
 */

//лекго написать программу, которая выполняет поставленную задачу для фиксированного количества запросов, скажем, не более 100
void ask_no_more_than_100() {
    int arr[100];
    int count = 0;
    int user_input;
    do {
        if (1 != scanf("%d",&user_input)) {
            printf("Can't read next value from input\n");
            break; //специальное ключевое слово для мгновенного прерывания цикла
        }

        if (100 == count) {
            printf("Can't save next value to the array\n");
            break;
        }

        if (user_input != 0)
            arr[count++] = user_input;
    } while (0 != user_input);

    for (unsigned idx = 100 - count + 1; idx != 101; ++idx)
        printf("%d ",arr[100 - idx]);
    printf("\n");
}

/**
 * Наивная попытка занять автоматический массив большего размера 
 * в случае, когда изначальный массив исчерпан, не будет рабочей, 
 * т.к. автоматический массив будет немедленно переиспользован, 
 * как только завершится блок кода, в котором он выделен.
 */

/**
 * Динамически выделенная память не переиспользуется до тех пор, 
 * пока программа сама не укажет, что память ей больше не требуется.
 * Потому каждый фрагмент динамически выделенной памяти следует 
 * явно возвращать системе.
 * Рассмотрим простейший пример выделения и возвращения динамической 
 * памяти.
 */
void simple_dynamic_memory_example() {
    int *var = malloc(4); //функция malloc запрашивает у системы указанное число байт

    *var = 5;             //динамически выделенная память не имеет связанного имени, в отличие переменной, а является набором последовательных адресов
                          //потому для обращения к динамически выделенной памяти необходимо использовать указатель, который сохранит начальный адрес выделенного фрагмента
    printf("%d\n",*var); //мы можем писать и читать данные в динамически выделенной памяти посредством косвенного доступа, операции разыменования

    free(var); //выделенная динамически память обязательно должна быть освобождена
}

/**
 * При динамическом выделении памяти мы получаем не новые переменные, 
 * а набор подряд идущих адресов, которые эксклюзивно выданы нашей 
 * программе. Другая программа не может ни читать, ни писать 
 * в эти адреса.
 * Без уменя работать с указателями не обойтись при работае с 
 * динамически выделенной памятью!
 */

/**
 * При работе с динамической памятью следует быть аккуратным.
 * Так же как и чтение неинициализированной переменной, 
 * попытка получить данные из только что выделенной памяти
 * приводит к неопределённому поведению!
 * Всегда сначала заполняйте память данными!
 * Один из способов получить уже инициализированную память - 
 * это использование вызова calloc, который заполняет все байты 
 * памяти нулями.
 */

void clean_memory_allocation() {
    int *var = calloc(1,4); //первый параметр указывает кол-во элементов, а второй - размер одного элемента в байтах, аналогично вызову malloc(1*4)

    printf("%d\n",*var); //безопасно, мы увидим значение 0

    free(var); //как и для malloc, нам следует вернуть память системе явно
}

/**
 * malloc и calloc выделяют память в виде строго подряд идущих байтов.
 * Подобная организация памяти характерная для массивов.
 * Используя эквивалентность синтаксиса ptr[i] <=> *(ptr + i) <=>i[ptr],
 * мы можем работать с указателем на начало динамически выделенной 
 * памяти, как с обычным массивом. Но для этого нам потребуется выделить
 * память не под один элемент данных, а под несколько. Например, если 
 * мы хотим выделить память под 10 элементов типа int, то нам потребуется 
 * 10*4 = 40 байт, по 4 байта на каждый из 10 элементов типа int.
 * В общем случае для массива из 'N' элементов нам потребуется 
 * N*sizeof(<название типа данных>) байт.
 */

void array_dynamic_allocation() {
    //выделяем память под 10 элементов типа double с использованием malloc
    double *d_arr1 = malloc(10*sizeof(double));
    for (unsigned idx = 0; idx != 10; ++idx) //malloc не инициализирует память, её нужно заполнить самостоятельно значениями
        d_arr1[idx] = 1.; //обращение к памяти можно осуществлять как к обычному массиву за счёт специального синтаксиса ptr[i] <=> *(ptr + i)
    for (unsigned idx = 0; idx != 10; ++idx)
        printf("%f ",d_arr1[idx]);
    printf("\n");
    free(d_arr1);

    double *d_arr2 = calloc(10,sizeof(double)); //calloc ожидает два параметра: кол-во элементов и размер одного элемента
    for (unsigned idx = 0; idx != 10; ++idx) //calloc заполняет память нулями, её можно причитать, результат будет предсказуем
        printf("%e ",d_arr2[idx]);
    printf("\n");
    free(d_arr2);
}

/**
 * Теперь мы располагаем необходимыми навыками, чтобы решить изначальную
 * задачу: сохранение произвольного, не известного заранее количества чисел.
 */

void ask_with_dynamic_allocation() {
    int *arr = malloc(10*sizeof(int));
    int count = 0, size = 10; //нам потребуется ещё одна переменная, которая будет хранить полное количество элементов в массиве - size
    int user_input;
    do {
        if (1 != scanf("%d",&user_input)) {
            printf("Can't read next value from input\n");
            break; //специальное ключевое слово для мгновенного прерывания цикла
        }

        if (size == count) {
            //printf("Can't save next value to the array\n");
            //break;
            /**
             * При заполнении массива мы будем выделять новую память 
             * динамически. К ней мы будем иметь доступ даже после 
             * завершения блока кода
             */
            int *tmp = malloc(2*size*sizeof(int)); //выделяем новую память вдвое больше прежней!
            for (unsigned idx = 0; idx != count; ++idx)
                tmp[idx] = arr[idx]; //в новую память необходимо перекопировать уже имеющиеся данные
            int *ptr = tmp;
            tmp = arr;
            arr = ptr;
            //поменяли местами данные в указателях tmp и arr, теперь arr указывает на новую память, а tmp - на старую
            free(tmp); //старую память нужно вернуть системе, мы больше не будем её использовать
            size *= 2; //не забываем, что size увеличился вдвое!
            printf("New memory allocated!\n"); fflush(stdout); //тестовое сообщение
        }

        if (user_input != 0)
            arr[count++] = user_input;
    } while (0 != user_input);

    for (unsigned idx = size - count + 1; idx != size+1; ++idx)
        printf("%d ",arr[size - idx]);
    printf("\n");
}


int main() {
    //запрос данных от пользователь при конечном объёме памяти, известном заранее
    if (false) ask_no_more_than_100();
    if (false) clean_memory_allocation();
    if (false) array_dynamic_allocation();
    if (true) ask_with_dynamic_allocation();

    return 0;
}
