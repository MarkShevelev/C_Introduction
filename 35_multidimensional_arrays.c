/**
 * Массивы удобны для работы с данными, которые 
 * могут быть легко представлены одним индексом.
 * Однако во многих задачах бывает удобного 
 * представлять данные двумя индексами. Например, 
 * если у нас есть города A, B, C, D и сеть дорог 
 * между городами, то расстояние между городами 
 * удобно представить таблицей. Элемент таблицы
 * определяется уже не одним, а двумя индексами.
 * Для работы с такими структурами в языке C 
 * предусмотрены многомерные массивы.
 */

#include <stdio.h>
#include <stdbool.h>

/**
 * Простейшее объявление многомерного автоматического 
 * массива.
 */

void multidimensional_automatic_array_declaration() {
    int arr_2d[3][4];
    /**
     * Объявление аналогично объявлению одномерного массива.
     * Каждая пара квадратных скобок задаёт количество элементов 
     * в одном измерении. В данном случае массив arr_2d состоит из 
     * трёх рядов, в каждом из которых по 4 элемента.
     */

    /**
     * Обращение к элементам массива осуществляется также через квадратные скобки,
     * но теперь нужно указать два индекса.
     */
    arr_2d[1][2] = 1;
    arr_2d[0][0] = 0; //самый малый допустимый индекс
    arr_2d[2][3] = 3; //самый большой допустимый индекс

    /**
     * Максимальный допустимый индекс, как и в случае одномерного массива,
     * равен size - 1 , где size - размерность по направлению.
     */

    /**
     * Если мы захотим заполнить такой массив данными,
     * то нам потребуется не один, а два цикла, один 
     * вложен в другой. Один цикл пробегает все элементы 
     * в ряду, а второй пребирает всевозможные ряды.
     * Заполним массив arr_2d произведениями индексов.
     */
    for (unsigned idx_1 = 0; idx_1 != 3; ++idx_1)     //перебираем ряды
        for (unsigned idx_2 = 0; idx_2 != 4; ++idx_2) //перебираем все элементы в ряду
            arr_2d[idx_1][idx_2] = idx_1 * idx_2;

    /**
     * Выведем таблицу на экран.
     */
    for (unsigned idx_1 = 0; idx_1 != 3; ++idx_1) {
        for (unsigned idx_2 = 0; idx_2 != 4; ++idx_2)
            printf("%2d ",arr_2d[idx_1][idx_2]);
        printf("\n");
    }

    /**
     * Многомерные автоматические массивы всегда имеют 
     * одинаковое количество элементов в каждом ряду.
     * Такие многомерные массивы называются "выровненные".
     */

    /**
     * Многомерные массивы могут быть не только двумерными, 
     * но и трёхмерными, и четырёхмерными, и т.д.
     */

    int arr_3d[3][3][3]; //куб данных: три слоя, каждый слой в три ряда, каждый ряд в три элемента
    int arr_4d[2][2][2][2]; //гиперкуб данных
}

/**
 * Двумерные массивы можно использовать для хранения
 * таблиц, это особенно важно при программировании 
 * конечных автоматов. Мы рассмотрим хорошо известный 
 * нам пример с цветными кирпичами. Если заданы цвета 
 * двух кирпичей на нижнем слое, то цвет нового кирпича 
 * определяется по правилам: если цвета кирпичей одинаковы, 
 * то на них мы кладём кирпич того же цвета, а если 
 * разные - то недостающего третьего. Ранее мы писали 
 * сложный код с множественным выбором. Можно удобно 
 * реализовать функцию выбора цвета кирпича с использованием 
 * двумерной таблицы.
 * Пусть цветам соответствуют числа 0, 1, 2.
 */
int next_color(int left, int right) {
    int color_table[3][3];
    color_table[0][0] = 0;
    color_table[0][1] = 2;
    color_table[0][2] = 1;
    color_table[1][0] = 2;
    color_table[1][1] = 1;
    color_table[1][2] = 0;
    color_table[2][0] = 1;
    color_table[2][1] = 0;
    color_table[2][2] = 2;

    return color_table[left][right];
}

/**
 * К сожалению создание массива и присваивание будет
 * происходить при каждом вызове функции next_color.
 * Можно улучшить работу с таблицей, сделав её статической,
 * чтобы избежать повторного выделения памяти. А чтобы 
 * избежать присваивания, нужно инициализировать таблицу.
 * Многомерные массивы можно инициализировать с помощью 
 * вложенных фигурных скобок. { {<первый ряд>}, {<второй ряд>}, {<третий ряд>}, <и т.д.> }
 * Перепишем функцию next_color.
 */
int next_color_static_table(int left, int right) {
    static int const color_table[3][3] = { {0, 2, 1}, { 2, 1, 0}, { 1, 0, 2} };
    //мы объявили массив статическим и неизменяемым
    return color_table[left][right];
}

/**
 * Аналогичным образом можно создать одномерную таблицу, 
 * которая будет переводить номер цвета в букву.
 */
char to_letter(int color) {
    static char const letters[3] = {'R','G','B'};
    return letters[color];
}

/**
 * Используя двумерный массив, мы можем сначала запомнить 
 * все ряды пирамиды, а затем вывести их, начиная от вершины!
 */
void color_pyramid() {
    int pyramid[10][10]; //пирамида с длиной основания 10 содержит 10 рядов
    for (unsigned idx = 0; idx != 10; ++idx)
        scanf("%d",&pyramid[0][idx]); //нулевой ряд, различные элементы в ряду

    for (unsigned row = 1; row != 10; ++row)
       for (unsigned idx = 0; idx != 10 - row; ++idx)
          pyramid[row][idx] = next_color_static_table(pyramid[row-1][idx],pyramid[row-1][idx+1]);

   //вывод пирамиды в обратном порядке
    for (unsigned row = 10; row != 0; --row) {
        for (unsigned l = 0; l != row-1; ++l) //просто для выравнивая в пирамиду
            printf(" ");
        for (unsigned idx = 0; idx != 10 - row + 1; ++idx)
            printf("%c ",to_letter(pyramid[row-1][idx]));
        printf("\n");
    }
}

/**
 * На самом деле половина массива pyramid не была задействована.
 * В каждом новом ряду на один элемент меньше, чем в предыдущем.
 * Но с использованием автоматических многомерных массивов 
 * иначе эту задачу нельзя решить, т.к. она всегда "выровненные", 
 * т.е. содержат одинаковое количество элементов в каждом ряду.
 * Для создания невыровненных массивов необходимо прибегать 
 * к другим методам.
 */    


int main() {
    if (false) multidimensional_automatic_array_declaration();
    if (false) color_pyramid();
    return 0;
}



