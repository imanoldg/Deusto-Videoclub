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
	char usuario[10];
	char password[10];

	printf("\n=======================================\nINICIO DE SESION\n=======================================\n\n");

	printf("Introducir Usuario: ");
	scanf("%s", usuario);

	printf("Introducir Contraseña: ");
	scanf("%s", password);

	if ((strcmp(usuario, "pomodoro") == 0) && (strcmp(password, "liso") == 0))
	{
		menu(usuario);
	}else
	{
		printf("usuario o contraseña incorrectos");
	}
}
//FUNCION PARA REGISTRAR UN USUARIO NUEVO
void registrarUsuario(void)
{

	char nombre[40];
	char apellido[60];
	char dni[9];
	int telef[9];
	char email[100];
	int num_tarjeta[16];
	char genero[1];
	char fecha_nacimiento[10];
	char usuario[40];
	char contraseña[60];
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
	printf("Introducir Género(H/M): \n");
	scanf("%s", &genero);
	printf("Introducir Fecha de  Nacimiento(XXXX-XX-XX): \n");
	scanf("%s", &fecha_nacimiento);
	printf("Introducir Usuario: \n");
	scanf("%s", &usuario);
	printf("Introducir Contraseña: \n");
	scanf("%s", &contraseña);

	sqlite3 *db;
	sqlite3_stmt *stmt;
	int result;

	sqlite3_open("BaseDeDatos/UserDB.db", &db);

	//COMPROBAR QUE EL DNI DADO NO ESTA EN LA BASE DE DATOS
	char sqlPrueba[] = "SELECT DNI FROM usuario WHERE DNI = ?";
	sqlite3_prepare_v2(db, sqlPrueba, strlen(sqlPrueba), &stmt, NULL);
	sqlite3_bind_text(stmt, 1, dni, strlen(dni), SQLITE_STATIC);

	result = sqlite3_step(stmt);
	if(result == SQLITE_DONE){
		printf("\nError, ya hay un usuario registrado con ese DNI\n");
	} 
	sqlite3_finalize(stmt);

	//INSERTAR EL NUEVO USUARIO EN LA BASE DE DATOS
	char sql[] = "INSERT INTO usuario (DNI, Nombre, Apellido, Email, Telefono, User, Password, Genero, Fecha_ncto, N_TARJETA, PUNTOS) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
	
	sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
	sqlite3_bind_text(stmt, 1, dni, strlen(dni), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, nombre, strlen(nombre), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, apellido, strlen(apellido), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 4, email, strlen(email), SQLITE_STATIC);
	sqlite3_bind_int(stmt, 5, telef);
	sqlite3_bind_text(stmt, 6, usuario, strlen(usuario), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 7, contraseña, strlen(contraseña), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 8, genero, strlen(genero), SQLITE_STATIC);
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
}
//FUNCION PARA CAMBIAR LA CONTRASEÑA DEL USUARIO
void contrasenyaOlvidada(void)
{
	system("cls");
	printf("\nCONTRASEÑA OLVIDADA\n=======================================\n");

	printf("Introducir DNI: \n");
	printf("Introducir Contraseña Nueva: \n");
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
		menu(usuario);
		break;
	default:
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