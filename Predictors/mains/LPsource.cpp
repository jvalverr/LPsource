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

#include <iostream>

#include "../../Network.h"
#include "../../Timer.h"

//traditional structural measures
#include "../CommonNeighborsLP.h"
#include "../AdamicAdarLP.h"
#include "../JaccardLP.h"
#include "../ResourceAllocationLP.h"
#include "../PreferentialAttachmentLP.h"


//weighted traditional measures
#include "../WeightedCommonNeighborsLP.h"
#include "../WeightedAdamicAdarLP.h"
#include "../WeightedJaccardLP.h"
#include "../WeightedPreferentialAttachmentLP.h"
#include "../WeightedResourceAllocationLP.h"

//global traditional measures
#include "../KatzLP.h"
#include "../SimRankLP.h"
#include "../RootedPageRankLP.h"

//overlapping group measures (proposals)
#include "../WithinAndOutsideCommonGroupsLP.h"
#include "../CommonNeighborsOfGroupsLP.h"
#include "../TotalAndPartialOverlappingOfGroupsLP.h"



using namespace std;

void dataSetup();
void linkPredictionSetup( const char*, const char*, const char*, const char* );
void runLinkPredictionMethods(const Network& , const char* );
void linkPredictionProcess(const char*, const Network&, const char*);

int main()
{
    dataSetup();
    return 0;
}

void dataSetup(){
    const char* isLinks    = "../data/MyNetwork_edges.txt";
    const char* isGroups   = "../data/MyNetwork.groups";
    const char* test       = "MyNetwork_test.txt"; //the name of our test data file for each iteration
    const char* outPath    = "../output/";

    //If I have node groups formed by a nodes list
    linkPredictionSetup( isLinks, isGroups, outPath, test );

    //If I have node groups formed by links pairs
    //linkPredictionSetup( numNodes, isLinks, isGroups2, outPath, test );
}

void linkPredictionSetup( const char* isLinks, const char* isGroups, const char* outPath, const char* test ){
    Timer timer = Timer();
    timer.start();

    cout << "\n Start the process";
    Network network = Network();
    cout << "\n ... reading links";
    network.readLinksFile( isLinks );
    cout << "\n ... reading node groups";
    //If I have node groups formed by a nodes list
    network.readGroupsFile( isGroups ); //If you have node groups formed by links pairs use: network.readLinkGroupsFile( isGroups );

    cout << "\n ... calculating network properties";

    network.printStatistics( cout );

    cout << "\n\n ... making the random subsampling";
    double percentEdgesToTrain = 70;
    network.edgeRandomSubSampling( percentEdgesToTrain ); //traditional random subsampling

    cout << "\n ... saving the test links file";
    ofstream os2;
    char nameFileTest[200] = "";
    strcpy(nameFileTest, outPath);
    strcat(nameFileTest, test );
    os2.open( nameFileTest );
    network.printLinksTest( os2 );
    os2.close();

    cout << "\n start the link prediction process\n";
    runLinkPredictionMethods( network, outPath );

    double duration = timer.stop();
    cout << "\n End the link prediction process.\n Total time = ";
    timer.printTime(duration);

}


void runLinkPredictionMethods(const Network& network, const char* prefix ){
    vector<string> listMethods;

    listMethods.push_back( "AdamicAdar" );
    listMethods.push_back( "CommonNeighbors" );
    listMethods.push_back( "Jaccard" );
    listMethods.push_back( "PreferentialAttachment" );
    listMethods.push_back( "ResourceAllocation" );

    listMethods.push_back( "CommonNeighborsOfGroups" );
    listMethods.push_back( "TotalAndPartialOverlappingOfGroups" );
    listMethods.push_back( "WithinAndOutsideCommonGroups" );

    listMethods.push_back( "Katz" );
    listMethods.push_back( "SimRank" );
    listMethods.push_back( "RootedPageRank" );

    listMethods.push_back( "WeightedCommonNeighbors" );
    listMethods.push_back( "WeightedAdamicAdar" );
    listMethods.push_back( "WeightedJaccard" );
    listMethods.push_back( "WeightedResourceAllocation" );
    listMethods.push_back( "WeightedPreferentialAttachment" );

    for(unsigned int i = 0; i < listMethods.size(); i++){
        Timer timer = Timer();
        timer.start();
        linkPredictionProcess( listMethods[i].c_str(), network, prefix );
        double duration = timer.stop();
        timer.printTime(duration);
    }
}


