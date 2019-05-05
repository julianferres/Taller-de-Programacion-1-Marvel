#ifndef HEADERS_MODEL_SERVIDOR_HPP_
#define HEADERS_MODEL_SERVIDOR_HPP_

#define CANT_MAX_CLIENTES 4
class Servidor{

	public:
		Servidor();
		void enviarIdCliente(int idCliente,int socketCliente);
		static void *conexionCliente(void *cliente);
	private:
		int cantidadDeClientes;
};
#endif
