javac -cp src:../Motif:../lib/*:../jbliss/:../jbliss/lib/* src/pathways/SingleQueryPathways.java

java -cp src:../Motif:../lib/*:../jbliss/:../jbliss/lib/* -Djava.library.path=../jbliss/lib/ pathways.SingleQueryPathways

