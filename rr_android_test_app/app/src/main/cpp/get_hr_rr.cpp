//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: get_hr_rr.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 04-Oct-2018 12:02:32
//

// Include Files
#include "rt_nonfinite.h"
#include "get_hr_rr.h"
#include "get_hr_rr_emxutil.h"

// Function Declarations
static void b_filter(const double b[2], const double x[506], double zi, double
                     y[506]);
static void b_flipud(double x[506]);
static void do_vectors(const emxArray_int32_T *a, const emxArray_int32_T *b,
  emxArray_int32_T *c, emxArray_int32_T *ia, emxArray_int32_T *ib);
static void filter(double b[4], double a[4], const double x[518], const double
                   zi[3], double y[518]);
static void flipud(double x[518]);
static void getAllPeaksCodegen(const double y[492], emxArray_int32_T *iPk,
  emxArray_int32_T *iInf, emxArray_int32_T *iInflect);

// Function Definitions

//
// Arguments    : const double b[2]
//                const double x[506]
//                double zi
//                double y[506]
// Return Type  : void
//
static void b_filter(const double b[2], const double x[506], double zi, double
                     y[506])
{
  int k;
  int j;
  y[0] = zi;
  memset(&y[1], 0, 505U * sizeof(double));
  for (k = 0; k < 2; k++) {
    for (j = k; j + 1 < 507; j++) {
      y[j] += b[k] * x[j - k];
    }
  }
}

//
// Arguments    : double x[506]
// Return Type  : void
//
static void b_flipud(double x[506])
{
  int i;
  double xtmp;
  for (i = 0; i < 253; i++) {
    xtmp = x[i];
    x[i] = x[505 - i];
    x[505 - i] = xtmp;
  }
}

