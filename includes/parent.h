#define _POSIX_C_SOURCE 200809L

#ifndef PARENT_H
#define PARENT_H

#define MAX_CHILDREN 100

extern pid_t children[MAX_CHILDREN];
extern int child_count;

void spawn_child();
void kill_last_child();
void list_processes();
void kill_all_children();

#endif