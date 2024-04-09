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
#include "sqlite3.h"
//FUNCION DEL INICIO DEL PROGRAMA
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
//FUNCION PARA INICIAR SESION
void iniciarSesion(void)
{
	system("cls");
	char usuario[40];
	char contrasenha[60];
	char contrasenhaBD[60];

	printf("\n=======================================\nINICIO DE SESION\n=======================================\n\n");

	printf("Introducir Usuario: ");
	scanf("%s", usuario);

	printf("Introducir Contraseña: ");
	scanf("%s", contrasenha);

	sqlite3 *db;
	sqlite3_stmt *stmt;
	int result;

	sqlite3_open("BaseDeDatos/UserDB.db", &db);

	//COMPROBAR QUE LA CONTRASEÑA DEL USUARIO INTRODUCIDO ES CORRECTA
	char sql[] = "SELECT Password FROM usuario WHERE User = ?";
	
	sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
	sqlite3_bind_text(stmt, 1, usuario, strlen(usuario), SQLITE_STATIC);

	do{
		result = sqlite3_step(stmt);
		if(result == SQLITE_ROW){
			//GUARDA EL DNI DEL USUARIO EN UNA VARIABLE
			strcpy(contrasenhaBD, (char*) sqlite3_column_text(stmt, 0));
		}
	} while(result == SQLITE_ROW);

	sqlite3_finalize(stmt);

	if (strcmp(contrasenha, contrasenhaBD) == 0)
	{
		menu(usuario);
	}else
	{
		printf("usuario o contrasenha incorrectos");
	}

	//CERRAR BASE DE DATOS
	sqlite3_close(db);
}
//FUNCION PARA REGISTRAR UN USUARIO NUEVO
void registrarUsuario(void)
{

	char nombre[40];
	char apellido[100];
	char dni[9];
	int telef;
	char email[100];
	int num_tarjeta;
	int genero;
	char fecha_nacimiento[10];
	char usuario[40];
	char contrasenha[60];
	int puntos = 0;

	system("cls");
	printf("\nREGISTRO DE SESIÓN\n=======================================");

	printf("Introducir Nombre: \n");
	scanf("%s", &nombre);
	printf("Introducir Apellido: \n");
	scanf("%s", &apellido);
	printf("Introducir DNI: \n");
	scanf("%s", &dni);
	printf("Introducir Telefono: \n");
	scanf("%i", &telef);
	printf("Introducir email: \n");
	scanf("%s", &email);
	printf("Introducir Nº Tarjeta: \n");
	scanf("%i", &num_tarjeta);
	printf("Introducir Género: Hombre - 1, Mujer - 2: \n");
	scanf("%i", &genero);
	printf("Introducir Fecha de  Nacimiento(XXXX-XX-XX): \n");
	scanf("%s", &fecha_nacimiento);
	printf("Introducir Usuario: \n");
	scanf("%s", &usuario);
	printf("Introducir Contraseña: \n");
	scanf("%s", &contrasenha);

	sqlite3 *db;
	sqlite3_stmt *stmt;
	int result;

	sqlite3_open("BaseDeDatos/UserDB.db", &db);

	//INSERTAR EL NUEVO USUARIO EN LA BASE DE DATOS
	char sql[] = "INSERT INTO usuario (DNI, Nombre, Apellido, Email, Telefono, User, Password, Genero, Fecha_ncto, N_TARJETA, PUNTOS) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
	
	sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
	sqlite3_bind_text(stmt, 1, dni, strlen(dni), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, nombre, strlen(nombre), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, apellido, strlen(apellido), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 4, email, strlen(email), SQLITE_STATIC);
	sqlite3_bind_int(stmt, 5, telef);
	sqlite3_bind_text(stmt, 6, usuario, strlen(usuario), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 7, contrasenha, strlen(contrasenha), SQLITE_STATIC);
	sqlite3_bind_int(stmt, 8, genero);
	sqlite3_bind_text(stmt, 9, fecha_nacimiento, strlen(fecha_nacimiento), SQLITE_STATIC);
	sqlite3_bind_int(stmt, 10, num_tarjeta);
	sqlite3_bind_int(stmt, 11, puntos);

	result = sqlite3_step(stmt);
	if(result != SQLITE_DONE){
		printf("\nError registrando al usuario\n");
	} else{
		printf("\nusuario registrado correctamente");
	}

	sqlite3_finalize(stmt);

	//CERRAR BASE DE DATOS
	sqlite3_close(db);
}
//FUNCION PARA CAMBIAR LA CONTRASEÑA DEL USUARIO
void contrasenyaOlvidada(void)
{
	char dni[9];
	char nuevaContrasenha[60];

	system("cls");
	printf("\nCONTRASEÑA OLVIDADA\n=======================================\n");

	printf("Introducir DNI: \n");
	scanf("%s", &dni);
	printf("Introducir Contraseña Nueva: \n");
	scanf("%s", &nuevaContrasenha);

	sqlite3 *db;
	sqlite3_stmt *stmt;
	int result;

	sqlite3_open("BaseDeDatos/UserDB.db", &db);

	char sql[] = "UPDATE usuario SET Password = ? WHERE DNI = ?";

	sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
	sqlite3_bind_text(stmt, 1, nuevaContrasenha, strlen(nuevaContrasenha), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, dni, strlen(dni), SQLITE_STATIC);

	result = sqlite3_step(stmt);
	if(result != SQLITE_DONE){
		printf("\nError al cambiar la contrasenha\n");
	} else{
		printf("\n¡Contraseña cambiada correctamente!\n");
	}
	sqlite3_finalize(stmt);
	
	//CERRAR BASE DE DATOS
	sqlite3_close(db);
}

