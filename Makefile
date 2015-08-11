#------------------------------------------------
#Copyright (C) 2015 by Jorge C. Valverde-Rebaza
#Email: jvalverr@icmc.usp.br
#This file is part of LPsource.

#LPsource is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
#as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
#LPsource is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
#of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should
#have received a copy of the GNU General Public License along with LPsource. If not, see <http://www.gnu.org/licenses/>.
#------------------------------------------------

CONFIG := BIN
ifeq ($(CONFIG),DEBUG) 
	CFLAGS := -Wall -g
	BINDIR := ./debug
endif
ifeq ($(CONFIG),BIN)
	CFLAGS := -Wall -O3 -D NDEBUG
endif
CC := g++
NETWORK_BINS := $(patsubst %.cpp,%,$(notdir $(wildcard ./mains/*.cpp)))

all: network predictors
	
network: $(addprefix $(BINDIR)/,$(NETWORK_BINS))
predictors: ./bin/LPsource

$(BINDIR)/%: ./mains/%.o Network.o Structures.o Timer.o Utils.o
	$(CC) $(CFLAGS) $^ -o $@;

./bin/LPsource: ./Predictors/mains/LPsource.o $(patsubst %.cpp,%.o,$(wildcard ./Predictors/*.cpp)) Network.o 
	$(CC) $(CFLAGS) $^ -o $@;

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@;
