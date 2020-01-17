#include <stdio.h>
#include <stdlib.h>

typedef struct casilla casilla;

typedef struct par{
  int x;
  int y;
}par;

struct casilla{
  char tipo;
  int valor;
  par pos;
  par *arreglo;//arreglo de posiciones con numeros
	int idEstado;
	int estadoAnterior;
	char * transicion;
};

int correlativo;

casilla crearEstado(char tipo, int valor, par pos, par *arr, int anterior, char * t);
casilla * agregarEstado(casilla *lista, int * elementos, casilla estado);
casilla * sacarElemento(casilla * lista, int * elementos);
int estaEstado(casilla * lista, int elementos, casilla b);

//funciones para verificar transiciones
int checkR(casilla estado);
int checkL(casilla estado);
int checkU(casilla estado);
int checkD(casilla estado);
//funciones para realizar transiciones
casilla moveR(casilla estado);
casilla moveL(casilla estado);
casilla moveU(casilla estado);
casilla moveD(casilla estado);
//funcion que avisa si el estado es final o no
int esFinal(casilla b);
//imprime un estado
void imprimirEstado(casilla b);



casilla crearEstado(char tipo, int valor, int *pares, int anterior, char * t){
	casilla nuevoEstado;
	nuevoEstado.tipo = tipo;
	nuevoEstado.valor = valor;
	nuevoEstado.pares = pares;
	nuevoEstado.estadoAnterior = anterior;
	nuevoEstado.transicion = t;
	correlativo = correlativo + 1;
	return nuevoEstado;
}

casilla * agregarEstado(casilla * lista, int * elementos, casilla estado){
	casilla * nuevaLista = (casilla *)malloc(sizeof(casilla)*(*elementos+1));
	for (int i = 0; i < *elementos; ++i){
		nuevaLista[i] = lista[i];
	}
	nuevaLista[*elementos] = estado;
	*elementos = *elementos+1;
	free(lista);
	return nuevaLista;
}

casilla * sacarElemento(casilla * lista, int * elementos){
  casilla * nuevaLista = (casilla *)malloc(sizeof(casilla)*(*elementos-1));
  for (int i = 1; i < *elementos; ++i){
    nuevaLista[i-1]=lista[i];
  }
  *elementos = *elementos-1;
  free(lista);
  return nuevaLista;
}



//funciones para verificar transiciones
int checkR(casilla estado, int size){
  if(estado.pos.x < size-1)
    return 1;
  return 0;
}
int checkL(casilla estado, int size){
  if(estado.pos.x > 0)
    return 1;
  return 0;
}
int checkU(casilla estado, int size){
  if(estado.pos.y > 0)
    return 1;
  return 0;
}
int checkD(casilla estado, int size){
  if(estado.pos.y < size-1)
    return 1;
  return 0;
}

//funciones para realizar transiciones
casilla moveR(casilla estado){
  //casilla crearEstado(char tipo, int valor, int *pares, int anterior, char * t);
  return crearEstado(, 5, estado.idEstado, "LL5");
}
casilla moveL(casilla estado);
casilla moveU(casilla estado);
casilla moveD(casilla estado);
// int verificarLL5(bidones estado){
// 	if(estado.AguaBidon5L < 5){
// 		return 1;
// 	}return 0;
// }
//
// bidones llenar5(bidones estado){
// 	return crearEstado(estado.AguaBidon3L, 5, estado.idEstado, "LL5");
// }



int esFinal(casilla c){

	return 0;
}

void imprimirEstado(casilla c){
	printf("Id:%d; T:%s, IdAnt:%d\n", c.idEstado, c.transicion, c.estadoAnterior);
}

int estaEstado(casilla * lista, int elementos, casilla c){
	for (int i = 0; i < elementos; ++i){
		if((lista[i].AguaBidon3L == c.AguaBidon3L) && (lista[i].AguaBidon5L == c.AguaBidon5L))
			return 1;
	}return 0;
}

void mostrarSolucion(casilla * lista, int ultimo){
	printf("Los pasos son, del ultimo al primero: \n");
	while(lista[ultimo].idEstado != 0){
		printf("%s\n", lista[ultimo].transicion);
		ultimo = lista[ultimo].estadoAnterior;
	}
}


int resolver(){
	correlativo = 0;
	int canAbiertos = 0;
	int canCerrados = 0;
	bidones bActual, bSiguiente;
	bidones * abiertos = (bidones *)malloc(sizeof(bidones)*canAbiertos);
	bidones * cerrados = (bidones *)malloc(sizeof(bidones)*canCerrados);
	bidones inicial = crearEstado(0, 0, correlativo, "");
	abiertos = agregarEstado(abiertos, &canAbiertos, inicial);
	while(canAbiertos > 0){
		bActual = abiertos[0];
		abiertos = sacarElemento(abiertos, &canAbiertos);
		cerrados = agregarEstado(cerrados, &canCerrados, bActual);
		if(esFinal(bActual) == 1){
			printf("Llegue\n");
			mostrarSolucion(cerrados,canCerrados-1);
			return 0;
		}else{
			//LL5
			if(verificarLL5(bActual) == 1){
				bSiguiente = llenar5(bActual);
				if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
				}else{
					correlativo = correlativo - 1;
				}
			}
			//LL3
			if(verificarLL3(bActual) == 1){
				bSiguiente = llenar3(bActual);
				if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
				}else{
					correlativo = correlativo - 1;
				}
			}
			//V5
			if(verificarV5(bActual) == 1){
				bSiguiente = vaciar5(bActual);
				if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
				}else{
					correlativo = correlativo - 1;
				}
			}
			//V3
			if(verificarV3(bActual) == 1){
				bSiguiente = vaciar3(bActual);
				if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
				}else{
					correlativo = correlativo - 1;
				}
			}
			//T5
			if(verificarT5(bActual) == 1){
				bSiguiente = tras5(bActual);
				if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
				}else{
					correlativo = correlativo - 1;
				}
			}
			//T3
			if(verificarT3(bActual) == 1){
				bSiguiente = tras3(bActual);
				if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
				}else{
					correlativo = correlativo - 1;
				}
			}
		}

		printf("ABIERTOS:");
		for (int i = 0; i < canAbiertos; ++i)
		{
			imprimirEstado(abiertos[i]);
		}


		printf("\nCERRADOS:");
		for (int i = 0; i < canCerrados; ++i)
		{
			imprimirEstado(cerrados[i]);
		}
		printf("\n\n");
	}
	return 0;
}


int main(){
  printf("HOLI\n", );

  return 0;
}
