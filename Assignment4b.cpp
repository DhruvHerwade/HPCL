#include <omp.h>
#include <queue>
#include <iostream>

#define BUFFER_SIZE 10

std::queue<int> buffer;
int bufferSize = 0;

omp_lock_t lock;

void producer() {
    for (int i = 0; i < 20; i++) {
        int item = i;

        omp_set_lock(&lock);
        while (bufferSize == BUFFER_SIZE) {
            omp_unset_lock(&lock);
            omp_set_lock(&lock);
        }
        
        buffer.push(item);
        bufferSize++;
        std::cout << "Produced: " << item << std::endl;

        omp_unset_lock(&lock);
    }
}

void consumer() {
    for (int i = 0; i < 20; i++) {
        omp_set_lock(&lock);
        while (bufferSize == 0) {
            omp_unset_lock(&lock);
            omp_set_lock(&lock);
        }

        int item = buffer.front();
        buffer.pop();
        bufferSize--;
        std::cout << "Consumed: " << item << std::endl;

        omp_unset_lock(&lock);
    }
}

int main() {
    omp_init_lock(&lock);

    #pragma omp parallel sections
    {
        #pragma omp section
        producer();

        #pragma omp section
        consumer();
    }

    omp_destroy_lock(&lock);

    return 0;
}

