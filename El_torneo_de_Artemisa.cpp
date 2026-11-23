#include <iostream>
#include <string.h>
#include <time.h>
#include <iomanip>
using namespace std;

const int MAX = 100;
const int FILA = 9, COL = 9;

typedef char tcad[50];

typedef struct arquero
{
    tcad apellido;
    tcad nombre;
    tcad apodo;
    tcad signo_zodiacal;

    float dracmas;
    float mayor_puntaje;

    int cant_torneos_ganados;
    int cant_torneos_disputados;

    float puntaje_actual;
};

typedef struct t_Casillas
{
    int id;
    int numero;
    int dracmas;
    int puntaje_zona;
    int puntaje_casilla;
    bool ocupada;
};

typedef arquero tvector[MAX];
typedef t_Casillas tmatriz[FILA][COL];
typedef int tParticipantes[MAX];
typedef int tPosiciones[MAX];

//***PROTOTIPOS***

//----------------------------------------------------
// MENUS
//----------------------------------------------------
void menu_principal(char &op);
void menu_arqueros(char &op);
void menu_diana(char &op);
void menu_podio(int &op);

//----------------------------------------------------
// GESTION DE ARQUEROS
//----------------------------------------------------
void gestionar_arqueros(tvector v, int &ocup);

void agregar_arquero(tvector v, int &ocup);
void insertar_ordenado(tvector v, int &ocup, arquero nuevo);

void consultar_arquero(tvector v, int ocup);
void modificar_arquero(tvector v, int ocup);
void eliminar_arquero(tvector v, int &ocup);

void mostrar_arquero(arquero a);
void listar_recursivo(tvector v, int ocup, int pos);

int busqueda_binaria(tvector v, int ocup, tcad apodo);

//----------------------------------------------------
// VALIDACIONES DE ARQUERO
//----------------------------------------------------
bool signo_valido(tcad signo);
bool cadena_valida(tcad text);

//----------------------------------------------------
// GESTION DE LA DIANA
//----------------------------------------------------
void gestionar_diana(tmatriz diana, bool &existe_diana);

void generar_diana(tmatriz diana, bool &existe_diana);
void mostrar_diana(tmatriz diana);
void reiniciar_diana(tmatriz diana);

void asignar_zona(tmatriz diana, int fila, int col);
bool repetido(tmatriz diana, int numero, int fila, int col);
bool diana_valida(tmatriz diana);

int puntaje_casilla(int numero);
int distancia_centro(int fila, int columna);

//----------------------------------------------------
// PROPIEDADES NUMERICAS (usadas por la diana)
//----------------------------------------------------
bool es_primo(int n);
bool es_fibo(int n);
bool es_capicua(int n);
bool es_cuadrado_perfecto(int n);
bool es_niven(int n);

//----------------------------------------------------
// JUGAR / PARTIDA
//----------------------------------------------------
void gestionar_juego(tvector arqueros, int ocup, tmatriz diana, bool existe_diana, tParticipantes participantes, int &ocupParticipantes);

void elegir_arqueros(tvector v, int ocup, tParticipantes participantes, int &ocupParticipantes);
void mostrar_participantes(tvector v, tParticipantes participantes, int ocupParticipantes);

void iniciar_partida(tvector arqueros, int ocup, tmatriz diana, bool existe_diana, tParticipantes participantes, int ocupParticipantes);

void disparar(tmatriz diana, int &fila, int &columna);
void mostrar_estado(arquero a, int flecha);
float calcular_puntaje(t_Casillas casilla);
bool flecha_perfecta(t_Casillas casilla);

int buscar_ganador(tvector v, tParticipantes participantes, int ocupParticipantes, tmatriz diana);
int desempatar(tvector arqueros, tParticipantes participantes, int pos1, int pos2, tmatriz diana);

void actualizar_estadisticas(tvector v, tParticipantes participantes, int ocupParticipantes, int posGanador);

//----------------------------------------------------
// PODIO
//----------------------------------------------------
void cambio(int &a, int &b);
void podio(tvector a, int op, int ocup);
void mostrar_podio_recursivo(tvector a, tParticipantes pos, int cant, int indice);

//*****MAIN****

