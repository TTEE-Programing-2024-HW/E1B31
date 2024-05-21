#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define PASSWORD 2024
#define MAX_TRIES 3
#define SEATS_ROWS 9
#define SEATS_COLS 9

void clear_screen() {
    // Clear the console screen
    system("cls");
}

void show_welcome_screen() {
    // Display a welcome screen with personalized artwork
    printf("**************************************\n");
    printf("* *\n");
    printf("* Welcome to the Booking System *\n");
    printf("* *\n");
    printf("**************************************\n");
    printf("\nPlease enter the 4-digit password: ");
}

int check_password(int password) {
    // Check if the entered password matches the predefined password
    return password == PASSWORD;
}

void show_warning_message() {
    // Display a warning message after 3 incorrect password attempts
    printf("\nToo many incorrect attempts. Exiting the program.\n");
}

void show_main_menu() {
    // Display the main menu
    printf("\n-[Booking System]-\n");
    printf("a. Available seats\n");
    printf("b. Arrange for you\n");
    printf("c. Choose by yourself\n");
    printf("d. Exit\n");
    printf("Choose an option: ");
}

void show_seat_chart(char seats[SEATS_ROWS][SEATS_COLS]) {
    // Display the current seat chart
    printf("\n 123456789\n");
    for (int i = 0; i < SEATS_ROWS; i++) {
        printf("%d ", i+1);
        for (int j = 0; j < SEATS_COLS; j++) {
            printf("%c", seats[i][j]);
        }
        printf("\n");
    }
}

void initialize_seats(char seats[SEATS_ROWS][SEATS_COLS]) {
    // Initialize the seats array with '-' and randomly set 10 seats as booked ('*')
    srand(time(0));
    for (int i = 0; i < SEATS_ROWS; i++) {
        for (int j = 0; j < SEATS_COLS; j++) {
            seats[i][j] = '-';
        }
    }

    for (int k = 0; k < 10; k++) {
        int rand_row = rand() % SEATS_ROWS;
        int rand_col = rand() % SEATS_COLS;
        if (seats[rand_row][rand_col] == '-') {
            seats[rand_row][rand_col] = '*';
        } else {
            k--; // Ensure we get exactly 10 random seats booked
        }
    }
}

void handle_option_a(char seats[SEATS_ROWS][SEATS_COLS]) {
    // Handle the display of available seats
    clear_screen();
    show_seat_chart(seats);
    printf("\nPress any key to return to the main menu...\n");
    getchar();
}

void suggest_seats(char seats[SEATS_ROWS][SEATS_COLS], int seats_needed) {
    // Suggest seats to the user
    int suggested = 0;
    clear_screen();
    
    // Try to find a continuous block of seats_needed seats
    for (int i = 0; i < SEATS_ROWS && !suggested; i++) {
        for (int j = 0; j < SEATS_COLS - seats_needed + 1 && !suggested; j++) {
            int k;
            for (k = 0; k < seats_needed; k++) {
                if (seats[i][j + k] != '-') {
                    break;
                }
            }
            if (k == seats_needed) {
                // We found a block of seats_needed seats
                for (k = 0; k < seats_needed; k++) {
                    seats[i][j + k] = '@';
                }
                suggested = 1;
            }
        }
    }

    // If not found, try to find two adjacent rows for 4 seats (only for 4 seats)
    if (!suggested && seats_needed == 4) {
        for (int i = 0; i < SEATS_ROWS - 1 && !suggested; i++) {
            for (int j = 0; j < SEATS_COLS - 1 && !suggested; j++) {
                if (seats[i][j] == '-' && seats[i][j + 1] == '-' && seats[i + 1][j] == '-' && seats[i + 1][j + 1] == '-') {
                    seats[i][j] = '@';
                    seats[i][j + 1] = '@';
                    seats[i + 1][j] = '@';
                    seats[i + 1][j + 1] = '@';
                    suggested = 1;
                }
            }
        }
    }

    show_seat_chart(seats);
    if (!suggested) {
        printf("\nUnable to find the requested seats. Press any key to return to the main menu...\n");
    } else {
        printf("\nAre you satisfied with the suggested seats? (y/n): ");
    }
    char response;
    while ((response = getchar()) == '\n');
    if (response == 'y') {
        // Convert '@' to '*' to mark as permanently booked
        for (int i = 0; i < SEATS_ROWS; i++) {
            for (int j = 0; j < SEATS_COLS; j++) {
                if (seats[i][j] == '@') {
                    seats[i][j] = '*';
                }
            }
        }
    }
    if (response == 'n') {
        // Convert '@' to '*' to mark as permanently booked
        for (int i = 0; i < SEATS_ROWS; i++) {
            for (int j = 0; j < SEATS_COLS; j++) {
                if (seats[i][j] == '@') {
                    seats[i][j] = '-';
                }
            }
        }
    }
    clear_screen();
}

