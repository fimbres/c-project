#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#define N 500

typedef struct _tnom{
	char nombre[20];
	char apeP[20];
	char apeM[20];
}Tsnomb;

typedef struct _tdato{
	long matri;
	Tsnomb nombres;
	int edad;
	int sexo;
	int estado;
}TsAlumno;

typedef struct _ttemp{
	long clave;
	char n[20], aP[20], aM[20], sexo[10];
	int ed;
	int est;
}TsTemp;

void menu();
Tsnomb Genombres(int s);
TsAlumno agregar();
float ValidaNum(int limi, int lims, char mens[]);
int cargarT(int tam, char nom[30]);
int agregarB(TsAlumno reg, int tam, char nom[30]);
int buscar(long num, TsAlumno *aux, int op);
void eliminar(TsAlumno *reg);
void imprimirB(TsAlumno *reg1, int op);
void Archivo(FILE **fa);
void Empaque(FILE **fa);

//Examen2_FAIR
//02/06/2020
//Isaac Rey Fimbres Aragón
//Estructura de datos y tipos de archivos

int main()
{
	srand(time(NULL));
	menu();
	return 0;
}

float ValidaNum(int limi, int lims, char mens[])
{
	float num;
	char Ne[50];
	do{
		puts(mens);
	    fflush(stdin);
	    gets(Ne);
	    num = atof(Ne);
	}while(num < limi || num > lims);
	return num;
}

void menu()
{
	TsAlumno regen, Vect[N], aux;
	FILE *fa;
	long mat;
	int op, op2, i=1, s, o=0, k=0, j, pos;
	fa = fopen("Bin.dat", "r+b");
    if(!fa)
	{
		fa = fopen("Bin.dat", "w+b");
	}
	char ar[30];
	do
	{
		system("cls");
		printf("MENU\n");
		printf("Ingresa una opcion:\n");
		printf("1.-Agregar 10 registros (Sin repetir)\n");
		printf("2.-Cargar archivo de texto (.txt)\n");
		printf("3.-Eliminar registro\n");
		printf("4.-Buscar registro\n");
		printf("5.-Mostrar todos los registros\n");
		printf("6.-Generar archivo de salida\n");
		printf("7.-Empaquetar\n");
		printf("0.-Salir\n");
		scanf("%d",&op);
		switch(op)
		{
			case 0: printf("Hasta luego!\n"); break;
			case 1: if(i<N)
			        { 
			        j=0;
					do{
			        	do{
			        	 	aux = agregar();
			        	 	op2 = buscar(aux.matri, &aux, 1);
			        	 }while(op2=!-1);
			             i = agregarB(aux, i, "Bin.dat");
			             j++;
					     system("CLS");
			          }while(j<10);
			          printf("\nListo!\n");
			        }
				   else
				    {
				    	printf("Archivo lleno\n");
				    } system("pause"); break;
			case 2: if(k==0){
				system("CLS");
				       printf("Antes de abrir un archivo debes verificar:\n  1- Que se encuentre en la misma direccion que el archivo fuente de este programa.\n  2- Elimina TODA información basura que no deseas que se lea, como los titulos.\n  3- Verificar previamente como se llama el archivo\n  4- Debe tener el formato: i, Clave, aP, aM, Nombre, Edad, Sexo\n  Una ves que los verifiques, Ingresa el nombre del Archivo a cargar:   ");
			           fflush(stdin); gets(ar);
					   i = cargarT(i,ar); k++; o=0;
		        	}
				   else
					{
						printf("Ya se cargo un archivo\n");
					}system("pause"); break;
			case 3: mat  = (long)ValidaNum(300000, 400000, "Ingresa la matricula del registro a eliminar: ");
			        pos = buscar(mat, &regen,2); imprimirB(&regen, 2); eliminar(&regen); imprimirB(&regen, 2); break;
			case 4: mat  = (long)ValidaNum(300000, 400000, "Ingresa la matricula del registro a buscar: ");
			        pos = buscar(mat, &regen,2); imprimirB(&regen, 2); break;
			case 5: system("cls"); printf("R E G I S T R O S\n"); imprimirB(&aux, 1); break;
			case 6: Archivo(&fa); break;
			case 7: Empaque(&fa); break;
			default: printf("Ingresa un comando valido\n"); break;
		}  		
	}
	while(op=!0);
	fclose(fa);
}

