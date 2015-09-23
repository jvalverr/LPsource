/*
------------------------------------------------
Copyright (C) 2015 by Jorge C. Valverde-Rebaza
Email: jvalverr@icmc.usp.br
This file is part of LPsource.

The code to calculate this link prediction measure is based on the paper [3].

[3] Linyuan Lü and Tao Zhou. "Link prediction in complex networks: A survey". Physica A: Statistical Mechanics and its
    Applications, 390 (6), pp. 1150 - 1170, 2011.

LPsource is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
LPsource is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should
have received a copy of the GNU General Public License along with LPsource. If not, see <http://www.gnu.org/licenses/>.
------------------------------------------------
*/

#include "SimRankLP.h"

SimRankLP::SimRankLP( const Network& network, double C ) : LinkPredictor(network), C(C){
    //we calculate the simrank for all the pairs
    index_v n = this->network.getNumUsers();
	vector<vector<double> >* oldSimRanks = new vector<vector<double> >( n, vector<double>(n) );
	vector<vector<double> >* simRanks = new vector<vector<double> >( n, vector<double>(n) );
   for( index_v vertex = 0; vertex < n; vertex++ ) {
		oldSimRanks->at( vertex ).at( vertex ) = 1;
		simRanks->at( vertex ).at( vertex ) = 1;
	}

	for( unsigned int k = 0; true; k++ ) {
	    for( index_v vertex1 = 0; vertex1 < n; vertex1++ ) {
	        vector<index_v> inNeighbors1 = this->network.getNeighbors( vertex1 );
	        for( index_v vertex2 = vertex1+1; vertex2 < n; vertex2++ ) {
                vector<index_v> inNeighbors2 = this->network.getNeighbors( vertex2 );
                double& cell = simRanks->at( vertex1 ).at( vertex2 );
				cell = 0;
				if( inNeighbors1.size() > 0 && inNeighbors2.size() > 0 ) {
				    for(unsigned int it1 = 0; it1 < inNeighbors1.size(); it1++){
                        index_v  neighbor1 = inNeighbors1[it1];
                        const vector<double>& oneDim = oldSimRanks->at( neighbor1 );
                        for(unsigned int it2 = 0; it2 < inNeighbors2.size(); it2++){
                            index_v  neighbor2 = inNeighbors2[it2];
                            cell += oneDim.at( neighbor2 );
                        }
				    }
				    cell = C * cell / (inNeighbors1.size()*inNeighbors2.size());
				}
				simRanks->at( vertex2 ).at( vertex1 ) = cell;
	        }
	    }

	    //convergence
	    if( k > 1 ) {
	        double r = this->network.getSampleCorrelationCoefficient( *oldSimRanks, *simRanks );
	        if( r > 0.999 ) {
				this->scores = *simRanks; //save the simrank scores
				break;
			}
	    }
	    vector<vector<double> >* tempSimRanks = oldSimRanks;
		oldSimRanks = simRanks;
		simRanks = tempSimRanks;
	}
	delete simRanks;
	delete oldSimRanks;
}

SimRankLP::~SimRankLP() {
}



double SimRankLP::generateScore( index_v vertex, index_v neighbor ) {
   return this->scores.at( vertex ).at( neighbor );
}
