#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Stack
// ---------------------------------
typedef struct Node
{
	int data;
	int prev;
	struct Node* next;
} Node;

Node* top = NULL;

void push(int value, int prev)
{
	struct Node* newNode;
	newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = value;
	newNode->prev = prev;
	if (top == NULL)
	{
		newNode->next = NULL;
	}
	else
	{
		newNode->next = top;
	}

	top = newNode;
}

int pop(int* prev)
{
	if (top == NULL)
	{
		printf("\nStack Underflow\n");
	}
	else
	{
		struct Node* temp = top;
		int temp_data = top->data;
		*prev = top->prev;
		top = top->next;
		free(temp);
		return temp_data;
	}
}

// End of Stack
// ---------------------------------

// Graph 
// -----------------------------------------------------------
typedef struct Graph
{
	int** matr;
	int* nodeIndex;
	int size;
} Graph;


void setRowToZero(int row, Graph* graph)
{
	for (int i = 0; i < graph->size; i++)
	{
		graph->matr[row][i] = 0;
	}
}

void createMatrix(int size, Graph* graph)
{
	graph->size = size;
	graph->nodeIndex = (int*)malloc(size * sizeof(int));
	graph->matr = (int**)malloc(size * sizeof(int*));
	for (int i = 0; i < size; i++)
	{
		graph->nodeIndex[i] = i;
		graph->matr[i] = (int*)malloc(size * sizeof(int));
		setRowToZero(i, graph);
	}
}

void addEdge(int a, int b, int price, Graph* graph)
{
	graph->matr[a][b] = price;
}

void removeEdge(int a, int b, Graph* graph)
{
	graph->matr[a][b] = 0;
}

void addNode(Graph* graph)
{
	graph->nodeIndex = (int*)realloc(graph->nodeIndex, (graph->size + 1) * sizeof(int));
	graph->matr = (int**)realloc(graph->matr, (graph->size + 1) * sizeof(int*));
	for (int i = 0; i < graph->size; i++)
	{
		graph->nodeIndex[i] = i;
		graph->matr[i] = (int*)realloc(graph->matr[i], (graph->size + 1) * sizeof(int));
		graph->matr[i][graph->size] = 0;
	}

	graph->matr[graph->size] = (int*)malloc((graph->size + 1) * sizeof(int));
	graph->size++;
	setRowToZero(graph->size - 1, graph);
}

void removeNode(int index, Graph* graph)
{
	for (int i = 0; i < graph->size; i++)
	{
		graph->matr[i][index] = 0;
	}

	for (int i = index; i < graph->size - 1; i++)
	{
		for (int j = 0; j < graph->size; j++)
		{
			graph->matr[i][j] = graph->matr[i + 1][j];
		}
	}

	// Everything after index move to left
	for (int i = 0; i < graph->size; i++)
	{
		for (int j = index; j < graph->size - 1; j++)
		{
			graph->matr[i][j] = graph->matr[i][j + 1];
		}

		graph->matr[i] = (int*)realloc(graph->matr[i], (graph->size - 1) * sizeof(int));
	}

	graph->matr = (int**)realloc(graph->matr, (graph->size - 1) * sizeof(int*));
	graph->size--;
}

void removeGraph(Graph* graph)
{
	// Everything after index move to left
	for (int i = 0; i < graph->size; i++)
	{
		free(graph->matr[i]);
	}

	free(graph->matr);
	free(graph);
}

void printGraph(Graph* graph)
{
	printf("Number of nodes: %d\n", graph->size);

	for (int i = 0; i < graph->size; i++)
	{
		printf("%2d: ", i);
		for (int j = 0; j < graph->size; j++)
		{
			printf("%7d ", graph->matr[i][j]);
		}

		printf("\n");
	}
}

// End of Graph 
// -----------------------------------------------------------

void readFromFile(Graph* graph)
{
	char fileName[50];
	printf("Ime fajla: \n");
	scanf("%s", fileName);

	FILE* f = fopen(fileName, "r");
	int n;

	fscanf(f, "%d", &n);
	createMatrix(n, graph);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			fscanf(f, "%d", &graph->matr[i][j]);
		}
	}
}

void reversePath(int* path, int pathLength)
{
	for (int i = 0; i < pathLength / 2; i++)
	{
		int temp = path[i];
		path[i] = path[pathLength - i - 1];
		path[pathLength - i - 1] = temp;
	}
}

void printPath(int* path, int pathLength)
{
	for (int i = 0; i < pathLength; i++)
	{
		printf("%d ", path[i]);
		if (i != pathLength - 1)
		{
			printf("-> ");
		}
	}

	printf("\n\n\n\n");
}

void reversePrint(int* path, int pathLength)
{
	for (int i = pathLength - 1; i >= 0; i--)
	{
		printf("%d ", path[i] + 1);
		if (i != 0)
		{
			printf("-> ");
		}
	}

	printf("\n");
}

int minn(int a, int b)
{
	if (a < b)
	{
		return a;
	}

	return b;
}

