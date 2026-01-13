#include <stdio.h>
#include <stdlib.h>

int main() {
    int insertValue, insertPosition;
    int currentArraySize = 4;
    int *numbers = malloc(currentArraySize * sizeof(int));

    if (numbers == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("ENTER %d NUMBERS (pressing enter after each entry):\n", currentArraySize);
    for (int count = 0; count < currentArraySize; ++count) {
        scanf("%d", &numbers[count]);
    }

    printf("\nENTER THE VALUE TO BE INSERTED: ");
    scanf("%d", &insertValue);
    printf("\nENTER THE POSITION TO INSERT THE VALUE (0 - %d): ", currentArraySize);
    scanf("%d", &insertPosition);

    if (insertPosition < 0 || insertPosition > currentArraySize) {
        printf("Invalid position!\n");
        free(numbers);
        return 1;
    }

    printf("\nThe current list of the array: ");
    for (int count = 0; count < currentArraySize; ++count) {
        printf("%d  ", numbers[count]);
    }
    printf("\n");

    // Increase array size
    numbers = realloc(numbers, (currentArraySize + 1) * sizeof(int));
    if (numbers == NULL) {
        printf("Memory reallocation failed\n");
        return 1;
    }

    // Shift elements right
    for (int index = currentArraySize; index > insertPosition; --index) {
        numbers[index] = numbers[index - 1];
    }

    // Insert new value
    numbers[insertPosition] = insertValue;
    currentArraySize++;

    printf("After insertion, the elements in the new list are: ");
    for (int count = 0; count < currentArraySize; ++count) {
        printf("%d  ", numbers[count]);
    }
    printf("\n");

    free(numbers);
    return 0;
}
