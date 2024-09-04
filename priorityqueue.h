#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Structure to represent a priority queue
typedef struct PriorityQueue {
    int data[MAX];
    int size;
} PriorityQueue;

// Function to initialize the priority queue
void init(PriorityQueue *pq) {
    pq->size = 0;
}

// Function to insert an element into the priority queue
void enqueue(PriorityQueue *pq, int value) {
    if (pq->size >= MAX) {
        printf("Queue overflow\n");
        return;
    }
    
    // Insert the new element at the end of the array
    pq->data[pq->size] = value;
    pq->size++;
    
    // Move the new element to its correct position
    for (int i = pq->size - 1; i > 0 && pq->data[i] > pq->data[i - 1]; i--) {
        int temp = pq->data[i];
        pq->data[i] = pq->data[i - 1];
        pq->data[i - 1] = temp;
    }
}

// Function to remove and return the highest priority element
int dequeue(PriorityQueue *pq) {
    if (pq->size == 0) {
        printf("Queue underflow\n");
        return -1;
    }
    
    // The highest priority element is at the front (index 0)
    int highestPriority = pq->data[0];
    
    // Shift all elements to the left
    for (int i = 1; i < pq->size; i++) {
        pq->data[i - 1] = pq->data[i];
    }
    
    pq->size--;
    
    return highestPriority;
}

// Function to check if the priority queue is empty
int isEmpty(PriorityQueue *pq) {
    return pq->size == 0;
}

// Function to display the elements of the priority queue
void display(PriorityQueue *pq) {
    if (isEmpty(pq)) {
        printf("Priority Queue is empty\n");
        return;
    }
    
    for (int i = 0; i < pq->size; i++) {
        printf("%d ", pq->data[i]);
    }
    printf("\n");
}

// Main function to test the priority queue
int main() {
    PriorityQueue pq;
    init(&pq);
    
    enqueue(&pq, 5);
    enqueue(&pq, 1);
    enqueue(&pq, 3);
    enqueue(&pq, 2);
    enqueue(&pq, 4);
    
    printf("Priority Queue: ");
    display(&pq);
    
    printf("Dequeue: %d\n", dequeue(&pq));
    printf("Priority Queue after dequeue: ");
    display(&pq);
    
    return 0;
}
