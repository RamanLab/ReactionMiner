# ReactionMiner

ReactionMiner is a tool to predict (bio)chemical reactions using graph mining. It currently is built on the KEGG database.

## Getting Started

1. Clone this repository to your computer using `git`, or [download the entire repository](https://github.com/RamanLab/ReactionMiner/archive/master.zip) and decompress it.
2. Unzip `data.zip` in its current (root) directory
3. `jbliss` needs to be installed, by using `make` command. In the `Makefile`, edit the path of the `JNI_H` and `JNI_MD_H` libraries. Also change `libjbliss.dylib` to `libjbliss.so` while compiling, if on a Linux system.

## Using ReactionMiner to predict paths

1. Use `ReactionMiner/java/PathwayFinding/Scripts/predict_paths.sh` script to use the ReactionMiner prediction algorithm. This requires a file as input. The file should contain the source and target molecules with KEGG ids, in a tab separated format. Alternatively, it can contain the entire path in a tab-separated format, in which case the paths will be predicted between the first and last molecules. 
2. For using an unknown molecule (not present in the KEGG database) as query, add the mol file to the `data/molStereo_Hadded_PH_CoA/` directory and use the name of the mol file in the query.
3. By default, pathway prediction will happen in the KEGG Universe. To predict paths in a different organism, an extra command line argument needs to be provided with the organism ID in the Path2Models database.

### Usage
````
cd java/PathwayFinding/Scripts/
./predict_paths.sh ../../../Queries/glyco_p1.txt BMID000000142681
````
In this case, paths will be predicted between [C00267](http://www.genome.jp/dbget-bin/www_bget?cpd:C00267) and [C00118](http://www.genome.jp/dbget-bin/www_bget?cpd:C00118) in _E. coli_

### Retrosynthesis Examples

````
cd java/PathwayFinding/Scripts/
./predict_paths.sh ../../../Queries/Retrosynthesis/artemisinate.txt
````

## Authors

* [Aravind Sankar](https://github.com/aravindsankar28)
* [Sayan Ranu](https://github.com/sayanranu)
* [Karthik Raman](https://github.com/karthikraman)

### Citing ReactionMiner
If you use ReactionMiner in your work, please cite
>Aravind Sankar, Sayan Ranu and Karthik Raman (2017) "Predicting novel metabolic pathways through subgraph mining
" _Bioinformatics_ **In Press** [doi:10.1093/bioinformatics/btx481](https://academic.oup.com/bioinformatics/advance-article-abstract/doi/10.1093/bioinformatics/btx481/4042129)

## License

1. By using the software enclosed in this package (ReactionMiner), you agree to become bound by the terms of this license. 
2. This software is for your internal use only. Please DO NOT redistribute it without the permission from the authors.
3. This software is for **academic use only**. No other usage is allowed without a written permission from the authors. It cannot be used for any commercial interest.
4. The authors appreciate it if you can send us your feedback including any bug report.
5. The authors do not hold any responsibility for the correctness of this software, though we cross-checked all experimental results.

## Acknowledgments

This work was supported by the [Indian Institute of Technology Madras](http://www.iitm.ac.in/) grant CSE/14-15/5643/NFSC/SAYN to Sayan Ranu and the [Initiative for Biological Systems Engineering (IBSE)](https://web.iitm.ac.in/ibse) at IIT Madras.
