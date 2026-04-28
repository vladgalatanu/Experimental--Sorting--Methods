#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

// ==========================================
// 1. DATA GENERATION FUNCTIONS
// ==========================================

void fill_random(int arr[], int n) {
    for (int i = 0; i < n; i++) arr[i] = rand() % n;
}

void fill_sorted(int arr[], int n) {
    for (int i = 0; i < n; i++) arr[i] = i;
}

void fill_reverse_sorted(int arr[], int n) {
    for (int i = 0; i < n; i++) arr[i] = n - i;
}

void fill_few_unique(int arr[], int n) {
    for (int i = 0; i < n; i++) arr[i] = rand() % 5;
}

void swap(int* a, int* b) {
    int temp = *a; 
    *a = *b; 
    *b = temp;
}

void fill_nearly_sorted(int arr[], int n) {
    for (int i = 0; i < n; i++) arr[i] = i;
    int num_swaps = (int)(n * 0.05);
    for (int i = 0; i < num_swaps; i++) {
        int idx1 = rand() % n;
        int idx2 = rand() % n;
        swap(&arr[idx1], &arr[idx2]);
    }
}

// ==========================================
// 2. SORTING ALGORITHMS
// ==========================================

int bubbleSort(int arr[], int n, double timeout_sec) {
    struct timespec start_t, current_t;
    clock_gettime(CLOCK_MONOTONIC, &start_t);

    for (int i = 0; i < n - 1; i++) {
        clock_gettime(CLOCK_MONOTONIC, &current_t);
        double elapsed = (current_t.tv_sec - start_t.tv_sec) + 
                         (current_t.tv_nsec - start_t.tv_nsec) / 1000000000.0;
        if (elapsed > timeout_sec) return -1;

        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
    return 0;
}

int insertionSort(int arr[], int n, double timeout_sec) {
    struct timespec start_t, current_t;
    clock_gettime(CLOCK_MONOTONIC, &start_t);
    for (int i = 1; i < n; i++) {
        clock_gettime(CLOCK_MONOTONIC, &current_t);
        double elapsed = (current_t.tv_sec - start_t.tv_sec) + 
                         (current_t.tv_nsec - start_t.tv_nsec) / 1000000000.0;
        if (elapsed > timeout_sec) return -1;
        
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
    return 0;
}

int selectionSort(int arr[], int n, double timeout_sec) {
    struct timespec start_t, current_t;
    clock_gettime(CLOCK_MONOTONIC, &start_t);
    for (int i = 0; i < n - 1; i++) {
        clock_gettime(CLOCK_MONOTONIC, &current_t);
        double elapsed = (current_t.tv_sec - start_t.tv_sec) + 
                         (current_t.tv_nsec - start_t.tv_nsec) / 1000000000.0;
        if (elapsed > timeout_sec) return -1;
        
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) min_idx = j;
        }
        swap(&arr[i], &arr[min_idx]);
    }
    return 0;
}

void merge(int arr[], int l, int m, int r){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));
    
    for (i = 0; i < n1; i++) L[i] = arr[l + i];
    for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    
    i = 0; j = 0; k = l;
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
    while (i < n1) { arr[k] = L[i]; i++; k++; }
    while (j < n2) { arr[k] = R[j]; j++; k++; }
    
    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r){
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int medianOfThree(int arr[], int low, int high) {
    int mid = low + (high - low) / 2;
    if (arr[low] > arr[mid]) swap(&arr[low], &arr[mid]);
    if (arr[low] > arr[high]) swap(&arr[low], &arr[high]);
    if (arr[mid] > arr[high]) swap(&arr[mid], &arr[high]);
    swap(&arr[mid], &arr[high]);
    return arr[high];
}

int partition(int arr[], int low, int high) {
    int pivot = medianOfThree(arr, low, high); 
    int i = (low - 1); 
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++; 
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quick_sort_logic(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort_logic(arr, low, pi - 1);
        quick_sort_logic(arr, pi + 1, high);
    }
}

void quick_sort(int arr[], int n) {
    quick_sort_logic(arr, 0, n - 1);
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

void countsort(int arr[], int n) {
    int maxval = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > maxval) maxval = arr[i];
    }
    int* cntArr = (int*)calloc(maxval + 1, sizeof(int));
    int* ans = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) cntArr[arr[i]]++;
    for (int i = 1; i <= maxval; i++) cntArr[i] += cntArr[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        ans[cntArr[arr[i]] - 1] = arr[i];
        cntArr[arr[i]]--;
    }
    for (int i = 0; i < n; i++) arr[i] = ans[i];
    free(cntArr);
    free(ans);
}

int getMax(int arr[], int n) {
    int mx = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > mx) mx = arr[i];
    }
    return mx;
}

