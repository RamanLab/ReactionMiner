javac -cp .:../lib/*:../jbliss/:../jbliss/lib/* openBabel/GraphConverter2.java 

java -cp src:../Motif:../lib/*:../jbliss/:../jbliss/lib/* -Djava.library.path=../jbliss/lib/ openBabel/GraphConverter2 $1

