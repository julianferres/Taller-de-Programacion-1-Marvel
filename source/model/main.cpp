#include <Juego.hpp>
#include <controler/ControladorJson.hpp>
#include <controler/ControladorLogger.hpp>
#include <Parallax.hpp>


time_t my_time = time(NULL);
ControladorJson *controladorJson = new ControladorJson();
ControladorLogger *controladorLogger = new ControladorLogger(controladorJson->nivelDebug());
Parallax *p = nullptr;

int main(int argc, char **argv){
	const int FPS = 60;
	const int frameDelay = 1000/ FPS;
	Uint32 frameStart;
	int frameTime;

	p = new Parallax();
	std::cout << "Creo al objeto!" << std::endl;

	return 0;

}

