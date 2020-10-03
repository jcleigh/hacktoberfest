#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

// TODO implement obey flags
// TODO implement remember pop (displays last item but also removes it
// TODO implement remember help (displays help text)
// TODO implement display all
// TODO implement clear history

// flags -p and -c
struct application_flags {
    int pop;
    int clear;
};

int parse_args(int argc, char** argv, struct application_flags* app_flags);
char* get_dir_path();
char* get_file_path(char* dir_path, char* file_name);
void create_dir_if_needed(char* path);
void get_last_entry(char* file_path);
void create_entry(char* file_path, char* tmp_file_path, int argc, char** argv);

int main (int argc, char** argv) {
    struct application_flags app_flags = {0};

    int useless_args = parse_args(argc, argv, &app_flags);

    argv += useless_args;
    argc -= useless_args;

    char* dir_path = get_dir_path();
    create_dir_if_needed(dir_path);
    char* file_path = get_file_path(dir_path, "/notes.txt");

    if (argc > 0) {
        char* tmp_file_path = get_file_path(dir_path, "/tmp.txt");
        create_entry(file_path, tmp_file_path, argc, argv);
    } else {
        get_last_entry(file_path);
    }
}

int parse_args(int argc, char** argv, struct application_flags* app_flags) {
    int i = 1;
    while (i < argc) {
        if(argv[i][0] != '-')
            break;
        for (int j = 1; j < strlen(argv[i]); ++j) {
            if (argv[i][j] == 'c')
                app_flags->clear = 1;
            if (argv[i][j] == 'p')
                app_flags->pop = 1;
        }

        ++i;
        if(strcmp(argv[i], "--"))
            break;
    }
    return i;
}

void create_entry(char* file_path, char* tmp_file_path, int argc, char** argv) {
    FILE* tmp = fopen(tmp_file_path, "w");
    FILE* fp = fopen(file_path, "r");

    if (tmp == NULL || fp == NULL) {
        fprintf(stderr, "Error while opening file.\n");
        return;
    } 
    for (int i = 0; i < argc; ++i) {
        fprintf(tmp, "%s ", argv[i]);
    }
    fputc('\n', tmp);

    int c;
    while ((c = fgetc(fp)) != EOF) 
        fputc(c, tmp);

    rename(tmp_file_path, file_path);

    fclose(tmp);
    fclose(fp);
}

void get_last_entry(char* file_path) {
    FILE* fp = fopen(file_path, "r");

    if (fp == NULL) {
        fprintf(stderr, "Cannot open reminder file.\n");
        return;
    } 
    int c = fgetc(fp);
    while(c != EOF && c != '\n') {
        putchar(c);
        c = fgetc(fp);
    }
    putchar('\n');

    fclose(fp);
}

char* get_dir_path() {
    char* home = getenv("HOME");
    char* remember;
    int len_home = strlen(home);
    if (home[len_home - 1] == '/') {
        remember = ".remember";
    } else {
        remember = "/.remember";
    }
    int required_length = (len_home + strlen(remember) + 1);
    char* dir_path = malloc(sizeof(char) * required_length);
    strcat(dir_path, home);
    strcat(dir_path, remember);

    return dir_path;
}

char* get_file_path(char* dir_path, char* file_name) {
    int required_length = (strlen(dir_path) + strlen(file_name) + 1);
    char* file_path = malloc(sizeof(char) * required_length);
    strcat(file_path, dir_path);
    strcat(file_path, file_name);

    return file_path;
}

void create_dir_if_needed(char* path) {
    struct stat sd = {0};
    if (stat(path, &sd) == -1) {
        mkdir(path, 0755);
    }
}
