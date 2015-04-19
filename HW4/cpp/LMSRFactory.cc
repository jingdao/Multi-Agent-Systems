#include "LMSRFactory.h"

LMSRFactory::LMSRFactory(double b) {
	this->b = b;
	snprintf(name,16,"LMSR (b=%1.2f)",b);
}

LMSR* LMSRFactory::make() {
	return new LMSR(b);
}
