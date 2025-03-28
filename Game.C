#include <stdio.h>
#include <stdbool.h>

#define MAX_POSITIONS 16 // Max area from (A x A) where A = {1,2,3,4}

// Initialize the system
void initialize_system(int uno_size, int dos_size, int tres_size, int turn, int go) {
    uno_size = dos_size = tres_size = 0; // Ensure sets are empty
    turn = 1; 
    go = 0; 
    
    printf("System initialized.\n");
    printf("Uno, Dos, Tres are empty.\n");
    printf("turn = %s\n", "true");
    printf("go = %s\n", "false");
}

//Uno U Tres
int
UnoUnionTres(int Uno[][2], int Tres[][2], int Union[][2], int UNO, int TRES){
	int i=0, j=0, k=0, UNION=0, found=0;
	
	//add everything in uno to union
	for(i=0; i<UNO; i++){
		Union[UNION][0]=Uno[i][0];
		Union[UNION][1]=Uno[i][1];
		UNION++;
	}
	
	//add elements of tres to union if not in uno
	for(j=0; j<TRES; j++){
		found=0;//assume element is not in uno
		
		for(k=0; k<UNO; k++){
			if(Uno[k][0]==Tres[j][0]&&Uno[k][1]==Tres[j][1])
				found=1;
		}
		
		if(!found){//if not found, add to union
			Union[UNION][0]=Tres[j][0];
			Union[UNION][1]=Tres[j][1];
			UNION++;
		}
	}
	
	return UNION;
}

int
PMinusUnion(int P[][2], int Union[][2], int F[][2], int UNO){
	int i=0, j=0, k=0, index=0, found=0, shift=0;
	
	//store everything in P to F
	for(i=0; i<MAX_POSITIONS; i++){
		F[index][0]=P[i][0];
		F[index][1]=P[i][1];
		index++;
	}
	
	//remove from F if in Union
	for(j=0; j<index; j++){
		found=0;
		
		for(k=0; k<UNO; k++){
			if(F[j][0]==Union[k][0]&&F[j][1]==Union[k][1])
				found=1;
		}
		
		if(found){
			for (shift=j; shift<index-1; shift++) {
				F[shift][0] = F[shift+1][0];
				F[shift][1] = F[shift+1][1];
			}
			
			index--;
			j--;
		}
	}
	
	return index;
}

int main() {
	
	//Applicable Sets
	int A[4]={1, 2, 3, 4};
	int P[16][2]={{1,1}, {1,2}, {1,3}, {1,4}, 
				  {2,1}, {2,2}, {2,3}, {2,4}, 
				  {3,1}, {3,2}, {3,3}, {3,4}, 
				  {4,1}, {4,2}, {4,3}, {4,4}};
	int B[2]={1,0};
	int C[4][4][2]={{{1,1}, {1,2}, {1,3}, {1,4}},
					{{1,1}, {2,2}, {3,3}, {4,4}},
					{{1,4}, {2,3}, {3,2}, {4,1}},
					{{4,1}, {4,2}, {4,3}, {4,4}}};
	int T[4][2]={{1,1}, {2,2}, {3,3}, {4,4}};
	
	//System variables
	int uno_size, dos_size, tres_size;
	int turn, go, over=0;
	
	initialize_system(uno_size, dos_size, tres_size, turn, go);
	
	int Uno[uno_size][2];
	int Dos[dos_size][2];
	int Tres[tres_size][2];
	int F[MAX_POSITIONS][2];
	
	//Sytem Facts
	int Union[uno_size+tres_size][2];
	int union_size;
	union_size=UnoUnionTres(Uno, Tres, Union, uno_size, tres_size);//Uno U Tres
	int F_size;
	F_size=PMinusUnion(P, Union, F, uno_size); //F=P-(Uno U Tres)
	
    return 0;
}