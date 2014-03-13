#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <direct.h>
#include <process.h>

#include "headers/IScanTailorPreProcessing.h"

#define GetCurrentDir _getcwd

using namespace std;

typedef IScanTailorPreProcessing* (* DLLFunction)(char *p, string p2);

int main()
{
    freopen("log.txt", "w", stdout);
    DLLFunction func;
    IScanTailorPreProcessing* preProcessingScanTailor;
    char cCurrentPath[FILENAME_MAX], finalPath[FILENAME_MAX]; // arrays of chars to hold the current path and the targeted path.
	int splitIndx; // used for splitting the path.
	string p; // temporarly used string to fix the paths.

	// locating current dir.
	if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath))){
		 printf("Could not locate the DIR!"); // if failed we return -1
		 return -1;
	}
	p = (string)cCurrentPath;

	p  = p + "\\bin\\Debug";
	cout << p;
	// copying the string to array of chars.
	for(int i = 0;i < p.size(); i++){
		finalPath[i] = p[i];
	}
	finalPath[p.size()]='\0';
	HINSTANCE DLL_Library = LoadLibraryA((p + "\\dlls\\scanTailorPreProcessing.dll").c_str());
	// check if DLL is loaded successfully.
	if(DLL_Library == NULL){
		cout << "Failed to load." << endl; // if load fails we free the library and return -2.
		FreeLibrary(DLL_Library);
		return -2;
	}

	func = (DLLFunction)GetProcAddress(DLL_Library, "getInstance"); // get a handle to the function
	if(!func){ // check if function located.
		cout << "Failed to locate the function" << endl; // if faild we return -3, function cannot be located
		cout << GetLastError();
		FreeLibrary(DLL_Library);
		return -3;
	}
	char image_path[FILENAME_MAX];// = (p + "\\images\\test.jpg");//.c_str();
	string tmp = p+"\\images\\test.jpg";
	int i;
	for( i = 0; i < tmp.size(); i++){
        image_path[i] = tmp[i];
	}
	image_path[i]='\0';
    preProcessingScanTailor = func(image_path, p);
    string imageResult = preProcessingScanTailor->applyBlackAndWhite();
    printf("\nimage PATH ::%s\n", image_path);
    cout << "imageResult::  " << imageResult << endl;
    cout << endl << "DONE!!"<<endl;
    return 0;
}
