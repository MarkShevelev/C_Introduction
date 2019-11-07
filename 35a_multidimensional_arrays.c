/**
 * Используя многомерные автоматические массивы,
 * можно создавать только "выравненные" массивы.
 * Если возникает необходимость для каждого 
 * отдельного ряда выделить своё количество 
 * элементов, такой многомерный массив называется
 * "рваным". Создать его можно, используя 
 * механизм динамического выделения памяти.
 * Также необходимость динамического выделения 
 * памяти может возникнуть в случае, если 
 * не известно заранее сколько потребует 
 * памяти задача.
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 * Рассмотрим способы организации двумерного 
 * массива с помощью динамического выделения
 * памяти под каждый ряд в отдельности.
 */
void two_dimensional_dynamic_memory_array() {
    unsigned row_number = 5;
    unsigned *sizes = malloc(row_number * sizeof(unsigned)); //в этом массиве мы будем хранить кол-во элементов для каждого ряда
    int **arr_2d = malloc(row_number * sizeof(int*)); //в этом массиве мы будем хранить для каждого ряда адрес его начала
    /**
     * Два массива, sizes и arr_2d, можно назвать "индексными" 
     * в том смысле, что мы храним в этих массивах данные о 
     * рядах, как номера страниц в оглавлении книги.
     */
    //для каждого ряда мы выделим память индивидуальным вызовом malloc
    for (unsigned idx = 0; idx != row_number; ++idx) {
        sizes[idx] = idx + 1;
        arr_2d[idx] = malloc(sizes[idx] * sizeof(int));
    }

    /**
     * Теперь мы можем обращаться к выделенной памяти
     * посредством разыменования или квадратных скобок.
     */
    for (unsigned row_idx = 0; row_idx != row_number; ++row_idx)
        for (unsigned col_idx = 0; col_idx != sizes[row_idx]; ++col_idx) //для каждого ряда мы выбираем столько элементов, сколько указано в индексном массиве размеров
            arr_2d[row_idx][col_idx] = col_idx;

    for (unsigned row_idx = 0; row_idx != row_number; ++row_idx) {
        for (unsigned col_idx = 0; col_idx != sizes[row_idx]; ++col_idx)
            printf("%2d ",arr_2d[row_idx][col_idx]);
        printf("\n");
    }

    //освобождаем память, выделанную под элементы
    for (unsigned row_idx = 0; row_idx != row_number; ++row_idx)
        free(arr_2d[row_idx]); //помните! на каждый вызов malloc должен быть симметричный вызов free

    //освобождаем память под индексные массивы
    free(sizes);
    free(arr_2d);
}

/**
 * Такую же технику выделения памяти можно использовать и для 
 * создания выровненных массивов с использованием 
 * динамического выделения памяти.
 * Рассмотрим задачу.
 * Пользователь вводит с клавиатуры размер вектора и 
 * его компоненты. Программа вычисляет матрицу, полученную 
 * от перемножения транспонированного вектора на изначальный.
 * Если вектор имеет размерность N, то получается матрица 
 * размера N*N - это выровненный двумерный массив.
 */

void vec_product_matrix_example() {
    float *vector = NULL, **matrix = NULL;
    int user_input;
    printf("Please, enter the vector space dimension: ");
    fflush(stdout); //эта команда необходима, чтобы запрос данных не начался раньше вывода
    if( 1 != scanf("%d",&user_input) || 0 >= user_input) {
        printf("Wrong vector size!\n");
        goto End; //при ошибке переходим в конец функции
    }

    unsigned N = user_input;
    vector = malloc(N * sizeof(float));
    if (NULL == vector) {
        printf("Can't allocate memory for the vector data!\n");
        goto End;
    }

    /**
     * Теперь выделим память под матрицу N*N.
     * сначала выделим память под индексный массив адресов,
     * массив размеров не нужен, т.к. массив выровненный и 
     * все ряды имеют одинаковый размер - N.
     */
    matrix = malloc(N * sizeof(float*));
    if (NULL == matrix) {
        printf("Can't allocate memory for the index array float **matrix!\n");
        goto Clear; //при ошибке мы должны перейти к освобождению памяти, т.к. память под vector уже была выделена
    }
    for (unsigned idx = 0; idx != N; ++idx)
        matrix[idx] = NULL; //мы обеспечиваем безопасность чтения данных из matrix

    //затем выделяем память под оддельные ряды
    for (unsigned idx = 0; idx != N; ++idx)
        if( NULL == (matrix[idx] = malloc(N * sizeof(float)))) {
            printf("Can't allocate memory for the row number %u!\n",idx);
            goto Clear; //мы должны освободить всю успешно занятую память: vector, matrix и те ряды, для которых вызов ранее в цикле прошёл успешно
        }
    
    printf("Please, enter the components of the vector: "); fflush(stdout);
    for (unsigned idx = 0; idx != N; ++idx)
        scanf("%f", &vector[idx]); //строго говоря, здесь тоже необходима проверка

    for (unsigned y_idx = 0; y_idx != N; ++y_idx) //этот цикл перебирает ряды
        for (unsigned x_idx = 0; x_idx != N; ++x_idx)
            matrix[y_idx][x_idx] = vector[y_idx] * vector[x_idx]; //по правилу перемножения матриц

    //выводим результат на экран
    for (unsigned y_idx = 0; y_idx != N; ++y_idx) {
        for (unsigned x_idx = 0; x_idx != N; ++x_idx)
            printf("%6.3f ", matrix[y_idx][x_idx]);
        printf("\n"); 
    }

Clear:
    if (NULL != matrix) {
        for (unsigned idx = 0; idx != N; ++idx)
            if (NULL != matrix[idx]) free(matrix[idx]);
        if (NULL != matrix) free(matrix);
    }
    if (NULL != vector) free(vector);
End:
    return;
}

