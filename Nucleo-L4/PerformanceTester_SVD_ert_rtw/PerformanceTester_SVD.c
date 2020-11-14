/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: PerformanceTester_SVD.c
 *
 * Code generated for Simulink model 'PerformanceTester_SVD'.
 *
 * Model version                  : 1.0
 * Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
 * C/C++ source code generated on : Sat Nov 14 09:06:04 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: STMicroelectronics->STM32 32-bit Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "PerformanceTester_SVD.h"
#define NumBitsPerChar                 8U

/* Block signals and states (default storage) */
DW rtDW;

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Real-time model */
RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;

/* Forward declaration for local functions */
static void isfinite(const real_T x[5000], boolean_T b[5000]);
static boolean_T all(const boolean_T x[5000]);
static boolean_T anyNonFinite(const real_T x[5000]);
static real_T xnrm2(int32_T n, const real_T x[5000], int32_T ix0);
static real_T xdotc(int32_T n, const real_T x[5000], int32_T ix0, const real_T
                    y[5000], int32_T iy0);
static void xaxpy(int32_T n, real_T a, int32_T ix0, const real_T y[5000],
                  int32_T iy0, real_T b_y[5000]);
static real_T xnrm2_n(int32_T n, const real_T x[50], int32_T ix0);
static void xaxpy_n5iz(int32_T n, real_T a, const real_T x[5000], int32_T ix0,
  real_T y[100], int32_T iy0);
static void xaxpy_n5(int32_T n, real_T a, const real_T x[100], int32_T ix0,
                     const real_T y[5000], int32_T iy0, real_T b_y[5000]);
static real_T xdotc_n(int32_T n, const real_T x[2500], int32_T ix0, const real_T
                      y[2500], int32_T iy0);
static void xaxpy_n5i(int32_T n, real_T a, int32_T ix0, const real_T y[2500],
                      int32_T iy0, real_T b_y[2500]);
static void xswap(const real_T x[2500], int32_T ix0, int32_T iy0, real_T b_x
                  [2500]);
static void xswap_n(const real_T x[5000], int32_T ix0, int32_T iy0, real_T b_x
                    [5000]);
static void xrotg(real_T a, real_T b, real_T *b_a, real_T *b_b, real_T *c,
                  real_T *s);
static void xrot(const real_T x[2500], int32_T ix0, int32_T iy0, real_T c,
                 real_T s, real_T b_x[2500]);
static void xrot_n(const real_T x[5000], int32_T ix0, int32_T iy0, real_T c,
                   real_T s, real_T b_x[5000]);
static void svd_n(const real_T A[5000], real_T U[5000], real_T s[50], real_T V
                  [2500]);
static void svd(const real_T A[5000], real_T U[5000], real_T S[2500], real_T V
                [2500]);
static void diag(const real_T v[2500], real_T d[50]);
static void SVD_stepImpl(const real_T A[5000], real_T varargout_1[5000], real_T
  varargout_2[50], real_T varargout_3[2500]);
static real_T rtGetNaN(void);
static real32_T rtGetNaNF(void);
extern real_T rtInf;
extern real_T rtMinusInf;
extern real_T rtNaN;
extern real32_T rtInfF;
extern real32_T rtMinusInfF;
extern real32_T rtNaNF;
static void rt_InitInfAndNaN(size_t realSize);
static boolean_T rtIsInf(real_T value);
static boolean_T rtIsInfF(real32_T value);
static boolean_T rtIsNaN(real_T value);
static boolean_T rtIsNaNF(real32_T value);
typedef struct {
  struct {
    uint32_T wordH;
    uint32_T wordL;
  } words;
} BigEndianIEEEDouble;

typedef struct {
  struct {
    uint32_T wordL;
    uint32_T wordH;
  } words;
} LittleEndianIEEEDouble;

typedef struct {
  union {
    real32_T wordLreal;
    uint32_T wordLuint;
  } wordL;
} IEEESingle;

real_T rtInf;
real_T rtMinusInf;
real_T rtNaN;
real32_T rtInfF;
real32_T rtMinusInfF;
real32_T rtNaNF;
static real_T rtGetInf(void);
static real32_T rtGetInfF(void);
static real_T rtGetMinusInf(void);
static real32_T rtGetMinusInfF(void);

