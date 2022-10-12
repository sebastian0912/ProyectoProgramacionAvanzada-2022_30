#ifndef _LIBRERIAS_H_
#define _LIBRERIAS_H_

#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <fstream>
#include <iomanip>

using namespace std;


struct rete
{
    char *nombre = new char[30];
    double documento;
    char *cargo = new char[20];
    double salario;
    double retefuente;
};

struct Empleado
{
    char nombre[45];
    double documento;
    char tipo [20];
    char cargo [20];
    double salarios;
};

struct asignatura
{
    char nombre[45];
    int numeroDeHoras;
};

struct Profesor
{
    char nombre[45];
    double documento;
    char cargo [20];
    double salarios;
    char escalafon [20];
    double valorHora;
    vector<asignatura> listaAsignaturas;
};

struct monitor
{
    char nombre[45];
    double documento;
    char cargo[30];
    double salarios;
    vector<asignatura> listaAsignaturas;
};

struct tipos
{
    vector<Empleado> listaEmpleados;
    vector<Profesor> listaProfesores;
    vector<monitor> listaMonitores;
};


/*Lee el archivo y guarda los datos en un vector de empleados, y luegos los separa 
por caracteres, y luego los distribuye en los diferentes vectores segun el tipo*/
void lecturaArchivoYGuardado(vector<char *> &empleados, string filename, vector<Empleado> &listaEmpleados, vector<Profesor> &listaProfesores, vector<monitor> &listaMonitores, struct tipos &lista)
{
    char *str = new char[100];
    char *datos = new char[100];
    int cont = 0;
    int cont2 = 0;
    Profesor prof;
    monitor moni;
    Empleado emp;
    ifstream file(filename);
    while (file.getline(str, 50))
    {
        // leer datos y pegarlos con un guion en char *datos
        // cout << str << endl;
        if (strcmp(str, "#") != 0 && strcmp(str, "FIN") != 0)
        {
            strcat(datos, str);
            strcat(datos, "-");
        }
        else
        {
            memset(datos, ' ', 6);
            empleados.push_back(datos);
            datos = new char[300];
        }
    }
    delete[] datos;
    delete[] str;
    file.close();
    // Imprimir vector
    for (int i = 0; i < empleados.size(); i++)
    {
        // cout << empleados[i] << endl;
        //  Separar datos
        if (strstr(empleados[i], "Profesor"))
        {
            char *token = strtok(empleados[i], "%-");
            while (token != NULL)
            {
                // cout << token << endl;
                if (cont == 0)
                {
                    strcpy(prof.nombre, token);
                }
                else if (cont == 1)
                {
                    prof.documento = atof(token);
                }
                else if (cont == 2)
                {
                    strcpy(prof.cargo, token);
                }
                else if (cont == 3)
                {
                    strcpy(prof.escalafon, token);
                }
                else if (cont > 3)
                {
                    asignatura asig;                    
                    // cout <<"Copia: "<<copia << endl;
                    strcpy(asig.nombre, token);

                    prof.listaAsignaturas.push_back(asig);
                }
                token = strtok(NULL, "%-");
                cont++;
            }
            // borrar memoria dinamica

            cont = 0;
            lista.listaProfesores.push_back(prof);
        }

        else if (strstr(empleados[i], "Monitor"))
        {

            char *token = strtok(empleados[i], "%-");
            while (token != NULL)
            {
                // cout << token << endl;
                if (cont == 0)
                {
                    strcpy(moni.nombre, token);
                }
                else if (cont == 1)
                {
                    moni.documento = atof(token);
                }
                else if (cont == 2)
                {
                    strcpy(moni.cargo, token);
                }
                else if (cont == 3)
                {
                    asignatura asig;
                    char *copia = token;
                    // cout <<"Copia: "<<copia << endl;
                    strcpy(asig.nombre, copia);
                    moni.listaAsignaturas.push_back(asig);
                }
                token = strtok(NULL, "%-");
                cont++;
            }
            cont = 0;
            lista.listaMonitores.push_back(moni);
        }
        else
        {
            char *token = strtok(empleados[i], "%-");
            while (token != NULL)
            {
                // cout << token << endl;
                if (cont == 0)
                {
                    strcpy(emp.nombre, token);
                }
                else if (cont == 1)
                {
                    emp.documento = atof(token);
                }
                else if (cont == 2)
                {
                    strcpy(emp.tipo, token);
                }
                else if (cont == 3)
                {
                    strcpy(emp.cargo, token);
                }
                else if (cont == 4)
                {
                    emp.salarios = atof(token);
                }

                token = strtok(NULL, "%-");
                cont++;
            }

            cont = 0;
            lista.listaEmpleados.push_back(emp);
        }
    }

    // separar datos de las asignaturas de los profesores
    for (int i = 0; i < lista.listaProfesores.size(); i++)
    {
        for (int j = 0; j < lista.listaProfesores[i].listaAsignaturas.size(); j++)
        {
            char *token = strtok(lista.listaProfesores[i].listaAsignaturas[j].nombre, ",");
            strcpy(lista.listaProfesores[i].listaAsignaturas[j].nombre, token);
            token = strtok(NULL, ",");
            lista.listaProfesores[i].listaAsignaturas[j].numeroDeHoras = atof(token);
        }
    }

    // Limpiar datos basura en las asignaturas del monitor separandolos
    for (int i = 0; i < lista.listaMonitores.size(); i++)
    {
        for (int j = 0; j < lista.listaMonitores[i].listaAsignaturas.size(); j++)
        {
            char *token = strtok(lista.listaMonitores[i].listaAsignaturas[j].nombre, ",");
            strcpy(lista.listaMonitores[i].listaAsignaturas[j].nombre, token);
            token = strtok(NULL, ",");
            lista.listaMonitores[i].listaAsignaturas[j].numeroDeHoras = atof(token);
        }
    }

    // elimina un valor basura que se agrega al final del vector
    lista.listaEmpleados.pop_back();

    cout << endl
         << " --> Empleados Cargados" << endl
         << endl;
}

