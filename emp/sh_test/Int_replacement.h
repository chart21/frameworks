#include "emp-sh2pc/emp-sh2pc.h"
using namespace emp;
using namespace std;

class Int_Replacement {

public:
    Int_Replacement(int, int);
    int counterA;
    int counterB;


};

Int_Replacement::Int_Replacement(int pCounterA, int pCounterB) {
    counterA = pCounterA;
    counterB = pCounterB;
}

