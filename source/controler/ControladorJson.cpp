#include <controler/ControladorJson.hpp>
#include <controler/ControladorLogger.hpp>
#include <fstream>

extern ControladorLogger *controladorLogger;

void ControladorJson::leerArchivo(){


	std::ifstream ifs (configPath, std::ifstream::in); //cambia el nombre y mira el log.txt

	try{
		json j = json::parse(ifs);
		this->setLogLevel(j);
		controladorLogger->setNivelDebug(nivel_debug);
		this->setAlturaVentana(j);
		this->setAnchoVentana(j);
		this->setPantallaCompleta(j);
		this->setFPS(j);
		this->setCantidadPersonajes(j);
		this->setCantidadFondos(j);

		for (int i = 0; i < cantidad_personajes; i++){
			personajes.push_back(std::make_tuple(j["characters"][i]["name"],j["characters"][i]["filepath"],j["characters"][i]["height"],j["characters"][i]["width"],j["characters"][i]["zindex"]));
		}

		for (int i = 0; i < cantidad_fondos; i++){
			fondos.push_back(std::make_tuple(j["battlefield"][i]["background"]["filepath"] , j["battlefield"][i]["background"]["zindex"] ));
		}

		controladorLogger->registrarEvento("INFO","Archivo de configuracion JSON leido correctamente");
	}

	catch(json::exception &e){
		controladorLogger->registrarEvento("ERROR",e.what());
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

std::string ControladorJson::pathFondo(int zindex){
    for (int i = 0; i < cantidad_fondos; i++){
            if(std::get<1>(fondos[i]) == zindex)
                return std::get<0>(fondos[i]);
        }
    controladorLogger->registrarEvento("ERROR","No se pudo encontrar imagen con zindex igual a "+ std::to_string(zindex));
    return NULL;
}

std::string ControladorJson::pathImagen(std::string nombrePersonaje){
    for (int i = 0; i < cantidad_personajes; i++){
            if(std::get<0>(personajes[i]).compare(nombrePersonaje) == 0){
            	controladorLogger->registrarEvento("INFO","Se cargo correctamente la imagen del personaje"+ nombrePersonaje);
            	return std::get<1>(personajes[i]);
            }
        }
    controladorLogger->registrarEvento("ERROR","No se pudo encontrar la imagen del personaje "+ nombrePersonaje);
    return NULL;
}

int ControladorJson::alturaPersonaje(std::string nombrePersonaje){
    for (int i = 0; i < cantidad_personajes; i++){
            if(std::get<0>(personajes[i]).compare(nombrePersonaje) == 0)
                return std::get<2>(personajes[i]);
        }
    return -1;
}

int ControladorJson::anchoPersonaje(std::string nombrePersonaje){
    for (int i = 0; i < cantidad_personajes; i++){
            if(std::get<0>(personajes[i]).compare(nombrePersonaje) == 0)
                return std::get<3>(personajes[i]);
        }
    return -1;
}


void ControladorJson::setLogLevel(json j){
	try{
		nivel_debug = j["logLevel"];
	}
	catch(json::exception &e){
		nivel_debug = "ERROR";
		controladorLogger->registrarEvento("ERROR","ControladorJson:: No se pudo encontrar el nivel de logg, seteado a ERROR");
	}
}

void ControladorJson::setAlturaVentana(json j){
	try{
		altura_ventana = j["window"]["height"];
	}
	catch(json::exception &e){
		altura_ventana = 800;
		controladorLogger->registrarEvento("ERROR","ControladorJson:: No se pudo encontrar la alura de la ventana, seteado a 800");
	}
}

void ControladorJson::setAnchoVentana(json j){
	try{
		ancho_ventana = j["window"]["width"];
	}
	catch(json::exception &e){
		ancho_ventana = 1400;
		controladorLogger->registrarEvento("ERROR","ControladorJson:: No se pudo encontrar el ancho de la ventana, seteado a 1400");
	}
}

void ControladorJson::setPantallaCompleta(json j){
	try{
		fullscreen = j["window"]["fullscreen"];
	}
	catch(json::exception &e){
		fullscreen = false;
		controladorLogger->registrarEvento("ERROR","ControladorJson:: No se pudo encontrar modo pantalla completa. False por default");
	}
}

void ControladorJson::setFPS(json j){
	try{
		FPS = j["FPS"];
	}
	catch(json::exception &e){
		FPS = 60;
		controladorLogger->registrarEvento("ERROR","ControladorJson:: No se pudo encontrar fps. Seteado a 60 por default.");
	}
}

void ControladorJson::setCantidadPersonajes(json j){
	try{
		cantidad_personajes = j["characters"].size();
	}
	catch(json::exception &e){
		cantidad_personajes = 4;
		controladorLogger->registrarEvento("ERROR","ControladorJson:: No se pudo encontrar los personajes. Cantidad seteada a 4");
	}
}

void ControladorJson::setCantidadFondos(json j){
	try{
		cantidad_fondos = j["battlefield"].size();
	}
	catch(json::exception &e){
		cantidad_fondos = 1;
		controladorLogger->registrarEvento("ERROR","ControladorJson:: No se pudo encontrar los fondos. Cantidad seteada a 1");
	}
}




