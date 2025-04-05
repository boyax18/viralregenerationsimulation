#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 20 
#define INITIAL_VIRUS_COUNT 30 

void displayGrid(int size, int grid[size][size]){
    printf("\033[H\033[J"); 
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%c ", grid[i][j] ? '$' : '.');
        }
        printf("\n");
    }
}

int countNeighbors(int size, int grid[size][size], int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int nx = x + i, ny = y + j;
            if (nx >= 0 && nx < size && ny >= 0 && ny < size){
                count += grid[nx][ny];
            }    
        }
    }
    return count;
}

void updateGrid(int size, int grid[size][size]) {
    int newGrid[size][size];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int neighbors = countNeighbors(size, grid, i, j);
            newGrid[i][j] = (grid[i][j] && (neighbors == 2 || neighbors == 3)) || (!grid[i][j] && neighbors == 3);
        }
    }
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            grid[i][j] = newGrid[i][j];
        }    
    }        
}

void RandomVirus(int size, int grid[size][size]) {
    srand(time(NULL));
    int count = 0;
    while (count < INITIAL_VIRUS_COUNT) {
        int virus=13;
        int x = rand() % size;
        int y = rand() % size;
        if (grid[x][y] == 0) {
            grid[x][y] = 1;
            count++;
        }
    }
}

int main() {
    int size;
    printf("\n ***** VIRUS SIMULATION ***** ");
    printf("\n\nEnter the size of the grid (10 - %d): ", MAX_SIZE);
    scanf("%d", &size);
    
    if (size <= 0 || size > MAX_SIZE) {
        printf("\n\nInvalid size. Using default size %d.\n", MAX_SIZE);
        size = MAX_SIZE;
        return 0;
    }
    
    int grid[size][size];
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            grid[i][j] = 0;
        }    
    }
    
    RandomVirus(size, grid);
    
    while(1) {
        displayGrid(size, grid);
        updateGrid(size, grid);
        usleep(500000);
    }
    
    
    
    return 0;
}
    