#pragma config(Sensor, S3,     lightSensor,         sensorLightActive)
#pragma config(Sensor, S4,     sonarSensor,         sensorSONAR)
#pragma config(Sensor, S1,     touchSensor,         sensorTouch)
#pragma config(Sensor, S2,     touchSensor2,         sensorTouch)
//Variables Globales
bool MarchaAtrasz = false;
bool Recogiendo = false;
bool evasion = false;






//======================================================================================================
task Buscar() { //Debajo de MarchaAtras,Sensores
  //StopTask(MarchaAtras);
bool avance = false
  while(1){
    if(avance){
      motor[motorA] = 80;
		  motor[motorB] = 80;
		  avance = false;
		  wait10Msec(100);
		}
    else{
   		  motor[motorA] = 20;
		    motor[motorB] = 60;
		    wait10Msec(350);
		    avance = true;
		  }


  }
  return;
}

//========================================================
task Maniobras(){
   nxtDisplayCenteredBigTextLine(0, "Trampa");
  Recogiendo = false;
  evasion = true;
  motor[motorA] = 100;
  motor[MotorB]= 30;
  wait10Msec(200);
  motor[motorA] = -30;
  motor[MotorB]= -100;
  wait10Msec(100);
  evasion = false;
  StartTask(Buscar);
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

task EmpujadEspartanos(){
  StopTask(Buscar);
  StopTask(MarchaRecojer);
  Recogiendo = true;
  while(1){
    motor[motorA] = 100;
    motor[MotorB]=100;
  }
}

//========================================================================================================
task MarchaAtras(){
  StopTask(MarchaRecojer);
  StopTask(Buscar);
  StopTask(EmpujadEspartanos);
  StopTask(Maniobras);
  motor[motorA] = - 70;
  motor[MotorB]= - 70;
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
      if (SensorValue(touchSensor) == 1)    // While the Touch Sensor is inactive (hasn't been pressed):
      {
        startTask(EmpujadEspartanos);
        PlaySound(soundBeepBeep);
      }
      if (SensorValue(touchSensor2) == 1 && evasion == false)    // While the Touch Sensor is inactive (hasn't been pressed):
      {
        startTask(Maniobras);
        PlaySound(soundBeepBeep);
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

  }
  return;
}

//==========================================================================================================================================
