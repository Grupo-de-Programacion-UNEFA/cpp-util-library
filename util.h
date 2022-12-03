/*
   ----------------------------
   cpp-util-library - util-0.3
   ----------------------------
*/
// I N F O R M A C I O N
// ======================
// Las siguientes lineas son las librerias de cabecero que usa el programa.
// Para proyecto de un archivo, copiar y pegar las librerias junto al namespace "util".
// Para proyectos multificheros, añadir las siguientes lineas al header.h o el
// archivo de cabecero que use el proyecto, copiar las lineas correspondiente a la definición del namespace util
// y comentar las lineas de abajo (recomendado).

// =============================
//  LIBRERIAS DEL UTIL.H
// =============================
#pragma once // directiva que indica que se compile una sola vez

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cctype>
#include <stdlib.h>
#include <climits>
#include <iterator>
#include <map>
#include <type_traits>

// ==============================
//  DECLARACION DE LAS FUNCIONES
// ==============================

namespace util {
   const std::map <char, int> typeOfValue = {
      {'b', 1},
      {'c', 2},
      {'i', 3},
      {'f', 4},
      {'d', 5},
      {'s', 6}
   };
   struct ConfigStatement {
      char typeOV[2];
      std::string key;
      std::string strValue;
   };
   class Config {
      private:
         // Dictionaries of configurations
         std::map <std::string, bool> _boolList = {
            {"isWin", false},
            {"willPause", false},
            {"willClear", false}
         };
         std::map <std::string, char> _charList;
         std::map <std::string, int> _intList;
         std::map <std::string, float> _floatList;
         std::map <std::string, double> _doubleList;
         std::map <std::string, std::string> _stringList;

         std::map <std::string, bool> _readonlyList;

         std::string removeComments(std::string line) {
            std::string cleaned;
            for (int i = 0; i < line.size(); i++) {
               if (line[i] == '#') break;
               cleaned += line[i];
            } 
            return cleaned;
         }
         std::string removeSpaces(std::string line) {
            std::string sanitized = "";
            for (int i = 0; i < line.size(); i++) {
               if (line[i] != ' ') sanitized += line[i];
            } 
            return sanitized;
         }
         // b:key=value
         ConfigStatement getStatement (std::string str) {
            ConfigStatement statement;

            int tSeparator = str.find(':');
            int pSeparator = str.find('=');
            if (tSeparator == -1 || pSeparator == -1) throw 1;
            for (int i = 0; i < str.size(); i++) {
               if (i == tSeparator || i == pSeparator) continue;
               if (i < tSeparator) {
                  statement.typeOV[i] = str[i];
               } else if (i < pSeparator) {
                  statement.key += str[i];
               } else {
                  statement.strValue += str[i];
               }
            }
            return statement;
         }
      public:
         Config ();

         char readChar(std::string key);
         bool readBool(std::string key);
         int readInt(std::string key);
         float readFloat(std::string key);
         double readDouble(std::string key);
         std::string readString(std::string key);

         void writeChar(std::string key, char value, bool readonly = false);
         void writeBool(std::string key, bool value, bool readonly = false);
         void writeInt(std::string key, int value, bool readonly = false);
         void writeFloat(std::string key, float value, bool readonly = false);
         void writeDouble(std::string key, double value, bool readonly = false);
         void writeString(std::string key, std::string value, bool readonly = false);
   };
   Config CONF;
   // Templates & Overloaded Functions
   template <typename numType> numType inputNumber (std::string textoARepetir, numType max = INT_MAX, numType min = INT_MIN);
   template <typename numType> numType strToNumber (std::string str);
   std::string formattedFloat (float num);
   std::string formattedFloat (std::string str);
   // Simple Functions
   bool validarClav (std::string clave, int intentos = 3);
   bool inputBool (std::string textoARepetir, std::string valorTrue, std::string valorFalse);
   bool strToBool (std::string str, std::string trueValue, std::string falseValue);
   std::string inputString (std::string textoARepetir, bool espaciosEnBlanco = false, unsigned int longitudDeseada = 0);
   std::string multiplyStr (std::string str, int times);
   void borrarPantalla ();
   void pause ();
   void setConfig(bool isWin = false, bool willPause = false, bool willClear = false);
} // namespace util

// En caso de trabajar con archivo de cabecero, descomentar la siguiente linea y modificar la ruta
// al nombre del archivo a trabajar

