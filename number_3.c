#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1

enum status_file {
    error_file_name,
    error_open_file,
    error_write_to_file,
    error_reading_file,
};

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("error\n");
        return error_file_name;
    }
    FILE *file1 = fopen(argv[1], "rb");
    if (file1 == NULL) {
        printf("error\n");
        return error_open_file;
    }
    FILE *file2 = fopen(argv[2], "wb");
    if (file2 == NULL) {
        printf("error\n");
        return error_open_file;
    }

    char buff[BUFFER_SIZE];
    char bytes;

    while (bytes = fread(buff, sizeof(char), sizeof(buff), file1) > 0) {
        if (fwrite(buff, sizeof(char), bytes, file2) != bytes) {
            printf("error\n");
            fclose(file1);
            fclose(file2);
            return error_write_to_file;
        }
    }
    fclose(file1);
    fclose(file2);
    return 0;
}
