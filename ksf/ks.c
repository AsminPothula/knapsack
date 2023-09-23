#include <stdio.h>
#include <stdlib.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

void printTable(int **table, int num_of_items, int max_weight)
{
    printf("\nKnapsack Table:\n");
    for (int i = 0; i <= num_of_items; i++)
    {
        for (int w = 0; w <= max_weight; w++)
        {
            printf("%-2d ", table[i][w]);
        }
        printf("\n");
    }
    printf("\n");
}

int knapSack(int max_weight, int wt[], int val[], int num_of_items)
{
    int i, w; //i to keep track of current element, w is the current weight being considered 
    int **K = malloc((num_of_items + 1) * sizeof(int *));
    for (i = 0; i <= num_of_items; i++)
    {
        K[i] = malloc((max_weight + 1) * sizeof(int)); //the knapsack table
    }


    // Building table - K[][] in bottom-up manner
    for (i = 0; i <= num_of_items; i++)
    {
        for (w = 0; w <= max_weight; w++)
        {
            if (i == 0 || w == 0)
            {
                K[i][w] = 0;
            }
            else if (wt[i - 1] <= w)
            {
                K[i][w] = max(val[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w]);
            }
            else
            {
                K[i][w] = K[i - 1][w];
            }
        }
    }

    printTable(K, num_of_items, max_weight);

    int result = K[num_of_items][max_weight];

    // Freeing allocated memory
    for (i = 0; i <= num_of_items; i++)
    {
        free(K[i]);
    }
    free(K);
    return result;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("\nFile must be provided on command line...exiting.\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Failed to open the file.\n");
        return 1;
    }

    int max_weight, num_of_items; //maximum weigth of the knapsack and total number of items
    fscanf(file, "%d", &max_weight);
    fscanf(file, "%d", &num_of_items);

    printf("\nKnapsack Capacity (W): %d\n", max_weight);
    printf("\nNumber of Items (n): %d\n", num_of_items);

    int *wt = malloc(num_of_items * sizeof(int)); //array containing weights of all the items
    int *val = malloc(num_of_items * sizeof(int)); //array containing profits (values) of all the items

    printf("\nWeights: \n");
    for (int i = 0; i < num_of_items; i++)
    {
        fscanf(file, "%d", &wt[i]);
        printf("%d ", wt[i]);
    }
    printf("\n");

    printf("\nValues: \n");
    for (int i = 0; i < num_of_items; i++)
    {
        fscanf(file, "%d", &val[i]);
        printf("%d ", val[i]);
    }
    printf("\n");

    fclose(file);

    int maxValue = knapSack(max_weight, wt, val, num_of_items);

    printf("The maximum value that can be obtained is: %d\n\n", maxValue);

    free(wt);
    free(val);

    return 0;
}


