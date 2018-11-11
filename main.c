#include<stdio.h>
#include<string.h>
#define MAX 100 
int contar_lineas(char line, FILE *f, char *file);
int contar_caracteres(char line, FILE *f, char *file);
int validar_comando(char *comando, char *archivo);
int contar_palabras(FILE *file,char *archivo);
void ejecutar_comando(char *comando, char *file,FILE *f, FILE *f1, char l);
void comand_help();
int get_retorno(char *comando);
static char *ccomando;
static char *ffile;

int main(int argc, char *argv[]){
	ccomando = argv[1];
	ffile = argv[2];
	FILE *f, *f1;
	char lineas;
		if(argc<=3){
		ejecutar_comando(ccomando,ffile,f,f1,lineas);
		}
		else{
		comand_help();
		}
	return 0;
}

void ejecutar_comando(char *comando, char *file,FILE *f, FILE *f1,char lineas){
switch (validar_comando(ccomando, ffile)){
			case 0:
				comand_help();
				break;
			case 1:
				printf("\e[41mContar saltos de linea\e[0m\n");
				int l = 0;
				l = contar_lineas(lineas,f,ffile);
				printf("%d %s\n",l,ffile);
				break;
			case 2:
				printf("\e[41mContar caracteres\e[0m\n");
				int c = 0;
				c = contar_caracteres(lineas,f,ffile);
				printf("%d %s\n",c,ffile);
				break;
			case 3:
				printf("\e[41mContar palabras\e[0m\n");
				int d= 0;
				d= contar_palabras(f,ffile);
				printf("%d %s\n",d,ffile);
				break;
			case 4:
				printf("\e[41mMostrar todo!\e[0m\n");
				int li, ch,t;
				li=contar_lineas(lineas,f1,ccomando);
				ch=contar_caracteres(lineas,f1, ccomando);
				t= contar_palabras(f1,ccomando);
				printf("%d   %d   %d %s\n", li, ch,t,ccomando);
				break;
			case 5:
				fputs("\e[31mFile error\e[0m\n", stderr);
				break;
			default:
				comand_help();
		
	}
}

/*
Este metodo acepta como argumento el parametro y el archivo escrito por el usuario
retorna un entero dependiendo del tipo de argumento
*/
int validar_comando(char *comando,char *archivo){
	FILE *a, *a1;
	a=fopen(comando,"r");
	a1=fopen(archivo,"r");
	if(a==NULL && a1== NULL){
		return 5;
	}
	if(a!=NULL){
		if(archivo!=NULL){
		//Intercambia los argumentos
		//Ver si no se crea un archivo...
		ccomando=archivo;
		ffile=comando;
		return get_retorno(archivo);		
		} else{
		return 4;
		}
	}
	return get_retorno(comando);
	fclose(a);
	fclose(a1);
	
}

/*
Metodo que retorna un entero de acuerdo al tipo de argumento ingresado
*/
int get_retorno(char *comando){
if(strcmp(comando,"-l")==0){
	        return 1;
	}
	if(strcmp(comando,"-c")==0){
	        return 2;
	}
	if(strcmp(comando,"-m")==0){
		return 3;
	}
	if(strcmp(comando,"-h")==0){
		return 0;
	}
	return 9;
}


int contar_lineas(char line, FILE *f, char *file){
	f = fopen(file,"a+");
	int nl=0;
	while((line = fgetc(f))!=EOF){	
		if (line == '\n'){
			++nl;
		}
	}
	fclose(f);
	return nl;
}

int contar_caracteres(char line, FILE *f, char *file){
	f = fopen(file,"a+");
	int nc=0;
	while((line = fgetc(f))!=EOF){
		if ((line != ' ') && (line !='\t') && (line != '\n')){
			++nc;
		}
	}
	fclose(f);
	return nc;
}

/*
Este metodo permite contar las palabras presentes en el archivo
*/
int contar_palabras(FILE *f, char *file){
	f = fopen(file,"a+");
	int w=0;
	char palabra[MAX];
	while(feof(f)==0){
	fscanf(f, "%s", palabra);
	++w;
	}
	fclose(f);
	return w-1;
}

void comand_help(){
printf("wc [option] FILE\nwc, o 'word count', muestra en consola el número de saltos de línea, palabras, y caracteres del archivo de entrada.\n-h: ayuda, muestra este mensaje\n-l: muestra el total de saltos de línea\n-m: muestra el total de palabras\n-c: muestra el total de caracteres\n");
}
