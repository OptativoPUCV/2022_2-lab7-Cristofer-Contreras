#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

typedef struct nodo{
   void* data;
   int priority;
}heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capac;
} Heap;


void* heap_top(Heap* pq){
  if(pq->size == 0) return NULL;
  
  return (void*)pq->heapArray[0].data;
}



void heap_push(Heap* pq, void* data, int priority){
  if(pq->size+1 > pq->capac){
    pq->capac = pq->capac*2+1;
    pq->heapArray = (heapElem*)realloc(pq->heapArray,sizeof(heapElem)*pq->capac);
  }
  pq->heapArray[pq->size].data = data;
  pq->heapArray[pq->size].priority = priority;
  int max = (pq->size-1)/2;
  int min = pq->size;
  heapElem* elemAux = (heapElem*)malloc(sizeof(heapElem));

  while(min > 0){
    if(pq->heapArray[min].priority > pq->heapArray[max].priority){
      *elemAux = pq->heapArray[max];
      pq->heapArray[max] = pq->heapArray[min];
      pq->heapArray[min] = *elemAux;
    }
    min = max;
    max = (min-1)/2;
  }
  pq->size++;
}


void heap_pop(Heap* pq){
  pq->size--;
  pq->heapArray[0] = pq->heapArray[pq->size];

  int prio = pq->heapArray[0].priority;
  int current = 1;

  while(((current <= pq->size) && (pq->heapArray[current].priority > prio))||((current <= pq->size) && (pq->heapArray[current+1].priority > prio))){
    heapElem aux = pq->heapArray[(current-1)/2];
    if(pq->heapArray[current+1].priority > prio)
      current++;
    pq->heapArray[(current-1)/2] = pq->heapArray[current];
    pq->heapArray[current] = aux;
    current = 2*current+1;
  }
}
    

Heap* createHeap(){
  Heap* Nheap = (Heap*)malloc(sizeof(Heap));
  Nheap-> capac = 3;
  Nheap->size = 0;

  Nheap->heapArray= (heapElem*)malloc(3*sizeof(heapElem));  
  return Nheap;
}
