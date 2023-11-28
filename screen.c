
#include "screen.h"

#include <stdio.h>
#include <assert.h>

#include "networking.h"
#include "color.h"

void screen_clear_single(int connfd){
    char clear_cmd[] = "\033[H\033[J";
    screen_print_single(connfd, clear_cmd, sizeof(clear_cmd)-1); // ommit \0
}

void screen_clear(struct player players[PLAYERS_MAX]){
    for(int player_idx=0; player_idx < PLAYERS_MAX; ++player_idx){
        struct player *player = &players[player_idx];
        screen_clear_single(player->connfd);
    }
}

void screen_cur_set_single(int connfd, int pos_y, int pos_x){
    char msg_buf[11];
    int written = snprintf(msg_buf, sizeof(msg_buf), "\033[%d;%dH", pos_y+1, pos_x+1); // the return values excludes the final \0
    assert(written >= 0);
    assert((long unsigned int)written < sizeof(msg_buf)); // buffer is too small
    screen_print_single(connfd, msg_buf, written);
}

void screen_cur_set(struct player players[PLAYERS_MAX], int pos_y, int pos_x){
    assert(pos_y >= 0);
    assert(pos_x >= 0);
    for(int player_idx=0; player_idx < PLAYERS_MAX; ++player_idx){
        struct player *player = &players[player_idx];
        screen_cur_set_single(player->connfd, pos_y, pos_x);
    }
}

void screen_print_single(int connfd, char *msg, int msg_len){
    net_send_single(connfd, msg, msg_len);
}

void screen_print(struct player players[PLAYERS_MAX], char *msg, int msg_len){
    for(int player_idx=0; player_idx < PLAYERS_MAX; ++player_idx){
        struct player *player = &players[player_idx];
        if(player->bot){
            continue;
        }
        screen_print_single(player->connfd, msg, msg_len);
    }
}

void screen_print_empty_tile(struct player players[PLAYERS_MAX]){
    static char empty_tile[] = RESET_WITH_SPACE;
    screen_print(players, empty_tile, sizeof(empty_tile));
}
