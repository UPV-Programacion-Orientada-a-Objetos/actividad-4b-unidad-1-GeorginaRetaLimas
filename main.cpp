#include <iostream>

// Añadi esta biblioteca que es para manipular los datos de salida :3
#include <iomanip> 

#include "Simulador2D.h"

int main() {
    std::cout<<"== Simulador Genérico de Fluidos (Difusión) ==="<<::std::endl;

    std::cout<<">> Inicializando Sistema (Tipo FLOAT) <<"<<::std::endl;
    Simulador2D<float> simFloat(5, 5);

    std::cout<<">> Agregando Fuentes de Concentración <<"<<::std::endl;
    simFloat.agregarFuente(100.0f);
    simFloat.agregarFuente(50.0f);
    std::cout<<"Fuentes agregadas: 100.0 y 50.0"<<::std::endl<<::std::endl;

    std::cout<<">> Aplicando Valores Iniciales <<"<<::std::endl;
    simFloat.setValor(2, 2, 100.0f);
    simFloat.setValor(4, 0, 50.0f);
    
    std::cout<<"--- Grid Inicial (Paso 0) ---"<<::std::endl;
    simFloat.mostrarGrid();
    
    // Simular 3 pasos
    for(int paso = 1; paso <= 3; paso++) {
        simFloat.simularPaso();
        std::cout << "--- Grid Después del Paso " << paso << " ---"<<::std::endl;
        simFloat.mostrarGrid();
    }
    
    // Redimensionar
    std::cout<<">> Redimensionando Grid a 6x6 <<"<<::std::endl;
    simFloat.redimensionarGrid(6, 6);
    simFloat.mostrarGrid();

    std::cout<<">> Inicializando Sistema (Tipo INT) <<"<<::std::endl;
    Simulador2D<int> simInt(4, 4);
    
    simInt.agregarFuente(80);
    simInt.setValor(1, 1, 80);
    
    std::cout<<"--- Grid Inicial (INT) ---"<<::std::endl;
    simInt.mostrarGrid();
    
    simInt.simularPaso();
    std::cout<<"--- Después de 1 Paso ---"<<::std::endl;
    simInt.mostrarGrid();
    
    return 0;
}
