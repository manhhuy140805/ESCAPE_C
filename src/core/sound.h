#ifndef SOUND_H
#define SOUND_H

#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>

// simple MCI
static void playBackgroundMusic(const char* path) {
    mciSendStringA("close bgm", NULL, 0, NULL);

    char cmd[512];
    snprintf(cmd, sizeof(cmd), "open \"%s\" type mpegvideo alias bgm", path);
    mciSendStringA(cmd, NULL, 0, NULL);
    mciSendStringA("play bgm repeat", NULL, 0, NULL);
}

static void stopBackgroundMusic() {
    mciSendStringA("stop bgm", NULL, 0, NULL);
    mciSendStringA("close bgm", NULL, 0, NULL);
}

static void playSoundEffect(const char* path) {
    mciSendStringA("close sfx", NULL, 0, NULL);

    char cmd[512];
    snprintf(cmd, sizeof(cmd), "open \"%s\" type mpegvideo alias sfx", path);
    mciSendStringA(cmd, NULL, 0, NULL);
    mciSendStringA("play sfx from 0", NULL, 0, NULL);
}

#endif // sOUND_H
