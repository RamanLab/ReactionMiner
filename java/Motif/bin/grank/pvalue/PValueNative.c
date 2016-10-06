#include <jni.h>
#include "grank_pvalue_PValueNative.h"
#include <gsl/gsl_sf_gamma.h>

    /**
     * @param p double[]
     * @param X int[]
     * @param Z int
     * @return double
     */
    JNIEXPORT jdouble JNICALL Java_grank_pvalue_PValueNative_lowerProb
    (JNIEnv * env, jclass jc, jdoubleArray p, jintArray X, jint Z) {
  jsize Xlen = ( * env) -> GetArrayLength(env, X);
  jint * Xbody = ( * env) -> GetIntArrayElements(env, X, 0);
  jsize plen = ( * env) -> GetArrayLength(env, p);
  jdouble * pbody = ( * env) -> GetDoubleArrayElements(env, p, 0);

  double prod = 1;
  int a = Z;
  int i;
  double sum;
  for (i = Xlen - 1; i >= 0; i--) {
    if (Xbody[i] == 0) {
      continue;
    }
    /*
	 double sum = Beta.regularizedBeta(p[i], X[i], a - X[i] + 1);
     double gsl_sf_beta_inc(const double a, const double b, const double x)
    */
    sum = gsl_sf_beta_inc(Xbody[i], a - Xbody[i] + 1, pbody[i]);
    prod *= sum;
    a -= Xbody[i];
  }
  (*env)->ReleaseIntArrayElements(env, X, Xbody, 0);
  (*env)->ReleaseDoubleArrayElements(env, p, pbody, 0);
  return prod;

}
