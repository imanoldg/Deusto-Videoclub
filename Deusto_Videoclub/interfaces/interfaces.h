/*
 * interfaces.h
 *
 *  Created on: 13 mar 2024
 *      Author: ima.dominguez
 */

#ifndef INTERFACES_INTERFACES_H_
#define INTERFACES_INTERFACES_H_

void inicio(void);
void iniciarSesion(void);
void registrarUsuario(void);
void contrasenyaOlvidada(void);
void menu(char usuario[]);
void genero(void);
void datosUsuario(char usuario[]);
void alquilarPelicula(char usuario[]);
void guardarAlquiler(char usuario[], char pelicula[], int duracion);

#endif /* INTERFACES_INTERFACES_H_ */
