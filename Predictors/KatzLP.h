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

#ifndef KATZLP_H_INCLUDED
#define KATZLP_H_INCLUDED


#include "../Network.h"
#include "LinkPredictor.h"


class KatzLP : public LinkPredictor {
	private:
		unsigned int l;
		double beta;
		vector<double> lookup;
		vector<double> scores;
		KatzLP( const Network& );
	protected:
	public:
		KatzLP( const Network&, unsigned int, double );
		~KatzLP();
		double generateScore( index_v, index_v );
};


#endif // KATZLP_H_INCLUDED