int main()
{
    srand(time(NULL));
    tvector arqueros;
    tmatriz diana; 
    tParticipantes participantes;
    bool existe_diana = false;
    int ocupado = -1, ocupParticipantes = -1;

    char opcion;
    do
    {
        menu_principal(opcion);
        switch (opcion)
        {
        case '1':
            gestionar_arqueros(arqueros, ocupado);
            break;
        case '2':
            gestionar_diana(diana, existe_diana);
            break;
        case '3':
            gestionar_juego(arqueros, ocupado, diana, existe_diana, participantes, ocupParticipantes);
            break;
        case '4':
            int op;
            menu_podio(op);
            podio(arqueros, op, ocupado);
            break;
        case '5':
            cout << "FIN DEL JUEGO" << endl;
            break;
        default:
            cout << "Opcion Incorrecta" << endl;
        }
    } while (opcion != '5');
    return 0;
}

void menu_principal(char &op)
{
    cout << "\n------------------------------" << endl;
    cout << "\n    TORNEO DE ARTEMISA" << endl;
    cout << "\n------------------------------" << endl;

    cout << "\n1. Gestionar arqueros" << endl;
    cout << "2. Gestionar diana" << endl;
    cout << "3. Jugar" << endl;
    cout << "4. Podio" << endl;
    cout << "5. Salir" << endl;
    cout << "\nSeleccione una opcion: ";
    cin >> op;
}

void menu_diana(char &op)
{
    cout << "\n------------------------------";
    cout << "\n      GESTION DIANA";
    cout << "\n------------------------------";

    cout << "\na) Generar diana" << endl;
    cout << "b) Mostrar diana" << endl;
    cout << "c) Volver";

    cout << "\nOpcion: ";
    cin >> op;
}

void menu_arqueros(char &op)
{
    cout << "\n------------------------------" << endl;
    cout << "\n    GESTION DE ARQUEROS" << endl;
    cout << "\n------------------------------" << endl;
    cout << "\na) Agregar arquero" << endl;
    cout << "b) Consultar arquero" << endl;
    cout << "c) Modificar arquero" << endl;
    cout << "d) Eliminar arquero" << endl;
    cout << "e) Listar arqueros" << endl;
    cout << "f) Volver" << endl;
    cout << "\nSeleccione opcion: ";
    cin >> op;
}

void menu_jugar(char &op)
{
    cout << "\n----------------------------";
    cout << "\n        JUGAR";
    cout << "\n----------------------------";

    cout << "\na) Elegir arqueros" << endl;
    cout << "b) Iniciar partida" << endl;
    cout << "c) Volver" << endl;

    cout << "\nOpcion: ";
    cin >> op;
}

void gestionar_arqueros(tvector v, int &ocup)
{
    char op;

    do
    {
        menu_arqueros(op);

        switch (op)
        {
        case 'a':
            agregar_arquero(v, ocup);
            break;

        case 'b':
            consultar_arquero(v, ocup);
            break;

        case 'c':
            modificar_arquero(v, ocup);
            break;

        case 'd':
            eliminar_arquero(v, ocup);
            break;

        case 'e':
            if (ocup >= 0)
                listar_recursivo(v, ocup, 0);
            else
                cout << "\nNo hay arqueros cargados" << endl;
            break;

        case 'f':
            break;

        default:
            cout << "Opcion invalida" << endl;
        }

    } while (op != 'f');
}

void gestionar_diana(tmatriz diana, bool &existe_diana)
{
    char op;

    do
    {
        menu_diana(op);

        switch (op)
        {
        case 'a':
            generar_diana(diana, existe_diana);
            break;

        case 'b':
            if (existe_diana==true)
                mostrar_diana(diana);
            else
                cout << "\nPrimero debe generar la diana." << endl;
            break;

        case 'c':
            break;

        default:
            cout << "\nOpcion invalida"<<endl;
        }

    } while (op != 'c');
}

void gestionar_juego(tvector arqueros, int ocup, tmatriz diana, bool existe_diana, tParticipantes participantes, int &ocupParticipantes)
{
    char op;

    do
    {
        menu_jugar(op);

        switch (op)
        {
        case 'a':
            ocupParticipantes = -1;
            elegir_arqueros(arqueros, ocup, participantes, ocupParticipantes);
            if (ocupParticipantes >= 0)
                mostrar_participantes(arqueros, participantes, ocupParticipantes);
            break;

        case 'b':
            iniciar_partida(arqueros, ocup, diana, existe_diana, participantes, ocupParticipantes);
            break;

        case 'c':
            break;

        default:
            cout << "\nOpcion invalida."<<endl;
        }

    } while (op != 'c');
}

