#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>



int** AllocateMemory(int rows, int cols) {
    int** array = (int**)malloc((size_t)rows * sizeof(int*));
    if (array == NULL) return NULL;
    
    for (int i = 0; i < rows; i++) {
        array[i] = (int*)malloc((size_t)cols * sizeof(int));
        if (array[i] == NULL) {
            for (int j = 0; j < i; j++) free(array[j]);
            free(array);
            return NULL;
        }
    }
    return array;
}

void FillArrayWithKeyboard(int** array, int rows, int cols) {
    printf("Enter elements of the array:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &array[i][j]);
        }
    }
    printf("Array filled successfully.\n");
}

void FillArrayWithRandom(int** array, int rows, int cols) {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            array[i][j] = rand() % 201 - 100;
        }
    }
    printf("Array filled with random values.\n");
}


void SortColumnsDescending(int** array, int rows, int cols) {
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows - 1; j++) {
            for (int k = 0; k < rows - j - 1; k++) {
                if (array[k][i] < array[k + 1][i]) {
                    int temp = array[k][i];
                    array[k][i] = array[k + 1][i];
                    array[k + 1][i] = temp;
                }
            }
        }
    }
}

void PrintArray(int** array, int rows, int cols) {
    printf("\nArray elements:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d ", array[i][j]); 
        }
        printf("\n");
    }
}

void FreeMemory(int** array, int rows) {
    if (array == NULL) return;

    for (int i = 0; i < rows; i++) {
        free(array[i]);
    }
    free(array);
}

int main(void) {
    int menu = 0;
    bool isProgramRunning = true;
    int** array = NULL;
    int rows = 0, cols = 0;
    while (isProgramRunning) {
        printf("Select an option:\n1. Dynamic Memory Allocation\n2. Input array elements from keyboard\n3. FIll array with random\n4. Bubble sort columns in descending\n5. Output array elements\n6. Free allocated memory\n7. Exit\nEnter your choice: ");
        scanf("%d", &menu);
        switch (menu) {
            case 1:
                if (array != NULL) {
                    FreeMemory(array, rows);
                }
                printf("Enter number of rows and cols: ");
                scanf("%d %d", &rows, &cols);
                array = AllocateMemory(rows, cols);
                if (array == NULL) {
                    printf("Memory allocation failed.\n");
                } else {
                    printf("Dynamic Memory Allocation selected.\n");
                }
                break;
            case 2:
                if (array == NULL) {
                    printf("Memory not allocated. Please allocate memory first.\n");
                } else {
                    FillArrayWithKeyboard(array, rows, cols);
                }
                break;
            case 3:
                if (array == NULL) {
                    printf("Memory not allocated. Please allocate memory first.\n");
                } else {
                    FillArrayWithRandom(array, rows, cols);
                }
                break;
            case 4:
                if (array == NULL) {
                    printf("Memory not allocated. Please allocate memory first.\n");
                } else {
                    SortColumnsDescending(array, rows, cols);
                }
                break;
            case 5:
                if (array == NULL) {
                    printf("Please allocate memory first (option 1).\n");
                } else {
                    PrintArray(array, rows, cols);
                }
                break;
            case 6:
                if (array == NULL) {
                    printf("No memory to free.\n");
                } else {
                    FreeMemory(array, rows);
                    array = NULL;
                    rows = 0;
                    cols = 0;
                    printf("Memory freed successfully.\n");
                }
                break;
            case 7:
                isProgramRunning = false;
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