// #include "header.h"


// =============================
//  DEFINICION DE LAS FUNCIONES
// =============================
namespace util {
   Config::Config () {
      bool isReadonly;
      int value;
      std::ifstream file ("util.conf");
      std::string line, output;
      ConfigStatement statement;

      while ( std::getline ( file, line)) {
         // Sanitize each line of configuration
         output = Config::removeSpaces(Config::removeComments( line ));
         if (output.size() == 0) continue;
         try {
            statement = getStatement(output);
            isReadonly = strToBool(std::string(1, statement.typeOV[0]), "r", "w");
            switch (typeOfValue.find(statement.typeOV[1])->second) {
               case 1:
                  // Add boolean to boolList
                  writeBool(statement.key, strToBool(statement.strValue, "true", "false"), isReadonly);
                  break;
               case 2:
                  // Add char to charList
                  writeChar(statement.key, statement.strValue[0], isReadonly);
                  break;
               case 3:
                  // Add int to intList
                  writeInt(statement.key, strToNumber<int>(statement.strValue), isReadonly);
                  break;
               case 4:
                  // Add float to floatList
                  writeFloat(statement.key, strToNumber<float>(statement.strValue), isReadonly);
                  break;
               case 5:
                  // Add double to doubleList
                  writeDouble(statement.key, strToNumber<double>(statement.strValue), isReadonly);
                  break;
               case 6:
                  // Add string to stringList
                  writeString(statement.key, statement.strValue, isReadonly);
                  break;
               default:
                  throw 2;
            }
         }
         catch(int err) {
            std::string msg = "ERROR: ";
            if (err == 1) msg += "getStatement process failed.\n";
            if (err == 2) msg += "Unknown type of value in configuration.\n";
            if (err == 3) msg += "Invalid conversion.\n";
            if (err == -1) msg += "ERROR. Read-only configuration already exists.\n";
            std::cout << msg;
         }
         catch(...) {
            std::cout << "hubo un error";
            pause();
         }
      }
      file.close();
   }

   bool Config::readBool(std::string key) {
      try {
         if (_boolList.find(key) == _boolList.end()) throw -1;
         return _boolList[key];
      } catch (int err) {
         std::cout << "ERROR: configuration not found. Abort\n";
         util::pause();
         exit(EXIT_FAILURE);
      }
   }
   char Config::readChar(std::string key) {
      try {
         if (_charList.find(key) == _charList.end()) throw -1;
         return _charList[key];
      } catch (int err) {
         std::cout << "ERROR: configuration not found. Abort\n";
         util::pause();
         exit(EXIT_FAILURE);
      }
   }
   int Config::readInt(std::string key) {
      try {
         if (_intList.find(key) == _intList.end()) throw -1;
         return _intList[key];
      } catch (int err) {
         std::cout << "ERROR: configuration not found. Abort\n";
         util::pause();
         exit(EXIT_FAILURE);
      }
   }
   float Config::readFloat(std::string key) {
      try {
         if (_floatList.find(key) == _floatList.end()) throw -1;
         return _floatList[key];
      } catch (int err) {
         std::cout << "ERROR: configuration not found. Abort\n";
         util::pause();
         exit(EXIT_FAILURE);
      }
   }
   double Config::readDouble(std::string key) {
      try {
         if (_doubleList.find(key) == _doubleList.end()) throw -1;
         return _doubleList[key];
      } catch (int err) {
         std::cout << "ERROR: configuration not found. Abort\n";
         util::pause();
         exit(EXIT_FAILURE);
      }
   }
   std::string Config::readString(std::string key) {
      try {
         if (_stringList.find(key) == _stringList.end()) throw -1;
         return _stringList[key];
      } catch (int err) {
         std::cout << "ERROR: configuration not found. Abort\n";
         util::pause();
         exit(EXIT_FAILURE);
      }
   }
   
