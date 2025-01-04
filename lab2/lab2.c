/*Name: Bhuwan Upadhyaya
NetId: bxu9187

command to run the lab 2
gcc lab2.c -o lab2
.\lab2
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_STRING_LENGTH 51

// Heap node structure
typedef struct {
    char str[MAX_STRING_LENGTH];
    int file_index;
} HeapNode;

// Swap two heap nodes
void swap(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// Min-heapify function
void minHeapify(HeapNode heap[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && strcmp(heap[left].str, heap[smallest].str) < 0)
        smallest = left;

    if (right < n && strcmp(heap[right].str, heap[smallest].str) < 0)
        smallest = right;

    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        minHeapify(heap, n, smallest);
    }
}

// Insert a new string into the heap
void insertHeap(HeapNode heap[], int *heapSize, HeapNode newNode) {
    heap[*heapSize] = newNode;
    int i = *heapSize;
    (*heapSize)++;

    // Adjust heap structure upwards
    while (i != 0 && strcmp(heap[i].str, heap[(i - 1) / 2].str) < 0) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Extract the minimum string from the heap
HeapNode extractMin(HeapNode heap[], int *heapSize) {
    if (*heapSize <= 0) {
        HeapNode emptyNode = {"", -1};
        return emptyNode;
    }
    if (*heapSize == 1) {
        (*heapSize)--;
        return heap[0];
    }

    HeapNode root = heap[0];
    heap[0] = heap[*heapSize - 1];
    (*heapSize)--;
    minHeapify(heap, *heapSize, 0);

    return root;
}

int main() {
    FILE *in_fp, *out_fp, *file_ptrs[MAX_FILES];
    HeapNode heap[MAX_FILES];
    char file_names[MAX_FILES][MAX_STRING_LENGTH];
    char current_string[MAX_STRING_LENGTH];
    int heapSize = 0;
    int n; // number of input files

    // Open the input descriptor file in.dat
    in_fp = fopen("in.dat", "r");
    if (in_fp == NULL) {
        printf("Error: Could not open in.dat\n");
        return 1;
    }

    // Read number of files from in.dat
    fscanf(in_fp, "%d", &n);

    // Open all input files and initialize the heap
    for (int i = 0; i < n; i++) {
        fscanf(in_fp, "%s", file_names[i]);
        file_ptrs[i] = fopen(file_names[i], "r");

        if (file_ptrs[i] == NULL) {
            printf("Error: Could not open %s\n", file_names[i]);
            return 1;
        }

        // Read the first string from each file and insert into the heap
        if (fscanf(file_ptrs[i], "%s", current_string) != EOF) {
            HeapNode newNode;
            strcpy(newNode.str, current_string);
            newNode.file_index = i;
            insertHeap(heap, &heapSize, newNode);
        }
    }

    // Open output file
    out_fp = fopen("out.dat", "w");
    if (out_fp == NULL) {
        printf("Error: Could not open out.dat\n");
        return 1;
    }

    // Variables to track previous string and count of files containing it
    char previous_string[MAX_STRING_LENGTH] = "";
    int k = 0; // count of files containing current string

    // Process the heap until all files are exhausted
    while (heapSize > 0) {
        HeapNode minNode = extractMin(heap, &heapSize);

        // If the current string is different from the previous one, output the previous string
        if (strcmp(minNode.str, previous_string) != 0) {
            if (k > 0) {
                fprintf(out_fp, "%s %d\n", previous_string, k);
            }
            strcpy(previous_string, minNode.str);
            k = 1; // reset file count for new string
        } else {
            k++; // string is found in another file
        }

        // Try to read the next string from the file from which the current min string came
        if (fscanf(file_ptrs[minNode.file_index], "%s", current_string) != EOF) {
            HeapNode newNode;
            strcpy(newNode.str, current_string);
            newNode.file_index = minNode.file_index;
            insertHeap(heap, &heapSize, newNode);
        }
    }

    // Output the last string
    if (k > 0) {
        fprintf(out_fp, "%s %d\n", previous_string, k);
    }

    // Close all open files
    fclose(in_fp);
    fclose(out_fp);
    for (int i = 0; i < n; i++) {
        fclose(file_ptrs[i]);
    }

    return 0;
}
