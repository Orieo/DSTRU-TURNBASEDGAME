#include <stdio.h>
#include <string.h>

#define MAX_POSITIONS 16 // Max area from (A x A) where A = {1,2,3,4}

// Initialize the system
void initialize_system(int Uno[][2], int Dos[][2], int Tres[][2], int* turn, int* go) {
	int i, j, initialized=1;
	
	// Ensure sets are empty
	for (i=0; i<MAX_POSITIONS; i++) {
        for (j=0; j<2; j++) {
            if (Uno[i][j]!= 0||Dos[i][j]!= 0||Tres[i][j]!= 0) {
                initialized=0;
            }
        }
    }
	
    *turn=1; 
    *go=0; 
    
	if(initialized){
		printf("System initialized.\n");
		printf("Uno, Dos, Tres are empty.\n");
	}
	
    if(*turn)
		printf("turn = true\n");
	else
		printf("turn = false\n");

	if(*go)
		printf("go = true\n");
	else
		printf("go = false\n");
}

//Calculate Size
int calculate_size(int Set[][2]){
    int i, count=0;
	
    for (i=0; i<MAX_POSITIONS; i++) {
        if (Set[i][0]!=0&&Set[i][1]!=0){
            count++;
        }
    }
    return count;
}

//Uno U Tres
int
uno_union_tres(int Uno[][2], int Tres[][2], int Union[][2], int uno_size, int tres_size){
	int i=0, j=0, k=0, UNION=0, found=0;
	
	//add everything in uno to union
	for(i=0; i<uno_size; i++){
		Union[UNION][0]=Uno[i][0];
		Union[UNION][1]=Uno[i][1];
		UNION++;
	}
	
	//add elements of tres to union if not in uno
	for(j=0; j<tres_size; j++){
		found=0;//assume element is not in uno
		
		for(k=0; k<uno_size; k++){
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

//F=P-(Uno U Tres)
int
UpdateF(int P[][2], int Uno[][2], int Tres[][2], int F[][2]){
	int i=0, j=0, k=0, index=0, found=0, shift=0;
	int union_size, uno_size, tres_size;
	int Union[2*MAX_POSITIONS][2];
	
	uno_size=calculate_size(Uno);
	tres_size=calculate_size(Tres);
	union_size=uno_union_tres(Uno, Tres, Union, uno_size, tres_size);//Uno U Tres
	
	//store everything in P to F
	for(i=0; i<MAX_POSITIONS; i++){
		F[index][0]=P[i][0];
		F[index][1]=P[i][1];
		index++;
	}
	
	//remove from F if in Union
	for(j=0; j<index; j++){
		found=0;
		
		for(k=0; k<union_size; k++){
			if(F[j][0]==Union[k][0]&&F[j][1]==Union[k][1])
				found=1;
		}
		
		if(found){
			//shift element to the left to remove current element
			for (shift=j; shift<index-1; shift++) {
				F[shift][0] = F[shift+1][0];
				F[shift][1] = F[shift+1][1];
				F[shift+1][0] = 0;
				F[shift+1][1] = 0;
			}
			
			//Special case: if there is only one element left
			if (index == 1) {
				F[0][0] = 0;
				F[0][1] = 0;
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
		int turn, go, over=0;
		int Uno[MAX_POSITIONS][2]={0};
		int Dos[MAX_POSITIONS][2]={0};
		int Tres[MAX_POSITIONS][2]={0};
		int F[MAX_POSITIONS][2]={0};
	
	//System initialization
		initialize_system(Uno, Dos, Tres, &turn, &go);
	
	//Sytem Facts
		//F=P-(Uno U Tres)
		int F_size;
		F_size=UpdateF(P, Uno, Tres, F); 
		
		//W=C-T
		int W[4][4][2]={{{1,1}, {1,2}, {1,3}, {1,4}},
						{{1,1}, {2,2}, {3,3}, {4,4}},
						{{1,4}, {2,3}, {3,2}, {4,1}},
						{{4,1}, {4,2}, {4,3}, {4,4}}};
		
		//over ↔ (Uno ∈ W ∨ Tres ∈ W ∨ F = ∅)
		if(F_size==0||Uno ∈ W ∨ Tres ∈ W)
			over=1;
	
	//System states and behavior
	
    return 0;
}