#ifndef PARAMETROS_ROVER
#define PARAMETROS_ROVER

//El grado en el que cambian las ruedas cuando se mueven todas al un�sono.
//double GRADOS_RUEDAS=0.0;

//Para girar a la IZQUIERDA s�lo avanza el giro de las ruedas de la derecha.
double GRADOS_RUEDA_DERECHA=0.0;

//Para girar a la DERECHA s�lo avanza el giro de las ruedas de la izquierda.
double GRADOS_RUEDA_IZQUIERDA=0.0;


double GRADOS_GIRO_ROVER=0.0;

//Cuanto mayor sea este valor menos real ser� la frecci�n con el suelo, al menos que no se cambie tb el giro de las ruedas.
double AGARRE_SUELO=1;

double X=0.0;
double Z=0.0;

double MODO=0;

double intensidadDifusaLuz0=1.0;
double intensidadAmbientalLuz0=1.0;
double intensidadEspecularLuz0=0.0;

double intensidadDifusaLuz1=1.0;
double intensidadAmbientalLuz1=1.0;
double intensidadEspecularLuz1=0.0;

double intensidadLuz0=1.0;

double intensidadLuz1=1.0;


//Para el movimiento:

        double Cx;
        double Cz;

int gradosRotacionCoche;


//Normal directriz:

_vertex3f normalDirectriz;


#endif
