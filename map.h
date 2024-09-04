#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

// Define the structure for a key-value pair (Node)
typedef struct Node {
    char *key;          // The key
    int value;          // The value
    struct Node *next;  // Pointer to the next node (for handling collisions)
} Node;

// Define the structure for the hash map
typedef struct {
    Node *table[TABLE_SIZE];  // Array of pointers to linked lists
} Map;

// Hash function to convert a string key into an index
unsigned int hash(const char *key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;  // Simple hash function (djb2 by Dan Bernstein)
    }
    return hash % TABLE_SIZE;
}

// Initialize the map
void map_init(Map *map) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        map->table[i] = NULL;  // Initialize all buckets to NULL
    }
}

// Create a new node
Node *create_node(const char *key, int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->key = strdup(key);  // Allocate memory and copy the key
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

// Insert a key-value pair into the map
void map_insert(Map *map, const char *key, int value) {
    unsigned int index = hash(key);
    Node *new_node = create_node(key, value);

    if (map->table[index] == NULL) {
        map->table[index] = new_node;  // No collision, insert directly
    } else {
        Node *temp = map->table[index];
        while (temp->next != NULL) {
            if (strcmp(temp->key, key) == 0) {
                temp->value = value;  // Update the value if key exists
                free(new_node->key);  // Free the key string of the new node
                free(new_node);       // Free the new node
                return;
            }
            temp = temp->next;
        }
        if (strcmp(temp->key, key) == 0) {
            temp->value = value;  // Update the value if key exists
            free(new_node->key);  // Free the key string of the new node
            free(new_node);       // Free the new node
        } else {
            temp->next = new_node;  // Collision occurred, add to the chain
        }
    }
}

// Retrieve a value by key
int map_get(Map *map, const char *key) {
    unsigned int index = hash(key);
    Node *temp = map->table[index];

    while (temp != NULL) {
        if (strcmp(temp->key, key) == 0) {
            return temp->value;
        }
        temp = temp->next;
    }

    return -1;  // Key not found (you can return another error code or handle differently)
}

// Delete a key-value pair from the map
void map_delete(Map *map, const char *key) {
    unsigned int index = hash(key);
    Node *temp = map->table[index];
    Node *prev = NULL;

    while (temp != NULL && strcmp(temp->key, key) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Key not found in the map\n");
        return;
    }

    if (prev == NULL) {
        map->table[index] = temp->next;  // Key is at the head of the chain
    } else {
        prev->next = temp->next;  // Key is in the middle or end of the chain
    }

    free(temp->key);
    free(temp);
}

// Free the memory allocated for the map
void map_free(Map *map) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *temp = map->table[i];
        while (temp != NULL) {
            Node *next = temp->next;
            free(temp->key);
            free(temp);
            temp = next;
        }
    }
}

// Example usage of the map
int main() {
    Map map;
    map_init(&map);

    map_insert(&map, "apple", 100);
    map_insert(&map, "banana", 200);
    map_insert(&map, "cherry", 300);

    printf("Value for 'apple': %d\n", map_get(&map, "apple"));
    printf("Value for 'banana': %d\n", map_get(&map, "banana"));
    printf("Value for 'cherry': %d\n", map_get(&map, "cherry"));

    map_delete(&map, "banana");
    printf("Value for 'banana' after deletion: %d\n", map_get(&map, "banana"));

    map_free(&map);
    return 0;
}
