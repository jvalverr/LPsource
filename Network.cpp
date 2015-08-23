/*
------------------------------------------------
Copyright (C) 2015 by Jorge C. Valverde-Rebaza
Email: jvalverr@icmc.usp.br

This file is part of LPsource.

Parts of the code of this file to calculate the topological properties of the network are based on parts of LPmade software.
The code to calculate the group properties are based on papers [1] and [2].

[1] Jorge Valverde-Rebaza and Alneu Lopes. "Link Prediction in Online Social Networks Using Group Information". The 14th
    International Conference on Computational Science and Its Applications (ICCSA 2014). Guimarães, Portugal, July 2014.

[2] Jorge Valverde-Rebaza, Alan Valejo, Lilian Berton, Thiago Faleiros and Alneu Lopes. "A naive bayes model based on
    overlapping groups for link prediction in online social networks". The 30th ACM/SIGAPP Symposium On Applied Computing
    (SAC '15). Salamanca, Spain, April 2015.


LPsource is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
LPsource is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should
have received a copy of the GNU General Public License along with LPsource. If not, see <http://www.gnu.org/licenses/>.
------------------------------------------------
*/

#include "Network.h"
#include "Utils.h"



Network::Network(unsigned int numUsers): numEdges(0), numNodes(numUsers), maxNumFriendsPerUser(INV_LONG) {
    for(index_v i = 0; i < numUsers; i++){
        Node user;
        user.Groups.reserve(1);

        this->Users.push_back(user);
    }
}

Network::~Network() {
}


Network& Network::operator=( const Network& network ) {
	this->numEdges              = network.numEdges;
    this->numNodes              = network.numNodes;

    return *this;
}


////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////     READS                   ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////


void Network::readLinksFile( const char* linksFile ){
    ifstream isLinks;
    isLinks.open( linksFile, ios::in );

     if(isLinks.is_open()){
        while(!isLinks.eof()){
            unsigned int idUser1, idUser2;
            isLinks >> idUser1 >> idUser2;
            this->Users[idUser1].Neighbors.push_back(idUser2);
            this->numEdges++;
        }
     }
     isLinks.close();
     sortNeighborsOfUsers();
}

void Network::readGroupsFile(const char* groupsFile){
    ifstream isGroups;
    isGroups.open( groupsFile, ios::in );
    index_g indexGroup = 0;
    const unsigned int tam = MAX_GROUP_SIZE;

    if(isGroups.is_open()){
        while( !isGroups.eof() ){
            Group group;
            group.idGroup = indexGroup;
            unsigned int node;
            char str[tam] = "";
            isGroups.getline(str, tam);
            char* pair;
            pair = strtok(str, " ");

            bool flag = false;
            while(pair != NULL){
                node = atoi(pair);
                
                //save the group information
                Users[node].Groups.push_back( indexGroup );

                //save the place information
                group.Users.push_back(node);

                pair = strtok(NULL, " ");
            }

            //sort by user id
            sort(group.Users.begin() , group.Users.end());
            //remove duplicates
            group.Users.erase( unique(group.Users.begin() , group.Users.end()), group.Users.end());
            //insert in Groups vector
            Groups.push_back(group);
            //new id group
            indexGroup++;
        }
    }

    isGroups.close();
    sortGroupsOfUsers();
}

void Network::readLinkGroupsFile(const char* groupsFile){
    ifstream isGroups;
    isGroups.open( groupsFile, ios::in );
    index_g indexGroup = 0;
    const unsigned int tam = MAX_GROUP_SIZE;

    if(isGroups.is_open()){
        while( !isGroups.eof() ){
            Group group;
            group.idGroup = indexGroup;
            unsigned int countpair = 1;
            unsigned int node1, node2;
            char str[tam] = "";
            isGroups.getline(str, tam);
            char* pair;
            pair = strtok(str, ", ");

            bool flag = false;
            while(pair != NULL){
                if( countpair == 1 )
                    node1 = atoi(pair);
                if( countpair == 2 ){
                    node2 = atoi(pair);

                    //save the group information
                    Users[node1].Groups.push_back( indexGroup );
                    Users[node2].Groups.push_back( indexGroup );

                    //save the place information
                    group.Users.push_back(node1);
                    group.Users.push_back(node2);

                }

                flag = true;
                pair = strtok(NULL, ", ");
                if( countpair == 2 )
                    countpair = 1;
                else
                    countpair = 2;
            }

            if( flag == true ){
                //sort by user id
                sort(group.Users.begin() , group.Users.end());
                //remove duplicates
                group.Users.erase( unique(group.Users.begin() , group.Users.end()), group.Users.end());
                //insert in Groups vector
                Groups.push_back(group);
                //new id group
                indexGroup++;
            }
        }
    }

    isGroups.close();
    sortGroupsOfUsers();
}




