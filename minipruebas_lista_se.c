#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

#define LISTA_VACIA 0

// Pre C.: Recibe un puntero a la lista.
// Post C.: Inserta 5 elementos en la lista.
void lista_insertar_seis_elementos(lista_t** lista){
    if(lista == NULL){
        return;
    }

    char elemento_1 = 'A', elemento_2 = 'L', elemento_3 = 'G', elemento_4 = 'O', elemento_5 = 'I';

    lista_insertar(*lista, &elemento_1);
    lista_insertar(*lista, &elemento_2);
    lista_insertar(*lista, &elemento_3);
    lista_insertar(*lista, &elemento_4);
    lista_insertar(*lista, &elemento_5);
    lista_insertar(*lista, &elemento_5);
}


// Función para el testeo del iterador interno:

// Pre C.: Recibe un puntero a un elemento.
// Post C.: Muestra el elemento por pantalla.
void mostrar_elemento(void* elemento){
    if(elemento){
        printf("%c ", *(char*)elemento);
    }
}


// Pruebas (testing) para la lista:

// Pre C.: ---
// Post C.: Ejecuta las pruebas provistas por la cátedra.
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
        printf("%c ", *(int*)lista_elemento_en_posicion(lista, i));
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
    printf("\n\n");
  
    lista_destruir(lista);
}

// Pre C.: ---
// Post C.: Inserta un elemento y luego verifica si la lista no quedó vacía, imprimiendo el resultado de la prueba por pantalla.
void luego_de_insertar_elemento_la_lista_no_esta_vacia(){
    lista_t* lista = lista_crear();

    printf("Prueba #1: Verificar si la lista dejar de estar vacía luego de insertar un elemento.\n");

    int elemento = 1469;
    lista_insertar(lista, &elemento);
    printf("\t%s: Luego de insertar un elemento la lista %s vacía. \n",
          (!lista_vacia(lista))?"EXITO":"FALLO",
          (!lista_vacia(lista))?"dejar de estar":"sigue");
    
    lista_destruir(lista);
}

// Pre C.: ---
// Post C.: Luego de insertar 5 elementos, intenta insertar otro en una posición inválida (superior al tamaño), y verfica
//          si este se insertó al final de la lista, imprimiendo el resultado de la prueba por pantalla.
void si_inserto_un_elemento_en_una_posicion_invalida_deberia_insertarse_al_final(){
    lista_t* lista = lista_crear();
    
    printf("\nPrueba #2: Verificar si al insertar un elemento en un posición inválida, este se inserta al final de la lista.\n");

    char elemento_extra = 'W';
    size_t posicion_superior_al_tamanio = 10;
    lista_insertar_seis_elementos(&lista);
    lista_insertar_en_posicion(lista, &elemento_extra, posicion_superior_al_tamanio);

    printf("\t%s: Al insertar en una posición inválida, el elemento %s al final de la lista.\n",
          (lista_ultimo(lista) == (void*)&elemento_extra)?"EXITO":"FALLO",
          (lista_ultimo(lista) == (void*)&elemento_extra)?"se inserta":"no se inserta");

    lista_destruir(lista);
}

// Pre C.: ---
// Post C.: Intenta borrar un elemento en una posición inválida (superior al tamaño), y luego verifica si se borró el último de la lista,
//          imprimiendo el resultado de la prueba por pantalla.
void si_borro_un_elemento_de_una_posicion_invalida_deberia_borrarse_el_ultimo_de_la_lista(){
    lista_t* lista = lista_crear();
    
    printf("\nPrueba #3: Verificar si al borrar un elemento de un posición inválida, se borra el último de la lista.\n");

    size_t posicion_invalida = 10;

    char elemento_1 = 'L', elemento_2 = 'U', elemento_3 = 'K', elemento_4 = 'E';

    lista_insertar(lista, &elemento_1);
    lista_insertar(lista, &elemento_2);
    lista_insertar(lista, &elemento_3);
    lista_insertar(lista, &elemento_4);
    lista_borrar_de_posicion(lista, posicion_invalida);

    printf("\t%s: Al borrar un elemento de una posición inválida, %s el último de la lista.\n",
          (lista_ultimo(lista) == (void*)&elemento_3)?"EXITO":"FALLO",
          (lista_ultimo(lista) == (void*)&elemento_3)?"se borra":"no se borra");

    lista_destruir(lista);
}

