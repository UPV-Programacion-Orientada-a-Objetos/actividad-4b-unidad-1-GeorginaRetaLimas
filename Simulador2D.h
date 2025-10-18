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
    // ... otros métodos de acceso y visualización
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
    for(int i = 0; i < filas; i++){
        delete[] _grid[i];
    }
    
    // Limpiamos los arrays
    delete[] _grid;
    delete[] _fuentes;
}

// Redimensionamiento
template <typename T>
Simulador2D<T>::redimensionarGrid(int nuevaF, int nuevaC){
    // Creamos la nueva Matriz
    T **nuevaGrid = new T*[nuevasF];
    for(int i = 0; i < nuevasF; i++){
        nuevaGrid[i] = new T[nuevasC];

        for(int j = 0; j < nuevasC; j ++){
            nuevaGrid[i][j] = 0;
        }
    }

    // Copiamos los datos, buscamos el indice menor para copiar
    int filasCopiar = (filas < nuevasF) ? filas : nuevasF;
    int columnasCopiar = (columnas < nuevasC) ? columnas : nuevasC;

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
    _filas = nuevasF;
    _columnas = nuevasC;
}