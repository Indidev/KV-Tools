#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <FL/Fl.h>

#include <math.h>
#include <string>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;


class Functions {

public:
	static bool isBetween(const int num, const int lower, const int upper) {
		return (num >= lower) && (num <= upper);
	}


	static bool isNumber(const char* text) {
		if ((strlen(text) == 0) || !isBetween(text[0], 49, 57))
			return false;
		
		for (int i = 0; i < strlen(text); i++) {
			if (!isBetween(text[i], 48, 57))
				return false;
		}
	
		return true;
	}
	
	static int StringToInt(const string input) {		
		return StringToInt(StringToCString(input));
	}
	
	static int StringToInt(const char* input) {
		int value = 0;
		int i = 1;
		char* s = new char[strlen(input) + 1];
		strcpy(s, input);
		
		while(strlen(s) > 0) {
			value += i * (s[strlen(s) - 1] - 48);
			s[strlen(s) - 1] = '\0';
			i *= 10;
		}
		
		free(s);
		return value;
	}
	
	static char* StringToCString(const string input) {
		char* output= new char [input.length()+1];
		
		strcpy(output, input.c_str());
		
		return output;
	}
	
	static void fillKVX(vector<int> *x, int quantity) {
		x->push_back(0);
		x->push_back(1);
	
		for (int i = 2; i <= quantity; i++) {
			int b = pow(2, (i + 1) / 2);
				int size = x->size();
		
			//printf("i: %d, b: %d\n", i, b);
		
			if ((i % 2) == 1) {
			
				for (int j = 0; j < size; j++) {
					x->push_back(b - x->at(j) - 1);
				}
			
			} else {
		
				for (int j = 0; j < size; j++) {
					x->push_back(x->at(j));
				}
			
			}
	
		}
	}

	static void fillKVY(vector<int> *y, int quantity) {
		y->push_back(0);
		y->push_back(0);
	
		for (int i = 2; i <= quantity; i++) {
			int h = pow(2, i / 2);
			int size = y->size();
		
			//printf("i: %d, b: %d\n", i, b);
		
			if ((i % 2) == 0) {
			
				for (int j = 0; j < size; j++) {
					y->push_back(h - y->at(j) - 1);
				}
			
			} else {
		
				for (int j = 0; j < size; j++) {
					y->push_back(y->at(j));
				}
			
			}
	
		}
	}
	
	static vector<string>* splitString(const string input, char delimiter) {
		string str = string(input);
		vector<string> *values = new vector<string>();
		
		int index = str.find_first_of(delimiter);
		
		while(index >= 0) {
		
			if (index > 0)
				values->push_back(str.substr(0, index));
			
			str = str.substr(index + 1);
			
			index = str.find_first_of(delimiter);
		}
		
		values->push_back(str);
		
		return values;
	}
	
	static vector<int>* splitStringToInt(const string input, char delimiter) {
		vector<string> *strVec = splitString(input, delimiter);
		
		vector<int> *intVec = new vector<int>();
		
		for (int i = 0; i < strVec->size(); i++) {
			string numString = onlyNumbers(strVec->at(i));
			if(numString.size() > 0) {
				intVec->push_back(StringToInt(numString));
			}
		}
		
		strVec->~vector();
		
		return intVec;
	}
	
	static string onlyNumbers(const string input) {
		string output = string(input);
		
		int index = output.find_first_not_of("0123456789");
		while(index >= 0) {
			output.replace(index, 1, "");
			index = output.find_first_not_of("0123456789");
		}
		
		return output;
	}
	
	static char* intToCString(int num) {
		char* str = new char[100];
		sprintf(str, "%d", num);
		return str;
	}
	
	static Fl_Color getColor(int index) {
	
		float x = (float) 3 + 3 * index * M_PI / 10;
	
		float r = fabs((float) (cos(x / 2)));
		float g = fabs((float) (cos(x / 5)));
		float b = fabs((float) (cos(x / 3)));
		
		//printf("x: %f, r: %f, g: %f, b: %f\n", x, r, g, b);

		if (r > 1)
			r = 1;
		if (g > 1)
			g = 1;
		if (b > 1)
			b = 1;
			
		if (r < 0)
			r = 0;
		if (g < 0)
			g = 0;
		if (b < 0)
			b = 0;
	
		return fl_rgb_color((int)(r * 255), (int)(g * 255), (int)(b * 255));
	}
	
	static string numberToBitString(int number) {
		string bitString = "";
		
		while (number > 0) {
		
			bitString += intToCString(number & 1);
		
			number >>= 1;
		}
		
		reverseString(&bitString);
		
		return bitString;
	}
	
	static void reverseString(string *str) {
		string revString = "";
		
		while (str->size() > 0) {
			revString += str->at(str->size() - 1);
			str->erase(str->size() - 1);
		}
		
		*str += revString;
	}
	
	static int i_rand(int low, int high) {
		static bool initiated = false;
		
		if (!initiated) {
			srand (time(NULL));
			initiated = true;
		}
		
		int random = rand();
		random %= high - low + 1;
		random += low;
		
		return random;
	}
};
#endif
