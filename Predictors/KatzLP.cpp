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



#include <stack>
#include <utility>
#include <cmath>
#include "KatzLP.h"

using std::stack;
using std::make_pair;
using std::cout;
using std::cerr;

KatzLP::KatzLP( const Network& network, unsigned int l, double beta ) : LinkPredictor(network), l(l), beta(beta), lookup(vector<double>(l+1)) {
	for( unsigned int degree = 0; degree <= l; ++degree ) {
		this->lookup.at( degree ) = pow( beta, degree );
	}
}

KatzLP::~KatzLP() {
}

double KatzLP::generateScore( index_v vertex, index_v neighbor ) {
    if( this->vertex != vertex ) {
		this->vertex = vertex;
		this->scores = vector<double>( this->network.getNumUsers()  );

		vector<index_v> oldSearch;
		vector<unsigned long> oldHits( this->network.getNumUsers()  );

		oldSearch.push_back( vertex );
		oldHits.at( vertex ) = 1;
		for( unsigned int degree = 1; degree <= this->l; ++degree ) {
			vector<unsigned long> newHits( this->network.getNumUsers() );
			vector<bool> found( this->network.getNumUsers() );
			vector<index_v> newSearch;
			for( vector<index_v>::const_iterator vertexIterator = oldSearch.begin(); vertexIterator != oldSearch.end(); ++vertexIterator ) {
				const index_v searchVertex = *vertexIterator;
                vector<index_v> neighbor_set = this->network.getNeighbors(searchVertex);
                for(unsigned int neighborIterator = 0; neighborIterator < neighbor_set.size(); neighborIterator++){
                    const index_v neighborVertex = neighbor_set[neighborIterator];
                    newHits.at( neighborVertex ) += oldHits.at( searchVertex );
                    if( !found.at( neighborVertex ) ) {
						found.at( neighborVertex ) = true;
						newSearch.push_back( neighborVertex );
					}
                }
			}
			double factor = this->lookup.at( degree );
			for( size_t i = 0; i < this->scores.size(); ++i ) {
				this->scores.at( i ) += factor * newHits.at( i );
			}
			oldSearch.swap( newSearch );
			oldHits.swap( newHits );
		}
	}

	return (double) this->scores.at( neighbor );
}
