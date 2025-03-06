#pragma once
#include <iostream>

//defining a macro , anything after the second space will replace the macro
			//macro						//compiler version
//cout a whit message to the console
#define CE_MSG_LOG(cn, msg) std::cout << cn << " | " << msg << std::endl;
//cout a red message to the console		//red colour						//reset to normal
#define CE_MSG_ERR(cn, msg) std::cout << "\033[31m" << cn << " | " << msg << "\033[0m" << std::endl;