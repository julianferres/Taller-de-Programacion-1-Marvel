#include <controler/ControladorJson.hpp>
#include "controler/json.hpp"
#include <fstream>
#include <iostream>

void ControladorJson::LeerArchivo(){
		using json = nlohmann::json;

		std::ifstream ifs ("source/config/config.json", std::ifstream::in);
		json j = json::parse(ifs);
		std::cout <<  "Tipo de debug: "<< j["debug"] << std::endl;
		std::cout <<  "Altura ventana "<< j["window"]["height"] << std::endl;

}
