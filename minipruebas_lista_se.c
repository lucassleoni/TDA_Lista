#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void mostrar_elemento(void* elemento){
    if(elemento){
      printf("%c ", *(char*)elemento);
    }
}

void ejecutar_caso_feliz(){
    lista_t* lista = lista_crear();
  
    char a = 'a', b = 'b', c = 'c', d = 'd', w = 'w';

    lista_insertar(lista, &a);
    lista_insertar(lista, &c);
    lista_insertar_en_posicion(lista, &d, 100);
    lista_insertar_en_posicion(lista, &b, 1);
    lista_insertar_en_posicion(lista, &w, 3);
  
    lista_borrar_de_posicion(lista, 3);

    printf("Elementos en la lista: ");
    for(size_t i = 0; i < lista_elementos(lista); i++){
        printf("%c ", *(char*)lista_elemento_en_posicion(lista, i));
    }
    printf("\n");

    
    lista_iterador_t* iterador = lista_iterador_crear(lista);    
    while(lista_iterador_tiene_siguiente(iterador)){
        printf("%c ", *(char*)lista_iterador_siguiente(iterador));
    }
    printf("\n");

    lista_iterador_destruir(iterador);

    printf("Imprimo la lista usando el iterador interno: ");
    lista_con_cada_elemento(lista, mostrar_elemento);
    printf("\n");
  
    lista_destruir(lista);
}

int main(){
    system("clear");

    ejecutar_caso_feliz();

    return 0;
}