#include "emp-sh2pc/emp-sh2pc.h"
#include "Int_replacement.h"
using namespace emp;
using namespace std;



int LEN = 200;
int BITSIZE = 8;




void test_setIntersectAlt3(string inputs_a[], string inputs_b[]) {
  //Integer product(BITSIZE, 1);
  Integer intersect[LEN];

	Integer a[LEN];
	Integer b[LEN];
  for (int i=0; i<LEN; i++)
    a[i] = Integer(BITSIZE, stoi(inputs_a[i]), ALICE);

  for (int i=0; i<LEN; i++)
    b[i] = Integer(BITSIZE, stoi(inputs_b[i]), BOB);

  for (int i=0; i<LEN; i++)
    intersect[i] = Integer(BITSIZE, 0, PUBLIC);

  sort(a,LEN);
  sort(b,LEN); 



  cout << "Set Intersection: ";
	
  //Integer counterA = Integer(LEN, 0, PUBLIC);
  //Integer counterB = Integer(LEN, 0, PUBLIC);
  // int counterA = 0;
  // int counterB = 0;
  
  // while(counterA < LEN & counterB < LEN)
  // {
  //   intersect[counterA] = If(a[counterA].equal(b[counterB]),a[counterA], intersect[counterA]);
  //   counterB = If(a[counterA].geq(b[counterB]),counterB+1, counterB);
  //   counterA = If(b[counterB].geq(a[counterA]),counterA+1, counterA);    
   
  // }

  Int_Replacement counter = Int_Replacement(0,0);
     while(counter.counterA < LEN & counter.counterB < LEN)
   {
     intersect[counter.counterA] = If(a[counter.counterA].equal(b[counter.counterB]),a[counter.counterA], intersect[counter.counterA]);
     counter = If(a[counter.counterA].geq(b[counter.counterB]), Int_Replacement(counter.counterA, counter.counterB+1), counter);
     counter = If(b[counter.counterB].geq(a[counter.counterB]), Int_Replacement(counter.counterA+1, counter.counterB), counter);
  //   counterA = If(b[counterB].geq(a[counterA]),counterA+1, counterA);    
   
   }
 
    for (int i = 0; i < LEN; i++)
    {    
      cout << "index " << i << ": " << intersect[i].reveal<int>() << endl;          
    }
    
  }              
    



int main(int argc, char** argv) {
    //int BITSIZE;

    // generate circuit for use in malicious library
    if (argc == 2 && strcmp(argv[1], "-m") == 0 ) {
        setup_plain_prot(true, "setIntersectAlt3.circuit.txt");
        //BITSIZE = 8;
        //string inputs[LEN] = {"0","0","0"};
        string inputs[LEN];
        for ( int i=0; i < LEN; i++ ) {
        inputs[i] = "0";
        }
        test_setIntersectAlt3(inputs, inputs);
        finalize_plain_prot();
	return 0;
    }

    // run computation with semi-honest model
    int port, party;
    parse_party_and_port(argv, &party, &port);
    NetIO * io = new NetIO(party==ALICE ? nullptr : "127.0.0.1", port);

    setup_semi_honest(io, party);

    if (argc != 3) {
      cout << "Usage: ./setIntersectAlt3 <party> <port> <BITSIZE>" << endl
           << "where <value> are the inputs of a party"
           << endl;
      delete io;
      return 0;
    }

    //BITSIZE = atoi(argv[3]);
    char fname_a[40];
    char fname_b[40];

    sprintf(fname_a, "data/setIntersectAlt3/%d.1.dat", BITSIZE);
    sprintf(fname_b, "data/setIntersectAlt3/%d.2.dat", BITSIZE);

    ifstream infile_a(fname_a);
    ifstream infile_b(fname_b);

    string inputs_a[LEN];
    string inputs_b[LEN];

    if( infile_a.is_open() && infile_b.is_open()) {
        for( int i=0; i<LEN; i++) {
            getline( infile_a, inputs_a[i]);
            getline( infile_b, inputs_b[i]);
        }
        infile_a.close();
        infile_b.close();
    }

    test_setIntersectAlt3(inputs_a, inputs_b);
    delete io;
}
