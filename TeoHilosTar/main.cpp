#include <windows.h>
#include <strsafe.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <list>

using namespace std;

#define BUF_SIZE 255
//#define Clientes 30
//#define Cajeros 5

std::list<std::string> cola;

DWORD WINAPI Thread_no_1(LPVOID lpParam) { //cliente
    HANDLE hStdout = NULL;

    if ((hStdout = GetStdHandle(STD_OUTPUT_HANDLE)) == INVALID_HANDLE_VALUE)
        return 1;

    
    srand(time(0));

    int tiempoElegirProducto = 10+(rand() % (80-10));
    Sleep(tiempoElegirProducto * 500);

    string IDCliente = std::to_string(GetCurrentThreadId());
    cout << "El cliente " << IDCliente << " eligio sus productos en " << tiempoElegirProducto << " seg" << endl;
    cola.push_back(IDCliente);

    return 0;
}

DWORD WINAPI Thread_no_2(LPVOID lpParam) { //cajero    
    HANDLE hStdout = NULL;

    if ((hStdout = GetStdHandle(STD_OUTPUT_HANDLE)) == INVALID_HANDLE_VALUE)
        return 1;

    
    while (cola.size() > 0) {
        srand(time(0));

        int tiempoEnCaja = rand() % 80;
        Sleep(tiempoEnCaja * 500);
        string IDCaja = std::to_string(GetCurrentThreadId());
        string clienteCola = cola.front();
        cola.pop_front();
        cout << "La cajera " << IDCaja << " atendio al cliente " << clienteCola << endl;
    }
    return 0;
}

int main() {
    cout << "-----Iniciando simulador de Supermercado-----"<< endl;
    cout << "Ingrese la cantidad de cajeros"<< endl;
    int Cajeros = 0;
    std::cin >> Cajeros;
    int numeroClientes = 50 + (rand()%(70 - 50));
    cout << "El numero de clientes se genera automaticamente y es " << numeroClientes << endl;
    int Clientes = numeroClientes;

    int Data_Of_Thread_1;
    int Data_Of_Thread_2;

    // variable to hold handle of Thread
    HANDLE Handle_Of_Thread_1 = 0;
    HANDLE Handle_Of_Thread_2 = 0;

    // thread 1.
    for (int i = 0; i < Clientes; i++) {
        Data_Of_Thread_1 = i + 1;
        Handle_Of_Thread_1 = CreateThread(NULL, 0, Thread_no_1, &Data_Of_Thread_1, 0, NULL);
        Sleep(400);
    }

    if (Handle_Of_Thread_1 == NULL)
        ExitProcess(Data_Of_Thread_1);

    //WaitForSingleObject(Handle_Of_Thread_1, INFINITE);

    // thread 2.
    for (int j = 0; j < Cajeros; j++) {
        Data_Of_Thread_2 = j + 1;
        Handle_Of_Thread_2 = CreateThread(NULL, 0, Thread_no_2, &Data_Of_Thread_2, 0, NULL);
        Sleep(400);
        
    }
    
    if (Handle_Of_Thread_2 == NULL)
            ExitProcess(Data_Of_Thread_2);

    WaitForSingleObject(Handle_Of_Thread_2, INFINITE);
    CloseHandle(Handle_Of_Thread_1);
    CloseHandle(Handle_Of_Thread_2);

    return 0;
}