#pragma config(Sensor, S3,     lightSensor,         sensorLightActive)
#pragma config(Sensor, S4,     sonarSensor,         sensorSONAR)
#pragma config(Sensor, S1,     touchSensor,         sensorTouch)
#pragma config(Sensor, S2,     touchSensor2,         sensorTouch)
//Variables Globales
bool MarchaAtrasz = false;
bool Recogiendo = false;






//======================================================================================================
task OjodeSauron() { //Debajo de MarchaAtras,Sensores
  //StopTask(MarchaAtras);
bool avance = false;
Recogiendo = false;
nxtDisplayCenteredBigTextLine(0, "SAURON");
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
  nxtDisplayCenteredBigTextLine(0, "RECOGIENDO");
  StopTask(OjodeSauron);
  Recogiendo = true;
  while(1){
    motor[motorA] = 70;
    motor[MotorB]= 70;
  }
}

//========================================================================================================

task EmpujadEspartanos(){
  nxtDisplayCenteredBigTextLine(0, "ESPARTA!");
  StopTask(OjodeSauron);
  StopTask(MarchaRecojer);
  Recogiendo = true;
  while(1){
    motor[motorA] = 100;
    motor[MotorB]= 100;
  }
}

//========================================================================================================
task MarchaAtras(){
  nxtDisplayCenteredBigTextLine(0, "MarchaAtras");
  StopTask(MarchaRecojer);
  StopTask(OjodeSauron);
  StopTask(EmpujadEspartanos);
  motor[motorA] = - 50;
  motor[MotorB]= - 50;
  wait10Msec(200);
  Recogiendo = false;
  MarchaAtrasz=false;
  startTask(OjodeSauron);

}
//==================================================
task EsUnaTrampa(){
  nxtDisplayCenteredBigTextLine(0, "Trampa");
  Recogiendo = false;
  motor[motorA] = 100;
  motor[MotorB]= 60;
  wait10Msec(200);
  motor[motorA] = -60;
  motor[MotorB]= -100;
  wait10Msec(100);
  StartTask(OjodeSauron);


}

//==========================================================
task Sensores() //Debajo de MarchaAtras y Marcha Recoger y encima de Main
{
   wait1Msec(20);
   int distance_in_cm = 60;   // Create variable 'distance_in_cm' and initialize it to 20(cm).
   while(true)   // While the reading is greater than 45 (a light surface):  NOTE- make this less than to detect light surfaces.
   {
      wait1Msec(20);
      ////////////////////////////////////////////////////

      if (SensorValue[lightSensor] > 45){
        if(MarchaAtrasz==false){
          StopTask(EsUnaTrampa);
          startTask(MarchaAtras);
          MarchaAtrasz=true;
        }
      }
      ///////////////////////////////////////////////////

      if (SensorValue[sonarSensor] < distance_in_cm){
        if(MarchaAtrasz == false && Recogiendo == false){
            startTask(MarchaRecojer);
            PlaySound(soundBeepBeep);
          }
      }
      //////////////////////////////////////////////

      if (SensorValue(touchSensor) == 1)    // While the Touch Sensor is inactive (hasn't been pressed):
      {
        startTask(EmpujadEspartanos);
      }

      //////////////////////////////

       if (SensorValue(touchSensor2) == 1)    // While the Touch Sensor is inactive (hasn't been pressed):
      {
          StopTask(MarchaRecojer);
          StopTask(OjodeSauron);
          StopTask(EmpujadEspartanos);

          StopTask(MarchaAtras);
          startTask(EsUnaTrampa);
      }

    }
}


//==============================================================================================

task main()
{
  StartTask(OjodeSauron);                             // Start Task Buscar.
  StartTask(Sensores);                             //Activar Sensores

  while(true)
  {
    wait1Msec(300);                                 // Allow for a short wait, freeing up the CPU for other tasks.

    nxtDisplayCenteredBigTextLine(0, "TASK M");     // Display that Main is running.
  }
  return;
}

//==========================================================================================================================================