////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////     PRINTS                   ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

void Network::printLinksList( ostream& os){
    os << "*Edges " << this->numEdges << "\n";

    for(index_v i = 0; i < this->Users.size(); ++i ) {
          for(index_v j = 0; j < Users[i].Neighbors.size(); ++j) {
            os <<  i << " " << this->Users[i].Neighbors[j] << "\n";
          }
    }
}

void Network::printLinksTest( ostream& os){
    for(index_v i = 0; i < TestLinks.size(); i++){
        os << TestLinks[i].indexVertex1 << " " << TestLinks[i].indexVertex2 << "\n";
    }
}


void Network::printGroups ( ostream& os ){
    os << "*Groups " << Groups.size() << "\n";
    for(unsigned int i = 0; i < Groups.size(); i++){
        os << i << " " << Groups[i].idGroup << " ";
        for(unsigned int j = 0; j < Groups[i].Users.size(); j++)
            os << Groups[i].Users[j] << " ";

        os << "\n";
    }
}


void Network::printStatistics( ostream& os ){
    os << "\n\nGeneral information";
    //caracteristicas de alto nivel do grafo
    os << "\nNumber of users \t |V| \t"                      << getNumUsers();
    os << "\nNumber of links \t |E| \t"                      << getNumEdgesFriendshipGraph();
    os << "\nAverage number of friends per user \t - \t"     << getAverageFriendsPerUser();
    os << "\nMax number of friends per user \t - \t"         << getMaxNumberFriendsPerUser();

    os << "\n\nStructural information";
    os << "\nAverage degree             \t <k> \t"           << getAverageDegree();
    os << "\nAverage path lenght            \t - \t"         << getAveragePathLenght();
    os << "\nDiameter (max path length)         \t D2 \t"    << getDiameter();
    os << "\nClustering coefficient \t C \t"                 << getAverageClusteringCoefficient();
    os << "\nAssortativity coefficient \t r \t"              << getAverageAssortativityCoefficient();
    os << "\nHeterogeneity \t H \t"                          << getHeterogeneity();

    os << "\n\nGroup information";
    os << "\nNumber of different groups  \t - \t"                   << getNumberOfGroups();
    os << "\nAverage of groups membership per user \t - \t"         << getAverageGroupMembershipPerUser();
    os << "\nAverage group size \t - \t"                            << getAverageGroupSize();
    os << "\nGroup Clustering coefficient \t C_g \t"                << getAverageGroupClusteringCoefficient();
    os << "\nAverage Overlapping Group Degree  \t k^g \t"           << getAverageOverlappingGroupsDegree();
    os << "\nOverlapping Group Clustering Coefficient  \t C^G \t"   << getAverageOverlappingGroupsClusteringCoefficient();

}



////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////     SAMPLING                 ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

void Network::edgeRandomSubSampling( double percentEdgesToTrain ){
    vector<index_v> edgeIndices = vector<index_v>();
    for( index_v index = 0; index < this->numEdges; index++ ) {
		edgeIndices.push_back( index );
	}

    srand( (unsigned)time(NULL) );
    random_shuffle( edgeIndices.begin(), edgeIndices.end(), randomNumberGeneratorPtr );
    double percentEdgesToTest = (100 - percentEdgesToTrain) / 100.0;
    unsigned int deletionCount = (unsigned int)( percentEdgesToTest * (this->numEdges/2) );
    edgeIndices.resize( deletionCount );
	sort( edgeIndices.begin(), edgeIndices.end() );

	index_v deletionIndex = 0, deletionCountIndex = 0;

	for(index_v i = 0; i < Users.size(); i++){
        for(index_v j = 0; j < Users[i].Neighbors.size(); j++){
            if( deletionCountIndex  == edgeIndices[deletionIndex] ){
                //save the test links index1->index2 and index2->index1
                Link link1;
                link1.indexVertex1 = i;
                link1.indexVertex2 = Users[i].Neighbors[j];
                Link link2;
                link2.indexVertex1 = Users[i].Neighbors[j];
                link2.indexVertex2 = i;

                TestLinks.push_back(link1);
                TestLinks.push_back(link2);

                //delete the links from the current network
                //delete the link formed by index1->index2
                Users[i].Neighbors.erase(remove(Users[i].Neighbors.begin(), Users[i].Neighbors.end(), Users[i].Neighbors[j]), Users[i].Neighbors.end());
                 //delete the link formed by index2->index1
                Users[link1.indexVertex2].Neighbors.erase(remove(Users[link1.indexVertex2].Neighbors.begin(), Users[link1.indexVertex2].Neighbors.end(), i), Users[link1.indexVertex2].Neighbors.end());

                deletionIndex++;
            }
            deletionCountIndex++;
        }
	}

	sortLinkListTest();
}



