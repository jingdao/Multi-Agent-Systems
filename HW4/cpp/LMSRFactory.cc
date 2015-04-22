#include "LMSRFactory.h"

LMSRFactory::LMSRFactory(double b) {
	this->b = b;
}

LMSR* LMSRFactory::make() {
	return new LMSR(b);
}
