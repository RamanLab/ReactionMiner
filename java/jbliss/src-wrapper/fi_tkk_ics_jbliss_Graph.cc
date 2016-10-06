#include <jni.h>
#include <stdio.h>
#include "graph.hh"
#include "fi_tkk_ics_jbliss_Graph.h"

static bliss::Graph *_j2c(const jlong j_ptr)
{
  bliss::Graph *c_ptr;
  c_ptr = (bliss::Graph *)j_ptr;
  //c_ptr = *(bliss::Graph **)&j_ptr;
  return c_ptr;
}

static jlong _c2j(bliss::Graph * const c_ptr)
{
  long j_ptr = (long)c_ptr;
  //long j_ptr = *(bliss::Graph **)&j_ptr = c_ptr;
  return j_ptr;
}


JNIEXPORT jlong JNICALL Java_fi_tkk_ics_jbliss_Graph_create
(JNIEnv *env, jobject o)
{
  bliss::Graph *graph = new bliss::Graph();
  assert(graph);
  return _c2j(graph);
}


JNIEXPORT void JNICALL Java_fi_tkk_ics_jbliss_Graph_destroy
(JNIEnv *env, jobject o, jlong true_bliss)
{
  assert(true_bliss != 0);
  bliss::Graph *graph = _j2c(true_bliss);
  assert(graph);
  delete graph;
}


JNIEXPORT jlong JNICALL Java_fi_tkk_ics_jbliss_Graph__1read_1dimacs
(JNIEnv *env, jclass c, jstring filename)
{
  /* Convert string from Java to C representation */
  const char *str = (*env).GetStringUTFChars(filename, NULL);
  if(str == NULL) {
    return 0; /* OutOfMemoryError already thrown */
  }
  /* Try opening the file, throw a Java exception if not succesfull */
  FILE *fp = fopen(str, "r");
  (*env).ReleaseStringUTFChars(filename, str);
  if(!fp) {
    jclass newExcCls = (*env).FindClass("java/io/FileNotFoundException");
    if (newExcCls == NULL) {
      /* Unable to find the exception class, give up. */
      return 0;
    }
    (*env).ThrowNew(newExcCls, NULL);
    return 0;
  }
  /* Read the graph from the file */
  bliss::Graph *graph = bliss::Graph::read_dimacs(fp, 0);
  assert(graph);
  fclose(fp); fp = 0;
  return _c2j(graph);
}


JNIEXPORT void JNICALL Java_fi_tkk_ics_jbliss_Graph__1write_1dimacs
(JNIEnv *env, jobject, jlong true_bliss, jstring filename)
{
  assert(true_bliss != 0);
  /* Convert string from Java to C representation */
  const char *str = env->GetStringUTFChars(filename, NULL);
  if(str == NULL) {
    return; /* OutOfMemoryError already thrown */
  }
  /* Try opening the file, throw a Java exception if not succesfull */
  FILE *fp = fopen(str, "w");
  env->ReleaseStringUTFChars(filename, str);
  if(!fp) {
    jclass newExcCls = env->FindClass("java/io/FileNotFoundException");
    if (newExcCls == NULL) {
      /* Unable to find the exception class, give up. */
      return;
    }
    env->ThrowNew(newExcCls, NULL);
    return;
  }
  /* Write the graph to the file */
  _j2c(true_bliss)->write_dimacs(fp);
  fclose(fp); fp = 0;
  return;
}


JNIEXPORT jlong JNICALL Java_fi_tkk_ics_jbliss_Graph__1permute
  (JNIEnv *env, jobject, jlong true_bliss, jintArray j_perm)
{
  assert(true_bliss != 0);
  bliss::Graph *graph = _j2c(true_bliss);
  assert(graph);

  /* Translate the permutation from a Java array to a C/C++ array */
  const unsigned int N = (unsigned int)env->GetArrayLength(j_perm);
  assert(N == graph->get_nof_vertices());
  unsigned int *perm = (unsigned int*)malloc(N * sizeof(unsigned int));
  if(!perm) {
    return _c2j(0); /* OutOfMemoryError already thrown */
  }
  for(unsigned int i = 0; i < N; i++)
    {
      jint j_image;
      env->GetIntArrayRegion(j_perm, i, 1, &j_image);
      perm[i] = (unsigned int)j_image;
    }
  
  /* Permute the graph */
  bliss::Graph *new_graph = graph->permute(perm);
  assert(new_graph);

  /* Release the C/C++ array */
  free(perm); perm = 0;

  return _c2j(new_graph);
}


