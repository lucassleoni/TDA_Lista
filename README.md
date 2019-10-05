TDA Lista (Nodos Simplemente Enlazados)

La implementación del TDA Lista incluído en 'TDA Lista (Lucas Leoni).zip' posee los siguientes programas:
    1) 'lista.h' es la biblioteca que incluye las firmas de las funciones primitivas para el funcionamiento de la lista.
    2) 'lista.c' es el programa con la implementación de la lista.
    3) 'minipruebas_lista_se.c' es el programa que contiene las pruebas que testean el funcionamiento de la lista implementada.
    4) 'makefile' es el programa que facilita el acceso a las líneas de compilación y ejecución de la lista, las pruebas y Valgrind.
    5) 'Consigna' es la consigna del trabajo pŕactico.


Funciones del TDA lista

Aclaración: todas las funciones utilizadas verifican (previo a ser ejecutadas) que no haya ningún error,
            (ver 'Funciones Propias > Verificación de errores generales').

1) Creación de la lista ---> lista_t* lista_crear();
     Crea la estructra 'lista_t lista'.
     Devuelve un puntero a la estructura 'lista_t lista' y reserva la memoria necesaria para su almacenamiento en el Heap,
     incializando los punteros a nodo_inicio y nodo_fin en NULL.
     Devuelve NULL en caso de haber habido un error al crear la lista.

2) Insertar elementos ---> int lista_insertar(lista_t* lista, void* elemento);
     Inserta el elemento recibido, reservando la memoria necesaria para el nuevo nodo que lo contiene y actualizando los punteros correspondientes.
     Si la lista esta vacía, tanto el 'inicio' como el 'fin' de la lista apuntan al nuevo nodo (el único).
     Aumenta la cantidad de elementos de la lista.
     Devuelve '0' si la operación tuvo éxito y '-1' si falló.

3) Insertar elementos en una posicón determinada ---> int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion);
     Inserta un elemento en la posición indicada (siendo '0' el primero de ellos), reservando la memoria necesaria para el nuevo nodo que lo
     contiene y actualizando los punteros correspondientes.
     Si la posición recibida es inválida, el elemento recibido se insertar como último elemento de la lista.
     Aumenta la cantidad de elementos de la lista.
     Devuelve '0' si la operación tuvo éxito y '-1' si falló.

4) Borrar elementos ---> int lista_borrar(lista_t* lista);
     Borra el elemento de la última posición de la lista, actualizando los punteros correspondientes y liberando
     la memoria ocupada por el nodo borrado.
     Disminuye la cantidad de elementos de la lista.
     Devuelve '0' si la operación tuvo éxito y '-1' si falló.

5) Borrar elementos de una posición determinada ---> int lista_borrar_de_posicion(lista_t* lista, size_t posicion);
     Borra el elemento de la posición indicada (siendo '0' el primero de ellos), liberando
     la memoria ocupada por el nodo borrado y actualizando los punteros correspondientes.
     Si la posición recibida es inválida, se borrará el último elemento de la lista.
     Disminuye la cantidad de elementos de la lista.
     Devuelve '0' si la operación tuvo éxito y '-1' si falló.

6) Conocer elemento de un aposición determinada ---> void* lista_elemento_en_posicion(lista_t* lista, size_t posicion);
     Devuelve un puntero al elemento de la posición indicada (siendo '0' el primero de ellos).
     Si la posición es inválida o la lista está vacía/es nula, devuelve NULL.

7) Último elemento de la lista --> void* lista_ultimo(lista_t* lista);
     Devuelve un puntero al último elemento de la lista.
     Si la posición es inválida o la lista no existe/está vacía, devuelve NULL.

8) Lista vacía ---> bool lista_vacia(lista_t* lista);
     Determina si la lista está vacía (es decir, si tiene 0 elementos/nodos).
     Devuelve 'true' si la lista está vacía o es nula, y 'false' en cualquier otro caso.

