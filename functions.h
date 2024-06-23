#include <string>
#include <fstream>
#include <streambuf>
#include <iostream>
#include <chrono>
/**
 * @brief Imprime los tamaños en bits del texto original, texto codificado y datos comprimidos. 
 * @param text La cadena de texto original.
 * @param encodedText La cadena de texto codificada.
 * @param compressed Vector de pares que representa la versión comprimida del texto.
 */
void printSize(string text, string encodedText, const vector<Pair> &compressed){

    int compressedSize = 0;
    
    for (const Pair &p : compressed) {
        if (p.second == 0) {
            compressedSize += 8; // carácter ASCII (8 bits)
        } else {
            compressedSize += 16; // posición (8 bits) + longitud (8 bits)
        }
    }

    std::cout << "Tamano original: " << text.size() * 8 << " bits" << std::endl;
    std::cout << "Tamano codificado: " << encodedText.size() << " bits" << std::endl;
    std::cout << "Tamano comprimido: " << compressedSize << " bits" << std::endl;
}
/**
 * @brief Método para medir el tiempo de ejecución para codificar y decodificar un archivo usando Huffman.
 * @param filename Nombre del archivo que se va a leer y procesar.
 * @return Un par de valores double que representan los tiempos de codificación y decodificación en segundos.
 */
std::pair<double, double> tiempoCodificado(string filename) {
    auto start = chrono::high_resolution_clock::now();

    HuffmanCoding huffman;

    std::string inputFilePath = filename;

    ifstream inputFile(inputFilePath, ios::binary);
    if (!inputFile.is_open()) {
        cerr << "No se pudo abrir el archivo de entrada." << endl;
        exit(1);
    }

    stringstream buffer;
    buffer << inputFile.rdbuf();
    string text = buffer.str();
    inputFile.close();

    // Codificación Huffman
    string encodedText = huffman.codificar(text);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> durationencoded = end - start;

    start = chrono::high_resolution_clock::now();

    string decodedText = huffman.decodificar(encodedText);

    end = chrono::high_resolution_clock::now();
    chrono::duration<double> durationdecoded = end - start;

    return {durationencoded.count(), durationdecoded.count()};
}
/**
 * @brief Método para medir el tiempo de ejecución para comprimir y descomprimir un archivo usando LZ.
 * @param filename Nombre del archivo que se va a leer y procesar.
 * @return Un par de valores double que representan los tiempos de compresión y descompresión en segundos.
 */
std::pair<double, double> tiempoCompresion(string filename) {
    auto start = chrono::high_resolution_clock::now();

    std::string inputFilePath = filename;

    ifstream inputFile(inputFilePath, ios::binary);
    if (!inputFile.is_open()) {
        cerr << "No se pudo abrir el archivo de entrada." << endl;
        exit(1);
    }

    stringstream buffer;
    buffer << inputFile.rdbuf();
    string text = buffer.str();
    inputFile.close();

    // Compresión LZ
    vector<Pair> compressedLZ = compress(text);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> durationcompress = end - start;

    start = chrono::high_resolution_clock::now();

    string decompressedLZ = decompress(compressedLZ);

    end = chrono::high_resolution_clock::now();
    chrono::duration<double> durationdecompress = end - start;

    return {durationcompress.count(), durationdecompress.count()};
}
/**
 * @brief Realiza múltiples pruebas de codificación y decodificación de archivos de diferentes tamaños, registrando los tiempos en un archivo CSV.
 * @param n_tests Número de pruebas que se van a realizar.
 * @param file_name Nombre base del archivo CSV que se creará para registrar los tiempos.
 */
void tiempoCodificadoDou(int n_tests,string file_name)
{
    ofstream file_out(file_name + ".csv", ios::app);
    file_out << "Tamaño del archivo, Tiempo de Codificacion(s), Tiempo de Decodificacion(s)" << endl;

        for (int i = 0; i < n_tests; i++) {
        auto tiempos = tiempoCodificado("D:/Joako/Desktop/Archivos de la U/Estructura de datos/Proyecto_EdD/100KB.txt");
        file_out << "100KB," << tiempos.first << "," << tiempos.second << endl;

        tiempos = tiempoCodificado("D:/Joako/Desktop/Archivos de la U/Estructura de datos/Proyecto_EdD/300KB.txt");
        file_out << "300KB," << tiempos.first << "," << tiempos.second << endl;

        tiempos = tiempoCodificado("D:/Joako/Desktop/Archivos de la U/Estructura de datos/Proyecto_EdD/500KB.txt");
        file_out << "500KB," << tiempos.first << "," << tiempos.second << endl;

        tiempos = tiempoCodificado("D:/Joako/Desktop/Archivos de la U/Estructura de datos/Proyecto_EdD/800KB.txt");
        file_out << "800KB," << tiempos.first << "," << tiempos.second << endl;

        tiempos = tiempoCodificado("D:/Joako/Desktop/Archivos de la U/Estructura de datos/Proyecto_EdD/1MB.txt");
        file_out << "1MB,"  << tiempos.first << "," << tiempos.second << endl;
    }

    file_out.close();
}
/**
 * @brief Realiza múltiples pruebas de compresión y decompresión de archivos de diferentes tamaños, registrando los tiempos en un archivo CSV.
 * @param n_tests Número de pruebas que se van a realizar.
 * @param file_name Nombre base del archivo CSV que se creará para registrar los tiempos.
 */
void tiempoCompresionDou(int n_tests,string file_name)
{
    ofstream file_out(file_name + ".csv", ios::app);
    file_out << "Tamaño del archivo, Tiempo de Compresion(s), Tiempo de Decompresion(s)" << endl;

        for (int i = 0; i < n_tests; i++) {
        auto tiempos = tiempoCompresion("D:/Joako/Desktop/Archivos de la U/Estructura de datos/Proyecto_EdD/100KB.txt");
        file_out << "100KB," << tiempos.first << "," << tiempos.second << endl;

        tiempos = tiempoCompresion("D:/Joako/Desktop/Archivos de la U/Estructura de datos/Proyecto_EdD/300KB.txt");
        file_out << "300KB," << tiempos.first << "," << tiempos.second << endl;

        tiempos = tiempoCompresion("D:/Joako/Desktop/Archivos de la U/Estructura de datos/Proyecto_EdD/500KB.txt");
        file_out << "500KB," << tiempos.first << "," << tiempos.second << endl;

        tiempos = tiempoCompresion("D:/Joako/Desktop/Archivos de la U/Estructura de datos/Proyecto_EdD/800KB.txt");
        file_out << "800KB," << tiempos.first << "," << tiempos.second << endl;

        tiempos = tiempoCompresion("D:/Joako/Desktop/Archivos de la U/Estructura de datos/Proyecto_EdD/1MB.txt");
        file_out << "1MB,"  << tiempos.first << "," << tiempos.second << endl;
    }

    file_out.close();
}