
#ifndef KVENTRY_H
#define KVENTRY_H

#include <string>
using namespace std;
		
		
/**
	This represents a kv diagramm entry
*/		
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
		
		/**
			returns the value of this kv-entry as label
		*/
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
		
		/**
			set value of this entry (0, 1, or anything other for don't care status)
		*/
		void setValue(int value) {
			if (!locked)
				this->value = value;
		}
		
		/**
			returns the integer value of this entry
		*/
		int getValue() {
			return value;
		}
		
		/**
			Lock or unlock this entry.			
			This entry can not be changed if it is locked!
		*/
		void lock(bool status) {
			this->locked = status;
		}
		
		/**
			Check if this entry is locked.
		*/
		bool lock() {
			return locked;
		}

};

#endif