   void Config::writeBool(std::string key, bool value, bool readonly) {
      try {
         if (_readonlyList.find(key) != _readonlyList.end() && _readonlyList[key]) throw -1;
         _readonlyList[key] = readonly;
         _boolList[key] = value;
      } catch (int err) {
         std::cout << "ERROR: Write a read-only configuration is forbidden. Abort\n";
         util::pause();
         exit(EXIT_FAILURE);
      }
   }
   void Config::writeChar(std::string key, char value, bool readonly) {
      try {
         if (_readonlyList.find(key) != _readonlyList.end() && _readonlyList[key]) throw -1;
         _readonlyList[key] = readonly;
         _charList[key] = value;
      } catch (int err) {
         std::cout << "ERROR: Write a read-only configuration is forbidden. Abort\n";
         util::pause();
         exit(EXIT_FAILURE);
      }
   }
   void Config::writeInt(std::string key, int value, bool readonly) {
      try {
         if (_readonlyList.find(key) != _readonlyList.end() && _readonlyList[key]) throw -1;
         _readonlyList[key] = readonly;
         _intList[key] = value;
      } catch (int err) {
         std::cout << "ERROR: Write a read-only configuration is forbidden. Abort\n";
         util::pause();
         exit(EXIT_FAILURE);
      }
   }
   void Config::writeFloat(std::string key, float value, bool readonly) {
      try {
         if (_readonlyList.find(key) != _readonlyList.end() && _readonlyList[key]) throw -1;
         _readonlyList[key] = readonly;
         _floatList[key] = value;
      } catch (int err) {
         std::cout << "ERROR: Write a read-only configuration is forbidden. Abort\n";
         util::pause();
         exit(EXIT_FAILURE);
      }
   }
   void Config::writeDouble(std::string key, double value, bool readonly) {
      try {
         if (_readonlyList.find(key) != _readonlyList.end() && _readonlyList[key]) throw -1;
         _readonlyList[key] = readonly;
         _doubleList[key] = value;
      } catch (int err) {
         std::cout << "ERROR: Write a read-only configuration is forbidden. Abort\n";
         util::pause();
         exit(EXIT_FAILURE);
      }
   }
   void Config::writeString(std::string key, std::string value, bool readonly) {
      try {
         if (_readonlyList.find(key) != _readonlyList.end() && _readonlyList[key]) throw -1;
         _readonlyList[key] = readonly;
         _stringList[key] = value;
      } catch (int err) {
         std::cout << "ERROR: Write a read-only configuration is forbidden. Abort\n";
         util::pause();
         exit(EXIT_FAILURE);
      }
   }
   // Habilita una entrada de usuario validada para que ingrese un numero entero o flotante,
   // imprimiendo un mensaje descriptivo que se repite tras cada iteracion.
   // Recibe un booleano que dicta ademas si el valor a devolver va a ser decimal o entero.
   template <typename numType> numType inputNumber (std::string textoARepetir, numType max, numType min) {
      numType num;
      std::string input = "";
      while (true) {
         std::cout << textoARepetir;
         std::cin >> input;
         try {
            num = util::strToNumber<numType>(input);
            if (num < min) throw 1;
            if (num > max) throw 2;
            return num;
         } catch (int err) {
            borrarPantalla();
            if (err == 1) {
               std::cout << "El numero que ingreso es MENOR al limite establecido ("<< min <<"). Ingrese un numero mayor." << std::endl;
            } else if (err == 2) {
               std::cout << "El numero que ingreso es MAYOR al limite establecido ("<< max <<"). Ingrese un numero menor." << std::endl;
            }
         } catch (...) {
            borrarPantalla();
            std::cout << "Entrada invalida." << std::endl;
         }
         continue;
      }
   }
   template <typename numType> numType strToNumber (std::string str) {
      return stod(str);
   }
   // Recibe un FLOAT
   // Retorna una cadena de texto que representa un numero flotante con dos decimales
   std::string formattedFloat (float num) {
      std::string str = "";
      str = std::to_string(num);
      return util::formattedFloat(str);
   }
   // recibe un STRING
   // Retorna una cadena de texto que representa un numero flotante con dos decimales
   std::string formattedFloat (std::string str) {
      int pos;
      pos = str.find('.');
      if (pos == -1) return str;
      return str.substr(0, pos) + str.substr(pos, 3);
   }
   // Genera una entrada booleana con dos valores posibles (ejemplo: S/N)
   bool inputBool (std::string textoARepetir, char valorTrue, char valorFalse) {
      std::string input;
      char option;
      while (true) {
         std::cout << textoARepetir << " (" << valorTrue << "/" << valorFalse << "): ";
         std::cin >> input;
         
         option = tolower(input[0]);
         if (option == std::tolower(valorTrue)) return true;
         if (option == std::tolower(valorFalse)) return false;
         
         std::cout << "Ingrese una letra valida." << std::endl;
      }
   }
   bool strToBool (std::string str, std::string trueValue, std::string falseValue) {
      if (str == trueValue) return true;
      if (str == falseValue) return false;
      throw 3;
   }
   // retorno booleano y cuyos parametros es la clave a validar como entero.
   // Son 3 intentos por DEFAULT
   bool validarClav (std::string clave, int intentos) {
      std::string claveIngresada;
      for (intentos; intentos > 0; intentos--) {
         claveIngresada = util::inputString("Ingrese clave para continuar: ", false);
         borrarPantalla();
         if (claveIngresada == clave) {
            std::cout << "Clave Ingresada Correcta. Puede Continuar.\n";
            pause();
            return true; // Retorna verdadero, que la clave ingresada fue valida
         } else { // Si no coincidio, avisa que se equivoco
            std::cout << "Clave Ingresada Incorrecta. ";
            if (intentos-1 > 0)	{
               std::cout << intentos-1 << " intento(s) restante(s).\n"; // Si los hay, imprime la cantidad de oportunidades restantes
            }
         }
      }
      std::cout << "Operacion Cancelada.\n";
      pause();
      return false;  // Retorna falso, ya que las claves ingresadas no fueron validas
   }
   // Habilita una entrada de usuario validada para que ingrese una cadena de texto validada,
   // imprimiendo un mensaje descriptivo que se repite tras cada iteracion.
   // Recibe un booleano que dicta si el valor acepta espacios en blanco.
   // Recibe un entero positivo que dicta la longitud necesaria de la cadena.
   std::string inputString (std::string textoARepetir, bool espaciosEnBlanco, unsigned int longitudDeseada) {
      std::string input = "";
      while (true) {
         // Imprime el texto en cada vuelta para que no se pierda
         std::cout << textoARepetir;
         if (espaciosEnBlanco) {
            // Limpia los datos para que no se adulteren
            std::cin.ignore();
            // Captura la línea completa
            getline(std::cin, input);
         } else {
            std::cin >> input;
         }
         try	{
            // Valida si tiene carácteres no permitidos '|', '\', ',', '.' o espacios en blanco si lo dice el argumento 
            if (input.find('|') != -1 || input.find('\\') != -1 || input.find(',') != -1 || input.find('.') != -1 || (!espaciosEnBlanco && input.find(' ') != -1)) throw 1;
            if (longitudDeseada > 0 && input.size() != longitudDeseada) throw 2;
            return input;
         } catch (int codigoError) {
            std::string mensajeError = "";
            switch (codigoError) {
               case 1:
                  mensajeError = "Entrada invalida, debe ingresar sin usar "; 
                  if (espaciosEnBlanco) mensajeError += "espacios en blanco ni ";						
                  mensajeError += "los caracteres especiales '|', '\\', ',' o '.'";
                  break;
               case 2:
                  mensajeError = "Entrada valida, el dato debe tener (" + std::to_string(longitudDeseada) + ") caracteres de longitud"; break;
            }
            std::cout << mensajeError << std::endl;
            continue;
         }
      }
   }
   // Recibe un string y lo retorna repetido la cantidad de veces indicada
   std::string multiplyStr (std::string str, int times) {
      std::string textoMultiplicado = "";
      for (int i = 0; i < times; i++) {
         textoMultiplicado += str;
      }
      return textoMultiplicado;
   }
   // Encapsula una funcion para limpiar la pantalla del programa para multiplataforma
   void borrarPantalla () {
      if (!CONF.readBool("willClear")) return;
      system(((CONF.readBool("isWin")) ? "cls" : "clear")); // LIMPIA LA CONSOLA EN WINDOWS/LINUX
      // std::cout << "\033[2J\033[1;1H"; // LIMPIA LA CONSOLA EN UNIX/LINUX
   }
   // Encapsula la funcion para pausar el programa para multiplataforma
   void pause () {
      if (!CONF.readBool("willPause")) return;
      if (CONF.readBool("isWin")) {system("pause"); return;}
      std::cout << "Presione una tecla para continuar . . . ";
      std::cin.ignore();
      std::cin.get();
   }
   void setConfig (bool isWin, bool willPause, bool willClear) {
      CONF.writeBool("isWin", isWin);
      CONF.writeBool("willPause", willPause);
      CONF.writeBool("willClear", willClear);
   }
} // namespace util