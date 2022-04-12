#include <iostream>
#include "Node/node.h"
//#include "CircularLinkedList/circularlinkedlist.h"
#include "LinkedList/linkedlist.h"

typedef LinkedList<int> ListaEntera;

template <typename T>
bool par(T _dataEvaluate){
    return _dataEvaluate % 2 == 0;
}

template <typename T>
void split(Node<T>* &L, Node<T>* &L1, Node<T>* &L2, bool(*decide)(T) ){
    Node<T> *t1,*t2;
    t1 = nullptr;
    t2 = nullptr;
    while(L){
        if(decide(L->data)){
            if(!L1){
                L1 = L;
                t1 = L;
                //L = L->next;
            }else{
                t1->next = L;
                t1 = L;
                //L = L->next;
            }
        }else{
            if(!L2){
                L2 = L;
                t2 = L;
                //L = L->next;
            }else{
                t2->next = L;
                t2 = L;
                //L = L->next;
            }
        }
        L = L->next;
    }
    t1->next = nullptr;
    t2->next = nullptr;
}

//template <class T>
//void split(Node<T> *&LImpar, Node<T> *&LPar){
//    Node<T> *aux1, *aux2;
//    aux1 = LImpar;
//    aux2 = nullptr;
//    while (aux1){
//        if (aux1->data % 2 == 0){
//            if (!LPar){
//                LPar = aux1;
//            } else{
//                LPar->next = aux1;
//            }
//            aux1 = aux1->next;
//        } else{
//            if (!aux2){
//                aux2 = aux1;
//                LImpar = aux2;
//                //LImpar->next = nullptr;
//            } else{
//                aux2 = aux1;
//                LImpar->next = aux2;
//            }
//            aux1 = aux1->next;
//        }
//        //aux1->next = nullptr;
//        aux2->next = nullptr;
//    }
//}

int main(){
	ListaEntera A;
	A.add(10);
	A.add(12);
	A.add(15);
	A.add(17);
    A.add(20);

    ListaEntera B;
    ListaEntera C;
//
    split(A.head,B.head,C.head, par);

    A.print();
    B.print();
    C.print();
    //split(A.head,l1.head,l2.head);


	//A.print();

	return 0;
}