void handle_option_b(char seats[SEATS_ROWS][SEATS_COLS]) {
    // Handle the seat arrangement for the user
    clear_screen();
    int seats_needed;
    printf("\nHow many seats do you need (1-4)? ");
    scanf("%d", &seats_needed);
    if (seats_needed >= 1 && seats_needed <= 4) {
        suggest_seats(seats, seats_needed);
    } else {
        printf("\nInvalid number of seats requested. Returning to main menu...\n");
    }
}

void handle_option_c(char seats[SEATS_ROWS][SEATS_COLS]) {
    // Handle the user selecting their own seats
    clear_screen();
    char input[10];
    printf("Enter your seat selection (e.g., 1-2,3-4):\n ");
    fflush(stdin);
    scanf("%s", input);
    char *token = strtok(input, ",");
    int valid_selection = 1;
    while (token) {
        int row, col;
        if (sscanf(token, "%d-%d", &row, &col) != 2 || row < 1 || row > 9  || col < 1 || col > 9 || seats[row-1][col-1] != '-') {
            valid_selection = 0;
            break;
        }
        seats[row-1][col-1] = '@';
        token = strtok(NULL, ",");
    }
    if (valid_selection) {
        show_seat_chart(seats);
        printf("Press any key to confirm and return to the main menu...\n");
        getchar(); // consume newline left by scanf
        getchar();
        for (int i = 0; i < SEATS_ROWS; i++) {
            for (int j = 0; j < SEATS_COLS; j++) {
                if (seats[i][j] == '@') {
                    seats[i][j] = '*';
                }
            }
        }
    } else {
        printf("\nInvalid selection or seat already booked. Returning to main menu...\n");
    }
    clear_screen();
}

void handle_option_d() {
    // Handle the exit option
    clear_screen();
    printf("Continue? (y/n): ");
    char response;
    while ((response = getchar()) == '\n');
    if (response == 'n') {
        printf("Exiting the program. Goodbye!\n");
        exit(0);
    } else if (response == 'y') {
        clear_screen();
    } else {
        printf("Invalid input. Returning to main menu...\n");
    }
}

int main() {
    int tries = 0;
    int password;
    char seats[SEATS_ROWS][SEATS_COLS];

    initialize_seats(seats);

    while (tries < MAX_TRIES) {
        show_welcome_screen();
        scanf("%d", &password);
        if (check_password(password)) {
            clear_screen();
            break;
        } else {
            printf("\nIncorrect password. Try again.\n");
            tries++;
        }
    }

    if (tries == MAX_TRIES) {
        show_warning_message();
        return 0;
    }

    char option;
    while (1) {
        show_main_menu();
        while ((option = getchar()) == '\n'); // consume newline left by previous input
        switch (option) {
            case 'a':
                handle_option_a(seats);
                break;
            case 'b':
                handle_option_b(seats);
                break;
            case 'c':
                handle_option_c(seats);
                break;
            case 'd':
                handle_option_d();
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}