//FUNCION PARA ELIMINAR USUARIO
void borrarUsuario(void)
{
	char usuario[40];
	char contrasenha[60];
	char respuesta[1];

	system("cls");
	printf("\nBORRAR USUARIO\n=======================================");

	printf("Introducir Usuario: \n");
	scanf("%s", &usuario);
	printf("Introducir Contraseña: \n");
	scanf("%s", &contrasenha);

	printf("¿Seguro que quieres eliminar el usuario? Y/N: \n");
	scanf("%s", &respuesta);

	if(strcmp(respuesta, "Y") == 0){
		sqlite3 *db;
		sqlite3_stmt *stmt;
		int result;

		sqlite3_open("BaseDeDatos/UserDB.db", &db);

		char sql[] = "DELETE FROM usuario WHERE User = ? AND Password = ?";
		
		sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
		sqlite3_bind_text(stmt, 1, usuario, strlen(usuario), SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, contrasenha, strlen(usuario), SQLITE_STATIC);

		result = sqlite3_step(stmt);
			if(result != SQLITE_DONE){
				printf("\nError al borrar el usuario\n");
			} else{
				printf("\nUsuario borrado correctamente");
			}

			sqlite3_finalize(stmt);

			//CERRAR BASE DE DATOS
			sqlite3_close(db);

	}else{
		datosUsuario(usuario);
	}


}
//FUNCION QUE MUESTRA EL MENU PRINCIPAL
void menu(char usuario[])
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
		alquilarPelicula(usuario); //de esta ventana irá a peliculas de dicho genero para luego gestionar el alquiler.
		break;
	case 2:
		extenderAlquiler(usuario);
		break;
	case 3:
		datosUsuario(usuario);
		break;
	case 4:
		datosAlquiler(usuario);
		break;
	case 5:

		break;
	default:
		break;
	}

}

