#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

struct fecha{
	int dia;	
	int mes;
	int anio;	
};

struct user
{
    char usuario[10];
    char contrasenia[32];
    char apeNom[60];
    bool prof; // prof = true (usuario profesional), prof = false (usuario recepcionista)			
};

struct prof
{
	char apeNom[60];
	int idPro;
	int dni;
	char tel[25];
};

struct cli
{
	char apeNom[60];	
	char dom[60];
	int dni;
	char loc[60];
	fecha nac;
	float peso;
	char tel[25];
};

struct turn
{
	int idPro;
	fecha fec;
	int dni;
	char detalleAt[380];
	bool borrado; // borrado  = true (el turno fue gestionado), borrado = false (el turno sigue pendiente)	
};

struct rank
{
    char apeNom[60];
    int turnosAtendidos;
    int idPro;
};

struct nodo
{
    rank info;
    nodo *sig;
};

//las funciones sgtes son del módulo de administración

void interfazAdm(){
	printf("Módulo Administración");
	printf("\n=========================");
	printf("\n1.- Registrar Profesional");
	printf("\n2.- Registrar Usuario Recepcionista");
	printf("\n3.- Atenciones por Profesional");	
	printf("\n4.- Ranking de Profesionales por Atenciones\n");	
	printf("\n5.- Cerrar la aplicación.\n");	
	printf("\nIngrese una opción: ");
}

void datosProf(prof x){
	printf("\nApellido/s y Nombre/s: %s", x.apeNom);
	printf("\nIdProfesional: %d", x.idPro);
	printf("\nDNI: %d", x.dni);
	printf("\nTeléfono: %s", x.tel);
}

bool validarUsername(char u[10]){
	FILE *arch;
	user x;
	bool aux=true;
	arch = fopen("Usuarios.dat", "a+b");
	
	fread(&x, sizeof(user), 1, arch);
	while(!feof(arch)){
		if(strcmp(x.usuario, u) == 0){
			printf("\nERROR: El nombre de usuario ya existe\n");
			aux=false;
			break;
		}
		fread(&x, sizeof(user), 1, arch);
	}
	
	fclose(arch);
	
	if(strlen(u)>10){
		printf("\nERROR: El nombre de usuarios excede los 10 caracteres\n");
		aux=false;
	}		
	
	if(strlen(u)<6){
		printf("\nERROR: El nombre de usuario debe tener mínimo 6 caracteres\n");
		aux=false;
	}

	if(isupper(u[0])==0){
		printf("\nERROR: El primer carácter debe ser una letra mayúscula\n");
		aux=false;
	}

	int mayus=0;
	for(int i=0; i<10; i++){
		if(isupper(u[i])!=0){
			mayus++;
		}
	}
	if(mayus<2){
		printf("\nERROR: El nombre de usuario debe tener al menos 2 mayúsculas\n");
		aux=false;
	}

	int digit=0;
	for(int j=0; j<10; j++){
		if(isdigit(u[j])!=0){
			digit++;
		}
	}
	if(digit>3){
		printf("\nERROR: El nombre de usuario debe tener como máximo 3 dígitos\n");
		aux=false;
	}
	
	if(aux==false){
		printf("\n");
		return true;
	}else{
		return false;
	}
}

