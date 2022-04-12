#include <iostream>

/* CONTADOR DE PALABRAS EN ESPERA EL SPLIT */
int wordCounter(char* c){
    char *aux;
    aux = c;
    int res = 1;
    while (*aux != '\0'){
        if(*aux == ' '){
            res++;
        }
        aux++;
    }
    return res;
}

/* QUE IMPRIME LA COSA ESTA? */
typedef int(*pf)(int,int);
int s (int a, int b){
    return a+b;
}

int r (int a, int b){
    return a-b;
}

template <typename T>
class clase{
    private:
        int _x;
    public:
        clase(int x):_x(x){};
        void operator () (T p, int y){
            _x = p(_x,y);
            std::cout<<y<<" "<<_x<<std::endl;
        };
        void print(){
            std::cout<<_x;
        };
};

/* 1 1 || 8 -7 */

int main(){

//    char pal[]  = "Lorem Ipsum es    simplemente el texto de relleno de las imprentas y archivos de texto. Lorem Ipsum ha sido el texto de relleno estándar de las industrias desde el año 1500, cuando un impresor (N. del T. persona que se dedica a la imprenta) desconocido usó una galería de textos y los mezcló de tal manera que logró hacer un libro de textos especimen. No sólo sobrevivió 500 años, sino que tambien ingresó como texto de relleno en documentos electrónicos, quedando esencialmente igual al original. Fue popularizado en los 60s con la creación de las hojas las cuales contenian pasajes de Lorem Ipsum, y más recientemente con software de autoedición, como por ejemplo Aldus PageMaker, el cual incluye versiones de Lorem Ipsum.";
//    std::cout<<wordCounter(pal);



//    int n[]={1,8,3,7,2,9,5,6,4};
//    int m[]={0,1,1,0,1,1,0,0,1};
//    pf q[] = {s,r};
//    clase<pf> A(0);
//
//    for (int i = 0; i < 9; ++i) {
//        A(q[m[i]],n[i]);
//    }
//
//    A.print();


}
