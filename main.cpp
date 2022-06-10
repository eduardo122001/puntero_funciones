#include <iostream>
#include <stdlib.h>
using namespace std;
// añadimos los typedef
typedef void(*drt)(int **&,int*&,int&);//direcciones(ptr a matriz,ptr a elemento de abolay,numero para el movimiento del abolay)
typedef int(*oper)(int*);//operandos aritmeticos(ptr del elemeto del abolay)

void horizonta(int **&m,int *&n,int &x){
    n=n+1;
    x=x+1;
}

void vertical(int **&m,int *&n,int &x){
    m=m+1;
    n=*m;
    n=n+x;

}

int aumentar(int *a){
  return (*a)+1;
}

int disminuir(int *a){
    return (*a)-1;
}

int main()
{
    int f=12;
    int c=5;
    //generamos la matriz
    int **m= new int *[f];
    int a=1;
    for(int **p=m;p<m+f;p++){
        *p=new int [c];
    }
     for(int **p=m;p<m+f;p++){
        for(int *q=*p;q<(*p+c);q++){
            *q=a;
            cout<<*q<<",";
            a++;
        }
        cout<<endl;
    }

    //generamos array dinamico para las direcciones
    int const b=15;
    bool bol=true;//nos ayudara para ajustar los 1 y 0
    int *control_direc=new int[b];
    int const h=5;int chosse[h]={1,5,2,5,2};int *g=chosse;//ptr a array para generar cierta cantidad del mismo elemento en el array dinamico
    for(int *i=control_direc;i<control_direc+b;i++){
        if(bol){//generamos y movemos el puntrero para todo 1
            for(int o=0;o<*g;o++){
                *i=1;
                i=i+1;
            }
            bol=false;
        }else{//generamos y movemos el puntrero para todo 0
            for(int o=0;o<(*g)-2;o++){
                *i=0;
                i=i+1;
            }
            bol=true;
        }
        g=g+1;//movimiento ptr para la cantidad de 1 y 0
    }
    int *res=control_direc;//ptr
    cout<<endl<<"CONTROL DE DIRECCIONES"<<endl;
   for(int *i=control_direc;i<control_direc+b;i++){cout<<*i<<",";}
    cout<<endl;
   //generamos array dinamico para las operaciones aritmeticas
    int *control_op=new int[b];
    bol=true;
    for(int *i=control_op;i<control_op+b;i++){
        *i=rand()%2;
    }
    cout<<endl<<"CONTROL DE OPERACIONES ARITMETICA"<<endl;
   for(int *i=control_op;i<control_op+b;i++){cout<<*i<<",";}
    int *j=control_op;
    //array de funciones de operaciones con su ptr
    oper ope[2]={aumentar,disminuir};
    int(*(*opep))(int*)=ope;
    //array de funciones de direcciones con su ptr
    drt dir[2]={vertical,horizonta};
    void (*(*diri))(int**&,int*&,int&)=dir;

    //ptr de la matriz y su array correspondiente
    int **u=m;
    int *v=*u;
    cout<<endl<<endl<<"INICIAMOS RECORRIDO Y OPERACIONES-->()operacion aritmetica dentro de los parentesis"<<endl;
    int t=0;//nos ayudara a mover el ptr de los array de la matriz
    for(int i =0;i<b;i++){
        cout<<"("<<(*(opep+*(control_op+i)))(v)<<")";//generamos la funcion operacion
        cout<<*v<<endl;
        (*(diri+*(control_direc+i)))(u,v,t);//generamos la funcion de direcciones
    }

    //empezamos a liberar la matriz y todos los arrays dinamicos
   for(int **p=m;p<m+f;p++){
        delete[] *p;
    }
    delete []m;
    delete[]control_op;
    delete[]control_direc;
}
