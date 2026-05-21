#include <iostream>
using namespace std;

// Estructura para cada curso (el nodo del tren)
struct Curso {
    string nombreCurso;       
    string nrc;                  // Numero de registro del curso
    int creditos;             // Creditos que vale la materia
    string docente;           // Nombre del profesor
    
    Curso* siguiente;         // El gancho que apunta al siguiente curso

    // Constructor: Para crear el curso con todos sus datos desde el inicio
    Curso(string nombre, string numNrc, int cred, string prof) {
        nombreCurso = nombre;
        nrc = numNrc;
        creditos = cred;
        docente = prof;
        siguiente = NULL;     // Al crear el nodo, todavia no apunta a nadie
    }
};

// --- VARIABLE GLOBAL ---
// Esta es nuestra lista principal. Al estar aqui afuera, todas las funciones 
// pueden moverla o revisarla sin necesidad de pasarle parametros.
Curso* listaCursos = NULL; 


// --- FUNCIONES PARA MANEJAR LA LISTA ---

// Saber si la lista no tiene nada
bool estaVacia() {
    return (listaCursos == NULL);
}

// Agregar un curso al inicio de la lista
void insertarAlPrincipio() {
    string nombre, prof, numNrc;
    int cred;

    // Pedimos los datos al usuario
    cout << "Nombre del curso: "; cin >> nombre;
    cout << "NRC del curso: "; cin >> numNrc;
    cout << "Creditos: "; cin >> cred;
    cout << "Nombre del docente: "; cin >> prof;

    // Creamos el nuevo nodo en memoria con sus datos
    Curso* nuevoCurso = new Curso(nombre, numNrc, cred, prof);
    
    // Lo conectamos al principio: su gancho apunta a lo que antes era el primero
    nuevoCurso->siguiente = listaCursos; 
    
    // Ahora nuestro nuevo curso pasa a ser la cabeza de la lista
    listaCursos = nuevoCurso;
    
    cout << "Curso " << nombre << " agregado al principio correctamente.\n";
}

// Agregar un curso al final de la lista
void insertarAlFinal() {
    string nombre, prof,numNrc;
    int  cred;

    cout << "Nombre del curso: "; cin >> nombre;
    cout << "NRC del curso: "; cin >> numNrc;
    cout << "Creditos: "; cin >> cred;
    cout << "Nombre del docente: "; cin >> prof;

    Curso* nuevoCurso = new Curso(nombre, numNrc, cred, prof);

    // Si la lista esta vacia, el nuevo curso se convierte en el primero
    if (listaCursos == NULL) {
        listaCursos = nuevoCurso;
    } else {
        // Si ya hay cosas, usamos un puntero auxiliar para recorrer la lista sin perder el inicio
        Curso* temp = listaCursos;
        
        // Avanzamos hasta encontrar el ultimo nodo (el que apunta a NULL)
        while (temp->siguiente != NULL) {
            temp = temp->siguiente;
        }
        // Cuando lo encontramos, le enganchamos el nuevo curso al final
        temp->siguiente = nuevoCurso;
    }
    cout << "Curso " << nombre << " agregado al final correctamente.\n";
}

// Mostrar en pantalla todos los cursos registrados
void imprimirLista() {
    if (estaVacia()) {
        cout << "La lista de cursos esta vacia." << "\n";
        return;
    }
    
    Curso* temp = listaCursos;
    cout << "\n=== LISTA ACTUAL DE CURSOS ===\n";
    
    // Recorremos toda la lista hasta salirnos de ella (hasta que temp sea NULL)
    while(temp != NULL) {
        cout << "[" << temp->nombreCurso 
             << " | NRC: " << temp->nrc 
             << " | Cred: " << temp->creditos 
             << " | Docente: " << temp->docente << "] -> ";
        
        temp = temp->siguiente; // Avanzamos al siguiente nodo
    }
    cout << "NULL\n";
}

// Borrar el primer elemento de la lista
void eliminarPrimero() {
    if (listaCursos != NULL) {
        Curso* temp = listaCursos;         // Guardamos el primero para que no se pierda
        listaCursos = listaCursos->siguiente; // Movemos la lista al segundo elemento
        delete temp;                       // Liberamos la memoria del que era el primero
        cout << "Primer curso eliminado.\n";
    } else {
        cout << "No hay cursos para eliminar.\n";
    }
}

