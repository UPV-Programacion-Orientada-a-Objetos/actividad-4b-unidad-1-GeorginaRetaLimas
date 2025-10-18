#ifndef SIMULADOR2D_H 
#define SIMULADOR2D_H

#include <iostream>
#include <iomanip> 

template <typename T>
class Simulador2D {
private:
    // Matriz de la cuadrícula (Dinámica y Genérica)
    T **_grid;
    int _filas;
    int _columnas;

    // Vector de Fuentes (Dinámico y Genérico)
    T *_fuentes;
    int _numFuentes;
    int _capacidadFuentes;

    // Vector de Constantes (Estático)
    float _constantes[3]; // [0] = Coeficiente de Difusión, [1] = DeltaX, [2] = DeltaT

public:
    // MÉTODOS PÚBLICOS OBLIGATORIOS:
    Simulador2D(int f, int c); // Constructor
    ~Simulador2D(); // Destructor
    void redimensionarGrid(int nuevaF, int nuevaC);
    void agregarFuente(T valor); // Expansión manual del vector dinámico si es necesario
    void simularPaso(); // Implementación del algoritmo
    
    // Aquí los otros metodos
    void setValor(int fila, int col, T valor);
    void mostrarGrid() const;
};


template <typename T>
Simulador2D<T>::Simulador2D(int f, int c)
    : _filas(f), _columnas(c), _numFuentes(0), _capacidadFuentes(4){
    
    // Creamos el array de punteros que tendra las filas
    _grid = new T*[_filas];

    // Crear las columnas
    for(int i = 0; i < _filas; i++){
        _grid[i] = new T[_columnas];
    
        // Inicializamos
        for(int j = 0; j < _columnas; j++) {
            _grid[i][j] = T(0); // Inicializamos en 0
        }
    }

    // Creamos el vector de la capacidad de las fuentes
    _fuentes = new T[_capacidadFuentes];

    _constantes[0] = 0.25f; // Coeficiente de difisión
    _constantes[1] = 1.0f;  // Delta X
    _constantes[2] = 1.0f;  // Delta Y
}

// Destructor :3
template <typename T>
Simulador2D<T>::~Simulador2D(){
    // Liberamos cada fila
    for(int i = 0; i < _filas; i++){
        delete[] _grid[i];
    }
    
    // Limpiamos los arrays
    delete[] _grid;
    delete[] _fuentes;

    std::cout<<"¡Grind limapiado con éxito!"<<std::endl;
    std::cout<<"Fuentes limapiadas con éxito!"<<std::endl;
}

// Redimensionamiento
template <typename T>
void Simulador2D<T>::redimensionarGrid(int nuevaF, int nuevaC){
    // Creamos la nueva Matriz
    T **nuevaGrid = new T*[nuevaF];
    for(int i = 0; i < nuevaF; i++){
        nuevaGrid[i] = new T[nuevaC];

        for(int j = 0; j < nuevaC; j ++){
            nuevaGrid[i][j] = 0;
        }
    }

    // Copiamos los datos, buscamos el indice menor para copiar
    int filasCopiar = (_filas < nuevaF) ? _filas : nuevaF;
    int columnasCopiar = (_columnas < nuevaC) ? _columnas : nuevaC;

    // Pasamos los datos
    for(int i = 0; i < filasCopiar; i++){
        for(int j = 0; j < columnasCopiar; j ++){
            nuevaGrid[i][j] = _grid[i][j];
        }
    }

    // Liberamos la memoria
    for(int i = 0; i < _filas; i++){
        delete[] _grid[i];
    }

    delete[] _grid;

    _grid = nuevaGrid;
    _filas = nuevaF;
    _columnas = nuevaC;
}

// Agregar una nueva fuente
template <typename T>
void Simulador2D<T>::agregarFuente(T valor) {
    // Si el número de fuentes ya iguala o sobrepasa la capacidad
    if(_numFuentes >= _capacidadFuentes){
        // Expandir
        int nuevaCapacidad = _capacidadFuentes * 2;
        T* nuevoArray = new T[nuevaCapacidad];

        // Pasamos los datos al nuevo
        for(int i = 0; i < _numFuentes; i++) {
            nuevoArray[i] = _fuentes[i];
        }

        // Limpiamos
        delete[] _fuentes;

        _fuentes = nuevoArray;
        _capacidadFuentes = nuevaCapacidad;
    }

    // Y si no es asi solo añadimos el nuevo valor
    _fuentes[_numFuentes] = valor;
    _numFuentes++;
}

template <typename T>
void Simulador2D<T>::simularPaso() {
    //Crear array de punteros
    T** temp = new T*[_filas];

    for(int i = 0; i < _filas; i++) {
        temp[i] = new T[_columnas];
    }

    // Calcular nuevos valores
    for(int i = 0; i < _filas; i++) {
        for(int j = 0; j < _columnas; j++) {
            if(i == 0 || i == _filas-1 || j == 0 || j == _columnas-1){
                temp[i][j] = _grid[i][j];
            } else { 
                T arriba = _grid[i-1][j];
                T abajo = _grid[i+1][j];
                T izquierda = _grid[i][j-1];
                T derecha = _grid[i][j+1];
                
                temp[i][j] = (arriba + abajo + izquierda + derecha) / T(4);
            }
        }
    }

    // Copiar de temporal a grid
    for(int i = 0; i < _filas; i++) {
        for(int j = 0; j < _columnas; j++) {
            _grid[i][j] = temp[i][j];
        }
    }

    // Liberar temp
    for(int i = 0; i < _filas; i++) {
        delete[] temp[i];
    }
    delete[] temp;
}

// Set Valor en el Grind
template <typename T>
void Simulador2D<T>::setValor(int fila, int col, T valor) {
    if(fila >= 0 && fila < _filas && col >= 0 && col < _columnas){
        _grid[fila][col] = valor;
    }
}

// Mostrar el Grind
template <typename T>
void Simulador2D<T>::mostrarGrid() const {
    for(int i = 0; i < _filas; i++) {
        for(int j = 0; j < _columnas; j++) {
            // setw(6) es un set with es decir nos va a reservar 
            // 6 espacios para lo que es el numero
            std::cout << std::setw(6) << _grid[i][j] << " ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

#endif