#include <iostream>
#include<cstring>
using namespace std;

struct Luchador{

	int id;
	char nombre[50];
	char apodo[50];
	float peso;
	int victorias;
	int derrotas;
	
	
};
struct Nodo{
    Luchador info;
    Nodo* sgte;
};

void crearArchivo() {
 FILE *archive = fopen("Luchadores.dat", "wb");
 Luchador l;
 l.id = 1;
 strcpy(l.nombre, "Martin");
 strcpy(l.apodo, "Tincho");
 l.peso = 80.500;
 l.victorias=3;
 l.derrotas=2;
 fwrite(&l, sizeof(Luchador), 1, archive);
 l.id = 2;
strcpy(l.nombre, "Carlos");
strcpy(l.apodo, "El Toro");
l.peso = 92.300;
l.victorias = 7;
l.derrotas = 1;
fwrite(&l, sizeof(Luchador), 1, archive);

l.id = 3;
strcpy(l.nombre, "Javier");
strcpy(l.apodo, "El Rayo");
l.peso = 75.800;
l.victorias = 5;
l.derrotas = 4;
fwrite(&l, sizeof(Luchador), 1, archive);

l.id = 4;
strcpy(l.nombre, "Diego");
strcpy(l.apodo, "La Mole");
l.peso = 105.600;
l.victorias = 10;
l.derrotas = 2;
fwrite(&l, sizeof(Luchador), 1, archive);

l.id = 5;
strcpy(l.nombre, "Lucas");
strcpy(l.apodo, "Pantera");
l.peso = 68.250;
l.victorias = 8;
l.derrotas = 3;
fwrite(&l, sizeof(Luchador), 1, archive);

l.id = 6;
strcpy(l.nombre, "Fernando");
strcpy(l.apodo, "El Titan");
l.peso = 88.900;
l.victorias = 6;
l.derrotas = 5;
fwrite(&l, sizeof(Luchador), 1, archive);

l.id = 7;
strcpy(l.nombre, "Matias");
strcpy(l.apodo, "Huracan");
l.peso = 79.400;
l.victorias = 4;
l.derrotas = 6;
fwrite(&l, sizeof(Luchador), 1, archive);
 fclose(archive);
}



Nodo* insertarOrdenado(Nodo*& lista,Luchador l)
{
	Nodo* p=new Nodo();
	p->info = l;
	p->sgte = NULL;
	
	if(lista==NULL || (l.victorias-l.derrotas) < (lista->info.victorias-lista->info.derrotas))
	{
		p->sgte=lista;
		lista=p;
	}
	else
	{ 
		Nodo* q=lista;
		while(q->sgte!=NULL &&(q->sgte->info.victorias-q->sgte->info.derrotas) < (l.victorias-l.derrotas))	
	   {
	   		q=q->sgte;
	   }	
	   p->sgte =q->sgte;
	   q->sgte = p;
	}
	return p;   
}
void mostrar(Nodo*& Lista)
{
    // Conservando la lista (no se libera memoria)

    Nodo* p = Lista;

    while (p != NULL)
    {
        cout << "ID: " << p->info.id << endl;
        cout << "Nombre: " << p->info.nombre << endl;
        cout << "Apodo: " << p->info.apodo << endl;
        cout << "Peso: " << p->info.peso << endl;
        cout << "Victorias: " << p->info.victorias << endl;
        cout << "Derrotas: " << p->info.derrotas << endl;
        cout << "---------------------------" << endl;
		
        p = p->sgte;
    }
}

int main(){
	
	Luchador Top_10[10];
	Nodo* lista=NULL;
	Nodo* aux;
	Luchador m;
	int opcion;
	crearArchivo();
	do
	{
	cout<<"1)Inscripción de Atleta"<<endl;
	if(opcion==1){
		 FILE *archive = fopen("Luchadores.dat", "rb");
		int i=0;
	while(fread(&m,sizeof(Luchador),1,archive)&&i!=7)
	{
		Top_10[i].id=m.id;
		strcpy(Top_10[i].nombre,m.nombre);
		strcpy(Top_10[i].apodo,m.apodo);
		Top_10[i].peso=m.peso;
		Top_10[i].victorias=m.victorias;
		Top_10[i].derrotas=m.derrotas;
		aux = insertarOrdenado(lista,m);		
		i++;
		cout<<i;
	}
	mostrar(lista);

	fclose(archive);
	}
	cout<<"2)Generar Main Card"<<endl;
	cout<<"3)Actualizar Récord"<<endl;
	cout<<"4)Guardar Gimnasio"<<endl;
	cout<<"5)Cargar Gimnasio"<<endl;
	cout<<"6)Salir"<<endl;
	cin>>opcion;
	}while(opcion!=6);

}
