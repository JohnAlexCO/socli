#define root_name "socli"
#define root_version "0.0.0"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include "../generated/help.h"
#include "file.c"
#include "lock.c"
#include "socli_main.c"

void help();
void version();
void reset();
void login_bluesky();
void login_mastodon();
void socli_main();

int main (int argc, char **argv) {
    switch(argc) {
        default: help(); exit(1);
        case 1: socli_main(); exit(0);
        case 2:
            if (strcmp(argv[1], "-v")==0)           { version(); exit(0); }
            if (strcmp(argv[1], "--version")==0)    { version(); exit(0); }
            if (strcmp(argv[1], "version")==0)      { version(); exit(0); }
            if (strcmp(argv[1], "-h")==0)           { help(); exit(0); }
            if (strcmp(argv[1], "--help")==0)       { help(); exit(0); }
            if (strcmp(argv[1], "help")==0)         { help(); exit(0); }
            if (strcmp(argv[1], "reset")==0)        { reset(); exit(0); }
            if (strcmp(argv[1], "bluesky")==0)      { login_bluesky(); exit(0); }
            if (strcmp(argv[1], "mastodon")==0)     { login_mastodon(); exit(0); }
            printf("error, unknown argument \"%s\"\nRun `socli help` for a quick-use guide\n", argv[1]); exit(0);
    }
}

void help(){ printf("%s %s, Modula.dev\n%s\n", root_name, root_version, root_help); }
void version() { printf("%s %s, Modula.dev\n", root_name, root_version); }
void reset(){
    #ifdef _WIN_32
        system("del .\\.bsky");
        system("del .\\.mastodon");
        system("del .\\.rss");
    #else
        system("rm ./.bsky");
        system("rm ./.mastodon");
        system("rm ./.rss");
    #endif
}

void login_bluesky(){
    char key[64]; char handle[128]; char pwd[128];
    char buffer[512];
    printf("    Bluesky handle: "); fgets(handle, sizeof(handle), stdin);
    printf("    password:       "); fgets(pwd, sizeof(pwd), stdin);
    printf("    socli-key:      "); fgets(key, sizeof(key), stdin);
    sprintf(buffer, "%s\n%s\0", handle, pwd);
    char *locked = lock(key, buffer);
    file_write(".bsky", locked, sizeof(buffer));
    #ifdef _WIN_32
        system("cls");
    #else
        system("clear");
    #endif
}

void login_mastodon(){
    char key[64]; char server[256]; char handle[128]; char pwd[128];
    char buffer[512];
    printf("    Mastodon server: "); fgets(server, sizeof(server), stdin);
    printf("    Mastodon handle: "); fgets(handle, sizeof(handle), stdin);
    printf("    password:        "); fgets(pwd, sizeof(pwd), stdin);
    printf("    socli-key:       "); fgets(key, sizeof(key), stdin);
    sprintf(buffer, "%s\n%s\n%s", server, handle, pwd);
    char *locked = lock(key, buffer);
    file_write(".mastodon", locked, sizeof(buffer));
    #ifdef _WIN_32
        system("cls");
    #else
        system("clear");
    #endif
}