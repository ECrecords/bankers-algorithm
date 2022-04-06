#include <stdio.h>
#include <stdlib.h>

//*********************************************************
void print_vector(int *num_proc, int *num_resrc, int **vector)
{
	for (int i = 0; i < *num_resrc; i++)
	{
		printf("\tr%d", i);
	}

	printf("\n");

	for (int i = 0; i < *num_resrc; i++)
	{
		printf("\t%d", *(*vector+i));
	}

	printf("\n");
}

//*************************************************************
void print_matrix(int *num_proc, int *num_resrc, int **matrix)
{

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
			printf("\t%d", *((*matrix) + (i * (*num_resrc) + j)));
		}
		printf("\n");
	}	
}

//**************************************************************
void init_param(int *num_proc, int *num_resrc, int **resource, int **available, int **max_claim, int **allocated, int **need)
{
	printf("\nEnter number of processes: ");
	scanf("%d", num_proc);
	printf("\nEnter number of resources: ");
	scanf("%d", num_resrc);
	
	(*resource) = (int *) malloc((*num_resrc) * sizeof(int));

	printf("\nEnter number of units for resources (0 to %d): ", *num_resrc - 1);
	for (int i = 0; i < *num_resrc; i++)
	{
		scanf("%d", (*resource) + i);
	}

	*available 	= (int *)malloc((*num_resrc) * sizeof(int));
	*max_claim 	= (int *)malloc((*num_proc) * (*num_resrc) * sizeof(int));
	*allocated 	= (int *)malloc((*num_proc) * (*num_resrc) * sizeof(int));
	*need 		= (int *)malloc((*num_proc) * (*num_resrc) * sizeof(int));

	for (int i = 0; i < *num_resrc; i++)
	{
		*( (*available) + i) = *( (*resource) + i);
	}

	for (int i = 0; i < *num_proc; i++)
	{
		printf("\nEnter maximum units process p%d will request from each resource (r0 to r%d): ", i, *num_resrc - 1);
		for (int j = 0; j < *num_resrc; j++)
		{
			scanf("%d", (*max_claim) + (i * (*num_resrc) + j));
		}
	}

	for (int i = 0; i < *num_proc; i++)
	{
		printf("\nEnter number of units of each resource (r0 to r%d) allocated to process p%d: ", *num_resrc - 1, i);
		for (int j = 0; j < *num_resrc; j++)
		{
			scanf("%d", (*allocated) + (i * (*num_resrc) + j));
		}
	}

	for (int j = 0; j < *num_resrc; j++)
	{
		for (int i = 0; i < *num_proc; i++)
		{
			*( *available + j ) -= *( *allocated + (j + (*num_resrc * i)));
		}
	}
	

	for (int i = 0; i < *num_proc; i++)
	{
		for (int j = 0; j < *num_resrc; j++)
		{
			*((*need) + ( (i * (*num_resrc)) + j)) = *((*max_claim) + ( (i * (*num_resrc)) + j)) - *((*allocated) + ( (i * (*num_resrc)) + j));
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
void free_mem(int **resource, int **available, int **max_claim, int **allocated, int **need)
{
	printf("Freeing Memory...\n");

	if ( (*resource) != NULL)
	{
		free(*resource);
	}

	if ( (*available) != NULL)
	{
		free(*available);
	}

	if ( (*max_claim) != NULL)
	{
		free(*max_claim);
	}

	if ( (*allocated) != NULL)
	{
		free(*allocated);
	}

	if ( (*need) != NULL)
	{
		free(*need);
	}
	
}

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

	int option;

	printf(	"Banker's Algorithm\n"
			"------------------\n");
	printf(	"1) Enter parameters\n"
			"2) Determine safe sequence\n"
			"3) Quit program\n");

	

	while (1)
	{
		printf("\nEnter Selection: ");
		scanf("%d", &option);

		if (option == 1)
		{
			init_param(&num_proc, &num_resrc, &resource, &available, &max_claim, &allocated, &need);

			printf("\nResources:\n");
			print_vector(&num_proc, &num_resrc, &resource);

			printf("\nAvailable:\n");

			print_vector(&num_proc, &num_resrc, &available);

			printf("\nMaximum:\n");
			print_matrix(&num_proc, &num_resrc, &max_claim);

			printf("\nAllocated:\n");
			print_matrix(&num_proc, &num_resrc, &allocated);

			printf("\nNeed:\n");
			print_matrix(&num_proc, &num_resrc, &need);
		}
		else if (option == 2)
		{

		}
		else if (option == 3)
		{
			free_mem(&resource, &available, &max_claim, &allocated, &need);
			printf("Quiting Program ...\n");
			return 0;
		}
		
	}
	return 0;
}