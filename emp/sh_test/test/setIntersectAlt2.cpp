#include "emp-sh2pc/emp-sh2pc.h"
using namespace emp;
using namespace std;


int LEN = 200;
int BITSIZE = 8;


void test_setIntersectAlt2(string inputs_a[], string inputs_b[]) {
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


  cout << "Set Intersection: ";
	for( int i=0; i < LEN; i++ ) 
  {   
    for (int j = 0; j < LEN; j++)
    {
      intersect[i] = If(a[i].equal(b[j]), a[i], intersect[i]);
      //Bit matching = intersect[i][j] | a[i].equal(b[j]); 
      //intersect[i][j] = intersect[i][j] & matching; 

      // intersect[i][j] = intersect[i][j] | a[i].equal(b[j]) ;                  
    }
    cout << "index " << i << ": " << intersect[i].reveal<int>() << endl; 
  }
                 
    
}


int main(int argc, char** argv) {
    //int BITSIZE;

    // generate circuit for use in malicious library
    if (argc == 2 && strcmp(argv[1], "-m") == 0 ) {
        setup_plain_prot(true, "setIntersectAlt2.circuit.txt");
        //BITSIZE = 8;
        //string inputs[LEN] = {"0","0","0"};
        string inputs[LEN];
        for ( int i=0; i < LEN; i++ ) {
        inputs[i] = "0";
        }
        test_setIntersectAlt2(inputs, inputs);
        finalize_plain_prot();
	return 0;
    }

    // run computation with semi-honest model
    int port, party;
    parse_party_and_port(argv, &party, &port);
    NetIO * io = new NetIO(party==ALICE ? nullptr : "127.0.0.1", port);

    setup_semi_honest(io, party);

    if (argc != 3) {
      cout << "Usage: ./setIntersectAlt2 <party> <port> <BITSIZE>" << endl
           << "where <value> are the inputs of a party"
           << endl;
      delete io;
      return 0;
    }

    //BITSIZE = atoi(argv[3]);
    char fname_a[40];
    char fname_b[40];

    sprintf(fname_a, "data/setIntersectAlt2/%d.1.dat", BITSIZE);
    sprintf(fname_b, "data/setIntersectAlt2/%d.2.dat", BITSIZE);

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

    test_setIntersectAlt2(inputs_a, inputs_b);
    delete io;
}
