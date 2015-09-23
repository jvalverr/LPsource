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


#include <math.h>
#include "AdamicAdarLP.h"



AdamicAdarLP::AdamicAdarLP( const Network&  network ) : LinkPredictor(network) {
}

AdamicAdarLP::~AdamicAdarLP() {
}


double AdamicAdarLP::generateScore( index_v indexVertex1, index_v indexVertex2 ) {
	double result = 0.0;
	vector<index_v> commonNeighbors = network.intersect(network.getNeighbors(indexVertex1), network.getNeighbors(indexVertex2));

	for( index_v i = 0; i < commonNeighbors.size(); i++) {
        double logDen = log( this->network.getDegree( commonNeighbors[i] ) );

		if( logDen != 0.0)
            result += 1.0 / logDen ;
	}

    return result;
}
