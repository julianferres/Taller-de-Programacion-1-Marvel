#include <controler/ControladorJson.hpp>
#include <controler/ControladorLogger.hpp>
#include <fstream>
#include <string>
#include<stdio.h>

extern ControladorLogger *controladorLogger;
using namespace std;

void ControladorJson::leerArchivo(std::string argumentoConsola){

	using json = nlohmann::json;
	std::ifstream ifs (configPath, std::ifstream::in);

	try{
		json j = json::parse(ifs);

		this -> setLogLevel(j,argumentoConsola);
		this -> setAlturaVentana(j);
		this -> setAnchoVentana(j);
		this -> setPantallaCompleta(j);
		this -> setFPS(j);
		this -> setCantidadClientes(j);
		this -> setCantidadPersonajes(j);
		this -> setCantidadRounds(j);
		this -> setCantidadFondos(j);
		//this -> setCantidadJugadores(j);
		this -> setPersonajes(j);
		this -> setRounds(j);

		controladorLogger->registrarEvento("INFO","ControladorJson::Archivo de configuracion JSON leido correctamente");
	}

	catch(json::exception &error){
		controladorLogger->registrarEvento("ERROR",error.what());
		controladorLogger->registrarEvento("ERROR","ControladorJson:: Se leera el archivo default");
		this->leerArchivoDefault();
	}
}

