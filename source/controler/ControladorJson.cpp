#include <controler/ControladorJson.hpp>
#include <controler/ControladorLogger.hpp>
#include <fstream>
#include <iostream>

extern ControladorLogger *controladorLogger;

void ControladorJson::leerArchivo(){


	using json = nlohmann::json;
	std::ifstream ifs (configPath, std::ifstream::in); //cambia el nombre y mira el log.txt

	try{
		json j = json::parse(ifs);
		nivel_debug = j["debug"];
		controladorLogger->setNivelDebug(nivel_debug);
		altura_ventana = j["window"]["height"];
		ancho_ventana = j["window"]["width"];
		fullscreen = j["window"]["fullscreen"];
		FPS = j["FPS"];
		cantidad_personajes = j["characters"].size();
		cantidad_fondos = j["battlefield"].size();

		for (int i = 0; i < cantidad_personajes; i++){
			personajes.push_back(std::make_tuple(j["characters"][i]["name"],j["characters"][i]["filepath"],j["characters"][i]["height"],j["characters"][i]["width"],j["characters"][i]["zindex"]));
		}

		for (int i = 0; i < cantidad_fondos; i++){
			fondos.push_back(std::make_tuple(j["battlefield"][i]["background"]["filepath"] , j["battlefield"][i]["background"]["zindex"] ));
		}
		controladorLogger->registrarEvento("INFO","Archivo de configuracion JSON leido correctamente",controladorLogger->obtenerHora());

	}

	catch(json::exception &e){
		controladorLogger->registrarEvento("ERROR",e.what(),controladorLogger->obtenerHora());
	}
}


int ControladorJson::alturaVentana(){
	return altura_ventana;
}

int ControladorJson::anchoVentana(){
	return ancho_ventana;
}

int ControladorJson::cantidadFPS(){
	return FPS;
}

bool ControladorJson::esfullscreen(){
	return fullscreen;
}

std::string ControladorJson::nivelDebug(){
	return nivel_debug;
}

std::string ControladorJson::pathImagen(int zindex){
    for (int i = 0; i < cantidad_fondos; i++){
            if(std::get<1>(fondos[i]) == zindex)
                return std::get<0>(fondos[i]);
        }
    controladorLogger->registrarEvento("ERROR","No se pudo encontrar imagen con zindex igual a "+ std::to_string(zindex),controladorLogger->obtenerHora());
    return NULL;
}