////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////     SORT                 ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

void Network::sortNeighborsOfUsers(){
   for(index_v i = 0; i < Users.size(); i++){
        sort(Users[i].Neighbors.begin(), Users[i].Neighbors.end());
   }
}


void Network::sortGroupsOfUsers(){
   for(index_v i = 0; i < Users.size(); i++){
        sort(Users[i].Groups.begin(), Users[i].Groups.end());
   }
}


void Network::sortLinkListTest(){
    sort(TestLinks.begin(), TestLinks.end(), linkCompareByNode1() );

    index_v indAct = 0;
    for(index_v ind = 1; ind < TestLinks.size(); ind++){
        if( TestLinks[ind].indexVertex1 != TestLinks[indAct].indexVertex1){
            sort(TestLinks.begin() + indAct, TestLinks.begin() + ind, linkCompareByNode2() );
            indAct = ind;
        }
    }
    sort(TestLinks.begin() + indAct, TestLinks.end(), linkCompareByNode2() );
}



////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////   STRUCTURAL  PROPERTIES                 ////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

bool Network::hasEdge( index_v indexVertex1, index_v indexVertex2 ) const{
    long first = 0, last = Users[indexVertex1].Neighbors.size() - 1, middle = (first+last)/2;

    while (first <= last) {
         if (Users[indexVertex1].Neighbors[middle] < indexVertex2)
            first = middle + 1;
         else if (Users[indexVertex1].Neighbors[middle] == indexVertex2) {
             return true;
         }
         else
            last = middle - 1;


        middle = (first + last)/2;
    }
    return false;
}


unsigned int Network::getNumUsers() const{
    return Users.size();
}

unsigned int Network::getDegree( index_v indexVertex ) const{
    return Users[indexVertex].Neighbors.size();
}

unsigned int Network::getDiameter(){
    if(maxPathLength <= 0){
       getAveragePathLenght();
    }
    return maxPathLength;
}

unsigned long Network::getNumEdgesFriendshipGraph(){
    return numEdges/2;
}

long Network::getMaxNumberFriendsPerUser(){
    if(maxNumFriendsPerUser == INV_LONG){
        unsigned long maxTemp = 0;
        for(index_v i = 0; i < Users.size(); i++){
            if( Users[i].Neighbors.size() > maxTemp )
                maxTemp = Users[i].Neighbors.size();
        }
        maxNumFriendsPerUser = maxTemp;
    }

    return maxNumFriendsPerUser;
}

double Network::getAverageFriendsPerUser(){
    return floor((double) numEdges / Users.size());
}

double Network::getAverageDegree() const{
    double sum = 0.0;
    for( index_v indexVertex = 0; indexVertex < Users.size(); indexVertex++ ) {
        if( Users[indexVertex].Neighbors.size() > 0 )
            sum += getDegree(indexVertex);
    }
    return sum / Users.size();
}

double Network::getClusteringCoefficient( index_v indexVertex ) const {
    if(Users[indexVertex].Neighbors.size() < 2)
        return 0.0;

    unsigned int edgeCount = 0;
    for(index_v index1 = 0; index1 < Users[indexVertex].Neighbors.size(); index1++){
        const long neighbor1 = Users[indexVertex].Neighbors[index1];
        for(index_v index2 = index1 + 1; index2 < Users[indexVertex].Neighbors.size(); index2++){
            const long neighbor2 = Users[indexVertex].Neighbors[index2];
            bool edge1 = hasEdge( neighbor1, neighbor2 );
            bool edge2 = hasEdge( neighbor2, neighbor1 );
            edgeCount += (unsigned int)edge1 + (unsigned int)edge2;
        }
    }
    return (double)edgeCount / (Users[indexVertex].Neighbors.size()*(Users[indexVertex].Neighbors.size()-1));
}

double Network::getAverageClusteringCoefficient() const{
    double sum = 0.0;
    for( index_v indexVertex = 0; indexVertex < Users.size(); indexVertex++ ) {
		sum += getClusteringCoefficient( indexVertex );
	}
	return sum / Users.size();
}

