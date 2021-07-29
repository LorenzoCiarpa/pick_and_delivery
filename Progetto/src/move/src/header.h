#pragma once
#include <string>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
using namespace std;


vector<string> parse(string s);
float* getStanza(string buf);
int stanzaLog(string buf, vector<string> stanze, bool* logged, int size);
void resetLog(bool* logged, int size);
int isLogged(string buf, vector<string> stanze, bool* logged, int size);
