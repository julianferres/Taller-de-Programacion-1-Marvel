#include <controler/ControladorJson.hpp>
#include <fstream>


void ControladorJson::leerArchivo(){
	using json = nlohmann::json;

	std::ifstream ifs ("source/config/config.json", std::ifstream::in);
	json j = json::parse(ifs);

	nivel_debug = j["debug"];
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
