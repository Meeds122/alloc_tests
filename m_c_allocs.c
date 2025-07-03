#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//The macros defined below define the experiment parameters.

// This defines the number of bytes allocated per block in the experiment and the number of allocated blocks. 
// max_size = max * max * sizeof(char)
#define MAX 5001
#define MIN 1 
#define STEP 10

#define SAMPLESIZE 100

struct Result {
	double calloc_time;
	double malloc_time;
};
typedef struct Result Result;

struct Simulation {
	double variance;
	int block_size;
	int block_quantity;
};
typedef struct Simulation Simulation;

Result race(int ROUNDS, int BLOCKSIZE) { // sorry about the captials. This was a macro conversion. TODO lmao
	
	Result result;

	// CALLOC memory
    clock_t start = clock();

    char *calloc_array[ROUNDS];
	for (int i = 0; i < ROUNDS; i++){
		calloc_array[i] = calloc(BLOCKSIZE, sizeof(char));
		if(calloc_array[i] == NULL)
			printf("FAIL CALLOC\n");
	}
    
	clock_t stop = clock();
    result.calloc_time = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;

	// MALLOC memory
	start = clock();

	char *malloc_array[ROUNDS];
	for (int j = 0; j < ROUNDS; j++){
		malloc_array[j] = malloc(sizeof(char) * BLOCKSIZE);
		if (malloc_array[j] == NULL)
			printf("FAIL MALLOC\n");
	}

    stop = clock();
    result.malloc_time = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;

	// clean up

	for (int k = 0; k < ROUNDS; k++){
		free(calloc_array[k]);
		free(malloc_array[k]);
	}

	return result;
} // Returns a Result object containing the time for the calloc and malloc run.

double simulate(int rounds, int blocksize){
	
	Result result;

	double calloc_sum = 0;
	double malloc_sum = 0;

	for(int i = 0; i < SAMPLESIZE; i++){
		result = race(rounds, blocksize);
		calloc_sum = calloc_sum + result.calloc_time;
		malloc_sum = malloc_sum + result.malloc_time;
	}
	
	// printf("Calloc Average time %f [ms] \n", calloc_sum / SAMPLESIZE);
	// printf("Malloc Average time %f [ms] \n", malloc_sum / SAMPLESIZE);

	double difference = (calloc_sum / SAMPLESIZE) - (malloc_sum / SAMPLESIZE);

	return difference;
} // Returns the difference between the calloc average run time and the malloc average run time. Calloc was longer if positive and malloc was longer if neg.

int main(){
	
	int number_of_simulations = (MAX - MIN) / STEP;
	Simulation results[number_of_simulations];
	int results_index = 0;

	for(int i = MIN; i < MAX; i = i + STEP){
		results[results_index].variance = simulate(i, i);
		results[results_index].block_quantity = i;
		results[results_index].block_size = i;
		results_index++;
	}
	

	// Print CSV format
	printf("block_quantity, block_size, variance (+ if calloc was slower)\n");
	for(int j = 0; j < number_of_simulations; j++){
		printf("%d, %d, %f\n", results[j].block_quantity, results[j].block_size, results[j].variance);
	}

	return 0;
}