bool validarCont(char u[32]){
	int i, m=0, M=0, n=0;
	bool aux=true;
	char auxiliar[32];
	strcpy(auxiliar, u);
	
	for(i=0; i<strlen(u); i++){
		if(isalnum(u[i])==0){
			printf("\nERROR: La contraseña solo debe contener caracteres alfanuméricos\n");
			aux=false;
			break;
		}
	}

	for(i=0; i<32; i++){
		if(isupper(u[i])!=0){
			M++;
		}
		
		if(isdigit(u[i])!=0){
			n++;
		}
		
		if(islower(u[i])!=0){
			m++;
		}
	}
	
	if(M<1){
		printf("\nERROR: La contraseña debe tener al menos una mayúscula\n");
		aux=false;
	}
	
	if(m<1){
		printf("\nERROR: La contraseña debe tener al menos una minúscula\n");
		aux=false;
	}
	
	if(n<1){
		printf("\nERROR: La contraseña debe tener al menos un número\n");
		aux=false;
	}
	
	if(strlen(u)>32){
		printf("\nERROR: La contraseña excede los 32 caracteres\n");
		aux=false;
	}		
	
	if(strlen(u)<6){
		printf("\nERROR: La contraseña debe tener mínimo 6 caracteres\n");
		aux=false;
	}
	
	for(i=2; i<31; i++){
		if(isdigit(u[i-2])!=0 && isdigit(u[i-1])!=0 && isdigit(u[i])!=0 && isdigit(u[i+1])!=0){
			printf("\nERROR: La contraseña no debe tener más de 3 números seguidos\n");
			aux=false;
			break;
		}
	}
	
	strlwr(auxiliar);
	
	int num1,num2;
	
	for(i=0; i<32; i++){
		if(isalpha(auxiliar[i])!=0){
			num1=auxiliar[i];
			num2=auxiliar[i+1];
			if(num1+1==num2){
				printf("\nERROR: La contraseña no puede tener dos letras alfábeticamente consecutivas (ascendente)");
				aux=false;
				break;
			}
		}
	}

	//
	
	if(aux==false){
		printf("\n");
		return true;
	}else{
		return false;
	}
}

void registrarProf(){
	FILE *arch1, *arch2;
	arch1 = fopen("Profesionales.dat","a+b");
	arch2 = fopen("Usuarios.dat", "a+b");
	
	prof x;
	user y;
	bool band;
	
	printf("Registrar Profesional");
	printf("\n=========================");
	
	y.prof = true;
		
	printf("\nApellido/s y Nombre/s: ");
	_flushall();
	gets(x.apeNom);
	strcpy(y.apeNom, x.apeNom);
	
	printf("IdProfesional: ");
	scanf("%d", &x.idPro);
	
	printf("DNI: ");
	scanf("%d", &x.dni);
	
	printf("Teléfono: ");
	_flushall();
	gets(x.tel);
	
	do{
		band=false;
		
		printf("\nUsuario: ");
		_flushall();
		gets(y.usuario);
		band=validarUsername(y.usuario);
		if(band==true){
			system("pause");
			system("cls");
			printf("Registrar Profesional");
			printf("\n=========================");
			datosProf(x);
			printf("\n");
		}	
	}while(band==true);
	
	do{
		band=false;
		
		printf("Contraseña: ");
		_flushall();
		gets(y.contrasenia);
		band=validarCont(y.contrasenia);
		
		if(band==true){
			printf("\n");
			system("pause");
			system("cls");
			printf("Registrar Profesional");
			printf("\n=========================");
			datosProf(x);
			_flushall();
			printf("\n\nUsuario: ");
			puts(y.usuario);
		}
	}while(band==true);
	
	fwrite(&x, sizeof(prof), 1, arch1);
	fwrite(&y, sizeof(user), 1, arch2);
	
	printf("\n=========================");
	printf("\nDatos de Profesional Guardados");
	getch();
	
	fclose(arch1);
	fclose(arch2);
}

void datosRec(struct user x){
	printf("Registrar Usuario Recepcionista");
	printf("\n=========================");
	printf("\n\nApellido/s y Nombre/s: %s", x.apeNom);
}

