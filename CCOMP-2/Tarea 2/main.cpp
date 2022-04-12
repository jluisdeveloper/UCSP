#include <iostream>

void print(int* Array, int size){
	int* tam = Array + size-1;
	for(; Array <= tam; Array++){
		std::cout << *Array << std::endl;
	}
}

void swap(int &a, int &b){
	int aux;
	aux = a;
	a = b;
	b = aux;
}

void CocktailSort(int* a, int n){ 
	bool stateMachine = true; 
	int* start = a; 
	int* end = a+n-1; 

	while(stateMachine){
		stateMachine = false;
		for(int* i = start; i < end; i++){
			if (*i > *(i+1)) {
				swap(*i , *(i+1));
				stateMachine = true;
			}			
		}
		if (!stateMachine) 
			break; 
		stateMachine = false; 
		end--;
		for(int* j = end-1; j>=start ;j--){
			if (*j > *(j+1)) {
				swap(*j , *(j+1));
				stateMachine = true;
			}			
		}
		start++;
	}
} 

void CocktailSortv2(int* a, int size){
    bool stateMachine = true;
    int* start = a;
    int* end = a+size-1;
	int* left = start;
	int* right = end-1;

	while(stateMachine){
        stateMachine = false;
        for(; left < end; left++){
            if(*left > *(left+1)){
                swap(*left,*(left+1));
                stateMachine = true;
            }
        }
        if (!stateMachine)
            break;
        stateMachine = false;
        end--;
        for(; right>= start; right--){
            if(*right > *(right+1)){
                swap(*right, *(right+1));
                stateMachine = true;
            }
        }
        start++;   

		left = start;
		right = end;
    }
	/* std::cout<<*start<<"  "<<*end<<std::endl;
	std::cout<<*left<<"  "<<*right<<std::endl; */
}

void CocktailSortv3(int* a, int size){
    bool stateMachine = true;
    int* start = a;
    int* end = a+size-1;
	int* left = start;
	int* right = end-1;

	while(stateMachine){
        stateMachine = false;
		while(left < end){
			if(*left > *(left+1)){
                swap(*left,*(left+1));
                stateMachine = true;
            }
			left++;
		}
        if (!stateMachine)
            break;
        stateMachine = false;
        end--;
		while(right >= start){
			if(*right > *(right+1)){
                swap(*right, *(right+1));
                stateMachine = true;
            }
			right--;
		}
        start++;   

		left = start;
		right = end;
    }
}

int main(){	

	/* int arr[] = { 52, 1, 15, 2, 8, 0, 2, 10, 90, 11, 3, -5 }; 
	int n = sizeof(arr) / sizeof(arr[0]); 
	CocktailSortv3(arr, n); 
	print(arr,n); */

	/* char cadena[10] = "Hola";
	char *c;
	int *n;
	void *v;
	c = cadena; // c apunta a cadena
	n = (int *)cadena; // n también apunta a cadena
	v = (void *)cadena; // v también
	std::cout << "carácter: " << c << std::endl;
	std::cout << "entero:" << *n << std::endl;
	std::cout << "float:" << *(float *)v << std::endl; */

	int a = 58;
	int *p = &a;
	int n = (int)p;

	std::cout<<n<<std::endl;

	return 0;
}