//
// Arguments    : const emxArray_int32_T *a
//                const emxArray_int32_T *b
//                emxArray_int32_T *c
//                emxArray_int32_T *ia
//                emxArray_int32_T *ib
// Return Type  : void
//
static void do_vectors(const emxArray_int32_T *a, const emxArray_int32_T *b,
  emxArray_int32_T *c, emxArray_int32_T *ia, emxArray_int32_T *ib)
{
  int na;
  int nb;
  int ncmax;
  int iafirst;
  int nc;
  int nia;
  int nib;
  int ialast;
  int ibfirst;
  int iblast;
  int b_ialast;
  int ak;
  int b_iblast;
  int bk;
  emxArray_int32_T *b_ia;
  emxArray_int32_T *b_ib;
  emxArray_int32_T *b_c;
  na = a->size[0];
  nb = b->size[0];
  ncmax = a->size[0] + b->size[0];
  iafirst = c->size[0];
  c->size[0] = ncmax;
  emxEnsureCapacity((emxArray__common *)c, iafirst, sizeof(int));
  iafirst = ia->size[0];
  ia->size[0] = a->size[0];
  emxEnsureCapacity((emxArray__common *)ia, iafirst, sizeof(int));
  iafirst = ib->size[0];
  ib->size[0] = b->size[0];
  emxEnsureCapacity((emxArray__common *)ib, iafirst, sizeof(int));
  nc = -1;
  nia = -1;
  nib = 0;
  iafirst = 1;
  ialast = 1;
  ibfirst = 0;
  iblast = 1;
  while ((ialast <= na) && (iblast <= nb)) {
    b_ialast = ialast;
    ak = a->data[ialast - 1];
    while ((b_ialast < a->size[0]) && (a->data[b_ialast] == ak)) {
      b_ialast++;
    }

    ialast = b_ialast;
    b_iblast = iblast;
    bk = b->data[iblast - 1];
    while ((b_iblast < b->size[0]) && (b->data[b_iblast] == bk)) {
      b_iblast++;
    }

    iblast = b_iblast;
    if (ak == bk) {
      nc++;
      c->data[nc] = ak;
      nia++;
      ia->data[nia] = iafirst;
      ialast = b_ialast + 1;
      iafirst = b_ialast + 1;
      iblast = b_iblast + 1;
      ibfirst = b_iblast;
    } else if (ak < bk) {
      nc++;
      nia++;
      c->data[nc] = ak;
      ia->data[nia] = iafirst;
      ialast = b_ialast + 1;
      iafirst = b_ialast + 1;
    } else {
      nc++;
      nib++;
      c->data[nc] = bk;
      ib->data[nib - 1] = ibfirst + 1;
      iblast = b_iblast + 1;
      ibfirst = b_iblast;
    }
  }

  while (ialast <= na) {
    b_ialast = ialast;
    while ((b_ialast < a->size[0]) && (a->data[b_ialast] == a->data[ialast - 1]))
    {
      b_ialast++;
    }

    nc++;
    nia++;
    c->data[nc] = a->data[ialast - 1];
    ia->data[nia] = ialast;
    ialast = b_ialast + 1;
  }

  while (iblast <= nb) {
    b_iblast = iblast;
    while ((b_iblast < b->size[0]) && (b->data[b_iblast] == b->data[iblast - 1]))
    {
      b_iblast++;
    }

    nc++;
    nib++;
    c->data[nc] = b->data[iblast - 1];
    ib->data[nib - 1] = iblast;
    iblast = b_iblast + 1;
  }

  if (a->size[0] > 0) {
    if (1 > nia + 1) {
      nia = -1;
    }

    emxInit_int32_T(&b_ia, 1);
    iafirst = b_ia->size[0];
    b_ia->size[0] = nia + 1;
    emxEnsureCapacity((emxArray__common *)b_ia, iafirst, sizeof(int));
    for (iafirst = 0; iafirst <= nia; iafirst++) {
      b_ia->data[iafirst] = ia->data[iafirst];
    }

    iafirst = ia->size[0];
    ia->size[0] = b_ia->size[0];
    emxEnsureCapacity((emxArray__common *)ia, iafirst, sizeof(int));
    nia = b_ia->size[0];
    for (iafirst = 0; iafirst < nia; iafirst++) {
      ia->data[iafirst] = b_ia->data[iafirst];
    }

    emxFree_int32_T(&b_ia);
  }

  if (b->size[0] > 0) {
    if (1 > nib) {
      nia = 0;
    } else {
      nia = nib;
    }

    emxInit_int32_T(&b_ib, 1);
    iafirst = b_ib->size[0];
    b_ib->size[0] = nia;
    emxEnsureCapacity((emxArray__common *)b_ib, iafirst, sizeof(int));
    for (iafirst = 0; iafirst < nia; iafirst++) {
      b_ib->data[iafirst] = ib->data[iafirst];
    }

    iafirst = ib->size[0];
    ib->size[0] = b_ib->size[0];
    emxEnsureCapacity((emxArray__common *)ib, iafirst, sizeof(int));
    nia = b_ib->size[0];
    for (iafirst = 0; iafirst < nia; iafirst++) {
      ib->data[iafirst] = b_ib->data[iafirst];
    }

    emxFree_int32_T(&b_ib);
  }

  if (ncmax > 0) {
    if (1 > nc + 1) {
      nia = -1;
    } else {
      nia = nc;
    }

    emxInit_int32_T(&b_c, 1);
    iafirst = b_c->size[0];
    b_c->size[0] = nia + 1;
    emxEnsureCapacity((emxArray__common *)b_c, iafirst, sizeof(int));
    for (iafirst = 0; iafirst <= nia; iafirst++) {
      b_c->data[iafirst] = c->data[iafirst];
    }

    iafirst = c->size[0];
    c->size[0] = b_c->size[0];
    emxEnsureCapacity((emxArray__common *)c, iafirst, sizeof(int));
    nia = b_c->size[0];
    for (iafirst = 0; iafirst < nia; iafirst++) {
      c->data[iafirst] = b_c->data[iafirst];
    }

    emxFree_int32_T(&b_c);
  }
}

