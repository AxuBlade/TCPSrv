cmake_minimum_required (VERSION 2.6)


add_library (commands STATIC command_put.c command_get.c command_ls.c command_move.c command_rename.c command_rm.c command_quit.c)