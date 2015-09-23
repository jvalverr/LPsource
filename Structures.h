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

#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

#include <vector>


using std::vector;
using std::pair;

typedef unsigned int index_v;
typedef unsigned int index_g;

const long   INV_LONG                = -1;
const double INF_P                   = 990000;
const unsigned int MAX_GROUP_SIZE    = 8000000;



/******************************************************/
/***************** Node of a network      **************/
/********************************************************/
struct Node{
    vector<index_v>  Neighbors;   //list of indexes of neighborhood of the node
    vector<double>   Weights;     //list of weights of relationships between the node and their neighbors
    vector<index_g>  Groups;      //list of labels of groups to which the node belong to
};




/******************************************************/
/********** Link between a pair of nodes      **********/
/********************************************************/
struct Link{
    index_v indexVertex1;
    index_v indexVertex2;
    double score;
    bool classLink; //0 = non-existent, 1 = existent
};




/******************************************************/
/** List of Indexes of Users belonging to the group ***/
/*******************************************************/
struct Group{
    index_g idGroup;
    vector<index_v> Users;
};






struct linkCompareByNode1{
    bool operator() (const Link& link1, const Link& link2 )const { return (link1.indexVertex1 < link2.indexVertex1); }
};

struct linkCompareByNode2{
    bool operator() (const Link& link1, const Link& link2 )const { return (link1.indexVertex2 < link2.indexVertex2); }
};

struct scoreLinkCompare{
    bool operator() (const Link& link1, const Link& link2 )const { return (link1.score > link2.score); }
};





#endif // STRUCTURES_H_INCLUDED
