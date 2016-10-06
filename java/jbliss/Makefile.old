#
# Modify these two flags according to your system
#
# The directory where jni.h is to be found
#JNI_H_PATH = /usr/lib/j2sdk1.5-sun/include
JNI_H_PATH = /Library/Java/JavaVirtualMachines/jdk1.8.0_101.jdk/Contents/Home/include/
#JNI_H_PATH = /usr/lib/jvm/java-6-sun-1.6.0.17/include/
# Where jni_md.h is to be found
#JNI_MD_H_PATH = /usr/lib/j2sdk1.5-sun/include/linux
JNI_MD_H_PATH = /Library/Java/JavaVirtualMachines/jdk1.8.0_101.jdk/Contents/Home/include/darwin/
#JNI_MD_H_PATH = /usr/lib/jvm/java-6-sun-1.6.0.17/include/linux


JNI_INCLUDE = -I$(JNI_H_PATH) -I$(JNI_MD_H_PATH)

# Where the true bliss is to be found
BLISS_DIR = ./bliss-0.50
# bliss sources, objects, and compiler options
BLISS_SRCS += $(BLISS_DIR)/graph.cc
BLISS_SRCS += $(BLISS_DIR)/partition.cc
BLISS_SRCS += $(BLISS_DIR)/orbit.cc
BLISS_SRCS += $(BLISS_DIR)/uintseqhash.cc
BLISS_SRCS += $(BLISS_DIR)/heap.cc
BLISS_SRCS += $(BLISS_DIR)/timer.cc
BLISS_OBJS = $(addsuffix .o, $(basename $(BLISS_SRCS)))
BLISS_CC = g++
BLISS_CCFLAGS = -O3 -Wall --pedantic -fPIC

#
JAVA_SRCDIR = ./src
JAVA_PREFIX = fi/tkk/ics/jbliss
JAVA_SRCS += Graph.java
JAVA_SRCS += Utils.java
JAVA_SRCS += Reporter.java
JAVA_SRCS += DefaultReporter.java
JAVA_SRCFILES = $(addprefix $(JAVA_SRCDIR)/$(JAVA_PREFIX)/, $(JAVA_SRCS))
JAVA_CLASSFILES = $(addsuffix .class, $(basename $(JAVA_SRCFILES)))

# The wrapper sources, objects, and compiler options
WRAPPER_DIR = ./src-wrapper
#WRAPPER_SRCS += $(WRAPPER_DIR)/jbliss_AbstractGraph.cc
WRAPPER_SRCS += $(WRAPPER_DIR)/fi_tkk_ics_jbliss_Graph.cc
#WRAPPER_SRCS += $(WRAPPER_DIR)/jbliss_Digraph.cc
WRAPPER_OBJS = $(addsuffix .o, $(basename $(WRAPPER_SRCS)))
WRAPPER_CC = g++
WRAPPER_CCFLAGS = -O3 -Wall -fPIC
WRAPPER_INCLUDES = $(JNI_INCLUDE) -I$(BLISS_DIR)

#
CLASSPATHOPT = -classpath src

all:: lib jar doc

gmp:    LIBS += -lgmp
gmp:    BLISS_CCFLAGS += -DBLISS_USE_GMP

.SUFFIXES: .java .class

.java.class: $@
	javac $(CLASSPATHOPT) $<

$(WRAPPER_DIR)/%.o: $(WRAPPER_DIR)/%.cc
	$(WRAPPER_CC) $(WRAPPER_CCFLAGS) $(WRAPPER_INCLUDES) -c -o $@ $<

.cc.o: $(BLISS_SRCS)
	$(BLISS_CC) $(BLISS_CCFLAGS) -c -o $@ $<


bliss: ./bliss-0.50.zip
	rm -rf ./bliss-0.50
	unzip bliss-0.50.zip

headers: $(JAVA_CLASSFILES)
	javah -jni -d $(WRAPPER_DIR) $(CLASSPATHOPT) fi.tkk.ics.jbliss.Graph

jar: $(JAVA_CLASSFILES)
	cd $(JAVA_SRCDIR); jar cf ../lib/jbliss.jar $(JAVA_PREFIX)/*.class

lib: bliss $(BLISS_OBJS) headers $(WRAPPER_OBJS)
	$(WRAPPER_CC) $(JNI_INCLUDE) -I$(BLISS_DIR) -shared -o lib/libjbliss.dylib $(BLISS_OBJS) $(WRAPPER_OBJS) $(LIBS)

jbliss: lib JBliss.class

doc: $(JAVA_SRCFILES)
	cd doc; javadoc -public -classpath ../src fi.tkk.ics.jbliss

clean:
	rm -f $(JAVA_CLASSFILES)
	rm -f $(WRAPPER_OBJS)
	rm -rf ./bliss-0.50
	rm -f lib/jbliss.jar
	rm -f lib/libjbliss.so