//FUNCION PARA ALQUILAR PELICULA
void alquilarPelicula(char usuario[])
{
	system("cls");
	FILE *f = fopen("Peliculas.csv", "r");
	char linea[1000];
	char *pelicula;
	char *genero;
	char titulo[100];
	char **listaPelis;
	listaPelis = (char**)malloc(sizeof(char*)*20);

	int seleccion;
	int duracionAlquiler;
	int dias;
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
					//strcpy(listaPelis[numPelicula], pelicula);
					numPelicula++;
				}
				
			}

			
			printf("\nIntroduce el titulo de la pelicula: ");
			scanf("\n%s", &titulo);


			printf("\nALQUILER: %s\n=======================================", titulo);
			printf("\n3.Alquilar 3 días: 3 euros\n5.Alquilar 5 días: 4,5 euros\n7.Alquilar 7 días: 6 euros\n");
			printf("Cuantos dias quieres alquilar: ");
			scanf("\n%i", &duracionAlquiler);
			guardarAlquiler(usuario, titulo, duracionAlquiler);

			printf("\n¡Gracias por alquilar!\n");

			


			break;
			

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

			
			printf("\nIntroduce el titulo de la pelicula: ");
			scanf("\n%s", &titulo);

			printf("\nALQUILER: %s\n=======================================", titulo);
			printf("\n3.Alquilar 3 días: 3 euros\n5.Alquilar 5 días: 4,5 euros\n7.Alquilar 7 días: 6 euros\n");
			printf("Cuantos dias quieres alquilar: ");
			scanf("\n%i", &duracionAlquiler);
			guardarAlquiler(usuario, titulo, duracionAlquiler);

			printf("\n¡Gracias por alquilar!\n");
			break;

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

			
			printf("\nIntroduce el titulo de la pelicula: ");
			scanf("\n%s", &titulo);

			printf("\nALQUILER: %s\n=======================================", titulo);
			printf("\n3.Alquilar 3 días: 3 euros\n5.Alquilar 5 días: 4,5 euros\n7.Alquilar 7 días: 6 euros\n");
			printf("Cuantos dias quieres alquilar: ");
			scanf("\n%i", &duracionAlquiler);
			guardarAlquiler(usuario, titulo, duracionAlquiler);

			printf("\n¡Gracias por alquilar!\n");
			break;
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

			
			printf("\nIntroduce el titulo de la pelicula: ");
			scanf("\n%s", &titulo);
			
			printf("\nALQUILER: %s\n=======================================", titulo);
			printf("\n3.Alquilar 3 días: 3 euros\n5.Alquilar 5 días: 4,5 euros\n7.Alquilar 7 días: 6 euros\n");
			printf("Cuantos dias quieres alquilar: ");
			scanf("\n%i", &duracionAlquiler);
			guardarAlquiler(usuario, titulo, duracionAlquiler);

			printf("\n¡Gracias por alquilar!\n");
			break;

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

			
			printf("\nIntroduce el titulo de la pelicula: ");
			scanf("\n%s", &titulo);

			printf("\nALQUILER: %s\n=======================================", titulo);
			printf("\n3.Alquilar 3 días: 3 euros\n5.Alquilar 5 días: 4,5 euros\n7.Alquilar 7 días: 6 euros\n");
			printf("Cuantos dias quieres alquilar: ");
			scanf("\n%i", &duracionAlquiler);
			guardarAlquiler(usuario, titulo, duracionAlquiler);

			printf("\n¡Gracias por alquilar!\n");
			break;
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


			
			printf("\nIntroduce el titulo de la pelicula: ");
			scanf("\n%s", &titulo);

			printf("\nALQUILER: %s\n=======================================", titulo);
			printf("\n3.Alquilar 3 días: 3 euros\n5.Alquilar 5 días: 4,5 euros\n7.Alquilar 7 días: 6 euros\n");
			printf("Cuantos dias quieres alquilar: ");
			scanf("\n%i", &duracionAlquiler);
			guardarAlquiler(usuario, titulo, duracionAlquiler);

			printf("\n¡Gracias por alquilar!\n");

			break;
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


			
			printf("\nIntroduce el titulo de la pelicula: ");
			scanf("\n%s", &titulo);
			printf("\nALQUILER: %s\n=======================================", titulo);
			printf("\n3.Alquilar 3 días: 3 euros\n5.Alquilar 5 días: 4,5 euros\n7.Alquilar 7 días: 6 euros\n");
			printf("Cuantos dias quieres alquilar: ");
			scanf("\n%i", &duracionAlquiler);
			guardarAlquiler(usuario, titulo, duracionAlquiler);

			printf("\n¡Gracias por alquilar!\n");
			break;

	default: break;
	}
}
//FUNCION PARA GUARDAR EL ALQUILER EN LA BASE DE DATOS
void guardarAlquiler(char usuario[], char pelicula[], int duracion)
{
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int result;

	sqlite3_open("BaseDeDatos/UserDB.db", &db);

	// -- SELECT DNI DEL USUARIO --
	char sql[] = "SELECT DNI, PUNTOS FROM usuario WHERE user = ?";
	char dni[100];
	int puntos;
	
	sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
	sqlite3_bind_text(stmt, 1, usuario, strlen(usuario), SQLITE_STATIC);

	do{
		result = sqlite3_step(stmt);
		if(result == SQLITE_ROW){
			//GUARDA EL DNI DEL USUARIO EN UNA VARIABLE
			strcpy(dni, (char*) sqlite3_column_text(stmt,0));
			puntos = sqlite3_column_int(stmt, 1);
		}
	} while(result == SQLITE_ROW);

	sqlite3_finalize(stmt);

	// INSERTAR EL ALQUILER EN LA BASE DE DATOS
	char sql2[] = "INSERT INTO alquiler (TITULO_PELI, DURACION_ALQUILER, DNI) VALUES(?, ?, ?)";

	sqlite3_prepare_v2(db, sql2, strlen(sql2), &stmt, NULL);
	sqlite3_bind_text(stmt, 1, pelicula, strlen(pelicula), SQLITE_STATIC);
	sqlite3_bind_int(stmt, 2, duracion);
	sqlite3_bind_text(stmt, 3, dni, strlen(dni), SQLITE_STATIC);

	result = sqlite3_step(stmt);
	if(result != SQLITE_DONE){
		printf("\nError insertando el alquiler\n");
		printf("%s\n", sqlite3_errmsg(db));
	} else{
		printf("\nAlquiler de la pelicula '%s' durante %d dias al usuario '%s' con DNI: %s insertado correctamente\n", pelicula, duracion, usuario, dni);
	}

	sqlite3_finalize(stmt);

	char sql3[] = "UPDATE usuario SET PUNTOS = ? + ? WHERE DNI = ?";

	sqlite3_prepare_v2(db, sql3, strlen(sql3), &stmt, NULL);
	sqlite3_bind_int(stmt, 1, puntos);
	sqlite3_bind_int(stmt, 2, duracion);
	sqlite3_bind_text(stmt, 3, dni, strlen(dni), SQLITE_STATIC);

	result = sqlite3_step(stmt);
	if(result != SQLITE_DONE){
		printf("\nError actualizando los datos\n");
		printf("%s\n", sqlite3_errmsg(db));
	} else{
		printf("\n¡+%d puntos añadidos exitosamente!\n", duracion);
	}

	sqlite3_finalize(stmt);
	//CERRAR BASE DE DATOS
	sqlite3_close(db);
}

