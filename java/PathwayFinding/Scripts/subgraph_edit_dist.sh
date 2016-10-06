javac -cp ../src:../../Motif:../../lib/*:../../jbliss/:../../jbliss/lib/* ../src/graph/SubGraphEditDistance.java
java -cp ../src:../../Motif:../../lib/*:../../jbliss/:../../jbliss/lib/* -Djava.library.path=../../jbliss/lib/ graph.SubGraphEditDistance $1 $2 $3
