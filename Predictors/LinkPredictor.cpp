/*
------------------------------------------------
Copyright (C) 2015 by Jorge C. Valverde-Rebaza
Email: jvalverr@icmc.usp.br
This file is part of LPsource.

LPsource is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
LPsource is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should
have received a copy of the GNU General Public License along with LPsource. If not, see <http://www.gnu.org/licenses/>.
------------------------------------------------
*/


#include "LinkPredictor.h"

LinkPredictor::LinkPredictor( const Network& network ) : network(network) {
}

LinkPredictor::~LinkPredictor() {
}


void LinkPredictor::printScores( ostream& os, unsigned int degree){
    if(degree <= 1){
        cerr << "For degree = " <<  degree << " we assume that the degree is 2";
        degree = 2;
    }


    for(index_v indexVertex = 0; indexVertex < network.getNumUsers(); indexVertex++){
        vector<index_v> verticesToAnalize = network.getNeighbors( indexVertex, degree );

        for(unsigned int j = 0; j < verticesToAnalize.size(); j++ ){
            index_v indexNeighbor = verticesToAnalize[j];
            double predictValue = this->generateScore(indexVertex, indexNeighbor);

            if( predictValue != 0.0 ){
                os << indexVertex << " " << indexNeighbor << " " << predictValue <<"\n";
            }
        }
    }

}


