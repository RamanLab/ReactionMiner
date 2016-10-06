javac -cp ../src:../../Motif:../../lib/*:../../jbliss/:../../jbliss/lib/* ../src/graph/GraphVisualize.java
java -cp ../src:../../Motif:../../lib/*:../../jbliss/:../../jbliss/lib/* -Djava.library.path=../../jbliss/lib/ graph.GraphVisualize $1 temp.dot
dot -Tpng temp.dot | display

rm temp.dot