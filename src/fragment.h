#ifndef MYSQL_SMILES_FRAGMENT

#define MYSQL_SMILES_FRAGMENT

#include "config.h"
#include <iostream>
#include <openbabel/babelconfig.h>
#include <openbabel/obconversion.h>
#include <openbabel/mol.h>
#include <openbabel/fingerprint.h>
#include <set>
#include <vector>
                        
typedef std::set<std::vector<int> > Fset;
typedef std::set<std::vector<int> >::iterator SetItr;

using namespace std;
using namespace OpenBabel;

class Fragmentor {

private:
    Fset fragset;
    Fset ringset;
	stringstream _ss;
	unsigned int _flags;

public:
	Fset* fragment(const char* smiles);

private:
    void getFragments(std::vector<int> levels, std::vector<int> curfrag,
            int level, OBAtom* patom, OBBond* pbond);
    void DoReverses();
    void DoRings();

    unsigned int CalcHash(const std::vector<int>& frag);
};

#endif