9) Cantidad de elementos ---> size_t lista_elementos(lista_t* lista);
     Devuelve la cantidad de elementos/nodos presentes en la lista.
     Si la lista es nula o está vacía, devuelve '0'.

10) Destrucción de la lista ---> void lista_destruir(lista_t* lista);
     En caso de no estar vacía, borra todos los elmentos/nodos de la lista hasta que no tenga ninguno.
     Luego, destruye la estructura 'lista_t lista' (liberando la memoria ocupada por ella).

11) Iterador interno ---> void lista_con_cada_elemento(lista_t* lista, void (*funcion)(void*));
     Recorre todos los nodos de la lista una vez, invocando (para cada uno de ellos) la función recibida por parámetro.
     Si la lista está vacía o es nula, finaliza el procedimiento sin ejecutar el bloque de acciones.


Funciones primitivas del TDA iterador

1) Crear iterador ---> lista_iterador_t* lista_iterador_crear(lista_t* lista);
     Crea la estructura 'lista_iterador_t iterador'.
     El iterador externo es válido hasta recorrer todos los elementos..
     Devuelve un puntero a la estructura 'lista_iterador_t iterador' y reserva la memoria necesaria para su almacenamiento en el Heap.
     Devuelve NULL en caso de haber habido un error al crear el iterador.

2) Verificar si hay nodo siguiente ---> bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador);
     Determina si hay un elemento luego del que está siendo apuntado por el iterador al momento ser invocada esta función.
     Si el iterador no comenzó a recorrer la lista (y la misma no está vacía), el elemento siguiente será el nodo inicial.
     Devuelve 'true' si hay nodo siguiente, y 'false' en cualquier otro caso.

3) Avanzar un elemento ---> void* lista_iterador_siguiente(lista_iterador_t* iterador);
     Avanza el iterador al proximo elemento y lo devuelve.
     Devuelve NULL si la lista a la que apunta el iterador no existe.

4) Destruir iterador ---> void lista_iterador_destruir(lista_iterador_t* iterador);
     Libera la memoria reservada por el iterador.


Funciones Propias (para modularizar la implementacíon de la lista/iterador)

1) Verificación de errores generales (lista) ---> bool hay_error_lista(lista_t* lista);
     Devuelve 'true' si:
        1.1) La estructura 'lista_t lista' es nula.
        1.2) El 'nodo_inicio' es nulo y el 'nodo_fin' no lo es, o viceversa.

2) Buscar nodo de una posicion determinada ---> nodo_t* buscar_nodo(lista_t* lista, size_t posicion);
     Devuelve un puntero al nodo que se encuentra en la posición recibida.
     Si la posición es inválida o la lista está vacía/es nula, devuelve NULL.

3) Borrar el nodo inicial ---> void lista_borrar_nodo_inicial(lista_t* lista, nodo_t* nodo_aux);
     Borra el nodo que se encentra en la primera posición de la lista.
     Si la lista está vacía o es nula, finaliza el procedimiento sin ejecutar el bloque de acciones.

4) Verificación de errores generales (iterador) ---> bool lista_iterador_es_nula(lista_iterador_t* iterador);
     Devuelve 'true' si la lista a la que apunta el iterador no existe.


Compilación y Convenciones

1) Tamaño de la lista
     Inicialmente, la lista se creará totalmente vacía (0 elementos/nodos).

2) Makefile
   La carpeta cuenta con un programa 'makefile' que posee los siguientes comandos:
     3.1) 'make compile' compilará el programa 'lista.c' junto con las pruebas que testean su funcionamiento, ejecutando la línea de compilación:
              gcc -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0 lista.c minipruebas_lista.c -o lista_se -g

     3.2) 'make lista' compilará el programa con la línea mencionada en el punto (3.1) y luego ejecutará las pruebas (incluídas en la carpeta) con la línea:
              ./lista_se

     3.2) 'make valgrind' ejecutrá Valgrind (mostrando los resultados de las pruebas por pantalla) con la línea:
              valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./lista_se
