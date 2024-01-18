#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int count(int x);
void win(int point1, int point2);
void game();
char check_left_choice();
char check_right_choice();
void make_field(int ball_x, int ball_y, int rocket_1_x, int rocket_1_y, int rocket_2_x, int rocket_2_y,
                int score_1_player, int score_2_player);

int main() {
    game();
    return 0;
}

void game() {
    int ball_x = 39, ball_y = 12, rocket1_x = 3, rocket1_y = 11, rocket2_x = 76, rocket2_y = 11;
    int move_x = 1, move_y = -1, score_left = 0, score_right = 0;
    char first, second;
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
            win(score_left, score_right);
            break;
        } else {
            first = check_left_choice();
            second = check_right_choice();
            rocket1_y = (first == 'a' && rocket1_y >= 2) ? rocket1_y - 1 : rocket1_y;
            rocket1_y = (first == 'z' && rocket1_y <= 20) ? rocket1_y + 1 : rocket1_y;
            if (second == 'k' && rocket2_y >= 2)
                --rocket2_y;
            else if (second == 'm' && rocket2_y <= 20)
                ++rocket2_y;
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
            if (second == 'k' && move_y < 0 && move_y > -3) move_y -= 2;
            if (second == 'm' && move_y > 0 && move_y < 3) move_y += 2;
            move_x *= -1;
        }
        if (ball_x + move_x < 79) ball_x += move_x;
        if (ball_y + move_y < 24) ball_y += move_y;
    }
}

char check_left_choice() {
    printf("LEFT STEP!\nEnter a for up or z for down:");

    char choice_left = getchar();
    while (getchar() != '\n')
        ;

    while (choice_left != 'A' && choice_left != 'a' && choice_left != 'z' && choice_left != 'Z' &&
           choice_left != ' ') {
        printf("Try again!\n");
        printf("LEFT STEP!\nEnter a for up or z for down:");

        choice_left = getchar();
        while (getchar() != '\n')
            ;
    }

    if (choice_left == 'Z' || choice_left == 'A') {
        choice_left = 'a' + (choice_left - 'A');
    }

    return choice_left;
}

char check_right_choice() {
    printf("RIGTH STEP!\nEnter k for up or m for down:");

    char choice_right = getchar();
    while (getchar() != '\n')
        ;

    while (choice_right != 'k' && choice_right != 'K' && choice_right != 'm' && choice_right != 'M' &&
           choice_right != ' ') {
        printf("Try again!\n");
        printf("RIGHT STEP!\nEnter k for up or m for down:");

        choice_right = getchar();
        while (getchar() != '\n')
            ;
    }

    if (choice_right == 'K' || choice_right == 'M') {
        choice_right = 'a' + (choice_right - 'A');
    }

    return choice_right;
}

int count(int x) {
    int result = 0;
    const int left_line = 1, right_line = 78;
    if (x <= left_line) {
        result = 1;
    }

    if (x >= right_line) {
        result = 1;
    }
    return result;
}

void win(int point1, int point2) {
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
    } else if (point2 == win_point) {
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
    printf("\033[2J\033[1;1H");
    for (int i = 0; i < 25; ++i) {
        for (int j = 0; j < 80; ++j) {
            if (i == 0 || j == 0 || i == 24 || j == 79) {
                printf("#");
            } else if (j == ball_x && i == ball_y) {
                printf("*");
            } else if (j == 39 && (i != ball_y || j != ball_x)) {
                printf("|");
            } else if ((j == rocket_1_x && i >= rocket_1_y && i <= rocket_1_y + 2) ||
                       (j == rocket_2_x && i >= rocket_2_y && i <= rocket_2_y + 2)) {
                printf("|");
            } else if (j == 35 && i == 3 && score_1_player < 10) {
                printf("%d", score_1_player);
            } else if (j == 34 && i == 3 && score_1_player >= 10) {
                printf("%d", score_1_player);
                j++;
            } else if (j == 43 && i == 3 && score_2_player < 10) {
                printf("%d", score_2_player);
            } else if (j == 42 && i == 3 && score_2_player >= 10) {
                printf("%d", score_2_player);
                ++j;
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}
