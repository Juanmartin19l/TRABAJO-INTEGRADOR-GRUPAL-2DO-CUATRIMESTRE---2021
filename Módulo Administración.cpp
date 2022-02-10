#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<locale.h>
#include<Estetica3.h>
 
int main(){
	setlocale(LC_ALL,""); // permite agregar tildes, la letra ñ y otros caracteres
	system("COLOR 3F"); // selecciona el color del fondo y letra
	
	int opc; 
	
	//menu a continuación
	
	do{
		system("cls");
		interfazAdm();	
		scanf("%d", &opc);
		printf("\n");
		system("pause");
		system("cls");
		
		switch(opc){
			case 1:
				registrarProf();
				break;
			case 2:
				registrarRec();
				break;
			case 3:
				verAtencProf();
				break;
			case 4:
				rankProf();
				break;
			case 5:
				break;
			default:
				printf("El valor ingresado no es válido");
				getch();
				break;
		}
	}while(opc!=5);

	
	return 0;
}