void registrarRec(){
	FILE *arch;
	arch = fopen("Usuarios.dat", "a+b");
	
	user x;
	bool band;;
	
	printf("Registrar Usuario Recepcionista");
	printf("\n=========================");
	
	printf("\n\nApellido/s y Nombre/s: ");
	_flushall();
	gets(x.apeNom);
	
	x.prof = false;
	
	do{
		band=false;
		
		printf("Usuario: ");
		_flushall();
		gets(x.usuario);
		band=validarUsername(x.usuario);
		if(band==true){
			system("pause");
			system("cls");
			datosRec(x);
			printf("\n");
		}	
	}while(band==true);
	
	do{
		band=false;
		
		printf("Contraseña: ");
		_flushall();
		gets(x.contrasenia);
		band=validarCont(x.contrasenia);
		
		if(band==true){
			printf("\n");
			system("pause");
			system("cls");
			datosRec(x);
			_flushall();
			printf("\nUsuario: ");
			puts(x.usuario);
		}
	}while(band==true);
	
	fwrite(&x, sizeof(user), 1, arch);
	
	printf("\n\n=========================");
	printf("\nDatos de Profesional Guardados");
}

bool verificarId(int id, struct prof &y){
	FILE *arch;
	arch = fopen("Profesionales.dat", "a+b");
	
	prof x;
	bool band=false;
	
	fread(&x, sizeof(prof), 1, arch);
	while(!feof(arch)){
		if(x.idPro==id){
			y.dni=x.dni;
			y.idPro=x.idPro;
			strcpy(y.apeNom,x.apeNom);
			strcpy(y.tel,x.tel);
			band = true;
			break;
		}
		fread(&x, sizeof(prof), 1, arch);
	}
	
	if(band==true){
		return true;
	}else{
		return false;
	}
	
	fclose(arch);
}

void verAtencProf(){
	FILE *arch1, *arch2;
	arch1 = fopen("Turnos.dat", "a+b");
	arch2 = fopen("Profesionales.dat", "a+b");
	
	bool profEx=false, atend=false;
	int id;
	prof x;
	turn z;
	
	do{
		system("cls");
		printf("Atenciones por Profesional");
		printf("\n=========================\n");
		printf("Ingrese ID del Profesional: ");
		scanf("%d", &id);
		
		profEx=verificarId(id, x);
		
		if(profEx==false){
			printf("\nEl ID ingresado no corresponde a ningún profesional");
			getch();
		}	
	}while(profEx==false);
	
	if(profEx==true){
		printf("\nLos datos del profesional son: ");
		printf("\n=========================");
		datosProf(x);
		
		fread(&z, sizeof(turn), 1, arch1);
		while(!feof(arch1)){
			if(z.borrado == true && z.idPro == id){
				atend=true;	
				printf("\n\nTurno administrado en la fecha %d/%d/%d",z.fec.dia,z.fec.mes,z.fec.anio);
				printf("\nDNI del cliente: %d", z.dni);
				printf("\nObservaciones: %s", z.detalleAt);		
			}
			fread(&z, sizeof(turn), 1, arch1);	
		}
		
		if(atend==false) printf("\n\nEl profesional no ha administrado turnos todavía");	
		getch();
	}
	
	fclose(arch1);
	fclose(arch2);
}

void funcNodo(nodo *&puntero, rank valor){
    nodo *nuevo = new nodo();
    nuevo->info = valor;

    nodo *aux1 = puntero;
    nodo *aux2;

    while ((aux1 != NULL) and (aux1->info.turnosAtendidos > valor.turnosAtendidos))
    {
        aux2 = aux1;
        aux1 = aux1->sig;
    }

    if (puntero == aux1)
    {
        puntero = nuevo;
    }
    else
    {
        aux2->sig = nuevo;
    }

    nuevo->sig = aux1;
}

void listar(nodo *puntero){
    nodo *p = puntero;

    int posicion = 1;

    while (p != NULL)
    {
        printf("\n#%d_ Profesional: %s", posicion, p->info.apeNom);
        printf("\nID Profesional: %d", p->info.idPro);
        printf("\nTurnos atendidos: %d\n", p->info.turnosAtendidos);
        p = p->sig;
        posicion++;
    }
}

