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

/**
	This provides some functions to deal with numbers strings and cstrings.
*/
class Functions {

public:

	/**
		Check if num is between lower and upper (including lower and upper).
	*/
	static bool isBetween(const int num, const int lower, const int upper) {
		return (num >= lower) && (num <= upper);
	}

	/**
		Check if text only consists of numbers and doesn't beginn with 0'.
		Will return true if text can be converted into a number.
		
		e.g.:
		isNumber("012") returns false
		isNumber("12k") returns false
		isNumber("123") returns true
	*/
	static bool isNumber(const char* text) {
		if ((strlen(text) == 0) || !isBetween(text[0], 49, 57))
			return false;
		
		for (int i = 0; i < strlen(text); i++) {
			if (!isBetween(text[i], 48, 57))
				return false;
		}
	
		return true;
	}
	
	/**
		Simply converts a string to an integer.
	*/
	static int StringToInt(const string input) {		
		return StringToInt(StringToCString(input));
	}
	
	/**
		Converts a c-string to an integer.
	*/
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
		
		return value;
	}
	
	/**
		Converts a string to a c-string.
	*/
	static char* StringToCString(const string input) {
		char* output= new char [input.length()+1];
		
		strcpy(output, input.c_str());
		
		return output;
	}
	
	/**
		Used for calculating the x-coordinates for a kv-diagramm.
		fills a given vector with the right coordinates.
		e.g.:
			x[0] will contain 0
			x[15] will contain 2
	*/
	static void fillKVX(vector<int> *x, int quantity) {
		x->push_back(0);
		x->push_back(1);
	
		for (int i = 2; i <= quantity; i++) {
			int b = pow(2, (i + 1) / 2);
				int size = x->size();
		
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

	/**
		Same as fillKVX, just for the y coordinates.
	*/
	static void fillKVY(vector<int> *y, int quantity) {
		y->push_back(0);
		y->push_back(0);
	
		for (int i = 2; i <= quantity; i++) {
			int h = pow(2, i / 2);
			int size = y->size();
		
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
	
	/**
		Splits a String (input) at a given delimiter and returns the result as a vector.
		
		e.g.: 
		splitString("abc,def,ghi", ',')
		would return a vector with following entrys:
		vec[0] = "abc"
		vec[1] = "def"
		vec[2] = "ghi"
	*/
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
	
	/**
		Similar to slitString, but this one returns a vector with integers.
		It eliminates every character in the string which is not a number.
	*/
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
	
	/**
		Removes every character which is not a number.
	*/
	static string onlyNumbers(const string input) {
		string output = string(input);
		
		int index = output.find_first_not_of("0123456789");
		while(index >= 0) {
			output.replace(index, 1, "");
			index = output.find_first_not_of("0123456789");
		}
		
		return output;
	}
	
	/**
		converts an integer to a c-string
	*/
	static char* intToCString(int num) {
		char* str = new char[100];
		sprintf(str, "%d", num);
		return str;
	}
	
	/**
		returns a Fl_Color (fast light tool kit color) for a given index.
		This is reproducable and returns different colors for different indexes.
	*/
	static Fl_Color getColor(int index) {
	
		float x = (float) 3 + 3 * index * M_PI / 10;
	
		float r = fabs((float) (cos(x / 2)));
		float g = fabs((float) (cos(x / 5)));
		float b = fabs((float) (cos(x / 3)));

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
	
	/**
		Converts a number into its binary representation and returns this as a string.
	*/
	static string numberToBitString(int number) {
		string bitString = "";
		
		while (number > 0) {
		
			bitString += intToCString(number & 1);
		
			number >>= 1;
		}
		
		reverseString(&bitString);
		
		return bitString;
	}
	
	/**
		Reverses a string.
		e.g.:
		reverseString("abcd") returns "dcba"
	*/
	static void reverseString(string *str) {
		string revString = "";
		
		while (str->size() > 0) {
			revString += str->at(str->size() - 1);
			str->erase(str->size() - 1);
		}
		
		*str += revString;
	}
	
	/**
		returns a random number element of [low, high]
	*/
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
