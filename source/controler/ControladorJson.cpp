#include <controler/ControladorJson.hpp>
#include <controler/ControladorLogger.hpp>
#include <fstream>

extern ControladorLogger *controladorLogger;

void ControladorJson::leerArchivo(){

	using json = nlohmann::json;
	std::ifstream ifs (configPath, std::ifstream::in); //cambia el nombre y mira el log.txt

	try{
		json j = json::parse(ifs);

		this -> setLogLevel(j);
		controladorLogger->setNivelDebug(nivel_debug);
		this -> setAlturaVentana(j);
		this -> setAnchoVentana(j);
		this -> setPantallaCompleta(j);
		this -> setFPS(j);
		this -> setCantidadPersonajes(j);
		this -> setCantidadFondos(j);
		this -> setPersonajes(j);
		this -> setFondos(j);
		//this->setMenuImage(j);
		controladorLogger->registrarEvento("INFO","ControladorJson::Archivo de configuracion JSON leido correctamente");
	}


	catch(json::exception &error){
		//No se puede abrir el json. Cargar uno nuevo por default
		controladorLogger->registrarEvento("ERROR",error.what());
		this->leerArchivoDefault();
	}

}

void ControladorJson::leerArchivoDefault(){

	using json = nlohmann::json;

	std::ifstream ifs (configPathDefault, std::ifstream::in);
	json j = json::parse(ifs);
	nivel_debug = j["logLevel"];
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

	controladorLogger->registrarEvento("INFO","ControladorJson::Archivo default de configuracion JSON leido correctamente");
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
int ControladorJson::cantidadFondos(){
	return cantidad_fondos;
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
    controladorLogger->registrarEvento("ERROR","ControladorJson::No se pudo encontrar imagen con zindex igual a "+ std::to_string(zindex));
    return NULL;
}

std::string ControladorJson::pathImagen(std::string nombrePersonaje){
    for (int i = 0; i < cantidad_personajes; i++){
            if(std::get<0>(personajes[i]).compare(nombrePersonaje) == 0){
            	controladorLogger->registrarEvento("INFO","ControladorJson::Se cargo correctamente la imagen del personaje"+ nombrePersonaje);
            	return std::get<1>(personajes[i]);
            }
        }
    controladorLogger->registrarEvento("ERROR","ControladorJson::No se pudo encontrar la imagen del personaje "+ nombrePersonaje);
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

void ControladorJson::setLogLevel(json j)throw(){
	try{
		nivel_debug = j["logLevel"];
		if (nivel_debug.compare("ERROR") != 0 && nivel_debug.compare("INFO") != 0 && nivel_debug.compare("DEBUG") != 0 ){
			controladorLogger->registrarEvento("ERROR","ControladorJson::Nivel de Debug no corresponde a ERROR, INFO o DEBUG. Se setea en " + nivel_debug_default);
			nivel_debug = nivel_debug_default;
		}
	}
	catch(json::type_error &e){
		controladorLogger->registrarEvento("ERROR","ControladorJson::Nivel de Debug no corresponde a ERROR, INFO o DEBUG. Se setea en " + nivel_debug_default);
		nivel_debug = nivel_debug_default;
	}


}

void ControladorJson::setAlturaVentana(json j)throw(){
	try{
		altura_ventana = j["window"]["height"];
		if (altura_ventana < rango_altura_ventana[0] || altura_ventana > rango_altura_ventana[1]){
			controladorLogger->registrarEvento("ERROR","ControladorJson::Altura de la ventana no permitida. Se setea en " + std::to_string(altura_ventana_default));
			altura_ventana = altura_ventana_default;
		}
	}
	catch(json::type_error &e){
		controladorLogger->registrarEvento("ERROR","ControladorJson::Altura de la ventana no permitida. Se setea en " + std::to_string(altura_ventana_default));
		altura_ventana = altura_ventana_default;
	}
}

void ControladorJson::setAnchoVentana(json j)throw(){
	try{
		ancho_ventana = j["window"]["width"];
		if (ancho_ventana < rango_ancho_ventana[0] || ancho_ventana > rango_ancho_ventana[1]){
			controladorLogger->registrarEvento("ERROR","ControladorJson::Ancho de la ventana no permitido. Se setea en " + std::to_string(ancho_ventana_default));
			ancho_ventana = ancho_ventana_default;
		}
	}
	catch(json::type_error &e){
		controladorLogger->registrarEvento("ERROR","ControladorJson::Ancho de la ventana no permitido. Se setea en " + std::to_string(ancho_ventana_default));
		ancho_ventana = ancho_ventana_default;
	}
}

void ControladorJson::setPantallaCompleta(json j)throw(){
	try{
		fullscreen = j["window"]["fullscreen"];
	}
	catch(json::type_error &e){
		controladorLogger->registrarEvento("ERROR","ControladorJson::Valor no permitido para fullscreen.");
		fullscreen = fullscreen_default;
	}
}

void ControladorJson::setFPS(json j)throw(){
	try{
		FPS = j["FPS"];
		if (FPS < rango_FPS[0] || FPS > rango_FPS[1]){
			controladorLogger->registrarEvento("ERROR","ControladorJson::Cantidad de FPS no permitido. Se setea en " + std::to_string(FPS_default));
			FPS = FPS_default;
		}
	}
	catch(json::type_error &e){
		controladorLogger->registrarEvento("ERROR","ControladorJson::Cantidad de FPS no permitido. Se setea en " + std::to_string(FPS_default));
		FPS = FPS_default;
	}
}

void ControladorJson::setCantidadPersonajes(json j)throw(){
	try{
		cantidad_personajes = j["characters"].size();
	}
	catch(json::type_error &e){
		cantidad_personajes = cantidad_personajes_default;
		controladorLogger->registrarEvento("ERROR","ControladorJson::Cantidad de personajes invalida. Se setea en: " + std::to_string(cantidad_personajes_default));

	}

}

void ControladorJson::setCantidadFondos(json j)throw(){
	try{
		cantidad_fondos = j["battlefield"].size();
	}
	catch(json::type_error &e){
		cantidad_fondos = cantidad_fondos_default;
		controladorLogger->registrarEvento("ERROR","ControladorJson::Cantidad de fondos invalida. Se setea en: " + std::to_string(cantidad_fondos_default));
	}

}

void ControladorJson::setFondos(json j)throw(){
	try{
		for (int i = 0; i < cantidad_fondos; i++){
			std::string filepath_fondo = j["battlefield"][i]["background"]["filepath"];
			int zindex_fondo = j["battlefield"][i]["background"]["zindex"];

			std::ifstream file(filepath_fondo.c_str());
			if (file.good() == false){
				//Cargar imagen con zindex correspondiente
				controladorLogger->registrarEvento("ERROR","ControladorJson::Imagen de fondo no encontrada. Se carga una por defecto");
				filepath_fondo = "contents/auxiliar/capa" + std::to_string(zindex_fondo) + ".png";
			}
			fondos.push_back(std::make_tuple(filepath_fondo , zindex_fondo));
		}
	}
	catch(json::type_error &e){
		fondos.clear();
		for (int i = 0; i < cantidad_fondos; i++){
			int zindex_fondo = 3 - i;
			std::string filepath_fondo = "contents/auxiliar/capa" + std::to_string(zindex_fondo) + ".png";

			//Cargar imagen con zindex correspondiente
			controladorLogger->registrarEvento("ERROR","ControladorJson::Imagen de fondo no encontrada. Se carga una por defecto");
			fondos.push_back(std::make_tuple(filepath_fondo , zindex_fondo));
		}
	}
}

void ControladorJson::setPersonajes(json j)throw(){
	for (int i = 0; i < cantidad_personajes; i++){
		std::string nombre_personaje = j["characters"][i]["name"];
		std::string filepath_personaje = j["characters"][i]["filepath"];
		int height_personaje = j["characters"][i]["height"];
		int width_personaje = j["characters"][i]["width"];
		int zindex_personaje = j["characters"][i]["zindex"];

		std::ifstream file(filepath_personaje.c_str());
		if (file.good() == false){
			//Cargar imagen con zindex correspondiente
			controladorLogger->registrarEvento("ERROR","ControladorJson::Imagen de personaje no encontrada. Se carga una por defecto");
			filepath_personaje = filepath_personaje_default;
		}

		personajes.push_back(std::make_tuple(nombre_personaje,filepath_personaje,height_personaje,width_personaje,zindex_personaje));
	}

}