int getMinimumWeightInPath(Graph* graph, int* path, int pathLength)
{
	int Min = 100000;
	for (int i = 0; i < pathLength - 1; i++)
	{
		Min = minn(Min, graph->matr[path[i]][path[i + 1]]);
	}

	return Min;
}

void decreasePath(Graph* graph, int* path, int pathLength, int weight)
{
	for (int i = 0; i < pathLength - 1; i++)
	{
		graph->matr[path[i]][path[i + 1]] -= weight;
		if (graph->matr[path[i]][path[i + 1]] == 0)
		{
			removeEdge(path[i], path[i + 1], graph);
		}
	}
}

void initToZero(int* arr, int len)
{
	for (int i = 0; i < len; i++)
	{
		arr[i] = 0;
	}
}


int visited[1000];
int previous[1000];

void findAllCycles(Graph* graph, int printCompensation, int createNewGraph)
{
	initToZero(visited, graph->size);
	initToZero(previous, graph->size);

	push(graph->nodeIndex[0], -1);
	while (top != NULL)
	{
		int prev = 0;
		int current = pop(&prev);

		if (visited[current] == 1)
		{
			int* path = malloc((graph->size + 10) * sizeof(int));
			int pathLength = 0;
			int cur = prev;
			
			path[pathLength++] = current;
			while (cur != current && cur != -1)
			{
				path[pathLength++] = cur;
				cur = previous[cur];

				// If it's real cycle, write it
				if (cur == current)
				{
					path[pathLength++] = current;
					reversePath(path, pathLength);
					printPath(path, pathLength);

					int maxCompensation = getMinimumWeightInPath(graph, path, pathLength);
					if (printCompensation)
					{
						printf("Maksimalna kompenzacija za ovaj ciklus je: %d\n\n", maxCompensation);
					}

					if (createNewGraph)
					{
						decreasePath(graph, path, pathLength, maxCompensation);
					}
				}
			}

			continue;
		}

		previous[current] = prev;
		visited[current] = 1;
		for (int i = 0; i < graph->size; i++)
		{
			if (graph->matr[current][i] != 0)
			{
				if (i == previous[current])
				{
					continue;
				}

				push(i, current);
			}
		}

	}
}

void menu()
{
	printf("----------------------\n");
	printf("1 ---> Dodaj cvor\n");
	printf("2 ---> Dodaj granu\n");
	printf("3 ---> Izbrisi cvor\n");
	printf("4 ---> Izbrisi granu\n");
	printf("5 ---> Ispisi graf\n");
	printf("6 ---> Ispisi cikluse \n");
	printf("7 ---> Ispisi cikluse i maksimalne kompenzacije\n");
	printf("8 ---> Resi kompenazijce i novi graf\n");
	printf("9 ---> Izbrisi graf\n");
}

int main()
{
	Graph* graph = (Graph*)malloc(sizeof(Graph));

	int x;
	printf("1 -> Ucitaj iz fajla\n");
	printf("2 -> Napravi graf\n");
	scanf("%d", &x);

	if (x == 1)
	{
		readFromFile(graph);
	}
	else
	{
		int n;
		printf("Unesi inicijalni broj cvorova:\n");
		scanf("%d", &n);
		createMatrix(n, graph);
	}

	while (1)
	{
		menu();
		int x;
		scanf("%d", &x);

		if (x == 1)
		{
			addNode(graph);
			printf("Nov cvor dodat!");
		}
		else if (x == 2)
		{
			printf("Unesite granu a\n");
			int a;
			scanf("%d", &a);
			printf("Unesite granu b\n");
			int b;
			scanf("%d", &b);
			printf("Unesite tezinu: \n");
			int weight;
			scanf("%d", &weight);
			addEdge(a, b, weight, graph);
		}
		else if (x == 3)
		{
			printf("Unesite cvor:\n");
			int n;
			scanf("%d", &n);
			removeNode(n, graph);
		}
		else if (x == 4)
		{
			printf("Unesite granu a\n");
			int a;
			scanf("%d", &a);
			printf("Unesite granu b\n");
			int b;
			scanf("%d", &b);
			removeEdge(a, b, graph);
		}
		else if (x == 5)
		{
			printGraph(graph);
		}
		else if (x == 6)
		{
			findAllCycles(graph, 0, 0);
		}
		else if (x == 7)
		{
			findAllCycles(graph, 1, 0);
		}
		else if (x == 8)
		{
			findAllCycles(graph, 1, 1);
		}
		else if (x == 9)
		{
			removeGraph(graph);
			printf("Graf izbrisan!\n");
			printf("1 - > Ucitaj novi graf iz fajla\n");
			printf("2 - > Sam unesi novi graf\n");
			int n;
			scanf("%d", &n);
			if (n == 1)
			{
				graph = (Graph*)malloc(sizeof(Graph));
				readFromFile(graph);
			}
			else
			{
				printf("Unesite broj cvorova:\n");
				scanf("%d", &n);
				createMatrix(n, graph);
			}
		}
	}

	return 0;
}