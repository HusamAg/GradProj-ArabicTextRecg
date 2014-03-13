#include "scanTailorPreProcessing.h"
#include <process.h>
#include <Windows.h>
#include <iostream>

using namespace std;

ScanTailorPreProcessing::ScanTailorPreProcessing(char *p,string p2){
   // cout << "\n\nPATHHHHHHH\n\n" << p<<endl;
    this->PATH_TO_IMAGE = string(p);
   /* for(int i = 0; p[i] != '\0'; i++)
        this->PATH_TO_IMAGE[i] = p[i];*/
    this->output_dir = p2 + this->output_dir;
    cout << "test----\n" << this->PATH_TO_IMAGE << endl << this->output_dir << endl;
}
string ScanTailorPreProcessing::applyBlackAndWhite(){
    this->command = this->SCANTAILOR_COMMAND+" \"" + this->PATH_TO_IMAGE + "\" \"" + this->output_dir+"\"";
    cout  << "COMMAND---" << endl<< command.c_str() << endl;
    this->image_name = "";
    system(command.c_str());
    return this->output_dir + "\\" + this->image_name;
}
