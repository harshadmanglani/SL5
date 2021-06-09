#include<stdio.h>

int cost_matrix[10][10],visited[10],n,cost=0,src;
int nearestCity(int);
void inputCostMatrix()
{
	printf("Enter number of cities: ");
	scanf("%d",&n);
	printf("\nEnter the cost matrix\n");
	for(int i=0;i<n;i++)
	{
		printf("\nEnter elements of row: %d\n",i+1);
		for(int j = 0; j < n; j++)
		{
			scanf("%d",&cost_matrix[i][j]);
		}
		visited[i]=0;
	}
	printf("The cost matrix is: \n");
	for(int i = 0; i < n; i++)
	{
		printf("\n");
		for(int j = 0; j < n; j++)
			printf("\t%d",cost_matrix[i][j]);
	}
}
//  C(S, i) = min { C(S-{i}, j) + dis(j, i)} where j belongs to S, j != i and j != 1

void travelingSalesman(int city, int src)
{
	int nearest_city;

    // visit the city
	visited[city] = 1;	
	printf("%d -->",city);
	nearest_city = nearestCity(city);

	if(nearest_city == 999) // all cities are visited
	{
		nearest_city = src; // set nearest_city to source to complete the loop
        printf("%d", src);
		cost += cost_matrix[city][nearest_city];
		return;
	}
	travelingSalesman(nearest_city, src);
}

int nearestCity(int c)
{
	int nearest_city = 999;
	int min = 999, kmin;

	for(int i = 0; i < n; i++)
	{
		if(cost_matrix[c][i] != 0 && visited[i] == 0) // if path exists and it is not visited
		{
			if(cost_matrix[i][c] + cost_matrix[c][i] < min) // if the route from that city to the current city is less than min
			{
				min = cost_matrix[i][c] + cost_matrix[c][i]; // update running min
				kmin = cost_matrix[c][i];                   // update cost
				nearest_city = i;
			}
		}
	}
	if(min!=999)
		cost += kmin; // update global cost
	return nearest_city;
}

void print()
{
	printf("\nMinimum cost: ");
	printf("%d",cost);
	printf("\n\n");
}

int main()
{
	inputCostMatrix();
	printf("\nEnter source vertex: ");
	scanf("%d",&src);
	printf("\nThe Path is: \n\n");
	travelingSalesman(src, src); 
	print();
	return 0;
}
