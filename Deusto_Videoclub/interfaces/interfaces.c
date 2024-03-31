/*
 * interfaces.c
 *
 *  Created on: 13 mar 2024
 *      Author: ima.dominguez
 */

#include <stdio.h>
#include "interfaces.h"
#include <string.h>
#include <stdlib.h>

void inicio(void)
{
	int option;
	printf("=======================================\n             VIDEOCLUB\n=======================================\n\n");

	printf("1.Iniciar Sesión\n2.Registrar Usuario\n3.Contraseña Olvidada\n4.Salir\n");
	printf("Introducir opcion: ");
	scanf("%i", &option);
	switch (option)
	{
	case 1:
		iniciarSesion();
		break;
	
	case 2:
		registrarUsuario();
		break;
	case 3:
		contrasenyaOlvidada();
		break;
	case 4:
		printf("salir\n");
		break;
	default:
		printf("Opcion no valida\n");
		break;
	}
}

void iniciarSesion(void)
{
	system("cls");
	char usuario[10];
	char password[10];

	printf("\n=======================================\nINICIO DE SESION\n=======================================\n\n");

	printf("Introducir Usuario: ");
	scanf("%s", &usuario);

	printf("Introducir Contraseña: ");
	scanf("%s", &password);

	if ((strcmp(usuario, "pomodoro") == 0) && (strcmp(password, "liso") == 0))
	{
		menu();
	}else
	{
		printf("usuario o contraseña incorrectos");
	}
}

void registrarUsuario(void)
{
	system("cls");
	printf("\nREGISTRO DE SESIÓN\n=======================================");

	printf("Introducir Nombre: \n");
	printf("Introducir Apellido: \n");
	printf("Introducir DNI: \n");
	printf("Introducir email: \n");
	printf("Introducir Nº Tarjeta: \n");
	printf("Introducir Género(H/M): \n");
	printf("Introducir Año Nacimiento(XXXX): \n");
	printf("Introducir Mes Nacimiento(XX): \n");
	printf("Introducir Día Nacimiento(XX): \n");
	printf("Introducir Usuario: \n");
	printf("Introducir Contraseña: \n");
}

void contrasenyaOlvidada(void)
{
	system("cls");
	printf("\nCONTRASEÑA OLVIDADA\n=======================================\n");

	printf("Introducir DNI: \n");
	printf("Introducir Contraseña Nueva: \n");
}


void menu(void)
{
	system("cls");
	int optionMenu;
	printf("\n=======================================\nBIENVENIDO AL MENU PRINCIPAL\n=======================================\n\n");

	printf("1.Alquilar película\n2.Extender alquiler\n3.Datos de usuario\n4.Datos de alquiler\n5.Cerrar Sesion\n");

	printf("\nintroducir opcion: ");

	scanf("%i", &optionMenu);

	switch (optionMenu)
	{
	case 1:
		alquilarPelicula(); //de esta ventana irá a peliculas de dicho genero para luego gestionar el alquiler.
		break;
	case 2:
		//genero(); // En vez de ir a la ventana de genero debería ir a la ventana propia de alquileres.
		break;
	case 3:
		datosUsuario();
		break;
	case 4:

		break;
	case 5:

		break;
	default:
		break;
	}

}

