#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int count(int x);
void win(int point1);
int game();
char check_left_choice();
void make_field(int ball_x, int ball_y, int rocket_1_x, int rocket_1_y, int rocket_2_x, int rocket_2_y,
                int score_1_player, int score_2_player);

int main() {
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    int res = game();
    endwin();
    endwin();
    win(res);
    return 0;
}

int game() {
    int ball_x = 39, ball_y = 12, rocket1_x = 3, rocket1_y = 11, rocket2_x = 76, rocket2_y = 11;
    int move_x = 1, move_y = -1, score_left = 0, score_right = 0;
    char first;
    while (1) {
        make_field(ball_x, ball_y, rocket1_x, rocket1_y, rocket2_x, rocket2_y, score_left, score_right);
        int touch = count(ball_x);
        if (touch == -1 || touch == 1) {
            score_right = (touch == 1) ? score_right + 1 : score_right;
            score_left = (touch == -1) ? score_left + 1 : score_left;
            ball_x = 39;
            ball_y = 12;
            move_x *= -1;
        }
        if (score_left == 21 || score_right == 21) {
            if (score_left == 21)
                return 21;
            else
                return -21;
        } else {
            first = check_left_choice();
            rocket1_y = (first == 'a' && rocket1_y >= 2) ? rocket1_y - 1 : rocket1_y;
            rocket1_y = (first == 'z' && rocket1_y <= 20) ? rocket1_y + 1 : rocket1_y;
            rocket2_y = (first == 'k' && rocket2_y >= 2) ? rocket2_y - 1 : rocket2_y;
            rocket2_y = (first == 'm' && rocket2_y <= 20) ? rocket2_y + 1 : rocket2_y;
        }
        if (ball_y + move_y <= 0 || ball_y + move_y >= 24) {
            if (move_y < -1) ++move_y;
            if (move_y > 1) --move_y;
            move_y *= -1;
        }
        if (ball_x < 40 && ball_x + move_x <= rocket1_x &&
            rocket1_y <= ball_y + move_y * (rocket1_x - ball_x) / move_x &&
            ball_y + move_y * (rocket1_x - ball_x) / move_x <= rocket1_y + 2) {
            if (first == 'a' && move_y < 0 && move_y > -3) move_y -= 2;
            if (first == 'z' && move_y > 0 && move_y < 3) move_y += 2;
            move_x *= -1;
        } else if (ball_x > 40 && ball_x + move_x >= rocket2_x &&
                   rocket2_y <= ball_y + move_y * (rocket2_x - ball_x) / move_x &&
                   ball_y + move_y * (rocket2_x - ball_x) / move_x <= rocket2_y + 2) {
            if (first == 'k' && move_y < 0 && move_y > -3) move_y -= 2;
            if (first == 'm' && move_y > 0 && move_y < 3) move_y += 2;
            move_x *= -1;
        }
        if (ball_x + move_x < 79) ball_x += move_x;
        if (ball_y + move_y < 24) ball_y += move_y;
        usleep(100000);
    }
}

char check_left_choice() {
    char choice_left = getch();
    if (choice_left == 'Z' || choice_left == 'A' || choice_left == 'K' || choice_left == 'M') {
        choice_left = 'a' + (choice_left - 'A');
    }
    return choice_left;
}

int count(int x) {
    int result = 0;
    const int left_line = 1, right_line = 78;
    if (x <= left_line) {
        result = 1;
    }

    if (x >= right_line) {
        result = -1;
    }
    return result;
}

void win(int point1) {
    const int win_point = 21;
    if (point1 == win_point) {
        printf("\033[2J\033[1;1H");
        printf(" ###  ###  #   # #### ####   ###  ### #  # #    ###  ### ###  ###   #   #  ### \n");
        printf("#  # #   # ##  # #    #   # #   #  #  #  # #   #   #  #   #  #   #  ##  # #   #\n");
        printf("#    #   # #  ## # ## ####  #####  #  #  # #   #####  #   #  #   #  #  ##  ##  \n");
        printf("#  # #   # #   # #  # #  #  #   #  #  #  # #   #   #  #   #  #   #  #   #    # \n");
        printf(" ###  ###  #   # #### #   # #   #  #   ##  ### #   #  #  ###  ###   #   # ###  \n");
        printf("                                                                               \n");
        printf("                 ###  #     ###  #   # #### ####     ##                        \n");
        printf("                 #  # #    #   # #   # #    #   #     #                        \n");
        printf("                 ###  #    #####  # #  ###  ####      #                        \n");
        printf("                 #    #    #   #   #   #    #  #      #                        \n");
        printf("                 #    #### #   #   #   #### #   #    ###                       \n");
    } else if (point1 == -win_point) {
        printf("\033[2J\033[1;1H");
        printf(" ###  ###  #   # #### ####   ###  ### #  # #    ###  ### ###  ###   #   #  ### \n");
        printf("#  # #   # ##  # #    #   # #   #  #  #  # #   #   #  #   #  #   #  ##  # #   #\n");
        printf("#    #   # #  ## # ## ####  #####  #  #  # #   #####  #   #  #   #  #  ##  ##  \n");
        printf("#  # #   # #   # #  # #  #  #   #  #  #  # #   #   #  #   #  #   #  #   #    # \n");
        printf(" ###  ###  #   # #### #   # #   #  #   ##  ### #   #  #  ###  ###   #   # ###  \n");
        printf("                                                                               \n");
        printf("                 ###  #     ###  #   # #### ####     ###                       \n");
        printf("                 #  # #    #   # #   # #    #   #       #                      \n");
        printf("                 ###  #    #####  # #  ###  ####      ##                       \n");
        printf("                 #    #    #   #   #   #    #  #     #                         \n");
        printf("                 #    #### #   #   #   #### #   #    ####                      \n");
    }
}

void make_field(int ball_x, int ball_y, int rocket_1_x, int rocket_1_y, int rocket_2_x, int rocket_2_y,
                int score_1_player, int score_2_player) {
    clear();

    for (int i = 0; i < 25; ++i) {
        for (int j = 0; j < 80; ++j) {
            if (i == 0 || j == 0 || i == 24 || j == 79) {
                printw("#");
            } else if (j == ball_x && i == ball_y) {
                printw("*");
            } else if (j == 39 && (i != ball_y || j != ball_x)) {
                printw("|");
            } else if ((j == rocket_1_x && i >= rocket_1_y && i <= rocket_1_y + 2) ||
                       (j == rocket_2_x && i >= rocket_2_y && i <= rocket_2_y + 2)) {
                printw("|");
            } else if (j == 35 && i == 3 && score_1_player < 10) {
                printw("%d", score_1_player);
            } else if (j == 34 && i == 3 && score_1_player >= 10) {
                printw("%d", score_1_player);
                ++j;
            } else if (j == 43 && i == 3 && score_2_player < 10) {
                printw("%d", score_2_player);
            } else if (j == 42 && i == 3 && score_2_player >= 10) {
                printw("%d", score_2_player);
                ++j;
            } else {
                printw(" ");
            }
        }
        printw("\n");
    }

    refresh();
}
