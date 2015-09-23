/*
------------------------------------------------
Copyright (C) 2015 by Jorge C. Valverde-Rebaza
Email: jvalverr@icmc.usp.br
This file is part of LPsource.

The code to calculate this link prediction measure is based on the paper [5].

[5] Murata, T. and Moriyasu, Sakiko. "Link Prediction of Social Networks Based on Weighted Proximity Measures". IEEE/WIC/ACM
    International Conference on Web Intelligence, pp. 85 - 88, IEEE, 2007.

LPsource is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
LPsource is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should
have received a copy of the GNU General Public License along with LPsource. If not, see <http://www.gnu.org/licenses/>.
------------------------------------------------
*/




#include "WeightedPreferentialAttachmentLP.h"



WeightedPreferentialAttachmentLP::WeightedPreferentialAttachmentLP( const Network&  network ) : LinkPredictor(network) {
     if(this->network.isNetworkWeighted() == false)
        cerr << "  Network is not weighted. We will consider 1 as the weight of all links\n";
}

WeightedPreferentialAttachmentLP::~WeightedPreferentialAttachmentLP() {
}


double WeightedPreferentialAttachmentLP::generateScore( index_v indexVertex1, index_v indexVertex2 ) {
    return this->network.getStrengthOfNode(indexVertex1) * this->network.getStrengthOfNode(indexVertex2);
}
