#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <iomanip>//libreria para setprecision "cuantos decimales quieres"
#include <fstream>//definir la libreria para escribrir y leer en archivos de texto
#define m 100
#define mstep 200

using namespace std;
float fo[m],f1[m],f2[m],rho[m],feq[m],x[m],dt=1.0,dx=1.0,csq,alpha=0.25,omega,twall=1.0;
int i,kk;
int main() 
{
    fstream file; //funcion para abrir escribir y leer en archivos
   /*
    ofstream: Stream clase para escribir en archivos
    ifstream: Corriente de clase para leer desde archivos
    fstream: Transmisión de clase para leer y escribir desde / a archivos.
   */
  x[0]=0;
  for(i=0;i<=m;i++){

        x[i]=x[i-1]+dx;

  }
  csq=dx*dx/(dt*dt);
  omega=1.0/(alpha/(dt*csq)+0.5);
  for(i=0;i<=m;i++){

    rho[i]=0.0; // Initial value of the domain temperature
    f1[i]=0.5*rho[i];
    f2[i]=0.5*rho[i];

  }
    for( kk = 1; kk <= mstep; kk++)
    {
       for(i=0;i<=m;i++){
            rho[i]=f1[i]+f2[i];
            feq[i]=0.5*rho[i];
                f1[i]=(1.-omega)*f1[i]+omega*feq[i];
                f2[i]=(1.-omega)*f2[i]+omega*feq[i];



    }

   for( i = 1; i < m; i++)
   {
       
       f1[m-i]=f1[m-i-1]; // f1 streaming
       f2[i-1]=f2[i]; // f2 streaming

   }
    f1[0]=twall-f2[0];// constant temperature boundary condition, x=0
    f1[m]=f1[m-1]; // adiabatic boundary condition, x=L
    f2[m]=f2[m-1];// adiabatic boundary condition, x=L

     
  }
  

    file.open("~\\home\\saul\\Documentos\\Kriket\\LB\\D1Q2\\resultcpp.txt");//adentro de open va la ruta del archivo separas carpetas con "\\"
    if (!file) {//comprobar si el archivo se puede abrir
        cout << "archivo no disponible";
        exit(1); // salir de la comprobación con error
    }
    for(i = 0; i < m; i++)
    {
        file<<setprecision(15)<<x[i]<<" "<<setprecision(15)<<rho[i]<<endl;
    }
    
   
    
/* ejemplo
    file << "Hello, World!";//la definicion file significa lo que hace en el archivo
*/
       file.close();//cierra el archivo
    
}