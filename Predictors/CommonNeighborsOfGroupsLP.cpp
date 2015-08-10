



#include <math.h>
#include "CommonNeighborsOfGroupsLP.h"

CommonNeighborsOfGroupsLP::CommonNeighborsOfGroupsLP( const Network& network ): LinkPredictor(network) {
}

CommonNeighborsOfGroupsLP::~CommonNeighborsOfGroupsLP() {
}


double CommonNeighborsOfGroupsLP::generateScore( index_v indexVertex1, index_v indexVertex2 ) {
    vector<index_v> CommonNeighborsList = network.intersect(network.getNeighbors(indexVertex1), network.getNeighbors(indexVertex2));

    vector<index_g> v1 = network.getGroups( indexVertex1 );
    vector<index_g> v2 = network.getGroups( indexVertex2 );
    double cng = 0.0;

    for(index_v index = 0; index < CommonNeighborsList.size(); index++){
        vector<index_g> v3 = network.getGroups( CommonNeighborsList[index] );

        vector<index_g> v_i13 = network.intersect(v1, v3);
        if( v_i13.size() > 0 ){
            cng++;
        }
        else{
            vector<index_g> v_i23 = network.intersect(v2, v3);
            if( v_i23.size() > 0 ){
                cng++;
            }
        }
     }

     return cng;
}

