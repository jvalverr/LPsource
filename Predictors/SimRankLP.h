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

#ifndef SIMRANKLP_H_INCLUDED
#define SIMRANKLP_H_INCLUDED


#include <vector>
#include "../Network.h"
#include "LinkPredictor.h"

using std::vector;

class SimRankLP : public LinkPredictor {
	private:
		double C;
		vector<vector<double> > scores;
		SimRankLP( const Network& );
	protected:
	public:
        SimRankLP( const Network&, double);
		~SimRankLP();
		double generateScore ( index_v, index_v );
    };


#endif // SIMRANKLP_H_INCLUDED
