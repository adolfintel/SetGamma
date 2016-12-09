#include<windows.h>

typedef BOOL (WINAPI *Type_SetDeviceGammaRamp)(HDC hDC, LPVOID lpRamp);

int main(int argc, char* argw[]){
	int gamma=128;
	if(argc==2){
		gamma=atoi(argw[1]);
	}
	HMODULE hGDI32=LoadLibrary("gdi32.dll");
	Type_SetDeviceGammaRamp pGetDeviceGammaRamp = (Type_SetDeviceGammaRamp)GetProcAddress(hGDI32, "GetDeviceGammaRamp");
	Type_SetDeviceGammaRamp pSetDeviceGammaRamp = (Type_SetDeviceGammaRamp)GetProcAddress(hGDI32, "SetDeviceGammaRamp");
	HDC hGammaDC = GetDC(NULL);
	WORD GammaArray[3][256];
	int iIndex;
	for (iIndex = 0; iIndex < 256; iIndex++){
		int iArrayValue = iIndex * (gamma + 128);
		if (iArrayValue > 65535)iArrayValue = 65535;
		GammaArray[0][iIndex] = GammaArray[1][iIndex] = GammaArray[2][iIndex] = (WORD)iArrayValue;
	}
	pSetDeviceGammaRamp(hGammaDC, GammaArray);
 	return 0;	
}
