/*
 * ControladorLogger.cpp
 *
 *  Created on: 26 mar. 2019
 *      Author: lucas
 */

#include <controler/ControladorLogger.hpp>
#include <iostream>
#include <fstream>

bool ControladorLogger::registrarEvento(){
	//Supongo que evento tiene un mensaje, una fecha, y el nivel de debug

	std::ofstream file;
	try{
		file.open("source/config/log.txt"); //Verificar la ruta
		file << "prueba" << std::endl; //Añado el mensaje con la fecha, si el nivel de debug es correcto.
		file.close();
		return true;
	}
	catch (int e){
		//No se puede abrir el archivo log.txt
		//Es bastante grave
		//Crear otro archivo
		return false;
	}
}


