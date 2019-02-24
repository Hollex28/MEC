#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <NIDAQmx.h>


void main(void){

	TaskHandle TareaEscritura;
	int32 error = 0;
	error = DAQmxCreateTask("TareaEscritura", &TareaEscritura);
	if (error != 0){
		printf("1");
	}
	error = DAQmxCreateAOVoltageChan(TareaEscritura, "Dev5/ao0","",-10,10,DAQmx_Val_Volts,NULL);
	if (error != 0){
		printf("2");
	}
	error = DAQmxStartTask(TareaEscritura);
	if (error != 0){
		printf("3");
	}
	error = DAQmxWriteAnalogScalarF64(TareaEscritura, 0, -1, 0, NULL);
	if (error != 0){
		printf("4");
	}
	error = DAQmxStopTask(TareaEscritura);
	if (error != 0){
		printf("5");
	}
	error = DAQmxClearTask(TareaEscritura);
	if (error != 0){
		printf("6");
	}
	else{ printf("funca"); }
	Sleep(5000);


}