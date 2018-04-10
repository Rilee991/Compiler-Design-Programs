#include<bits/stdc++.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;

int cursor=0;
int savedcursor=cursor;
string inputword;
//char nexttoken;

void savecursor();
void backtrack();
char getnexttoken();
bool term(char x);
bool E();
bool E1();
bool E2();
bool T();
bool T1();
bool T2();
bool T3();

void savecursor(){
        savedcursor=cursor;
        return;
}

void backtrack(){
        cursor=savedcursor;
        return;
}

char getnexttoken(){
        char nexttoken=inputword[cursor];
        while (inputword[cursor] == ' ')
                        cursor++;
                  nexttoken = inputword[cursor];
        cursor++;
        return nexttoken;
}

bool term(char x){
        return getnexttoken()==x;
}

bool E(){
        return (savecursor(),E1())||(backtrack(),savecursor(),E2());
}

bool E1(){
        return T();
}

bool E2(){
        return T()&&term('+')&&E();
}

bool T(){
        return (savecursor(),T3())||(backtrack(),savecursor(),T2())||(backtrack(),savecursor(),T1());
}

bool T1(){
        return term('a');
}

bool T2(){
        return term('a')&&term('*')&&T();
}

bool T3(){
        return term('(')&&E()&&term(')');
}


        
int main(){
        
        cin>>inputword;
        //nexttoken=inputword[cursor];
        if(E()&&(cursor==inputword.length()))
                cout<<"valid\n";
        else
                cout<<"invalid\n";
        return 0;
}


