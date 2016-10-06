/*/////////////////////////////////////////////////////
//  File:           Type:            Made by         //
//   default.h       Localization     Katt           //
//                                                   //
//                                                   //
//                                                   //
/////////////////////////////////////////////////////*/

// double

double mpx, mpy;


// float

float windowSize;
float width;
float height;
float timer;


// unsigned int

unsigned int frames;


// const char*

#ifdef _DEBUG
	const char* varMode = " DEBUG MODE";
#else
	const char* varMode = " RELEASE MODE";
#endif

const char* vertLoc = "src/shaders/basic.vert";
const char* fragLoc = "src/shaders/basic.frag";