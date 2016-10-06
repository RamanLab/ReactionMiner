javac -cp src:../Motif:../Maximal-Common-Subgraph/*:../Maximal-Common-Subgraph:../lib/*:../jbliss/:../jbliss/lib/* src/pathways/Validation.java
java -cp src:../Motif:../Maximal-Common-Subgraph/*:../Maximal-Common-Subgraph:../lib/*:../jbliss/:../jbliss/lib/* -Djava.library.path=../jbliss/lib/ pathways.Validation $1 $2
