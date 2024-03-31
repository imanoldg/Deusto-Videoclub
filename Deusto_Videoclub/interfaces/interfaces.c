/*
 * interfaces.c
 *
 *  Created on: 13 mar 2024
 *      Author: ima.dominguez
 */

#include <stdio.h>
#include "interfaces.h"
#include <string.h>

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
	printf("\nCONTRASEÑA OLVIDADA\n=======================================\n");

	printf("Introducir DNI: \n");
	printf("Introducir Contraseña Nueva: \n");
}


void menu(void)
{
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
		genero(); // En vez de ir a la ventana de genero debería ir a la ventana propia de alquileres.
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
	FILE *f = fopen("Peliculas.csv", "r");
	char linea[1000];
	char *pelicula;
	char *genero;

	int seleccion;
	int numPelicula = 1;

	printf("\nGENERO\n=======================================");
	printf("1.Accion\n2.Drama\n3.Ciencia Ficcion\n4.Clasicas\n5.Comedia\n6.Terror\n7.Romanticas");

	printf("\nIntroducir opcion: ");

	scanf("%i", &seleccion);

	//FORMATO DEL CSV: Nombre,duración,nota,género, sinopsis
	switch(seleccion)
	{
	case 1:
			//Cargar las peliculas de accion
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
					printf("%d.%s", numPelicula, pelicula);
					numPelicula++;
				}
			}
	}
}

void genero(void)
{
	int opcionGenero;
	printf("\n=======================================\nGENERO\n=======================================\n\n");

	printf("\n1.Accion\n2.Drama\n3.Ciencia Ficcion\n4.Clásicas\n5.Comedia\n6.Terror\n7.Romanticas");
	printf("\nIntroducir opcion: ");
	
	scanf("%i", &opcionGenero);

	switch (opcionGenero)
	{
	case 1:
		// listado peliculas Acción.
		break;
	case 2:
		// listado peliculas Drama.
		break;
	case 3:
		// listado peliculas Ciencia ficción.
		break;
	case 4:
		// listado peliculas Clásicas.
		break;
	case 5:
		// listado peliculas Comedia.
		break;
	case 6:
		// listado peliculas Terror.
		break;
	case 7:
		// listado peliculas Románticas.
		break;
	default:
		break;
	}

}

void datosUsuario(void)
{
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
