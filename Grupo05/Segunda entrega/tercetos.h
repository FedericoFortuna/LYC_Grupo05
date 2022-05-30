
#include "TablaSimbolos.h"

#define OFFSET TAM_TS
#define MAX_TERCETOS 512

/* Operadores extra para usar con los tokens */
#define NOOP -1 /* Sin operador */
#define BLOQ 7  /* Operador que indica el orden de las sentencias */
#define CMP 21  /* Comparador de assembler */
#define BNE 2   /* = */
#define BGE 4   /* < */
#define BLT 6   /* >= */
#define BLE 10  /* > */
#define BEQ 14  /* != */
#define BGT 8   /* <= */
#define JMP 16  /* Branch Always o Salto Incondicional*/
#define INL 18  /* Un terceto con este operador representa el resultado del inlist.
                /* Representa la comparacion de dos numeros iguales si dio verdadero
                * o de dos numeros distintos si dio falso.
                */

/* Posiciones dentro de un terceto */
#define OP1 2
#define OP2 3
#define OPERADOR 1

typedef struct{
  int operador;
  int op1;
  int op2;
} terceto;

terceto lista_terceto[MAX_TERCETOS];
int ultimo_terceto; /* Apunta al ultimo terceto escrito. Incrementarlo para guardar el siguiente. */


/* Funciones */

//int crear_terceto(int operador, int op1, int op2);
int crear_terceto(int operador, int op1, int op2){
	ultimo_terceto++;
	if(ultimo_terceto >= MAX_TERCETOS){
		printf("Error: me quede sin espacio en para los tercetos. Optimiza tu codigo.\n");
		system("Pause");
		exit(3);
	}

	lista_terceto[ultimo_terceto].operador = operador;
	lista_terceto[ultimo_terceto].op1 = op1;
	lista_terceto[ultimo_terceto].op2 = op2;
	return ultimo_terceto + OFFSET;
}


//void modificarTerceto(int indice, int posicion, int valor);
void modificarTerceto(int indice, int posicion, int valor){
	if(indice > ultimo_terceto + OFFSET){
		printf("Ups, algo fallo. Intente modificar un terceto que no existe. Mala mia.");
		system ("Pause");
		exit (4);
	}
	switch(posicion){
	case OP1:
		lista_terceto[indice - OFFSET].op1 = valor;
		break;
	case OP2:
		lista_terceto[indice - OFFSET].op2 = valor;
		break;
	case OPERADOR:
		lista_terceto[indice - OFFSET].operador = valor;
		break;
	}
}

//void guardarTercetos();
void guardarTercetos(){
	if(ultimo_terceto == -1)
		yyerror("No encontre los tercetos");

	FILE* arch = fopen("intermedia.txt", "w+");
	if(!arch){
		printf("No pude crear el archivo intermedia.txt\n");
		return;
	}
  int i = 0;
	for(i ; i <= ultimo_terceto; i++){
		//La forma es [i] (operador, op1, op2)
		//Escribo indice
		fprintf(arch, "[%d] (", i + OFFSET);

		//escribo operador
		switch(lista_terceto[i].operador){
		case NOOP:
			fprintf(arch, "---");
			break;
		case BLOQ:
			fprintf(arch, "sentencia");
			break;
		case ID:
			fprintf(arch, "declaracion");
			break;
		case IF:
			fprintf(arch, "if");
			break;
		case ELSE:
			fprintf(arch, "cuerpoElse");
			break;
		case ENDIF:
			fprintf(arch, "finIf");
			break;
		case WHILE:
			fprintf(arch, "while");
			break;
		case ENDWHILE:
			fprintf(arch, "finWhile");
			break;
		case OP_ASIG:
			fprintf(arch, ":=");
			break;
		case OP_SUM:
			fprintf(arch, "+");
			break;
		case OP_RES:
			fprintf(arch, "-");
			break;
		case OP_MUL:
			fprintf(arch, "*");
			break;
		case OP_DIV:
			fprintf(arch, "/");
			break;
		case AND:
			fprintf(arch, "y");
			break;
		case OR:
			fprintf(arch, "o");
			break;
		case NEGADO:
			fprintf(arch, "no");
			break;
		case MENOR:
			fprintf(arch, "<");
			break;
		case MAYOR:
			fprintf(arch, ">");
			break;
		case MEN_O_IG:
			fprintf(arch, "<=");
			break;
		case MAY_O_IG:
			fprintf(arch, ">=");
			break;
		case IGUAL:
			fprintf(arch, "==");
			break;
		case DISTINTO:
			fprintf(arch, "!=");
			break;
		case AVG:
			fprintf(arch, "avg");
			break;
		case TAKE:
			fprintf(arch, "take");
			break;
		case COMA:
			fprintf(arch, "\',\'");
			break;
		case P_Y_COMA:
			fprintf(arch, "\';\'");
			break;
		case READ:
			fprintf(arch, "leeme");
			break;
		case WRITE:
			fprintf(arch, "mostrame");
			break;
		case CMP:
			fprintf(arch, "CMP");
			break;
		case BNE:
			fprintf(arch, "BNE");
			break;
		case BEQ:
			fprintf(arch, "BEQ");
			break;
		case BGT:
			fprintf(arch, "BGT");
			break;
		case BGE:
			fprintf(arch, "BGE");
			break;
		case BLE:
			fprintf(arch, "BLE");
			break;
		case BLT:
			fprintf(arch, "BLT");
			break;
		case JMP:
			fprintf(arch, "JMP");
			break;
		case INL:
			fprintf(arch, "INL");
			break;
		default:
			fprintf(arch, "operador no encontrado");
			break;
		}

		fprintf(arch, ", ");
		//Escribo op1
		int op = lista_terceto[i].op1;

		if(op == NOOP)
			fprintf(arch, "---");
		else if(op < TAM_TS){
			//Es una entrada a tabla de simbolos
			fprintf(arch, "%s", &(ts[op].nombre) );
		}
		else //Es el indice de otro terceto
			fprintf(arch, "[%d]", op);

		fprintf(arch, ", ");
		//Escribo op2
		op = lista_terceto[i].op2;
		if(op == NOOP)
			fprintf(arch, "---");
		else if(op < TAM_TS){
			//Es una entrada a tabla de simbolos
			fprintf(arch, "%s", &(ts[op].nombre) );
		}
		else //Es el indice de otro terceto
			fprintf(arch, "[%d]", op);

		fprintf(arch, ")\n");
	}
	fclose(arch);
}


