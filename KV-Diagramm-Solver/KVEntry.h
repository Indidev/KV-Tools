
#ifndef KVENTRY_H
#define KVENTRY_H

#include <string>
using namespace std;
		
class KVEntry {

	private:
	
		int index;
		int value;
		bool locked;
	
	public:
	
		
		KVEntry(int index, int value) {
			this->index = index;
			this->value = value;
			this->locked = false;
		}
		
		string getLabel() {
			string label = "";
			
			switch(value) {
				case 0:
					label = "0";
				break;
				case 1:
					label = "1";
				break;
				default:
					label = "-";
			}
			return label;
		} 
		
		void setValue(int value) {
			if (!locked)
				this->value = value;
		}
		
		int getValue() {
			return value;
		}
		
		void lock(bool status) {
			this->locked = status;
		}
		
		bool lock() {
			return locked;
		}

};

#endif
