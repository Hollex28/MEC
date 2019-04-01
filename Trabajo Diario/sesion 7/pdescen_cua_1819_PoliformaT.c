#pragma config(Motor,  motorA,          ,              tmotorNormal, openLoop, encoder)
#pragma config(Motor,  motorB,          ,              tmotorNormal, openLoop, encoder)
#pragma config(Motor,  motorC,          ,              tmotorNormal, openLoop, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma  platform(NXT)
#include "writeFile3.c"

const string  sFileName = "cuadrado.txt";

task main()
{
   long i = 0;                // contador
	 float tfinal=17.5;         // tiempo final trayectoria circular
	 long niteraciones=0;       // numero iteraciones para trayectoria circular
	 long ruedaAant=0;          // posicion anterior rueda derecha (motorA)
	 long ruedaAnue=0;          // posicion actual rueda derecha
	 long ruedaBant=0;          // posicion anterior rueda izquierda (motorB)
	 long ruedaBnue=0;          // posicion actual rueda izquierda
	 long acontrolA,acontrolB;  // acciones de control rueda derecha (motorA) e izquierda (motorB)

	 float wd, wi;              // velocidades angulares rueda derecha (wd) e izquierda (wi)
	 float vd, vi;              // velociades lineales rueda derecha (vd) e izquierda (vi)

	 float vd_ref, vi_ref;      // velocidades lineales de referencia
	 float wd_ref,wi_ref;       // velocidades angulares de referencia


	 float velLin_robot;        // velocidad lineal robot
	 float velAng_robot;        // velocidad angular robot

	 float xref;                // posicion de referencia eje X del robot
	 float yref;                // posicion de referencia eje Y del robot
	 float xrefante;            // posicion X iteracion anterior: para calculo velocidad X
	 float yrefante;            // posicion Y iteracion anterior: para calculo velocidad Y

	 float vel_xref=0.0;        // velocidad referencia eje X
	 float vel_yref=0.0;        // velocidad referencia eje y

	 float xp_punto=0.0;        // xp control cinematico
	 float yp_punto=0.0;        // yp control cinematico

	 float error_wd, error_wi;  // errores velocidades angulares (rueda derecha e izquierda)
   float errorcua=0.0;        //indice integral error cuadrado
   float ex=0.0, ey=0.0;      // errores posicion eje X e Y

	 float Kmp=9.4276;          // ganancia proporcional control dinamico velocidad angular ruedas robot
   float krp=10.0;             // ganancia proporcional control cinematico
   float krv=1.0;             // ganancia derivativa control cinematico

	 float theta=6.2832;        // orientacion inicial del robot (2*pi)
	 float x=-0.05;             // posicion inicial eje X del robot (-0.05m)
	 float y=-0.05;             // posicion inicial eje Y del robot (-0.05m)

	 float b=0.056;             //mm (separaci�n entre las ruedas)/2
	 float g=0.07;             //mm (punto descentrado para c�lculo la velocidad y posici�n

	 float pul2rad=0.0174533;   // pul2rad=2*pi/360=0.0174533: cad vuelta: 360 pulsos de encoder
	 float radiorueda=0.028;    // el radio de la rueda son 28 mm (0.028m)

	 float Ts=0.02;             // periodo de muestreo (en segundo) utilizado para el control

	 float incre=0.0041;          //incremento para la generacion de la trayectoria cuadrada de 1 metro de lado
	 //Variables P
	 float Tp = 0.0696;
	 float T0 = 0.0238;
   float K = 0.1445;
	 float Kp = Tp / (K*T0);
	 float q0=Kp;

   nMotorEncoder[motorA] = 0; // reseteamos el encoder de la rueda derecha
   nMotorEncoder[motorB] = 0; // reseteamos el encoder de la rueda izquierda
   Delete(sFileName,nIoResult);
   createTextFile(sFileName, 30000);


   i=0;
   niteraciones=(int)((tfinal)/Ts);

   while(i < niteraciones)    //bucle de control
      {
        ClearTimer(T1);

        // calculo de las referencias de posicion y velocidad: trayectoria CIRCULAR
 	if ((i>=0) && (i<226))
      	  {
            xref=incre*i;
            yref=0;
          }
      	if ((i>225) && (i<451))
      	  {
            xref=incre*225.0;
            yref=(i-225.0)*incre;
          }
       if ((i>450) && (i<676))
          {
            xref=(incre*225.0)-(incre*(i-450.0));
            yref=incre*225.0;
          }
        if ((i>675) && (i<901))
          {
            xref=0;
            yref=(incre*225.0)-(incre*(i-675.0));
          }

        // generacion referencias de velocidad
      	vel_xref=(xref-xrefante)/Ts;
      	vel_yref=(yref-yrefante)/Ts;

      	// obtener el valor de los encoders para ver cuanto se ha movido
        ruedaAnue=nMotorEncoder[motorA];
      	ruedaBnue=nMotorEncoder[motorB];

        // calculo de las velocidades angulares (rad/s) de las ruedas
		    wd=pul2rad*(ruedaAnue-ruedaAant)/Ts;
		    wi=pul2rad*(ruedaBnue-ruedaBant)/Ts;

		    // calculo de las velocidades lineales (mm/s) de las ruedas: v = w*radio
		    vd=wd*radiorueda;
		    vi=wi*radiorueda;

		    // ToDo: calculo de la velocidad lineal del robot
		    velLin_robot=(vd+vi)/2;

		    // ToDo: calculo de la velocidad angular del robot
		    velAng_robot=(vd-vi)/(2*b);

		    // calculo de la posicion X-Y y la orientacion del robot
		    x=x+velLin_robot*Ts*cos(theta);
		    y=y+velLin_robot*Ts*sin(theta);
		    theta=theta+velAng_robot*Ts;

		    // ToDo: calculo de la expresion del control cinematico del robot
		    xp_punto=krv*vel_xref+krp*(xref-(x+g*cos(theta)));
		    yp_punto=krv*vel_yref+krp*(yref-(y+g*sin(theta)));

	      // ToDo: calculo del modelo cinematico inverso del robot
		    vi_ref=(1/g)*(((g*cos(theta)+b*sin(theta))*xp_punto)+((g*sin(theta)-b*cos(theta))*yp_punto));
		    vd_ref=(1/g)*(((g*cos(theta)-b*sin(theta))*xp_punto)+((g*sin(theta)+b*cos(theta))*yp_punto));

		    // calculo de las velocidades angulares de referencia para el control dinamico
		    wd_ref=vd_ref/radiorueda;
		    wi_ref=vi_ref/radiorueda;

		    // calculo los errores de la velocidad angular de las ruedas
		    error_wd=wd_ref-wd;
		    error_wi=wi_ref-wi;

		    // calculo de las acciones de control a aplicar a cada rueda
        acontrolA=q0*error_wd;//P
        acontrolB=q0*error_wi;//P

		    // saturacion de las acciones de control
		    if (acontrolA>100)
			    {
				    acontrolA=100;
			    }
		    if (acontrolA<-100)
			    {
				    acontrolA=-100;
			    }
		    if (acontrolB>100)
			    {
				    acontrolB=100;
			    }
		    if (acontrolB<-100)
			    {
				    acontrolB=-100;
			    }

			  // aplicacion de las acciones de control a los motores
		    motor[motorA] = acontrolA;
		    motor[motorB] = acontrolB;

        // guardado de los valores de los encoder para la proxima iteracion
		    ruedaAant=ruedaAnue;
		    ruedaBant=ruedaBnue;

		    // guardado de los valores posiciones X-Y para la iteracion k-1: estimacion velocidad
		    xrefante=xref;
		    yrefante=yref;

		    // calculo indice integral error cuadratico
				ex=xref-x;
				ey=yref-y;
				errorcua=errorcua+sqrt(ex*ex+ey*ey);

        // escritura de los valores mas importantes en el fichero de datos
		    writeFloatNumber(xref);
		    writeFloatNumber(yref);
		    writeFloatNumber(x);
		    writeFloatNumber(y);
		    writeFloatNumber(errorcua);
		    writeNewLine();

		    i++;

		    // implementacion del periodo de muestreo e incrementamos el valor del contador
   	    while(time1(T1)<20)
		      {
		      	wait1Msec(4);
		       }
  }
  closeWriteTextFile();
}
