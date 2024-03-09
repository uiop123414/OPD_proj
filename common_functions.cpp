// јвтор: “атаринцев ¬италий, akizelokro@mail.ru, vtatarintsev.ru, 3 августа 2013 года
// Written by vitaly Tatarintsev, akizelokro@mail.ru, vtatarintsev.ru, 3 August 2013
//
// общие функции, библиотеки и определени€
//#include "StdAfx.h"
#include "common_functions.h"
//#include <afxinet.h>




//TRANSLATED



// удал€ет начальные пробельные символы (пробелы, табул€ции и пр.) из начала строки
void removeLeadingWhitespaces(tstring * str)
{
	while ( (*str).length() && istspace((*str)[0]))
		(*str).erase(0, 1);
}

// удал€ет завершающие пробельные символы (пробелы, табул€ции и пр.) из начала строки
void removeTrailingWhitespaces(tstring * str)
{
	while ( (*str).length() &&  istspace((*str)[(*str).length() - 1]))
		(*str).erase( (*str).length() - 1, 1);
	
}

// удал€ет начальные и завершающие пробельные символы (пробелы, табул€ции и пр.) из строки
void trimWhitespaces(tstring * str)
{
	removeTrailingWhitespaces(str);
	removeLeadingWhitespaces(str);
}

//удал€ет повторные пробельные символы
void removeDoubledWhitespaces(tstring * ptstr)
{
	int nPos = 0;
	if(ptstr->length() < 2)
		return;
	while ( nPos < (ptstr->length() - 1) )
	{
		if(istspace((*ptstr)[nPos]) && istspace((*ptstr)[nPos+1]) )
			ptstr->erase(nPos, 1);
		else
			nPos++;
	}
}

//удал€ет все пробельные символы
void removeAllWhitespaces(tstring * ptstr)
{
	int nPos = 0;
	if(ptstr->length() < 1)
		return;
	while ( nPos < ptstr->length() )
	{
		if(istspace((*ptstr)[nPos]))
			ptstr->erase(nPos, 1);
		else
			nPos++;
	}
}



// функци€ удал€ет из строки url подстроку протокола (http://, https://) и завешающий слэш
tstring * removeProtocolAndSlash(tstring * url)
{
	removeTrailingWhitespaces(url);    // удал€ю завершающие пробельные символы
	tstring str;
	long pos = url->find_last_of(_T("/"));   // ищу последнее вхождение слэша "/"
	if ( pos == (url->length() - 1))     // если это последний символ
	{
		str = url->substr(0, url->length() - 1);    // получаю подстроку без него
	}
	else
	{
		str = *url;    // если строка не содержитзавершающий слэш, то копирую всю строку
	}
//	delete url;
	pos = str.find(_T("http://"));     // провер€ю на вхождение "http://"
	if(pos == 0)    // если найдено в начале строки
	{
		str = str.substr(7, str.length() - 7);    // удал€ю начальный "http://"
	}
	pos = str.find(_T("https://"));     // провер€ю на вхождение "https://"
	if(pos == 0)    // если найдено в начале строки
	{
		str = str.substr(8, str.length() - 8);    // удал€ю начальный "https://"
	}
	removeTrailingWhitespaces(&str);    // удал€ю завершающие симаолы
	tstring * result = new tstring(str);    
		
	return result;    // возвращаю рельтирующую строку
}

