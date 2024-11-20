char *lock(char *key, char *content);
char *unlock(char *key, char *content);
#ifdef LOCK_TEST
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
#define test_content "[127.0.0.0] -- This is the test case\0"
int main (int argc, char **argv) {
    int i; if (argc == 1) { exit(1); }
    printf("... testing %d cases\n", argc-1);
    for(i=0;i<argc;i++) {
        char *locked = lock(argv[i], test_content);
        char *unlocked = unlock(argv[i], locked);
        printf("%d: %s\n    locked %s\n    unlocked %s\n",
            i, argv[i], locked, unlocked
        );
    }
}
#endif

char *lock(char *key, char *content) {
    char *result = malloc(sizeof(char)*1024);
    int klen = strnlen(key, 64);
    int len =  strnlen(content, 1024);
    int i=0; int k=0;
    for(i=0; i<len;i++){
        k = (k + 1) % klen;
        int c = (int)content[i] -1;
        int b = (c ^ key[k]) % 255;
        result[i] = (char)b;
    }   result[len] = 0;
    return result;
}

char *unlock(char *key, char *content) {
    char *result = malloc(sizeof(char)*1024);
    int klen = strnlen(key, 64);
    int len = strnlen(content, 1024);
    int i; int k=0;
    for(i=0; i<len;i++){
        k = (k + 1) % klen;
        int c = (int)content[i];
        int b = (c ^ key[k]) % 255;
        result[i] = (char)b +1;
    }   result[len] = 0;
    return result;
}
