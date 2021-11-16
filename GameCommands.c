// Copyright 2021 Diaconu Tudor-Gabriel

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "/home/student/GameCommands.h"

// Functia de adaugare a unei planete noi in galaxie
void
add_planet(cdll_list_t *planet_list)
{
	// initializarea noului nod(noii planete)
	node_data_t *n;
	char name[50] = {0};
	unsigned int index, shields_nr;

	// alocarea planetei si a listei de scuturi
	n = malloc(sizeof(node_data_t));
	DIE(!n, "malloc failed\n");
	n->sh_list = cdll_create(sizeof(int));

	scanf("%s %d %d", name, &index, &shields_nr);

	// cazul in care indexul este prea mare
	if (index > planet_list->size) {
		printf("Planet out of bounds!\n");
		// eliberarea listei de shield-uri alocate daca nu adaugam planeta
		cdll_free(&n->sh_list);
	} else {
		// initializarea kill-urilor si a numelui
		n->nr_kills = 0;
		memcpy(n->name, name, sizeof(name));
		n->name[strlen(name)] = '\0';

		// adaugarea shield-urilor cu valoarea 1
		int one = 1;
		for (unsigned int j = 0; j < shields_nr; j++) {
			cdll_add_node(n->sh_list, j, &one);
		}

		// adaugarea efectiva a planetei in galaxie pe indexul citit
		cdll_add_node(planet_list, index, n);

		printf("The planet %s has joined the galaxy.\n", n->name);
	}

	// eliberarea planetei, deoarece in add_node este facut un deep_copy
	free(n);
}

// Functia de afisare a informatiilor cerute despre o planeta
void
show_planet(cdll_list_t *planet_list)
{
	// citirea indexului
	unsigned int index;
	scanf("%d", &index);

	// cazul in care indexul este prea mare
	if (index >= planet_list->size || planet_list->size == 0) {
		printf("Planet out of bounds!\n");
	} else {
		// accesarea nodului din galaxie dorit
		node_t *curr_node = cdll_get_nth_node(planet_list, index);
		// accesarea informatiilor despre planeta dorita
		node_data_t *curr_planet = (node_data_t *)curr_node->data;
		// accesarea informatiilor despre planetele vecine
		node_data_t *next_planet = (node_data_t *)curr_node->next->data;
		node_data_t *prev_planet = (node_data_t *)curr_node->prev->data;

		// afisarea numelui si a vecinilor
		printf("NAME: %s\n", curr_planet->name);
		if (planet_list->size == 1) {
			printf("CLOSEST: none\n");
		} else if (planet_list->size == 2) {
			printf("CLOSEST: %s\n", next_planet->name);
		} else {
			printf("CLOSEST: %s and ", prev_planet->name);
			printf("%s\n", next_planet->name);
		}

		// afisarea listei de scuturi
		printf("SHIELDS: ");
		cdll_print_int_list(curr_planet->sh_list);

		// afisarea kill-urilor
		printf("KILLED: %d\n", curr_planet->nr_kills);
	}
}

// Functia de adaugare a unui scut in lista de scuturi
void
exp_planet(cdll_list_t *planet_list)
{
	// citirea indexului si a valorii
	unsigned int index, value;
	scanf("%d %d", &index, &value);

	// cazul in care indexul e prea mare
	if (index >= planet_list->size) {
		printf("Planet out of bounds!\n");
	} else {
		// accesarea planetei dorite dupa index
		node_t *curr_node = cdll_get_nth_node(planet_list, index);
		// accesarea informatiilor despre planeta dorita
		node_data_t *curr_planet = (node_data_t *)curr_node->data;

		// adaugarea efectiva a scutului in lista de scuturi
		int size = curr_planet->sh_list->size;
		cdll_add_node(curr_planet->sh_list, size, &value);
	}
}

