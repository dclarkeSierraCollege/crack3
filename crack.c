#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "md5.h"
#include "fileutil.h"

#define PASS_LEN 50
#define HASH_LEN 33


int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s hash_file dictionary_file\n", argv[0]);
        exit(1);
    }

    // Load hashes into memory using array of arrays
    int size;
    char **hashes = loadFileAA(argv[1], &size);
    if (!hashes) {
        printf("Error loading hash file\n");
        exit(1);
    }

    // Open dictionary file
    FILE *dict = fopen(argv[2], "r");
    if (!dict) {
        printf("Error opening dictionary file\n");
        freeAA(hashes, size);
        exit(1);
    }

    // Process each password
    char password[PASS_LEN];
    char hash[HASH_LEN];
    int found = 0;
    
    while (fgets(password, PASS_LEN, dict)) {
        // Remove newline if present
        password[strcspn(password, "\n")] = 0;
        
        // Generate MD5 hash
        md5String(password, hash);
        
        // Search for hash in array
        int index = linearSearchAA(hash, hashes, size);
        if (index >= 0) {
            printf("Found: %s -> %s\n", password, hash);
            found++;
        }
    }

    // Clean up
    fclose(dict);
    printf("Cracked %d of %d hashes\n", found, size);
    
    // Free memory using the provided function
    freeAA(hashes, size);

    return 0;
}
