// Таблицы Шульте by AlexRoth - VERSION 3.0
// Версия с псевдографикой в структурном стиле

// по сравнению с 1.0 сделан таймер с милисекундами,
// нормально отображаются таблицы со стороной > 9
// результат теперь можно посмотреть нажав enter
// - необходимо добавить динамическое выделение памяти в массиве структур содержащих таблицы
// - необходимо добавить парсер для table_size_set()
// - необходимо сделать возможность по enter оставлять размер таблицы как у текущей (реализовать в функции парсера)
// - необходимо сделать аналитику по каждой таблице
// - необходимо сделать сохранение по
#include <stdio.h> //стандартный ввод-вывод (на всякий)
#include <stdlib.h> // необходима для работы rand()
#include <time.h> // для rand() и clock_gettime()
#include <sys/times.h> // ?? пока не знаю
#include <ncurses.h> // для работы с терминалом
#include <locale.h> // для отображения киррилицы

#define TABLE_VOLUME 1000 // максимальное кол-во создаваемых таблиц за 1 сессию
#define MAX_SIZE 20*20 // максимальное кол-во чисел в таблице
#define SQR(a) (a * a)

typedef struct {
    int table_side; // размер сторны таблицы (задается пользователем)
    unsigned int solution_time; // время (в тиках)  за которое пользователь прошел таблицу
    //    unsigned short rund_sequence[MAX_SIZE]; // уникальная послдовательность чисел таблицы
    int rund_sequence[MAX_SIZE]; // уникальная послдовательность чисел таблицы
}TABLE;
TABLE Table[TABLE_VOLUME];  // массив таблиц
//
//void table_size_set(int); // функция получения размера стороны таблицы
//void rundom_set(int); // создает уникальную послдовательность чисел таблицы
//void print_table(int); // рисует таблицу
//void print_final_result(int); // выдает статистику по прохождению всех таблиц
//void show_time (void); // показывает пройденное время