// VALIDACIONES

bool cadena_valida(tcad text)
{
    return strlen(text) > 3;
}

bool signo_valido(tcad signo)
{
    bool validacion = false;

    if (strcmp(signo, "Aries") == 0 || strcmp(signo, "Tauro") == 0 ||
        strcmp(signo, "Geminis") == 0 || strcmp(signo, "Cancer") == 0 ||
        strcmp(signo, "Leo") == 0 || strcmp(signo, "Virgo") == 0 ||
        strcmp(signo, "Libra") == 0 || strcmp(signo, "Escorpio") == 0 ||
        strcmp(signo, "Sagitario") == 0 || strcmp(signo, "Capricornio") == 0 ||
        strcmp(signo, "Acuario") == 0 || strcmp(signo, "Piscis") == 0)
    {
        validacion = true;
    }
    return validacion;
}

//----------------------------------------------------
// BUSQUEDA BINARIA
//----------------------------------------------------

int busqueda_binaria(tvector v, int ocup, tcad apodo)
{
    int pri, ult, medio, posicion;
    bool encontrado;

    pri = 0;
    ult = ocup;
    encontrado = false;
    posicion = -1;
    while (encontrado == false && (pri <= ult))
    {
        medio = (pri + ult) / 2;

        if (strcmp(v[medio].apodo, apodo) == 0)
        {
            encontrado = true;
            posicion = medio;
        }
        else
        {
            if (strcmp(apodo, v[medio].apodo) < 0)
                ult = medio - 1;
            else
                pri = medio + 1;
        }
    }
    return posicion;
}

//----------------------------------------------------
// AGREGAR
//----------------------------------------------------

void agregar_arquero(tvector v, int &ocup)
{
    if (ocup == MAX - 1)
    {
        cout << "Vector lleno." << endl;
    }
    else
    {
        arquero nuevo;
        do
        {
            cout << "\nApellido: ";
            cin >> nuevo.apellido;
            if (!cadena_valida(nuevo.apellido))
                cout << "\nError: los datos deben tener mas de 3 caracteres." << endl;
        } while (!cadena_valida(nuevo.apellido));

        do
        {
            cout << "Nombre: ";
            cin >> nuevo.nombre;
            if (!cadena_valida(nuevo.nombre))
                cout << "\nError: los datos deben tener mas de 3 caracteres." << endl;
        } while (!cadena_valida(nuevo.nombre));

        do
        {
            cout << "Apodo: ";
            cin >> nuevo.apodo;
            if (!cadena_valida(nuevo.apodo))
                cout << "\nError: los datos deben tener mas de 3 caracteres." << endl;
        } while (!cadena_valida(nuevo.apodo));

        do
        {
            cout << "Signo zodiacal: ";
            cin >> nuevo.signo_zodiacal;
            if (!signo_valido(nuevo.signo_zodiacal))
                cout << "\nError: signo zodiacal invalido." << endl;
        } while (!signo_valido(nuevo.signo_zodiacal));
        if (busqueda_binaria(v, ocup, nuevo.apodo) != -1)
        {
            cout << "\nError: el apodo ya existe." << endl;
        }
        else
        {
            nuevo.dracmas = 0;
            nuevo.mayor_puntaje = 0;
            nuevo.cant_torneos_ganados = 0;
            nuevo.cant_torneos_disputados = 0;

            insertar_ordenado(v, ocup, nuevo);
            cout << "\nArquero agregado correctamente." << endl;
        }
    }
}

void insertar_ordenado(tvector v, int &ocup, arquero nuevo)
{
    int i, j;
    if (ocup == MAX - 1)
        cout << "Vector Lleno" << endl;
    else
    {
        i = 0;
        while ((i <= ocup) && strcmp(v[i].apodo, nuevo.apodo) < 0)
            i++;
        j = ocup;
        while (j >= i)
        {
            v[j + 1] = v[j];
            j = j - 1;
        }
        v[i] = nuevo;
        ocup = ocup + 1;
    }
}