double Network::getAverageAssortativityCoefficient() const {
    vector<index_v> x = vector<index_v>();
	vector<index_v> y = vector<index_v>();

	for(index_v i = 0; i < Users.size(); i++){
	    for(index_v j = 0; j < Users[i].Neighbors.size(); j++){
            x.push_back(Users[i].Neighbors.size());
            y.push_back(getDegree(Users[i].Neighbors[j]));
	    }
	}
	return sampleCorrelationCoefficient( x, y );
}

double Network::getHeterogeneity()const{
    double num = 0, den = 0;
    for( index_v vertex = 0; vertex < Users.size(); vertex++ ) {
        double degree = getDegree(vertex);
        num += (degree * degree);
        den += degree;
    }

    double k1 = num / Users.size();
    double k2 = (den / Users.size()) *  (den / Users.size());
    return k1 / k2;
}

double Network::getAveragePathLenght(){
    double sum = 0.0;
    maxPathLength = 0;
    vector<unsigned int> lengths = getShortestPathLengths();
    for( index_v i = 0; i < lengths.size(); i++ ){
        sum = sum + lengths[i];

        if( lengths[i] > maxPathLength )
            maxPathLength = lengths[i];
    }
    return sum * (2.0 / (Users.size() * (Users.size() -1 ) ) );
}

vector<index_v> Network::getNeighbors( index_v indexVertex )const{
    return Users[indexVertex].Neighbors;
}

vector<index_v> Network::getNeighbors( index_v indexVertex, unsigned int degree )const{
    vector<bool> found = vector<bool>( Users.size() );
    vector<index_v>* oldSearch = new vector<index_v>();
	vector<index_v>* newSearch = new vector<index_v>();

	found.at( indexVertex ) = true;
	newSearch->push_back( indexVertex );

	for( unsigned int currentDegree = 0; currentDegree < degree; currentDegree++ ){
        delete oldSearch;
		oldSearch = newSearch;
		newSearch = new vector<index_v>();

		for( vector<index_v>::const_iterator searchIterator = oldSearch->begin(); searchIterator != oldSearch->end(); searchIterator++ ){
		    const index_v searchVertex = *searchIterator;

		    for(index_v j = 0; j < Users[searchVertex].Neighbors.size(); j++){
                index_v indexNeighbor = Users[searchVertex].Neighbors[j];

                if( !found.at( indexNeighbor ) ) {
                    found.at( indexNeighbor ) = true;
                    newSearch->push_back( indexNeighbor );
                }
		    }
		}
	}

	vector<index_v> results = vector<index_v>( newSearch->size() );
	for( index_v searchVertex = 0; searchVertex < newSearch->size(); searchVertex++ ) {
		results.at( searchVertex ) = newSearch->at( searchVertex );
	}

	delete newSearch;
	delete oldSearch;

	return results;
}

vector<index_v>  Network::getShortestPathLengths() const{
    vector<index_v> lengths;
    for( index_v i = 0; i < Users.size(); i++ ){
        vector<unsigned int> vertexLengths = getPathLengths( i );
        lengths.insert( lengths.end(), vertexLengths.begin(), vertexLengths.end() );
    }
    return lengths;
}

vector<index_v> Network::getPathLengths( index_v vertex ) const {
	vector<index_v> found = vector<unsigned int>( Users.size() );
	vector<index_v> oldSearch;
	found.at( vertex ) = 0;
	oldSearch.push_back( vertex );
	unsigned int currentDegree = 1;
	while( !oldSearch.empty() ) {
        vector<index_v> newSearch;
        for( index_v i = 0; i < oldSearch.size(); i++ ) {
			const index_v searchVertex = oldSearch[i];
			vector<index_v> neighbors = getNeighbors(searchVertex);
            for(index_v j = 0; j < neighbors.size(); j++){
                const index_v neighborVertex = neighbors[j];
                if( neighborVertex != vertex && found.at( neighborVertex ) == 0 ) {
                    found.at( neighborVertex ) = currentDegree;
                    newSearch.push_back( neighbors[j] );
                }
            }
        }
        ++currentDegree;
        oldSearch = newSearch;
    } //end of while

    return found;
}

vector<index_v> Network::intersect( vector<index_v> neighborsV1, vector<index_v> neighborsV2)const{
    vector<index_v> intesectList(neighborsV1.size() + neighborsV2.size());
    vector<index_v>::iterator it;
    it = set_intersection( neighborsV1.begin(), neighborsV1.end(), neighborsV2.begin(), neighborsV2.end(), intesectList.begin());
    intesectList.resize(it - intesectList.begin());
    return intesectList;
}

