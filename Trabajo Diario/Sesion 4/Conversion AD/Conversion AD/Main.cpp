#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <NIDAQmx.h>


void main(void){
	double lectura;
	TaskHandle TareaEscritura;
	int32 error = 0;
	error = DAQmxCreateTask("TareaEscritura", &TareaEscritura);
	if (error != 0){
		printf("1");
	}
	error = DAQmxCreateAIVoltageChan(TareaEscritura, "Dev5/ai0", "", DAQmx_Val_RSE, -10, 10, DAQmx_Val_Volts,NULL);
	if (error != 0){
		printf("2");
	}
	error = DAQmxStartTask(TareaEscritura);
	if (error != 0){
		printf("3");
	}
	for (int i = 0; i <= 1000; i++){
		error = DAQmxReadAnalogScalarF64(TareaEscritura, 0, &lectura, NULL);
		if (error != 0){
			printf("4");
		}
		else{ printf("iteracion Num %i  tiene valor %f \n", i,lectura);}
	}
	error = DAQmxStopTask(TareaEscritura);
	if (error != 0){
		printf("5");
	}
	error = DAQmxClearTask(TareaEscritura);
	if (error != 0){
		printf("6");
	}
	Sleep(1000);


}