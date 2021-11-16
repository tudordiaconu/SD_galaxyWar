// Copyright 2021 Diaconu Tudor-Gabriel

#ifndef CIRCULARDOUBLYLINKEDLIST_H_
#define CIRCULARDOUBLYLINKEDLIST_H_

typedef struct node_t node_t;
struct node_t {
	void *data;
	node_t *prev, *next;
};

typedef struct cdll_list_t cdll_list_t;
struct cdll_list_t {
	node_t *head;
	unsigned int data_size;
	unsigned int size;
};

typedef struct node_data_t node_data_t;
struct node_data_t {
	char name[50];
	cdll_list_t *sh_list;
	unsigned int nr_kills;
};

cdll_list_t*
cdll_create(unsigned int data_size);

void
cdll_print_int_list(cdll_list_t* list);

node_t*
cdll_get_nth_node(cdll_list_t* list, unsigned int n);

void
cdll_add_node(cdll_list_t* list, unsigned int n, const void* data);

node_t*
cdll_remove_node(cdll_list_t* list, unsigned int n);

void
cdll_free(cdll_list_t** pp_list);

#endif  // CIRCULARDOUBLYLINKEDLIST_H_
