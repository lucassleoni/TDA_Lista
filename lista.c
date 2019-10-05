#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

#define ERROR -1
#define EXITO 0
#define LISTA_VACIA 0

typedef struct nodo{
	void* elemento;
	struct nodo* siguiente;
} nodo_t;

typedef struct lista{
	nodo_t* nodo_inicio;
	nodo_t* nodo_fin;
	size_t cantidad;
}lista_t;

typedef struct lista_iterador{
	nodo_t* corriente;
	lista_t* lista;
}lista_iterador_t;


/*
 * Crea la lista reservando la memoria necesaria.
 * Devuelve un puntero a la lista creada o NULL en caso de error.
 */
lista_t* lista_crear(){
	lista_t* lista = malloc(sizeof(lista_t));
	if(lista == NULL){
		return NULL;
	}

	lista->nodo_inicio = NULL;
	lista->nodo_fin = NULL;
	lista->cantidad = LISTA_VACIA;

	return lista;
}

// Pre C.: Se debe recibir un puntero al struct lista_t lista.
// Post C.: Devuelve 'true' si hay algún error que invalide la lista.
bool hay_error_lista(lista_t* lista){
	return ((lista == NULL) ||
		   (((lista->nodo_inicio) == NULL) && ((lista->nodo_fin) != NULL)) ||
		   (((lista->nodo_inicio) != NULL) && ((lista->nodo_fin) == NULL)));
}

/* 
 * Devuelve true si la lista está vacía o false en caso contrario.
 */
bool lista_vacia(lista_t* lista){
	return ((hay_error_lista(lista)) || (lista->cantidad == LISTA_VACIA));
}

// Pre C.: Recibe un puntero a la lista y la posición buscada.
// Post C.: Devuelve un puntero al nodo en la posicón buscada o NULL en caso de error.
nodo_t* buscar_nodo(lista_t* lista, size_t posicion){
	if((lista_vacia(lista)) || (posicion >= lista->cantidad)){
		return NULL;
	}

	size_t contador_posicion_buscada = 0;
	nodo_t* nodo_buscado = lista->nodo_inicio;

	while(contador_posicion_buscada < posicion){
		if(nodo_buscado != NULL){
			nodo_buscado = nodo_buscado->siguiente;
		}
		contador_posicion_buscada++;
	}

	return nodo_buscado;
}

/*
 * Inserta un elemento al final de la lista.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 */
int lista_insertar(lista_t* lista, void* elemento){
	if(hay_error_lista(lista)){
		return ERROR;
	}

	nodo_t* nodo = malloc(sizeof(nodo_t));
	if(nodo == NULL){
		return ERROR;
	}

	if(lista_vacia(lista)){
		lista->nodo_inicio = nodo;
		lista->nodo_fin = nodo;
	}
	else{
		lista->nodo_fin->siguiente = nodo;
		lista->nodo_fin = nodo;
	}

	nodo->elemento = elemento;
	nodo->siguiente = NULL;
	(lista->cantidad)++;

	return EXITO;
}

/*
 * Inserta un elemento en la posicion indicada,
 * Donde '0' es insertar como primer elemento y '1' es insertar luego del primer elemento.
 * En caso de no existir la posicion indicada, lo inserta al final.
 * Devuelve '0' si pudo insertar o '-1' si no pudo.
 */
int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){
	if(hay_error_lista(lista)){
		return ERROR;
	}

	if(posicion >= lista->cantidad){
		lista_insertar(lista, elemento);
		return EXITO;
	}

	nodo_t* nodo = malloc(sizeof(nodo_t));
	if(nodo == NULL){
		return ERROR;
	}

	if(posicion == 0){
		nodo->siguiente = lista->nodo_inicio;
		lista->nodo_inicio = nodo;
	}
	else{
		nodo_t* nodo_aux = buscar_nodo(lista, posicion-1);
		nodo->siguiente = nodo_aux->siguiente;
		nodo_aux->siguiente = nodo;
	}

	nodo->elemento = elemento;
	(lista->cantidad)++;

	return EXITO;
}

/*
 * Quita de la lista el elemento que se encuentra en la ultima posición.
 * Devuelve 0 si pudo eliminar o -1 si no pudo.
 */
int lista_borrar(lista_t* lista){
	if(lista_vacia(lista)){
		return ERROR;
	}

	if((lista->cantidad) == 1){
		free(lista->nodo_fin);
		lista->nodo_inicio = NULL;
		lista->nodo_fin = NULL;
	}
	else{
		nodo_t* nodo_aux = buscar_nodo(lista, (lista->cantidad)-2);
		free(lista->nodo_fin);
		lista->nodo_fin = nodo_aux;
		lista->nodo_fin->siguiente = NULL;
	}

	(lista->cantidad)--;

	return EXITO;
}