//
// Arguments    : double b[4]
//                double a[4]
//                const double x[518]
//                const double zi[3]
//                double y[518]
// Return Type  : void
//
static void filter(double b[4], double a[4], const double x[518], const double
                   zi[3], double y[518])
{
  double a1;
  int k;
  int naxpy;
  int j;
  a1 = a[0];
  if ((!rtIsInf(a[0])) && (!rtIsNaN(a[0])) && (!(a[0] == 0.0)) && (a[0] != 1.0))
  {
    for (k = 0; k < 4; k++) {
      b[k] /= a1;
    }

    for (k = 0; k < 3; k++) {
      a[k + 1] /= a1;
    }

    a[0] = 1.0;
  }

  for (k = 0; k < 3; k++) {
    y[k] = zi[k];
  }

  memset(&y[3], 0, 515U * sizeof(double));
  for (k = 0; k < 518; k++) {
    naxpy = 518 - k;
    if (!(naxpy < 4)) {
      naxpy = 4;
    }

    for (j = 0; j + 1 <= naxpy; j++) {
      y[k + j] += x[k] * b[j];
    }

    naxpy = 517 - k;
    if (!(naxpy < 3)) {
      naxpy = 3;
    }

    a1 = -y[k];
    for (j = 1; j <= naxpy; j++) {
      y[k + j] += a1 * a[j];
    }
  }
}

//
// Arguments    : double x[518]
// Return Type  : void
//
static void flipud(double x[518])
{
  int i;
  double xtmp;
  for (i = 0; i < 259; i++) {
    xtmp = x[i];
    x[i] = x[517 - i];
    x[517 - i] = xtmp;
  }
}

//
// Arguments    : const double y[492]
//                emxArray_int32_T *iPk
//                emxArray_int32_T *iInf
//                emxArray_int32_T *iInflect
// Return Type  : void
//
static void getAllPeaksCodegen(const double y[492], emxArray_int32_T *iPk,
  emxArray_int32_T *iInf, emxArray_int32_T *iInflect)
{
  int kfirst;
  int nPk;
  int nInf;
  int nInflect;
  char dir;
  double ykfirst;
  boolean_T isinfykfirst;
  int k;
  double yk;
  boolean_T isinfyk;
  char previousdir;
  int i0;
  kfirst = iPk->size[0];
  iPk->size[0] = 492;
  emxEnsureCapacity((emxArray__common *)iPk, kfirst, sizeof(int));
  kfirst = iInf->size[0];
  iInf->size[0] = 492;
  emxEnsureCapacity((emxArray__common *)iInf, kfirst, sizeof(int));
  kfirst = iInflect->size[0];
  iInflect->size[0] = 492;
  emxEnsureCapacity((emxArray__common *)iInflect, kfirst, sizeof(int));
  nPk = 0;
  nInf = 0;
  nInflect = -1;
  dir = 'n';
  kfirst = 0;
  ykfirst = rtInf;
  isinfykfirst = true;
  for (k = 0; k < 492; k++) {
    yk = y[k];
    if (rtIsNaN(y[k])) {
      yk = rtInf;
      isinfyk = true;
    } else if (rtIsInf(y[k]) && (y[k] > 0.0)) {
      isinfyk = true;
      nInf++;
      iInf->data[nInf - 1] = k + 1;
    } else {
      isinfyk = false;
    }

    if (yk != ykfirst) {
      previousdir = dir;
      if (isinfyk || isinfykfirst) {
        dir = 'n';
        if (kfirst >= 1) {
          nInflect++;
          iInflect->data[nInflect] = kfirst;
        }
      } else if (yk < ykfirst) {
        dir = 'd';
        if ('d' != previousdir) {
          nInflect++;
          iInflect->data[nInflect] = kfirst;
          if (previousdir == 'i') {
            nPk++;
            iPk->data[nPk - 1] = kfirst;
          }
        }
      } else {
        dir = 'i';
        if ('i' != previousdir) {
          nInflect++;
          iInflect->data[nInflect] = kfirst;
        }
      }

      ykfirst = yk;
      kfirst = k + 1;
      isinfykfirst = isinfyk;
    }
  }

  if ((!isinfykfirst) && ((nInflect + 1 == 0) || (iInflect->data[nInflect] < 492)))
  {
    nInflect++;
    iInflect->data[nInflect] = 492;
  }

  kfirst = iPk->size[0];
  if (1 > nPk) {
    iPk->size[0] = 0;
  } else {
    iPk->size[0] = nPk;
  }

  emxEnsureCapacity((emxArray__common *)iPk, kfirst, sizeof(int));
  kfirst = iInf->size[0];
  if (1 > nInf) {
    iInf->size[0] = 0;
  } else {
    iInf->size[0] = nInf;
  }

  emxEnsureCapacity((emxArray__common *)iInf, kfirst, sizeof(int));
  kfirst = iInflect->size[0];
  if (1 > nInflect + 1) {
    i0 = -1;
  } else {
    i0 = nInflect;
  }

  iInflect->size[0] = i0 + 1;
  emxEnsureCapacity((emxArray__common *)iInflect, kfirst, sizeof(int));
}

