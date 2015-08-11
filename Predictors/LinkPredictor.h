/*
------------------------------------------------
Copyright (C) 2015 by Jorge C. Valverde-Rebaza
Email: jvalverr@icmc.usp.br
This file is part of LPsource.

The code structure of the class of this file is based on parts of LPmade software.

LPsource is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
LPsource is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should
have received a copy of the GNU General Public License along with LPsource. If not, see <http://www.gnu.org/licenses/>.
------------------------------------------------
*/


#ifndef LINKPREDICTOR_H_INCLUDED
#define LINKPREDICTOR_H_INCLUDED


#include "../Network.h"

using namespace std;

class LinkPredictor {
    protected:
		const Network& network;
        LinkPredictor();

    public:
        LinkPredictor( const Network& );
        virtual ~LinkPredictor();
        virtual double generateScore( index_v, index_v ) = 0;
        void printScores( ostream& , unsigned int );

};

#endif // LINKPREDICTOR_H_INCLUDED
