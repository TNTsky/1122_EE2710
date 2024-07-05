#define _CRT_SECURE_NO_WARNINGS  // 禁用 fopen 的警告

#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        puts("Please use: cp <filename1> <filename2>\n");
        return 0;
    }

    FILE* source_file;
    if (fopen_s(&source_file, argv[1], "rb") != 0) {
        printf("Unable to open file %s\n", argv[1]);
        return 1;
    }

    FILE* destination_file;
    if (fopen_s(&destination_file, argv[2], "wb") != 0) {
        printf("Unable to open file %s\n", argv[2]);
        fclose(source_file);
        return 1;
    }

    char buffer[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source_file)) > 0) {
        fwrite(buffer, 1, bytes_read, destination_file);
    }

    fclose(source_file);
    fclose(destination_file);

    printf("File copied successfully.\n");
    return 0;
}
