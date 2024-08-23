#include <stdio.h>

double calculateFlops(int cores, double clock_speed, int flops_per_cycle) {
    return cores * clock_speed * flops_per_cycle;
}

int main() {
   
    int num_cores = 12;               
    double clock_speed = 4.056e9;       
    int flops_per_cycle = 16;         


    double flops = calculateFlops(num_cores, clock_speed, flops_per_cycle);
    
    printf("%f * 1e9 \n",flops/1e9);

    return 0;
}