void ControladorJson::leerArchivoDefault(){
	//TODO ARREGLAR ARCHIVO DEFAULT
	using json = nlohmann::json;
	vector<tuple<string, int>> fondos;
	std::ifstream ifs (configPathDefault, std::ifstream::in);
	json j = json::parse(ifs);
	nivel_debug = j["logLevel"];
	this -> setAlturaVentana(j);
	this -> setAnchoVentana(j);
	this -> setPantallaCompleta(j);
	this -> setFPS(j);
	this -> setCantidadClientes(j);
	this -> setCantidadPersonajes(j);
	this -> setCantidadRounds(j);
	this -> setCantidadFondos(j);
	//this -> setCantidadJugadores(j);
	this -> setPersonajes(j);
	this -> setRounds(j);
	/*
	nivel_debug = j["logLevel"];
	controladorLogger->setNivelDebug(nivel_debug);
	altura_ventana = j["window"]["height"];
	ancho_ventana = j["window"]["width"];
	fullscreen = j["window"]["fullscreen"];
	FPS = j["FPS"];
	cantidad_jugadores = j["jugadores"].size();
	cantidad_personajes = j["characters"].size();
	cantidad_fondos[0] = 3;

	for (int i = 0; i < cantidad_personajes; i++){
		tuplaPersonaje personaje = tuplaPersonaje(j["characters"][i]["name"],j["characters"][i]["filepath"],j["characters"][i]["height"],j["characters"][i]["width"],j["characters"][i]["zindex"], j["characters"][i]["buttonpath"]);
		personajes.push_back(personaje);
	}

	for (int i = 0; i < cantidad_fondos[0]; i++){
		//TODO ARREGLAR ARCHIVO DEFAULT
		std::tuple<std::string, int> fondo(j["battlefield"][i]["background"]["filepath"] , j["battlefield"][i]["background"]["zindex"] );
		fondos.push_back(fondo);
	}

	personajesJugador1.push_back(j["jugadores"][0]["jugador"]["personaje1"]);
	personajesJugador1.push_back(j["jugadores"][0]["jugador"]["personaje2"]);
	personajesJugador2.push_back(j["jugadores"][1]["jugador"]["personaje1"]);
	personajesJugador2.push_back(j["jugadores"][1]["jugador"]["personaje2"]);
	*/
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

int ControladorJson::cantidadFondos(int round){
	return cantidad_fondos[round];
}

bool ControladorJson::esfullscreen(){
	return fullscreen;
}

string ControladorJson::nivelDebug(){
	return nivel_debug;
}

vector<int>ControladorJson::getZindexes(int round){
	for(int i=0;i<escenarios[round-1].size();i++){
		zindexes.push_back(std::get<1>(escenarios[round-1][i]));
	}
	return zindexes;
}

vector<string>ControladorJson::getNombresPersonajes(){
	return nombresPersonajes;
}

string ControladorJson::pathFondo(int zindex, int round){
    for (int i = 0; i < cantidad_fondos[round-1]; i++){
		if(std::get<1>(escenarios[round-1][i]) == zindex)
			return std::get<0>(escenarios[round-1][i]);
        }
    return "";
}

string ControladorJson::pathImagen(string nombrePersonaje){
    for (int i = 0; i < cantidad_personajes; i++){
            if(std::get<0>(personajes[i]).compare(nombrePersonaje) == 0){
            	return std::get<1>(personajes[i]);
            }
        }
    return "";
}

string ControladorJson::nombrePersonajeI(int i){
	return std::get<0>(personajes[i]);
}


string ControladorJson::pathBoton(string nombrePersonaje){
	for (int i = 0; i < cantidad_personajes; i++){
		if(std::get<0>(personajes[i]).compare(nombrePersonaje) == 0){
			return std::get<5>(personajes[i]);
		}
	}
	return "";
}

bool ControladorJson::existePersonaje(string nombrePersonaje){
	for (int i = 0; i < cantidad_personajes; i++){
		if(std::get<0>(personajes[i]).compare(nombrePersonaje) == 0){
			controladorLogger->registrarEvento("DEBUG","ControladorJson::Personaje encontrado: "+ nombrePersonaje);
			return true;
		}
	}
	controladorLogger->registrarEvento("ERROR","ControladorJson::No se encontro el personaje: "+ nombrePersonaje);
	return false;

}

int ControladorJson::alturaPersonaje(string nombrePersonaje){
    for (int i = 0; i < cantidad_personajes; i++){
		if(std::get<0>(personajes[i]).compare(nombrePersonaje) == 0){
			int altura = std::get<2>(personajes[i]);
			if(altura < rango_altura_personaje[0] || altura > rango_altura_personaje[1]){
				controladorLogger->registrarEvento("ERROR","Altura del personaje "+ nombrePersonaje + " no permitida. Se setea en " + std::to_string(altura_personaje_default));
				altura = altura_personaje_default;
			}
			return altura;
		}
	}
    return -1;
}

int ControladorJson::anchoPersonaje(string nombrePersonaje){
    for (int i = 0; i < cantidad_personajes; i++){
		if(std::get<0>(personajes[i]).compare(nombrePersonaje) == 0){
			int ancho = std::get<3>(personajes[i]);
			if(ancho < rango_ancho_personaje[0] || ancho > rango_ancho_personaje[1]){
				controladorLogger->registrarEvento("ERROR","Ancho del personaje "+ nombrePersonaje + " no permitida. Se setea en " + std::to_string(ancho_personaje_default));
				ancho = ancho_personaje_default;
			}
			return ancho;
		}
    }
    return -1;
}



int ControladorJson::zindexPersonaje(string nombrePersonaje){
    for (int i = 0; i < cantidad_personajes; i++){
		if(std::get<0>(personajes[i]).compare(nombrePersonaje) == 0){
			int zindex_personaje = std::get<4>(personajes[i]);
			if(zindex_personaje < 0 or zindex_personaje > 99){
				controladorLogger->registrarEvento("Error", "zindex del personaje "+ nombrePersonaje + " no permitido. Se setea en " + std::to_string(zindex_personaje_default));
				zindex_personaje = zindex_personaje_default;
			}
			return zindex_personaje;
		}
    }
    return -1;
}

void ControladorJson::setLogLevel(json j,string argumentoConsola)throw(){
	try{
		if(argumentoConsola.empty())
			nivel_debug = j["logLevel"];
		else
			nivel_debug = argumentoConsola;
		if (nivel_debug !="ERROR" && nivel_debug != "INFO"  && nivel_debug != "DEBUG" ){
			controladorLogger->registrarEvento("ERROR","ControladorJson::Nivel de Debug no corresponde a ERROR, INFO o DEBUG. Se setea en " + nivel_debug_default);
			nivel_debug = nivel_debug_default;
		}
	}
	catch(json::type_error &e){
		controladorLogger->registrarEvento("ERROR","ControladorJson::Nivel de Debug no corresponde a ERROR, INFO o DEBUG. Se setea en " + nivel_debug_default);
		nivel_debug = nivel_debug_default;
	}
	controladorLogger->setNivelDebug(nivel_debug);
	controladorLogger->registrarEvento("INFO","ControladorJson::Log level = " + nivel_debug);

}

void ControladorJson::setCantidadClientes(json j){
	try{
		cantidad_clientes = j["cantidadClientes"];
	}catch(json::type_error &e){
		controladorLogger->registrarEvento("ERROR", "Cantidad de clientes debe ser un número. Seteado a 4 por default.");
		cantidad_clientes = 4;
		return;
	}
	if (cantidad_clientes > 4){
		controladorLogger->registrarEvento("ERROR", "El servidor no soporta mas de 4 jugadores, seteado a 4 por default.");
		cantidad_clientes = 4;
		return;
	}
	if (cantidad_clientes < 1){
		controladorLogger->registrarEvento("ERROR", "El servidor necesita al menos 1 jugador, seteado a 1 por default.");
		cantidad_clientes = 1;
		return;
	}
}

int ControladorJson::cantidadClientes(){
	return cantidad_clientes;
}

void ControladorJson::setAlturaVentana(json j)throw(){
	try{
		altura_ventana = j["window"]["height"];
		if (altura_ventana < rango_altura_ventana[0] || altura_ventana > rango_altura_ventana[1]){
			controladorLogger->registrarEvento("ERROR","ControladorJson::Altura de la ventana no permitida. Se setea en " + std::to_string(altura_ventana_default));
			altura_ventana = altura_ventana_default;
		}
		else
			controladorLogger->registrarEvento("DEBUG","ControladorJson::Altura ventana seteada: "+std::to_string(altura_ventana));
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
		else
			controladorLogger->registrarEvento("DEBUG","ControladorJson::Ancho ventana seteada: "+std::to_string(ancho_ventana));
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
	controladorLogger->registrarEvento("DEBUG","ControladorJson::Fullscreen = " + std::to_string(fullscreen));
}

void ControladorJson::setFPS(json j)throw(){
	try{
		FPS = j["FPS"];
		if (FPS < rango_FPS[0] || FPS > rango_FPS[1]){
			controladorLogger->registrarEvento("ERROR","ControladorJson::Cantidad de FPS no permitido. Se setea en " + std::to_string(FPS_default));
			FPS = FPS_default;
		}
		else
			controladorLogger->registrarEvento("DEBUG","ControladorJson::FPS seteados = " + std::to_string(FPS));
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
	controladorLogger->registrarEvento("DEBUG","ControladorJson::Personajes contados = " + std::to_string(cantidad_personajes));

}
void ControladorJson::setCantidadRounds(json j)throw(){
	cantidad_rounds = 3;
	controladorLogger->registrarEvento("DEBUG","ControladorJson::Cantidad Rounds seteados = " + std::to_string(cantidad_rounds));
}
void ControladorJson::setCantidadFondos(json j)throw(){
	controladorLogger->registrarEvento("DEBUG", "ControladorJson:: Por setear cantidad fondos por round");
	/*cantidad_fondos.push_back(j["round1"].size());
	cantidad_fondos.push_back(j["round2"].size());
	cantidad_fondos.push_back(j["round3"].size());
	//cantidad_fondos[1] = j["round2"].size();
	//cantidad_fondos[2] = j["round3"].size();
	controladorLogger->registrarEvento("DEBUG", "ControladorJson:: Cantidad fondos por round seteado");
	/*/
	for (int i=1; i<cantidad_rounds+1; i++){
		try{
			cantidad_fondos.push_back(j["round" + std::to_string(i)].size());
		}
		catch(json::type_error &e){
			cantidad_fondos[i] = cantidad_fondos_default;
			controladorLogger->registrarEvento("ERROR","ControladorJson::Cantidad de fondos para round " + std::to_string(i) + " invalida. Se setea en: " + std::to_string(j["round" + std::to_string(i)].size()));
		}
		controladorLogger->registrarEvento("DEBUG","ControladorJson::Fondos contados para round " + std::to_string(i) + " = " + std::to_string(cantidad_fondos[i-1]));

	}
}
void ControladorJson::setRounds(json j)throw(){
	try{
		for (int i=0; i<cantidad_rounds; i++){
			vector<tuple<string, int>> fondosi = (this->setFondos(j, i+1));
			controladorLogger->registrarEvento("DEBUG", "ControladorJson:: Fondos para escenario " + to_string(i+1) + " encontrado");
			escenarios.push_back(fondosi);
			controladorLogger->registrarEvento("DEBUG", "ControladorJson:: Fondos para escenario " + to_string(i+1) + " seteado");
		}
	}catch(json::type_error &e){
		//TODO cachear error
		controladorLogger->registrarEvento("ERROR", "ControladorJson:: Fondos para escenario no se pudo setear");
	}
}
vector<tuple<string, int>> ControladorJson::setFondos(json j, int round)throw(){
	vector<tuple<string, int>> fondos;
	try{
		controladorLogger->registrarEvento("DEBUG","ControladorJson::Seteando fondos para round " + std::to_string(round) + " cantidad: " + std::to_string(cantidad_fondos[round-1]));
		for (int i = 0; i < cantidad_fondos[round-1]; i++){
			string filepath_fondo = j["round"+ std::to_string(round)][i]["background"]["filepath"];
			int zindex_fondo = j["round"+ std::to_string(round)][i]["background"]["zindex"];

			std::ifstream file(filepath_fondo.c_str());
			if (file.good() == false){
				controladorLogger->registrarEvento("ERROR","ControladorJson::Imagen de fondo zindex" + std::to_string(zindex_fondo) + "no encontrada. Se carga una por defecto");
				filepath_fondo = "contents/auxiliar/capa" + std::to_string(zindex_fondo) + "aux.png";
			}
			fondos.push_back(std::make_tuple(filepath_fondo , zindex_fondo));
		}
		controladorLogger->registrarEvento("DEBUG","ControladorJson::Fondos round " + std::to_string(round) + " seteados");
	}
	catch(json::type_error &e){
		fondos.clear();
		for (int i = 0; i < cantidad_fondos[round]; i++){
			int zindex_fondo = 3 - i;
			string filepath_fondo = "contents/auxiliar/capa" + std::to_string(zindex_fondo) + "aux.png";
			controladorLogger->registrarEvento("ERROR","ControladorJson::Imagen de fondo no encontrada. Se carga una por defecto");
			fondos.push_back(std::make_tuple(filepath_fondo , zindex_fondo));
		}
	}
	return fondos;
}

int ControladorJson::cantidadPersonajes(){
	return this->cantidad_personajes;
}

void ControladorJson::setPersonajes(json j)throw(){
	try{
		for (int i = 0; i < cantidad_personajes; i++){
			string nombre_personaje = j["characters"][i]["name"];
			string filepath_personaje = j["characters"][i]["filepath"];
			string file_boton_personaje = j["characters"][i]["buttonpath"];
			int height_personaje = j["characters"][i]["height"];
			int width_personaje = j["characters"][i]["width"];
			int zindex_personaje = j["characters"][i]["zindex"];

			std::vector<std::string> vec;
			vec.push_back("CapitanAmerica");
			vec.push_back("Hulk");
			vec.push_back("Venom");
			vec.push_back("Spiderman");
			vec.push_back("MegaMan");

			if ( std::find(vec.begin(), vec.end(), nombre_personaje) == vec.end() ){
				controladorLogger->registrarEvento("ERROR","ControladorJson::Imagen de personaje" + nombre_personaje+" no encontrada. Se carga una por defecto");
				nombre_personaje = "SinSprite";
				filepath_personaje = "contents/images/sinSprite.png";
				file_boton_personaje = "contents/images/BotonSinSprite.png";
			}


			ifstream file(filepath_personaje.c_str());
			if (file.good() == false){
				controladorLogger->registrarEvento("ERROR","ControladorJson::Imagen de personaje" + nombre_personaje+" no encontrada. Se carga una por defecto");
				nombre_personaje = "SinSprite";
				filepath_personaje = "contents/images/sinSprite.png";
				file_boton_personaje = "contents/images/BotonSinSprite.png";
			}
			ifstream fileboton(file_boton_personaje.c_str());
			if (fileboton.good() == false){
				controladorLogger->registrarEvento("ERROR","ControladorJson::Boton del personaje" + nombre_personaje+" no encontrada. Se carga una por defecto");
				nombre_personaje = "SinSprite";
				filepath_personaje = "contents/images/sinSprite.png";
				file_boton_personaje = "contents/images/BotonSinSprite.png";
			}
			personajes.push_back(std::make_tuple(nombre_personaje, filepath_personaje, height_personaje, width_personaje, zindex_personaje, file_boton_personaje));
			nombresPersonajes.push_back(nombre_personaje);
		}
		controladorLogger->registrarEvento("DEBUG","ControladorJson::Personajes seteados");
	}
	catch(json::type_error &e){
		personajes.clear();
		controladorLogger->registrarEvento("ERROR","ControladorJson::Hubo un error de tipo en el parse de datos de uno o varios personajes. Se cargan personajes por defecto");
		for (int i = 0; i < cantidad_personajes; i++){
			string nombre_personaje = nombre_personaje_default;
			string filepath_personaje = "contents/images/sinSprite.png";
			string file_boton_personaje = "contents/images/sinSprite.png";
			int height_personaje = height_personaje_default;
			int width_personaje = width_personaje_default;
			int zindex_personaje = zindex_personaje_default;
			personajes.push_back(std::make_tuple(nombre_personaje, filepath_personaje, height_personaje, width_personaje, zindex_personaje,file_boton_personaje));
		}
	}


}

void ControladorJson::setPersonajeJugador(int personaje, int jugador, string nombre){
	if(nombre!="CapitanAmerica" && nombre!="Venom" && nombre!="Spiderman" && nombre!="Hulk"&& nombre!="MegaMan"){
		controladorLogger->registrarEvento("ERROR","ControladroJson::No es un nombre valido: "+ nombre );
		nombre = "sinSprite";
	}
	if(jugador==1){
		this->personajesJugador1[personaje-1]=nombre;
		controladorLogger->registrarEvento("INFO", "Se eligio a " + nombre + " para el jugador 1");
	}else if (jugador==2){
		this->personajesJugador2[personaje-1]=nombre;
		controladorLogger->registrarEvento("INFO", "Se eligio a " + nombre + " para el jugador 2");
	}
}

string ControladorJson::jugador1Personaje(int numero){
	return personajesJugador1[numero];
}

string ControladorJson::jugador2Personaje(int numero){
	return personajesJugador2[numero];
}

void ControladorJson::setCantidadJugadores(json j)throw(){
	try{
		cantidad_jugadores = j["jugadores"].size();
	}
	catch(json::type_error &e){
		cantidad_jugadores = 2;
		controladorLogger->registrarEvento("ERROR","ControladorJson::Cantidad de jugadores invalida. Se setea en: 2");
	}
	controladorLogger->registrarEvento("DEBUG","ControladorJson::Jugadores contados = " + std::to_string(cantidad_jugadores));
}


void ControladorJson::cambiarPantallaCompleta(){
	this->fullscreen = not this->fullscreen;
}

void ControladorJson::maximizarVentana(int ancho, int alto){
	this->ancho_ventana = ancho;
	this->altura_ventana = alto;
	this->altura_piso = altura_ventana *2/15;
}


int ControladorJson::getPosicionXInicialEquipo1(){
	return this->ancho_ventana * 1/16;
}

int ControladorJson::getPosicionXInicialEquipo2(){
	return this->ancho_ventana * 3/4;
}

int ControladorJson::getLimiteFondoDer(){
	return this->ancho_ventana * 15/16;
}

int ControladorJson::getLimiteFondoIzq(){
	return this->altura_ventana *1/16;
}

int ControladorJson::getAlturaPiso(){
	return this->altura_piso;
}

int ControladorJson::alturaPersonajeDefault(){
	return this->altura_personaje_default;
}

int ControladorJson::anchoPersonajeDefault(){
	return this->ancho_personaje_default;
}