vector<long> Network::intersect( vector<long> neighborsV1, vector<long> neighborsV2)const{
    vector<long> intesectList(neighborsV1.size() + neighborsV2.size());
    vector<long>::iterator it;
    it = set_intersection( neighborsV1.begin(), neighborsV1.end(), neighborsV2.begin(), neighborsV2.end(), intesectList.begin());
    intesectList.resize(it - intesectList.begin());
    return intesectList;
}

vector<index_v> Network::junction(vector<index_v> neighborsV1, vector<index_v> neighborsV2)const{
    vector<index_v> unionList(neighborsV1.size() + neighborsV2.size());
    vector<index_v>::iterator it;
    it = set_union( neighborsV1.begin(), neighborsV1.end(), neighborsV2.begin(), neighborsV2.end(), unionList.begin());
    unionList.resize(it - unionList.begin());
    return unionList;
}



////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////   GROUP  PROPERTIES                   ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////


unsigned int Network::getNumberOfGroups() const{
    return Groups.size();
}

unsigned int Network::getOverlappingGroupsDegree(index_v vertex) const{
    return getOverlappingGroupsNeighbors(vertex).size();
}

long Network::getIndexGroup( index_g key ){
    long first = 0, last = Groups.size() - 1, middle = (first+last)/2;

    while (first <= last) {
         if (Groups[middle].idGroup < key)
            first = middle + 1;
         else if (Groups[middle].idGroup == key) {
             return middle;
         }
         else
            last = middle - 1;


        middle = (first + last)/2;
    }
    return INV_LONG;
}

double Network::getAverageGroupMembershipPerUser() const{
    double avg = 0.0;
    for( index_v vertex = 0; vertex < Users.size(); vertex++ ) {
            avg += Users[vertex].Groups.size();
    }
    return avg / Users.size();
}

double Network::getAverageGroupSize() const{
    double avg = 0.0;
    for(index_g i = 0; i < Groups.size(); i++){
        avg += Groups[i].Users.size();
    }

    return avg / Groups.size();
}

double Network::getAverageOverlappingGroupsDegree() const{
    double avg = 0.0;
    for( index_v vertex = 0; vertex < Users.size(); vertex++ ) {
        avg += getOverlappingGroupsDegree(vertex);
    }
    return avg / Users.size();
}


double Network::getAverageGroupClusteringCoefficient() const{
    double avg = 0.0;
    for(index_g i = 0; i < Groups.size(); i++)
        avg += getGroupClusteringCoefficient(Groups[i]);

    return avg / Groups.size();
}

double Network::getGroupClusteringCoefficient(Group group) const{
    double cci = 0.0;
    for(index_g i = 0; i < group.Users.size(); i++){
        cci += getClusteringCoefficient( group.Users[i] );
    }
    return cci / group.Users.size();
}

double Network::getOverlappingGroupsClusteringCoefficient( index_v vertex ) const{
    vector<index_v> neighbors = getOverlappingGroupsNeighbors( vertex );
    if(neighbors.size() < 2)
        return 0.0;

    unsigned int edgeCount = 0;
    for(index_v index1 = 0; index1 < neighbors.size(); index1++){
        const long neighbor1 = neighbors[index1];
        for(index_v index2 = index1 + 1; index2 < neighbors.size(); index2++){
            const long neighbor2 = neighbors[index2];
            bool edge1 = hasEdge( neighbor1, neighbor2 );
            bool edge2 = hasEdge( neighbor2, neighbor1 );
            edgeCount += (unsigned int)edge1 + (unsigned int)edge2;
        }
    }

    return (double) edgeCount / (neighbors.size()*(neighbors.size()-1));
}


double Network::getAverageOverlappingGroupsClusteringCoefficient() const{
    double sum = 0.0;
    for( unsigned int indexVertex = 0; indexVertex < Users.size(); indexVertex++ ) {
		sum += getOverlappingGroupsClusteringCoefficient( indexVertex );
	}
	return sum / Users.size();
}


vector<index_v> Network::getOverlappingGroupsNeighbors(index_v vertex) const{
    vector<index_v> neighbors = Users[vertex].Neighbors;
    vector<index_g> Ga = Users[vertex].Groups;
    vector<index_v> neighborsG;

    for(index_v i = 0; i < neighbors.size(); i++){
        vector<index_g> Gb = Users[neighbors[i]].Groups;

        for(index_g a = 0; a < Ga.size(); a++){
            for(index_g b = 0; b < Gb.size(); b++)
                if(Ga[a] == Gb[b]){
                    neighborsG.push_back(neighbors[i]);
                    b = Gb.size();
                    a = Ga.size();
                }
        }
    }
    return neighborsG;
}

vector<index_g> Network::getGroups( index_v indexVertex )const{
    return Users[indexVertex].Groups;
}
