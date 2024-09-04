#include <stdio.h>
#include <stdlib.h>

// Define the Vector structure
typedef struct {
    int *data;        // Pointer to the underlying array
    size_t size;      // Current number of elements in the vector
    size_t capacity;  // Current allocated capacity of the vector
} Vector;

// Initialize the vector with a default capacity
void vector_init(Vector *v) {
    v->size = 0;
    v->capacity = 4; // Start with a small capacity
    v->data = (int *)malloc(v->capacity * sizeof(int));
    if (v->data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}

// Add an element to the end of the vector
void vector_push_back(Vector *v, int value) {
    // Check if we need to resize the vector
    if (v->size == v->capacity) {
        v->capacity *= 2; // Double the capacity
        v->data = (int *)realloc(v->data, v->capacity * sizeof(int));
        if (v->data == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
    }
    v->data[v->size++] = value; // Add the element and increment size
}

// Get an element at a specific index
int vector_get(Vector *v, size_t index) {
    if (index < v->size) {
        return v->data[index];
    }
    fprintf(stderr, "Index out of bounds\n");
    return -1; // Return an error code if index is out of bounds
}

// Set an element at a specific index
void vector_set(Vector *v, size_t index, int value) {
    if (index < v->size) {
        v->data[index] = value;
    } else {
        fprintf(stderr, "Index out of bounds\n");
    }
}

// Get the current size of the vector
size_t vector_size(Vector *v) {
    return v->size;
}

// Free the memory allocated for the vector
void vector_free(Vector *v) {
    free(v->data);
}

// Example usage of the vector
int main() {
    Vector v;
    vector_init(&v);

    vector_push_back(&v, 10);
    vector_push_back(&v, 20);
    vector_push_back(&v, 30);
    vector_push_back(&v, 40);

    for (size_t i = 0; i < vector_size(&v); i++) {
        printf("Element at index %zu: %d\n", i, vector_get(&v, i));
    }

    vector_set(&v, 1, 100);
    printf("After setting index 1 to 100: %d\n", vector_get(&v, 1));

    vector_free(&v);
    return 0;
}
