// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the THREADDLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// THREADDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef THREADDLL_EXPORTS
#define THREADDLL_API __declspec(dllexport)
#else
#define THREADDLL_API __declspec(dllimport)
#endif

// This class is exported from the threaddll.dll
class THREADDLL_API Cthreaddll {
public:
	Cthreaddll(void);
	// TODO: add your methods here.
};

extern THREADDLL_API int nthreaddll;

THREADDLL_API int fnthreaddll(void);
