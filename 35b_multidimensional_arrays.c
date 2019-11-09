/**
 * Как и одномерные массивы, многомерные массивы можно 
 * передавать в функции. Точнее в функцию можно передать 
 * адрес индексного массива. Рассмотрим функции для 
 * печати таблицы и её (функции) вызов.
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void table_print(int **table, unsigned x_size, unsigned y_size) {
    /**
     * table - адрес индексного массива.
     * table[idx] - это массив, ряд элементов с номером idx
     * Размеры таблицы: y_size рядов и x_size элементов в ряду
     */
    for (unsigned y_idx = 0; y_idx != y_size; ++y_idx) {
        for (unsigned x_idx = 0; x_idx != x_size; ++x_idx)//важно организовывать данные таким образом, чтобы последний индекс был наболее часто изменяемым
            printf("%3d ", table[y_idx][x_idx]);
        printf("\n");
    }
}

//пример выделения памяти под таблицу и вызова функции table_print
void table_print_test() {
    unsigned N = 10;
    int **table = NULL, *table_data = NULL;

    if(NULL == (table = malloc(N * sizeof(int*)))) {
        printf("Can't allocate index array!\n");
        goto Clear;
    }

    if (NULL == (table_data = malloc(N * N *sizeof(int)))) {
        printf("Can't allocate table data!\n");
        goto Clear;
    }

    for (unsigned idx = 0; idx != N; ++idx)
        table[idx] = table_data + N * idx;
    //использование непрерывной выделенной памяти позволяет нам эффективно обойти весь массив
    for (unsigned idx = 0; idx != N * N; ++idx)
        table_data[idx] = idx;

    table_print(table, N, N); //при вызове мы просто передаём адрес, по которому выделена память под индексный массив

Clear:
    if (NULL != table) free(table);
    if (NULL != table_data) free(table_data);
}

int main() {
    if (false) table_print_test();
    return 0;
}

