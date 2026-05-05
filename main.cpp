#include <iostream>
#include <vector>

using namespace std;

struct Nodo {
    int valor;
    Nodo* izq;
    Nodo* der;
};

vector<Nodo*> versiones_arbol;

Nodo* crear_nodo(int valor) {
    Nodo* nuevo = new Nodo();
    nuevo->valor = valor;
    nuevo->izq = nullptr;
    nuevo->der = nullptr;
    return nuevo;
}

Nodo* insertar_recursivo(Nodo* raiz_antigua, int valor) {
    if (raiz_antigua == nullptr) {
        return crear_nodo(valor);
    }

    Nodo* nueva_raiz = new Nodo();
    nueva_raiz->valor = raiz_antigua->valor;

    if (valor < raiz_antigua->valor) {
        nueva_raiz->izq = insertar_recursivo(raiz_antigua->izq, valor);
        nueva_raiz->der = raiz_antigua->der;
    } else {
        nueva_raiz->izq = raiz_antigua->izq;
        nueva_raiz->der = insertar_recursivo(raiz_antigua->der, valor);
    }

    return nueva_raiz;
}

void insertar_nueva_version(int valor) {
    Nodo* raiz_actual = nullptr;
    if (versiones_arbol.size() > 0) {
        raiz_actual = versiones_arbol.back();
    }
    
    Nodo* nueva_raiz = insertar_recursivo(raiz_actual, valor);
    versiones_arbol.push_back(nueva_raiz);
}

bool buscar_en_version(Nodo* raiz, int valor) {
    if (raiz == nullptr) {
        return false;
    }
    if (raiz->valor == valor) {
        return true;
    }
    
    if (valor < raiz->valor) {
        return buscar_en_version(raiz->izq, valor);
    } else {
        return buscar_en_version(raiz->der, valor);
    }
}

int main() {
    insertar_nueva_version(50);
    insertar_nueva_version(30);
    insertar_nueva_version(70);
    insertar_nueva_version(20);
    insertar_nueva_version(40);

    int total_versiones = versiones_arbol.size();
    
    cout << "Total de versiones creadas: " << total_versiones << "\n\n";

    cout << "Buscando el numero 40 en todas las versiones historicas:\n";
    for (int i = 0; i < total_versiones; i++) {
        bool encontrado = buscar_en_version(versiones_arbol[i], 40);
        cout << "Version " << i + 1 << ": ";
        if (encontrado) {
            cout << "Encontrado\n";
        } else {
            cout << "No encontrado\n";
        }
    }

    cout << "\nBuscando el numero 70 en todas las versiones historicas:\n";
    for (int i = 0; i < total_versiones; i++) {
        bool encontrado = buscar_en_version(versiones_arbol[i], 70);
        cout << "Version " << i + 1 << ": ";
        if (encontrado) {
            cout << "Encontrado\n";
        } else {
            cout << "No encontrado\n";
        }
    }

    return 0;
}