void linkPredictionProcess(const char* predictorName, const Network& network, const char* prefix ){
     int lengthPath = 5;
     double beta = 0.05;
     double alpha = 0.15;
     double C = 0.8;
     bool predictorExist = true;
     LinkPredictor* predictor = NULL;

     if( strcmp( predictorName, "CommonNeighbors" ) == 0 ) {
        predictor = new CommonNeighborsLP( network );
     }
     else if( strcmp( predictorName, "AdamicAdar" ) == 0 ) {
        predictor = new AdamicAdarLP( network );
     }
     else if( strcmp( predictorName, "Jaccard" ) == 0 ) {
        predictor = new JaccardLP( network );
     }
     else if( strcmp( predictorName, "ResourceAllocation" ) == 0 ) {
        predictor = new ResourceAllocationLP( network );
     }
     else if( strcmp( predictorName, "PreferentialAttachment" ) == 0 ) {
        predictor = new PreferentialAttachmentLP( network );
     }
     else if( strcmp( predictorName, "CommonNeighborsOfGroups" ) == 0 ) {
        predictor = new CommonNeighborsOfGroupsLP( network );
     }
     else if( strcmp( predictorName, "TotalAndPartialOverlappingOfGroups" ) == 0 ) {
        predictor = new TotalAndPartialOverlappingOfGroupsLP( network );
     }
     else if( strcmp( predictorName, "WithinAndOutsideCommonGroups" ) == 0 ) {
        predictor = new WithinAndOutsideCommonGroupsLP( network );
     }
     else if( strcmp( predictorName, "WeightedCommonNeighbors" ) == 0 ) {
        predictor = new WeightedCommonNeighborsLP( network );
    }
    else if( strcmp( predictorName, "WeightedAdamicAdar" ) == 0 ) {
        predictor = new WeightedAdamicAdarLP( network );
    }
    else if( strcmp( predictorName, "WeightedJaccard" ) == 0 ) {
        predictor = new WeightedJaccardLP( network );
    }
    else if( strcmp( predictorName, "WeightedResourceAllocation" ) == 0 ) {
        predictor = new WeightedResourceAllocationLP( network );
	}
	else if( strcmp( predictorName, "WeightedPreferentialAttachment" ) == 0 ) {
	    predictor = new WeightedPreferentialAttachmentLP( network );
	}
	else if( strcmp( predictorName, "Katz" ) == 0 ) {
        predictor = new KatzLP( network , lengthPath, beta );
    }
    else if( strcmp( predictorName, "SimRank" ) == 0 ) {
        predictor = new SimRankLP( network, C );
	}
	else if( strcmp( predictorName, "RootedPageRank" ) == 0 ) {
	    predictor = new RootedPageRankLP( network, alpha );
	}
    else{
        cout<<"\n... The predictor " << predictorName << " does not exist";
        predictorExist = false;
    }

    if( predictorExist == true ){
        char predictFileAval[250] = "";
        strcpy( predictFileAval , prefix );
        strcat( predictFileAval , predictorName );
        strcat( predictFileAval ,  "-PredScores.txt" );

        ofstream fileScoresOut;
        cout<<"  ... link prediction method: " << predictorName<<" ";

        fileScoresOut.open( predictFileAval );
        unsigned int degree = 2;
        predictor->printScores( fileScoresOut , degree );
        fileScoresOut.close();
    }
}