// Pre C.: ---
// Post C.: Intenta buscar un elemento en una posición invalida (superior al tamaño) y verifica si la funcion utilzada devuelve NULL,
//          imprimiendo el resultado de la prueba por pantalla..
void si_pido_un_elemento_de_una_posicion_invalida_deberia_devolver_NULL(){
    lista_t* lista = lista_crear();

    printf("\nPrueba #4: Verificar si al pedir un elemento de un posición inválida, la función devuelve NULL.\n");

    size_t posicion_invalida = 10;
    lista_insertar_seis_elementos(&lista);

    printf("\t%s: Al pedir un elemento de un posición inválida, la función %s NULL.\n",
          (lista_elemento_en_posicion(lista, posicion_invalida) == NULL)?"EXITO":"FALLO",
          (lista_elemento_en_posicion(lista, posicion_invalida) == NULL)?"devuelve":"no devuelve");

    lista_destruir(lista);
}

// Pre C.: ---
// Post C.: Verifica si el último elemento de una lista vacía es NULL, imprimiendo el resultado de la prueba por pantalla.
void si_la_lista_esta_vacia_entonces_el_ultimo_elemento_deberia_ser_NULL(){
    lista_t* lista = lista_crear();

    printf("\nPrueba #5: Verificar si el último elemento de una lista vacía es NULL.\n");

    printf("\t%s: El último elemento de una lista vacía %s NULL.\n",
          (lista_ultimo(lista) == NULL)?"EXITO":"FALLO",
          (lista_ultimo(lista) == NULL)?"es":"no es");

    lista_destruir(lista);
}

// Pre C.: ---
// Post C.: Verifica si la cantidad de elementos de una lista vacía es '0', imprimiendo el resultado de la prueba por pantalla.
void si_la_lista_esta_vacia_entonces_la_cantidad_de_elementos_deberia_ser_cero(){
    lista_t* lista = lista_crear();

    printf("\nPrueba #6: Verificar si la cantidad de elementos de una lista vacía es cero.\n");

    printf("\t%s: La cantidad de elementos de una lista vacía %s cero.\n",
          (lista_elementos(lista) == LISTA_VACIA)?"EXITO":"FALLO",
          (lista_elementos(lista) == LISTA_VACIA)?"es":"no es");

    lista_destruir(lista);
}


/* --------------------------------------------------------------------------------------------------------------------------*/


// Pruebas (testing) para la lista:

// Pre C.: ---
// Post C.: Crea una lista con 5 nodos y verifica si, al avanzar al nodo siguiente (estando posicionado en el último de ellos),
//          la función 'lista_iterador_siguiente()' devuelve NULL, imprimiendo el resultado de la prueba por pantalla.
void si_ejecuto_iterador_siguiente_en_el_ultimo_nodo_deberia_devolver_NULL(){
    lista_t* lista = lista_crear();
    lista_iterador_t* iterador = lista_iterador_crear(lista);

    printf("\nPrueba #7: Verificar si avanzar al nodo siguiente (estando parado en el nodo fin) devuelve NULL.\n");

    lista_insertar_seis_elementos(&lista);

    for(int i = 0; i < lista_elementos(lista); i++){
        lista_iterador_siguiente(iterador);
    }

    printf("\t%s: Avanzar al nodo siguiente (estando parado en el nodo fin) %s NULL.\n",
          (lista_iterador_siguiente(iterador) == NULL)?"EXITO":"FALLO",
          (lista_iterador_siguiente(iterador) == NULL)?"devuelve":"no devuelve");

    lista_iterador_destruir(iterador);
    lista_destruir(lista);
}


int main(){
    system("clear");

    ejecutar_caso_feliz();

    luego_de_insertar_elemento_la_lista_no_esta_vacia();
    si_inserto_un_elemento_en_una_posicion_invalida_deberia_insertarse_al_final();
    si_borro_un_elemento_de_una_posicion_invalida_deberia_borrarse_el_ultimo_de_la_lista();
    si_pido_un_elemento_de_una_posicion_invalida_deberia_devolver_NULL();
    si_la_lista_esta_vacia_entonces_el_ultimo_elemento_deberia_ser_NULL();
    si_la_lista_esta_vacia_entonces_la_cantidad_de_elementos_deberia_ser_cero();
    si_ejecuto_iterador_siguiente_en_el_ultimo_nodo_deberia_devolver_NULL();

    return 0;
}