#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<assert.h>

// crearArreglo: array --> int
// crearArreglo: recibe un array vacio donde se almacenan las palabras que son leídas desde
// un archivo, y devuelve la cantidad de palabras que hay en el archivo.

int crearArreglo(char listPalabras[100][16]){
  FILE *archivo;
  char nombreArchivo[16];
  printf("Ingrese el nombre del archivo (no mas de 15 caracteres) con .txt al final:\n");
  scanf("%s",nombreArchivo);
  archivo=fopen(nombreArchivo, "r");
  int i=0;
  char c=fgetc(archivo);
  while(i<100&&c!=EOF){
	  ungetc(c,archivo);
	  fgets(listPalabras[i],100,(FILE*)archivo);
	  i++;
	  c=fgetc(archivo);
  }
  fclose(archivo);
  return i;
}

//inversa: array array -> None
//inversa: recibe dos palabras (arrays) de igual longitud y reemplaza la segunda
//por la inversa de la primera

void inversa(char p[],char p1[]){
	int largo = strlen(p);
	for(int i=0;i<largo;i++){
		p1[i]=p[largo-1-i];
	}
}

// hayPalabra: array array --> Int
// hayPalabra: dados dos arrays, devuelve 1 si el segundo esta contenido en el
// primero, caso contrario, devuelve 0.

int hayPalabra(char string[], char substring[]){
	int estaPalabra=0,longStr=strlen(string),longSubstr=strlen(substring),inicioPalabra=0;
	while(inicioPalabra<=longStr-longSubstr && estaPalabra==0){
		int i=0;
		while(i<longSubstr && string[inicioPalabra+i]==substring[i]){
			i++;
		}
		inicioPalabra++;
		if(i==longSubstr){
			estaPalabra=1;
		}
	}
	return estaPalabra;
}

// hayNumero: int int int --> int
// hayNumero: dado un arreglo de numeros, el tamaño del arreglo y un número,
// devuelve cuantas veces aparece dicho número en el arreglo.

int hayNumero(int numeros[],int cantidad,int numero){
	int apariciones=0;
	for(int i=0;i<cantidad;i++){
		if(numeros[i]==numero){
			apariciones++;
		}
	}
	return apariciones;
}

// elegirNumero: None --> Int
// elegirNumero: elige aleatoriamente un número entre 1 y la cantidad de palabras que tiene la lista,
// este será el numero de palabras que vamos a colocar en el archivo.

int elegirNumero(int cantidadPalabras){
  int numero;
  numero=rand()%cantidadPalabras;
  while(numero==0){
    numero=rand()%cantidadPalabras; //el while sirve para que la cantidad de palabras a seleccionar no sea 0.
  }
  return numero;
}

//chequearSubstring: char char int -> int
//chequearSubstring: recibe una palabra, una lista de palabras en la que esta esa palabra y la cantidad de palabras que hay en la lista
//y devuelve la cantidad de veces que aparece la palabra como substring (o como la misma palabra) en la lista

int chequearSubstring(char palabra[],char palabras[][16],int cantPalabras){
	int apariciones=0;
	for(int i=0; i<cantPalabras; i++){
		if(strlen(palabras[i])>=strlen(palabra)){
			if(hayPalabra(palabras[i],palabra)){
				apariciones+=1;
			}
		}
		else{
			if(hayPalabra(palabra,(palabras[i]))){
				apariciones+=1;
			}
		}
	}
	return apariciones;
}

//listaPalabras: char int -> none
//listaPalabras: arma un arreglo de una cierta cantidad de strings (determinada por cantidadPalabras) donde se le
//pide que escriba por teclado las palabras a agregar, con una longitud no mayor a 15.

void listaPalabras(char palabras[][16],int cantidadPalabras){
  for(int i=0; i<cantidadPalabras; i++){
	printf("Ingrese una palabra que desea agregar a la lista: ");
    scanf("%s", palabras[i]);
  }
}

//listaInversas: char char int -> none
//listaInversas: a partir de una lista de palabras y una lista de igual longitud,
//convierte la copia en una lista de las palabras de la primera invertidas

void listaInversas(char palabras[][16],char palabrasInversas[][16],int cantidadPalabras){
	for(int i=0;i<cantidadPalabras;i++){
		strcpy(palabrasInversas[i],palabras[i]);
	}
	for(int i=0;i<cantidadPalabras;i++){
		inversa(palabras[i],palabrasInversas[i]);
	}
}

//verificarPalabras: char char int int --> int
//verificarPalabras: recibe la lista de palabras, la lista de palabras invertidas, la lista de palabras verificadas, la cantidad de palabras verificadas
//y un indice correspondiente a una de las palabras de la lista. Devuelve 1 si la palabra cumple con los
//requisitos pedidos para la seleccion aleatoria de palabras; caso contrario devuelve 0.

