#include <stdio.h>
#include <stdlib.h>

// Declare dynamic arrays and global variables

//*********************************************************
void print_resrc(int *num_proc, int *num_resrc, int **resource)
{
	printf("\nResources:\n");

	for (int i = 0; i < *num_resrc; i++)
	{
		printf("\tr%d", i);
	}

	printf("\n");

	for (int i = 0; i < *num_resrc; i++)
	{
		printf("\t%d", *(*resource+i));
	}

	printf("\n");
}

//*********************************************************
void print_avail(int *num_proc, int *num_resrc, int **available)
{
	printf("\nAvailable:\n");

	for (int i = 0; i < *num_resrc; i++)
	{
		printf("\tr%d", i);
	}

	printf("\n");

	for (int i = 0; i < *num_resrc; i++)
	{
		printf("\t%d", *(*available+i));
	}

	printf("\n");
}

//*************************************************************
void print_max(int *num_proc, int *num_resrc, int **max_claim)
{
	printf("\nMaximum:\n");

	for (int i = 0; i < *num_resrc; i++)
	{
		printf("\tr%d", i);
	}

	printf("\n");

	for (int i = 0; i < *num_proc; i++)
	{
		printf("p%d", i);
		for (int j = 0; j < *num_resrc; j++)
		{
			printf("\t%d", *((*max_claim) + (i * (*num_resrc) + j)));
		}
		printf("\n");
	}	
	// declare local variables
	// for loop: print each resource index
	// for each process:
	// for each resource:
	// print max_claim number of units each process may request from each resource
	return;
}

//*************************************************************
// void "PROCEDURE TO PRINT ALLOCATED ARRAY"()
// {
// 	// declare local variables
// 	// for loop: print each resource index
// 	// for each process:
// 	// for each resource:
// 	// print number of units each process is allocated from each resource
// 	return;
// }

//*************************************************************
// void "PROCEDURE TO PRINT NEED ARRAY"()
// {
// 	// declare local variables
// 	// for loop: print each resource index
// 	// for each process:
// 	// for each resource:
// 	// print number of units each process needs from each resource
// 	return;
// }

//**************************************************************
void init_param(int *num_proc, int *num_resrc, int **resource, int **available, int **max_claim, int **allocated, int **need)
{
	// declare local variables
	// prompt for number of processes and number of resources
	printf("Enter number of processes: ");
	scanf("%d", num_proc);
	printf("Enter number of resources: ");
	scanf("%d", num_resrc);

	(*resource) = (int *)malloc((*num_resrc) * sizeof(int));

	printf("Enter number of units for resources (0 to %d): ", *num_resrc - 1);
	for (int i = 0; i < *num_resrc; i++)
	{
		scanf("%d", (*resource) + i);
	}

	*available 	= (int *)malloc((*num_resrc) * sizeof(int));
	*max_claim 	= (int *)malloc((*num_proc) * (*num_resrc) * sizeof(int));
	*allocated 	= (int *)malloc((*num_proc) * (*num_resrc) * sizeof(int));
	*need 		= (int *)malloc((*num_proc) * (*num_resrc) * sizeof(int));

	for (int i = 0; i < *num_proc; i++)
	{
		printf("Enter maximum units process p%d will request from each resource (r0 to r%d): ", i, *num_resrc - 1);
		for (int j = 0; j < *num_resrc; j++)
		{
			scanf("%d", (*max_claim) + (i * (*num_resrc) + j));
		}
	}

	for (int i = 0; i < *num_proc; i++)
	{
		printf("Enter number of units of each resource (r0 to r%d) allocated to process p%d:", *num_resrc - 1, i);
		for (int j = 0; j < *num_resrc; j++)
		{
			scanf("%d", (*allocated) + (i * (*num_resrc) + j));
		}
	}


	// allocate memory for vectors and arrays: resource, available, max_claim, allocated, need
	// for each resource, prompt for number of units, set resource and available vectors indices
	// for each process, for each resource, prompt for max_claim number of units requested by process, update maxclaim and need arrays
	// for each process, for each resource, prompt for number of resource units allocated to process
	// print resource vector, available vector, maxclaim array, allocated array, need array
}

//******************************************************************
// void "OPTION #2"()
// {

// 	// declare local variables, including vector to indicate if process is safely sequenced and "num_sequenced" count
// 	// while not all processes are processed
// 	// for each process
// 	// if process has not been processed yet
// 	// print message comparing need vector with available vector
// 	// for each resource
// 	// check for safe processing by comparing process' need vector to available vector
// 	// if each resource is available
// 	// print message that process can be processed
// 	// update number of available units of resource
// 	// for each resource
// 	free all resources allocated to process
// 		// increment number of sequenced processes
// 		// else print message that process cannot be processed
// 		// if (no process was processed in the final round of the for-loop)
// 		//  print message of deadlock among processes not processed
// 		return;
// }

//******************************************************************
// void "OPTION #3"()
// {
// 	// check if vectors/array are not NULL--if so, free each vector/array 	);
// 	return;
// }

//*************************************************************
int main()
{
	int num_proc;
	int num_resrc;
	int *resource;
	int *available;
	int *max_claim;
	int *allocated;
	int *need;

	init_param(&num_proc, &num_resrc, &resource, &available, &max_claim, &allocated, &need);
	print_resrc(&num_proc, &num_resrc, &resource);
	print_avail(&num_proc, &num_resrc, &available);
	print_max(&num_proc, &num_resrc, &max_claim);
	// declare local vars
	// while user has not chosen to quit
	// print menu of options
	// prompt for menu selection
	// call appropriate procedure based on choice--use switch statement or series of if, else if, else statements
	// while loop
	return 0; // indicates success
} // end of procedure