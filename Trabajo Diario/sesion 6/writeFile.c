//******************************************************************************//
//                                                                              //
//                           ROBOTC WRITE FILE UTILITIES                        //
//                Robotics Academy of Carnegie Mellon University                //
//                                                                              //
//******************************************************************************//



//******************************************************************************//
//                                                                              //
//	                      VARIABLES DECLARATIONS                              	//
//                                                                              //
//******************************************************************************//


const int     MaxFileSize    = 60000;       // file size
bool bFirstNumberOnLine      = true;
TFileIOResult nIoResult      = ioRsltSuccess;
TFileHandle hFileWriteHandle = NOT_A_HANDLE;
TFileHandle hFileWriteHandle2 = NOT_A_HANDLE;

//******************************************************************************//
//                                                                              //
//	                      PROTOTYPES DECLARATIONS                              	//
//                                                                              //
//******************************************************************************//

bool createTextFile(const string &sFileName, int nFileSize);
bool openTextFile(const string &sFileName, int nFileSize);
void closeWriteTextFile();
void closeReadTextFile();
void writeNewLine();
long readtext(long conta);
void writeIntegerNumber(long  nNumber);
void writeFloatNumber(float fNumber);




//******************************************************************************//
//                                                                              //
//	              FILE AND MEASUREMENTS UTILITIES                              	//
//                                                                              //
//******************************************************************************//

bool createTextFile(const string &sFileName, int nFileSize)
{
	bFirstNumberOnLine = true;
	Delete(sFileName, nIoResult);
	OpenWrite(hFileWriteHandle, nIoResult, sFileName, nFileSize);
	return nIoResult == ioRsltSuccess;
}
bool openTextFile(const string &sFileName, int nFileSize)
{
	OpenRead(hFileWriteHandle2, nIoResult, sFileName, nFileSize);
	return nIoResult == ioRsltSuccess;
}
void closeWriteTextFile()
{
	Close(hFileWriteHandle, nIoResult);
	hFileWriteHandle = NOT_A_HANDLE;
}
void closeReadTextFile()
{
	Close(hFileWriteHandle, nIoResult);
	hFileWriteHandle = NOT_A_HANDLE;
}
// WRITES CARRIAGE RETURN AND NEW LINE CHARACTERS TO START A NEW LINE
void writeNewLine()
{
	WriteText(hFileWriteHandle, nIoResult, "\r\n");
	bFirstNumberOnLine = true;
	return;
}

long readtext(long conta)
{
	long npara;

	return ReadLong(hFileWriteHandle2, nIoResult, npara);
}



// IF REQUIRED, WRITES A DELIMITER BETWEEN NUMBERS ON SAME LINE
void writeDelimiterBetweenNumbers()
{
	if (bFirstNumberOnLine)
		bFirstNumberOnLine = false;
	else
		WriteText(hFileWriteHandle, nIoResult, " "); // delimiter
	return;
}

// WRITES AN INTEGER TO THE FILE OF THE ROBOT RESPONSE

void writeIntegerNumber(long nNumber)
{
	string sTemp;

	writeDelimiterBetweenNumbers();
	//
	// Modify format code ("%d") if you want to change the format -- say to line up the
	// columns for your application; e.g. "%5d" will make every number five characters.
	//
	StringFormat(sTemp, "%d", (long) nNumber);
	WriteText(hFileWriteHandle, nIoResult, sTemp);
	return;
}

// WRITES A FLOATING POINT NUMBER TO THE LINE
void writeFloatNumber(float fNumber)
{
	string sTemp;

	writeDelimiterBetweenNumbers();
	StringFormat(sTemp, "%.4f", fNumber);
	WriteText(hFileWriteHandle, nIoResult, sTemp);
	return;
}