void mostrar_arquero(arquero a)
{
    cout << "\n----------------------------\n";
    cout << "\nApellido: " << a.apellido;
    cout << "\nNombre: " << a.nombre;
    cout << "\nApodo: " << a.apodo;
    cout << "\nSigno: " << a.signo_zodiacal;
    cout << "\nDracmas: " << a.dracmas;
    cout << "\nMayor puntaje: " << a.mayor_puntaje;
    cout << "\nTorneos ganados: " << a.cant_torneos_ganados;
    cout << "\nTorneos disputados: " << a.cant_torneos_disputados << endl;
    cout << "\n----------------------------\n";
}

void consultar_arquero(tvector v, int ocup)
{
    tcad apodo;
    int pos;

    if (ocup == -1)
    {
        cout << "\nNo hay arqueros cargados."<<endl;
    }
    else
    {
        cout << "\nIngrese el apodo: ";
        cin >> apodo;

        pos = busqueda_binaria(v, ocup, apodo);

        if (pos == -1)
            cout << "\nArquero inexistente."<<endl;
        else
            mostrar_arquero(v[pos]);
    }
}

void modificar_arquero(tvector v, int ocup)
{
    tcad apodo;
    int pos;

    if (ocup == -1)
    {
        cout << "\nNo hay arqueros cargados." << endl;
    }
    else
    {
        cout << "\nApodo del arquero: ";
        cin >> apodo;

        pos = busqueda_binaria(v, ocup, apodo);

        if (pos == -1)
        {
            cout << "\nArquero inexistente." << endl;
        }
        else
        {
            do
            {
                cout << "Nuevo apellido: ";
                cin >> v[pos].apellido;
                if (!cadena_valida(v[pos].apellido))
                    cout << "Apellido invalido" << endl;
            } while (!cadena_valida(v[pos].apellido));

            do
            {
                cout << "Nuevo nombre: ";
                cin >> v[pos].nombre;
                if (!cadena_valida(v[pos].nombre))
                    cout << "Nombre invalido" << endl;
            } while (!cadena_valida(v[pos].nombre));

            do
            {
                cout << "Nuevo signo zodiacal: ";
                cin >> v[pos].signo_zodiacal;
                if (!signo_valido(v[pos].signo_zodiacal))
                    cout << "Signo invalido." << endl;
            } while (!signo_valido(v[pos].signo_zodiacal));
            cout << "\nArquero modificado correctamente." << endl;
        }
    }
}

void eliminar_arquero(tvector v, int &ocup)
{
    tcad apodo;
    int pos;
    int i;

    if (ocup == -1)
    {
        cout << "\nNo hay arqueros cargados." << endl;
    }
    else
    {
        cout << "\nApodo del arquero: ";
        cin >> apodo;

        pos = busqueda_binaria(v, ocup, apodo);

        if (pos == -1)
        {
            cout << "\nArquero inexistente." << endl;
        }
        else
        {
            for (i = pos; i < ocup; i++)
            {
                v[i] = v[i + 1];
            }

            ocup--;

            cout << "\nArquero eliminado." << endl;
        }
    }
}

void listar_recursivo(tvector v, int ocup, int pos)
{
    if (pos <= ocup)
    {
        mostrar_arquero(v[pos]);
        listar_recursivo(v, ocup, pos + 1);
    }
}

bool repetido(tmatriz diana, int numero, int fila, int col)
{
    int i, j;
    bool enc = false;

    // Revisar todas las filas anteriores
    for(i = 0; i < fila; i++)
    {
        for(j = 0; j < COL; j++)
        {
            if(diana[i][j].numero == numero)
                enc = true;
        }
    }

    // Revisar solamente las columnas anteriores de la fila actual
    for(j = 0; j < col; j++)
    {
        if(diana[fila][j].numero == numero)
            enc = true;
    }

    return enc;
}

