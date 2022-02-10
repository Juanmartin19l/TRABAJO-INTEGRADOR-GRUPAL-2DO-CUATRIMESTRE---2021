#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<locale.h>
#include<Estetica3.h>

int main(){
	setlocale(LC_ALL,""); // permite agregar tildes, la letra ñ y otros caracteres
	system("COLOR 3F"); // selecciona el color del fondo y letra
	
	int opc, TT=0;
	bool inicioSes=false;
	//menu a continuación
	
	do{
		system("cls");
		interfazRec();	
		scanf("%d", &opc);
		printf("\n");
		system("pause");
		system("cls");
		int acceso=0;
		switch(opc){
			case 1:
				inicioSes=iniciarSesRec();
				break;
			case 2:
				if(inicioSes==true){
					clien();	
				}else{
					printf("¡Primero debe iniciar sesión!");
					getch();
				}
				break;
			case 3:
				if(inicioSes==true){
					regturno();	
				}else{
					printf("¡Primero debe iniciar sesión!");
					getch();
				}
				break;
			case 4:
				if(inicioSes==true){
					listur();	
				}else{
					printf("¡Primero debe iniciar sesión!");
					getch();
				}
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