/*
 * Initialize rtNaN needed by the generated code.
 * NaN is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetNaN(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T nan = 0.0;
  if (bitsPerReal == 32U) {
    nan = rtGetNaNF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0xFFF80000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    nan = tmpVal.fltVal;
  }

  return nan;
}

/*
 * Initialize rtNaNF needed by the generated code.
 * NaN is initialized as non-signaling. Assumes IEEE.
 */
static real32_T rtGetNaNF(void)
{
  IEEESingle nanF = { { 0 } };

  nanF.wordL.wordLuint = 0xFFC00000U;
  return nanF.wordL.wordLreal;
}

/*
 * Initialize the rtInf, rtMinusInf, and rtNaN needed by the
 * generated code. NaN is initialized as non-signaling. Assumes IEEE.
 */
static void rt_InitInfAndNaN(size_t realSize)
{
  (void) (realSize);
  rtNaN = rtGetNaN();
  rtNaNF = rtGetNaNF();
  rtInf = rtGetInf();
  rtInfF = rtGetInfF();
  rtMinusInf = rtGetMinusInf();
  rtMinusInfF = rtGetMinusInfF();
}

/* Test if value is infinite */
static boolean_T rtIsInf(real_T value)
{
  return (boolean_T)((value==rtInf || value==rtMinusInf) ? 1U : 0U);
}

/* Test if single-precision value is infinite */
static boolean_T rtIsInfF(real32_T value)
{
  return (boolean_T)(((value)==rtInfF || (value)==rtMinusInfF) ? 1U : 0U);
}

/* Test if value is not a number */
static boolean_T rtIsNaN(real_T value)
{
  boolean_T result = (boolean_T) 0;
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  if (bitsPerReal == 32U) {
    result = rtIsNaNF((real32_T)value);
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.fltVal = value;
    result = (boolean_T)((tmpVal.bitVal.words.wordH & 0x7FF00000) == 0x7FF00000 &&
                         ( (tmpVal.bitVal.words.wordH & 0x000FFFFF) != 0 ||
                          (tmpVal.bitVal.words.wordL != 0) ));
  }

  return result;
}

/* Test if single-precision value is not a number */
static boolean_T rtIsNaNF(real32_T value)
{
  IEEESingle tmp;
  tmp.wordL.wordLreal = value;
  return (boolean_T)( (tmp.wordL.wordLuint & 0x7F800000) == 0x7F800000 &&
                     (tmp.wordL.wordLuint & 0x007FFFFF) != 0 );
}

