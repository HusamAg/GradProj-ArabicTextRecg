#include <windows.h>
#include <process.h>
#include <string>

#include "IScanTailorPreProcessing.h"


#define GetCurrentDir _getcwd


using namespace std;

/*  To use this exported function of dll, include this header
 *  in your project.
 */
#define CLASS_API __declspec(dllexport)
class ScanTailorPreProcessing : public IScanTailorPreProcessing{
private:
    string command; // scantailor-cli.exe <image> <output_dir>
    string output_dir = "\\images";
    string image_name;
    string PATH_TO_IMAGE="";
    string SCANTAILOR_COMMAND="scantailor-cli";

public:
    ScanTailorPreProcessing(char *p, string p2);
    string applyBlackAndWhite();

};

extern "C" CLASS_API IScanTailorPreProcessing* getInstance(char *p, string p2){return new ScanTailorPreProcessing(p, p2);} // a function that returns an instance of the class scanTailorPreProcessing.