//
// get_hr_rr This function uses a variant of the Pan-Tompkins Algorithm to
// detect ECG QRS features from low frequency data:
//  Input: X (raw data, floats or doubles (preferred);
//  Outputs: Y .. (TODO);
// Arguments    : double X[500]
//                emxArray_real_T *Output
//                double *HR_mean
//                double *Respiratory_rate
// Return Type  : void
//
void get_hr_rr(double X[500], emxArray_real_T *Output, double *HR_mean, double
               *Respiratory_rate)
{
  double y;
  int k;
  double base;
  double b_y[518];
  int i;
  double dv0[4];
  static const double dv1[4] = { 0.950971887923409, -2.8529156637702271,
    2.8529156637702271, -0.950971887923409 };

  double dv2[4];
  static const double dv3[4] = { 1.0, -2.8994795946118641, 2.8039479773829989,
    -0.904347531392409 };

  double c_y[518];
  double a[3];
  static const double b_a[3] = { -0.95097188792623888, 1.9019437758521933,
    -0.95097188792596821 };

  double d_y[506];
  double e_y[506];
  double dv4[2];
  double X3[500];
  double X4[492];
  static const double B[9] = { 0.0, 0.146446609406726, 0.5, 0.853553390593274,
    1.0, 0.853553390593274, 0.5, 0.146446609406726, 0.0 };

  int n;
  boolean_T exitg1;
  emxArray_int32_T *iPk;
  emxArray_int32_T *idx;
  emxArray_int32_T *iFinite;
  emxArray_int32_T *iInfinite;
  emxArray_int32_T *c;
  emxArray_int32_T *f_y;
  emxArray_int32_T *b_idx;
  emxArray_real_T *b_X4;
  emxArray_int16_T *dist;

  //  1. Remove Mean:
  y = X[0];
  for (k = 0; k < 499; k++) {
    y += X[k + 1];
  }

  y /= 500.0;
  for (k = 0; k < 500; k++) {
    X[k] -= y;
  }

  //  2. Remove baseline drift (Butterworth, high pass: [b, a] = butter(3, 0.5*2/62.5, 'high');  
  //  @ 5 hz
  //  b = [0.601580928135908,-1.804742784407724,1.804742784407724,-0.601580928135908]; 
  //  a = [1,-2.003797477370017,1.447054019489380,-0.361795928227867];
  //  @ 0.5 Hz:
  y = 2.0 * X[0];
  base = 2.0 * X[499];
  for (k = 0; k < 9; k++) {
    b_y[k] = y - X[9 - k];
  }

  memcpy(&b_y[9], &X[0], 500U * sizeof(double));
  for (k = 0; k < 9; k++) {
    b_y[k + 509] = base - X[498 - k];
  }

  for (k = 0; k < 4; k++) {
    dv0[k] = dv1[k];
    dv2[k] = dv3[k];
  }

  for (i = 0; i < 3; i++) {
    a[i] = b_a[i] * b_y[0];
  }

  memcpy(&c_y[0], &b_y[0], 518U * sizeof(double));
  filter(dv0, dv2, c_y, a, b_y);
  flipud(b_y);
  for (k = 0; k < 4; k++) {
    dv0[k] = dv1[k];
    dv2[k] = dv3[k];
  }

  for (i = 0; i < 3; i++) {
    a[i] = b_a[i] * b_y[0];
  }

  memcpy(&c_y[0], &b_y[0], 518U * sizeof(double));
  filter(dv0, dv2, c_y, a, b_y);
  flipud(b_y);

  //  2.1 Divide by max value to acheive peak of 1
  //  X0 = X0/ max( abs( X0 ) );
  //  3. Derivative Filter:
  y = 2.0 * b_y[9];
  base = 2.0 * b_y[508];
  for (k = 0; k < 3; k++) {
    d_y[k] = y - b_y[12 - k];
  }

  memcpy(&d_y[3], &b_y[9], 500U * sizeof(double));
  for (k = 0; k < 3; k++) {
    d_y[k + 503] = base - b_y[507 - k];
  }

  for (k = 0; k < 2; k++) {
    dv4[k] = 7.8125 + -16.5625 * (double)k;
  }

  memcpy(&e_y[0], &d_y[0], 506U * sizeof(double));
  b_filter(dv4, e_y, -8.75 * d_y[0], d_y);
  b_flipud(d_y);
  for (k = 0; k < 2; k++) {
    dv4[k] = 7.8125 + -16.5625 * (double)k;
  }

  memcpy(&e_y[0], &d_y[0], 506U * sizeof(double));
  b_filter(dv4, e_y, -8.75 * d_y[0], d_y);
  b_flipud(d_y);

  //  X2 = X2/max(X2);
  //  4. Square to accentuate ecg waveformsS
  for (k = 0; k < 500; k++) {
    X3[k] = d_y[k + 3] * d_y[k + 3];
  }

  //  5. Convolution filtering to smooth peaks:
  //  conv_filter = ones(1, round(0.150*62.5)) / round(0.150*62.5);
  //  Custom: Use Hann Window as filter - better defined peaks.
  memset(&X4[0], 0, 492U * sizeof(double));
  for (k = 0; k < 9; k++) {
    for (i = 0; i < 492; i++) {
      X4[i] += B[k] * X3[(i - k) + 8];
    }
  }

  // rescale_minmax
  //  Extract fiducial markers (peaks);
  i = 1;
  y = X4[0];
  if (rtIsNaN(X4[0])) {
    n = 2;
    exitg1 = false;
    while ((!exitg1) && (n < 493)) {
      i = n;
      if (!rtIsNaN(X4[n - 1])) {
        y = X4[n - 1];
        exitg1 = true;
      } else {
        n++;
      }
    }
  }

  if (i < 492) {
    while (i + 1 < 493) {
      if (X4[i] > y) {
        y = X4[i];
      }

      i++;
    }
  }

  emxInit_int32_T(&iPk, 1);
  emxInit_int32_T(&idx, 1);
  emxInit_int32_T(&iFinite, 1);
  emxInit_int32_T(&iInfinite, 1);

  //  [Peaks, Locations] = findpeaks(X4,'MinPeakProminence',0.3656836669*max_peak); 
  y *= 0.3656836669;
  getAllPeaksCodegen(X4, iFinite, iInfinite, idx);
  k = iPk->size[0];
  iPk->size[0] = iFinite->size[0];
  emxEnsureCapacity((emxArray__common *)iPk, k, sizeof(int));
  i = 0;
  for (k = 0; k + 1 <= iFinite->size[0]; k++) {
    if (X4[iFinite->data[k] - 1] > y) {
      if ((X4[iFinite->data[k] - 2] > X4[iFinite->data[k]]) || rtIsNaN
          (X4[iFinite->data[k]])) {
        base = X4[iFinite->data[k] - 2];
      } else {
        base = X4[iFinite->data[k]];
      }

      if (X4[iFinite->data[k] - 1] - base >= 0.0) {
        i++;
        iPk->data[i - 1] = iFinite->data[k];
      }
    }
  }

  emxInit_int32_T(&c, 1);
  emxInit_int32_T1(&f_y, 2);
  k = iPk->size[0];
  if (1 > i) {
    iPk->size[0] = 0;
  } else {
    iPk->size[0] = i;
  }

  emxEnsureCapacity((emxArray__common *)iPk, k, sizeof(int));
  do_vectors(iPk, iInfinite, c, idx, iFinite);
  i = c->size[0];
  emxFree_int32_T(&iInfinite);
  emxFree_int32_T(&iFinite);
  if (i < 1) {
    n = 0;
  } else {
    n = i;
  }

  k = f_y->size[0] * f_y->size[1];
  f_y->size[0] = 1;
  f_y->size[1] = n;
  emxEnsureCapacity((emxArray__common *)f_y, k, sizeof(int));
  if (n > 0) {
    f_y->data[0] = 1;
    i = 1;
    for (k = 2; k <= n; k++) {
      i++;
      f_y->data[k - 1] = i;
    }
  }

  k = idx->size[0];
  idx->size[0] = f_y->size[1];
  emxEnsureCapacity((emxArray__common *)idx, k, sizeof(int));
  i = f_y->size[1];
  for (k = 0; k < i; k++) {
    idx->data[k] = f_y->data[f_y->size[0] * k];
  }

  emxFree_int32_T(&f_y);
  if (idx->size[0] > 492) {
    emxInit_int32_T(&b_idx, 1);
    k = b_idx->size[0];
    b_idx->size[0] = 492;
    emxEnsureCapacity((emxArray__common *)b_idx, k, sizeof(int));
    for (k = 0; k < 492; k++) {
      b_idx->data[k] = idx->data[k];
    }

    k = idx->size[0];
    idx->size[0] = b_idx->size[0];
    emxEnsureCapacity((emxArray__common *)idx, k, sizeof(int));
    i = b_idx->size[0];
    for (k = 0; k < i; k++) {
      idx->data[k] = b_idx->data[k];
    }

    emxFree_int32_T(&b_idx);
  }

  k = iPk->size[0];
  iPk->size[0] = idx->size[0];
  emxEnsureCapacity((emxArray__common *)iPk, k, sizeof(int));
  i = idx->size[0];
  for (k = 0; k < i; k++) {
    iPk->data[k] = c->data[idx->data[k] - 1];
  }

  emxFree_int32_T(&c);
  emxInit_real_T(&b_X4, 1);
  k = b_X4->size[0];
  b_X4->size[0] = iPk->size[0] + iPk->size[0];
  emxEnsureCapacity((emxArray__common *)b_X4, k, sizeof(double));
  i = iPk->size[0];
  for (k = 0; k < i; k++) {
    b_X4->data[k] = X4[iPk->data[k] - 1];
  }

  i = iPk->size[0];
  for (k = 0; k < i; k++) {
    b_X4->data[k + iPk->size[0]] = (short)(1 + (short)(iPk->data[k] - 1));
  }

  k = Output->size[0];
  Output->size[0] = b_X4->size[0];
  emxEnsureCapacity((emxArray__common *)Output, k, sizeof(double));
  i = b_X4->size[0];
  for (k = 0; k < i; k++) {
    Output->data[k] = b_X4->data[k];
  }

  emxFree_real_T(&b_X4);
  emxInit_int16_T(&dist, 2);

  //  calculate distance between fiducial markers:
  n = idx->size[0] - 1;
  k = dist->size[0] * dist->size[1];
  dist->size[0] = 1;
  dist->size[1] = n;
  emxEnsureCapacity((emxArray__common *)dist, k, sizeof(short));
  for (k = 0; k < n; k++) {
    dist->data[k] = 0;
  }

  n = idx->size[0];
  i = 0;
  emxFree_int32_T(&idx);
  while (i <= n - 2) {
    dist->data[i] = (short)(iPk->data[i + 1] - iPk->data[i]);
    i++;
  }

  emxFree_int32_T(&iPk);
  if (dist->size[1] == 0) {
    y = 0.0;
  } else {
    y = dist->data[0];
    for (k = 2; k <= dist->size[1]; k++) {
      y += (double)dist->data[k - 1];
    }
  }

  //  average in seconds:
  y = 60.0 / (y / (double)dist->size[1] / 62.5);

  //  TODO: Get RR:
  *HR_mean = y;
  *Respiratory_rate = 0.0;
  emxFree_int16_T(&dist);
}

//
// Arguments    : void
// Return Type  : void
//
void get_hr_rr_initialize()
{
  rt_InitInfAndNaN(8U);
}

//
// Arguments    : void
// Return Type  : void
//
void get_hr_rr_terminate()
{
  // (no terminate code required)
}

//
// File trailer for get_hr_rr.cpp
//
// [EOF]
//