/*
 * Initialize rtInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetInf(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T inf = 0.0;
  if (bitsPerReal == 32U) {
    inf = rtGetInfF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0x7FF00000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    inf = tmpVal.fltVal;
  }

  return inf;
}

/*
 * Initialize rtInfF needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real32_T rtGetInfF(void)
{
  IEEESingle infF;
  infF.wordL.wordLuint = 0x7F800000U;
  return infF.wordL.wordLreal;
}

/*
 * Initialize rtMinusInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetMinusInf(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T minf = 0.0;
  if (bitsPerReal == 32U) {
    minf = rtGetMinusInfF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0xFFF00000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    minf = tmpVal.fltVal;
  }

  return minf;
}

/*
 * Initialize rtMinusInfF needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real32_T rtGetMinusInfF(void)
{
  IEEESingle minfF;
  minfF.wordL.wordLuint = 0xFF800000U;
  return minfF.wordL.wordLreal;
}

static void isfinite(const real_T x[5000], boolean_T b[5000])
{
  int32_T i;
  for (i = 0; i < 5000; i++) {
    b[i] = ((!rtIsInf(x[i])) && (!rtIsNaN(x[i])));
  }
}

static boolean_T all(const boolean_T x[5000])
{
  boolean_T y;
  int32_T b_k;
  boolean_T exitg1;
  y = true;
  b_k = 0;
  exitg1 = false;
  while ((!exitg1) && (b_k < 5000)) {
    if (!x[b_k]) {
      y = false;
      exitg1 = true;
    } else {
      b_k++;
    }
  }

  return y;
}

static boolean_T anyNonFinite(const real_T x[5000])
{
  boolean_T p;
  int32_T b_k;
  p = true;
  for (b_k = 0; b_k < 5000; b_k++) {
    if (p && ((!rtIsInf(x[b_k])) && (!rtIsNaN(x[b_k])))) {
    } else {
      p = false;
    }
  }

  return !p;
}

static real_T xnrm2(int32_T n, const real_T x[5000], int32_T ix0)
{
  real_T y;
  real_T scale;
  int32_T kend;
  real_T absxk;
  real_T t;
  int32_T k;
  y = 0.0;
  scale = 3.3121686421112381E-170;
  kend = ix0 + n;
  for (k = ix0; k < kend; k++) {
    absxk = fabs(x[k - 1]);
    if (absxk > scale) {
      t = scale / absxk;
      y = y * t * t + 1.0;
      scale = absxk;
    } else {
      t = absxk / scale;
      y += t * t;
    }
  }

  return scale * sqrt(y);
}

static real_T xdotc(int32_T n, const real_T x[5000], int32_T ix0, const real_T
                    y[5000], int32_T iy0)
{
  real_T d;
  int32_T ix;
  int32_T iy;
  int32_T k;
  d = 0.0;
  ix = ix0 - 1;
  iy = iy0 - 1;
  for (k = 0; k < n; k++) {
    d += x[ix] * y[iy];
    ix++;
    iy++;
  }

  return d;
}

static void xaxpy(int32_T n, real_T a, int32_T ix0, const real_T y[5000],
                  int32_T iy0, real_T b_y[5000])
{
  int32_T ix;
  int32_T iy;
  int32_T k;
  memcpy(&b_y[0], &y[0], 5000U * sizeof(real_T));
  if (!(a == 0.0)) {
    ix = ix0;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      b_y[iy] += b_y[ix - 1] * a;
      ix++;
      iy++;
    }
  }
}

static real_T xnrm2_n(int32_T n, const real_T x[50], int32_T ix0)
{
  real_T y;
  real_T scale;
  int32_T kend;
  real_T absxk;
  real_T t;
  int32_T k;
  y = 0.0;
  scale = 3.3121686421112381E-170;
  kend = ix0 + n;
  for (k = ix0; k < kend; k++) {
    absxk = fabs(x[k - 1]);
    if (absxk > scale) {
      t = scale / absxk;
      y = y * t * t + 1.0;
      scale = absxk;
    } else {
      t = absxk / scale;
      y += t * t;
    }
  }

  return scale * sqrt(y);
}

static void xaxpy_n5iz(int32_T n, real_T a, const real_T x[5000], int32_T ix0,
  real_T y[100], int32_T iy0)
{
  int32_T ix;
  int32_T iy;
  int32_T k;
  if (!(a == 0.0)) {
    ix = ix0;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      y[iy] += x[ix - 1] * a;
      ix++;
      iy++;
    }
  }
}

static void xaxpy_n5(int32_T n, real_T a, const real_T x[100], int32_T ix0,
                     const real_T y[5000], int32_T iy0, real_T b_y[5000])
{
  int32_T ix;
  int32_T iy;
  int32_T k;
  memcpy(&b_y[0], &y[0], 5000U * sizeof(real_T));
  if (!(a == 0.0)) {
    ix = ix0;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      b_y[iy] += x[ix - 1] * a;
      ix++;
      iy++;
    }
  }
}

static real_T xdotc_n(int32_T n, const real_T x[2500], int32_T ix0, const real_T
                      y[2500], int32_T iy0)
{
  real_T d;
  int32_T ix;
  int32_T iy;
  int32_T k;
  d = 0.0;
  ix = ix0 - 1;
  iy = iy0 - 1;
  for (k = 0; k < n; k++) {
    d += x[ix] * y[iy];
    ix++;
    iy++;
  }

  return d;
}

static void xaxpy_n5i(int32_T n, real_T a, int32_T ix0, const real_T y[2500],
                      int32_T iy0, real_T b_y[2500])
{
  int32_T ix;
  int32_T iy;
  int32_T k;
  memcpy(&b_y[0], &y[0], 2500U * sizeof(real_T));
  if (!(a == 0.0)) {
    ix = ix0;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      b_y[iy] += b_y[ix - 1] * a;
      ix++;
      iy++;
    }
  }
}

static void xswap(const real_T x[2500], int32_T ix0, int32_T iy0, real_T b_x
                  [2500])
{
  int32_T ix;
  int32_T iy;
  real_T temp;
  int32_T k;
  memcpy(&b_x[0], &x[0], 2500U * sizeof(real_T));
  ix = ix0 - 1;
  iy = iy0 - 1;
  for (k = 0; k < 50; k++) {
    temp = b_x[ix];
    b_x[ix] = b_x[iy];
    b_x[iy] = temp;
    ix++;
    iy++;
  }
}

static void xswap_n(const real_T x[5000], int32_T ix0, int32_T iy0, real_T b_x
                    [5000])
{
  int32_T ix;
  int32_T iy;
  real_T temp;
  int32_T k;
  memcpy(&b_x[0], &x[0], 5000U * sizeof(real_T));
  ix = ix0 - 1;
  iy = iy0 - 1;
  for (k = 0; k < 100; k++) {
    temp = b_x[ix];
    b_x[ix] = b_x[iy];
    b_x[iy] = temp;
    ix++;
    iy++;
  }
}

static void xrotg(real_T a, real_T b, real_T *b_a, real_T *b_b, real_T *c,
                  real_T *s)
{
  real_T roe;
  real_T absa;
  real_T absb;
  real_T scale;
  real_T ads;
  real_T bds;
  roe = b;
  absa = fabs(a);
  absb = fabs(b);
  if (absa > absb) {
    roe = a;
  }

  scale = absa + absb;
  if (scale == 0.0) {
    *s = 0.0;
    *c = 1.0;
    *b_a = 0.0;
    *b_b = 0.0;
  } else {
    ads = absa / scale;
    bds = absb / scale;
    *b_a = sqrt(ads * ads + bds * bds) * scale;
    if (roe < 0.0) {
      *b_a = -*b_a;
    }

    *c = a / *b_a;
    *s = b / *b_a;
    if (absa > absb) {
      *b_b = *s;
    } else if (*c != 0.0) {
      *b_b = 1.0 / *c;
    } else {
      *b_b = 1.0;
    }
  }
}

static void xrot(const real_T x[2500], int32_T ix0, int32_T iy0, real_T c,
                 real_T s, real_T b_x[2500])
{
  int32_T ix;
  int32_T iy;
  real_T temp;
  int32_T k;
  memcpy(&b_x[0], &x[0], 2500U * sizeof(real_T));
  ix = ix0 - 1;
  iy = iy0 - 1;
  for (k = 0; k < 50; k++) {
    temp = c * b_x[ix] + s * b_x[iy];
    b_x[iy] = c * b_x[iy] - s * b_x[ix];
    b_x[ix] = temp;
    iy++;
    ix++;
  }
}

static void xrot_n(const real_T x[5000], int32_T ix0, int32_T iy0, real_T c,
                   real_T s, real_T b_x[5000])
{
  int32_T ix;
  int32_T iy;
  real_T temp;
  int32_T k;
  memcpy(&b_x[0], &x[0], 5000U * sizeof(real_T));
  ix = ix0 - 1;
  iy = iy0 - 1;
  for (k = 0; k < 100; k++) {
    temp = c * b_x[ix] + s * b_x[iy];
    b_x[iy] = c * b_x[iy] - s * b_x[ix];
    b_x[ix] = temp;
    iy++;
    ix++;
  }
}

static void svd_n(const real_T A[5000], real_T U[5000], real_T s[50], real_T V
                  [2500])
{
  real_T s_0[50];
  real_T e[50];
  real_T work[100];
  int32_T qp1;
  int32_T qq;
  boolean_T apply_transform;
  real_T nrm;
  int32_T qjj;
  int32_T qp1jj;
  int32_T m;
  real_T rt;
  int32_T colqp1;
  real_T ztest0;
  real_T ztest;
  real_T smm1;
  real_T emm1;
  real_T sqds;
  real_T shift;
  real_T ztest0_tmp;
  boolean_T exitg1;
  memcpy(&rtDW.A[0], &A[0], 5000U * sizeof(real_T));
  memset(&s_0[0], 0, 50U * sizeof(real_T));
  memset(&e[0], 0, 50U * sizeof(real_T));
  memset(&work[0], 0, 100U * sizeof(real_T));
  memset(&U[0], 0, 5000U * sizeof(real_T));
  memset(&rtDW.Vf[0], 0, 2500U * sizeof(real_T));
  for (m = 0; m < 50; m++) {
    qp1 = m + 2;
    qq = (100 * m + m) + 1;
    apply_transform = false;
    nrm = xnrm2(100 - m, rtDW.A, qq);
    if (nrm > 0.0) {
      apply_transform = true;
      if (rtDW.A[qq - 1] < 0.0) {
        s_0[m] = -nrm;
      } else {
        s_0[m] = nrm;
      }

      if (fabs(s_0[m]) >= 1.0020841800044864E-292) {
        nrm = 1.0 / s_0[m];
        qp1jj = qq - m;
        for (qjj = qq; qjj <= qp1jj + 99; qjj++) {
          rtDW.A[qjj - 1] *= nrm;
        }
      } else {
        qp1jj = qq - m;
        for (qjj = qq; qjj <= qp1jj + 99; qjj++) {
          rtDW.A[qjj - 1] /= s_0[m];
        }
      }

      rtDW.A[qq - 1]++;
      s_0[m] = -s_0[m];
    } else {
      s_0[m] = 0.0;
    }

    for (qp1jj = qp1; qp1jj < 51; qp1jj++) {
      qjj = ((qp1jj - 1) * 100 + m) + 1;
      if (apply_transform) {
        memcpy(&rtDW.A_m[0], &rtDW.A[0], 5000U * sizeof(real_T));
        xaxpy(100 - m, -(xdotc(100 - m, rtDW.A, qq, rtDW.A, qjj) / rtDW.A[100 *
                         m + m]), qq, rtDW.A_m, qjj, rtDW.A);
      }

      e[qp1jj - 1] = rtDW.A[qjj - 1];
    }

    for (qq = m + 1; qq < 101; qq++) {
      qp1jj = (100 * m + qq) - 1;
      U[qp1jj] = rtDW.A[qp1jj];
    }

    if (m + 1 <= 48) {
      nrm = xnrm2_n(49 - m, e, m + 2);
      if (nrm == 0.0) {
        e[m] = 0.0;
      } else {
        if (e[m + 1] < 0.0) {
          e[m] = -nrm;
        } else {
          e[m] = nrm;
        }

        nrm = e[m];
        if (fabs(e[m]) >= 1.0020841800044864E-292) {
          nrm = 1.0 / e[m];
          for (qjj = qp1; qjj < 51; qjj++) {
            e[qjj - 1] *= nrm;
          }
        } else {
          for (qjj = qp1; qjj < 51; qjj++) {
            e[qjj - 1] /= nrm;
          }
        }

        e[m + 1]++;
        e[m] = -e[m];
        for (qq = qp1; qq < 101; qq++) {
          work[qq - 1] = 0.0;
        }

        for (qq = qp1; qq < 51; qq++) {
          xaxpy_n5iz(99 - m, e[qq - 1], rtDW.A, (m + 100 * (qq - 1)) + 2, work,
                     m + 2);
        }

        for (qq = qp1; qq < 51; qq++) {
          memcpy(&rtDW.A_m[0], &rtDW.A[0], 5000U * sizeof(real_T));
          xaxpy_n5(99 - m, -e[qq - 1] / e[m + 1], work, m + 2, rtDW.A_m, ((qq -
                     1) * 100 + m) + 2, rtDW.A);
        }
      }

      for (qq = qp1; qq < 51; qq++) {
        rtDW.Vf[(qq + 50 * m) - 1] = e[qq - 1];
      }
    }
  }

  m = 49;
  e[48] = rtDW.A[4948];
  e[49] = 0.0;
  for (colqp1 = 49; colqp1 >= 0; colqp1--) {
    qq = 100 * colqp1 + colqp1;
    if (s_0[colqp1] != 0.0) {
      for (qp1jj = colqp1 + 2; qp1jj < 51; qp1jj++) {
        qjj = ((qp1jj - 1) * 100 + colqp1) + 1;
        memcpy(&rtDW.A[0], &U[0], 5000U * sizeof(real_T));
        xaxpy(100 - colqp1, -(xdotc(100 - colqp1, U, qq + 1, U, qjj) / U[qq]),
              qq + 1, rtDW.A, qjj, U);
      }

      for (qp1 = colqp1 + 1; qp1 < 101; qp1++) {
        qp1jj = (100 * colqp1 + qp1) - 1;
        U[qp1jj] = -U[qp1jj];
      }

      U[qq]++;
      qp1 = colqp1 - 1;
      if (0 <= qp1) {
        memset(&U[colqp1 * 100], 0, (qp1 + 1) * sizeof(real_T));
      }
    } else {
      memset(&U[colqp1 * 100], 0, 100U * sizeof(real_T));
      U[qq] = 1.0;
    }
  }

  for (colqp1 = 49; colqp1 >= 0; colqp1--) {
    if ((colqp1 + 1 <= 48) && (e[colqp1] != 0.0)) {
      qq = (50 * colqp1 + colqp1) + 2;
      for (qjj = colqp1 + 2; qjj < 51; qjj++) {
        qp1jj = ((qjj - 1) * 50 + colqp1) + 2;
        memcpy(&rtDW.Vf_c[0], &rtDW.Vf[0], 2500U * sizeof(real_T));
        xaxpy_n5i(49 - colqp1, -(xdotc_n(49 - colqp1, rtDW.Vf, qq, rtDW.Vf,
                    qp1jj) / rtDW.Vf[qq - 1]), qq, rtDW.Vf_c, qp1jj, rtDW.Vf);
      }
    }

    memset(&rtDW.Vf[colqp1 * 50], 0, 50U * sizeof(real_T));
    rtDW.Vf[colqp1 + 50 * colqp1] = 1.0;
  }

  for (qp1 = 0; qp1 < 50; qp1++) {
    ztest = e[qp1];
    if (s_0[qp1] != 0.0) {
      rt = fabs(s_0[qp1]);
      nrm = s_0[qp1] / rt;
      s_0[qp1] = rt;
      if (qp1 + 1 < 50) {
        ztest = e[qp1] / nrm;
      }

      qq = 100 * qp1;
      for (qjj = qq + 1; qjj <= qq + 100; qjj++) {
        U[qjj - 1] *= nrm;
      }
    }

    if ((qp1 + 1 < 50) && (ztest != 0.0)) {
      rt = fabs(ztest);
      nrm = rt / ztest;
      ztest = rt;
      s_0[qp1 + 1] *= nrm;
      colqp1 = (qp1 + 1) * 50;
      for (qjj = colqp1 + 1; qjj <= colqp1 + 50; qjj++) {
        rtDW.Vf[qjj - 1] *= nrm;
      }
    }

    e[qp1] = ztest;
  }

  rt = 0.0;
  nrm = 0.0;
  for (colqp1 = 0; colqp1 < 50; colqp1++) {
    nrm = fmax(nrm, fmax(fabs(s_0[colqp1]), fabs(e[colqp1])));
  }

  while ((m + 1 > 0) && (!(rt >= 75.0))) {
    colqp1 = m;
    qp1 = m;
    exitg1 = false;
    while ((!exitg1) && (qp1 > -1)) {
      colqp1 = qp1;
      if (qp1 == 0) {
        exitg1 = true;
      } else {
        ztest0 = fabs(e[qp1 - 1]);
        if ((ztest0 <= (fabs(s_0[qp1 - 1]) + fabs(s_0[qp1])) *
             2.2204460492503131E-16) || (ztest0 <= 1.0020841800044864E-292) ||
            ((rt > 20.0) && (ztest0 <= 2.2204460492503131E-16 * nrm))) {
          e[qp1 - 1] = 0.0;
          exitg1 = true;
        } else {
          qp1--;
        }
      }
    }

    if (colqp1 == m) {
      ztest0 = 4.0;
    } else {
      qp1 = m + 1;
      qq = m + 1;
      exitg1 = false;
      while ((!exitg1) && (qq >= colqp1)) {
        qp1 = qq;
        if (qq == colqp1) {
          exitg1 = true;
        } else {
          ztest0 = 0.0;
          if (qq < m + 1) {
            ztest0 = fabs(e[qq - 1]);
          }

          if (qq > colqp1 + 1) {
            ztest0 += fabs(e[qq - 2]);
          }

          ztest = fabs(s_0[qq - 1]);
          if ((ztest <= 2.2204460492503131E-16 * ztest0) || (ztest <=
               1.0020841800044864E-292)) {
            s_0[qq - 1] = 0.0;
            exitg1 = true;
          } else {
            qq--;
          }
        }
      }

      if (qp1 == colqp1) {
        ztest0 = 3.0;
      } else if (m + 1 == qp1) {
        ztest0 = 1.0;
      } else {
        ztest0 = 2.0;
        colqp1 = qp1;
      }
    }

    switch ((int32_T)ztest0) {
     case 1:
      ztest0 = e[m - 1];
      e[m - 1] = 0.0;
      for (qq = m; qq >= colqp1 + 1; qq--) {
        xrotg(s_0[qq - 1], ztest0, &s_0[qq - 1], &ztest0, &ztest, &sqds);
        if (qq > colqp1 + 1) {
          ztest0_tmp = e[qq - 2];
          ztest0 = ztest0_tmp * -sqds;
          e[qq - 2] = ztest0_tmp * ztest;
        }

        memcpy(&rtDW.Vf_c[0], &rtDW.Vf[0], 2500U * sizeof(real_T));
        xrot(rtDW.Vf_c, (qq - 1) * 50 + 1, 50 * m + 1, ztest, sqds, rtDW.Vf);
      }
      break;

     case 2:
      ztest0 = e[colqp1 - 1];
      e[colqp1 - 1] = 0.0;
      for (qp1 = colqp1 + 1; qp1 <= m + 1; qp1++) {
        xrotg(s_0[qp1 - 1], ztest0, &s_0[qp1 - 1], &ztest, &sqds, &smm1);
        ztest0_tmp = e[qp1 - 1];
        ztest0 = ztest0_tmp * -smm1;
        e[qp1 - 1] = ztest0_tmp * sqds;
        memcpy(&rtDW.A[0], &U[0], 5000U * sizeof(real_T));
        xrot_n(rtDW.A, (qp1 - 1) * 100 + 1, (colqp1 - 1) * 100 + 1, sqds, smm1,
               U);
      }
      break;

     case 3:
      smm1 = s_0[m - 1];
      sqds = e[m - 1];
      ztest = fmax(fmax(fmax(fmax(fabs(s_0[m]), fabs(smm1)), fabs(sqds)), fabs
                        (s_0[colqp1])), fabs(e[colqp1]));
      ztest0 = s_0[m] / ztest;
      smm1 /= ztest;
      emm1 = sqds / ztest;
      sqds = s_0[colqp1] / ztest;
      smm1 = ((smm1 + ztest0) * (smm1 - ztest0) + emm1 * emm1) / 2.0;
      emm1 *= ztest0;
      emm1 *= emm1;
      if ((smm1 != 0.0) || (emm1 != 0.0)) {
        shift = sqrt(smm1 * smm1 + emm1);
        if (smm1 < 0.0) {
          shift = -shift;
        }

        shift = emm1 / (smm1 + shift);
      } else {
        shift = 0.0;
      }

      ztest0 = (sqds + ztest0) * (sqds - ztest0) + shift;
      ztest = e[colqp1] / ztest * sqds;
      for (qq = colqp1 + 1; qq <= m; qq++) {
        xrotg(ztest0, ztest, &sqds, &smm1, &emm1, &shift);
        if (qq > colqp1 + 1) {
          e[qq - 2] = sqds;
        }

        ztest0_tmp = e[qq - 1];
        ztest0 = s_0[qq - 1];
        e[qq - 1] = ztest0_tmp * emm1 - ztest0 * shift;
        ztest = shift * s_0[qq];
        s_0[qq] *= emm1;
        memcpy(&rtDW.Vf_c[0], &rtDW.Vf[0], 2500U * sizeof(real_T));
        xrot(rtDW.Vf_c, (qq - 1) * 50 + 1, 50 * qq + 1, emm1, shift, rtDW.Vf);
        xrotg(ztest0 * emm1 + ztest0_tmp * shift, ztest, &s_0[qq - 1], &sqds,
              &smm1, &emm1);
        ztest0 = e[qq - 1] * smm1 + emm1 * s_0[qq];
        s_0[qq] = e[qq - 1] * -emm1 + smm1 * s_0[qq];
        ztest = emm1 * e[qq];
        e[qq] *= smm1;
        memcpy(&rtDW.A[0], &U[0], 5000U * sizeof(real_T));
        xrot_n(rtDW.A, (qq - 1) * 100 + 1, 100 * qq + 1, smm1, emm1, U);
      }

      e[m - 1] = ztest0;
      rt++;
      break;

     default:
      if (s_0[colqp1] < 0.0) {
        s_0[colqp1] = -s_0[colqp1];
        qq = 50 * colqp1;
        for (qjj = qq + 1; qjj <= qq + 50; qjj++) {
          rtDW.Vf[qjj - 1] = -rtDW.Vf[qjj - 1];
        }
      }

      qp1 = colqp1 + 1;
      while ((colqp1 + 1 < 50) && (s_0[colqp1] < s_0[qp1])) {
        rt = s_0[colqp1];
        s_0[colqp1] = s_0[qp1];
        s_0[qp1] = rt;
        memcpy(&rtDW.Vf_c[0], &rtDW.Vf[0], 2500U * sizeof(real_T));
        xswap(rtDW.Vf_c, 50 * colqp1 + 1, (colqp1 + 1) * 50 + 1, rtDW.Vf);
        memcpy(&rtDW.A[0], &U[0], 5000U * sizeof(real_T));
        xswap_n(rtDW.A, 100 * colqp1 + 1, (colqp1 + 1) * 100 + 1, U);
        colqp1 = qp1;
        qp1++;
      }

      rt = 0.0;
      m--;
      break;
    }
  }

  for (m = 0; m < 50; m++) {
    s[m] = s_0[m];
    memcpy(&V[m * 50], &rtDW.Vf[m * 50], 50U * sizeof(real_T));
  }
}

static void svd(const real_T A[5000], real_T U[5000], real_T S[2500], real_T V
                [2500])
{
  real_T s[50];
  int32_T i;
  if (!anyNonFinite(A)) {
    svd_n(A, U, s, V);
  } else {
    for (i = 0; i < 5000; i++) {
      U[i] = (rtNaN);
    }

    for (i = 0; i < 50; i++) {
      s[i] = (rtNaN);
    }

    for (i = 0; i < 2500; i++) {
      V[i] = (rtNaN);
    }
  }

  memset(&S[0], 0, 2500U * sizeof(real_T));
  for (i = 0; i < 50; i++) {
    S[i + 50 * i] = s[i];
  }
}

static void diag(const real_T v[2500], real_T d[50])
{
  int32_T k;
  for (k = 0; k < 50; k++) {
    d[k] = v[50 * k + k];
  }
}

static void SVD_stepImpl(const real_T A[5000], real_T varargout_1[5000], real_T
  varargout_2[50], real_T varargout_3[2500])
{
  isfinite(A, rtDW.bv);
  if (all(rtDW.bv)) {
    svd(A, varargout_1, rtDW.s, varargout_3);
    diag(rtDW.s, varargout_2);
  } else {
    memset(&varargout_1[0], 0, 5000U * sizeof(real_T));
    memset(&varargout_2[0], 0, 50U * sizeof(real_T));
    memset(&varargout_3[0], 0, 2500U * sizeof(real_T));
  }
}

/* Model step function */
void PerformanceTester_SVD_step(void)
{
  /* Outport: '<Root>/Outport1' incorporates:
   *  Inport: '<Root>/Inport'
   *  MATLABSystem: '<Root>/Singular Value Decomposition'
   */
  SVD_stepImpl(rtU.Inport, rtY.Outport, rtY.Outport1, rtY.Outport2);
}

/* Model initialize function */
void PerformanceTester_SVD_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* Start for MATLABSystem: '<Root>/Singular Value Decomposition' */
  rtDW.obj.isInitialized = 1;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
