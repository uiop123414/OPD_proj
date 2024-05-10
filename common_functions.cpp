// �����: ���������� �������, akizelokro@mail.ru, vtatarintsev.ru, 3 ������� 2013 ����
// Written by vitaly Tatarintsev, akizelokro@mail.ru, vtatarintsev.ru, 3 August 2013
//
// ����� �������, ���������� � �����������
//#include "StdAfx.h"
#include "common_functions.h"
//#include <afxinet.h>




//TRANSLATED



// ������� ��������� ���������� ������� (�������, ��������� � ��.) �� ������ ������
void removeLeadingWhitespaces(tstring * str)
{
    while ( (*str).length() && istspace((*str)[0]))
        (*str).erase(0, 1);
}

// ������� ����������� ���������� ������� (�������, ��������� � ��.) �� ������ ������
void removeTrailingWhitespaces(tstring * str)
{
    while ( (*str).length() &&  istspace((*str)[(*str).length() - 1]))
        (*str).erase( (*str).length() - 1, 1);

}

// ������� ��������� � ����������� ���������� ������� (�������, ��������� � ��.) �� ������
void trimWhitespaces(tstring * str)
{
    removeTrailingWhitespaces(str);
    removeLeadingWhitespaces(str);
}

//������� ��������� ���������� �������
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

//������� ��� ���������� �������
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



// ������� ������� �� ������ url ��������� ��������� (http://, https://) � ���������� ����
tstring * removeProtocolAndSlash(tstring * url)
{
    removeTrailingWhitespaces(url);    // ������ ����������� ���������� �������
    tstring str;
    long pos = url->find_last_of(_T("/"));   // ��� ��������� ��������� ����� "/"
    if ( pos == (url->length() - 1))     // ���� ��� ��������� ������
    {
        str = url->substr(0, url->length() - 1);    // ������� ��������� ��� ����
    }
    else
    {
        str = *url;    // ���� ������ �� ������������������� ����, �� ������� ��� ������
    }
//	delete url;
    pos = str.find(_T("http://"));     // �������� �� ��������� "http://"
    if(pos == 0)    // ���� ������� � ������ ������
    {
        str = str.substr(7, str.length() - 7);    // ������ ��������� "http://"
    }
    pos = str.find(_T("https://"));     // �������� �� ��������� "https://"
    if(pos == 0)    // ���� ������� � ������ ������
    {
        str = str.substr(8, str.length() - 8);    // ������ ��������� "https://"
    }
    removeTrailingWhitespaces(&str);    // ������ ����������� �������
    tstring * result = new tstring(str);

    return result;    // ��������� ������������ ������
}
