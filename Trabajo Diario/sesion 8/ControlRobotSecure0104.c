#pragma config(Sensor, S3,     lightSensor,         sensorLightActive)
#pragma config(Sensor, S4,     sonarSensor,         sensorSONAR)
//Variables Globales
bool MarchaAtrasz = false;
bool Recogiendo = false;






//======================================================================================================
task Buscar() { //Debajo de MarchaAtras,Sensores
  //StopTask(MarchaAtras);
bool avance = false
  while(1){
    if(avance){
      motor[motorA] = 70;
		  motor[motorB] = 70;
		  avance = false;
		  wait10Msec(100);
		}
    else{
   		  motor[motorA] = 30;
		    motor[motorB] = 60;
		    wait10Msec(300);
		    avance = true;
		  }


  }
  return;
}
//==========================================================================================================
task MarchaRecojer(){
  StopTask(Buscar);
  Recogiendo = true;
  while(1){
    motor[motorA] = 70;
    motor[MotorB]= 70;
  }
}

//========================================================================================================
task MarchaAtras(){
  StopTask(MarchaRecojer);
  StopTask(Buscar);
  motor[motorA] = - 50;
  motor[MotorB]= - 50;
  wait10Msec(200);
  Recogiendo = false;
  MarchaAtrasz=false;
  startTask(Buscar);
}

//==========================================================
task Sensores() //Debajo de MarchaAtras y Marcha Recoger y encima de Main
{
   wait1Msec(20);
   int distance_in_cm = 60;   // Create variable 'distance_in_cm' and initialize it to 20(cm).
   while(true)   // While the reading is greater than 45 (a light surface):  NOTE- make this less than to detect light surfaces.
   {
      wait1Msec(20);
      if (SensorValue[lightSensor] > 45){
        if(MarchaAtrasz==false){
          startTask(MarchaAtras);
          MarchaAtrasz=true;
        }
      }
      if (SensorValue[sonarSensor] < distance_in_cm){
        if(MarchaAtrasz == false && Recogiendo == false){
            startTask(MarchaRecojer);
            PlaySound(soundBeepBeep);
          }
      }
    }
}
//==============================================================================================

task main()
{
  StartTask(Buscar);                             // Start Task Buscar.
  StartTask(Sensores);                             //Activar Sensores

  while(true)
  {
    wait1Msec(300);                                 // Allow for a short wait, freeing up the CPU for other tasks.

    nxtDisplayCenteredBigTextLine(0, "TASK M");     // Display that Main is running.
  }
  return;
}

//==========================================================================================================================================
