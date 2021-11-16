// Copyright 2021 Diaconu Tudor-Gabriel

#ifndef GAMECOMMANDS_H_
#define GAMECOMMANDS_H_

#include "/home/student/CircularDoublyLinkedList.h"
#include "/home/student/utils.h"

void
add_planet(cdll_list_t *planet_list);

void
show_planet(cdll_list_t *planet_list);

void
exp_planet(cdll_list_t *planet_list);

void
rotate_shields(cdll_list_t *planet_list);

void
upgrade_shield(cdll_list_t *planet_list);

void
remove_shield(cdll_list_t *planet_list);

void
eat_planet(cdll_list_t *planet_list);

void
colision_planets(cdll_list_t *planet_list);

#endif  // GAMECOMMANDS_H_