void countSortForRadix(int arr[], int n, int exp) {
    int* output = (int*)malloc(n * sizeof(int));
    int i, count[10] = { 0 };

    for (i = 0; i < n; i++) count[(arr[i] / exp) % 10]++;
    for (i = 1; i < 10; i++) count[i] += count[i - 1];
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (i = 0; i < n; i++) arr[i] = output[i];
    free(output);
}

void radixSort(int arr[], int n) {
    int m = getMax(arr, n);
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSortForRadix(arr, n, exp);
}

// ==========================================
// 3. MAIN EXPERIMENT ENGINE
// ==========================================

int main() {
    srand(time(NULL));
    
    int sizes[] = {10, 20, 100, 1000, 10000, 50000, 100000}; 
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    double timeout_limit = 7.0;
    
    FILE *file = fopen("results.csv", "w");
    if (file == NULL) {
        printf("Error: Could not open file for writing!\n");
        return 1;
    }
    
    fprintf(file, "Size,DataType,Algorithm,Time_Seconds\n");
    
    printf("Starting sorting experiments. This may take a few minutes...\n");
    printf("Writing data directly to results.csv...\n\n");
    
    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        int current_iterations = (n <= 1000) ? 10 : 1; 
        
        int *original_arr = (int *)malloc(n * sizeof(int));
        int *test_arr = (int *)malloc(n * sizeof(int));
        
        for (int data_type = 0; data_type < 5; data_type++) {
            char data_label[20];
            
            if (data_type == 0) strcpy(data_label, "Random");
            else if (data_type == 1) strcpy(data_label, "Sorted"); 
            else if (data_type == 2) strcpy(data_label, "Reverse"); 
            else if (data_type == 3) strcpy(data_label, "Few_Unique"); 
            else if (data_type == 4) strcpy(data_label, "Nearly_Sorted"); 
            
            for (int algo = 0; algo < 8; algo++) {
                char algo_name[20];
                double total_time = 0.0;
                bool timeout_triggered = false;
                
                if (algo == 0) strcpy(algo_name, "Bubble");
                else if (algo == 1) strcpy(algo_name, "Insertion");
                else if (algo == 2) strcpy(algo_name, "Selection");
                else if (algo == 3) strcpy(algo_name, "Merge");
                else if (algo == 4) strcpy(algo_name, "Quick");
                else if (algo == 5) strcpy(algo_name, "Heap");
                else if (algo == 6) strcpy(algo_name, "Counting");
                else if (algo == 7) strcpy(algo_name, "Radix");

                for (int run = 0; run < current_iterations; run++) {
                    
                    if (data_type == 0) fill_random(original_arr, n);
                    else if (data_type == 1) fill_sorted(original_arr, n);
                    else if (data_type == 2) fill_reverse_sorted(original_arr, n);
                    else if (data_type == 3) fill_few_unique(original_arr, n);
                    else if (data_type == 4) fill_nearly_sorted(original_arr, n);

                    for(int i = 0; i < n; i++) test_arr[i] = original_arr[i];
                    
                    struct timespec start_time, end_time;
                    int status = 0;
                    
                    clock_gettime(CLOCK_MONOTONIC, &start_time);
                    
                    if (algo == 0) status = bubbleSort(test_arr, n, timeout_limit);
                    else if (algo == 1) status = insertionSort(test_arr, n, timeout_limit);
                    else if (algo == 2) status = selectionSort(test_arr, n, timeout_limit);
                    else if (algo == 3) mergeSort(test_arr, 0, n - 1);
                    else if (algo == 4) quick_sort(test_arr, n);
                    else if (algo == 5) heapSort(test_arr, n);
                    else if (algo == 6) countsort(test_arr, n);
                    else if (algo == 7) radixSort(test_arr, n);
                    
                    clock_gettime(CLOCK_MONOTONIC, &end_time);

                    if (status == -1) {
                        timeout_triggered = true;
                        break; 
                    }
                    
                    double time_taken = (end_time.tv_sec - start_time.tv_sec) + 
                                        (end_time.tv_nsec - start_time.tv_nsec) / 1000000000.0;
                    total_time += time_taken;
                }
                
                if (timeout_triggered) {
                    fprintf(file, "%d,%s,%s,TIMEOUT\n", n, data_label, algo_name);
                    printf("Completed: %-10d | %-15s | %-10s -> [TIMEOUT]\n", n, data_label, algo_name);
                } else {
                    double display_time = total_time / current_iterations;
                    fprintf(file, "%d,%s,%s,%.9f\n", n, data_label, algo_name, display_time);
                    printf("Completed: %-10d | %-15s | %-10s -> %.5f sec\n", n, data_label, algo_name, display_time);
                }
            }
        }
        free(original_arr);
        free(test_arr);
    }
    
    fclose(file);
    printf("\nSuccess! All data has been saved to 'results.csv'.\n");
    printf("You can now run your Python script to generate the charts!\n");
    
    return 0;
}