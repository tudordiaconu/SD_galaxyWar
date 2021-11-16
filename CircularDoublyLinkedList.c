// Copyright 2021 Diaconu Tudor-Gabriel

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "/home/student/CircularDoublyLinkedList.h"
#include "/home/student/utils.h"

// Functiile utile aplicate listelor circulare duble inlantuite,
// preluate din laboratorul de CDLL

// Functia de creare a unei liste
cdll_list_t*
cdll_create(unsigned int data_size) {
	// alocarea listei
	cdll_list_t *list = malloc(sizeof(cdll_list_t));
	DIE(!list, "malloc failed\n");

	// initializarea listei
	list->head = NULL;
	list->data_size = data_size;
	list->size = 0;
	return list;
}

// Functia de afisare a unei liste de nr intregi
void
cdll_print_int_list(cdll_list_t* list)
{
	// cazul in care lista nu exista
	if(list == NULL)
		return;

	// accesarea head-ului listei pentru parcurgere
	node_t *curr = list->head;
	unsigned int index = 0;

	// parcurgerea listei si afisarea informatiei din noduri
	while(index < list->size) {
		printf("%d ", *((int *)curr->data));
		curr = curr->next;
		++index;
	}

	printf("\n");
}

// Functia de extragere a unui nod anume, fara a-l sterge
node_t*
cdll_get_nth_node(cdll_list_t* list, unsigned int n)
{
	// accesarea head-ului listei pentru parcurgere
	node_t *curr = list->head;

	// cazul in care lista nu exista
	if (list == NULL || list->head == NULL)
		return NULL;

	// parcurgerea listei pana la indexul transmis ca argument al functiei
	// astfel ajungem la nodul dorit
	unsigned int index = 0;
	while(index < n % list->size){
		curr = curr->next;
		++index;
	}

	// returnarea nodului dorit
	return curr;
}

// Functia de adaugare a unui nod in lista pe o pozitie data ca argument
void
cdll_add_node(cdll_list_t* list, unsigned int n, const void* data)
{
	// cazul in care lista nu exista
	if (list == NULL)
		return;

	// alocarea noului nod si a informatiei din el
	node_t *new_node = (node_t *)malloc(sizeof(node_t));
	DIE(!new_node, "malloc failed\n");

	new_node->data = malloc(list->data_size);
	DIE(!new_node->data, "malloc failed\n");
	memcpy(new_node->data, data, list->data_size);

	// initializarea next-ului si a prev-ului pentru noul nod
	new_node->next = NULL;
	new_node->prev = NULL;

	// cazul in care nodul adaugat este primul element al listei
	// in acest caz, next si prev vor pointa catre nodul insusi
	if (list->size == 0) {
		list->head = new_node;
		list->head->next = list->head;
		list->head->prev = list->head;

	} else if (n == 0) {
		// cazul in care se doreste adaugarea pe prima pozitie a listei

		// next-ul ultimului element al listei va pointa catre noul nod
		list->head->prev->next = new_node;
		// prev-ul noului element va pointa catre ultimul element al listei
		new_node->prev = list->head->prev;
		// next-ul noului element va pointa catre head, devenind astfel primul
		new_node->next = list->head;
		// prev-ul head-ului va pointa catre noul nod, cel de pe prima pozitie
		list->head->prev = new_node;
		// noul head al listei va deveni noul nod, fiind pe prima pozitie
		list->head = new_node;

	} else if (n >= list->size) {
		// cazul in care adaugam pe ultima pozitie a listei

		// procedeul este similar cu cel de adaugare pe prima pozitie, insa
		// nu mai mutam head-ul pe noul nod, pt ca vrem ca noul nod sa fie ultimul
		list->head->prev->next = new_node;
		new_node->prev = list->head->prev;
		new_node->next = list->head;
		list->head->prev = new_node;

	} else {
		// cazul in care adaugam nodul in interiorul listei

		// accesarea head-ului pentru parcurgerea listei
		node_t *curr = list->head;

		// parcurgerea listei pana la pozitia dorita
		for(unsigned int i = 0; i < n - 1; i++) {
			curr = curr->next;
		}
		node_t *nxt = curr->next;

		// practic inseram noul nod intre nxt si curr, asa ca vom crea legaturile
		// corespunzatoare intre new_node si noii sai "vecini"
		curr->next = new_node;
		new_node->prev = curr;
		new_node->next = nxt;
		nxt->prev = new_node;
	}
	list->size++;
}

// Functia de stergere a unui nod de pe o anumita pozitie trimisa ca argument
node_t*
cdll_remove_node(cdll_list_t* list, unsigned int n)
{
	// cazul in care lista nu exista sau e goala
	if (list == NULL || list->size == 0)
		return NULL;

	// cazul in care lista are un singur element
	if (list->size == 1) {
		// practic stergem head-ul facandu-l NULL
		node_t *z = list->head;
		list->head = NULL;
		list->size--;
		return z;

	} else if (n == 0) {
		// cazul in care se vrea stergerea elementului de pe prima pozitie

		// ne luam prin doua variabile primul si ultimul element al listei
		node_t *p = list->head;
		node_t *last = list->head->prev;

		// refacem legaturile

		// mutam head-ul cu o pozitie mai la dreapta
		list->head = p->next;
		// facem next-ul ultimului element sa pointeze catre noul head
		last->next = list->head;
		// facem prev-ul noului head sa pointeze catre ultimul element
		list->head->prev = last;
		list->size--;
		return p;

	} else if (n >= list->size - 1 && list->size > 1) {
		// cazul in care vrem sa stergem elementul de pe ultima pozitie

		// accesam head-ul listei pentru parcurgerea ei
		node_t *rem = list->head;

		// parcurgem lista pana la nodul dinaintea celui pe care il stergem
		for(unsigned int i = 0; i < list->size - 2; i++) {
			rem = rem->next;
		}

		// in variabila ret luam nodul pe care il stergem
		node_t *ret = rem->next;

		// refacem legaturile in vederea stergerii
		rem->next = list->head;
		list->head->prev = rem;
		list->size--;

		return ret;

	} else {
		// cazul stergerii fara nicio exceptie

		// accesarea head-ului in vederea parcurgerii listei
		node_t *curr;
		curr = list->head;

		// parcurgerea listei pana la nodul pe care vrem sa il stergem
		for(unsigned int i = 0; i < n; i++) {
			curr = curr->next;
		}

		// luam in 2 variabile vecinii nodului pe care vrem sa il stergem
		node_t *nxt = curr->next;
		node_t *prv = curr->prev;

		// refacem legaturile
		prv->next = nxt;
		nxt->prev = prv;
		list->size--;

		return curr;
	}
}

// Functia de eliberare a memoriei alocate pentru o lista generica
void
cdll_free(cdll_list_t** pp_list)
{
	// cazul in care lista nu exista
	if (*pp_list == NULL)
		return;

	// accesarea head-ului in vederea parcurgerii listei
	node_t *curr = (*pp_list)->head;
	unsigned int index = 0;

	if (curr != NULL) {
		// parcurgerea fiecarui nod din lista
		while (index != (*pp_list)->size - 1) {
			// luam un nod auxiliar care sa ne ajute la incrementare
			node_t *aux = curr->next;

			// eliberarea informatiei din nod si a nodului efectiv
			free(curr->data);
			free(curr);

			// incrementarea
			curr = aux;
			++index;
		}

		// eliberarea ultimului nod din lista
		free(curr->data);
		free(curr);
	}

	// eliberarea listei
	free(*pp_list);
	*pp_list = NULL;
}
