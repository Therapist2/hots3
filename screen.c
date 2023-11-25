
#include "screen.h"

#include <stdio.h>

#include "networking.h"

void screen_clear(int connfd){
    char clear_cmd[] = "\033[H\033[J";
    net_send_single(connfd, clear_cmd, sizeof(clear_cmd)-1); // ommit \0
}

void screen_cur_set_single(int connfd, int pos_y, int pos_x){
    char msg_buf[20]; // TODO fat fingered
    int written = snprintf(msg_buf, sizeof(msg_buf), "\033[%d;%dH", pos_y, pos_x); // the return values excludes the final \0
    net_send_single(connfd, msg_buf, written);
}

void screen_cur_set(struct player players[PLAYERS_REQUIRED], int pos_y, int pos_x){
    for(int player_idx=0; player_idx < PLAYERS_REQUIRED; ++player_idx){
        struct player *player = &players[player_idx];

        screen_cur_set_single(player->connfd, pos_y, pos_x);
    }
}