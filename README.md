# LPsource
A link prediction framework which considers the traditional topological measures from the state-of-the-art and 
new measures based on communities and overlapping groups information.

To build LPsource and prepare it for use, you must execute the Makefile file using the command 'make'. This will compile 
all components of LPsource framework. After this process completes without errors, you can make use of the LPsource binary 
saved into ./bin directory.

The following steps describe the process to quickly use the automated build system for link prediction on sample data sets:

1. Follow the instructions above to prepare the LPsource binary
2. Save the network to use into the directory ./data
3. Execute the LPsource binary using directly the command './LPsource' or 'nohup ./LPsource > LPsource.log &' to execute the binary as background (recommended for large scale networks)
4. After the execution, find into the directory ./output the ouput files (one for each link prediction measure) containing, each one, a list of predicted links and their corresponding scores.