void alquilarPelicula(void)
{
	system("cls");
	FILE *f = fopen("Peliculas.csv", "r");
	char linea[1000];
	char *pelicula;
	char *genero;
	char titulo;

	int seleccion;
	int numPelicula = 1;

	printf("\nGENERO\n=======================================\n");
	printf("\n1.Accion\n2.Drama\n3.Ciencia Ficcion\n4.Clasicas\n5.Comedia\n6.Terror\n7.Romanticas");

	printf("\nIntroducir opcion: ");

	scanf("\n%i", &seleccion);

	printf("\nPELICULAS\n=======================================\n");
	//FORMATO DEL CSV: Nombre,duración,nota,género, sinopsis
	switch(seleccion)
	{
	case 1:
			
			//Cargar las peliculas de ACCION
			while(fgets(linea, sizeof(linea), f)){
				pelicula = strtok(linea, ";");
				//Apunta a la duracion
				genero = strtok(NULL, ";");
				//Apunta a la nota
				genero = strtok(NULL, ";");
				//Apunta al genero
				genero = strtok(NULL, ";");

				if(strcmp(genero, "Acción") == 0)
				{
					printf("%d.%s\n", numPelicula, pelicula);
					numPelicula++;
				}

				printf("\nIntroduce el titulo de la pelicula: ");
				scanf("\n%s", &titulo);

				printf("\nALQUILER: %s\n=======================================");
			}

	case 2:
			
			//Cargar las peliculas de DRAMA
			while(fgets(linea, sizeof(linea), f)){
				pelicula = strtok(linea, ";");
				//Apunta a la duracion
				genero = strtok(NULL, ";");
				//Apunta a la nota
				genero = strtok(NULL, ";");
				//Apunta al genero
				genero = strtok(NULL, ";");

				if(strcmp(genero, "Drama") == 0)
				{
					printf("%d.%s\n", numPelicula, pelicula);
					numPelicula++;
				}
			}

	case 3:
			//Cargar las peliculas de CIENCIA FICCION
			while(fgets(linea, sizeof(linea), f)){
				pelicula = strtok(linea, ";");
				//Apunta a la duracion
				genero = strtok(NULL, ";");
				//Apunta a la nota
				genero = strtok(NULL, ";");
				//Apunta al genero
				genero = strtok(NULL, ";");

				if(strcmp(genero, "Ciencia Ficción") == 0)
				{
					printf("%d.%s\n", numPelicula, pelicula);
					numPelicula++;
				}
			}	
	case 4:
			//Cargar las peliculas CLASICAS
			while(fgets(linea, sizeof(linea), f)){
				pelicula = strtok(linea, ";");
				//Apunta a la duracion
				genero = strtok(NULL, ";");
				//Apunta a la nota
				genero = strtok(NULL, ";");
				//Apunta al genero
				genero = strtok(NULL, ";");

				if(strcmp(genero, "Clásica") == 0)
				{
					printf("%d.%s\n", numPelicula, pelicula);
					numPelicula++;
				}
			}

	case 5:
			//Cargar las peliculas de COMEDIA
			while(fgets(linea, sizeof(linea), f)){
				pelicula = strtok(linea, ";");
				//Apunta a la duracion
				genero = strtok(NULL, ";");
				//Apunta a la nota
				genero = strtok(NULL, ";");
				//Apunta al genero
				genero = strtok(NULL, ";");

				if(strcmp(genero, "Comedia") == 0)
				{
					printf("%d.%s\n", numPelicula, pelicula);
					numPelicula++;
				}
			}
	case 6:
			//Cargar las peliculas de TERROR
			while(fgets(linea, sizeof(linea), f)){
				pelicula = strtok(linea, ";");
				//Apunta a la duracion
				genero = strtok(NULL, ";");
				//Apunta a la nota
				genero = strtok(NULL, ";");
				//Apunta al genero
				genero = strtok(NULL, ";");

				if(strcmp(genero, "Terror") == 0)
				{
					printf("%d.%s\n", numPelicula, pelicula);
					numPelicula++;
				}
			}
	case 7:
			//Cargar las peliculas ROMANTICAS
			while(fgets(linea, sizeof(linea), f)){
				pelicula = strtok(linea, ";");
				//Apunta a la duracion
				genero = strtok(NULL, ";");
				//Apunta a la nota
				genero = strtok(NULL, ";");
				//Apunta al genero
				genero = strtok(NULL, ";");

				if(strcmp(genero, "Romántica") == 0)
				{
					printf("%d.%s\n", numPelicula, pelicula);
					numPelicula++;
				}
			}

	default: printf("Opcion no valida");
	}
}


void datosUsuario(void)
{
	system("cls");
	int opcionDatosUsuario;
	printf("\n=======================================\nDATOS USUARIO\n=======================================\n\n");
	printf("\nNombre: \nApellido: \nDNI: \nEmail: \nNº Tarjeta: \nGenero(H/M): \nFecha Nacimiento: \nUsuario: \nPuntos: \n");
	printf("\n¿Que quieres hacer?\n1.Editar informacion\n2.Eliminar Usuario\n3.Volver al Menu\n\nIntroducir opcion: ");

	scanf("%i\n", &opcionDatosUsuario);

	switch (opcionDatosUsuario)
	{
	case 1:
		
		break;
	case 2:
		
		break;
	case 3:
		menu();
		break;
	default:
		break;
	}
}

void datosAlquiler(void)
{

}
