#pragma config(Motor,  motorA,          ,              tmotorNormal, openLoop, encoder)
#pragma config(Motor,  motorB,          ,              tmotorNormal, openLoop, encoder)
#pragma config(Motor,  motorC,          ,              tmotorNormal, openLoop, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma  platform(NXT)
#include "writeFile.c"

const string  sFileName = "data111.txt";

task main()
{
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        /// INICIALIZACI�N DEL BUCLE DE CONTROL DE POSICI�N
        ///////////////////////////////////////////////////////////////////////////////////////////////////

        // espacio definici�n obligatoria de variables
	float Pos_final=6.0*2*pi; // valor final de la referencia de posici�n: 6 vueltas (en radianes)
	float tfinal=10.0;	  // tiempo (en segundos) para la generaci�n de la rampa: 10
	float refrad;		  // variable en que se calcular� la referencia de posici�n
	float erroractual=0.0;	  // error de posici�n instante k
	float errorcua=0.0;	  // indice error cuadr�tico
	float acActual=0.0;	  // valor acci�n de control instante k
	float pmuestreo=0.02;	  // periodo muestreo
	long i = 0;
	long niteraciones;
	float incre;

        // espacio definici�n libre de variables



        // inicializaci�n del proceso: reset encoder, fichero de datos, fin de bucle...
	nMotorEncoder[motorA] = 0;
	Delete(sFileName,nIoResult);
	createTextFile(sFileName, 30000);
        niteraciones=(int)((tfinal-2.0)/0.02); // n. de iteraciones: tiempo final (menos 2 segundo) dividido entre Ts (20 mS)
        incre=(float)(Pos_final/niteraciones); // incremento: valor final de la rampa dividivo por el n. de iteraciones



        ///////////////////////////////////////////////////////////////////////////////////////////////////
        /// PRIMER BUCLE DE CONTROL DE POSICI�N: GENERACI�N DE LA RAMPA
        ///////////////////////////////////////////////////////////////////////////////////////////////////

        while(i < niteraciones)  // 1� parte de la referencia: generaci�n de la rampa
         {

          // generaci�n de la referencia de posici�n.
          refrad=incre*i;


	  // obtener el valor de la posici�n actual (en radianes). MODIFICAR!!!
          posradactual=


	  // calcular del error de posici�n. MODIFICAR!!!
          erroractual=refrad-posradactual;


	  // calcular la acci�n de control. MODIFICAR!!!
	  acActual=


	  // saturar la acci�n de control para que est� en el rango -100 .. +100


	  // proporcionar la acci�n de control


	  // actualizaci�n de los valores del error y de la acci�n de control en instantes anteriores


	  // c�lculo de los �ndices de error cuadr�tico
	  errorcua=errorcua+erroractual*erroractual;


          // escritura de los valores significativos en el fichero de datos de salida
	  writeFloatNumber(refrad);
	  writeFloatNumber(posradactual);
	  writeFloatNumber(acActual);
	  writeFloatNumber(errorcua);
	  writeNewLine();

          // verificar el periodo de muestreo de 20mS


         i++;
      }


       ///////////////////////////////////////////////////////////////////////////////////////////////////
       /// SEGUNDO BUCLE DE CONTROL DE POSICI�N: MANTENER REF POSICI�N CONSTANTE DURANTE 2 SEG.
       ///////////////////////////////////////////////////////////////////////////////////////////////////

	i=0;
        niteraciones=(int)((2.0)/0.02); // n. de iteraciones: 2 segundos dividido entre Ts (20 mS)
	while(i < niteraciones)
        {

    	// obtener el valor de la posici�n actual (en radianes). MODIFICAR
        posradactual=


	// calcular el error de posici�n en funci�n de Pos_final. MODIFICAR
        erroractual=

	// calcular la acci�n de control. MODIFICAR
	acActual=

	// saturar la acci�n de control para que est� en el rango -100 .. +100


	// proporcionar la acci�n de control


	// actualizaci�n de los valores del error y de la acci�n de control en instantes anteriores


	// calcular de los �ndices de error cuadr�tico y absoluto
	errorcua=errorcua+erroractual*erroractual;

	// escritura de los valores significativos en el fichero de datos
	writeFloatNumber(Pos_final);
	writeFloatNumber(posradactual);
	writeFloatNumber(acActual);
	writeFloatNumber(errorcua);
	writeNewLine();

        // verificar el periodo de muestreo de 20mS



        i++;
    }

    closeWriteTextFile();

}