#pragma once

#include "base.h"

double Base::_radius = 1.0;

void Base::move(int x, int y) {
	//declaration

}

//destructor
Base::~Base() {

}

// getters
int Base::getX() const {
	return _x;
}
int Base::getY() const {
	return _y;
}


// setters
void Base::setX(int num) {
	_x = num;
}
void Base::setY(int num) {
	_y = num;
}