Tsnomb Genombres(int s)
{
	Tsnomb NomCom;
	char Ape[20][20]={"NURMAGOMEDOV ","MCGREGOR ","CERRONE ","PETTIS ","ADESANYA ","GASTELUM ","VELASQUEZ ","FERGUSON ","MASVIDAL ","DIAZ ","NUNEZ ","SHEVCHENKO ","POIRIER ","HOLM ","NAMAJUNAS ","ALDANA ","PENNINGTON ","ZHANG ","JEDRZEJCZYK ","ESPARZA "};
	char NomH[10][20]={"KHABIB","TONY","CONOR","DONALD","ANTHONY","ISRAEL","KELVIN","CAIN","JORGE","NATE"};
	char NomM[10][20]={"AMANDA","VALENTINA","ROSE","CRIS","HOLLY","JESSICA","JOANNA","ALEXA","CARLA","TATIANA"};
    strcpy(NomCom.apeP,Ape[rand()%20]);
    strcpy(NomCom.apeM,Ape[rand()%20]);
    if(s==1)
    {
	    strcpy(NomCom.nombre,NomH[rand()%10]);
    }
   else
    {
    	strcpy(NomCom.nombre,NomM[rand()%10]);
    }
    return NomCom;
}

TsAlumno agregar()
{
	TsAlumno reg;
	int s;
    reg.matri = rand()%100000+300000;
    if(rand()%2==1)
    {
    	reg.sexo = 1;
    	s = 1;
	    reg.nombres = Genombres(s);
    }
   else
    {
    	reg.sexo = 0;
    	s = 0;
    	reg.nombres = Genombres(s);
    }
    reg.edad = rand()%44+17;
    reg.estado = 1;
    return reg;
}

int cargarT(int tam, char nom[30])
{
	TsAlumno reg;
	TsTemp temp;
	char aux[30];
	int i,t;
	strcpy(aux,nom); strupr(aux); t = strlen(aux);
	if((aux[t-4],aux[t-3],aux[t-2],aux[t-1]) == ('.','T','X','T')){
		
	}
	else
	{
		strcat(nom,".txt");
	}
	FILE *arch;
	arch = fopen(nom,"rt");
	if(arch)
	{
		while(!feof(arch))
		{
			
	        fscanf(arch,"%d%d%s%s%s%d%s", &i, &temp.clave, &temp.aP, &temp.aM, &temp.n, &temp.ed, &temp.sexo);
			reg.estado=1;
	        reg.matri=temp.clave;
	        strcpy(reg.nombres.apeP,temp.aP);
	        strcpy(reg.nombres.apeM,temp.aM);
	        strcpy(reg.nombres.nombre,temp.n);
	        reg.edad=temp.ed;
	        if(strcmp(temp.sexo,"Masculino")==0)
	        {
	        	reg.sexo=1;
	        }
	       else
	        {
	        	reg.sexo=0;
	        }
            tam = agregarB(reg, tam,"Bin.dat");
	    }
		fclose(arch); printf("\nListo!\n");
	}
	else
	{
		printf("\nNo verificaste correctamente la ubicacion, o no escribiste el nombre correctamente del archivo ya que no se ha encontrado\n");
	}
	return tam;
	system("pause");
}

int cargarB(TsAlumno v[],int tam, char nom[30])
{
	TsAlumno reg;
	FILE *arch;
	arch = fopen(nom,"r+b");
	if(arch)
	{
		while(fread(&reg,1,sizeof(TsAlumno),arch))
		{
			v[tam]=reg;
			tam++;
		}
		fclose(arch);
		printf("\nListo!\n");
	}
	else
	{
		fclose(arch);
		printf("\nNo verificaste correctamente la ubicacion, o no escribiste el nombre correctamente del archivo ya que no se ha encontrado\n");
	}
	return tam;
	system("pause");
}

void eliminar(TsAlumno *reg)
{
	int op;
	system("cls");
	op = (int) ValidaNum(1, 2, "Estas seguro?\n   1- Si\n   2- No\n");
	if(op==1){
		reg->estado=0;
        printf("Listo!\n");
	}
    system("pause");
}

int agregarB(TsAlumno reg, int tam, char nom[30])
{
	FILE *arch;
	arch = fopen(nom,"ab");
	fwrite(&reg,1,sizeof(TsAlumno),arch); 
	tam++;
	fclose(arch);
	return tam;
}

