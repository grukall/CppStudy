#include <string.h>
#include <iostream>
#include "MyString.h"

MyString::~MyString()
{
    delete[] string_content;
}

MyString::MyString(int capacity)
{
    string_content = new char[capacity];
    string_length = 0;
    memory_capacity = capacity;
}

MyString::MyString(char c)
{
    string_content = new char[1];
    string_content[0] = c;
    string_length = 1;
    memory_capacity = string_length;
}

MyString::MyString(const char *str)
{
    string_length = strlen(str);
    string_content = new char[string_length];
    for (int i = 0; i < string_length; i++) string_content[i] = str[i];
    memory_capacity = string_length;
}

MyString::MyString(const MyString &str)
{
    string_length = str.string_length;
    string_content = new char[string_length];
    for (int i = 0; i < string_length; i++) string_content[i] = str.string_content[i];
    memory_capacity = string_length;
}

int MyString::length() const{ return string_length; }

void MyString::print() const
{
    for (int i = 0; i < string_length; i++)
        std::cout << string_content[i];
}

void MyString::println() const
{
    for (int i = 0; i < string_length; i++)
        std::cout << string_content[i];
    std::cout << '\n';
}

MyString &MyString::assign(const char *str)
{
    int str_length = strlen(str);
    if (memory_capacity < str_length)
    {
        delete[] string_content;
        string_content = new char[str_length];
        memory_capacity = str_length;
    }

    string_length = str_length;
    for (int i = 0; i < string_length; i++) string_content[i] = str[i];

    return *this;
}

MyString &MyString::assign(const MyString &str)
{
    if (memory_capacity < str.string_length)
    {
        delete[] string_content;
        string_content = new char[str.string_length];
        memory_capacity = str.string_length;
    }

    string_length = str.string_length;
    for (int i = 0; i < string_length; i++) string_content[i] = str.string_content[i];

    return *this;
}

int MyString::capacity() const {return memory_capacity;}

void MyString::reserve(int size)
{
    if (memory_capacity < size)
    {
        char *temp = new char[size];
        for (int i = 0; i < string_length; i++) temp[i] = string_content[i];

        delete[] string_content;
        string_content = temp;

        memory_capacity = size;
    }
}

char MyString::at(int i) const
{
    if (i >= string_length || i < 0)
        return 0;
    else
        return string_content[i];
}

MyString &MyString::insert(int loc, const MyString &str)
{
    if (loc < 0 || loc >= string_length) return *this;

    if (string_length + str.string_length > memory_capacity)
    {
        //메모리 크기를 2배 or 두 문자열 길이의 합으로 설정
        if (memory_capacity * 2 > string_length + str.string_length)
            memory_capacity *= 2;
        else
            memory_capacity = string_length + str.string_length;
        
        char *temp = string_content;
        string_content = new char[memory_capacity];

        //먼저 뒷 내용을 복사
        for (int i = string_length-1; i >= loc; i--)
        {
            string_content[i + str.string_length] = temp[i];
        }

        //앞 부분을 복사
        for (int i = 0; i < loc; i++)
        {
            string_content[i] = temp[i];
        }

        //가운데 빈 부분 내용을 str로 채워넣는다.
        for (int i = loc; i < loc + str.string_length; i++)
        {
            string_content[i] = str.string_content[i-loc];
        }

        delete[] temp;
        string_length += str.string_length;
        return *this;
    }

    for (int i = string_length-1; i >= loc; i--)
    {
        string_content[i + str.string_length] = string_content[i];
    }

    for (int i = loc; i < loc + str.string_length; i++)
    {
        string_content[i] = str.string_content[i-loc];
    }

    string_length += str.string_length;
    return *this;
}

MyString &MyString::insert(int loc, const char *str)
{
    MyString temp(str);
    return insert(loc, temp);
}

MyString &MyString::insert(int loc, char c)
{
    MyString temp(c);
    return insert(loc, temp);
}

MyString &MyString::erase(int loc, int num)
{
    if (loc < 0 || loc >= string_length) return *this;

    if (num <= 0) return *this;
    else if (loc + num > string_length) num = string_length -loc;

    for (int i = loc; i+num < string_length; i++)
        string_content[i] = string_content[i+num];

    return *this;
}

int MyString::find(int find_from, const MyString &str) const
{
    if (str.string_length == 0) return -1;

    int pi[str.string_length] = {0, };
    
    int j = 0;
    for (int i = 1; i < str.string_length; i++)
    {
        while (str.string_content[i] != str.string_content[j] && j > 0)
            j = pi[j-1];
        
        if (str.string_content[i] == str.string_content[j])
            j++;
    }

    j = 0;
    for (int i = find_from; i < string_length; i++)
    {
        while (j > 0 && string_content[i]  != str.string_content[j])
            j = pi[j-1];
        
        if (string_content[i] == str.string_content[j])
        {
            if (j == str.string_length - 1)
            {
                return i-str.string_length+1;
            }
            else j++;
        }
    }

    return -1;
}

int MyString::find(int find_from, const char *str) const
{
    MyString temp(str);
    return find(find_from, temp);
}

int MyString::find(int find_from, char c) const
{
    MyString temp(c);
    return find(find_from, temp);
}

int MyString::compare(const MyString &str)
{
    for (int i = 0; i < std::min(string_length, str.string_length); i++)
    {
        if (string_content[i] > str.string_content[i])
            return 1;
        else if (string_content[i] < str.string_content[i])
            return -1;
    }

    if (string_length == str.string_length)
        return 0;
    else if (string_length > str.string_length)
        return 1;
    else
        return -1;
}

bool MyString::operator==(MyString &str)
{
    return !compare(str);
}

int main() {
  MyString str1("a word");
  MyString str2("sentence");
  MyString str3("sentence");

  if (str1 == str2)
    std::cout << "str1 와 str2 같다." << std::endl;
  else
    std::cout << "st1 와 str2 는 다르다." << std::endl;

  if (str2 == str3)
    std::cout << "str2 와 str3 는 같다." << std::endl;
  else
    std::cout << "st2 와 str3 는 다르다" << std::endl;
}