void asignar_zona(tmatriz diana, int fila, int col)
{
    // Centro
    if (fila == 4 && col == 4)
    {
        diana[fila][col].dracmas = 50;
        diana[fila][col].puntaje_zona = 100;
    }
    else
    {
        // Primer anillo
        if (fila >= 3 && fila <= 5 && col >= 3 && col <= 5)
        {
            diana[fila][col].dracmas = 30;
            diana[fila][col].puntaje_zona = 50;
        }
        else
        { // Segundo anillo
            if (fila >= 2 && fila <= 6 && col >= 2 && col <= 6)
            {
                diana[fila][col].dracmas = 20;
                diana[fila][col].puntaje_zona = 30;
            }
            else
            { // Tercer anillo
                if (fila >= 1 && fila <= 7 && col >= 1 && col <= 7)
                {
                    diana[fila][col].dracmas = 15;
                    diana[fila][col].puntaje_zona = 20;
                }
                else
                {
                    diana[fila][col].dracmas = 10;
                    diana[fila][col].puntaje_zona = 10;
                }
            }
        }
    }
}

bool diana_valida(tmatriz diana)
{
    int i, j;

    bool primo = false;
    bool fibonacci = false;
    bool capicua = false;
    bool cuadrado = false;
    bool niven = false;

    for (i = 0; i < FILA; i++)
    {
        for (j = 0; j < COL; j++)
        {
            if (es_primo(diana[i][j].numero))
                primo = true;

            if (es_fibo(diana[i][j].numero))
                fibonacci = true;

            if (es_capicua(diana[i][j].numero))
                capicua = true;

            if (es_cuadrado_perfecto(diana[i][j].numero))
                cuadrado = true;

            if (es_niven(diana[i][j].numero))
                niven = true;
        }
    }
    return primo == true && fibonacci == true && capicua == true && cuadrado == true && niven == true;
}

void generar_diana(tmatriz diana, bool &existe_diana)
{
    int i, j;
    int numero;

    do
    {
        for (i = 0; i <= FILA - 1; i++)
        {
            for (j = 0; j <= COL - 1; j++)
            {
                do
                {
                    numero = rand() % (999 - 1 + 1) + 1; // (ls-li+1)+li//rand()%100->0..99
                } while (repetido(diana, numero, i, j)==true);

                diana[i][j].numero = numero;
                diana[i][j].ocupada = false;

                // Asigna dracmas y puntaje de zona
                asignar_zona(diana, i, j);

                diana[i][j].puntaje_casilla = puntaje_casilla(numero);
            }
        }
    } while (diana_valida(diana) == false);
    existe_diana = true;
    cout << "\nDiana generada correctamente." << endl;
}

void mostrar_diana(tmatriz diana)
{
    int i, j;

    cout << endl;

    for (i = 0; i <= FILA - 1; i++)
    {
        for (j = 0; j <= COL - 1; j++)
        {
            if (diana[i][j].ocupada)
            {
                cout << "[ X ] ";
            }
            else
            {
                cout << "[" << setw(3) << diana[i][j].numero << "] ";
            }
        }
        cout << endl;
    }
}



bool es_primo(int num)
{
    int i, cont = 0;
    for (i = 1; i <= num; i++)
    {
        if (num % i == 0)
            cont++;
    }
    return cont == 2;
}

bool es_capicua(int num)
{
    int dig, inv = 0, aux = num;
    while (aux > 0)
    {
        dig = aux % 10;
        inv = inv * 10 + dig;
        aux = aux / 10;
    }
    return num == inv;
}

bool es_niven(int n)
{
    int suma = 0;
    int aux = n;

    while (aux > 0)
    {
        suma = suma + aux % 10;
        aux = aux / 10;
    }

    return suma != 0 && n % suma == 0;
}

bool es_cuadrado_perfecto(int n)
{
    int i = 1;
    bool es_cuad = false;

    while (i * i <= n && es_cuad == false)
    {
        if (i * i == n)
            es_cuad = true;
        i++;
    }

    return es_cuad;
}

bool es_fibo(int n)
{
    int a = 1, b = 1, aux;

    if (n == 1)
        return true;

    while (b < n)
    {
        aux = a + b;
        a = b;
        b = aux;
    }
    return b == n;
}

