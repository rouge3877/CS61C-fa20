#include "list.h"

/* Add a node to the end of the linked list. Assume head_ptr is non-null. */
void append_node (node** head_ptr, int new_data) {
	/* First lets allocate memory for the new node and initialize its attributes */
	/* YOUR CODE HERE */
	node* new_node = (node*)malloc(sizeof(node));
	if (new_node == NULL) {
        printf("Memory allocation failed!");
        exit(1);
    }
	new_node->next = NULL;
	new_node->val = new_data;
	/* If the list is empty, set the new node to be the head and return */
	if (*head_ptr == NULL) {
		/* YOUR CODE HERE */
		*head_ptr = new_node;
		return;
	}
	node* curr = *head_ptr;
	while (curr->next != NULL) {
		curr = curr->next;
	}
	/* Insert node at the end of the list */
	curr->next = new_node;
}

/* Reverse a linked list in place (in other words, without creating a new list).
   Assume that head_ptr is non-null. */
void reverse_list (node** head_ptr) {
	node* prev = NULL;
	node* curr = *head_ptr;
	node* next = NULL;
	while (curr != NULL) {
		/* INSERT CODE HERE */
		prev = curr;
		curr = curr->next;
		prev->next = next;
		next = prev;
	}
	/* Set the new head to be what originally was the last node in the list */
	*head_ptr = prev;
}