/////////////////// main ////////////////////
int main(int argc, char *argv[])
{
    setlocale(LC_ALL, ""); // выставляем поддержку киррилицы - всегда перед initscr()
    initscr(); // инициализация ncurses
    use_default_colors(); //  // чтобы цвета вернулись к настройкам terminal (белый был белым а не серый и цвет фона и шрифта были как настроено в terminal (работает даже если  использовать после введенного текста)
    // noecho(); // чтобы не печатались вводимые символы
    curs_set(0); // убираем курсор
    int xMax, yMax; // переменные для получения размера экрана terminal
    getmaxyx(stdscr, yMax, xMax); // получаем размеры экрана
    box(stdscr, 0, 0); // рисуем бокс на границе stdscr
    refresh(); // выводим бокс на экран терминала
    int height = yMax-2, width = xMax, offsety = 0, offsetx = 0; // задаем переменные для инициализации окна таблицы
    WINDOW *main_win = newwin(height, width, offsety, offsetx); // создаем окно
    keypad(main_win, TRUE); // подключаем спец. клавиши (без keypad в режиме echo() они отображаются, но не влияют на процесс)
    box(main_win, 0, 0); // рисуем бокс по размерам окна
    int a = 159;
    mvwprintw (main_win, 1,1,"Введите значение (Table+0) -> table_side.");
   mvwscanw(main_win, 5, 9, "%d", &(Table+0) -> table_side);
mvwprintw (main_win, 6, 5, "Table[0].table_side = %d",Table[0].table_side);
    
//    mvwprintw (main_win, 6,5,"%d",Table[0].table_side);
//    mvwscanw(main_win, 5, 9,"%i", &(Table+0) -> table_side);
//    wrefresh(main_win); // работает только для stdscr
//    if (a == 1)
//        mvwprintw (main_win, 6,5,"hello %d",Table[0].table_side);
//    refresh();
//    mvwprintw (main_win, 6,5,"a = %d",a);
    wrefresh(main_win);
    getch();
    // объявление переменных
//    srand ((unsigned)time(0));
//    int count = 0;
//
//    while (count <= TABLE_VOLUME) { // выход из цикла осуществляется в функции table_size_set()
//        table_size_set(count); // пользователь инициализирует размер в структуре  таблицы
//        rundom_set(count); // посылаем только указатель на переменную table_size (для тренировки)
//        print_table(count); // посылаем только указатели на переменные table_size и массив rund_sequence (для тренировки)
//        count++;
//    }
    endwin(); // заканчиваем работу ncurses
}
///////////////////// table_set /////////////////////
//void table_size_set(int count){
//    initscr();
//    int xMax, yMax; // переменные для получения размера экрана terminal
//    getmaxyx(stdscr, yMax, xMax); // получаем размеры экрана
//    WINDOW *t_set = newwin(20, 8, yMax/2-4, xMax/2-10); // задаем размеры окна для вывода диалогов, привязывае его положение к центру консоли
//    wclear(t_set);
//    box(t_set, 0, 0);
//    wrefresh(t_set);
//    if (!count){ // если это самое начало работы программы
//        mvwprintw (t_set, 1,1,"Введите ширину таблицы № %d.",count+1);
//        mvwprintw (t_set, 2,1,"Введите \"0\" для завершения");
//        mvwprintw (t_set, 3,1, "Число должно быть не менее 2 и не более 20, иначе таблица не получится.\n");
//        wrefresh(t_set);
//    }
//    else
//        mvwprintw (t_set, 4,1,"Введите ширину таблицы № %d.\n",count+1);
//    mvwscanw(t_set, 5, 9,"%d", &(Table+count) -> table_side); // scanf получилось запустить для УКАЗАТЕЛЕЙ структуры но не для массивов
//    wrefresh(t_set);
//    while (Table[count].table_side){ // если пользователь не ввел "0" сперва следует проверка
//        if (Table[count].table_side > 20){ // защита от попыток ввода слишком больших таблиц
//            wclear(t_set);
//            mvwprintw (t_set, 1,1, "Извините, таблица %d x %d не поместится на экране, введите значениене не более 20\n",
//                       Table[count].table_side, Table[count].table_side);
//            wrefresh(t_set);
//            mvwscanw(t_set, 5, 9,"%i", &(Table[count].table_side));
//        }
//        else if (Table[count].table_side < 2 && Table[count].table_side){ // защита от попыток ввода слишком маленьких таблиц
//            wclear(t_set);
//            mvwprintw (t_set, 1,1, "Значение %d чересчур мало, введите другое значение\n",Table[count].table_side);
//            wrefresh(t_set);
//            mvwscanw(t_set, 5, 9,"%i", &(Table[count].table_side));
//        }
//        else return; // (return можно использовать даже в void функции)
//    }
//    wclear(t_set);
//    wrefresh(t_set);
//    print_final_result (count); // если пользователь ввел "0" то идем завершать программу
//    exit (0);
//}
//
///////////////////// rundom_set /////////////////////
//// Получает массив не повторяющихся чисел в рандомном порядке ("глупый" алгоритм)
//
//void rundom_set(int tbl_num){ // получает номер таблицы
//    int temp_rand; // временное хранилище для значениея rand
//    for (int rand_count = 0; rand_count < SQR(Table[tbl_num].table_side); rand_count++) // задаем цикл для получения сырого (без проверки) значения rand
//    {
//        Table[tbl_num].rund_sequence[rand_count] = temp_rand = (rand() % (SQR(Table[tbl_num].table_side)))+1; // получчение значения rand
//        for (int rand_check = 0; rand_check < rand_count; rand_check++) // проверка на не повторемость
//        {
//            if (Table[tbl_num].rund_sequence[rand_check] == temp_rand && rand_count > 0) // && если сравнивается не первое число с первым числом
//            {
//                rand_check = -1; // "-1", потому, что в строке "for" произойдет "rand_check++" и он станет "0"
//                Table[tbl_num].rund_sequence[rand_count] = temp_rand = (rand() % (SQR(Table[tbl_num].table_side)))+1;
//            }
//        }
//    }
//
//}
//
///////////////////// print_table /////////////////////
//// Печатает таблицу
//
//void print_table(int number){ // получает номер таблицы
//    if (Table[number].table_side > 3) // если таблица содержит 2-значные числа
//        for (int count = 1; count <= (Table[number].table_side - 3) * 5/2; count++) // формула для отступа нативно, кровью и потом полученная еще во времена 1.0 версии, как работает, ХЗ, забыл
//            printf(" "); // печатает отступ для заголовка таблицы
//    printf("–– ОТ 1 ДО %d ––\n", SQR(Table[number].table_side)); // печатаем сам заголовок
//    for (int str = 1; str <= Table[number].table_side; str++) // печатаем верхнюю горизонтальную линию
//        if (Table[number].table_side > 9) // если в таблице будут 3-х значные числа
//            printf("–––––-");
//        else // для 2-х значных и 1-значных
//            printf("–––––");
//    printf("–\n"); // "завершающий штрих"
//
//    for (int count = 1; count <= SQR(Table[number].table_side); count++){ // печатаем цифры таблицы
//        if (Table[number].table_side < 3) // если в таблице только одноразрядные числа
//            printf("| % 2d ", Table[number].rund_sequence[count-1]);
//        else if (Table[number].table_side > 9) // если в таблице есть 3-разрядные числа
//            printf("| %3d ", Table[number].rund_sequence[count-1]);
//        else
//            printf("| %2d ", Table[number].rund_sequence[count-1]); // иначе для 2-х и одноразрядных
//        if (count % Table[number].table_side == 0) // печатаем "закрывающую" стенку таблицы
//            printf("|\n");
//        if (count % Table[number].table_side == 0 || count == SQR(Table[number].table_side)){
//            for (int str = 1; str <= Table[number].table_side; str++)
//                if (Table[number].table_side > 9) // печатаем остальные горизонтальные линии
//                    printf("–––––-"); // для 3-ч значных
//                else
//                    printf("–––––"); // для двузначных
//            printf("–\n");
//        }
//    }
//    if (Table[number].table_side > 3) // еще раз формула для отступа
//        for (int str = 1; str <= (Table[number].table_side-3)*5/2; str++)
//            printf(" ");
//    printf("– ВРЕМЯ ПОШЛО -\n");
//    show_time (); // будем считать затраченое время на прохождение таблицы
//}
//
///////////////////// print_final_result /////////////////////
//void print_final_result ( int count){
//    printf("Вот и все.\n");
//    if (count) // если больше 1 таблицы
//        printf("Спасибо, что воспользовались нашими услугами!\n");
//    else
//        printf("Сожелеем, что не воспользовались нашими услугами.\n");
//}
//
///////////////////// show_time /////////////////////
//void show_time (){
//    // Структуры для сохранения разрешения часов
//    struct timespec res_clock; // создаем свой экземпляр структуры, который содержит tv_sec и tv_nsec
//    clock_gettime (CLOCK_REALTIME, &res_clock); // получаем "время в начале"
//    long sec, nsec; // будем хранить тут "время в начале"
//    sec = res_clock.tv_sec;
//    nsec = res_clock.tv_nsec;
//    getchar(); // поток хранит "\n", убираем его
//    if (getchar() != '\n') // пока пользователь не нажмет "enter"
//        getchar();
//    printf ("Ваш рузультат: ");
//    clock_gettime (CLOCK_REALTIME, &res_clock); // получаем "время в конце"
//    if (res_clock.tv_nsec < nsec){ // если наносекунд в конце меньше, чем в начале, преобразуем одну секунду в наносекунды
//        res_clock.tv_sec = res_clock.tv_sec -1;
//        res_clock.tv_nsec = res_clock.tv_nsec+ 1000000000;
//    }
//    printf ("%ld мин, %02ld сек, ",(res_clock.tv_sec - sec)/60, (res_clock.tv_sec - sec)%60); // выводим резульат
//    printf ("%03.0lf мс.\n\n",((double)res_clock.tv_nsec - (double)nsec)/1000000.); // наносекунды переврдим в double, для вывода правильного сокращения значений
//    return;
//}
//
//
//
//
//
//
//
