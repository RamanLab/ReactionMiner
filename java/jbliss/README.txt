jbliss - a Java wrapper for bliss
(c) 2008-2010 Tommi Junttila

jbliss is a Java wrapper for the bliss graph canonical labeling tool
(http://www.tcs.hut.fi/Software/bliss/).
The source code of bliss is included in this directory.
For performance critical software, please use the C++ interface of bliss
instead of this Java wrapper.

To compile jbliss on Linux platforms, just say
  make
and hope that everything goes smoothly.
To compile on non-Linux platforms, you're unfortunately pretty much
on your own.

Some documentation is produced in the 'doc' directory.
You can view it by opening the file 'doc/index.html' in your browser.

The important thing is always to include the file '<PATH>/lib/jbliss.jar'
in the "classpath" and the directory '<PATH>lib' in the "library path",
where <PATH> is the path to this directory.
Please see the examples below.

After succesfull compilation, you can inspect the files in the 'examples'
directory. For instance, you can try the following
  cd examples
  javac -classpath .:../lib/jbliss.jar TestEnumerateROM.java
  java -classpath .:../lib/jbliss.jar -Djava.library.path=../lib TestEnumerateROM
and should see an output consisting of the line:
There are 1044 graphs with 7 vertices

Similarly, try:
  javac -classpath .:../lib/jbliss.jar TestSimple.java
  java -classpath .:../lib/jbliss.jar -Djava.library.path=../lib TestSimple