void rankProf(){
	FILE *archT, *archP;
	archT = fopen("Turnos.dat", "a+b");
	archP = fopen("Profesionales.dat", "a+b");
	
	prof x;
	turn y;
	int numAten;
	rank rankingProf;
	
	nodo *lista;
	lista = NULL;
	
	fread(&x, sizeof(prof), 1, archP);
	while(!feof(archP)){
		fread(&y, sizeof(turn), 1, archT);
		numAten=0;
		while(!feof(archT)){
			if(x.idPro==y.idPro && y.borrado==true){
				numAten++;
			}
			fread(&y, sizeof(turn), 1, archT);
		}
		strcpy(rankingProf.apeNom,x.apeNom);
		rankingProf.idPro=x.idPro;
		rankingProf.turnosAtendidos=numAten;
		
		funcNodo(lista, rankingProf);
		
		fread(&x, sizeof(prof), 1, archP);
	} 
	
	fclose(archT);
	fclose(archP);
	
	system("cls");

	printf("Ranking de Profesionales\n");
	printf("=======================\n");

	if (lista == NULL)
	{
		printf("\nNo hay profesionales registrados...");
	}

	listar(lista);

	getch();
}

//las funciones sgtes son del módulo de recepción

void interfazRec(){
	printf("Módulo Recepción");
	printf("\n=========================");
	printf("\n1.- Iniciar Sesión");
	printf("\n2.- Registrar Cliente");
	printf("\n3.- Registrar Turno");	
	printf("\n4.- Listado de Atenciones por Profesional y Fecha\n");	
	printf("\n5.- Cerrar la aplicación.\n");	
	printf("\nIngrese una opción: ");
}

void clien(){
	FILE *arch;
	cli a;
	arch = fopen ("Clientes.dat","a+b");
	
	printf("Registrar cliente\nNombre: ");
	_flushall();
	gets(a.apeNom);
	printf("Domicilio: ");
	_flushall();
	gets(a.dom);
	printf("DNI: ");
	scanf("%d", &a.dni);
	printf("Localidad: ");
	_flushall();
	gets(a.loc);
	printf("Fecha Nacimiento (DD/MM/AA):\n");
	scanf("%d", &a.nac.dia);
	scanf("%d", &a.nac.mes);
	scanf("%d", &a.nac.anio);
	printf("Peso: ");
	scanf("%f", &a.peso);
	printf("Telefono: ");
	_flushall();
	gets(a.tel);
	fwrite(&a,sizeof(cli),1,arch);
	fclose(arch);
}
/*		BORRAR
void vercli(){
	FILE *arch;
	turn a;
	arch = fopen ("Turnos.dat","a+b");
	fread(&a,sizeof(turn),1,arch);
	printf("\n\nDNI: %d", a.dni);
	fclose(arch);
	system("pause");
}		BORRAR
*/
int valiDNI(int dni){
	FILE *arch;
	cli a;
	int ban=0;
	arch = fopen ("Clientes.dat","a+b");
	fread(&a,sizeof(cli),1,arch);
	while (!feof(arch)){
		if(dni == a.dni){
			ban=1;
		}
		fread(&a,sizeof(cli),1,arch);
	}
	return ban;
	fclose(arch);
}

int valiID(int ide){
	FILE *arch;
	arch = fopen("Profesionales.dat", "a+b");
	prof a;
	int ban=0;
	fread(&a,sizeof(prof),1,arch);
	while (!feof(arch)){
		if(ide == a.idPro){
			ban=1;
		}
		fread(&a,sizeof(prof),1,arch);
	}
	return ban;
	fclose(arch);
}

void regturno(){
	FILE *arch;
	turn a;
	arch = fopen ("Turnos.dat","a+b");
	int ban=0, dni, bol=0, ide;
	printf("DNI Cliente: ");
	scanf("%d", &a.dni);
	dni=a.dni;
	ban=valiDNI(dni);
	
	if(ban==1){
		printf("IdProfesional: ");
		scanf("%d", &a.idPro);
		ide=a.idPro;
		bol=valiID(ide);
		if(bol==1){
			printf("Fecha (DD/MM/AA): \n");
			scanf("%d", &a.fec.dia);
			scanf("%d", &a.fec.mes);
			scanf("%d", &a.fec.anio);
			printf("Detalle de atencion: ");
			_flushall();
			gets(a.detalleAt);
			a.borrado=false;
			fwrite(&a,sizeof(turn),1,arch);
		}else{
			printf("\nERROR IdProfesional NO REGISTRADO\n");
		}
		
	}else{
		printf("\nERROR DNI NO REGISTRADO\n");
	}

	fclose(arch);
	system("pause");
}

