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

#include <algorithm>
#include <vector>
#include <math.h>



using std::vector;



ptrdiff_t randomNumberGenerator (ptrdiff_t i) { return rand()%i; }
ptrdiff_t (*randomNumberGeneratorPtr)(ptrdiff_t) = randomNumberGenerator;



void mergeVectors(unsigned int p, unsigned int q,  unsigned int r, vector<unsigned int>& vToSort, vector<double>& vRelated){
    vector<unsigned int> vToSortAux;
    vector<double> vRelatedAux;
    unsigned int i, j, k;

    for(i = 0; i < (r-p); i++){
        vToSortAux.push_back(0);
        vRelatedAux.push_back(0);
    }

    for (i = 0, k = p; k < q; i++, k++){
        vToSortAux.at(i)  = vToSort[k];
        vRelatedAux.at(i) = vRelated[k];
    }

    for (j = r-p-1, k = q; k < r; j--, k++){
        vToSortAux.at(j)  = vToSort[k];
        vRelatedAux.at(j) = vRelated[k];
    }

    i = 0;
    j = r - p - 1;
    for (k = p; k < r; k++){
        if (vToSortAux[i] <= vToSortAux[j]){
                vToSort.at(k)  = vToSortAux[i];
                vRelated.at(k) = vRelatedAux[i++];
        }
        else{
            vToSort.at(k)  = vToSortAux[j];
            vRelated.at(k) = vRelatedAux[j--];
        }
    }

    vToSortAux.clear();
    vRelatedAux.clear();
}

void sortWeightedLinks(unsigned int p, unsigned int r, vector<unsigned int>& vToSort, vector<double>& vRelated){
    if( p < r - 1 ){
        unsigned int q = (p + r)/2;
        sortWeightedLinks(p, q, vToSort, vRelated);
        sortWeightedLinks(q, r, vToSort, vRelated);
        mergeVectors(p, q, r, vToSort, vRelated);
    }
}

unsigned int sum( const vector<unsigned int>& x ) {
    unsigned int sum = 0;
    for( unsigned int i = 0; i < x.size(); i++ ) {
        sum += x.at( i );
    }

    return sum;
}

double sum( const vector<double>& x ) {
    double sum = 0;
    for( unsigned int i = 0; i < x.size(); i++ ) {
        sum += x.at( i );
    }

    return sum;
}

unsigned int getSize( const vector<vector<double> >& x ) {
    unsigned int count = 0;

    for( unsigned int i = 0; i < x.size(); i++ ) {
            count += x.at(i).size();
    }
    return count;
}

double mean( const vector<unsigned int>& x ){
    return (double) sum(x) / x.size();
}

double mean( const vector<double>& x ){
    return  sum(x) / x.size();
}

double sum( const vector<vector<double> >& x ) {
    double sum = 0;
    for( unsigned int i = 0; i < x.size(); i++ ) {
            sum += mean( x.at( i ) );
    }
    return sum;
}

double mean( const vector<vector<double> >& x ) {
    return (double) sum(x) / getSize(x);
}



double standardDeviation( const vector<unsigned int>& x, double xmean ) {
    double sum = 0;
	for( std::size_t i = 0; i < x.size(); i++ ) {
        sum += pow( x.at(i) - xmean, 2 );
    }

    return sqrt( sum / (x.size()-1) );
}

double standardDeviation( const vector<double>& x, double xmean ) {
    double sum = 0;
	for( std::size_t i = 0; i < x.size(); i++ ) {
        sum += pow( x.at(i) - xmean, 2 );
    }

    return sqrt( sum / (x.size()-1) );
}

double standardDeviation( const vector<vector<double> >& x ) {
    double xmean = mean( x );
    double sum = 0;

    for( unsigned int i = 0; i < x.size(); i++ ) {
        const vector<double>& row = x.at( i );
        for( unsigned int j = 0; j < row.size(); j++ ) {
                sum += pow( row.at( j ) - xmean, 2 );
        }
    }

	return sqrt( sum / (getSize( x ) - 1) );
}

double standardDeviation( const vector<vector<double> >& x, double xmean ) {
    double sum = 0;
	for( unsigned int i = 0; i < x.size(); i++ ) {
        const vector<double>& row = x.at( i );
        for( unsigned int j = 0; j < row.size(); j++ ) {
            sum += pow( row.at( j ) - xmean, 2 );
        }
    }

    return sqrt( sum / (getSize( x ) - 1) );
}





double sampleCorrelationCoefficient( const vector<unsigned int>& x, const vector<unsigned int>& y ){
    if( x.size() != y.size() ){
		throw "Vector sizes do not match\n";
	}

	double xmean = mean( x );
	double ymean = mean( y );
	double xStdDev = standardDeviation( x, xmean );
	double yStdDev = standardDeviation( y, ymean );
	double sum = 0;

	for( unsigned int i = 0; i < x.size(); i++ ) {
			sum += (x.at( i ) - xmean) * (y.at(i) - ymean);
	}

	return sum / ((x.size()-1) * xStdDev * yStdDev);
}

double sampleCorrelationCoefficient( const vector<double>& x, const vector<double>& y ){
    if( x.size() != y.size() ){
		throw "Vector sizes do not match\n";
	}

	double xmean = mean( x );
	double ymean = mean( y );
	double xStdDev = standardDeviation( x, xmean );
	double yStdDev = standardDeviation( y, ymean );
	double sum = 0;

	for( unsigned int i = 0; i < x.size(); i++ ) {
			sum += (x.at( i ) - xmean) * (y.at(i) - ymean);
	}

	return sum / ((x.size()-1) * xStdDev * yStdDev);
}

double sampleCorrelationCoefficient( const vector<vector<double> >& x, const vector<vector<double> >& y ){
    if(getSize(x) != getSize(y)){
        throw "Vector sizes do not match\n";
    }

    double xmean = mean( x );
    double ymean = mean( y );
    double xStdDev = standardDeviation( x, xmean );
    double yStdDev = standardDeviation( y, ymean );
    double sum = 0;

    for( unsigned int i = 0; i < x.size(); i++ ) {
        const vector<double>& xRow = x.at( i );
        const vector<double>& yRow = y.at( i );

        for( unsigned int j = 0; j < xRow.size(); j++ ) {
            sum += (xRow.at( j )-xmean) * (yRow.at( j )-ymean);
        }
    }

	return sum / ((getSize(x) - 1) * xStdDev * yStdDev);

}


#endif // UTILS_H_INCLUDED