//FUNCION PARA MOSTRAR LOS DATOS DEL USUARIO
void datosUsuario(char usuario[])
{
	system("cls");
	int opcionDatosUsuario;
	printf("\n=======================================\nDATOS USUARIO\n=======================================\n\n");
	printf("\n¿Que quieres hacer?\n1.Editar informacion\n2.Eliminar Usuario\n3.Volver al Menu\n");
	printf("Introducir opcion: ");
	scanf("%i", &opcionDatosUsuario);

	switch (opcionDatosUsuario)
	{
	case 1:
		editarInfo(usuario);
		break;
	case 2:
		borrarUsuario();
		break;
	case 3:
		menu(usuario);
		break;
	default:
		break;
	}
}

//FUNCION PARA EDITAR INFORMACION
void editarInfo(char usuario[])
{
	char respuesta[1];

	system("cls");
	int opcion;
	printf("\n=======================================\nQUE DATOS QUIERES CAMBIAR\n=======================================\n\n");
	printf("1.Telefono\n2.Email\n3.Numero de tarjeta\n4.Volver atras\n");
	printf("Introducir opcion: ");
	fflush(stdin);
	scanf("%i", &opcion);

	sqlite3 *db;
	sqlite3_stmt *stmt;
	int result;
	int telef;
	char email[100];
	int num_tarjeta;

	sqlite3_open("BaseDeDatos/UserDB.db", &db);

	switch (opcion)
	{
	case 1:
		printf("Introduce el telefono nuevo: ");
		scanf("%i", &telef);

		char sql[] = "UPDATE usuario SET Telefono = ? WHERE User = ?";
		sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
		sqlite3_bind_int(stmt, 1, telef);
		sqlite3_bind_text(stmt, 2, usuario, strlen(usuario), SQLITE_STATIC);

		result = sqlite3_step(stmt);
			if(result != SQLITE_DONE){
				printf("\nError al cambiar el telefono\n");
			} else{
				printf("\n¡Telefono cambiado correctamente!\n");
			}
			sqlite3_finalize(stmt);
			
			//CERRAR BASE DE DATOS
			sqlite3_close(db);

		printf("¿Quieres volver atras? Y/N: \n");
			scanf("%s", &respuesta);

			if(strcmp(respuesta, "Y") == 0){
			datosUsuario(usuario);};
		break;
	
	case 2:
		printf("Introduce el email nuevo: ");
		scanf("%s", &email);

		char sql2[] = "UPDATE usuario SET Email = ? WHERE User = ?";
		sqlite3_prepare_v2(db, sql2, strlen(sql2), &stmt, NULL);
		sqlite3_bind_text(stmt, 1, email, strlen(email), SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, usuario, strlen(usuario), SQLITE_STATIC);

		result = sqlite3_step(stmt);
			if(result != SQLITE_DONE){
				printf("\nError al cambiar el email\n");
			} else{
				printf("\n¡Email cambiado correctamente!\n");
			}
			sqlite3_finalize(stmt);
			
			//CERRAR BASE DE DATOS
			sqlite3_close(db);

			printf("¿Quieres volver atras? Y/N: \n");
			scanf("%s", &respuesta);

			if(strcmp(respuesta, "Y") == 0){
			datosUsuario(usuario);};
		break;
	case 3:
		printf("Introduce el numero de tarjeta nuevo: ");
		scanf("%i", &num_tarjeta);

		char sql3[] = "UPDATE usuario SET N_TARJETA = ? WHERE User = ?";
		sqlite3_prepare_v2(db, sql3, strlen(sql3), &stmt, NULL);
		sqlite3_bind_int(stmt, 1, num_tarjeta);
		sqlite3_bind_text(stmt, 2, usuario, strlen(usuario), SQLITE_STATIC);

		result = sqlite3_step(stmt);
			if(result != SQLITE_DONE){
				printf("\nError al cambiar el numero de tarjeta\n");
			} else{
				printf("\n¡Numero de tarjeta cambiado correctamente!\n");
			}
			sqlite3_finalize(stmt);
			
			//CERRAR BASE DE DATOS
			sqlite3_close(db);

			printf("¿Quieres volver atras? Y/N: \n");
			scanf("%s", &respuesta);

			if(strcmp(respuesta, "Y") == 0){
			datosUsuario(usuario);};
		break;
	case 4:
		//CERRAR BASE DE DATOS
		sqlite3_close(db);
		
		datosUsuario(usuario);
		break;
	default:
		printf("Opcion no valida\n");
		break;
	}


}