bool iniciarSesRec(){
	FILE *arch;
	arch=fopen("Usuarios.dat", "a+b");
	
	user x;
	char u[10], c[32], nom[60];
	bool aux=false, rec=false;
	
	do{
		printf("Iniciar Sesión");
		printf("\n=========================");
		printf("\nUsuario: ");
		_flushall();
		gets(u);
		
		fseek(arch, 0, SEEK_SET);
		fread(&x, sizeof(user), 1, arch);
		
		while(!feof(arch)){
			if(strcmp(u,x.usuario)==0){
				aux=true;
				if(x.prof==false){
					rec=true;
				} 
			}
			fread(&x, sizeof(user), 1, arch);	
		}
		
		if(aux==false){
			printf("\nERROR: Usuario no existe");
			getch();
			system("cls");
		}else if(rec==false){
			printf("\nERROR: El usuario no es Recepcionista");
			getch();
			system("cls");
		}
	}while(aux==false || rec==false);
	
	aux=false;
	
	do{
		printf("Contraseña: ");
		_flushall();
		gets(c);
		
		fseek(arch, 0, SEEK_SET);
		fread(&x, sizeof(user), 1, arch);
		while(!feof(arch)){
			
			if(strcmp(u,x.usuario)==0 && strcmp(c,x.contrasenia)==0){
				aux=true;
				strcpy(nom, x.apeNom);
			}
			
			fread(&x, sizeof(user), 1, arch);
		}
		
		if(aux==false){
			printf("\nERROR: Contraseña incorrecta");
			getch();
			system("cls");
			printf("Iniciar Sesión");
			printf("\n=========================");
			printf("\nUsuario: %s\n", u);
		}
		
	}while(aux==false);
	
	printf("\nBienvenido %s", nom);
	getch();
	
	fclose(arch);
	return true;
}

void listarturnos(fecha fec){
	FILE *arch;
	turn a;
	arch = fopen ("Turnos.dat","a+b");
	fread(&a,sizeof(turn),1,arch);
	while (!feof(arch)){
		if(fec.dia == a.fec.dia and fec.mes == a.fec.mes and fec.anio == a.fec.anio and a.borrado==true){
			printf("\nDNI del clinete atendido: %d", a.dni);
		}
		fread(&a,sizeof(turn),1,arch);	
	}
	fclose(arch);
}

void listur(){
	int medi, ban=0;
	fecha fec;
	prof a;
	printf("Ingrese ID del Medico: ");
	scanf("%d", &a.idPro);
	medi=a.idPro;
	ban=valiID(medi);
	if(ban==1){
		printf("Ingrese Fecha (DD/MM/AA): \n");
		scanf("%d", &fec.dia);
		scanf("%d", &fec.mes);
		scanf("%d", &fec.anio);
		listarturnos(fec);
	}else{
		printf("\nERROR ID del Medico no existe");
	}
	getch();
}

void menues(){
	printf("Módulo Espacios");
	printf("\n=========================");
	printf("\n1.- Iniciar Sesión");
	printf("\n2.- Visualizar Lista de Espera de Turnos (informe)");
	printf("\n3.- Registrar Evolución del tratamiento");		
	printf("\n4.- Cerrar la aplicación.\n");	
	printf("\nIngrese una opción: ");
}

