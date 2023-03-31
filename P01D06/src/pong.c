// Copyright 2022 Dreamteam
#include <stdio.h>
#include <stdlib.h>

#define WIDTH_SCRING 80
#define HEIGHT_SCRING 25
#define HEIGHT_SCOPE 3
#define ROCKET1_START_Y 19
#define ROCKET2_START_Y 5
#define ROCKET1_DEFAULT_X 2
#define ROCKET2_DEFAULT_X (WIDTH_SCRING - 3)
#define BALL_START_X (WIDTH_SCRING / 2)
#define BALL_START_Y (HEIGHT_SCRING / 2)
#define START_INPUT_EXIT 5
#define START_INPUT_SCOPE 19
#define NUMBER_SCOPE_CHARACTERS 55
#define WINSCORE 21
#define TRUE 1
#define FALSE 0

// движение ракетки
void moveRocket(int *rocket_1_Y, int *rocket_2_Y, char temp);
// движение мяча
void moveBall(int *ball1_x, int *ball1_y,
                int *vector_X, int *vector_Y,
                const int *rocket_1_Y, const int *rocket_2_Y);

// обновление экрана
void screenRendering(const int *rocket_1_Y, const int *rocket_2_Y,
                        const int *ball1_x, const int *ball1_y,
                        int *scPlayer1, int *scPlayer2);

// проверка табло
int checkTablo(int *scPlayer1, int *scPlayer2, int *ball1_x, int *ball1_y);
void clearScreen(void);

int main(void) {
// стартовая позиция рокетки 1 и 2 по оси Y. По оси X она не меняется
    int rocket_1_Y = ROCKET1_START_Y;
    int rocket_2_Y = ROCKET2_START_Y;
// стартовая позиция мяча по оси X и Y
    int ball_X = BALL_START_X;
    int ball_Y = BALL_START_Y;
// направление движения мяча по оси X и Y
    int vector_X = -1;
    int vector_Y = 1;
// очки со старта у игрока 1 и 2
    int score_Player_1 = 0;
    int score_Player_2 = 0;
    char temp = ' ';

// пока мы не ввели q, мы исполняем программу
    while (temp != 'q') {
// вызываем функцию с переменными из памяти, которые ранее присвоили
        screenRendering(&rocket_1_Y, &rocket_2_Y, &ball_X, &ball_Y,
                        &score_Player_1, &score_Player_2);
// считываем ввод и записываем в переменную в temp и в cooked
        system("/bin/stty raw");
        temp = getchar();
        system("/bin/stty cooked");
// движение рокетки исходя из переменной temp. И мяча
// первоначально, движение осуществляется по переменным из main()
        moveRocket(&rocket_1_Y, &rocket_2_Y, temp);
        moveBall(&ball_X, &ball_Y,
                    &vector_X, &vector_Y,
                    &rocket_1_Y, &rocket_2_Y);
        clearScreen();
// если значения из табло и положение мяча задано стартовому значению
// то разрываем процесс
        if (checkTablo(&score_Player_1, &score_Player_2,
                                &ball_X, &ball_Y)) {
            break;
        }
    }
    return 0;
}

// движение ракетки. Задаем 2 параметра где мы возвращаем значение переменной через указатель
void moveRocket(int *rocket_1_Y, int *rocket_2_Y, char temp) {
    switch (temp) {
// узнаем какое значение переменной мы получили в temp.
// если символ а, и мы проверили, что мы не дошли ракеткой до вверха (-2), иначе мы поднимаемся на -1
        case 'a' : ((*rocket_1_Y - 2) != 0) ? (*rocket_1_Y -= 1) : \
            *rocket_1_Y;
            break;
// если символ  z, и мы проверили, что мы не дошли ракеткой до нижней границы (ВЫСОТА - 1)
// иначе мы спускаем решение через +1
        case 'z' : ((*rocket_1_Y + 2) != HEIGHT_SCRING - 1) ? \
            (*rocket_1_Y += 1) : *rocket_1_Y;
            break;
// если символ  k, и мы проверили, что мы не дошли ракеткой до вверха (-2)
// иначе мы поднимаемся на -1
        case 'k' : ((*rocket_2_Y - 2) != 0) ? (*rocket_2_Y -= 1) : \
            *rocket_2_Y;
            break;
// если символ  m, и мы проверили, что мы не дошли ракеткой до нижней границы (ВЫСОТА - 1)
// иначе мы спускаем решение через +1
        case 'm' : ((*rocket_2_Y + 2) != HEIGHT_SCRING - 1) ? \
            (*rocket_2_Y += 1) : *rocket_2_Y;
            break;
  }
}

