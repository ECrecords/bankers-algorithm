/*********************************************************
Author: Elvis Chino-Islas
Date Started: 4/6/2022
Date Completed: 4/6/2022
*********************************************************/

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
		printf("\t%d", *(*vector + i));
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

	(*resource) = (int *)realloc(*resource, (*num_resrc) * sizeof(int));

	printf("\nEnter number of units for resources (0 to %d): ", *num_resrc - 1);
	for (int i = 0; i < *num_resrc; i++)
	{
		scanf("%d", (*resource) + i);
	}

	*available = (int *)realloc(*available, (*num_resrc) * sizeof(int));
	*max_claim = (int *)realloc(*max_claim, (*num_proc) * (*num_resrc) * sizeof(int));
	*allocated = (int *)realloc(*allocated, (*num_proc) * (*num_resrc) * sizeof(int));
	*need = (int *)realloc(*need, (*num_proc) * (*num_resrc) * sizeof(int));

	for (int i = 0; i < *num_resrc; i++)
	{
		*((*available) + i) = *((*resource) + i);
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
			*(*available + j) -= *(*allocated + (j + (*num_resrc * i)));
		}
	}

	for (int i = 0; i < *num_proc; i++)
	{
		for (int j = 0; j < *num_resrc; j++)
		{
			*((*need) + ((i * (*num_resrc)) + j)) = *((*max_claim) + ((i * (*num_resrc)) + j)) - *((*allocated) + ((i * (*num_resrc)) + j));
		}
	}
}

//******************************************************************
void safe_sequence(int *num_proc, int *num_resrc, int **resource, int **available, int **max_claim, int **allocated, int **need)
{

	// declare local variables, including vector to indicate if process is safely sequenced and "num_sequenced" count
	int not_processed = *num_proc;
	int cached_not_processed = *num_proc;

	int process_status[*num_proc];
	int curr_need[*num_resrc];

	int is_available;

	for (int i = 0; i < *num_proc; i++)
	{
		process_status[i] = 0;
	}

	while (not_processed > 0)
	{
		cached_not_processed = not_processed;
		for (int i = 0; i < *num_proc; i++)
		{
			if (process_status[i] == 0)
			{
				for (int j = 0; j < *num_resrc; j++)
				{
					curr_need[j] = *((*need) + ((i * *num_resrc) + j));
				}

				printf("Comparing: < ");

				for (int k = 0; k < *num_resrc; k++)
				{
					printf("%d ", curr_need[k]);
				}

				printf("> <= < ");

				for (int k = 0; k < *num_resrc; k++)
				{
					printf("%d ", *((*available) + k));
				}

				printf("> : ");

				is_available = 1;

				for (int j = 0; j < *num_resrc; j++)
				{
					if (curr_need[j] > *((*available) + j))
					{
						is_available = 0;
					}
				}

				if (is_available)
				{
					printf("Yes --> p%d can be processed\n", i);

					for (int j = 0; j < *num_resrc; j++)
					{
						*((*available) + j) += *((*allocated) + ((*num_resrc * i) + j));
					}

					process_status[i] = 1;
					not_processed--;
					
				}
				else
				{
					printf("No --> p%d could not be processed\n", i);
				}
			}
		}

		if (not_processed == cached_not_processed)
		{
			printf("Deadlock among processes: ");
			for (int i = 0; i < *num_proc; i++)
			{
				if (process_status[i] == 0)
				{
					printf("p%d ", i);
				}
			}

			return;
		}
	}
}

//******************************************************************
void free_mem(int **resource, int **available, int **max_claim, int **allocated, int **need)
{
	printf("\nFreeing Memory...\n");

	if ((*resource) != NULL)
	{
		free(*resource);
	}

	if ((*available) != NULL)
	{
		free(*available);
	}

	if ((*max_claim) != NULL)
	{
		free(*max_claim);
	}

	if ((*allocated) != NULL)
	{
		free(*allocated);
	}

	if ((*need) != NULL)
	{
		free(*need);
	}
}

//*************************************************************
int main()
{
	int num_proc;
	int num_resrc;
	int *resource = NULL;
	int *available = NULL;
	int *max_claim = NULL;
	int *allocated = NULL;
	int *need = NULL;

	int option;

	printf("Banker's Algorithm\n"
		   "------------------\n");
	printf("1) Enter parameters\n"
		   "2) Determine safe sequence\n"
		   "3) Quit program\n");

	while (1)
	{
		printf("\nEnter Selection: ");
		scanf("%d", &option);
		printf("\n");

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
			safe_sequence(&num_proc, &num_resrc, &resource, &available, &max_claim, &allocated, &need);
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