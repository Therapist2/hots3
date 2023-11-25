
#include <stdio.h>
#include <string.h>

#include "errors.h"
#include "networking.h"
#include "player.h"
#include "settings.h"
#include "screen.h"

int main(void){
    int err;

    // init socket

    int sockfd;
    struct sockaddr_in servaddr;

    if((err = create_server(&sockfd, &servaddr, PORT, LISTEN))){
        return err;
    }

    // lobby

    int player_count = 0;
    struct player players[PLAYERS_REQUIRED];

    while(player_count < PLAYERS_REQUIRED){
        struct player *player = &players[player_count];
        player_init_mem(player);

        printf("waiting for connection\n");
    
        player->connfd = accept(sockfd, (struct sockaddr *) &player->sock, &player->sock_len);
        if(player->connfd < 0){
            printf("player could not connect\n");
            continue;
        }

        player_init_telnet(player);

        printf("player connected\n");

        player_count += 1;
    }

    // spawn players

    for(int player_idx=0; player_idx < PLAYERS_REQUIRED; ++player_idx){
        struct player *player = &players[player_idx];
        player_spawn(player, players);
    }

    // clear screen

    for(int player_idx=0; player_idx < PLAYERS_REQUIRED; ++player_idx){
        struct player *player = &players[player_idx];
        screen_clear(player->connfd);
    }

    // print players

    for(int player_idx=0; player_idx < PLAYERS_REQUIRED; ++player_idx){
        struct player *player = &players[player_idx];

        player_draw(player, players);
    }

    // game loop

    while(1){

        // process input

        for(int player_idx=0; player_idx < PLAYERS_REQUIRED; ++player_idx){
            struct player *player = &players[player_idx];
            
            char action;
            int bytes = net_recv_1B(player->connfd, &action);
            if(bytes <= 0){
                continue;
            }

            // printf("received from `%d`: `%c` (%d)\n", player->connfd, action, (int)action);

            player_process_action(player, action, players);
        }
    }

    return 0;
}
