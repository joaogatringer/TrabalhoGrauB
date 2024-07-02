#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_SIZE 65536

// Protótipos das funções de ordenação
void bubbleSort(int arr[], int n);
void insertionSort(int arr[], int n);
void selectionSort(int arr[], int n);
void heapSort(int arr[], int n);
void shellSort(int arr[], int n);
void mergeSort(int arr[], int l, int r);
void quickSort(int arr[], int low, int high);
void heapify(int arr[], int n, int i);
void merge(int arr[], int l, int m, int r);
int partition(int arr[], int low, int high);

// Funções auxiliares
void swap(int* a, int* b);
void printArray(int arr[], int size);
void generateArray(int arr[], int n, int type);

int main() {
    srand(time(NULL));

    int sizes[] = {128, 256, 512, 1024, 2048, 4096, 65536};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < numSizes; i++) {
        int n = sizes[i];
        int arr[MAX_SIZE];
        
        // Testar cada cenário
        for (int type = 0; type < 4; type++) {
            printf("Tamanho do vetor: %d, Tipo de cenário: %d\n", n, type);
            generateArray(arr, n, type);

            // Ordenação por Bolha
            int bubbleArr[MAX_SIZE];
            memcpy(bubbleArr, arr, n * sizeof(int));
            clock_t start = clock();
            bubbleSort(bubbleArr, n);
            clock_t end = clock();
            printf("Ordenação por Bolha: %lf segundos\n", (double)(end - start) / CLOCKS_PER_SEC);

            // Ordenação por Inserção
            int insertionArr[MAX_SIZE];
            memcpy(insertionArr, arr, n * sizeof(int));
            start = clock();
            insertionSort(insertionArr, n);
            end = clock();
            printf("Ordenação por Inserção: %lf segundos\n", (double)(end - start) / CLOCKS_PER_SEC);

            // Ordenação por Seleção
            int selectionArr[MAX_SIZE];
            memcpy(selectionArr, arr, n * sizeof(int));
            start = clock();
            selectionSort(selectionArr, n);
            end = clock();
            printf("Ordenação por Seleção: %lf segundos\n", (double)(end - start) / CLOCKS_PER_SEC);

            // Ordenação por Heap
            int heapArr[MAX_SIZE];
            memcpy(heapArr, arr, n * sizeof(int));
            start = clock();
            heapSort(heapArr, n);
            end = clock();
            printf("Ordenação por Heap: %lf segundos\n", (double)(end - start) / CLOCKS_PER_SEC);

            // Ordenação de Shell
            int shellArr[MAX_SIZE];
            memcpy(shellArr, arr, n * sizeof(int));
            start = clock();
            shellSort(shellArr, n);
            end = clock();
            printf("Ordenação de Shell: %lf segundos\n", (double)(end - start) / CLOCKS_PER_SEC);

            // Ordenação por Intercalação
            int mergeArr[MAX_SIZE];
            memcpy(mergeArr, arr, n * sizeof(int));
            start = clock();
            mergeSort(mergeArr, 0, n - 1);
            end = clock();
            printf("Ordenação por Intercalação: %lf segundos\n", (double)(end - start) / CLOCKS_PER_SEC);

            // Ordenação Rápida
            int quickArr[MAX_SIZE];
            memcpy(quickArr, arr, n * sizeof(int));
            start = clock();
            quickSort(quickArr, 0, n - 1);
            end = clock();
            printf("Ordenação Rápida: %lf segundos\n", (double)(end - start) / CLOCKS_PER_SEC);

            printf("\n");
        }
    }

    return 0;
}

// Função de troca
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Gerar diferentes tipos de vetores
void generateArray(int arr[], int n, int type) {
    switch(type) {
        case 0: // Ordenado crescente
            for (int i = 0; i < n; i++) {
                arr[i] = i;
            }
            break;
        case 1: // Ordenado decrescente
            for (int i = 0; i < n; i++) {
                arr[i] = n - i;
            }
            break;
        case 2: // Aleatório sem duplicados
            for (int i = 0; i < n; i++) {
                arr[i] = i;
            }
            for (int i = 0; i < n; i++) {
                int j = rand() % n;
                swap(&arr[i], &arr[j]);
            }
            break;
        case 3: // Aleatório com duplicados
            for (int i = 0; i < n; i++) {
                arr[i] = rand() % n;
            }
            break;
    }
}

// Implementação dos algoritmos de ordenação
void bubbleSort(int arr[], int n) {
    int i, j;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(&arr[minIdx], &arr[i]);
    }
}

void heapSort(int arr[], int n) {
    // Construir heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    // Extrair elementos do heap
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void shellSort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
    }

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
