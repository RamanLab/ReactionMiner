# Note that over writing of indexes will take place.

javac -cp ../src:../../Motif:../../lib/*:../../jbliss/:../../jbliss/lib/* ../src/ruleMining/ReactionRule/MiningRules.java
java -cp ../src:../../Motif:../../lib/*:../../jbliss/:../../jbliss/lib/* -Djava.library.path=../../jbliss/lib/ ruleMining.ReactionRule.MiningRules

