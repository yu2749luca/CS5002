/*
 * @file linked_array.c
 *
 * This file provides the definitions for functions that operate on
 * chains of linked nodes. Methods can be used in one of two ways.
 *
 * If the empty chain of nodes is represented by a NULL pointer,
 * then add the first item by setting the pointer to the first item.
 * Delete the final node by freeing it and setting the pointer to NULL.
 *
 * If the empty node chain is represented by a dummy first node,
 * then add the first item by calling addAfterLinkedNode() with the
 * dummy node and the first node, delete the last item by calling
 * deleteAfterLinkedNode() with the dummy first node, and get
 * the size excluding the dummy node by passing the dummy node's
 * next pointer to getLinkedSize().
 *
 * @since 2018-10-24
 * @author philip gust
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "linked_node.h"


/**
 * Create and initialize new node.
 *
 * @param data the data for the node.
 * @return Node with fields set to NULL
 */
LinkedNode* newLinkedNode(const char* data) {
	// allocate node
	LinkedNode* newNode = malloc(sizeof(LinkedNode));

	// initialize fields
	newNode->data = (data == NULL) ? NULL : strdup(data);
	newNode->next = NULL;

	//***
	newNode->prev = NULL;

	return newNode;

}

/**
 * Freeing node storage. The node must be removed from its chain
 * by calling deleteNode() first. A NULL node value is ignored.
 *
 * @param node the LinkedListNode to delete
 */
void deleteLinkedNode(LinkedNode* node) {

	if (node != NULL) {
		// free pointer to data string
		free(node->data);  // free ok with NULL
		node->data = NULL;

		// reset the next pointer
		node->next = NULL;

		// ****reset the prev pointer
		node->prev = NULL;

		// now free the node
		free(node);
	}
}

/**
 * Return the node at the Kth position in the chain relative to the
 * input node. If there are fewer than K items in the list, returns NULL.
 *
 * @param node the first node in the chain
 * @param k the index
 * @return the Kth node from input node or NULL if fewer than K items
 */
LinkedNode *getLinkedNodeAt(LinkedNode *node, size_t k) {
	LinkedNode* n = node;
	for ( ; n != NULL && k > 0; n = n->next, k--) {}
	return n;
}

/**
 * Return the value of the node at the Kth position in the chain relative to
 * the input node. If there are fewer than K items in the list, returns false.
 *
 * @param node the first node in the chain
 * @param k the index
 * @param val the result parameter for  the value of the Kth node from input node
 * @return true if returned value of kth node as val, or false if index out of bounds
 */
bool getLinkedNodeValAt(LinkedNode *node, size_t k, const char **val) {
	LinkedNode* n = getLinkedNodeAt(node, k);
	if (n != NULL) {
		*val = n->data;
		return true;
	}
	return false;
}

/**
 * Returns last node in the chain, or NULL if node is NULL.
 *
 * @param node first node in chain
 * @return the last node in the chain or NULL
 */
LinkedNode* getLastLinkedNode(LinkedNode* node) {
	// traverse down the list to end node
	if (node != NULL) {
		for ( ; node->next != NULL; node = node->next) {}
	}
	return node;
}
/**
 *
 * @param node any position in the node
 * @return the first node in the chain or NULL
 */
LinkedNode* getFirstLinkedNode(LinkedNode* node) {
	LinkedNode *first = node;
	// traverse down the list to end node
	if (first != NULL) {
		for ( ; first->prev != NULL; first = first->prev) {
		}
	}
	return first;
}

/**
 * Set the value of the node at the Kth position relative to the input
 * node. If there are fewer than K items in the chain, returns false.
 *
 * @param node the first node in the chain
 * @param k the index
 * @param val the value to set.
 * @return true if set value of kth node as val, or false if index out of bounds
 */
bool setLinkedNodeValAt(LinkedNode *node, size_t k, const char *val) {
	LinkedNode* n = getLinkedNodeAt(node, k);
	if (n != NULL) {
		free(n->data);
		n->data = (val == NULL) ? NULL : strdup(val);
		return true;
	}
	return false;
}

/**
 * Return the size of the node chain. If the list has a dummy
 * first node, pass its next pointer to this function.
 *
 * @param node first node in chain to be measured
 * @return the size of the node chain
 */
size_t linkedNodeSize(LinkedNode* node) {
	size_t size = 0;
	// traverse down the list, counting as it goes
	for (LinkedNode* n = node; n != NULL; n = n->next, size++) {}
	return size;
}

/**
 * Add new node after the specified node in the chain.
 *
 * @param node (the node after which new node will be added
 * @param the new node to insert
 */
void addAfterLinkedNode(LinkedNode* node, LinkedNode* newNode) {
	if (node != NULL) {
		// make new node point to successor of list node
		// newNode.next point to what the node.next original point to



		if(node->next!=NULL){
			//original next is not null
			newNode->next=node->next;
			node->next->prev=newNode;
			node->next=newNode;
			newNode->prev=node;
		}
		else {
//			//original next is null
			newNode->next = NULL;
			node->next    = newNode;
			newNode->prev = node;
		}


	} else {
		// first node in list
		newNode->next = NULL;
		newNode->prev = NULL;
	}
}

/**
 * Delete node after specified chain node. Caller is responsible for
 * freeing the deleted node by calling deleteLinkedNode().
 *
 * @param node the node after which node will be deleted
 * @return the deleted node that the caller must free, or NULL if
 *   chain has no next node
 */
LinkedNode* deleteAfterLinkedNode(LinkedNode* node) {
	LinkedNode *deletedNode = NULL;

	if (node != NULL) {
		// pointer to next node that will to be deleted
		deletedNode = node->next;

		// only need to do if there is a next node to delete
		if (deletedNode != NULL) {
//			// make list node point to where next node pointed
//			node->next = deletedNode->next;
//			//***** node after delete must connect with previous node
//			deletedNode->next->prev = node;
//			// reset next pointer of deletedNode node
//			deletedNode->next = NULL; // what if it already has something else
			LinkedNode *afterDelete = NULL;
			afterDelete=deletedNode->next;
			if(afterDelete!=NULL){
				node->next=afterDelete;
				afterDelete->prev=node;
			}
			else {
				node->next=NULL;
			}
			deletedNode->next=NULL;
			deletedNode->prev=NULL;

		}

	}

	return deletedNode;
}



/**
 * Deletes all nodes in the chain.
 *
 * @param node the first node in the chain
 */
void deleteAllLinkedNodes(LinkedNode *node) {
	// delete all nodes after node
	LinkedNode *n;
	while ((n = deleteAfterLinkedNode(node)) != NULL) {
		deleteLinkedNode(n);
	}
	// delete last node
	deleteLinkedNode(node);
}

/**
 * Print the linked node chain data.
 *
 * @param node the first node in the chain to print
 */
void printLinkedNodes(LinkedNode *node) {
	printf("( ");
	for (LinkedNode* n = node; n != NULL; n = n->next) {
		printf("\"%s\" ", n->data);
	}
	printf(")\n");
	fflush(stdout);
}

