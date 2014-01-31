#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/fl_ask.H>
#include <vector>
#include <math.h>
#include <stdio.h>

#include "Functions.h"
#include "KVEntry.h"
#include "MyButton.h"
#include "MyWindow.h"
#include "MyHLine.h"
#include "MyVLine.h"
#include "MyLabledHLine.h"
#include "MyLabledVLine.h"
#include "KVEntryBox.h"
#include "PrimBlock.h"


#include "KVWindow.h"

KVWindow::KVWindow(int t, int l, int w, int h, char* title, vector<KVEntry*> *entrys):MyWindow(t, l, w, h, title) {
	this->entrys = *entrys;
	this->color(FL_LIGHT3);
	
	this->blockType = 1;
	
	quantity = (int) log2(this->entrys.size());
	
	drawTable();
	
	for (int i = 0; i < quantity; i++) {
		if (i % 2) {
			drawVLine(i);
		} else {
			drawHLine(i);
		}
	}
	
	this->begin();
		stepButton = new MyButton(this->w() - 110, this->h() - 40, 100, 30, "Step", this);
		stepButton->color(FL_LIGHT3);
		
		solveButton = new MyButton(this->w() - 110, this->h() - 80, 100, 30, "Solve", this);
		solveButton->color(FL_LIGHT3);
		
		resetButton = new MyButton(10, this->h() - 40, 100, 30, "Reset", this);
		resetButton->color(FL_LIGHT3);
		
		string bt = "Block Type: ";
		bt += Functions::intToCString(blockType);
		
		blockTypeButton = new MyButton(10, this->h() - 80, 100, 30, Functions::StringToCString(bt), this);
		blockTypeButton->color(FL_LIGHT3);
		
		
	this->end();
}

void KVWindow::handleCallback(Fl_Widget* widgetptr) {
	if (widgetptr == stepButton) {
	
		solveStep();
	
	} else if(widgetptr == solveButton) {
	
		solve();
	
	} else if(widgetptr == resetButton) {
	
		reset();
	
	} else if(widgetptr == blockTypeButton) {
	
		changeBlockType();
	
	}
}

void KVWindow::drawTable() {
	
	int minW = BSIZE * pow(2, (quantity + 1) / 2) + 2 * OFFSET;
	int minH = BSIZE * pow(2, quantity / 2) + 2 * OFFSET;
	
	this->resize(this->x(), this->y(), minW, minH);
	
	
	Functions::fillKVX(&xCord, quantity);
	Functions::fillKVY(&yCord, quantity);
	
	this->begin();
	for (int i = 0; i < this->entrys.size(); i++) {
	
		char* label = Functions::StringToCString(this->entrys[i]->getLabel());
		
		KVEntryBox *b = new KVEntryBox(OFFSET + xCord[i] * BSIZE, OFFSET + yCord[i] * BSIZE, BSIZE, BSIZE, label, i, this);
		
	}
	this->end();	
}

void KVWindow::drawHLine(int index) {
	vector<MyHLine*> lineVec;
	
	bool top = !((index % 4) / 2);
	char* letter = new char[2];
	letter[0] = 97 + index;
	letter[1] = '\0';
	
	int height = OFFSET - (4 + (30 * (index / 4)));
	
	if (!top)
		height = this->h() - height + LINEWIDTH ;
		
	this->begin();
	
	MyHLine *line = new MyLabledHLine(OFFSET + pow(2, index / 2) * BSIZE, height, pow(2, index / 2) * BSIZE, LINEWIDTH, FL_BLACK, letter, top);
		
	lineVec.push_back(line);
	
	for (int i = index + 2; i < quantity; i += 2) {
		
		if (i == index + 2) {
			
			line->doubleLength();
			
		} else {
		
			int size = lineVec.size();
			for (int j = 0; j < size; j++) {
				int deltaX = pow(2, i / 2) * BSIZE - (lineVec[j]->x() + lineVec[j]->w() - OFFSET);
				int newX = lineVec[j]->x() + lineVec[j]->w() + 2 * deltaX;
					
				MyHLine *line2 = new MyLabledHLine(newX, lineVec[j]->y(), lineVec[j]->w(), LINEWIDTH, FL_BLACK, letter, top);
				lineVec.push_back(line2);
					
			}
		}
		
		
	}
		
	this->end();
}

