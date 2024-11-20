void socli_main() {
    char command_path[1024];
    char key[64];
    printf("    pass-key: "); fgets(key, sizeof(key), stdin);
    bool bluesky = file_exists(".bsky");
    bool mastodon = file_exists(".mastodon");
    /* First, get our feeds */
    if (bluesky) {
        /* TODO: fix relative path issue; path should be known, not just hoping cwd is good */
        #ifdef _WIN_32
            sprintf(command_path, ".\\bluesky -t %s\0", key);
        #else
            sprintf(command_path, "./bluesky -t %s\0", key);
        #endif
        system(command_path);
    }
    if (mastodon) {
        #ifdef _WIN_32
            sprintf(command_path, ".\\mastodon -t %s\0", key);
        #else
            sprintf(command_path, "./mastodon -t %s\0", key);
        #endif
        system(command_path);
    }
}