// Pre C.: Recibe un puntero a la lista y un puntero a un nodo auxiliar.
// Post C.: Elimina el nodo inidial de la lista.
void lista_borrar_nodo_inicial(lista_t* lista, nodo_t* nodo_aux){
	if(lista_vacia(lista)){
		return;
	}
	
	nodo_aux = lista->nodo_inicio->siguiente;
	free(lista->nodo_inicio);
	lista->nodo_inicio = nodo_aux;
}

/*
 * Quita de la lista el elemento que se encuentra en la posición
 * indicada, donde 0 es el primer elemento.  
 * En caso de no existir esa posición se intentará borrar el último
 * elemento.  
 * Devuelve 0 si pudo eliminar o -1 si no pudo.
 */
int lista_borrar_de_posicion(lista_t* lista, size_t posicion){
	if(lista_vacia(lista)){
		return ERROR;
	}

	nodo_t* nodo_aux = NULL;

	if(posicion >= lista->cantidad){
		lista_borrar(lista);
		return EXITO;
	}

	if(posicion == 0){
		lista_borrar_nodo_inicial(lista, nodo_aux);
	}
	else{
		nodo_aux = buscar_nodo(lista, posicion-1);
		nodo_t* nodo_aux_2 = nodo_aux->siguiente->siguiente;
		free(nodo_aux->siguiente);
		nodo_aux->siguiente = nodo_aux_2;
	}

	(lista->cantidad)--;

	return EXITO;
}

/*
 * Devuelve el elemento en la posicion indicada, donde 0 es el primer
 * elemento.
 *
 * Si no existe dicha posicion devuelve NULL.
 */
void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){
	if((lista_vacia(lista)) || (posicion >= lista->cantidad)){
		return NULL;
	}
	nodo_t* nodo = buscar_nodo(lista, posicion);

	return (nodo->elemento);
}

/* 
 * Devuelve el último elemento de la lista o NULL si la lista se
 * encuentra vacía.
 */
void* lista_ultimo(lista_t* lista){
	if(lista_vacia(lista)){
		return NULL;
	}

	return (lista->nodo_fin->elemento);
}

/*
 * Devuelve la cantidad de elementos almacenados en la lista.
 */
size_t lista_elementos(lista_t* lista){
	if(lista_vacia(lista)){
		return LISTA_VACIA;
	}
	return (lista->cantidad);
}

/*
 * Libera la memoria reservada por la lista.
 */
void lista_destruir(lista_t* lista){
	while(!lista_vacia(lista)){
		lista_borrar(lista);
	}
	free(lista);
}

// Pre C.: Recibe la estructura del iterador externo.
// Post C.: Devuelve 'true' si la lista a la que apunta el iterador es nula y 'false' en caso contrario.
bool lista_iterador_es_nula(lista_iterador_t* iterador){
	return (iterador->lista == NULL);
}


/* ------------------------------------------------------------------------------------------------------------------------------------------------ */


/*
 * Crea un iterador para una lista. El iterador creado es válido desde
 * el momento de su creación hasta que no haya mas elementos por
 * recorrer o se modifique la lista iterada (agregando o quitando
 * elementos de la lista).
 *
 * Devuelve el puntero al iterador creado o NULL en caso de error.
 */
lista_iterador_t* lista_iterador_crear(lista_t* lista){
	if(hay_error_lista(lista)){
		return NULL;
	}

	lista_iterador_t* iterador = malloc(sizeof(lista_iterador_t));
	if(iterador == NULL){
		return NULL;
	}

	iterador->corriente = NULL;
	iterador->lista = lista;

	return iterador;
}

/*
 * Devuelve true si hay mas elementos sobre los cuales iterar o false
 * si no hay mas.
 */
bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
	if((lista_iterador_es_nula(iterador)) || (lista_vacia(iterador->lista))){
		return false;
	}

	if(((iterador->corriente) == NULL) && (!lista_vacia(iterador->lista))){
		return true;
	}

	return ((iterador->corriente->siguiente) != NULL);
}

/*
 * Avanza el iterador al proximo elemento y lo devuelve.
 * En caso de error devuelve NULL.
 */
void* lista_iterador_siguiente(lista_iterador_t* iterador){
	if(lista_iterador_es_nula(iterador)){
		return NULL;
	}

	if((iterador->corriente) == NULL){
		iterador->corriente = iterador->lista->nodo_inicio;
	}
	else if(lista_iterador_tiene_siguiente(iterador)){
		iterador->corriente = iterador->corriente->siguiente;
	}

	void* elemento = iterador->corriente->elemento;

	return elemento;
}

/*
 * Libera la memoria reservada por el iterador.
 */
void lista_iterador_destruir(lista_iterador_t* iterador){
	free(iterador);
}

/*
 * Iterador interno. Recorre la lista e invoca la funcion con cada
 * elemento de la misma.
 */
void lista_con_cada_elemento(lista_t* lista, void (*funcion)(void*)){
	if(lista_vacia(lista)){
		return;
	}

	nodo_t* nodo = lista->nodo_inicio;

	for(int i = 0; i < (lista->cantidad); i++){
		(*funcion)(nodo->elemento);
		nodo = nodo->siguiente;
	}
}