bool iniciarSesMed(){
	FILE *arch;
	arch=fopen("Usuarios.dat", "a+b");
	
	user x;
	char u[10], c[32], nom[60];
	bool aux=false, rec=false;
	
	do{
		printf("Iniciar Sesión");
		printf("\n=========================");
		printf("\nUsuario: ");
		_flushall();
		gets(u);
		
		fseek(arch, 0, SEEK_SET);
		fread(&x, sizeof(user), 1, arch);
		
		while(!feof(arch)){
			if(strcmp(u,x.usuario)==0){
				aux=true;
				if(x.prof==true){
					rec=true;
				} 
			}
			fread(&x, sizeof(user), 1, arch);	
		}
		
		if(aux==false){
			printf("\nERROR: Usuario no existe");
			getch();
			system("cls");
		}else if(rec==false){
			printf("\nERROR: El usuario no es un Profesional");
			getch();
			system("cls");
		}
	}while(aux==false || rec==false);
	
	aux=false;
	
	do{
		printf("Contraseña: ");
		_flushall();
		gets(c);
		
		fseek(arch, 0, SEEK_SET);
		fread(&x, sizeof(user), 1, arch);
		while(!feof(arch)){
			
			if(strcmp(u,x.usuario)==0 && strcmp(c,x.contrasenia)==0){
				aux=true;
				strcpy(nom, x.apeNom);
			}
			
			fread(&x, sizeof(user), 1, arch);
		}
		
		if(aux==false){
			printf("\nERROR: Contraseña incorrecta");
			getch();
			system("cls");
			printf("Iniciar Sesión");
			printf("\n=========================");
			printf("\nUsuario: %s\n", u);
		}
		
	}while(aux==false);
	
	printf("\nBienvenido %s", nom);
	getch();
	
	fclose(arch);
	return true;
}

void lismedico(fecha fec){
	FILE *arch;
	turn a;
	int ban=0;
	arch = fopen ("Turnos.dat","a+b");
	fread(&a,sizeof(turn),1,arch);
	while (!feof(arch)){
		if(fec.dia == a.fec.dia and fec.mes == a.fec.mes and fec.anio == a.fec.anio and a.borrado==false){
			printf("\nDNI del clinete por atender: %d", a.dni);// cambiar por nombre y apellido en vez de mostrar dni
			ban=1;
		}
		fread(&a,sizeof(turn),1,arch);	
	}
	if (ban==0){
		printf("\nNo hay clientes hoy\n");
	}
	fclose(arch);
}
/*
void espera(){
	int medi, ban=0;
	fecha fec;
	prof a;
	printf("Ingrese su ID: ");
	scanf("%d", &a.idPro);
	medi=a.idPro;
	ban=valiID(medi);
	if(ban==1){
		printf("Ingrese Fecha (DD/MM/AA): \n");
		scanf("%d", &fec.dia);
		scanf("%d", &fec.mes);
		scanf("%d", &fec.anio);
		lismedico(fec);
	}else{
		printf("\nERROR ID del Medico no existe");
	}
	getch();
} */

