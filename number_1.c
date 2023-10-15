#include <stdio.h>
#include <stdlib.h>

enum status_file {
    error_file_name,
    error_open_file,
    error_write_to_file,
    error_reading_file,
};

void print_file_state(FILE* files) {
    printf("__pad5: %ld ", files->__pad5);
    printf("_chain: %p ", files->_chain);
    printf("_codecvt: %p ", files->_codecvt);
    printf("_cur_column: %d ", files->_cur_column);
    printf("_fileno: %d ", files->_fileno);
    printf("_flags: %d ", files->_flags);
    printf("_freeres_buf: %p ", files->_freeres_buf);
    printf("_freeres_list: %p ", files->_freeres_list);
    printf("_IO_backup_base: %p ", files->_IO_backup_base);
    printf("_IO_buf_base: %p ", files->_IO_buf_base);
    printf("_IO_buf_end: %p ", files->_IO_buf_end);

    printf("_IO_read_base: %p ", files->_IO_read_base);
    printf("_IO_read_end: %p ", files->_IO_read_end);
    printf("_IO_read_ptr: %p ", files->_IO_read_ptr);
    printf("_IO_save_base: %p ", files->_IO_save_base);
    printf("_IO_save_end: %p ", files->_IO_save_end);
    printf("_IO_write_base: %p ", files->_IO_write_base);
    printf("_IO_write_end: %p ", files->_IO_write_end);
    printf("_IO_write_ptr: %p ", files->_IO_write_ptr);
    printf("_lock: %p ", files->_lock);
    printf("_markers: %p ", files->_markers);
    printf("_mode: %d ", files->_mode);
    printf("_offset: %ld ", files->_offset);

    printf("_shortbuf: %p ", files->_shortbuf);
    printf("_unused2: %p ", files->_unused2);
    printf("_vtable_offset: %d ", files->_vtable_offset);
    printf("_wide_data: %p ", files->_wide_data);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("enter the file name\n");
        return error_file_name;
    }

    FILE *file = fopen(argv[1], "wb+");
    if (file == NULL) {
        printf("error\n");
        return error_open_file;
    }

    char array[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};

    if (fwrite(array, sizeof(array[0]), sizeof(array) / sizeof(array[0]), file) != sizeof(array) / sizeof(array[0])) {
        printf("error\n");
        fclose(file);
        return error_write_to_file;
    }

    fseek(file, 0, SEEK_SET);
    int size_file = sizeof(array) / sizeof(array[0]);
    char arr[11] = {};

    if (fread(arr, sizeof(char), 11, file) != 11) {
        printf("error\n");
        return error_reading_file;
    }

    for (int i = 0; i < size_file; i++) {
        printf("%d\n", arr[i]);
        print_file_state(file);
        printf("\n");
    }

    fclose(file);

    FILE* file_read = fopen(argv[1], "rb");
    if (file_read == NULL) {
        printf("error\n");
        return error_open_file;
    }

    fseek(file_read, 3, SEEK_SET);
    char array_result[4] = {0};

    if (fread(array_result, sizeof(char), 4, file_read) != 4) {
        printf("error\n");
        fclose(file_read);
        return error_reading_file;
    }   

    for (int i = 0; i < 4; ++i) {
        printf("%d ", array_result[i]);
    }
    printf("\n");
    fclose(file_read);
    return 0;
}
