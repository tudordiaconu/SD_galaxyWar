// Copyright 2021 Diaconu Tudor-Gabriel

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "/home/student/CircularDoublyLinkedList.h"
#include "/home/student/GameCommands.h"

int main(void)
{
	// citirea numarului de operatii
	int m;
	scanf("%d", &m);

	// crearea galaxiei
	cdll_list_t *planet_list;
	planet_list = cdll_create(sizeof(node_data_t));

	for(int i = 0; i < m; i++) {
		// citirea comenzii
		char command[16];
		scanf("%s ", command);

		// implementarea comenzilor posibile
		if(strcmp(command, "ADD") == 0) {
			add_planet(planet_list);
		}

		if(strcmp(command, "SHW") == 0) {
			show_planet(planet_list);
		}

		if(strcmp(command, "EXP") == 0) {
			exp_planet(planet_list);
		}

		if(strcmp(command, "ROT") == 0) {
			rotate_shields(planet_list);
		}

		if(strcmp(command, "UPG") == 0) {
			upgrade_shield(planet_list);
		}

		if(strcmp(command, "RMV") == 0) {
			remove_shield(planet_list);
		}

		if(strcmp(command, "BLH") == 0) {
			eat_planet(planet_list);
		}

		if(strcmp(command, "COL") == 0) {
			colision_planets(planet_list);
		}
	}

	// accesarea galaxiei pentru eliberarea memoriei
	node_t *curr = planet_list->head;

	for(unsigned int i = 0; i < planet_list->size; i++) {
		// accesarea informatiilor despre fiecare planeta
		node_data_t *curr_planet = (node_data_t *)curr->data;

		// eliberarea listei de scuturi
		cdll_free(&curr_planet->sh_list);
		curr = curr->next;
	}

	// eliberarea galaxiei
	cdll_free(&planet_list);

	return 0;
}
