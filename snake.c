#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define WIDTH 40
#define HEIGHT 20
#define MAX_SNAKE 100

typedef struct {
    int x, y;
} Point;

Point snake[MAX_SNAKE];
int snake_length = 5;
int dx = 1, dy = 0;
Point food;
int score = 0;

void init_game() {
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    srand(time(NULL));

    // Inicializuj hada v strede
    for (int i = 0; i < snake_length; ++i) {
        snake[i].x = WIDTH / 2 - i;
        snake[i].y = HEIGHT / 2;
    }

    // Prvé jedlo
    food.x = rand() % WIDTH;
    food.y = rand() % HEIGHT;
}

void draw_border() {
    for (int x = 0; x <= WIDTH + 1; ++x) {
        mvaddch(0, x, '#');
        mvaddch(HEIGHT + 1, x, '#');
    }
    for (int y = 0; y <= HEIGHT + 1; ++y) {
        mvaddch(y, 0, '#');
        mvaddch(y, WIDTH + 1, '#');
    }
}

void draw() {
    clear();
    draw_border();
    mvprintw(0, WIDTH + 5, "Score: %d", score);

    // Jedlo
    mvaddch(food.y + 1, food.x + 1, '@');

    // Had
    for (int i = 0; i < snake_length; ++i) {
        mvaddch(snake[i].y + 1, snake[i].x + 1, i == 0 ? 'O' : '*');
    }

    refresh();
}

void update_snake() {
    // Posuň telo
    for (int i = snake_length - 1; i > 0; --i) {
        snake[i] = snake[i - 1];
    }

    // Hlava
    snake[0].x += dx;
    snake[0].y += dy;
}

int check_collision() {
    // Steny
    if (snake[0].x < 0 || snake[0].x >= WIDTH || snake[0].y < 0 || snake[0].y >= HEIGHT)
        return 1;

    // So sebou
    for (int i = 1; i < snake_length; ++i) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
            return 1;
    }

    return 0;
}

void generate_food() {
    int valid = 0;
    while (!valid) {
        food.x = rand() % WIDTH;
        food.y = rand() % HEIGHT;
        valid = 1;
        for (int i = 0; i < snake_length; ++i) {
            if (snake[i].x == food.x && snake[i].y == food.y) {
                valid = 0;
                break;
            }
        }
    }
}

int main() {
    init_game();

    while (1) {
        int ch = getch();
        switch (ch) {
            case KEY_UP:    if (dy == 0) { dx = 0; dy = -1; } break;
            case KEY_DOWN:  if (dy == 0) { dx = 0; dy = 1; } break;
            case KEY_LEFT:  if (dx == 0) { dx = -1; dy = 0; } break;
            case KEY_RIGHT: if (dx == 0) { dx = 1; dy = 0; } break;
            case 'q': endwin(); return 0;
        }

        update_snake();

        // Kontrola zjedenej potravy
        if (snake[0].x == food.x && snake[0].y == food.y) {
            if (snake_length < MAX_SNAKE)
                snake_length++;
            score += 10;
            generate_food();
        }

        if (check_collision()) {
            clear();
            mvprintw(HEIGHT / 2, (WIDTH - 9) / 2, "GAME OVER");
            mvprintw(HEIGHT / 2 + 1, (WIDTH - 16) / 2, "Final score: %d", score);
            refresh();
            sleep(2);
            break;
        }

        draw();
        usleep(120000);
    }

    endwin();
    return 0;
}