void screenRendering(const int *rocket_1_Y, const int *rocket_2_Y,
                    const int *ball1_x, const int *ball1_y,
                    int *scPlayer1, int *scPlayer2) {
// присваем y=0 и если меньше масштаба_высоты? мы индекс увеличиваем на ++1
    for (int y = 0; y < HEIGHT_SCOPE; ++y) {
// если индекс меньше ширины экрана, то увеличиваем индекс на ++1
        for (int x = 0; x < WIDTH_SCRING; ++x) {
// РИСУЕМ ГРАНИЦУ ЭКРАНА ТАБЛО
// рисуем верхнюю и нижнюю границу табло
            if ((y == 0 && x != 0 && x != WIDTH_SCRING-1) ||
                (y == HEIGHT_SCOPE - 1 && x != 0 && x != WIDTH_SCRING-1)) {
                printf(" ");
// рисуем левую и правую границу табло
            } else if (((x == 0 && y != 0 && y != HEIGHT_SCOPE - 1) ||
                        (x == WIDTH_SCRING - 1 && y != 0 && y != \
                         HEIGHT_SCOPE - 1))) {
                printf(" ");
// ГРАНИЦЫ НАРИСОВАНЫ
// если значение х равно нашей глобальной переменной для старта текста для выхода, то печатаем текст
            } else if (x == START_INPUT_EXIT) {
                printf("Press \'Control + c\' to exit");
// если значение х равно нашей глобальной переменной для старта текста для выхода, то печатаем текст
            } else if (x == START_INPUT_SCOPE) {
                printf("Player one: %d | Player two: %d", *scPlayer1, \
                       *scPlayer2);
// печатаем пробелы если y == 1 и x меньше ШИРИНЫ ЭКРАНА и КОЛ-ВА символов
            }  else if (y == 1 && x < WIDTH_SCRING - NUMBER_SCOPE_CHARACTERS) {
                printf(" ");
// если y не 1 то тоже печатаем пробелы
            } else if (y != 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
// если 1 индекс меньше высоты экрана, то добавляем к индексу 1
    for (int y = 0; y < HEIGHT_SCRING; ++y) {
// если 2 индекс меньше ширины экрана, то добавляем к индексу 1
        for (int x = 0; x < WIDTH_SCRING; ++x) {
// рисуем ракетки
// ракетка состоит из 3х символов. где x - положение ракетки по умолчанию (см выше)
// и положение y и рисуем 3 символа по вертикали по границам от -1 0 1
            if ((x == ROCKET1_DEFAULT_X &&
                (y == *rocket_1_Y - 1 || y == *rocket_1_Y || y == \
                 *rocket_1_Y + 1)) ||
                (x == ROCKET2_DEFAULT_X &&
                (y == *rocket_2_Y - 1 || y == *rocket_2_Y || y == \
                 *rocket_2_Y + 1))) {
                printf("§");
// устанавливаем мяч. Мы обращаемся к памяти переменной. По умолчанию установливаем из переменных выше
            } else if (x == *ball1_x && y == *ball1_y) {
                printf("o");
// устанавливаем верхние и нижние границы
// если координата y равна 0 и максимальной высоты -1. Отступы -1
            } else if ((y == 0 && x != 0 && x != WIDTH_SCRING - 1) ||
                        (y == HEIGHT_SCRING - 1 && x != 0 && x != \
                         WIDTH_SCRING - 1)) {
                printf("Г");
// рисуем вертикальные границы
            } else if ((x == 0 && y != 0 && y != HEIGHT_SCRING - 1) ||
                        (x == WIDTH_SCRING - 1 && y != 0 && y != \
                         HEIGHT_SCRING - 1) ||
                        (x == WIDTH_SCRING / 2)) {
                printf("В");
// иначе рисую пустые значения
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

// движение мяча
// устанавливаю параметры мяча, движение мяча по x и y, и 2 ракетки
void moveBall(int *ball1_x, int *ball1_y, int *vector_X, int *vector_Y,
                const int *rocket_1_Y, const int *rocket_2_Y) {
// если значение y 1 или y равна нижней границы
// то мы меняем движение вектора в противоположную сторону и заканчиваем условие
    if (*ball1_y == 1 || *ball1_y == HEIGHT_SCRING - 2) {
        *vector_Y = -(*vector_Y);
    }
// если значение x дотронулось до ракетки И
// y дотронулся до ракетки в промежутке от -1<=rocket_1_Y<=1 (смотри там где ИЛИ)
// то мы меняем движение вектора в противоположную сторону по оси X
    if (*ball1_x == ROCKET1_DEFAULT_X + 1 &&
        (*ball1_y == *rocket_1_Y - 1 ||*ball1_y == *rocket_1_Y  || \
         *ball1_y == *rocket_1_Y + 1)) {
        *vector_X = -(*vector_X);
    }
// если значение x дотронулось до ракетки И
// y дотронулся до ракетки в промежутке от -1<=rocket_2_Y<=1 (смотри там где ИЛИ)
// то мы меняем движение вектора в противоположную сторону по оси X
    if (*ball1_x == ROCKET2_DEFAULT_X - 1 &&
        (*ball1_y == *rocket_2_Y - 1 || *ball1_y == *rocket_2_Y  || \
         *ball1_y == *rocket_2_Y + 1)) {
        *vector_X = -(*vector_X);
    }
// иначе мы координатам мяча плюсуем переменную вектора который установлен в main() и обращаемся к памяти
    *ball1_y += *vector_Y;
    *ball1_x += *vector_X;
}
// проверяем табло
int checkTablo(int *scPlayer1, int *scPlayer2, int *ball1_x, int *ball1_y) {
// если положение мяча по оси x меньше 2, то есть ушел за левую границу И
// мы добавляем очко игроку с противоположной стороны и возвращаем положение мяча обратно
    if (*ball1_x < 2) {
        *scPlayer2 += 1;
        *ball1_x = BALL_START_X;
        *ball1_y = BALL_START_Y;
    }
    if (*ball1_x > WIDTH_SCRING - 3) {
        *scPlayer1 += 1;
        *ball1_x = BALL_START_X;
        *ball1_y = BALL_START_Y;
    }
    if (*scPlayer1 == WINSCORE) {
        printf("\n\tCONGRATULATION!!! PLAYER ONE IS WON BY %d TO %d.", \
               *scPlayer1, *scPlayer2);
        return TRUE;
    } else if (*scPlayer2 == WINSCORE) {
        printf("\n\tCONGRATULATION!!! PLAYER TWO IS WON BY %d TO %d.", \
               *scPlayer2, *scPlayer1);
        return TRUE;
    }
    return FALSE;
}
// очистка экрана
void clearScreen(void) {
    printf("\33[0d\33[2J");
}