int puntaje_casilla(int numero)
{
    int puntaje = 0;

    if (es_niven(numero))
        puntaje = puntaje + 40;
    else
    {
        if (es_cuadrado_perfecto(numero))
            puntaje = puntaje + 30;
        else
        {
            if (es_capicua(numero))
                puntaje = puntaje + 25;
            else
            {
                if (es_fibo(numero))
                    puntaje = puntaje + 20;
                else
                {
                    if (es_primo(numero))
                        puntaje = puntaje + 10;
                }
            }
        }
    }
    return puntaje;
}

bool participante_repetido(tParticipantes participantes, int ocupParticipantes, int posicion)
{
    bool repetido = false;
    int i = 0;

    while (i <= ocupParticipantes && repetido == false)
    {
        if (participantes[i] == posicion)
            repetido = true;
        else
            i++;
    }

    return repetido;
}

void elegir_arqueros(tvector v, int ocup, tParticipantes participantes, int &ocupParticipantes)
{
    tcad apodo;
    int pos;
    char op;

    if (ocup < 1)
    {
        cout << "\nDebe haber al menos 2 arqueros registrados." << endl;
    }
    else
    {
        do
        {
            cout << "\nApodo: ";
            cin >> apodo;

            pos = busqueda_binaria(v, ocup, apodo);

            if (pos == -1)
            {
                cout << "\nArquero inexistente."<<endl;
            }
            else
            {
                if (participante_repetido(participantes, ocupParticipantes, pos))
                {
                    cout << "\nEse arquero ya fue seleccionado."<<endl;
                }
                else
                {
                    ocupParticipantes++;
                    participantes[ocupParticipantes] = pos;

                    cout << "\nArquero agregado al torneo."<<endl;
                }
            }

            cout << "\nAgregar otro arquero? (s/n): ";
            cin >> op;

        } while (op == 's' || op == 'S');

        if (ocupParticipantes < 1)
        {
            cout << "\nDebe seleccionar al menos dos arqueros." << endl;
            ocupParticipantes = -1;
        }
    }
}

void mostrar_participantes(tvector v, tParticipantes participantes, int ocupParticipantes)
{
    int i;

    cout << "\nPARTICIPANTES" << endl;

    for (i = 0; i <= ocupParticipantes; i++)
    {
        cout << i + 1 << ". " << v[participantes[i]].apodo << endl;
    }
}

void disparar(tmatriz diana, int &fila, int &columna)
{
    char tecla;

    cout << "\nPresione ENTER para disparar...";
    cin.ignore();
    cin.get(tecla); 

    do
    {
        fila = rand() % FILA;
        columna = rand() % COL;
    } while (diana[fila][columna].ocupada);

    diana[fila][columna].ocupada = true;
}

void mostrar_estado(arquero a, int flecha)
{
    cout << "\n==============================";
    cout << "\nTurno de: " << a.apodo << endl;
    cout << "Dracmas: " << a.dracmas << endl;
    cout << "Puntaje actual: " << a.puntaje_actual << endl;
    cout << "Flecha " << flecha << " de 5";
    cout << "\n==============================\n";
}

float calcular_puntaje(t_Casillas casilla)
{
    return casilla.dracmas + (0.5 * casilla.puntaje_zona + 0.3 * casilla.puntaje_casilla) * 100;
}


