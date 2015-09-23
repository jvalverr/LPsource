/*
------------------------------------------------
Copyright (C) 2015 by Jorge C. Valverde-Rebaza
Email: jvalverr@icmc.usp.br
This file is part of LPsource.

The code to calculate this link prediction measure is based on the paper [4].

[4] Linyuan Lü and Tao Zhou. "Link prediction in weighted networks: The role of weak ties". EPL, 89 (1), 2010.

LPsource is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
LPsource is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should
have received a copy of the GNU General Public License along with LPsource. If not, see <http://www.gnu.org/licenses/>.
------------------------------------------------
*/

#include "WeightedJaccardLP.h"



WeightedJaccardLP::WeightedJaccardLP( const Network&  network ) : LinkPredictor(network) {
     if(this->network.isNetworkWeighted() == false)
        cerr << "  Network is not weighted. We will consider 1 as the weight of all links\n";
}

WeightedJaccardLP::~WeightedJaccardLP() {
}


double WeightedJaccardLP::generateScore( index_v indexVertex1, index_v indexVertex2 ) {
    vector<index_v> commonNeighbors = network.intersect(network.getNeighbors(indexVertex1), network.getNeighbors(indexVertex2));
    double num = 0.0;

    for( index_v i = 0; i < commonNeighbors.size(); i++) {
        num += this->network.getWeight( indexVertex1, commonNeighbors[i] ) + this->network.getWeight( indexVertex2, commonNeighbors[i]);
    }

    double den = this->network.getStrengthOfNode(indexVertex1) + this->network.getStrengthOfNode(indexVertex2);

	if( den != 0 )
        return num / den;

    return 0.0;

}
