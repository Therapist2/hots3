
#ifndef ERRORS_H
#define ERRORS_H

enum {
    ERR_NONE = 0,
    ERR_CANT_CREATE_SOCKET = 1,
    ERR_CANT_BIND_SOCET = 2,
    ERR_CANT_LISTEN = 3,
    ERR_CANT_SET_REUSEADDR = 4,
    ERR_COULD_NOT_FIND_SPAWN_SPOT = 5,
    ERR_CANT_GET_FCNTL_FOR_CLIENT_SOCKET = 6,
    ERR_CANT_SET_FCNTL_FOR_CLIENT_SOCKET = 7,
    ERR_COULD_NOT_SPAWN_TOWER = 8,
    ERR_BAD_COMMAND_LINE_ARGS = 9,
    ERR_COULD_NOT_SPAWN_WALL = 10,
};

#endif