int verificarPalabras(char palabras[][16],char palabrasInversas[][16],char palabrasVerificadas[][16],int cantidadVerificadas,int indice){
	printf("palabra: %s,%d letras,substring de %d,inversas %d\n",palabras[indice],strlen(palabras[indice]),chequearSubstring(palabras[indice],palabrasVerificadas,cantidadVerificadas),chequearSubstring(palabrasInversas[indice],palabrasVerificadas,cantidadVerificadas));
	if(strlen(palabras[indice])>4){
		if(chequearSubstring(palabras[indice],palabrasVerificadas,cantidadVerificadas)==0){
			if(chequearSubstring(palabrasInversas[indice],palabrasVerificadas,cantidadVerificadas)==0){
				return 1;
				printf("%s",palabras[indice]);
			}
			else{
				return 0;
			}
		}
		else{
			return 0;
		}
	}
	else{
		return 0;
	}
}

int main(){
	srand(time(NULL));
	int opcion;
	printf("Ingrese 1 para ingresar palabras por teclado o 2 para abrir un archivo con una lista de palabras: ");
	scanf("%d",&opcion);
	int cantidadPalabras,j=0,n,indiceAleatorio;
	char palabras[100][16],palabrasInversas[100][16],seleccion[100][16];
	if(opcion==1){
		printf("Ingrese la cantidad de palabras que desea agregar (maximo 100):\n");
		scanf("%d", &cantidadPalabras);
		listaPalabras(palabras,cantidadPalabras);
	}
	else{
		cantidadPalabras=crearArreglo(palabras);
	}
	//este for agrega las palabras que cumplen la verificacion a la lista de palabras verificadas
	//y cuenta la cantidad de palabras que se agregaron
	//~ for(int i=0;i<cantidadPalabras;i++){
		//~ if(verificarPalabras(palabras,palabrasInversas,palabrasVerificadas,j,i)==1){
			//~ strcpy(palabrasVerificadas[j],palabras[i]);
			//~ j++;
		//~ }
	//~ }
	//char verificadas[j][16];
	//este for crea una lista final de palabras verificadas con el tamano exacto
	//para que no quede basura en los espacios vacios al final
	//~ for(int i=0;i<j;i++){
		//~ strcpy(verificadas[i],palabrasVerificadas[i]);
	//~ }
	//elegimos una cantidad aleatoria de palabras entre 1 y la cantidad de palabras verificadas
	//y esa sera la cantidad de paabras que se escribiran en el archivo
	n=elegirNumero(cantidadPalabras);
	int indices[cantidadPalabras];
	for(int i=0;i<n;i++){
		indiceAleatorio=elegirNumero(j)-1;
		while(hayNumero(indices,n,indiceAleatorio)>0){
			indiceAleatorio=elegirNumero(j)-1;
		}
		strcpy(seleccion[i],palabras[indiceAleatorio]);
		//~ if(opcion==1){
			//~ fputs("\n",fp);
		//~ }
		indices[i]=indiceAleatorio;
	}
	listaInversas(seleccion,palabrasInversas,cantidadPalabras);
	char palabrasVerificadas[n][16];
	for(int i=0;i<n;i++){
		if(verificarPalabras(seleccion,palabrasInversas,palabrasVerificadas,j,i)==1){
			strcpy(palabrasVerificadas[j],palabras[i]);
			j++;
		}
	}
	FILE *fp;
	//creamos un archivo en el que poner las palabras
	char p[16];
	printf("Elija el nombre del archivo a crear con la seleccion de palabras: ");
	scanf("%s",p);
	fp=fopen(strcat(p,".txt"),"w");
	//este for agrega n palabras elegidas aleatoriamente de las verificadas al archivo creado
	for(int i=0;i<j;i++){
		fputs(palabrasVerificadas[i],fp);
		if(opcion==1){
			fputs("\n",fp);
		}
	}
	fclose(fp);

// TESTING DE LAS FUNCIONES:

	assert(hayPalabra("hola", "ola")==1);
	assert(hayPalabra("casa", "las")==0);
	
	int l[6]={2, 1, 2, 3, 5, 2},m[5]={1, 2, 3, 4, 5};
	assert(hayNumero(l, 6, 2)==3);
	assert(hayNumero(m, 5, 0)==0);
	
	char h[4][16]={"ola","hola","hholaa","abc"};
	assert(chequearSubstring("hola",h,4)==3);
	assert(chequearSubstring("uno",h,4)==0);
	
	char f[4][16]={"alo","aloh","aalohh","cba"},b[][16]={"aloh"};
	assert(verificarPalabras(h,f,b,4,1)==0);
	assert(verificarPalabras(h,f,b,4,0)==0);
	
	return 0;
}
