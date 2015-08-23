# LPsource
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                                             
Copyright (C) 2015 by Jorge C. Valverde-Rebaza	                                                                     
Email: jvalverr@icmc.usp.br	                                                                                            
Site: http://www.labic.icmc.usp.br/jvalverr/	

This file is part of LPsource.

LPsource is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. LPsource is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with LPsource. If not, see <http://www.gnu.org/licenses/>.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


LPsource is a link prediction framework which considers the traditional topological measures from the state-of-the-art and 
new measures based on communities and overlapping groups information.

To build LPsource and prepare it for use, you must execute the Makefile file using the command 'make'. This will compile 
all components of LPsource framework. After this process completes without errors, you can make use of the LPsource binary 
saved into ./bin directory.

The following steps describe the process to quickly use the automated build system for link prediction on sample data sets:

1. Follow the instructions above to prepare the LPsource binary
2. Save the network to use into the directory ./data
3. Execute the LPsource binary using directly the command './LPsource' or 'nohup ./LPsource > LPsource.log &' to execute the binary as background (recommended for large scale networks)
4. After the execution, find into the directory ./output the ouput files (one for each link prediction measure) containing, each one, a list of predicted links and their corresponding scores.

Is important to note that, for purposes of example, we call our network as MyNetwork, so the LPsource framework uses the files ./data/MyNetwork_edges.txt and ./data/MyNetwork.groups. The first file contains a list of all the links which constitute the network structure. The second file is necessary to calculate link prediction measures based on overlapping group information. Thus, each line in this file contains a list of of nodes belonging to the same social group. To obtain the .groups file you can use the code available here: https://github.com/jvalverr/ovLinkCom 

