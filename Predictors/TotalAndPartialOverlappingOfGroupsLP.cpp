/*
------------------------------------------------
Copyright (C) 2015-2016 by Jorge C. Valverde-Rebaza
Email: jvalverr@icmc.usp.br
This file is part of LPsource.

The code to calculate this link prediction measure is based on the paper [1].

[1] Jorge Valverde-Rebaza and Alneu Lopes. "Link Prediction in Online Social Networks Using Group Information". The 14th
    International Conference on Computational Science and Its Applications (ICCSA 2014). Guimarães, Portugal, July 2014.

LPsource is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
LPsource is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should
have received a copy of the GNU General Public License along with LPsource. If not, see <http://www.gnu.org/licenses/>.
------------------------------------------------
*/

#include "TotalAndPartialOverlappingOfGroupsLP.h"

TotalAndPartialOverlappingOfGroupsLP::TotalAndPartialOverlappingOfGroupsLP( const Network& network): LinkPredictor(network) {
}

TotalAndPartialOverlappingOfGroupsLP::~TotalAndPartialOverlappingOfGroupsLP() {
}


double TotalAndPartialOverlappingOfGroupsLP::generateScore( index_v indexVertex1, index_v indexVertex2 ) {
    vector<index_v> CommonNeighborsList = network.intersect(network.getNeighbors(indexVertex1), network.getNeighbors(indexVertex2));

    vector<index_g> v1 = network.getGroups( indexVertex1 );
    vector<index_g> v2 = network.getGroups( indexVertex2 );
    double cng = 0.0, tog = 0.0;

    for(index_v index = 0; index < CommonNeighborsList.size(); index++){
        vector<index_g> v3 = network.getGroups( CommonNeighborsList[index] );

        vector<index_g> v_i13 = network.intersect(v1, v3);
        vector<index_g> v_i23 = network.intersect(v2, v3);
        if( v_i13.size() > 0 ){
            cng++;

            if( v_i23.size() > 0 ){
                tog++;
            }
        }
        else{
            if( v_i23.size() > 0 ){
               cng++;
            }
        }
     }

    double pog = cng - tog;
    if( pog == 0.0 )
        return tog;

    return tog / pog;
}
