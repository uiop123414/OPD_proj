// �����: ���������� �������, akizelokro@mail.ru, vtatarintsev.ru, 3 ������� 2013 ����
// Written by vitaly Tatarintsev, akizelokro@mail.ru, vtatarintsev.ru, 3 August 2013
//
// ����� �������, ���������� � �����������

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


// ����������� ��� ������ � ������������� ������������ ����� (� ����������� �� ����� ���������� multibyte ��� Unicode)
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

// ������� ��������� ���������� ������� (�������, ��������� � ��.) �� ������ ������
void removeLeadingWhitespaces(tstring * str);

// ������� ����������� ���������� ������� (�������, ��������� � ��.) �� ������ ������
void removeTrailingWhitespaces(tstring * str);

// ������� ��������� � ����������� ���������� ������� (�������, ��������� � ��.) �� ������ ������
void trimWhitespaces(tstring * str);

//������� ��������� ���������� �������
void removeDoubledWhitespaces(tstring * ptstr);

//������� ��� ���������� �������
void removeAllWhitespaces(tstring * ptstr);

// ������� ���������� true, ���� ������ ������� � ������� �����, � false � ���� ������
bool search_in(tstring *search, vector<tstring> *where);

// ������� ������������ ������ � long � ������������ ��������, ��� �� ������� ��������������.
// � ������ ������� ���������������� �������� ���������� false
bool parseLongFromString(tstring * str, long * value);

// ������� ������� �� ������ url ��������� ��������� (http://, https://) � ���������� ����
tstring * removeProtocolAndSlash(tstring * url);
