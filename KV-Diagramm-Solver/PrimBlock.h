#ifndef PRIMBLOCK_H
#define PRIMBLOCK_H

#include <vector>
#include <string>
#include <iostream>
#include <FL/Fl.H>
#include "Marker.h"


class PrimBlock {
	private:
		static const int EPS = 10;
		string term;
		vector<Marker*> markers;
		bool deleted;
		Fl_Color color;
		
		
		bool fuseMarkers(vector<Marker*> *nm, int index1, int index2) {
			Marker* m1 = nm->at(index1);
			Marker* m2 = nm->at(index2);
			
			
			
			bool fused = false;
			
			if (((m2->x() + EPS) < m1->x()) || ((m2->y() + EPS) < m1->y())) {
				m1 = nm->at(index2);
				m2 = nm->at(index1);
			}
			
			if (((abs(m2->y() - m1->y()) < EPS) && (m2->h() == m1->h()) && ((m2->x() - m1->x()) <  (m1->w() + EPS)))
			 != ((abs(m2->x() - m1->x()) < EPS) && (m2->w() == m1->w()) && ((m2->y() - m1->y()) <  (m1->h() + EPS)))) {
		
			 
			 	int x = m1->x();
			 	int y = m1->y();
			 	int w = m1->w();
			 	int h = m1->h();
				
				if ((abs(m1->x() - m2->x()) > EPS)) {
					w = m2->x() - m1->x() + m2->w();
				} else {
					h = m2->y() - m1->y() + m2->h();
				}				
				
				m1 = nm->at(index1);
				m2 = nm->at(index2);
				
				m1->resize(x, y, w, h);
				delete(m2);
				nm->erase(nm->begin() + index2);
				
				fused = true;
			 
			 }
			 
			return fused;
		}
	
	public:
		PrimBlock() {
			this->deleted = false;
		}
		
		PrimBlock(int x, int y, int w, int h, int number, int quantity, Fl_Color color) {
			this->deleted = false;
			
			markers.push_back(new Marker(x, y, w, h, color));
		
			this->color = color;
		
			term = Functions::numberToBitString(number);
			
			while (term.size() < quantity) {
				term = "0" + term;
			}
		}
	
		PrimBlock(int number, int quantity, Fl_Color color) {
		
			this->color = color;
		
			term = Functions::numberToBitString(number);
			
			while (term.size() < quantity) {
				term = "0" + term;
			}
			
		}
		
		PrimBlock(string term, vector<Marker*> markers, Fl_Color color) {
			this->deleted = false;
			this->term = term;
			this->color = color;
			this->markers = markers;
		}
		
		~PrimBlock() {
			this->cleanup();
		}
		
		string getTerm() {
			return term;
		}
		
		void markDeleted() {
			deleted = true;
		}
		
		bool isMarkedForDeletion() {
			return deleted;
		}
		
		vector<Marker*>* getMarker() {
			return &markers;
		}
		
		int compare(PrimBlock *other) {
			int index = -1;
			int diff = 0;
			
			for (int i = 0; i < term.size(); i++) {
				if (term[i] != other->getTerm()[i]) {
					diff++;
					index = i;
				}
			}
			
			if (diff != 1) {
				index = -1;
			}
			
			return index;
		}
		
		PrimBlock* fusePrim(PrimBlock *other, int index) {
			other->markDeleted();
			this->markDeleted();
			
			vector<Marker*> nm;
			
			for (int i = 0; i < other->getMarker()->size(); i++) {
				Marker *m = other->getMarker()->at(i);
				nm.push_back(new Marker(m->x(), m->y(), m->w(), m->h(), color));
			}
			
			for (int i = 0; i < this->getMarker()->size(); i++) {
				Marker *m = this->getMarker()->at(i);
				nm.push_back(new Marker(m->x(), m->y(), m->w(), m->h(), color));
			}
			
			string nterm = term;
			nterm.replace(index, 1, "-");
			
			PrimBlock *npb = new PrimBlock(nterm, nm, color);
			
			npb->fuseMarkers();
			
			return npb;
		}
		
		void setColor(Fl_Color color) {
			this->color = color;
			
			for (int i = 0; i < markers.size(); i++) {
				markers[i]->color(color);
			}
		}
		
		void cleanup() {
			for (int i = 0; i < markers.size(); i++) {
				delete(markers[i]);
			}
			markers.clear();
		}
		
		void fuseMarkers() {
			
			bool fusedSomething = true;
			
			while (fusedSomething) {
				fusedSomething = false;
				for (int i = 0; i < markers.size(); i++) {
					bool fused = false;
					for (int j = markers.size() - 1;j > i ; j--) {
						fused = fuseMarkers(&markers, i, j);
					}
					
					if (fused) 
						fusedSomething = true;
				}
			}
			
		}
			
};

#endif
