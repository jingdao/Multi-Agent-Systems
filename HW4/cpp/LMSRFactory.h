#pragma once
#include <stdio.h>
#include "LMSR.h"

class LMSRFactory {
	public:
		LMSRFactory(double b);
		LMSR* make();

	private:
		double b;
};