/*Verifica que se guarde un empleado, un profesor o un monitor repetido*/
bool verificarSiUnEmpleadoExiste(string tipo, struct tipos lista, Empleado emp, Profesor prof, monitor mom)
{
    vector<Empleado>::iterator it; //1 2 3 4 5 8 6 98 7 
    vector<Profesor>::iterator it2;
    vector<monitor>::iterator it3;

    if (tipo == "Empleado" || tipo == "empleado")
    {
        for (it = lista.listaEmpleados.begin(); it != lista.listaEmpleados.end(); it++)
        {
            if (it->nombre == emp.nombre)
            {
                if (it->documento == emp.documento)
                {
                    if (it->tipo == emp.tipo)
                    {
                        if (it->cargo == emp.cargo)
                        {
                            if (it->salarios == emp.salarios)
                            {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    else if (tipo == "Profesor" || tipo == "profesor")
    {
        for (it2 = lista.listaProfesores.begin(); it2 != lista.listaProfesores.end(); it2++)
        {
            if (it2->nombre == prof.nombre)
            {
                if (it2->documento == prof.documento)
                {
                    if (it2->cargo == prof.cargo)
                    {
                        if (it2->escalafon == prof.escalafon)
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    else if (tipo == "Monitor" || tipo == "monitor")
    {
        for (it3 = lista.listaMonitores.begin(); it3 != lista.listaMonitores.end(); it3++)
        {
            if (it3->nombre == mom.nombre)
            {
                if (it3->documento == mom.documento)
                {
                    if (it3->cargo == mom.cargo)
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

/*Agrega un empleado o un profesor o un monitor con los datos basicos, primiero pide el tipo y empieza
a operar, tambien verifica que no exista y ahi si lo guarda*/
void agregarEmpleado(struct tipos &lista)
{
    string tipo;
    Profesor prof;
    monitor mon;
    Empleado emp;
    cout << "Que tipo de empleado desea agregar?" << endl;
    cin >> tipo;

    if (tipo == "Profesor" || tipo == "profesor")
    {
        cout << "Ingrese el nombre del profesor: ";
        cin.ignore();
        cin.getline(prof.nombre, 50, '\n');
        cout << "Ingrese el documento del profesor: ";
        cin >> prof.documento;
        cin.ignore();
        strcpy(prof.cargo, "Profesor");
        cout << "Ingrese el escalafon del profesor: ";
        cin.getline(prof.escalafon, 30, '\n');
        if (verificarSiUnEmpleadoExiste(tipo, lista, emp, prof, mon) == false)
        {
            lista.listaProfesores.push_back(prof);
            cout << "Profesor agregado" << endl;
        }
        else
        {
            cout << "El profesor ya existe" << endl;
        }
    }
    else if (tipo == "Monitor" || tipo == "monitor")
    {

        cout << "Ingrese el nombre del monitor: ";
        cin.ignore();
        cin.getline(mon.nombre, 50, '\n');
        cout << "Ingrese el documento del monitor: ";
        cin >> mon.documento;
        strcpy(mon.cargo, "Monitor");
        if (verificarSiUnEmpleadoExiste(tipo, lista, emp, prof, mon) == false)
        {
            lista.listaMonitores.push_back(mon);
            cout << "Monitor agregado" << endl;
        }
        else
        {
            cout << "El monitor ya existe" << endl;
        }
    }
    else if (tipo == "Empleado" || tipo == "empleado")
    {
        cout << "Ingrese el nombre del empleado: ";
        cin.ignore();
        cin.getline(emp.nombre, 50, '\n');
        cout << "Ingrese el documento del empleado: ";
        cin >> emp.documento;
        strcpy(emp.tipo, "Empleado");
        cout << "Ingrese el cargo del empleado: ";
        cin.ignore();
        cin.getline(emp.cargo, 30, '\n');
        cout << "Ingrese el salario del empleado: ";
        cin >> emp.salarios;
        if (verificarSiUnEmpleadoExiste(tipo, lista, emp, prof, mon) == false)
        {
            lista.listaEmpleados.push_back(emp);
            cout << "Empleado agregado" << endl;
        }
        else
        {
            cout << "El empleado ya existe" << endl;
        }
    }
    else
    {
        cout << "Tipo de empleado no valido" << endl;
    }
}

/*Elimina un empleado segun su cedula o su nombre, segun el caso lo busca por todos los
vectores y lo elimina*/
void eliminarEmpleado(struct tipos &lista)
{
    int cedula;
    char *nombre = new char[50];
    int opcion, cont = 0;
    cout << "De que forma lo quiere eliminar? \n 1. Su nombre \n 2. Su cedula \n"
         << endl;
    cin >> opcion;
    if (opcion == 1)
    {
        cout << "Ingrese el nombre del empleado a eliminar: ";
        cin.ignore();
        cin.getline(nombre, 50, '\n');
        for (int i = 0; i < lista.listaEmpleados.size(); i++)
        {
            if (strstr(lista.listaEmpleados[i].nombre, nombre))
            {
                lista.listaEmpleados.erase(lista.listaEmpleados.begin() + i);
                cout << "Empleado eliminado" << endl;
                break;
            }
        }
        for (int i = 0; i < lista.listaProfesores.size(); i++)
        {
            if (strstr(lista.listaProfesores[i].nombre, nombre))
            {
                lista.listaProfesores.erase(lista.listaProfesores.begin() + i);
                cout << "Profesor eliminado" << endl;
                break;
            }
        }
        for (int i = 0; i < lista.listaMonitores.size(); i++)
        {
            if (strstr(lista.listaMonitores[i].nombre, nombre))
            {
                lista.listaMonitores.erase(lista.listaMonitores.begin() + i);
                cout << "Monitor eliminado" << endl;
                break;
            }
        }
    }
    else if (opcion == 2)
    {
        cout << "Ingrese la cedula del empleado a eliminar: ";
        cin >> cedula;
        for (int i = 0; i < lista.listaEmpleados.size(); i++)
        {
            if (lista.listaEmpleados[i].documento == cedula)
            {
                lista.listaEmpleados.erase(lista.listaEmpleados.begin() + i);
                cout << "Empleado eliminado" << endl;
                break;
            }
        }
        for (int i = 0; i < lista.listaProfesores.size(); i++)
        {
            if (lista.listaProfesores[i].documento == cedula)
            {
                lista.listaProfesores.erase(lista.listaProfesores.begin() + i);
                cout << "Profesor eliminado" << endl;
                break;
            }
        }
        for (int i = 0; i < lista.listaMonitores.size(); i++)
        {
            if (lista.listaMonitores[i].documento == cedula)
            {
                lista.listaMonitores.erase(lista.listaMonitores.begin() + i);
                cout << "Monitor eliminado" << endl;
                break;
            }
        }
    }
    else
    {
        cout << "Opcion no valida" << endl;
    }
}

/*Agrega asignatura a un profesor por su cedula, */
void adicionarAsignaturaProfesor(struct tipos &lista)
{
    int cedula;
    asignatura asig;
    cout << "Ingrese la cedula del profesor: ";
    cin >> cedula;
    vector<Profesor>::iterator it; 
    for (it = lista.listaProfesores.begin(); it != lista.listaProfesores.end(); it++)
    {
        if (it->documento == cedula)
        {
            cout << "Ingrese el nombre de la asignatura: ";
            cin.ignore();
            cin.getline(asig.nombre, 50, '\n');
            cout << "Ingrese el numero de horas: ";
            cin >> asig.numeroDeHoras;
            it->listaAsignaturas.push_back(asig);
            cout << "Asignatura agregada" << endl;
            break;
        }
    }
}

/*Agrega asignatura a un monitor por su cedula, */
void adicionarAsignaturaMonitor(tipos &lista)
{
    int cedula;
    asignatura asig;
    vector<monitor>::iterator it;
    cout << "Ingrese la cedula del monitor: ";
    cin >> cedula;
    for (it = lista.listaMonitores.begin(); it != lista.listaMonitores.end(); it++)
    {
        if (it->documento == cedula)
        {
            cout << "Ingrese el nombre de la asignatura: ";
            cin.ignore();
            cin.getline(asig.nombre, 50, '\n');
            cout << "Ingrese el numero de horas: ";
            cin >> asig.numeroDeHoras;
            it->listaAsignaturas.push_back(asig);
            cout << "Asignatura agregada" << endl;
        }
    }
}

/*calcula el salario de un empleado de tipo Empleado y lo genera segun el caso
si gana mas de 4 salarios y menos de 16 es una ecuacion y si es menor es otra*/
double calcularSalarioEmpleado(tipos lista)
{
    int cedula;
    double salario;
    cout << "Ingrese la cedula del empleado: ";
    cin >> cedula;
    vector<Empleado>::iterator it;
    for (it = lista.listaEmpleados.begin(); it != lista.listaEmpleados.end(); it++)
    {
        if (it->documento == cedula)
        {
            if (it->salarios > 4 && it->salarios < 16)
            {
                salario = ((it->salarios * 1000000) - ((it->salarios * 1000000) * 0.10)) * 0.75;
                return salario;
            }
            else if (it->salarios <= 4)
            {
                salario = ((it->salarios * 1000000) - ((it->salarios * 1000000) * 0.08)) * 0.75;
                return salario;
            }
            
        }
    }
    return 0;
}

/*calcula el salario segun el escalafon, y lo multiplica por la cantidad de horas trabajadas*/
double calcularSalarioProfesor(tipos &lista)
{
    int cedula, acumulador = 0;
    double salario;

    cout << "Ingrese la cedula del profesor: ";
    cin >> cedula;
    vector<Profesor>::iterator it;
    vector<asignatura>::iterator it2;
    for (it = lista.listaProfesores.begin(); it != lista.listaProfesores.end(); it++)
    {
        if (it->documento == cedula)
        {
            if (strcmp(it->escalafon, "Catedra") == 0)
            {
                salario = ((1000000 * 0.5) - ((1000000 * 0.5) * 0.08)) * 0.75;
                for (it2 = it->listaAsignaturas.begin(); it2 != it->listaAsignaturas.end(); it2++)
                {
                    acumulador += it2->numeroDeHoras;
                }
                return salario * acumulador;
            }
            else if (strcmp(it->escalafon, "Instructor") == 0)
            {
                salario = ((1000000) - (1000000 * 0.08)) * 0.75;
                for (it2 = it->listaAsignaturas.begin(); it2 != it->listaAsignaturas.end(); it2++)
                {
                    acumulador += it2->numeroDeHoras;
                }
                return salario * acumulador;
            }
            else if (strcmp(it->escalafon, "Asistente") == 0)
            {
                salario = ((1000000 * 1.5) - ((1000000 * 1.5) * 0.08)) * 0.75;
                for (it2 = it->listaAsignaturas.begin(); it2 != it->listaAsignaturas.end(); it2++)
                {
                    acumulador += it2->numeroDeHoras;
                }
                return salario * acumulador;
            }
            else if (strcmp(it->escalafon, "Asociado") == 0)
            {
                salario = ((1000000 * 2) - ((1000000 * 2) * 0.08)) * 0.75;
                for (it2 = it->listaAsignaturas.begin(); it2 != it->listaAsignaturas.end(); it2++)
                {
                    acumulador += it2->numeroDeHoras;
                }
                return salario * acumulador;
            }
            else if (strcmp(it->escalafon, "Titular") == 0)
            {
                salario = ((1000000 * 2.5) - ((1000000 * 2.5) * 0.08)) * 0.75;
                for (it2 = it->listaAsignaturas.begin(); it2 != it->listaAsignaturas.end(); it2++)
                {
                    acumulador += it2->numeroDeHoras;
                }
                return salario * acumulador;
            }
        }
    }
    return 0;
}

/*calcula el salario de un monitor segun la cantidad de horas trabajadas*/
double calcularSalarioMonitor(tipos &lista)
{
    int cedula, acumulador = 0;
    double salario;
    cout << "Ingrese la cedula del monitor: ";
    cin >> cedula;
    vector<monitor>::iterator it;
    for (it = lista.listaMonitores.begin(); it != lista.listaMonitores.end(); it++)
    {
        if (it->documento == cedula)
        {
            vector<asignatura>::iterator it2;
            for (it2 = it->listaAsignaturas.begin(); it2 != it->listaAsignaturas.end(); it2++)
            {
                acumulador += it2->numeroDeHoras;
            }
            return 7197 * acumulador;
        }
    }
    return 0;
}

/*Calcula el salario base de los empelados sea empleado, profesor, monitor, 
y va guardando la informacion en la estructura rete que es la de retencion en la fuente
luego genera el archivo con la estructura*/
void listarEmpleadosRetencion(tipos lista, vector<rete> &listaRetencion)
{
    vector<Empleado>::iterator it;
    vector<Profesor>::iterator it2;
    vector<monitor>::iterator it3;
    vector<rete>::iterator it4;
    vector<asignatura>::iterator it5;

    for (it = lista.listaEmpleados.begin(); it != lista.listaEmpleados.end(); it++)
    {
        rete retencion;
        strcpy(retencion.nombre, it->nombre);
        strcpy(retencion.cargo, it->tipo);
        retencion.documento = it->documento;
        retencion.salario = it->salarios * 1000000;
        if (retencion.salario > 5700600)
        {
            retencion.retefuente = retencion.salario * 0.28;
        }
        else
        {
            retencion.retefuente = 0;
        }

        listaRetencion.push_back(retencion);
    }

    for (it2 = lista.listaProfesores.begin(); it2 != lista.listaProfesores.end(); it2++)
    {
        rete retencion;
        double salario = 0, acumulador = 0;
        strcpy(retencion.nombre, it2->nombre);
        strcpy(retencion.cargo, it2->cargo);
        retencion.documento = it2->documento;
        if (strcmp(it2->escalafon, "Catedra") == 0)
        {
            salario = ((1000000 * 0.5));
            for (it5 = it2->listaAsignaturas.begin(); it5 != it2->listaAsignaturas.end(); it5++)
            {
                acumulador += it5->numeroDeHoras;
            }
            retencion.salario = salario * acumulador;

            if (retencion.salario > 5700600)
            {
                retencion.retefuente = retencion.salario * 0.28;
            }
            else
            {
                retencion.retefuente = 0;
            }
        }

        else if (strcmp(it2->escalafon, "Instructor") == 0)
        {
            salario = ((1000000));
            for (it5 = it2->listaAsignaturas.begin(); it5 != it2->listaAsignaturas.end(); it5++)
            {
                acumulador += it5->numeroDeHoras;
            }
            retencion.salario = salario * acumulador;
            if (retencion.salario > 5700600)
            {
                retencion.retefuente = retencion.salario * 0.28;
            }
            else
            {
                retencion.retefuente = 0;
            }
        }

        else if (strcmp(it2->escalafon, "Asistente") == 0)
        {
            salario = ((1000000 * 1.5));
            for (it5 = it2->listaAsignaturas.begin(); it5 != it2->listaAsignaturas.end(); it5++)
            {
                acumulador += it5->numeroDeHoras;
            }
            retencion.salario = salario * acumulador;
            if (retencion.salario > 5700600)
            {
                retencion.retefuente = retencion.salario * 0.28;
            }
            else
            {
                retencion.retefuente = 0;
            }
        }

        else if (strcmp(it2->escalafon, "Asociado") == 0)
        {
            salario = ((1000000 * 2));

            for (it5 = it2->listaAsignaturas.begin(); it5 != it2->listaAsignaturas.end(); it5++)
            {
                acumulador += it5->numeroDeHoras;
            }
            retencion.salario = salario * acumulador;
            if (retencion.salario > 5700600)
            {
                retencion.retefuente = retencion.salario * 0.28;
            }
            else
            {
                retencion.retefuente = 0;
            }
        }

        else if (strcmp(it2->escalafon, "Titular") == 0)
        {
            salario = ((1000000 * 2.5));
            for (it5 = it2->listaAsignaturas.begin(); it5 != it2->listaAsignaturas.end(); it5++)
            {
                acumulador += it5->numeroDeHoras;
            }
            retencion.salario = salario * acumulador;

            if (retencion.salario > 5700600)
            {
                retencion.retefuente = retencion.salario * 0.28;
            }
            else
            {
                retencion.retefuente = 0;
            }
        }
        listaRetencion.push_back(retencion);
        acumulador = 0;
    }

    for (it3 = lista.listaMonitores.begin(); it3 != lista.listaMonitores.end(); it3++)
    {
        rete retencion;
        double acumulador = 0;
        strcpy(retencion.nombre, it3->nombre);
        strcpy(retencion.cargo, it3->cargo);
        retencion.documento = it3->documento;
        for (it5 = it3->listaAsignaturas.begin(); it5 != it3->listaAsignaturas.end(); it5++)
        {
            acumulador += it5->numeroDeHoras;
        }
        retencion.salario = 7197 * acumulador;
        if (retencion.salario > 5700600)
        {
            retencion.retefuente = retencion.salario * 0.28;
        }
        else
        {
            retencion.retefuente = 0;
        }
        listaRetencion.push_back(retencion);
        acumulador = 0;
    }

    for (it4 = listaRetencion.begin(); it4 != listaRetencion.end(); it4++)
    {
        cout << setw(43) << "Nombre: " << setw(30) << it4->nombre << endl;
        cout << setw(43) << "Cargo: " << setw(30) << it4->cargo << endl;
        cout << setw(43) << "Documento: " << setw(30) << it4->documento << endl;
        cout << setw(43) << "Salario Base,Sin descuentros, sin factor: " << setw(30) << it4->salario << endl;
        cout << setw(43) << "Retencion 28%: " << setw(30) << it4->retefuente << endl;
        cout << endl
             << endl;
    }
    // escribir en archivo de texto la listaderetencion
    ofstream archivo;
    archivo.open("Retefuente.txt");
    for (it4 = listaRetencion.begin(); it4 != listaRetencion.end(); it4++)
    {
        archivo << setw(43) << "Nombre: " << setw(30) << it4->nombre << endl;
        archivo << setw(43) << "Cargo: " << setw(30) << it4->cargo << endl;
        archivo << setw(43) << "Documento: " << setw(30) << it4->documento << endl;
        archivo << setw(43) << "Salario Base,Sin descuentros, sin factor: " << setw(30) << it4->salario << endl;
        archivo << setw(43) << "Retencion 28%: " << setw(30) << it4->retefuente << endl;
        archivo << endl
                << endl;
    }
}

/*Calcular el salario de los empleados sea empleado, profesor, monitor; 
va guardando en el archivo de texto, su nombre, cedula y el salario*/
void generarNomina(tipos &lista)
{
    vector<Empleado>::iterator it;
    vector<Profesor>::iterator it2;
    vector<monitor>::iterator it3;
    double salario, acumulador = 0;
    vector<asignatura>::iterator it5;
    // escribir en archivo de texto la lista de empleados
    ofstream archivo;
    archivo.open("Reporte.txt");
 

    for (it = lista.listaEmpleados.begin(); it != lista.listaEmpleados.end(); it++)
    {
        archivo << it->nombre << ",";
        archivo << it->documento << ",";
        if (it->salarios > 4 && it->salarios < 8)
        {
            salario = ((it->salarios * 1000000) - ((it->salarios * 1000000) * 0.10)) * 0.75;
        }
        else if (it->salarios > 4)
        {
            salario = ((it->salarios * 1000000) - ((it->salarios * 1000000) * 0.08)) * 0.75;
        }
        it->salarios = salario;
        archivo << "$" << it->salarios << endl;
    }
    acumulador = 0;
    for (it2 = lista.listaProfesores.begin(); it2 != lista.listaProfesores.end(); it2++)
    {
        archivo << it2->nombre << ",";
        archivo << it2->documento << ",";
        if (strcmp(it2->escalafon, "Catedra") == 0)
        {
            salario = ((1000000 * 0.5) - ((1000000 * 0.5) * 0.08)) * 0.75;
            for (it5 = it2->listaAsignaturas.begin(); it5 != it2->listaAsignaturas.end(); it5++)
            {
                acumulador += it5->numeroDeHoras;
            }
            it2->salarios = salario * acumulador;
            cout << "Catedra: " << it2->salarios << endl;
            archivo << "$" << it2->salarios << endl;
        }
        else if (strcmp(it2->escalafon, "Instructor") == 0)
        {
            salario = ((1000000) - (1000000 * 0.08)) * 0.75;
            for (it5 = it2->listaAsignaturas.begin(); it5 != it2->listaAsignaturas.end(); it5++)
            {
                acumulador += it5->numeroDeHoras;
            }
            it2->salarios = salario * acumulador;
            archivo << "$" << it2->salarios << endl;
            cout << "Instructor: " << it2->salarios << endl;
        }
        else if (strcmp(it2->escalafon, "Asistente") == 0)
        {
            salario = ((1000000 * 1.5) - ((1000000 * 1.5) * 0.08)) * 0.75;
            for (it5 = it2->listaAsignaturas.begin(); it5 != it2->listaAsignaturas.end(); it5++)
            {
                acumulador += it5->numeroDeHoras;
            }
            it2->salarios = salario * acumulador;
            archivo << "$" << it2->salarios << endl;
            cout << "Asistente: " << it2->salarios << endl;
        }
        else if (strcmp(it2->escalafon, "Asociado") == 0)
        {
            salario = ((1000000 * 2) - ((1000000 * 2) * 0.08)) * 0.75;
            for (it5 = it2->listaAsignaturas.begin(); it5 != it2->listaAsignaturas.end(); it5++)
            {
                acumulador += it5->numeroDeHoras;
            }
            it2->salarios = salario * acumulador;
            archivo << "$" << it2->salarios << endl;
            cout << "Asociado: " << it2->salarios << endl;
        }
        else if (strcmp(it2->escalafon, "Titular") == 0)
        {
            salario = ((1000000 * 2.5) - ((1000000 * 2.5) * 0.08)) * 0.75;
            for (it5 = it2->listaAsignaturas.begin(); it5 != it2->listaAsignaturas.end(); it5++)
            {
                acumulador += it5->numeroDeHoras;
            }
            it2->salarios = salario * acumulador;
            archivo << "$" << it2->salarios << endl;
            cout << "Titular: " << it2->salarios << endl;
        }
        acumulador = 0;
    }
    acumulador = 0;
    for (it3 = lista.listaMonitores.begin(); it3 != lista.listaMonitores.end(); it3++)
    {

        double acumulador = 0;
        archivo << it3->nombre << ",";
        archivo << it3->documento << ",";
        for (it5 = it3->listaAsignaturas.begin(); it5 != it3->listaAsignaturas.end(); it5++)
        {
            acumulador += it5->numeroDeHoras;
        }
        it3->salarios = 7197 * acumulador;
        archivo << "$" << it3->salarios << endl;

        
    }
}

//Generar un archivo archivo de binario con los datos de los empleados sea empleado, profesor, monitor
void persistenciaNomina(tipos lista)
{
    // escribir en archivo binario la lista de empleados
    ofstream archi("Nomina.dat", ios::binary | ios::app);
    vector<Empleado>::iterator it;
    vector<Profesor>::iterator it2;
    vector<monitor>::iterator it3;
    vector<asignatura>::iterator it5;
    struct Empleado *empleado;

    for (it = lista.listaEmpleados.begin(); it != lista.listaEmpleados.end(); it++)
    {
        if (archi.is_open())
        {
            archi.write((char *)&(*it), sizeof(*it));            
        }
        else
            cout << "Error de apertura de archivo." << endl;        
    }
    for (it2 = lista.listaProfesores.begin(); it2 != lista.listaProfesores.end(); it2++)
    {
        if (archi.is_open())
        {
            archi.write((char *)&(*it2), sizeof(*it2));
        }
        else
            cout << "Error de apertura de archivo." << endl;
    }
    for (it3 = lista.listaMonitores.begin(); it3 != lista.listaMonitores.end(); it3++)
    {
        if (archi.is_open())
        {
            archi.write((char *)&(*it3), sizeof(*it3));
        }
        else
            cout << "Error de apertura de archivo." << endl;
    }
}

/*Imprime los empleados*/
void imprimir(tipos &lista)
{
    cout << endl
         << "Profesores: " << endl
         << endl;
    for (int i = 0; i < lista.listaProfesores.size(); i++)
    {
        cout << "Nombre: " << lista.listaProfesores[i].nombre << endl;
        cout << "Documento: " << lista.listaProfesores[i].documento << endl;
        cout << "Cargo: " << lista.listaProfesores[i].cargo << endl;
        cout << "Escalafon: " << lista.listaProfesores[i].escalafon << endl;
        for (int j = 0; j < lista.listaProfesores[i].listaAsignaturas.size(); j++)
        {
            cout << "Asignatura: " << lista.listaProfesores[i].listaAsignaturas[j].nombre << endl;
            cout << "Horas: " << lista.listaProfesores[i].listaAsignaturas[j].numeroDeHoras << endl;
        }
        cout << endl;
    }

    cout << endl
         << "Monitores: " << endl
         << endl;
    for (int i = 0; i < lista.listaMonitores.size(); i++)
    {
        cout << "Nombre: " << lista.listaMonitores[i].nombre << endl;
        cout << "Documento: " << lista.listaMonitores[i].documento << endl;
        cout << "Cargo: " << lista.listaMonitores[i].cargo << endl;
        for (int j = 0; j < lista.listaMonitores[i].listaAsignaturas.size(); j++)
        {
            cout << "Asignatura: " << lista.listaMonitores[i].listaAsignaturas[j].nombre << endl;
            cout << "Horas: " << lista.listaMonitores[i].listaAsignaturas[j].numeroDeHoras << endl;
        }
        cout << endl;
    }

    cout << endl
         << "Empleados: " << endl
         << endl;
    for (int i = 0; i < lista.listaEmpleados.size(); i++)
    {
        cout << "Nombre: " << lista.listaEmpleados[i].nombre << endl;
        cout << "Documento: " << lista.listaEmpleados[i].documento << endl;
        cout << "Tipo: " << lista.listaEmpleados[i].tipo << endl;
        cout << "Cargo: " << lista.listaEmpleados[i].cargo << endl;
        cout << "Salario: " << lista.listaEmpleados[i].salarios << endl;

        cout << endl;
    }
}

#endif