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
  char nombreArchivo[50];
  printf("Ingrese el nombre del archivo con .txt al final:\n");
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
	int largo = strlen(p),i=0
  ;
	for(i;i<largo;i++){
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
	int apariciones=0,i=0;
	for(i;i<cantidad;i++){
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
	int apariciones=0,i=0;
	for(i; i<cantPalabras; i++){
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
  int i=0;
  for(i; i<cantidadPalabras; i++){
	printf("Ingrese una palabra que desea agregar a la lista: ");
    scanf("%s", palabras[i]);
  }
}

//listaInversas: char char int -> none
//listaInversas: a partir de una lista de palabras y una lista de igual longitud,
//convierte la copia en una lista de las palabras de la primera invertidas

void listaInversas(char palabras[][16],char palabrasInversas[][16],int cantidadPalabras){
  int i=0;
	for(i;i<cantidadPalabras;i++){
		strcpy(palabrasInversas[i],palabras[i]);
	}
	for(i;i<cantidadPalabras;i++){
		inversa(palabras[i],palabrasInversas[i]);
	}
}

//verificarPalabras: char char int int --> int
//verificarPalabras: recibe la lista de palabras, la lista de palabras invertidas, la lista de palabras verificadas, la cantidad de palabras verificadas
//y un indice correspondiente a una de las palabras de la lista. Devuelve 1 si la palabra cumple con los
//requisitos pedidos para la seleccion aleatoria de palabras; caso contrario devuelve 0.

int verificarPalabras(char palabras[][16],char palabrasInversas[][16],char palabrasVerificadas[][16],int cantidadVerificadas,int indice){
	printf("palabra: %s,substring de %d,inversas %d\n",palabras[indice],chequearSubstring(palabras[indice],palabrasVerificadas,cantidadVerificadas),chequearSubstring(palabrasInversas[indice],palabrasVerificadas,cantidadVerificadas));
	if(strlen(palabras[indice])>3){
		if(chequearSubstring(palabras[indice],palabrasVerificadas,cantidadVerificadas)==1){
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
	int opcion,i=0;
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
	//elegimos una cantidad aleatoria de palabras entre 1 y la cantidad de palabras verificadas
	//y esa sera la cantidad de paabras que se escribiran en el archivo
	n=elegirNumero(cantidadPalabras);
	int indices[cantidadPalabras];
	for(i;i<n;i++){
		indiceAleatorio=elegirNumero(cantidadPalabras)-1;
		while(hayNumero(indices,n,indiceAleatorio)>0){
			indiceAleatorio=elegirNumero(cantidadPalabras)-1;
		}
		strcpy(seleccion[i],palabras[indiceAleatorio]);
		indices[i]=indiceAleatorio;
	}
  printf("hola");
	listaInversas(seleccion,palabrasInversas,cantidadPalabras);
	char palabrasVerificadas[n][16];
  i=0;
	for(i;i<n;i++){
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
  i=0;
	for(i;i<j;i++){
		fputs(palabrasVerificadas[i],fp);
		if(opcion==1){
			fputs("\n",fp);
		}
	}
	fclose(fp);

	return 0;
}