/**
 * Выделение памяти в случае многомерных динамических массивов
 * предложенным выше способом соряжено с рядом проблем:
 * i) техническая сложность кода - много вызовов malloc и free, сложная структура кода при ошибках
 * ii) требуется большое количество вызовов malloc, каждый из которых может быть неудачным
 * iii) память выделяется "где попало", это может привести к сложностям при попытке обойти все данные
 * Решение - использовать выделение памяти одним вызовом
 * сразу под все элементы массива!
 */
void continuous_two_dimensional_array() {
    float *vector = NULL, **matrix = NULL, *matrix_data;
    int user_input;
    printf("Please, enter the vector space dimension: ");
    fflush(stdout); //эта команда необходима, чтобы запрос данных не начался раньше вывода
    if( 1 != scanf("%d",&user_input) || 0 >= user_input) {
        printf("Wrong vector size!\n");
        goto End; //при ошибке переходим в конец функции
    }

    unsigned N = user_input;
        if (NULL == (vector = malloc(N * sizeof(float)))) {
        printf("Can't allocate memory for the vector data!\n");
        goto Clear;
    }

    if (NULL == (matrix = malloc(N *sizeof(float*)))) { //индексный массив нужен для удобства обращения к данным
        printf("Can't allocate memory for the index array!\n");
        goto Clear;
    }

    if (NULL == (matrix_data = malloc(N * N * sizeof(float)))) { //N * N элементов
        printf("Can't allocate memory for the matirx data!\n");
        goto Clear;
    }

    for (unsigned idx = 0; idx != N; ++idx)
        matrix[idx] = matrix_data + idx * N; //мы вычисляем адреса строк внутри массива данных

    //далее код абсолютно такой же!
    printf("Please, enter the components of the vector: "); fflush(stdout);
    for (unsigned idx = 0; idx != N; ++idx)
        scanf("%f", &vector[idx]); //строго говоря, здесь тоже необходима проверка

    for (unsigned y_idx = 0; y_idx != N; ++y_idx) //этот цикл перебирает ряды
        for (unsigned x_idx = 0; x_idx != N; ++x_idx)
            matrix[y_idx][x_idx] = vector[y_idx] * vector[x_idx]; //по правилу перемножения матриц

    //выводим результат на экран
    for (unsigned y_idx = 0; y_idx != N; ++y_idx) {
        for (unsigned x_idx = 0; x_idx != N; ++x_idx)
            printf("%6.3f ", matrix[y_idx][x_idx]);
        printf("\n"); 
    }

Clear:
    if (NULL != matrix_data) free(matrix_data);
    if (NULL != matrix) free(matrix);    
    if (NULL != vector) free(vector);
End:
    return;
}

/**
 * Выделение памяти одним вызовом malloc позволяет
 * при необходимости обойти весь массив как непрерывную 
 * область памяти, что при большом количестве рядов 
 * может быть выполнено ощутимо быстрее, чем обход 
 * разбросанных по памяти кусочков данных.
 * Помимо этого, упрощается работа с ресурсами - 
 * выделение и освобождение памяти.
 */

int main() {
    if (false) two_dimensional_dynamic_memory_array();
    if (false) vec_product_matrix_example();
    if (false) continuous_two_dimensional_array();
    return 0;
}
