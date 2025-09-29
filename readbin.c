#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#define MAX_KEY_LEN 32
#define MAX_TEXT_LEN 1024

char* generate_key(int length) {
    const char* charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int charset_len = 36;
    char* key = malloc(length + 1);
    if (!key) return NULL;
    time_t now = time(NULL);
    struct tm* infoTime = localtime(&now);
    int year = infoTime->tm_year + 1900;
    int month = infoTime->tm_mon + 1;
    int day = infoTime->tm_mday;
    int hour = infoTime->tm_hour;
    int min = infoTime->tm_min;
    int sec = infoTime->tm_sec;
    printf("Year: %d, Month: %d, Day: %d, Hour: %d, Minute: %d, Second: %d\n", year, month, day, hour, min, sec);
    int date_sum = year + month + day + hour + min + sec;
    for (int i = 0; i < length; i++) {
        int state = (state * 31 + i + date_sum) % charset_len;
        key[i] = charset[state];
    }
    key[length] = '\0';
    return key;
}
char** load_words(const char* filename, int* out_count) {
    FILE* fp = fopen(filename, "rb");
    if (!fp) {
        perror("Error opening file");
        return NULL;
    }

    int capacity = 128;
    int count = 0;
    char** words = malloc(capacity * sizeof(char*));
    if (!words) {
        fclose(fp);
        return NULL;
    }

    while (1) {
        uint8_t len;
        if (fread(&len, sizeof(uint8_t), 1, fp) != 1) break;

        char* word = malloc(len + 1);
        if (!word || fread(word, sizeof(char), len, fp) != len) {
            free(word);
            break;
        }
        word[len] = '\0';

        if (count >= capacity) {
            capacity *= 2;
            char** temp = realloc(words, capacity * sizeof(char*));
            if (!temp) {
                free(word);
                break;
            }
            words = temp;
        }

        words[count++] = word;
    }

    fclose(fp);
    *out_count = count;
    return words;
}

void free_words(char** words, int count) {
    for (int i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
}

int find_index(const char* word_to_find, char** data, int count) {
    for (int i = 0; i < count; i++) {
        if (strcmp(data[i], word_to_find) == 0)
            return i;
    }
    return -1;
}

char* encrypt(const char* text, const char* key, char** data, int count) {
    int key_len = strlen(key);
    char* result = malloc(MAX_TEXT_LEN * 32);
    result[0] = '\0';

    for (int i = 0; text[i] != '\0'; i++) {
        int c = (unsigned char)text[i];
        int k = (unsigned char)key[i % key_len];
        int index = (c + k) % count;
        strcat(result, data[index]);
        strcat(result, " ");
    }

    return result;
}

char* decrypt(const char* text, const char* key, char** data, int count) {
    int key_len = strlen(key);
    char* result = malloc(MAX_TEXT_LEN);
    if (!result) return NULL;

    char* text_copy = strdup(text);
    if (!text_copy) {
        free(result);
        return NULL;
    }
    char* token = strtok(text_copy, " ");
    int i = 0;
    int result_len = 0;
    while (token) {
        int index = find_index(token, data, count);
        if (index < 0) {
            free(text_copy);
            free(result);
            return NULL;
        }
        int k = (unsigned char)key[i % key_len];
        result[result_len++] = (char)((index - k + count) % count);
        token = strtok(NULL, " ");
        i++;
    }

    result[result_len] = '\0';
    free(text_copy);
    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 4 || (strcmp(argv[1], "-e") != 0 && strcmp(argv[1], "-d") != 0)) {
        printf("Usage: %s -e|-d <file.bin> <message|encrypted_text>\n", argv[0]);
        return 1;
    }

    int count;
    char** data = load_words(argv[2], &count);
    if (!data) return 1;

    if (strcmp(argv[1], "-e") == 0) {
        char* key = generate_key(10);
        if (!key) {
            free_words(data, count);
            return 1;
        }
        printf("Key: %s\n", key);
        char* encrypted_result = encrypt(argv[3], key, data, count);
        printf("Result: %s\n", encrypted_result);
        free(encrypted_result);
        free(key);
    } else {
        printf("Enter the key used: ");
        char input_key[MAX_KEY_LEN];
        fgets(input_key, MAX_KEY_LEN, stdin);
        input_key[strcspn(input_key, "\n")] = '\0';
        char* decrypted_result = decrypt(argv[3], input_key, data, count);
        if (decrypted_result != NULL) {
            printf("Original text: %s\n", decrypted_result);
            free(decrypted_result);
        } else {
            printf("Error: Decryption failed. An unknown word was found or key is incorrect.\n");
        }
    }
    free_words(data, count);
    return 0;
}