// Functia de rotire a scuturilor unei planete
void
rotate_shields(cdll_list_t *planet_list)
{
	// citirea indexului, a numarului de rotatii si a sensului
	unsigned int index, units;
	char way;
	scanf("%d %c %d", &index, &way, &units);

	// cazul in care indexul e prea mare
	if (index >= planet_list->size) {
		printf("Planet out of bounds!\n");
	} else {
		// accesarea planetei dorite dupa index
		node_t *curr_node = cdll_get_nth_node(planet_list, index);
		// accesarea informatiilor despre planeta dorita
		node_data_t *curr_planet = (node_data_t *)curr_node->data;
		unsigned int shield_size = curr_planet->sh_list->size;

		// cazul in care directia citita nu este valida
		if (way != 'c' && way != 't') {
			printf("Not a valid direction!\n");
		} else if (way == 'c') {
			// rotirea de cate ori este cerut in sensul orar
			for(unsigned int j = 0; j < units % shield_size; j++) {
				curr_planet->sh_list->head = curr_planet->sh_list->head->prev;
			}
		} else if (way == 't') {
			// rotirea de cate ori este cerut in sens trigonometric
			for(unsigned int j = 0; j < units % shield_size; j++) {
				curr_planet->sh_list->head = curr_planet->sh_list->head->next;
			}
		}
	}
}

// Functia de upgrade pentru scutul unei planete
void
upgrade_shield(cdll_list_t *planet_list)
{
	// citirea indexelor pentru planeta si scut si a valorii
	unsigned int planet_ind, sh_ind, value;
	scanf("%d %d %d", &planet_ind, &sh_ind, &value);

	// accesarea planetei dorite dupa index
	node_t *curr_node = cdll_get_nth_node(planet_list, planet_ind);
	// accesarea informatiilor despre planeta dorita
	node_data_t *curr_planet = (node_data_t *)curr_node->data;
	// accesarea shield-ului dorit dupa index
	node_t *curr_shield = cdll_get_nth_node(curr_planet->sh_list, sh_ind);

	// cazul in care indexul planetei e prea mare
	if (planet_ind >= planet_list->size) {
		printf("Planet out of bounds!\n");
	} else if (sh_ind >= curr_planet->sh_list->size) {
		// cazul in care indexul scutului e prea mare
		printf("Shield out of bounds!\n");
	} else {
		// upgrade-ul efectiv pe scut
		*((int *)curr_shield->data) += value;
	}
}

// Functia de stergere a unui scut
void
remove_shield(cdll_list_t *planet_list)
{
	// citirea indexelor ale planetei si scutului
	unsigned int planet_ind, sh_ind;
	scanf("%d %d", &planet_ind, &sh_ind);

	// accesarea planetei dorite dupa index
	node_t *curr_node = cdll_get_nth_node(planet_list, planet_ind);
	// accesarea informatiilor despre planeta dorita
	node_data_t *curr_planet = (node_data_t *)curr_node->data;

	// cazul in care indexul planetei este prea mare
	if (planet_ind >= planet_list->size) {
		printf("Planet out of bounds!\n");

	} else if (sh_ind >= curr_planet->sh_list->size) {
		// cazul in care indexul scutului este prea mare
		printf("Shield out of bounds!\n");

	} else if (curr_planet->sh_list->size == 4) {
		// cazul in care planeta are doar 4 scuturi
		printf("A planet cannot have less than 4 shields!\n");

	} else {
		// accesarea scutului pe care il stergem in vederea eliberarii memoriei
		node_t *removed_shield = cdll_remove_node(curr_planet->sh_list, sh_ind);

		// eliberarea memoriei
		if(removed_shield != NULL) {
			free(removed_shield->data);
			free(removed_shield);
		}
	}
}

// Functia de BLH
void
eat_planet(cdll_list_t *planet_list)
{
	// ciirea indexului planetei
	unsigned int index;
	scanf("%d", &index);

	// cazul in care indexul e prea mare
	if(index >= planet_list->size) {
		printf("Planet out of bounds!\n");

	} else {
		// accesarea planetei pe care o stergem
		node_t *removed_node = cdll_remove_node(planet_list, index);
		// accesarea informatiilor despre planeta pe care o stergem
		node_data_t *removed_planet = (node_data_t *)removed_node->data;

		// printarea ceruta de enunt
		printf("The planet %s", removed_planet->name);
		printf(" has been eaten by the vortex.\n");

		// eliberarea memoriei pentru planeta stearsa
		if(removed_node != NULL) {
			cdll_free(&removed_planet->sh_list);
			free(removed_node->data);
			free(removed_node);
		}
	}
}

