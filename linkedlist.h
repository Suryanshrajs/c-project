#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the linked list
typedef struct Node {
    int data;           // Data stored in the node
    struct Node* next;  // Pointer to the next node
} Node;

// Define the structure for the linked list
typedef struct {
    Node* head;  // Pointer to the first node in the list
} LinkedList;

// Initialize the linked list
void list_init(LinkedList* list) {
    list->head = NULL;  // Set the head pointer to NULL (empty list)
}

// Create a new node
Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// Add a node at the end of the list
void list_append(LinkedList* list, int data) {
    Node* new_node = create_node(data);

    if (list->head == NULL) {
        list->head = new_node;  // If the list is empty, the new node becomes the head
    } else {
        Node* temp = list->head;
        while (temp->next != NULL) {
            temp = temp->next;  // Traverse to the end of the list
        }
        temp->next = new_node;  // Link the last node to the new node
    }
}

// Add a node at the beginning of the list
void list_prepend(LinkedList* list, int data) {
    Node* new_node = create_node(data);
    new_node->next = list->head;
    list->head = new_node;
}

// Delete a node with a specific value
void list_delete(LinkedList* list, int data) {
    Node* temp = list->head;
    Node* prev = NULL;

    // If the head node contains the data to be deleted
    if (temp != NULL && temp->data == data) {
        list->head = temp->next;  // Change the head pointer
        free(temp);  // Free the old head node
        return;
    }

    // Search for the node to be deleted, keeping track of the previous node
    while (temp != NULL && temp->data != data) {
        prev = temp;
        temp = temp->next;
    }

    // If the data was not found in the list
    if (temp == NULL) {
        printf("Data not found in the list\n");
        return;
    }

    // Unlink the node from the list and free it
    prev->next = temp->next;
    free(temp);
}

// Print all elements in the list
void list_print(LinkedList* list) {
    Node* temp = list->head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Free the memory allocated for the list
void list_free(LinkedList* list) {
    Node* temp = list->head;
    while (temp != NULL) {
        Node* next = temp->next;
        free(temp);
        temp = next;
    }
    list->head = NULL;
}

// Example usage of the linked list
int main() {
    LinkedList list;
    list_init(&list);

    list_append(&list, 10);
    list_append(&list, 20);
    list_append(&list, 30);

    printf("List after appending elements: ");
    list_print(&list);

    list_prepend(&list, 5);
    printf("List after prepending element: ");
    list_print(&list);

    list_delete(&list, 20);
    printf("List after deleting element with value 20: ");
    list_print(&list);

    list_free(&list);
    return 0;
}