//FUNCION PARA MOSTRAR LOS DATOS DEL ALQUILER
void datosAlquiler(char usuario[])
{
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int result;

	sqlite3_open("BaseDeDatos/UserDB.db", &db);

	//-- SELECT DNI DEL USUARIO
	char sql[] = "SELECT DNI FROM usuario WHERE user = ?";
	char dni[100];

	sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
	sqlite3_bind_text(stmt, 1, usuario,strlen(usuario), SQLITE_STATIC);

	do{
		result = sqlite3_step(stmt);
		if(result == SQLITE_ROW){
			//GUARDA LE DNI DEL USUARIO EN UNA VARIABLE
			strcpy(dni, (char*) sqlite3_column_text(stmt,0));
		}
	} while(result == SQLITE_ROW);

	sqlite3_finalize(stmt);

	// -- SELECT DE LOS ALQUILERES DEL USUARIO
	char sql2[] = "SELECT * FROM ALQUILER WHERE DNI = ?";
	
	sqlite3_prepare_v2(db, sql2, strlen(sql2), &stmt, NULL);
	sqlite3_bind_text(stmt, 1, dni, strlen(dni), SQLITE_STATIC);

	do{
		int i;
		result = sqlite3_step(stmt);
		if(result == SQLITE_ROW){

			printf("CODIGO: %d   TITULO: %s   DURACION: %d\n", sqlite3_column_int(stmt, 0), (char *)sqlite3_column_text(stmt,1), sqlite3_column_int(stmt, 2));

		}

	} while(result == SQLITE_ROW);

	sqlite3_finalize(stmt);

	// --SELECT DEL ALQUILER SEGUN EL CODIGO
	int codigo;
	printf("Introduce el CODIGO DEL ALQUILER: ");
	scanf("\n%i", &codigo);

	char sql3[] = "SELECT TITULO_PELI, DURACION_ALQUILER FROM alquiler WHERE ID_ALQUILER = ?";
	sqlite3_prepare_v2(db, sql3, strlen(sql3), &stmt, NULL);
	sqlite3_bind_int(stmt,1,codigo);

	do{
		result = sqlite3_step(stmt);
		if(result == SQLITE_ROW){
			printf("%s\n=======================================\n", (char *)sqlite3_column_text(stmt,0));
			printf("Duracion del alquiler: %d dias\nPuntos Obtenidos con el alquiler: %i", sqlite3_column_int(stmt, 1), sqlite3_column_int(stmt, 1));
		}
	} while (result == SQLITE_ROW);

	sqlite3_finalize(stmt);
	sqlite3_close(db);
}