// Functia de coliziune a planetelor
void
colision_planets(cdll_list_t *planet_list)
{
	// citirea indecsilor celor doua planete
	unsigned int index1, index2;
	scanf("%d %d", &index1, &index2);

	// accesarea celor doua planete dorite dupa indecsi
	node_t *curr1 = cdll_get_nth_node(planet_list, index1);
	node_t *curr2 = cdll_get_nth_node(planet_list, index2);

	// accesarea informatiilor despre cele doua planete dorite
	node_data_t *planet1 = (node_data_t *)curr1->data;
	node_data_t *planet2 = (node_data_t *)curr2->data;

	unsigned int size1 = planet1->sh_list->size;
	unsigned int size2 = planet2->sh_list->size;

	// accesarea listelor de scuturi ale celor doua planete
	node_t *curr_shield1 = planet1->sh_list->head;
	node_t *curr_shield2 = planet2->sh_list->head;

	// parcurgerea si accesarea scuturilor ce intra in coliziune
	for(unsigned int i = 0; i < size1 / 4; i++) {
		curr_shield1 = curr_shield1->next;
	}
	for(unsigned int i = 0; i < (size2 / 4) * 3; i++) {
		curr_shield2 = curr_shield2->next;
	}

	// accesarea valorilor celor 2 scuturi din coliziune
	int *value1 = (int *)curr_shield1->data;
	int *value2 = (int *)curr_shield2->data;

	// cazul in care indecsii sunt prea mari
	if(index1 >= planet_list-> size || index2 >= planet_list->size) {
		printf("Planet out of bounds!\n");

	} else if (*value1 == 0 && *value2 != 0) {
		// cazul in care planeta 2 o omoara pe prima
		planet2->nr_kills++;
		*value2 -= 1;
		printf("The planet %s has imploded.\n", planet1->name);

		// accesarea planetei ce urmeaza a fi stearsa in vederea eliberarii memoriei
		node_t *removed_node = cdll_remove_node(planet_list, index1);
		node_data_t *removed_planet = (node_data_t *)removed_node->data;

		// eliberarea memoriei
		if(removed_node != NULL) {
			cdll_free(&removed_planet->sh_list);
			free(removed_node->data);
			free(removed_node);
		}

	} else if (*value2 == 0 && *value1 != 0) {
		// cazul in care planeta 1 o omoara pe cealalta
		planet1->nr_kills++;
		*value1 -= 1;
		printf("The planet %s has imploded.\n", planet2->name);

		// accesarea planetei ce urmeaza a fi stearsa in vederea eliberarii memoriei
		node_t *removed_node = cdll_remove_node(planet_list, index2);
		node_data_t *removed_planet = (node_data_t *)removed_node->data;

		// eliberarea memoriei
		if(removed_node != NULL) {
			cdll_free(&removed_planet->sh_list);
			free(removed_node->data);
			free(removed_node);
		}

	} else if (*value1 == 0 && *value2 == 0) {
		// cazul in care ambele planete sunt distruse
		printf("The planet %s has imploded.\n", planet1->name);
		printf("The planet %s has imploded.\n", planet2->name);

		// accesarea planetelor ce vor fi sterse
		// la a doua planeta am pus index - 1 pentru ca trebuie contorizat faptul
		// ca prima planeta va fi stearsa inaintea ei
		node_t *removed_node1 = cdll_remove_node(planet_list, index1);
		node_data_t *removed_planet1 = (node_data_t *)removed_node1->data;
		node_t *removed_node2 = cdll_remove_node(planet_list, index2 - 1);
		node_data_t *removed_planet2 = (node_data_t *)removed_node2->data;

		// eliberarea memoriei
		if(removed_node1 != NULL) {
			cdll_free(&removed_planet1->sh_list);
			free(removed_node1->data);
			free(removed_node1);
		}

		if(removed_node2 != NULL) {
			cdll_free(&removed_planet2->sh_list);
			free(removed_node2->data);
			free(removed_node2);
		}

	// cazul in care coliziunea se realizeaza fara "victime"
	} else {
		*value1 -= 1;
		*value2 -= 1;
	}
}
