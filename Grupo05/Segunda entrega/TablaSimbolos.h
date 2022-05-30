#ifndef TablaSimbolos_h_
#define TablaSimbolos_h_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef TAM_TS
#define TAM_TS 1000
#endif
#ifndef TAM_LEXEMA
#define TAM_LEXEMA 100
#endif

typedef struct simbolo {
	char nombre[TAM_LEXEMA + 1];
 	char tipoDato[31];
 	char valor[40];
 	int longitud;
} simbolo;

simbolo ts[TAM_TS];
int ultimo=0;

int insertarEnTabla(char *nombre, char *tipo, char *valor, int longitud){
	if(ultimo == TAM_TS)
		return -1;
	
	strncpy(ts[ultimo].nombre, nombre, TAM_LEXEMA + 1);
	strncpy(ts[ultimo].tipoDato, tipo, 31);
	strncpy(ts[ultimo].valor, valor, 40);
  //strncpy(ts[ultimo].longitud, longitud, 31);
  ts[ultimo].longitud = longitud;

	return ultimo++;
};

int buscarEnTabla(char *nombre){
	int pos = 0;
	while(pos != ultimo){
		if(strcmp(nombre, ts[pos].nombre) == 0)
			return pos;
		pos++;
	}
	return -1;
};

/*int buscarFloatEnTabla(float nombre){
	int pos = 0;
	while(pos != ultimo){
    char aux[TAM_LEXEMA + 1];
    ftoa(nombre,aux,2);
    char nombre2[TAM_LEXEMA + 1]  = "_";
    strcat(nombre2,aux);
		if(strcmp(nombre2, ts[pos].nombre) == 0)
			return pos;
		pos++;
	}
	return -1;
};*/

/*int buscarIntEnTabla(int nombre){
	int pos = 0;
  printf("buscar int en tabla");
  printf("%d",nombre);
	while(pos != ultimo){
    char aux[TAM_LEXEMA + 1];
    itoa(nombre, aux, 10);
    char nombre2[TAM_LEXEMA + 1]  = "_";
    strcat(nombre2,aux);
    printf("%s",nombre2);
		if(strcmp(nombre2, ts[pos].nombre) == 0)
      printf("encuentro cte int en tabla");
			return pos;
		pos++;
	}
	return -1;
};*/

/*char* getNombre(int pos){
	return (ts[pos].nombre);
};

char* getTipo(int pos){
	return (ts[pos].tipoDato);
};

char* getValor(int pos){
	return (ts[pos].valor);
};

char* getLongitud(int pos){
	return (ts[pos].longitud);
};*/

void borrarTiposDato(){
	ultimo = ultimo - 5;
};

int getCountTS(){
	return ultimo;
};

void imprimirTabla()
{

  printf("\n\n");
  printf("Cantidad de elementos: %d\n", getCountTS());
  
  printf("------------------------------------------TABLA DE SIMBOLOS------------------------------------|\n");
  printf("       NOMBRE             |        TIPO        |              VALOR              |  LONGITUD   |\n");
  printf("-----------------------------------------------------------------------------------------------|\n");

  size_t i;
  for(i = 0; i < getCountTS(); i++)
  {
    simbolo *sim = &ts[i];

    char linea[ 1024 ];
    memset( linea, 0, sizeof( linea ) );

    sprintf(linea, " %-*s | %-*s | %*s | %*d |\n", 24, sim->nombre,
                                                 18, sim->tipoDato,
                                                 31, sim->valor,
                                                 11, sim->longitud);
    printf("%s", linea );

  }
  printf("\n\n");
}

void generarArchivo()
{
  FILE *fp;
  
  fp = fopen ( "ts.txt", "w+" );
  
  fprintf(fp,"----------------------------------------TABLA DE SIMBOLOS------------------------------------|\n");
  fprintf(fp,"       NOMBRE           |        TIPO        |              VALOR              |  LONGITUD   |\n");
  fprintf(fp,"---------------------------------------------------------------------------------------------|\n");

  size_t i;
  for(i = 0; i < getCountTS(); i++)
  {
    simbolo *sim = &ts[i];

    fprintf(fp, " %-*s | %-*s | %*s | %*d |\n", 22, sim->nombre,
                                                 18, sim->tipoDato,
                                                 31, sim->valor,
                                                 11, sim->longitud);
  }
  fclose ( fp );
}

#endif