JNIEXPORT jint JNICALL Java_fi_tkk_ics_jbliss_Graph__1add_1vertex
(JNIEnv *, jobject, jlong true_bliss, jint color)
{
  assert(true_bliss != 0);
  bliss::Graph *graph = _j2c(true_bliss);
  assert(graph);

  const unsigned int v = graph->add_vertex((unsigned int)color);
  return (jint)v;
}


JNIEXPORT void JNICALL Java_fi_tkk_ics_jbliss_Graph__1add_1edge
(JNIEnv *, jobject, jlong true_bliss, jint v1, jint v2)
{
  assert(true_bliss != 0);
  assert(0 <= v1);
  assert(0 <= v2);
  bliss::Graph *graph = _j2c(true_bliss);
  assert(graph);

  graph->add_edge(v1, v2);
}



struct _report_t {
  JNIEnv *env;
  jobject reporter;
  jmethodID report_method;
};


static void report_aut(void *param, unsigned int n, const unsigned int *aut)
{
  assert(param);
  assert(n > 0);
  assert(aut);

  struct _report_t *t = (struct _report_t *)param;
  JNIEnv * const env = t->env;

  /* Construct a Java int array for the automorphism */
  jintArray j_aut = env->NewIntArray(n);
  assert(j_aut);
  for(unsigned int i = 0; i < n; i++)
    {
      jint j_image = (jint)aut[i];
      env->SetIntArrayRegion(j_aut, i, 1, &j_image);
    }

  /* Call the report hook method */
  env->CallVoidMethod(t->reporter, t->report_method, j_aut); 

  /* Release the local reference to the array */
  env->DeleteLocalRef(j_aut);
}



JNIEXPORT void JNICALL Java_fi_tkk_ics_jbliss_Graph__1find_1automorphisms
(JNIEnv *env, jobject caller, jlong true_bliss, jobject reporter)
{
  assert(true_bliss != 0);
  bliss::Graph *graph = _j2c(true_bliss);
  assert(graph);

  bliss::Stats stats;

  if(reporter == NULL)
    {
      /* Find the automorphisms, do not report them */
      graph->find_automorphisms(stats, 0, (void*)0);
      return;
    }

  /* Allocate a temporary structure to store information for
     the report hook function */
  struct _report_t *t = (struct _report_t *)malloc(sizeof(struct _report_t));
  assert(t);
  t->env = env;
  t->reporter = caller; /*reporter;*/

  // Find the Java class of the Reporter interface
  jclass reporter_class = env->FindClass("fi/tkk/ics/jbliss/Graph");
  assert(reporter_class);
  // Find the report method in the interface
  jmethodID report_method = env->GetMethodID(reporter_class,
					     "_report",
					     "([I)V");
  assert(report_method);
  t->report_method = report_method;

  /* Find the automorphisms */
  graph->find_automorphisms(stats, &report_aut, (void*)t);

  /* Release the temporary structure */
  free(t);
}


JNIEXPORT jintArray JNICALL Java_fi_tkk_ics_jbliss_Graph__1canonical_1labeling
(JNIEnv *env, jobject caller, jlong true_bliss, jobject reporter)
{
  assert(true_bliss != 0);
  bliss::Graph* graph = _j2c(true_bliss);
  assert(graph);

  bliss::Stats stats;
  const unsigned int* cl = 0;

  if(reporter == NULL)
    {
      /* Find a canonical labeling,
	 do not report found generator automorphisms */
      cl = graph->canonical_form(stats, 0, (void*)0);
    }
  else
    {
      /* Allocate a temporary structure to store information for
	 the report hook function */
      struct _report_t *t = (struct _report_t *)malloc(sizeof(struct _report_t));
      assert(t);
      t->env = env;
      t->reporter = caller; /*reporter;*/

      // Find the Java class of the Reporter interface
      jclass reporter_class = env->FindClass("fi/tkk/ics/jbliss/Graph");
      assert(reporter_class);
      // Find the report method in the interface
      jmethodID report_method = env->GetMethodID(reporter_class,
						 "_report",
						 "([I)V");
      assert(report_method);
      t->report_method = report_method;
      
      /* Find a canonical labeling, report the found generator automorphisms */
      cl = graph->canonical_form(stats, &report_aut, (void*)t);

      /* Release the temporary structure */
      free(t);
    }
  
  /* Construct a Java int array for the canonical labeling */
  const unsigned int N = graph->get_nof_vertices();
  assert(cl or N == 0);
  jintArray j_canlab = env->NewIntArray(N);
  assert(j_canlab);
  for(unsigned int i = 0; i < N; i++)
    {
      jint j_image = (jint)cl[i];
      env->SetIntArrayRegion(j_canlab, i, 1, &j_image);
    }
  return j_canlab;
}
