#pragma once

#include <fstream>
#include <windows.h>

#define LOGGING			
#define SLOWLOG			
					         


#define ERRORSTRING(x) L"Error not specified"


class ErrorLogger
{
private:
	static ErrorLogger instance;		
										     
										     
	ErrorLogger();
	~ErrorLogger();
	std::wofstream file;				  
	const static wchar_t Filename[];	
	const static int MAXLINES=100;	
										      
	static int LineCount;				
										      

public:
	static void Writeln(const wchar_t text[]);	
												           
												          
	static void Writeln(double num);			     
												           
												            
	static void Write(const wchar_t text[]);	 
												           
	static void Write(double num);				  
												          
};
