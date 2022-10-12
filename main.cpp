#include "librerias.h"

#include <iostream>
#include <vector>



using namespace std;

int main()
{        
    vector<char *> empleados;
    vector<Empleado> listaEmpleados;
    vector<Profesor> listaProfesores;
    vector<monitor> listaMonitores;
    vector<rete> listaRete;
    struct tipos lista;
    double salMon, salProf, salEmp;
    
    
    bool continuar = true;
    int opcion;
    do {
        cout<< "Programa de Nomina" << endl;
        cout<< "1. Cargar empleados" << endl;
        cout<< "2. Agregar empleado" << endl;
        cout<< "3. Eliminar empleado" << endl;
        cout << "4. Adicionar una asignatura a un profesor" << endl;
        cout << "5. Adicionar una asignatura a un monitor" << endl;
        cout << "6. Calcular el salario de un Empleado" << endl;
        cout << "7. Calcular el salario de un Profesor:" << endl;
        cout << "8. Calcular el salario de un Monitor" << endl;
        cout << "9. Listar los empleados que deben pagar Retencion en la Fuente" << endl;
        cout << "10. Generar la nomina en un archivo Reporte.txt " << endl;
        cout << "11. Hacer persistir la nomina/Salvarla en un archivo binario" << endl; 
        cout << "12. Salir"<<endl;
        cout << "Digite una opcion: ";
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            lecturaArchivoYGuardado(empleados, "Nomina.txt", listaEmpleados, listaProfesores, listaMonitores, lista);
            imprimir(lista);
            break;
        case 2:
            agregarEmpleado(lista);
            imprimir(lista);
            break;
        case 3:
            eliminarEmpleado(lista);
            imprimir(lista);
            break;
        case 4:
            adicionarAsignaturaProfesor(lista);
            imprimir(lista);
            break;
        case 5:
            adicionarAsignaturaMonitor(lista);
            imprimir(lista);
            break;
        case 6:
            salEmp = calcularSalarioEmpleado(lista);
            cout << "El salario del empleado es: " << salEmp << endl;
            break;
        case 7:
            salProf = calcularSalarioProfesor(lista);
            cout << "El salario del profesor es: " << salProf << endl;            
            break;
        case 8:
            salMon = calcularSalarioMonitor(lista);
            cout << "El salario del monitor es: " << salMon << endl;
            break;
        case 9:
            listarEmpleadosRetencion(lista, listaRete);
            break;
        case 10:
            generarNomina(lista);
            break;
        case 11:
            persistenciaNomina(lista);
            break; 
        case 12:
            continuar = false;
            break;            
        default:
            cout << "Opcion no valida" << endl;            
        }

        system  ("pause");
        system  ("cls");
    }
    while (true);

    return 0;
}