void KVWindow::drawVLine(int index) {
	vector<MyVLine*> lineVec;
	
	bool left = (((index - 1) % 4) / 2);
	char* letter = new char[2];
	letter[0] = 97 + index;
	letter[1] = '\0';
	
	int offset = OFFSET - (4 + (30 * ((index - 1) / 4))) ;
	
	if (!left)
		offset = this->w() - offset + LINEWIDTH;
		
	this->begin();
	
	MyVLine *line = new MyLabledVLine(offset, OFFSET + pow(2, (index - 1) / 2) * BSIZE, pow(2, (index - 1) / 2) * BSIZE, LINEWIDTH, FL_BLACK, letter, left);
		
	lineVec.push_back(line);
	
	for (int i = index + 2; i < quantity; i += 2) {
		
		if (i == index + 2) {
			
			line->doubleLength();
			
		} else {
		
			int size = lineVec.size();
			for (int j = 0; j < size; j++) {
				int deltaY = pow(2, (i - 1) / 2) * BSIZE - (lineVec[j]->y() + lineVec[j]->h() - OFFSET);
				int newY = lineVec[j]->y() + lineVec[j]->h() + 2 * deltaY;
					
				MyVLine *line2 = new MyLabledVLine(lineVec[j]->x(), newY, lineVec[j]->h(), LINEWIDTH, FL_BLACK, letter, left);
				lineVec.push_back(line2);
					
			}
		}
		
		
	}
		
	this->end();
}

bool KVWindow::solveStep() {
	this->begin();

	static bool initiated = false;
	bool changedSomething = false;

	if (!primBlocks.size()) {
		
		int counter = 0;
				
		for (int i = 0; i < this->entrys.size(); i++) {
		
			if (entrys[i]->getValue() != (1 - blockType)) {
			
				PrimBlock *m = new PrimBlock(OFFSET + xCord[i] * BSIZE, OFFSET + yCord[i] * BSIZE, BSIZE, BSIZE, i, quantity, Functions::getColor(counter));
				
				counter++;
				primBlocks.push_back(m);
			}
		}
		
		changedSomething = primBlocks.size();
		
		initiated = true;
	} else {
	
		vector<PrimBlock*> np;
	
		for (int i = 1; i < primBlocks.size(); i++) {
			for (int j = 0; j < i; j++) {
				int index = primBlocks[i]->compare(primBlocks[j]);
			
				if (index >= 0) {
				
					PrimBlock* npb = primBlocks[i]->fusePrim(primBlocks[j], index);
					
					bool deleted = false;
					
					for (int k = 0; (k < np.size()) && !deleted; k++)
						deleted = !npb->getTerm().compare(np[k]->getTerm());
					
					if (deleted)
						delete(npb);
					else
						np.push_back(npb);
					
				}
			}
		}	
		
		changedSomething = np.size();
	
		for (int i = primBlocks.size() - 1; i >= 0; i--) {
			if (primBlocks[i]->isMarkedForDeletion()) {
			
				delete(primBlocks[i]);
				primBlocks.erase(primBlocks.begin() + i);
			}	
		}
	
		for (int i = 0; i < np.size(); i++) {
			primBlocks.push_back(np[i]);
		}
		
		for (int i = 0; i < primBlocks.size(); i++) {
			primBlocks[i]->setColor(Functions::getColor(i));
		}
	
	}
	
	this->end();
	
	this->redraw();
	
	return changedSomething;
}

	void KVWindow::reset() {
		
		for (int i = 0; i < primBlocks.size(); i++)
			delete(primBlocks[i]);
			
		primBlocks.clear();
		
		this->redraw();
	}
	
	void KVWindow::solve() {
		while(solveStep());
	}
	
	void KVWindow::changeBlockType() {
		
		blockType = 1 - blockType;
		
		string bt = "Block Type: ";
		bt += Functions::intToCString(blockType);
		
		blockTypeButton->label(Functions::StringToCString(bt));
		
		reset();
	}
