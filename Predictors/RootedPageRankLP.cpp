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


#include "RootedPageRankLP.h"

RootedPageRankLP::RootedPageRankLP( const Network& network, double alpha ) : LinkPredictor(network), alpha(alpha) {
}


RootedPageRankLP::~RootedPageRankLP() {
}



double RootedPageRankLP::generateScore( index_v vertex, index_v neighbor ) {
	if( this->vertex != vertex ) {
		this->vertex = vertex;
		this->scores = vector<double>( this->network.getNumUsers() );

		vector<double> oldPageRanks = vector<double>( this->network.getNumUsers() );
		index_v currentVertex = vertex;
		this->scores.at( currentVertex )++;

		for( index_v step = 1; true; step++ ) {
            vector<index_v> neighbors  = this->network.getNeighbors( currentVertex );
            if( neighbors.size() < 1 || (double)rand()/RAND_MAX < this->alpha ) {
				currentVertex = vertex;
			}
			else {
				index_v randomNeighbor = rand() % neighbors.size();
				currentVertex = neighbors.at( randomNeighbor );
			}

			this->scores.at( currentVertex )++;

			if( step == 100000 ) {
				oldPageRanks = this->scores;
			}
			else if( step % 100000 == 0 ) {
                double r = this->network.getSampleCorrelationCoefficient( oldPageRanks, this->scores );

                if( r > 0.9999 ) {
					return this->scores.at( neighbor );
				}
				else {
					oldPageRanks = this->scores;
				}
			}
		}
	}

	return this->scores.at( neighbor );
}
