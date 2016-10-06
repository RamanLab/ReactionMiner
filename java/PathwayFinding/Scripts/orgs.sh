#!/bin/sh

#  orgs.sh
#  
#
#  Created by Aravind Sankar on 8/13/16.
#
javac -cp ../src:../../Motif:../../lib/*:../../jbliss/:../../jbliss/lib/* ../src/pathways/OrgAnalysis.java
java -cp ../src:../../Motif:../../lib/*:../../jbliss/:../../jbliss/lib/* -Djava.library.path=../../jbliss/lib/ pathways.OrgAnalysis
