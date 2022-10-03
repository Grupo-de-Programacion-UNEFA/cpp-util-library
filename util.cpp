/*
   -------------------------------------
   Definicion de funciones de Utilidades
   -------------------------------------
*/
// I N F O R M A C I O N
// ======================
// Las siguientes lineas son las librerias de cabecero que usa el programa.
// Para proyecto de un archivo, copiar y pegar las librerias junto al namespace "util".
// Para proyectos multificheros, añadir las siguientes lineas al header.h o el
// archivo de cabecero que use el proyecto, copiar las lineas correspondiente a la definición del namespace util
// y comentar las lineas de abajo (recomendado).

// =============================
//  LIBRERIAS DEL UTIL.CPP
// =============================
#include <iostream>
#include <string>
#include <cmath>
#include <cctype>
#include <stdlib.h>
#include <random>

using namespace std;

// ==============================
//  DECLARACION DE LAS FUNCIONES
// ==============================
namespace util {
   bool validarClav (string clave, int intentos = 3);
   float inputNumber (string textoARepetir, bool decimal = false);
   string formattedFloat (float num);
   string formattedFloat (string str);
   string inputString (string textoARepetir, bool espaciosEnBlanco = false, unsigned int longitudDeseada = 0);
   string inputRandom ();
} // namespace util

// En caso de trabajar con archivo de cabecero, descomentar la siguiente linea y modificar la ruta
// al nombre del archivo a trabajar

// #include "header.h"


// =============================
//  DEFINICION DE LAS FUNCIONES
// =============================
namespace util {
	// retorno booleano y cuyos parametros es la clave a validar como entero.
	// Son 3 intentos por DEFAULT
	bool validarClav (string clave, int intentos) {
		string claveIngresada;
		for (intentos; intentos > 0; intentos--) {
			claveIngresada = util::inputString("Ingrese clave para continuar: ", false);
			borrarPantalla();
			if (claveIngresada == clave) {
				cout << "Clave Ingresada Correcta. Puede Continuar.\n";
				system("pause");
				return true; // Retorna verdadero, que la clave ingresada fue valida
			} else { // Si no coincidio, avisa que se equivoco
				cout << "Clave Ingresada Incorrecta. ";
				if (intentos-1 > 0)	{
					cout << intentos-1 << " intento(s) restante(s).\n"; // Si los hay, imprime la cantidad de oportunidades restantes
				}
			}
		}
		cout << "Operacion Cancelada.\n";
		system("pause");
		return false;  // Retorna falso, ya que las claves ingresadas no fueron validas
	}
    // Habilita una entrada de usuario validada para que ingrese un numero entero o flotante,
    // imprimiendo un mensaje descriptivo que se repite tras cada iteracion.
    // Recibe un booleano que dicta ademas si el valor a devolver va a ser decimal o entero.
    float inputNumber (string textoARepetir, bool decimal) {
		string input = "";
		while (true) {
            cout << textoARepetir;
			cin >> input;
			input = util::formattedFloat(input);
			try	{
				// Lo convierte a float, luego a string formateado y por último
                if (decimal) return stof(input);
                return stoi(input);
			} catch (...) {
				cout << "Numero ingresado invalido." << endl;
				continue;
			}
		}
	}
    // Recibe un FLOAT
    // Retorna una cadena de texto que representa un numero flotante con dos decimales
	string formattedFloat (float num) {
		string str = "";
		str = to_string(num);
		return util::formattedFloat(str);
	}
    // recibe un STRING
    // Retorna una cadena de texto que representa un numero flotante con dos decimales
	string formattedFloat (string str) {
		int pos;
		pos = str.find('.');
		if (pos == -1) return str;
		return str.substr(0, pos) + str.substr(pos, 3);
	}
    // Habilita una entrada de usuario validada para que ingrese una cadena de texto validada,
    // imprimiendo un mensaje descriptivo que se repite tras cada iteracion.
    // Recibe un booleano que dicta si el valor acepta espacios en blanco.
    // Recibe un entero positivo que dicta la longitud necesaria de la cadena.
	string inputString (string textoARepetir, bool espaciosEnBlanco, unsigned int longitudDeseada) {
		string input = "";
		while (true) {
			// Imprime el texto en cada vuelta para que no se pierda
            cout << textoARepetir;
			if (espaciosEnBlanco) {
				// Limpia los datos para que no se adulteren
				cin.ignore();
				// Captura la línea completa
				getline(cin, input);
			} else {
				cin >> input;
			}
			try	{
				// Valida si tiene carácteres no permitidos '|', '\', ',', '.' o espacios en blanco si lo dice el argumento 
                if (input.find('|') != -1 || input.find('\\') != -1 || input.find(',') != -1 || input.find('.') != -1 || (!espaciosEnBlanco && input.find(' ') != -1)) throw 1;
				if (longitudDeseada > 0 && input.size() != longitudDeseada) throw 2;
				return input;
			} catch (int codigoError) {
				string mensajeError = "";
				switch (codigoError) {
					case 1:
						mensajeError = "Entrada invalida, debe ingresar sin usar "; 
						if (espaciosEnBlanco) mensajeError += "espacios en blanco ni ";						
						mensajeError += "los caracteres especiales '|', '\\', ',' o '.'";
						break;
					case 2:
						mensajeError = "Entrada valida, el dato debe tener (" + to_string(longitudDeseada) + ") caracteres de longitud"; break;
				}
				cout << mensajeError << endl;
				continue;
			}
		}
	}
    // Genera un codigo numerico aleatorio y lo devuelve en forma de cadena
	string inputRandom () {
		string Coordenadas;
	    random_device nun;
	    mt19937 generator(nun());
	    uniform_int_distribution<>dist(10000000,99999999);
	    Coordenadas=to_string(dist(generator));
	
	    return Coordenadas;
	}
    // Declara y define la funcion borrarPantalla, sin argumentos ni retorno (void)
    void borrarPantalla () {
	    // cout << "\033[2J\033[1;1H"; // LIMPIA LA CONSOLA EN UNIX/LINUX
	    system("CLS"); // LIMPIA LA CONSOLA EN WINDOWS
    }
} // namespace util