void extenderAlquiler(char usuario[])
{
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int result;
	int extension;
	int duracion;
	int puntos;

	sqlite3_open("BaseDeDatos/UserDB.db", &db);

	// -- SELECT DNI DEL USUARIO
	char sql[] = "SELECT DNI, PUNTOS FROM usuario WHERE user = ?";
	char dni[100];

	sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
	sqlite3_bind_text(stmt, 1, usuario,strlen(usuario), SQLITE_STATIC);

	do{
		result = sqlite3_step(stmt);
		if(result == SQLITE_ROW){
			//GUARDA LE DNI DEL USUARIO EN UNA VARIABLE
			strcpy(dni, (char*) sqlite3_column_text(stmt,0));
			puntos = sqlite3_column_int(stmt, 1);
		}
	} while(result == SQLITE_ROW);

	sqlite3_finalize(stmt);

	// -- SELECT DE LOS ALQUILERES DEL USUARIO
	char sql2[] = "SELECT * FROM ALQUILER WHERE DNI = ?";
	
	sqlite3_prepare_v2(db, sql2, strlen(sql2), &stmt, NULL);
	sqlite3_bind_text(stmt, 1, dni, strlen(dni), SQLITE_STATIC);

	do{
		int i;
		result = sqlite3_step(stmt);
		if(result == SQLITE_ROW){

			printf("CODIGO: %d   TITULO: %s   DURACION: %d\n", sqlite3_column_int(stmt, 0), (char *)sqlite3_column_text(stmt,1), sqlite3_column_int(stmt, 2));

		}

	} while(result == SQLITE_ROW);

	sqlite3_finalize(stmt);

	// --SELECT DEL ALQUILER SEGUN EL CODIGO
	int codigo;
	printf("Introduce el CODIGO DEL ALQUILER: ");
	scanf("\n%i", &codigo);

	char sql3[] = "SELECT TITULO_PELI, DURACION_ALQUILER FROM alquiler WHERE ID_ALQUILER = ?";
	sqlite3_prepare_v2(db, sql3, strlen(sql3), &stmt, NULL);
	sqlite3_bind_int(stmt,1,codigo);

	do{
		result = sqlite3_step(stmt);
		if(result == SQLITE_ROW){
			printf("\nALQUILER: %s\n=======================================", (char*) sqlite3_column_text(stmt,0));
			printf("\n3.Extender 3 días: 3 euros\n5.Extender 5 días: 4,5 euros\n7.Extender 7 días: 6 euros\n");
			duracion = sqlite3_column_int(stmt,1);
		}
	} while (result == SQLITE_ROW);

	printf("Cuantos dias quieres extender: ");
	scanf("\n%i", &extension);
	sqlite3_finalize(stmt);

	char sql4[] = "UPDATE alquiler SET DURACION_ALQUILER = ? + ? WHERE DNI = ? AND ID_ALQUILER = ?";
	
	sqlite3_prepare_v2(db, sql4, strlen(sql4), &stmt, NULL);
	sqlite3_bind_int(stmt,1,duracion);
	sqlite3_bind_int(stmt,2,extension);
	sqlite3_bind_text(stmt, 3, dni, strlen(dni), SQLITE_STATIC);
	sqlite3_bind_int(stmt,4,codigo);

	result = sqlite3_step(stmt);
	if(result != SQLITE_DONE){
		printf("\nError actualizando los datos\n");
		printf("%s\n", sqlite3_errmsg(db));
	} else{
		printf("\nAlquiler extendido %i dias con exito\n", extension);
	}
	
	sqlite3_finalize(stmt);

	char sql5[] = "UPDATE usuario SET PUNTOS = ? + ? WHERE DNI = ?";

	sqlite3_prepare_v2(db, sql5, strlen(sql5), &stmt, NULL);
	sqlite3_bind_int(stmt, 1, puntos);
	sqlite3_bind_int(stmt, 2, extension);
	sqlite3_bind_int(stmt, 3, extension);
	sqlite3_bind_text(stmt, 4, dni, strlen(dni), SQLITE_STATIC);

	result = sqlite3_step(stmt);
	if(result != SQLITE_DONE){
		printf("\nError actualizando los datos\n");
		printf("%s\n", sqlite3_errmsg(db));
	} else{
		printf("\n%i puntos añadidos\n", extension);
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
}