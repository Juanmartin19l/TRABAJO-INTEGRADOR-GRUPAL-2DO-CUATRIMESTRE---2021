#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<locale.h>
#include<Estetica3.h>

int main(){
	setlocale(LC_ALL,""); // permite agregar tildes, la letra ñ y otros caracteres
	system("COLOR 3F"); // selecciona el color del fondo y letra
	
	int opc, TT=0, id;
	bool inicioSes=false;
	//menu a continuación
	
	do{
		system("cls");
		menues();	
		scanf("%d", &opc);
		printf("\n");
		system("pause");
		system("cls");

		switch(opc){
			case 1:
				if(inicioSes==false){
					inicioSes=iniciarSesMed2(id);
				}else{
					printf("Usted ya inicio sesión con un usuario");
					getch();
				}
				break;
			case 2:
				if(inicioSes==true){
					listarTurnos(id);	
				}else{
					printf("¡Primero debe iniciar sesión!");
					getch();
				}
				break;
			case 3:
				if(inicioSes==true){
					regEvo();
				}else{
					printf("¡Primero debe iniciar sesión!");
					getch();
				}
				break;
			case 4:
				break;
			default:
				printf("El valor ingresado no es válido");
				getch();
				break;
		}
	}while(opc!=4);	
	return 0;
}