// Borrar el ultimo elemento de la lista
void eliminarUltimo() {
    if(listaCursos == NULL) {
        cout << "La lista esta vacia.\n";
        return;
    }
    
    // Si solo hay un curso en la lista
    if(listaCursos->siguiente == NULL) {
        delete listaCursos;
        listaCursos = NULL;
    } else {
        Curso* temp = listaCursos;
        // Avanzamos hasta quedar parados en el penultimo nodo
        while (temp->siguiente->siguiente != NULL) {
            temp = temp->siguiente;
        }
        // Borramos el ultimo nodo de la memoria
        delete temp->siguiente;
        // El penultimo ahora pasa a ser el ultimo, asi que apunta a NULL
        temp->siguiente = NULL;
    }
    cout << "Ultimo curso eliminado.\n";
}

// Buscar un curso por su nombre y decir en que posicion esta
void buscarCurso() {
    if (estaVacia()) {
        cout << "La lista esta vacia. No hay nada que buscar.\n";
        return;
    }
    
    string valor;
    cout << "Introduce el nombre del curso a buscar: "; cin >> valor;

    Curso* temp = listaCursos;
    int pos = 0;
    
    while (temp != NULL) {
        if (temp->nombreCurso == valor) {
            cout << "Curso " << valor << " encontrado en la posicion " << pos << "\n";
            cout << "Detalles -> NRC: " << temp->nrc << ", Profesor: " << temp->docente << "\n";
            return; // Cortamos la funcion porque ya lo encontramos
        }
        temp = temp->siguiente;
        pos++;
    }
    cout << "El curso " << valor << " no se encuentra en la lista.\n";
}

// Borrar un curso especifico buscando su nombre
void eliminarEspecifico() {
    if(listaCursos == NULL) {
        cout << "La lista esta vacia.\n";
        return;
    }

    string valor;
    cout << "Nombre del curso que deseas eliminar: "; cin >> valor;

    // Caso especial: Si el que queremos borrar resulta que es el primero
    if(listaCursos->nombreCurso == valor) {
        eliminarPrimero(); 
        return;
    }

    Curso* temp = listaCursos;
    // Buscamos el nodo que esta JUSTO ANTES del que queremos borrar
    while (temp->siguiente != NULL && temp->siguiente->nombreCurso != valor) {
        temp = temp->siguiente;
    }

    // Si encontramos el curso
    if (temp->siguiente != NULL) {
        Curso* borrar = temp->siguiente; // Guardamos el nodo objetivo
        temp->siguiente = temp->siguiente->siguiente; // Saltamos el nodo haciendo un puente
        delete borrar; // Lo eliminamos de la memoria
        cout << "Curso " << valor << " fue eliminado con exito.\n";
    } else {
        cout << "No se encontro el curso con ese nombre.\n";
    }
}

// Vaciar toda la lista por completo
void eliminarTodo() {
    // Mientras la lista tenga nodos, borramos el primero uno por uno
    while (listaCursos != NULL) {
        eliminarPrimero();
    }
    cout << "Se han limpiado todos los cursos de la memoria.\n";
}

// --- PROGRAMA PRINCIPAL ---
int main() {
    int opcion;

    do {
        cout << "\n--- MENU DE CONTROL DE CURSOS ---" << "\n";
        cout << "1. Insertar al principio" << "\n";
        cout << "2. Insertar al final" << "\n";
        cout << "3. Eliminar primero" << "\n";
        cout << "4. Eliminar ultimo" << "\n";
        cout << "5. Eliminar curso especifico" << "\n";
        cout << "6. Buscar curso por nombre" << "\n";
        cout << "7. Comprobar si esta vacia" << "\n";
        cout << "8. Mostrar todos los cursos" << "\n";
        cout << "9. Eliminar toda la lista" << "\n";
        cout << "10. Salir" << "\n";
        cout << "Selecciona una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: insertarAlPrincipio(); break;
            case 2: insertarAlFinal(); break;
            case 3: eliminarPrimero(); break;
            case 4: eliminarUltimo(); break;
            case 5: eliminarEspecifico(); break;
            case 6: buscarCurso(); break;
            case 7:
                if(estaVacia()) cout << "La lista esta vacia.\n";
                else cout << "La lista ya tiene cursos registrados.\n";
                break;
            case 8: imprimirLista(); break;
            case 9: eliminarTodo(); break;
            case 10: cout << "Saliendo del programa...\n"; break;
            default: cout << "Opcion invalida, intenta de nuevo.\n"; break;
        }
        system("pause");
        system("cls");
        
    } while (opcion != 10);

    return 0;
}
