#include <stdio.h>
#include <stdlib.h>


typedef struct node node_t;
struct node{
	int value;
	node_t *next;
};


static node_t *nodeNew(node_t *next, int value) {

	node_t *node = malloc(sizeof(node_t));
	if (node != NULL) {
		node->next = next;
		node->value = value;
	}
	return node;
}

static void printList(char *label, node_t *list, int level) {
	int i;
	node_t *current;
	for (i = 0; i < level; i++) {
		printf("\t");
	}
	printf("%s : ", label);
	current = list;
	while (current != NULL) {
		printf("%d ", current->value);
		current = current->next;
	}
	printf("\n");
}

static node_t *splitlist(node_t *head) {
	node_t *slow = head;
	node_t *fast = head->next;
	node_t *ndHead;

	while (fast != NULL && fast->next != NULL) {
		fast = fast->next->next;
		slow = slow->next;
	}
	ndHead = slow->next;
	slow->next = NULL;
	return ndHead;
}



static node_t *merge(node_t *a, node_t *b){




}





static node_t *mergesort(node_t *head, int level) {
	
	
	if (head == NULL || head->next == NULL) {
		return head;
	}

	node_t *ndHead = splitlist(head);
	printList("1st part", head, level);

	mergesort(head, level + 1))

	printList("1st part sorted:", head, level);

	printList("2nd part", ndHead, level);

	ndHead = mergesort(ndHead, level + 1);
	printList("2nd part sorted: ", ndHead, level);


}



int main(int argc, char **argv) {
	int i;
	int value;
	node_t *list = NULL;

	for (i = 0; i < 8; i++) {
		value = rand() % 100;
		list = nodeNew(list, value);
	}
	printList("unsorted", list, 0);



}