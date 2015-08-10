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


#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED


#include <vector>
#include <cmath>

using std::vector;


ptrdiff_t randomNumberGenerator (ptrdiff_t i) { return rand()%i; }
ptrdiff_t (*randomNumberGeneratorPtr)(ptrdiff_t) = randomNumberGenerator;


double standardDeviation( const vector<unsigned int>& x, double xmean ) {
    double sum = 0;
	for( std::size_t i = 0; i < x.size(); i++ ) {
        sum += pow( x.at(i) - xmean, 2 );
    }

    return sqrt( sum / (x.size()-1) );
}

unsigned int sum( const vector<unsigned int>& x ) {
    unsigned int sum = 0;
    for( std::size_t i = 0; i < x.size(); i++ ) {
        sum += x.at( i );
    }

    return sum;
}

double mean( const vector<unsigned int>& x ){
    return (double) sum(x) / x.size();
}

double sampleCorrelationCoefficient( const vector<unsigned int>& x, const vector<unsigned int>& y ){
    if( x.size() != y.size() ) {
		throw "Statistics::r - vector sizes do not match\n";
	}

	double xmean = mean( x );
	double ymean = mean( y );
	double xStdDev = standardDeviation( x, xmean );
	double yStdDev = standardDeviation( y, ymean );
	double sum = 0;

	for( std::size_t i = 0; i < x.size(); i++ ) {
			sum += (x.at( i ) - xmean) * (y.at(i) - ymean);
	}

	return sum / ((x.size()-1) * xStdDev * yStdDev);
}

#endif // UTILS_H_INCLUDED