void iniciar_partida(tvector arqueros, int ocup, tmatriz diana, bool existe_diana, tParticipantes participantes, int ocupParticipantes)
{
    int ronda, i, pos, fila, columna;
    bool alguien_acerto_centro = false;
    int posGanador;

    if (existe_diana==false)
    {
        cout << "\nPrimero debe generar la diana." << endl;
    }
    else
    {
        if (ocupParticipantes < 1)
        {
            cout << "\nDebe elegir al menos 2 arqueros antes de jugar." << endl;
        }
        else
        {
            reiniciar_diana(diana);

            for (i = 0; i <= ocupParticipantes; i++)
            {
                arqueros[participantes[i]].puntaje_actual = 0;
                arqueros[participantes[i]].dracmas = 0;
            }

            for (ronda = 1; ronda <= 5 && alguien_acerto_centro==false; ronda++)
            {
                cout << "\n====================================";
                cout << "\n          RONDA " << ronda;
                cout << "\n====================================\n";

                for (i = 0; i <= ocupParticipantes && alguien_acerto_centro==false; i++)
                {
                    pos = participantes[i];

                    mostrar_estado(arqueros[pos], ronda);
                    mostrar_diana(diana);

                    disparar(diana, fila, columna);

                    t_Casillas casilla = diana[fila][columna];

                    arqueros[pos].dracmas = arqueros[pos].dracmas + casilla.dracmas;
                    arqueros[pos].puntaje_actual = arqueros[pos].puntaje_actual + calcular_puntaje(casilla);

                    cout << "\nImpacto en la posicion [" << fila << "][" << columna << "]";
                    cout << "\nNumero obtenido: " << casilla.numero;
                    cout << "\nDracmas ganadas: " << casilla.dracmas;
                    cout << "\nPuntaje de zona: " << casilla.puntaje_zona;
                    cout << "\nPuntaje adicional: " << casilla.puntaje_casilla;
                    cout << "\nDracmas acumuladas: " << arqueros[pos].dracmas;
                    cout << "\nPuntaje acumulado: " << arqueros[pos].puntaje_actual << endl;

                    if (flecha_perfecta(casilla)==true)
                    {
                        alguien_acerto_centro = true;
                        posGanador = i;

                        cout << "\n***********************************";
                        cout << "\n      ¡FLECHA PERFECTA!";
                        cout << "\nEl torneo ha finalizado.";
                        cout << "\n***********************************\n";
                    }
                }
            }
            
            if (alguien_acerto_centro==false)
            {
                posGanador = buscar_ganador(arqueros, participantes, ocupParticipantes, diana);
            }

            actualizar_estadisticas(arqueros, participantes, ocupParticipantes, posGanador);

            cout << "\n====================================";
            cout << "\n      CAMPEON DEL TORNEO";
            cout << "\n====================================";
            cout << "\nArquero: " << arqueros[participantes[posGanador]].apodo;
            cout << "\nPuntaje final: " << arqueros[participantes[posGanador]].puntaje_actual;
            cout << "\nDracmas obtenidas: " << arqueros[participantes[posGanador]].dracmas;
            cout << "\n====================================\n";
        }
    }
}

bool flecha_perfecta(t_Casillas casilla)
{
    // la casilla central es la unica con puntaje_zona == 100 (ver asignar_zona)
    return casilla.puntaje_zona == 100;
}

int buscar_ganador(tvector v, tParticipantes participantes, int ocupParticipantes, tmatriz diana)
{
    int posGanador = 0;
    int i;

    for (i = 1; i <= ocupParticipantes; i++)
    {
        if (v[participantes[i]].puntaje_actual > v[participantes[posGanador]].puntaje_actual)
        {
            posGanador = i;
        }
        else
        {
            if (v[participantes[i]].puntaje_actual == v[participantes[posGanador]].puntaje_actual)
            {
                posGanador = desempatar(v, participantes, posGanador, i, diana);
            }
        }
    }
    return posGanador;
}

void actualizar_estadisticas(tvector v, tParticipantes participantes, int ocupParticipantes, int posGanador)
{
    int i, pos;

    for (i = 0; i <= ocupParticipantes; i++)
    {
        pos = participantes[i];
        v[pos].cant_torneos_disputados++;
    }

    pos = participantes[posGanador];
    v[pos].cant_torneos_ganados++;

    if (v[pos].puntaje_actual > v[pos].mayor_puntaje)
        v[pos].mayor_puntaje = v[pos].puntaje_actual;
}

void reiniciar_diana(tmatriz diana)
{
    int i, j;

    for (i = 0; i <= FILA - 1; i++)
    {
        for (j = 0; j <= COL - 1; j++)
        {
            diana[i][j].ocupada = false;
        }
    }
}

void menu_podio(int &op)
{
    do
    {
        cout << "\n------ PODIO ------";
        cout << "\n1. Orden creciente" << endl;
        cout << "2. Orden decreciente" << endl;
        cout << "\nOpcion: ";
        cin >> op;
        if(op!=1 && op!=2)
            cout<<"Ingrese una opcion valida"<<endl;
    } while (op!=1 && op!=2);
}

void cambio(int &a, int &b)
{
    int aux;
    aux = a;
    a = b;
    b = aux;
}

