#include <iostream>
#include<cstring>
#include <conio.h> // para el get key

using namespace std;

//estructuras
struct Luchador{
    int id;
    char nombre[50];
    char apodo[50];
    float peso;
    int victorias;
    int derrotas;
};
struct nodo{
    Luchador info;
    nodo* sgte;
   
};

//Prototipos de la funcion
void actualizarRecord(nodo*);
void inscripcionAtleta(nodo*&, Luchador);
Luchador pop(nodo* &);
void push(nodo*&,Luchador);
nodo* buscar(nodo*, Luchador);
nodo* insertarOrdenado(nodo*&, Luchador);
nodo* insertarSinRepetir(nodo*&, Luchador);
void guardarDatos(nodo* &);
void cargarGimnasio(FILE*,nodo* &);
int generarMainCard(nodo*, Luchador[]);

int main(){
	Luchador luchador;
    Luchador top_10[10];
    Luchador top_5[5];

    nodo* lista = NULL;

	int opcion;

    do
    {
    cout << "1)Inscripcion de Atleta" << endl;
    cout << "2)Generar Main Card" << endl;
    cout << "3)Actualizar Record" << endl;
    cout << "4)Guardar Gimnasio" << endl;
    cout << "5)Cargar Gimnasio" << endl;
    cout << "6)Salir" << endl;

    cout << endl << "> ";
    cin>>opcion;

    system("cls");

    if(opcion==1)
	{
		inscripcionAtleta(lista,luchador);
	}
	if(opcion == 2)
    {
    	int x;
    	int cant = generarMainCard(lista, top_10);
    	if (cant == 0)
		{
			cout << "No hay luchadores disponibles para mostrar";
		}
		else
		{
			for(int i = 0; i < cant; i++)
			{
                cout << "LUCHADOR " << i+1 << endl;
                cout << "ID: " << top_10[i].id << endl;
                cout << "Nombre: " << top_10[i].nombre << endl;
                cout << "Apodo: " << top_10[i].apodo << endl;
                cout << "Peso: " << top_10[i].peso << endl;
                cout << "Victorias: " << top_10[i].victorias << endl;
                cout << "Derrotas: " << top_10[i].derrotas << endl << endl;
			}
            cout << "Presione una tecla para regresar al menu...";
		}

        _getch();
        system("cls");
	}
    if(opcion == 3)
	{
    	actualizarRecord(lista);
	}
	if(opcion == 4)
	{
    	guardarDatos(lista);
	}
	if(opcion == 5)
	{
		cout << "-----Datos Cargados del Gimnasio-----"<< endl;
		   FILE *archivo = fopen("Luchadores.dat", "rb");
    	cargarGimnasio(archivo,lista);
	}

    }while(opcion!=6);

	return 0;
}

//funciones
void inscripcionAtleta(nodo* &lista, Luchador luchador)
{
    cout << "Ingrese ID: ";
    cin >> luchador.id;

    cout << "Ingrese nombre: ";
    cin >> luchador.nombre;

    cout << "Ingrese apodo: ";
    cin >> luchador.apodo;

    cout << "Ingrese peso: ";
    cin >> luchador.peso;

    cout << "Ingrese cantidad de victorias: ";
    cin >> luchador.victorias;

    cout << "Ingrese cantidad de derrotas: ";
    cin >> luchador.derrotas;

    insertarSinRepetir(lista, luchador);
    system("cls");
    cout << "-----Luchador insertado correctamente-----";
    _getch();
    system("cls");
}

void actualizarRecord(nodo* lista)
{
    Luchador laux;
    cout << "Ingrese el nro de ID del luchador a buscar: ";
    cin >> laux.id;
    nodo *q;
    q = buscar(lista, laux);
    if(q==NULL){
        cout << "No se encontro el ID del luchador.";
    }else{
        cout << "ID: " << q->info.id << endl <<
        "Nombre:" << q->info.nombre << endl <<
        "Apodo: " << q->info.apodo << endl <<
        "Victorias: " << q->info.victorias << endl <<
        "Derrotas: " << q->info.derrotas << endl;
        cout << "Ingrese las victorias del luchador: ";
        cin >> q->info.victorias;
        cout << "Ingrese las Derrotas del luchador: ";
        cin >> q->info.derrotas;
        system("cls");
        cout << "Se modifico las victorias/derrotas del luchador exitosamente";
    }
    _getch();
    system("cls");
}

int generarMainCard(nodo* lista, Luchador top_10[])
{
    nodo* aux = lista;
    int i = 0;

    while(aux != NULL && i < 10)
    {
        top_10[i] = aux->info;
        aux = aux->sgte;
        i++;
    }
    return i;
}

void cargarGimnasio(FILE *archivo,nodo* &lista)
{
 
    Luchador l;

    while (fread(&l, sizeof(Luchador), 1, archivo))
    {
        insertarSinRepetir(lista, l);
    }

    fclose(archivo);
}

void guardarDatos(nodo* &lista)
{
	FILE* archivo = fopen("Luchadores.dat","wb");
	nodo* aux = lista;
	while(aux!=NULL)
	{
		fwrite(&aux->info, sizeof(Luchador), 1, archivo);
		aux = aux->sgte;
	}

	fclose(archivo);
}

nodo* insertarSinRepetir(nodo*& Lista, Luchador info)
{
	nodo* q;
	q = buscar(Lista,info);
	if(q==NULL)
	{
		q=insertarOrdenado(Lista,info);
	}
	return q;
}

nodo* insertarOrdenado(nodo*& lista, Luchador x)
{
    nodo* p = new nodo();
    p->info = x;
    p->sgte = NULL;

    int dif = x.victorias - x.derrotas;

    if(lista == NULL ||
       dif > (lista->info.victorias - lista->info.derrotas))
    {
        p->sgte = lista;
        lista = p;
    }
    else
    {
        nodo* q = lista;
        while(q->sgte != NULL &&
              (q->sgte->info.victorias - q->sgte->info.derrotas) > dif)
        {
            q = q->sgte;
        }
        p->sgte = q->sgte;
        q->sgte = p;
    }

    return p;
}

nodo* buscar(nodo* lista, Luchador x)
{
	nodo* aux=lista;
	while(aux!=NULL && aux->info.id!=x.id)
	{
		aux=aux->sgte;

	}
	return aux;
}

void push(nodo*&pila,Luchador info)
{
    nodo* p=new nodo();
    p->info=info;
    p->sgte=pila;
    pila=p;

}

Luchador pop(nodo* & pila)
{
    Luchador aux;
    aux= pila->info;
    nodo* p=pila;
    pila=p->sgte;
    delete p;
    return aux;
}
