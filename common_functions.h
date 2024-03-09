// јвтор: “атаринцев ¬италий, akizelokro@mail.ru, vtatarintsev.ru, 3 августа 2013 года
// Written by vitaly Tatarintsev, akizelokro@mail.ru, vtatarintsev.ru, 3 August 2013
//
// общие функции, библиотеки и определени€

#pragma once

#include "tchar.h"
#include <vector>
#include <functional>
#include <algorithm> 
#include <string>
#include <iostream>
#include <fstream>
#include <utility>
#include <tuple>
#include <random>
#include <map>

#include <sys/timeb.h>
#include <time.h>
using namespace std;


// обозначени€ дл€ работы с универсальным определением строк (в зависимости от опции компил€ции multibyte или Unicode)
#ifdef _UNICODE
typedef wstring tstring;
#define tcin wcin
#define tcout wcout         
#define tcerr wcerr 
typedef wostringstream tostringstream; 
typedef wistringstream tistringstream;
typedef wifstream tifstream;      
typedef wofstream tofstream;
typedef wostream tostream;
#define istspace iswspace
#define to_tstring to_wstring
#define SetWindowTextT SetWindowTextW
#define GetWindowTextT GetWindowTextW
#define GetWindowTextLengthT GetWindowTextLengthW
#define HtmlHelpT HtmlHelpW
#define istdigit iswdigit
#else
typedef std::string tstring;
#define tcin cin
#define tcout cout 
#define tcerr cerr 
typedef ostringstream tostringstream; 
typedef istringstream tistringstream;
typedef ifstream tifstream;      
typedef ofstream tofstream; 
typedef ostream tostream;
#define istspace isspace
#define to_tstring to_string
#define SetWindowTextT SetWindowText
#define GetWindowTextT GetWindowText
#define GetWindowTextLengthT GetWindowTextLength
#define HtmlHelpT HtmlHelp
#define istdigit isdigit
#endif




const long bufferLength = 500;

// удал€ет начальные пробельные символы (пробелы, табул€ции и пр.) из начала строки
void removeLeadingWhitespaces(tstring * str);

// удал€ет завершающие пробельные символы (пробелы, табул€ции и пр.) из начала строки
void removeTrailingWhitespaces(tstring * str);

// удал€ет начальные и завершающие пробельные символы (пробелы, табул€ции и пр.) из начала строки
void trimWhitespaces(tstring * str);

//удал€ет повторные пробельные символы
void removeDoubledWhitespaces(tstring * ptstr);

//удал€ет все пробельные символы
void removeAllWhitespaces(tstring * ptstr);

// функци€ возвращает true, если строка найдена в векторе строк, и false в ином случае
bool search_in(tstring *search, vector<tstring> *where);

// функци€ конвертирует строку в long и осуществл€ет проверку, все ли символы конвертируютс€. 
// ¬ случае наличи€ неконвертируемых символов возвращает false
bool parseLongFromString(tstring * str, long * value);

// функци€ удал€ет из строки url подстроку протокола (http://, https://) и завешающий слэш
tstring * removeProtocolAndSlash(tstring * url);

