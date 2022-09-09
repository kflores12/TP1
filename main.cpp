#include <iostream>
#include <fstream>
using namespace std;

void puntouno(float m[][5], int dfil, string clientes[], string productos[]){
  const int dcol{5};
  int i, j;
  for(i = 0 ; i < dfil ; i++){
    cout << clientes[i] << ": ";
    for(j = 0 ; j < dcol ; j++){
      if(m[i][j] > 13000){
        cout << productos[j] <<"-";
      }
    }
    cout << endl;
  }
}



int puntodos(float m[][5], int dfil)
{
  const int dcol{5};
  int cliente, producto, posicion, guardar=0;
  for(cliente = 0 ; cliente < dfil ; cliente++)
  {
    int cant{};
    for(producto = 0 ; producto < dcol ; producto++)
    {
     if(m[cliente][producto] > 13000)
        cant++;
    }
    if(cant > guardar)
    {
          posicion = cliente;
          guardar = cant;
    }
  }
  return posicion;
}



void ordenardoble(float v[], int dim , string productosaux[])
{
  int i, pos, imin;
  for(pos = 0 ; pos < dim ; pos++)
  {
    imin = pos;
    for(i = pos+1 ; i < dim ; i++)
      if(v[i] < v[pos])
      imin = i;
      swap(v[pos], v[imin]);
  		swap(productosaux[pos], productosaux[imin]);
  }
}



int main(){
const int dfil{8};
const int dcol{5};
float matriz1[dfil][dcol]{}; //matriz para guardar KG entre cliente-producto
float matriz2[dfil][dcol]{}; //matriz para guardar KM entre cliente-producto
int vector1[dcol]{}; //vector que cuenta las entregas de cada producto, sin importar cliente
float vector2[dcol]{}; //vector para guardar la fila del mayor en el punto 2
string clientes[dfil]{}; //array para nombres de clientes
string productos[dcol]{}; //array para nombres de productos
string productosaux[dcol]{}; //array auxiliar para no alterar el original
ifstream archidatos;
ifstream archinombres;

//Leemos los dos archivos

archidatos.open("Datos.txt");
int cl, pr;
float kg, km;
while(archidatos >> cl >> pr >> kg >> km){
  matriz1[cl][pr] += kg;
  matriz2[cl][pr] += km;
  vector1[pr]++;
}
archidatos.close();

archinombres.open("Nombres.txt");
for(int i = 0 ; i < dfil && archinombres >> clientes[i] ; i++);
for(int j = 0 ; j < dcol && archinombres >> productos[j] ; j++);
archinombres.close();

//Primer punto

cout<< "Lista de combinaciones cliente-producto por encima de 13mil kg: " << endl;
puntouno(matriz1, dfil, clientes, productos);


cout<< endl << "-------------------------------------" << endl << endl;




//Segundo punto
int ipos = puntodos(matriz1, dfil);
cout<<"El cliente que tuvo mas productos por encima de los 13mil kg es: "<<clientes[ipos]<<endl;


//Guardamos la fila del cliente en un vector
for(int i = ipos ; i < ipos + 1 ; i++)
{
  for(int j = 0 ; j < dcol ; j++)
  {
    vector2[j] = matriz2[i][j];
  }
}

//copiamos el string productos en su auxiliar para no alterarlo
for(int i=0 ; i<dcol ; i++)
productosaux[i]=productos[i];


//llamamos a la funcion para ordenar el vector de manera ascendente con sus respectivos nombres
ordenardoble(vector2, dcol, productosaux);
for(int i = 0 ; i < dcol ; i++)
cout<< productosaux[i] << ": " << vector2[i] << endl;


cout<< endl << "-------------------------------------" << endl << endl;




//Tercer punto
//guardamos el nombre del producto con mayor recorrido del punto anterior en una variable

string save = productosaux[dcol-1];

//buscamos la posicion del producto en el vector string original

int posicion{};
for(int i = 0 ; i < dcol ; i++)
{
  if(productos[i] == save)
  {
    posicion = i;
  }
}

//usamos la posicion en el vector que guarda la cantidad de entregas por producto y mostramos en pantalla

cout << "Cantidad de entregas para el tipo de producto " << productos[posicion] << ": " << vector1[posicion] <<endl;









  return 0;
}
