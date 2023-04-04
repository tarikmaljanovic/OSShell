#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <termios.h>
#include <fcntl.h>

#define WIDTH 80
#define HEIGHT 24

int main() {
    // Set up the terminal to read input without echo
    struct termios old_attr, new_attr;
    tcgetattr(STDIN_FILENO, &old_attr);
    new_attr = old_attr;
    new_attr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_attr);

    // Set up the random number generator
    srand(time(NULL));

    // Initialize the matrix with spaces
    char matrix[HEIGHT][WIDTH];
    int i, j;
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            matrix[i][j] = ' ';
        }
    }

    // Display the matrix
    while (1) {
        // Move all the characters down by one row
        for (i = HEIGHT-1; i > 0; i--) {
            for (j = 0; j < WIDTH; j++) {
                matrix[i][j] = matrix[i-1][j];
            }
        }

        // Generate a new row of characters
        for (j = 0; j < WIDTH; j++) {
            matrix[0][j] = rand() % 94 + 33; // ASCII characters between '!' and '~'
        }

        // Print the matrix to the terminal
        printf("\033[2J\033[%d;%dH", 0, 0); // Clear the screen and move the cursor to the top left
        for (i = 0; i < HEIGHT; i++) {
            for (j = 0; j < WIDTH; j++) {
                printf("%c", matrix[i][j]);
            }
            printf("\n");
        }
        fflush(stdout);

        // Sleep for a short amount of time
        usleep(100000);
    }

    // Restore the terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &old_attr);

    return 0;
}