#include <iostream>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include "kayttoliittyma.h"
#include "asema.h"

using namespace std; 

int main()
{
	Asema asema;
	Kayttoliittyma ui(&asema);
	ui.piirraLauta();
	
	return 0;
}
