#include "lab1.h"
#include <stdio.h>
#include <math.h>

// Сортировка вставками
void sort_mass(int* mass, const size_t size, const enum ESort eSort) { 
    
    switch(eSort) {
        case E_UP:
            for (int i = 1; i < size; i++) {
                int key = mass[i];
                int j = i - 1;

                while (j >= 0 && mass[j] > key) {
                    mass[j + 1] = mass[j];
                    j = j - 1;
                }

                mass[j + 1] = key;
            }
            return;

        case E_DOWN:
            for (int i = size-1; i >= 0; i--) {
                int key = mass[i];
                int j = i + 1;
            
                while (j < size && mass[j] > key) {
                    mass[j - 1] = mass[j];
                    j = j + 1;
                }

                mass[j - 1] = key;
            }
            return;
    }
}

// Функция возвращает длину числа с его знаком (+/-)
int getLen(int a) {

        if(a > 0) {
            return floor(log10(abs(a))) + 1;
        }

        if(a < 0) {
            return floor(log10(abs(a))) + 1;
        }

        if(a == 0) {
            return 1;
        }
}

// Вывод массива в табличном виде
void print(const int* mass, const size_t size, const unsigned column){
    
    int max = getLen(mass[0]);
    unsigned row = size/column;
    
    if(size % column != 0) {
        printf("Unable to print");
        return;
    }

    for(int i = 0; i < size; i++) {
        if(max < getLen(mass[i])) {
            max = getLen(mass[i]);
        }
    }

    for(int i = 0; i < row; i++) {
        for(int j = 0; j < column; j++) {
            printf("%+-*d ", max + 1, mass[i*column+j]);
        }
        printf("\n");
    }

    return;
}

// Копирование массива (много памяти)
int* copyArr(const int* mass, const size_t size) {
    int* temp = (int*) malloc(size * sizeof(int));

    for(int i = 0; i < size; i++) {
        temp[i] = mass[i];
    }

    return temp;
}


float get_median(const int* mass, const size_t size) {
    float result;

    int* temp = copyArr(mass, size);
    sort_mass(temp, size, E_UP);

    if(size%2==0) {
        result = ((temp[size/2-1] + temp[size/2])/2.0f);
    }

    else {
        result = temp[size/2+1];

    }

    free(temp);
    return result;
}

void print_moda(const int* mass, const size_t size) {

    int* temp = copyArr(mass, size);
    sort_mass(temp, size, E_DOWN);

    int count = 0, maxm = 0;

    for(int i = 0; i < size-1; i++) {
        if(temp[i] == temp[i+1]) {
            count+=1;
        }
        else { 
            count = 0;
        }
        if(count > maxm) {
            maxm = count;
        }
    }

    count = 0;
    for(int i = 0; i < size-1; i++) {
        if(temp[i] == temp[i+1]) {
            count+=1;
        }
        else { 
            count = 0;
        }

        if(count == maxm && maxm>1) {
            printf("%d ", temp[i]);
        }
    }

    if(maxm == 0) {
        printf("Each number only appears once.");
    }

    printf("\n");
    free(temp);
    return;
}

float get_average(const int* mass, const size_t size) {
    int sum = 0;

    for(int i = 0; i < size; i++) {
        sum += mass[i];
    }

    return (sum/(float)size);

}

int get_max(const int* mass, const size_t size) {
    int temp = mass[0];
    for(int i = 0; i < size; i++) {
        if(temp < mass[i]) {
            temp = mass[i];
        }
    }
    return temp;
}

int get_min(const int* mass, const size_t size) {
    int temp = mass[0];
    for(int i = 0; i < size; i++) {
        if(temp > mass[i]) {
            temp = mass[i];
        }
    }
    return temp;
}
int get_range(const int* mass, const size_t size) {
    return get_max(mass, size) - get_min(mass, size);
}

float get_dispersion(const int* mass, const size_t size) {
    float average = get_average(mass, size);
    float sum = 0, temp = (size-1);
    for(int i = 0; i < size; i++) {
        sum += (mass[i]-average)*(mass[i]-average);
    }
    return sum/temp;
}

float get_st_deviation(const int* mass, const size_t size) {
    return sqrt(get_dispersion(mass, size));
}

void hist(const int* mass, const size_t size, int* count, const size_t bins) {
    float min = get_min(mass, size);
    float max = get_max(mass, size);
    float range = get_range(mass, size);
    float border[bins];
    border[bins-1] = max;
    for(int i = 1; i < bins; i++) {
        border[i-1] = min + (range/(float)bins)*i;
    }
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < bins; j++) {
            if(mass[i] <= border[j]) {
                count[j]+=1;
                break;;
            }
        }
    }
    return;
}

void print_hist(const int* mass, const size_t size, const int* count, const size_t bins) {
    float min = get_min(mass, size);
    float max = get_max(mass, size);
    float range = get_range(mass, size);
    float border[bins+1];
    border[0] = min;
    border[bins] = max;
    for(int i = 1; i < bins; i++) {
        border[i] = min + (range/(float)bins)*i;
    }
    
    int max_len = getLen(border[0]);
    for(int i = 0; i < bins+1; i++) {
        if(max_len < getLen(border[i])) {
            max_len = getLen(border[i]);
        }
    }

    for(int i = 0; i < bins; i++) {
        printf("[%10.2f,%10.2f] ", border[i], border[i+1]);
        for(int j = 0; j < count[i]; j++) {
            printf("[]");
        }
        printf("\n");
    }
}