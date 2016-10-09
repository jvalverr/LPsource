/*
------------------------------------------------
Copyright (C) 2015-2016 by Jorge C. Valverde-Rebaza
Email: jvalverr@icmc.usp.br
This file is part of LPsource.

LPsource is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
LPsource is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should
have received a copy of the GNU General Public License along with LPsource. If not, see <http://www.gnu.org/licenses/>.
------------------------------------------------
*/

#ifndef NETWORK_H_INCLUDED
#define NETWORK_H_INCLUDED

#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <math.h>
#include <time.h>
#include <cstdlib>
#include <stdio.h>
#include <limits>

#include "Structures.h"

using namespace std;

class Network {
    private:
        unsigned int numEdges;
        unsigned int numNodes;
        unsigned int maxPathLength;
        long          maxNumFriendsPerUser;
        bool         isWeighted;

        vector<Node>  Users;       //list of all users
        vector<Group> Groups;      //list of user groups
        vector<Link>  TestLinks;   //list of all test links


        //methods
        void sortNeighborsOfUsers();
        void sortGroupsOfUsers();



    public:
        Network();
       ~Network();
        Network& operator=( const Network& );
        double getSampleCorrelationCoefficient(vector<vector<double> >&, vector<vector<double> >&) const;
        double getSampleCorrelationCoefficient(vector<double>&, vector<double>&) const;


        //reads
        void readLinksFile        ( const char* );
        void readGroupsFile       ( const char* );
        void readLinkGroupsFile   ( const char* );
        void readWeightedLinksFile ( const char* );


        //prints
        void printLinksList ( ostream& );
        void printLinksTest ( ostream& );
        void printWeightedLinksTest ( ostream& );
        void printGroups    ( ostream& );
        void printStatistics( ostream& );


        //sample
        void edgeRandomSubSampling( double );
        void setTestLinksList(vector<Link>);
        void sortLinkListTest();


        //structural properties
        bool          hasEdge( index_v, index_v )                           const;
        bool          isNetworkWeighted()                                   const;
        double        getWeight( index_v, index_v)                          const;
        double        getStrengthOfNode( index_v )                          const;
        unsigned int  getNumUsers()                                         const;
        unsigned int  getDegree( index_v )                                  const;
        unsigned int  getDiameter();
        unsigned long getNumEdgesFriendshipGraph();
        long          getMaxNumberFriendsPerUser();
        double        getAverageFriendsPerUser();
        double        getAverageDegree()                                    const;
        double        getClusteringCoefficient( index_v )                   const;
        double        getAverageClusteringCoefficient()                     const;
        double        getAverageAssortativityCoefficient()                  const;
        double        getHeterogeneity()                                    const;
        double        getAveragePathLenght();
        vector<index_v>     getNeighbors( index_v )                        const;
        vector<index_v>     getNeighbors( index_v, unsigned int )          const;
        vector<index_v>     getShortestPathLengths()                       const;
        vector<index_v>     getPathLengths( index_v )                      const;
        vector<index_v>     intersect(vector<index_v>, vector<index_v>)    const;
        vector<long>        intersect(vector<long>, vector<long>)          const;
        vector<index_v>     junction (vector<index_v>, vector<index_v>)    const;
        vector<Link>        getTrainLinks()                                const;


        //group properties
        unsigned int    getNumberOfGroups()                                  const;
        unsigned int    getOverlappingGroupsDegree(index_v)                  const;
        long            getIndexGroup( index_g );
        double          getAverageGroupMembershipPerUser()                   const;
        double          getAverageGroupSize()                                const;
        double          getAverageOverlappingGroupsDegree()                  const;
        double          getAverageGroupClusteringCoefficient()               const;
        double          getGroupClusteringCoefficient(Group)                 const;
        double          getOverlappingGroupsClusteringCoefficient( index_v ) const;
        double          getAverageOverlappingGroupsClusteringCoefficient()   const;
        vector<index_v> getOverlappingGroupsNeighbors(index_v)               const;
        vector<index_g> getGroups( index_v )                                 const;




};

#endif // NETWORK_H_INCLUDED
