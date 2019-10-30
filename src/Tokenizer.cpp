//
// Created by rubelem on 10/29/19.
//

#include "Tokenizer.h"
#include <cstring>
#include <sstream>
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

// The folowing three functions are from:
// https://stackoverflow.com/questions/14094621/change-all-accented-letters-to-normal-letters-in-c
unsigned char SimplifyDoubleCharForSorting( unsigned char c1, unsigned char c2, bool changeToLowerCase )
{
    if ( c1 == 0xC2 )
    {
        if ( c2 == 0xAA ) { return 'a'; }
        if ( c2 == 0xBA ) { return ' '; }
        if ( c2 == 0xA9 ) { return ' '; }
        if ( c2 == 0xAE ) { return ' '; }
    }

    if ( c1 == 0xC3 )
    {
        if ( c2 >= 0x80 && c2 <= 0x85 ) { return changeToLowerCase ? 'a' : 'A'; }
        if ( c2 >= 0xA0 && c2 <= 0xA5 ) { return 'a'; }
        if ( c2 >= 0x88 && c2 <= 0x8B ) { return changeToLowerCase ? 'e' : 'E'; }
        if ( c2 >= 0xA8 && c2 <= 0xAB ) { return 'e'; }
        if ( c2 >= 0x8C && c2 <= 0x8F ) { return changeToLowerCase ? 'i' : 'I'; }
        if ( c2 >= 0xAC && c2 <= 0xAF ) { return 'i'; }
        if ( c2 >= 0x92 && c2 <= 0x96 ) { return changeToLowerCase ? 'o' : 'O'; }
        if ( c2 >= 0xB2 && c2 <= 0xB6 ) { return 'o'; }
        if ( c2 >= 0x99 && c2 <= 0x9C ) { return changeToLowerCase ? 'u' : 'U'; }
        if ( c2 >= 0xB9 && c2 <= 0xBC ) { return 'u'; }
        if ( c2 == 0x87 ) { return changeToLowerCase ? 'c' : 'C'; }
        if ( c2 == 0xA7 ) { return 'c'; }
        if ( c2 == 0x91 ) { return changeToLowerCase ? 'n' : 'N'; }
        if ( c2 == 0xB1 ) { return 'n'; }
        if ( c2 == 0x9F ) { return 's'; }
        if ( c2 == 0x9D ) { return changeToLowerCase ? 'y' : 'Y'; }
        if ( c2 == 0xBD || c2 == 0xBF ) { return 'y'; }
    }

    if ( c1 == 0xC5 )
    {
        if ( c2 == 0xBD ) { return changeToLowerCase ? 'z' : 'Z'; }
        if ( c2 == 0xBE ) { return 'z'; }
        if ( c2 == 0xB8 ) { return changeToLowerCase ? 'y' : 'Y'; }
    }

    if (c1 == 0xE2) {
        if (c2 == 0x84) return ' ';
        if (c2 == 0x80) return '"';
    }

    return c1;
}

unsigned char SimplifySingleCharForSorting( unsigned char c, bool changeToLowerCase )
{
    if ( ( c >= 0xC0 && c <= 0xC5 ) || ( c >= 0xE1 && c <= 0xE5 ) || c == 0xAA )
    {
        return ( ( c >= 0xC0 && c <= 0xC5 ) && !changeToLowerCase ) ? 'A' : 'a';
    }

    if ( ( c >= 0xC8 && c <= 0xCB ) || ( c >= 0xE8 && c <= 0xEB ) )
    {
        return ( c > 0xCB || changeToLowerCase ) ? 'e' : 'E';
    }

    if ( ( c >= 0xCC && c <= 0xCF ) || ( c >= 0xEC && c <= 0xEF ) )
    {
        return ( c > 0xCF || changeToLowerCase ) ? 'i' : 'I';
    }

    if ( ( c >= 0xD2 && c <= 0xD6 ) || ( c >= 0xF2 && c <= 0xF6 ) || c == 0xBA )
    {
        return ( ( c >= 0xD2 && c <= 0xD6 ) && !changeToLowerCase ) ? 'O' : 'o';
    }

    if ( ( c >= 0xD9 && c <= 0xDC ) || ( c >= 0xF9 && c <= 0xFC ) )
    {
        return ( c > 0xDC || changeToLowerCase ) ? 'u' : 'U';
    }

    if ( c == 0xA9 || c == 0xC7 || c == 0xE7 )
    {
        return ( c == 0xC7 && !changeToLowerCase ) ? 'C' : 'c';
    }

    if ( c == 0xD1 || c == 0xF1 )
    {
        return ( c == 0xD1 && !changeToLowerCase ) ? 'N' : 'n';
    }

    if ( c == 0xAE )
    {
        return 'r';
    }

    if ( c == 0xDF )
    {
        return 's';
    }

    if ( c == 0x8E || c == 0x9E )
    {
        return ( c == 0x8E && !changeToLowerCase ) ? 'Z' : 'z';
    }

    if ( c == 0x9F || c == 0xDD || c == 0xFD || c == 0xFF )
    {
        return ( ( c == 0x9F || c == 0xDD ) && !changeToLowerCase ) ? 'Y' : 'y';
    }

    return c;
}

void SimplifyStringForSorting( string *s, bool changeToLowerCase )
{

    int n = s->size();
    int pos = 0;
    for ( int i = 0 ; i < n ; i++, pos++ )
    {
        unsigned char c = (unsigned char)s->at( i );
        if ( c >= 0x80 )
        {
            if ( i < ( n - 1 ) && (unsigned char)s->at( i + 1 ) >= 0x80 )
            {
                unsigned char c2 = SimplifyDoubleCharForSorting( c, (unsigned char)s->at( i + 1 ), changeToLowerCase );
                if ( c2 < 0x80 )
                {
                    s->at( pos ) = c2;
                    i++;
                }
                else
                {
                    i++;
                }
            }
            else
            {
                unsigned char c2 = SimplifySingleCharForSorting( c, changeToLowerCase );
                if ( c2 < 0x80 )
                {
                    s->at( pos );
                }
                else
                {
                    pos--;
                }
            }
        }
        else
        {
            if ( changeToLowerCase && c >= 'A' && c <= 'Z' )
            {
                s->at( pos ) = c + ( 'a' - 'A' );
            }
            else
            {
                s->at( pos ) = c;
            }
        }
    }
    if ( pos < n )
    {
        s->resize( pos );
    }
}

string removePunctuation(const string& text) {
    string result;
    std::replace_copy_if(text.begin(), text.end(),
                        std::back_inserter(result), //Store output
                        std::ptr_fun<int, int>(&std::ispunct), ' '
    );

    return result;
}

std::vector<std::string> Tokenizer::get(const std::string& s) {
    vector<string> tokens;
    string token;
    string toConvert = s;

    SimplifyStringForSorting(&toConvert, true);
    toConvert = removePunctuation(toConvert);

    istringstream tokenStream(toConvert);

    while (std::getline(tokenStream, token, ' ')) {
        if (token != "") // if token is not empty, add to the return list.
            tokens.push_back(token);
    }

    return tokens;
}