#!/bin/bash

#  orgs_specific.sh
#  
#
#  Created by Aravind Sankar on 8/13/16.
#
find ../src -name "*.class" -type f -delete
javac -cp ../src:../../Motif:../../lib/*:../../jbliss/:../../jbliss/lib/* ../src/pathways/OrgSpecific.java
java -cp ../src:../../Motif:../../lib/*:../../jbliss/:../../jbliss/lib/* -Djava.library.path=../../jbliss/lib/ pathways.OrgSpecific $1 $2