bool iniciarSesMed2(int &id){
	FILE *arch, *arch1;
	arch=fopen("Usuarios.dat", "a+b");
	arch1=fopen("Profesionales.dat", "a+b");
	
	user x;
	prof y;
	char u[10], c[32], nom[60];
	bool aux=false, rec=false;
	
	do{
		printf("Iniciar Sesión");
		printf("\n=========================");
		printf("\nUsuario: ");
		_flushall();
		gets(u);
		
		fseek(arch, 0, SEEK_SET);
		fread(&x, sizeof(user), 1, arch);
		
		while(!feof(arch)){
			if(strcmp(u,x.usuario)==0){
				aux=true;
				if(x.prof==true){
					rec=true;
					
					//a continuación se guarda el id
					fread(&y, sizeof(prof), 1, arch1);
					while(!feof(arch1)){
						if(strcmp(y.apeNom, x.apeNom)==0){
							id = y.idPro;
						}
						fread(&y, sizeof(prof), 1, arch1);
					}
					
				} 
			}
			fread(&x, sizeof(user), 1, arch);	
		}
		
		if(aux==false){
			printf("\nERROR: Usuario no existe");
			getch();
			system("cls");
		}else if(rec==false){
			printf("\nERROR: El usuario no es un Profesional");
			getch();
			system("cls");
		}
	}while(aux==false || rec==false);
	
	aux=false;
	
	do{
		printf("Contraseña: ");
		_flushall();
		gets(c);
		
		fseek(arch, 0, SEEK_SET);
		fread(&x, sizeof(user), 1, arch);
		while(!feof(arch)){
			
			if(strcmp(u,x.usuario)==0 && strcmp(c,x.contrasenia)==0){
				aux=true;
				strcpy(nom, x.apeNom);
			}
			
			fread(&x, sizeof(user), 1, arch);
		}
		
		if(aux==false){
			printf("\nERROR: Contraseña incorrecta");
			getch();
			system("cls");
			printf("Iniciar Sesión");
			printf("\n=========================");
			printf("\nUsuario: %s\n", u);
		}
		
	}while(aux==false);
	
	printf("\nBienvenido %s", nom);
	getch();
	
	fclose(arch);
	fclose(arch1);
	return true;
}

void mostrarTurno(turn x){
	printf("\nDNI: %d", x.dni);
	printf("\nFecha: %d/%d/%d", x.fec.dia, x.fec.mes, x.fec.anio);
	printf("\nObservaciones: %s", x.detalleAt);
}

void listarTurnos(int id){
	FILE *arch;
	turn x;
	int cont=0;
	arch = fopen("Turnos.dat", "a+b");
	
	printf("Visualizar Lista de Espera de Turnos (informe)");
	printf("\n=========================");
	printf("\nSus turnos pendientes son los siguientes: \n");
	
	fread(&x, sizeof(turn), 1, arch);
	while(!feof(arch)){
		if(x.borrado==false && x.idPro==id){
			cont++;
			mostrarTurno(x);
			printf("\n*************************");
		}
		fread(&x, sizeof(turn), 1, arch);
	}
	
	if(cont==0){
		printf("\nNo hay turnos pendientes");
	}
	
	getch();
	
	fclose(arch);
}

void regEvo(){
	FILE *arch, *aux;
	bool band=false;
	int dni;
	turn x, z;
	char obs[380];
	arch = fopen("Turnos.dat", "a+b");
	aux = fopen("Auxiliar.dat", "wb");
	
	do{
		printf("Registrar Evolución del tratamiento");
		printf("\n=========================");
		printf("\nIngrese el DNI del paciente: ");
		scanf("%d", &dni);
		
		fseek(arch, 0, SEEK_SET);
		fread(&x, sizeof(turn), 1, arch);
		while(!feof(arch)){
			if(x.dni == dni && x.borrado==false){
				band=true;
				z.borrado = true;
				z.dni = x.dni;
				z.fec.anio = x.fec.anio;
				z.fec.mes = x.fec.mes;
				z.fec.dia = x.fec.dia;
				z.idPro = x.idPro;
				strcpy(z.detalleAt, x.detalleAt);
			}
			fread(&x, sizeof(turn), 1, arch);
		}
		
		if(band==false){
			printf("\nEl DNI ingresado no corresponde a ningún turno");
			getch();
			system("cls");
		}
		
	}while(band==false);
	
	printf("\nIngrese las observaciones del paciente: ");
	_flushall();
	gets(obs);
	strcat(z.detalleAt, obs);
	
	fseek(arch, 0, SEEK_SET);
	fread(&x, sizeof(turn), 1, arch);
	while(!feof(arch)){
		if(dni!=x.dni){
			fwrite(&x, sizeof(turn), 1, aux);
		}else{
			fwrite(&z, sizeof(turn), 1, aux);
		}
		fread(&x, sizeof(turn), 1, arch);	
	}
	fclose(arch);
	fclose(aux);
	
	remove("Turnos.dat");
	rename("Auxiliar.dat", "Turnos.dat");
}


































