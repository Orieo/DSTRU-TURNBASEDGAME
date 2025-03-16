#include <stdio.h>
#include <stdbool.h>

#define MAX_POSITIONS 16 // Max area from (A x A) where A = {1,2,3,4}

// Define sets as arrays (initialized as empty)
int Uno[MAX_POSITIONS];
int Dos[MAX_POSITIONS];
int Tres[MAX_POSITIONS];
int uno_size = 0, dos_size = 0, tres_size = 0;

// Boolean variables
bool turn = true;
bool go = false;

// Initialize the system
void initialize_system() {
    uno_size = dos_size = tres_size = 0; // Ensure sets are empty
    turn = true; 
    go = false; 
    
    printf("System initialized.\n");
    printf("Uno, Dos, Tres are empty.\n");
    printf("turn = %s\n", turn ? "true" : "false");
    printf("go = %s\n", go ? "true" : "false");
}

int main() {
    initialize_system();
    return 0;
}