int buscar(long num, TsAlumno *aux, int op)
{
	int i,k=0;
	TsAlumno reg;
	system("cls");
	FILE *fa;
	fa = fopen("Bin.dat","rb");
	if(fa)
	{
	   while(!feof(fa)){
		   while(fread(&reg, sizeof(TsAlumno), 1, fa))
           {
   	           if(reg.matri == num)
   	           {
   	        	   if(reg.estado==1)
			       {
			       	   if(op == 2)
			       	   {
			       	   	  *aux = reg;
			       	   }
				       k++;
		    	       printf("Encontrado\n");
		               fclose(fa);
		               return i;
			       }
		          else
		           {
		               printf("El registro que buscas fue eliminado\n");
		               k++;
		           }
		      }
	       }
	   }fclose(fa);
	   if(k==0){
		  return -1;
	   }
    }
   else
    {
	   printf("No se encontro el archivo");
    }
	system("pause");
}

void imprimirB(TsAlumno *reg1, int op)
{
	TsAlumno reg;
	int i=1;
	char sex[10];
	FILE *fa;
	switch(op)
	{
	case 1: fa = fopen("Bin.dat","rb");
	        while(!feof(fa)){
	          	while(fread(&reg, sizeof(TsAlumno), 1, fa))
                {
   	                if(reg.estado == 1)
   	                {
   	  	               if(reg.sexo==1)
		               {
		    	            strcpy(sex,"MASCULINO");
	     	           }
	                  else
	                   {
	                        strcpy(sex,"FEMENINO");
	                   }
	    	           printf("%3d-  %-20s %-20s %-20s |     %6ld    |  %2d  | %10s \n", i, reg.nombres.apeP, reg.nombres.apeM, reg.nombres.nombre, reg.matri, reg.edad, sex); i++;
   	                }
                }
            }fclose(fa); break;
    case 2: if(reg1->estado == 1)
   	        {
				if(reg1->sexo==1)
		        {
		    	    strcpy(sex,"MASCULINO");
	     	    }
	           else
	            {
	                strcpy(sex,"FEMENINO");
	            }
	    	    printf("%3d-  %-20s %-20s %-20s |     %6ld    |  %2d  | %10s \n", i, reg1->nombres.apeP, reg1->nombres.apeM, reg1->nombres.nombre, reg1->matri, reg1->edad, sex);
   	         }
		    else
		     {
		     	printf("\n    El registro fue eliminado\n");
		     }break;
    }
	system("pause");
}

void Archivo(FILE **fa)
{
	int i=0,tam;
	TsAlumno reg;
	char sex[10], nom[30], aux[30];
	FILE *arch;
	printf("Nombre del archivo: "); fflush(stdin); gets(nom); strcpy(aux,nom); strupr(aux); tam = strlen(aux);
	if((aux[tam-4],aux[tam-3],aux[tam-2],aux[tam-1]) == ('.','T','X','T')){
		
	}
	else
	{
		strcat(nom,".txt");
	}
	arch = fopen(nom,"w+");
    rewind(*fa);
    fprintf(arch ,"R E G I S T R O S\n");
	fprintf(arch,"     Nombre Completo                         |   Matricula   | Edad |    Sexo    | Fecha Nacimiento \n");
    while(!feof(*fa)){
	    while(fread(&reg, sizeof(TsAlumno), 1, *fa))
        {
   	         if(reg.estado == 1)
   	         {
   	  	        if(reg.sexo==1)
		        {
		    	    strcpy(sex,"MASCULINO");
	     	    }
	           else
	            {
	                strcpy(sex,"FEMENINO");
	            }
	    	    fprintf(arch,"%3d-  %-20s %-20s %-20s |     %6ld    |  %2d  | %10s \n", i, reg.nombres.apeP, reg.nombres.apeM, reg.nombres.nombre, reg.matri, reg.edad, sex); i++;
   	         }
        }
    }fclose(*fa);
    fclose(arch);
    printf("\nArchivo generado\n   "); system("pause");
}

void Empaque(FILE **fa)
{
   FILE *ftemp;
   TsAlumno reg;
   ftemp = fopen("alea.tmp", "wb");
   rewind(*fa);
   while(fread(&reg, sizeof(TsAlumno), 1, *fa))
   {
   	  if(reg.estado == 1)
   	  {
   	  	 fwrite(&reg, sizeof(TsAlumno), 1, ftemp);
   	  }
   }
   fclose(ftemp);
   fclose(*fa);
   remove("alea.bak");
   rename("alea.dat", "alea.bak");
   rename("alea.tmp", "alea.dat");
   *fa = fopen("alea.dat", "r+b");
   printf("\nLos registros inactivos fueron removidos\n   "); system("pause");
}
