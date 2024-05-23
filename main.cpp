#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

void append_text(char **text, int *text_len, int *text_size);
void start_new_line(char **text, int *text_len, int *text_size);
void save_text_to_file(const char *text);
void load_text_from_file(char **text, int *text_len, int *text_size);
void print_loaded_text(const char *text);
void clear_console();

int main() {
    setbuf(stdout, 0);

    int text_size = 10;
    char *text = (char *)calloc(text_size, sizeof(char));
    int text_len = 0;

    while (true) {
        printf("\nChoose the command (1/2/3/4/5/6/7/8/exit): ");
        char command[10];
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "exit") == 0) {
            printf("\nProgram was cancelled\n");
            break;
        }

        switch (command[0]) {
            case '1':
                append_text(&text, &text_len, &text_size);
                break;
            case '2':
                start_new_line(&text, &text_len, &text_size);
                break;
            case '3':
                save_text_to_file(text);
                break;
            case '4':
                load_text_from_file(&text, &text_len, &text_size);
                break;
            case '5':
                print_loaded_text(text);
                break;
            case '6':
                //append_by_coordinate();
                break;
            case '7':
                //search_position();
                break;
            case '8':
                clear_console();
                break;
            default:
                printf("\nInvalid command\n");
                break;
        }
    }

    free(text);
    text = NULL;
    return 0;
}

void append_text(char **text, int *text_len, int *text_size) {
    printf("\nEnter text to append:\n");

    int input_len = 0;
    int input_size = 80;
    char *input = (char *)calloc(input_size, sizeof(char));

    int character;
    while ((character = getchar()) != '\n' & EOF) {
        if (input_len >= input_size - 1) {
            input_size *= 2;
            input = (char *)realloc(input, input_size * sizeof(char));
        }
        input[input_len++] = (char)character;
    }

    if (*text_len + input_len >= *text_size - 1) {
        *text_size = (*text_len + input_len) * 2;
        *text = (char *)realloc(*text, *text_size * sizeof(char));
    }

    strcat(*text, input);
    *text_len += input_len;
    printf("Current text:\n%s\n", *text);
    free(input);
    input = NULL;
}

void start_new_line(char **text, int *text_len, int *text_size) {
    if (*text_len + 1 >= *text_size - 1) {
        *text_size = (*text_size) * 2;
        *text = (char *)realloc(*text, *text_size * sizeof(char));
    }
    strcat(*text, "\n");
    (*text_len)++;
    printf("\nNew line is started\n");
    printf("Current text:\n%s\n", *text);
}

void save_text_to_file(const char *text) {
    char file_name[25];
    printf("\nEnter the file name for saving: ");
    fgets(file_name, sizeof(file_name), stdin);
    file_name[strcspn(file_name, "\n")] = '\0';

    FILE *file = fopen(file_name, "w");
    if (file != NULL) {
        fprintf(file, "%s", text);
        fclose(file);
        printf("\nText has been saved successfully\n");
    } else {
        printf("\nError opening file %s for writing\n", file_name);
    }
}

void load_text_from_file(char **text, int *text_len, int *text_size) {
    printf("\nEnter the file name for loading: ");
    char file_name[25];
    fgets(file_name, sizeof(file_name), stdin);
    file_name[strcspn(file_name, "\n")] = '\0';

    FILE *file = fopen(file_name, "r");
    if (file != NULL) {
        fseek(file, 0, SEEK_END);
        long file_size = ftell(file);
        fseek(file, 0, SEEK_SET);

        if (file_size == 0) {
            printf("\nThe file %s is empty\n", file_name);
            fclose(file);
            return;
        }

        char *loaded_text = (char *)calloc(file_size + 1, sizeof(char));
        if (loaded_text == NULL) {
            printf("\nMemory allocation failed\n");
            fclose(file);
            return;
        }

        fread(loaded_text, sizeof(char), file_size, file);
        loaded_text[file_size] = '\0';

        fclose(file);

        if (*text != NULL) {
            free(*text);
        }
        *text = loaded_text;
        *text_size = file_size + 1;
        *text_len = strlen(*text);

        printf("\nText has been loaded successfully\n");
    } else {
        printf("\nError opening file %s for reading\n", file_name);
    }
}

void print_loaded_text(const char *text) {
    printf("\nLoaded text:\n");
    printf("\n%s\n", text);
}

void clear_console() {
    printf("Press enter to clear the screen\n");
    char enter[2];
    fgets(enter, sizeof(enter), stdin);
    if (enter[0] == '\n') {
        system("cls");
        printf("\nCondole was cleared\n");
    }
}