void podio(tvector a, int op, int ocup)
{
    tPosiciones pos;
    int cant = 0;
    int i;

    // Guardar solamente los arqueros que ganaron al menos un torneo
    for (i = 0; i <= ocup; i++)
    {
        if (a[i].cant_torneos_ganados > 0)
        {
            pos[cant] = i;
            cant++;
        }
    }

    if (cant == 0)
    {
        cout << "\nNo hay arqueros con torneos ganados."<<endl;
    }
    else
    {
        // Ordenar por mayor_puntaje
        bool ordenado;
        int pri, ult;
        ordenado = false;
        pri = 0;
        ult = cant - 1;
        if (op == 1) // Orden creciente
        {
            while (ordenado == false && pri < ult)
            {
                ordenado = true;

                // Derecha -> Izquierda
                for (i = ult; i >= pri + 1; i--)
                {
                    if (a[pos[i]].mayor_puntaje < a[pos[i - 1]].mayor_puntaje)
                    {
                        cambio(pos[i], pos[i - 1]);
                        ordenado = false;
                    }
                }

                pri++;

                if (ordenado == false)
                {
                    ordenado = true;

                    // Izquierda -> Derecha
                    for (i = pri; i <= ult - 1; i++)
                    {
                        if (a[pos[i]].mayor_puntaje > a[pos[i + 1]].mayor_puntaje)
                        {
                            cambio(pos[i], pos[i + 1]);
                            ordenado = false;
                        }
                    }
                    ult--;
                }
            }
        }
        else // Orden decreciente
        {
            ordenado = false;
            pri = 0;
            ult = cant - 1;

            while (ordenado == false && pri < ult)
            {
                ordenado = true;

                // Derecha -> Izquierda
                for (i = ult; i >= pri + 1; i--)
                {
                    if (a[pos[i]].mayor_puntaje > a[pos[i - 1]].mayor_puntaje)
                    {
                        cambio(pos[i], pos[i - 1]);
                        ordenado = false;
                    }
                }

                pri++;

                if (ordenado == false)
                {
                    ordenado = true;

                    // Izquierda -> Derecha
                    for (i = pri; i <= ult - 1; i++)
                    {
                        if (a[pos[i]].mayor_puntaje < a[pos[i + 1]].mayor_puntaje)
                        {
                            cambio(pos[i], pos[i + 1]);
                            ordenado = false;
                        }
                    }

                    ult--;
                }
            }
        }

        cout << "\n========== PODIO =========="<<endl;
        mostrar_podio_recursivo(a, pos, cant, 0);
    }
}

// Calcula la distancia al centro utilizando la distancia Manhattan.
int distancia_centro(int fila, int columna)
{
    int difFila, difColumna;

    difFila = fila - 4;
    if (difFila < 0)
        difFila = difFila * -1;

    difColumna = columna - 4;
    if (difColumna < 0)
        difColumna = difColumna * -1;

    return difFila + difColumna;
}

int desempatar(tvector arqueros, tParticipantes participantes, int pos1, int pos2, tmatriz diana)
{
    int fila1, col1;
    int fila2, col2;

    int dist1;
    int dist2;
    int pos_Ganador;

    cout << "\n******** DESEMPATE ********"<<endl;

    do
    {
        cout << "\nTurno de " << arqueros[participantes[pos1]].apodo;
        disparar(diana, fila1, col1);

        cout << "\nTurno de " << arqueros[participantes[pos2]].apodo;
        disparar(diana, fila2, col2);

        dist1 = distancia_centro(fila1, col1);
        dist2 = distancia_centro(fila2, col2);

        cout << "\nDistancia " << arqueros[participantes[pos1]].apodo << ": " << dist1;

        cout << "\nDistancia " << arqueros[participantes[pos2]].apodo << ": " << dist2;

        if (dist1 == dist2)
            cout << "\nEmpate... repiten el disparo."<<endl;

    } while (dist1 == dist2);

    if (dist1 < dist2)
        pos_Ganador=pos1;
    else
        pos_Ganador=pos2;

    return pos_Ganador;
}

void mostrar_podio_recursivo(tvector a, tPosiciones pos, int cant, int indice)
{
    if (indice < cant && indice < 3)
    {
        cout << "\nPuesto " << indice + 1 << endl;

        mostrar_arquero(a[pos[indice]]);

        mostrar_podio_recursivo(a, pos, cant, indice + 1);
    }
}