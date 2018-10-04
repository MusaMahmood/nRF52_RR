//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: get_hr_rr.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 03-Oct-2018 23:07:16
//

// Include Files
#include "rt_nonfinite.h"
#include "get_hr_rr.h"
#include "get_hr_rr_emxutil.h"

// Function Declarations
static void b_do_vectors(const emxArray_int32_T *a, const emxArray_int32_T *b,
                         emxArray_int32_T *c, emxArray_int32_T *ia, emxArray_int32_T *ib);

static void b_filter(const double b[2], const double x[506], double zi, double
y[506]);

static void b_flipud(double x[506]);

static void do_vectors(const emxArray_int32_T *a, const emxArray_int32_T *b,
                       emxArray_int32_T *c, emxArray_int32_T *ia, emxArray_int32_T *ib);

static void filter(double b[4], double a[4], const double x[518], const double
zi[3], double y[518]);

static void findExtents(const double y[492], emxArray_int32_T *iPk, const
emxArray_int32_T *iFin, const emxArray_int32_T *iInf, const emxArray_int32_T
                        *iInflect, double minP, emxArray_real_T *bPk, emxArray_real_T *bxPk,
                        emxArray_real_T *byPk, emxArray_real_T *wxPk);

static void findpeaks(const double Yin[492], double varargin_2, emxArray_real_T *
Ypk, emxArray_real_T *Xpk);

static void flipud(double x[518]);

static void getAllPeaksCodegen(const double y[492], emxArray_int32_T *iPk,
                               emxArray_int32_T *iInf, emxArray_int32_T *iInflect);

static void getLeftBase(const double yTemp[492], const emxArray_int32_T *iPeak,
                        const emxArray_int32_T *iFinite, const emxArray_int32_T *iInflect,
                        emxArray_int32_T *iBase, emxArray_int32_T *iSaddle);

static void getPeakBase(const double yTemp[492], const emxArray_int32_T *iPk,
                        const emxArray_int32_T *iFin, const emxArray_int32_T *iInflect,
                        emxArray_real_T *peakBase, emxArray_int32_T *iLeftSaddle, emxArray_int32_T
                        *iRightSaddle);

// Function Definitions

//
// Arguments    : const emxArray_int32_T *a
//                const emxArray_int32_T *b
//                emxArray_int32_T *c
//                emxArray_int32_T *ia
//                emxArray_int32_T *ib
// Return Type  : void
//
static void b_do_vectors(const emxArray_int32_T *a, const emxArray_int32_T *b,
                         emxArray_int32_T *c, emxArray_int32_T *ia, emxArray_int32_T *ib) {
    int iafirst;
    int ncmax;
    int nc;
    int ialast;
    int ibfirst;
    int iblast;
    int b_ialast;
    int ak;
    emxArray_int32_T *b_ia;
    int b_iblast;
    int bk;
    emxArray_int32_T *b_ib;
    emxArray_int32_T *b_c;
    iafirst = a->size[0];
    ncmax = b->size[0];
    if (iafirst < ncmax) {
        ncmax = iafirst;
    }

    iafirst = c->size[0];
    c->size[0] = ncmax;
    emxEnsureCapacity((emxArray__common *) c, iafirst, sizeof(int));
    iafirst = ia->size[0];
    ia->size[0] = ncmax;
    emxEnsureCapacity((emxArray__common *) ia, iafirst, sizeof(int));
    iafirst = ib->size[0];
    ib->size[0] = ncmax;
    emxEnsureCapacity((emxArray__common *) ib, iafirst, sizeof(int));
    nc = 0;
    iafirst = 0;
    ialast = 1;
    ibfirst = 0;
    iblast = 1;
    while ((ialast <= a->size[0]) && (iblast <= b->size[0])) {
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
            c->data[nc - 1] = ak;
            ia->data[nc - 1] = iafirst + 1;
            ib->data[nc - 1] = ibfirst + 1;
            ialast = b_ialast + 1;
            iafirst = b_ialast;
            iblast = b_iblast + 1;
            ibfirst = b_iblast;
        } else if (ak < bk) {
            ialast = b_ialast + 1;
            iafirst = b_ialast;
        } else {
            iblast = b_iblast + 1;
            ibfirst = b_iblast;
        }
    }

    if (ncmax > 0) {
        if (1 > nc) {
            ialast = 0;
        } else {
            ialast = nc;
        }

        emxInit_int32_T(&b_ia, 1);
        iafirst = b_ia->size[0];
        b_ia->size[0] = ialast;
        emxEnsureCapacity((emxArray__common *) b_ia, iafirst, sizeof(int));
        for (iafirst = 0; iafirst < ialast; iafirst++) {
            b_ia->data[iafirst] = ia->data[iafirst];
        }

        iafirst = ia->size[0];
        ia->size[0] = b_ia->size[0];
        emxEnsureCapacity((emxArray__common *) ia, iafirst, sizeof(int));
        ialast = b_ia->size[0];
        for (iafirst = 0; iafirst < ialast; iafirst++) {
            ia->data[iafirst] = b_ia->data[iafirst];
        }

        emxFree_int32_T(&b_ia);
        if (1 > nc) {
            ialast = 0;
        } else {
            ialast = nc;
        }

        emxInit_int32_T(&b_ib, 1);
        iafirst = b_ib->size[0];
        b_ib->size[0] = ialast;
        emxEnsureCapacity((emxArray__common *) b_ib, iafirst, sizeof(int));
        for (iafirst = 0; iafirst < ialast; iafirst++) {
            b_ib->data[iafirst] = ib->data[iafirst];
        }

        iafirst = ib->size[0];
        ib->size[0] = b_ib->size[0];
        emxEnsureCapacity((emxArray__common *) ib, iafirst, sizeof(int));
        ialast = b_ib->size[0];
        for (iafirst = 0; iafirst < ialast; iafirst++) {
            ib->data[iafirst] = b_ib->data[iafirst];
        }

        emxFree_int32_T(&b_ib);
        if (1 > nc) {
            ialast = 0;
        } else {
            ialast = nc;
        }

        emxInit_int32_T(&b_c, 1);
        iafirst = b_c->size[0];
        b_c->size[0] = ialast;
        emxEnsureCapacity((emxArray__common *) b_c, iafirst, sizeof(int));
        for (iafirst = 0; iafirst < ialast; iafirst++) {
            b_c->data[iafirst] = c->data[iafirst];
        }

        iafirst = c->size[0];
        c->size[0] = b_c->size[0];
        emxEnsureCapacity((emxArray__common *) c, iafirst, sizeof(int));
        ialast = b_c->size[0];
        for (iafirst = 0; iafirst < ialast; iafirst++) {
            c->data[iafirst] = b_c->data[iafirst];
        }

        emxFree_int32_T(&b_c);
    }
}

//
// Arguments    : const double b[2]
//                const double x[506]
//                double zi
//                double y[506]
// Return Type  : void
//
static void b_filter(const double b[2], const double x[506], double zi, double
y[506]) {
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
static void b_flipud(double x[506]) {
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
                       emxArray_int32_T *c, emxArray_int32_T *ia, emxArray_int32_T *ib) {
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
    emxEnsureCapacity((emxArray__common *) c, iafirst, sizeof(int));
    iafirst = ia->size[0];
    ia->size[0] = a->size[0];
    emxEnsureCapacity((emxArray__common *) ia, iafirst, sizeof(int));
    iafirst = ib->size[0];
    ib->size[0] = b->size[0];
    emxEnsureCapacity((emxArray__common *) ib, iafirst, sizeof(int));
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
        while ((b_ialast < a->size[0]) && (a->data[b_ialast] == a->data[ialast - 1])) {
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
        while ((b_iblast < b->size[0]) && (b->data[b_iblast] == b->data[iblast - 1])) {
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
        emxEnsureCapacity((emxArray__common *) b_ia, iafirst, sizeof(int));
        for (iafirst = 0; iafirst <= nia; iafirst++) {
            b_ia->data[iafirst] = ia->data[iafirst];
        }

        iafirst = ia->size[0];
        ia->size[0] = b_ia->size[0];
        emxEnsureCapacity((emxArray__common *) ia, iafirst, sizeof(int));
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
        emxEnsureCapacity((emxArray__common *) b_ib, iafirst, sizeof(int));
        for (iafirst = 0; iafirst < nia; iafirst++) {
            b_ib->data[iafirst] = ib->data[iafirst];
        }

        iafirst = ib->size[0];
        ib->size[0] = b_ib->size[0];
        emxEnsureCapacity((emxArray__common *) ib, iafirst, sizeof(int));
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
        emxEnsureCapacity((emxArray__common *) b_c, iafirst, sizeof(int));
        for (iafirst = 0; iafirst <= nia; iafirst++) {
            b_c->data[iafirst] = c->data[iafirst];
        }

        iafirst = c->size[0];
        c->size[0] = b_c->size[0];
        emxEnsureCapacity((emxArray__common *) c, iafirst, sizeof(int));
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
zi[3], double y[518]) {
    double a1;
    int k;
    int naxpy;
    int j;
    a1 = a[0];
    if ((!rtIsInf(a[0])) && (!rtIsNaN(a[0])) && (!(a[0] == 0.0)) && (a[0] != 1.0)) {
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
// Arguments    : const double y[492]
//                emxArray_int32_T *iPk
//                const emxArray_int32_T *iFin
//                const emxArray_int32_T *iInf
//                const emxArray_int32_T *iInflect
//                double minP
//                emxArray_real_T *bPk
//                emxArray_real_T *bxPk
//                emxArray_real_T *byPk
//                emxArray_real_T *wxPk
// Return Type  : void
//
static void findExtents(const double y[492], emxArray_int32_T *iPk, const
emxArray_int32_T *iFin, const emxArray_int32_T *iInf, const emxArray_int32_T
                        *iInflect, double minP, emxArray_real_T *bPk, emxArray_real_T *bxPk,
                        emxArray_real_T *byPk, emxArray_real_T *wxPk) {
    double yFinite[492];
    int iLeft;
    int i1;
    emxArray_real_T *b_bPk;
    emxArray_int32_T *iLB;
    emxArray_int32_T *iRB;
    emxArray_boolean_T *x;
    emxArray_int32_T *ii;
    int nx;
    int idx;
    boolean_T exitg1;
    emxArray_real_T *b_idx;
    emxArray_int32_T *b_iPk;
    emxArray_real_T *c_bPk;
    emxArray_int32_T *b_iLB;
    emxArray_int32_T *b_iRB;
    unsigned int unnamed_idx_0;
    emxArray_real_T *b_wxPk;
    emxArray_int32_T *iInfL;
    double refHeight;
    emxArray_int32_T *iInfR;
    emxArray_int32_T *c;
    double xc;
    emxArray_int32_T *iInfinite;
    emxArray_real_T *r1;
    emxArray_real_T *r2;
    memcpy(&yFinite[0], &y[0], 492U * sizeof(double));
    iLeft = iInf->size[0];
    for (i1 = 0; i1 < iLeft; i1++) {
        yFinite[iInf->data[i1] - 1] = rtNaN;
    }

    emxInit_real_T1(&b_bPk, 1);
    emxInit_int32_T(&iLB, 1);
    emxInit_int32_T(&iRB, 1);
    emxInit_boolean_T(&x, 1);
    getPeakBase(yFinite, iPk, iFin, iInflect, b_bPk, iLB, iRB);
    i1 = x->size[0];
    x->size[0] = iPk->size[0];
    emxEnsureCapacity((emxArray__common *) x, i1, sizeof(boolean_T));
    iLeft = iPk->size[0];
    for (i1 = 0; i1 < iLeft; i1++) {
        x->data[i1] = (yFinite[iPk->data[i1] - 1] - b_bPk->data[i1] >= minP);
    }

    emxInit_int32_T(&ii, 1);
    nx = x->size[0];
    idx = 0;
    i1 = ii->size[0];
    ii->size[0] = x->size[0];
    emxEnsureCapacity((emxArray__common *) ii, i1, sizeof(int));
    iLeft = 1;
    exitg1 = false;
    while ((!exitg1) && (iLeft <= nx)) {
        if (x->data[iLeft - 1]) {
            idx++;
            ii->data[idx - 1] = iLeft;
            if (idx >= nx) {
                exitg1 = true;
            } else {
                iLeft++;
            }
        } else {
            iLeft++;
        }
    }

    if (x->size[0] == 1) {
        if (idx == 0) {
            i1 = ii->size[0];
            ii->size[0] = 0;
            emxEnsureCapacity((emxArray__common *) ii, i1, sizeof(int));
        }
    } else {
        i1 = ii->size[0];
        if (1 > idx) {
            ii->size[0] = 0;
        } else {
            ii->size[0] = idx;
        }

        emxEnsureCapacity((emxArray__common *) ii, i1, sizeof(int));
    }

    emxFree_boolean_T(&x);
    emxInit_real_T1(&b_idx, 1);
    i1 = b_idx->size[0];
    b_idx->size[0] = ii->size[0];
    emxEnsureCapacity((emxArray__common *) b_idx, i1, sizeof(double));
    iLeft = ii->size[0];
    for (i1 = 0; i1 < iLeft; i1++) {
        b_idx->data[i1] = ii->data[i1];
    }

    emxInit_int32_T(&b_iPk, 1);
    i1 = b_iPk->size[0];
    b_iPk->size[0] = b_idx->size[0];
    emxEnsureCapacity((emxArray__common *) b_iPk, i1, sizeof(int));
    iLeft = b_idx->size[0];
    for (i1 = 0; i1 < iLeft; i1++) {
        b_iPk->data[i1] = iPk->data[(int) b_idx->data[i1] - 1];
    }

    i1 = iPk->size[0];
    iPk->size[0] = b_iPk->size[0];
    emxEnsureCapacity((emxArray__common *) iPk, i1, sizeof(int));
    iLeft = b_iPk->size[0];
    for (i1 = 0; i1 < iLeft; i1++) {
        iPk->data[i1] = b_iPk->data[i1];
    }

    emxFree_int32_T(&b_iPk);
    emxInit_real_T1(&c_bPk, 1);
    i1 = c_bPk->size[0];
    c_bPk->size[0] = b_idx->size[0];
    emxEnsureCapacity((emxArray__common *) c_bPk, i1, sizeof(double));
    iLeft = b_idx->size[0];
    for (i1 = 0; i1 < iLeft; i1++) {
        c_bPk->data[i1] = b_bPk->data[(int) b_idx->data[i1] - 1];
    }

    i1 = b_bPk->size[0];
    b_bPk->size[0] = c_bPk->size[0];
    emxEnsureCapacity((emxArray__common *) b_bPk, i1, sizeof(double));
    iLeft = c_bPk->size[0];
    for (i1 = 0; i1 < iLeft; i1++) {
        b_bPk->data[i1] = c_bPk->data[i1];
    }

    emxFree_real_T(&c_bPk);
    emxInit_int32_T(&b_iLB, 1);
    i1 = b_iLB->size[0];
    b_iLB->size[0] = b_idx->size[0];
    emxEnsureCapacity((emxArray__common *) b_iLB, i1, sizeof(int));
    iLeft = b_idx->size[0];
    for (i1 = 0; i1 < iLeft; i1++) {
        b_iLB->data[i1] = iLB->data[(int) b_idx->data[i1] - 1];
    }

    i1 = iLB->size[0];
    iLB->size[0] = b_iLB->size[0];
    emxEnsureCapacity((emxArray__common *) iLB, i1, sizeof(int));
    iLeft = b_iLB->size[0];
    for (i1 = 0; i1 < iLeft; i1++) {
        iLB->data[i1] = b_iLB->data[i1];
    }

    emxFree_int32_T(&b_iLB);
    emxInit_int32_T(&b_iRB, 1);
    i1 = b_iRB->size[0];
    b_iRB->size[0] = b_idx->size[0];
    emxEnsureCapacity((emxArray__common *) b_iRB, i1, sizeof(int));
    iLeft = b_idx->size[0];
    for (i1 = 0; i1 < iLeft; i1++) {
        b_iRB->data[i1] = iRB->data[(int) b_idx->data[i1] - 1];
    }

    i1 = iRB->size[0];
    iRB->size[0] = b_iRB->size[0];
    emxEnsureCapacity((emxArray__common *) iRB, i1, sizeof(int));
    iLeft = b_iRB->size[0];
    for (i1 = 0; i1 < iLeft; i1++) {
        iRB->data[i1] = b_iRB->data[i1];
    }

    emxFree_int32_T(&b_iRB);
    if (iPk->size[0] == 0) {
        unnamed_idx_0 = (unsigned int) iPk->size[0];
        i1 = b_idx->size[0];
        b_idx->size[0] = (int) unnamed_idx_0;
        emxEnsureCapacity((emxArray__common *) b_idx, i1, sizeof(double));
        iLeft = (int) unnamed_idx_0;
        for (i1 = 0; i1 < iLeft; i1++) {
            b_idx->data[i1] = 0.0;
        }

        unnamed_idx_0 = (unsigned int) iPk->size[0];
        i1 = iLB->size[0];
        iLB->size[0] = (int) unnamed_idx_0;
        emxEnsureCapacity((emxArray__common *) iLB, i1, sizeof(int));
        iLeft = (int) unnamed_idx_0;
        for (i1 = 0; i1 < iLeft; i1++) {
            iLB->data[i1] = 0;
        }

        unnamed_idx_0 = (unsigned int) iPk->size[0];
        i1 = iRB->size[0];
        iRB->size[0] = (int) unnamed_idx_0;
        emxEnsureCapacity((emxArray__common *) iRB, i1, sizeof(int));
        iLeft = (int) unnamed_idx_0;
        for (i1 = 0; i1 < iLeft; i1++) {
            iRB->data[i1] = 0;
        }
    } else {
        i1 = b_idx->size[0];
        b_idx->size[0] = b_bPk->size[0];
        emxEnsureCapacity((emxArray__common *) b_idx, i1, sizeof(double));
        iLeft = b_bPk->size[0];
        for (i1 = 0; i1 < iLeft; i1++) {
            b_idx->data[i1] = b_bPk->data[i1];
        }
    }

    emxInit_real_T(&b_wxPk, 2);
    i1 = b_wxPk->size[0] * b_wxPk->size[1];
    b_wxPk->size[0] = iPk->size[0];
    b_wxPk->size[1] = 2;
    emxEnsureCapacity((emxArray__common *) b_wxPk, i1, sizeof(double));
    iLeft = iPk->size[0] << 1;
    for (i1 = 0; i1 < iLeft; i1++) {
        b_wxPk->data[i1] = 0.0;
    }

    for (nx = 0; nx < iPk->size[0]; nx++) {
        refHeight = (yFinite[iPk->data[nx] - 1] + b_idx->data[nx]) / 2.0;
        iLeft = iPk->data[nx];
        while ((iLeft >= iLB->data[nx]) && (yFinite[iLeft - 1] > refHeight)) {
            iLeft--;
        }

        if (iLeft < iLB->data[nx]) {
            b_wxPk->data[nx] = 1.0 + ((double) iLB->data[nx] - 1.0);
        } else {
            xc = (1.0 + ((double) iLeft - 1.0)) + (0.5 * (yFinite[iPk->data[nx] - 1] +
                                                          b_idx->data[nx]) - yFinite[iLeft - 1]) /
                                                  (yFinite[iLeft] - yFinite[iLeft
                                                                            - 1]);
            if (rtIsNaN(xc)) {
                if (rtIsInf(b_idx->data[nx])) {
                    xc = 0.5 * (double) ((iLeft + iLeft) + 1);
                } else {
                    xc = 1.0 + (double) iLeft;
                }
            }

            b_wxPk->data[nx] = xc;
        }

        iLeft = iPk->data[nx];
        while ((iLeft <= iRB->data[nx]) && (yFinite[iLeft - 1] > refHeight)) {
            iLeft++;
        }

        if (iLeft > iRB->data[nx]) {
            b_wxPk->data[nx + b_wxPk->size[0]] = 1.0 + ((double) iRB->data[nx] - 1.0);
        } else {
            xc = (1.0 + ((double) iLeft - 1.0)) + -(0.5 * (yFinite[iPk->data[nx] - 1] +
                                                           b_idx->data[nx]) - yFinite[iLeft - 1]) /
                                                  (yFinite[iLeft - 2] -
                                                   yFinite[iLeft - 1]);
            if (rtIsNaN(xc)) {
                if (rtIsInf(b_idx->data[nx])) {
                    xc = 0.5 * (double) ((iLeft + iLeft) - 1);
                } else {
                    xc = 1.0 + ((double) iLeft - 2.0);
                }
            }

            b_wxPk->data[nx + b_wxPk->size[0]] = xc;
        }
    }

    emxInit_int32_T(&iInfL, 1);
    emxInit_int32_T(&iInfR, 1);
    emxInit_int32_T(&c, 1);
    do_vectors(iPk, iInf, c, ii, iInfR);
    b_do_vectors(c, iPk, iInfL, ii, iInfR);
    i1 = b_idx->size[0];
    b_idx->size[0] = ii->size[0];
    emxEnsureCapacity((emxArray__common *) b_idx, i1, sizeof(double));
    iLeft = ii->size[0];
    for (i1 = 0; i1 < iLeft; i1++) {
        b_idx->data[i1] = ii->data[i1];
    }

    emxInit_int32_T(&iInfinite, 1);
    b_do_vectors(c, iInf, iInfL, ii, iInfR);
    i1 = iInfinite->size[0];
    iInfinite->size[0] = ii->size[0];
    emxEnsureCapacity((emxArray__common *) iInfinite, i1, sizeof(int));
    iLeft = ii->size[0];
    for (i1 = 0; i1 < iLeft; i1++) {
        iInfinite->data[i1] = ii->data[i1];
    }

    iLeft = c->size[0];
    i1 = c->size[0];
    c->size[0] = iLeft;
    emxEnsureCapacity((emxArray__common *) c, i1, sizeof(int));
    unnamed_idx_0 = (unsigned int) c->size[0];
    i1 = bPk->size[0];
    bPk->size[0] = (int) unnamed_idx_0;
    emxEnsureCapacity((emxArray__common *) bPk, i1, sizeof(double));
    iLeft = (int) unnamed_idx_0;
    for (i1 = 0; i1 < iLeft; i1++) {
        bPk->data[i1] = 0.0;
    }

    iLeft = b_bPk->size[0];
    for (i1 = 0; i1 < iLeft; i1++) {
        bPk->data[(int) b_idx->data[i1] - 1] = b_bPk->data[i1];
    }

    emxFree_real_T(&b_bPk);
    i1 = ii->size[0];
    ii->size[0] = iInfinite->size[0];
    emxEnsureCapacity((emxArray__common *) ii, i1, sizeof(int));
    iLeft = iInfinite->size[0];
    for (i1 = 0; i1 < iLeft; i1++) {
        ii->data[i1] = iInfinite->data[i1];
    }

    iLeft = ii->size[0];
    for (i1 = 0; i1 < iLeft; i1++) {
        bPk->data[ii->data[i1] - 1] = 0.0;
    }

    i1 = ii->size[0];
    ii->size[0] = iInf->size[0];
    emxEnsureCapacity((emxArray__common *) ii, i1, sizeof(int));
    iLeft = iInf->size[0];
    for (i1 = 0; i1 < iLeft; i1++) {
        ii->data[i1] = iInf->data[i1] - 1;
    }

    unnamed_idx_0 = (unsigned int) ii->size[0];
    i1 = iInfL->size[0];
    iInfL->size[0] = (int) unnamed_idx_0;
    emxEnsureCapacity((emxArray__common *) iInfL, i1, sizeof(int));
    for (nx = 0; nx + 1 <= (int) unnamed_idx_0; nx++) {
        if (ii->data[nx] < 1) {
            iLeft = 1;
        } else {
            iLeft = ii->data[nx];
        }

        iInfL->data[nx] = iLeft;
    }

    i1 = ii->size[0];
    ii->size[0] = iInf->size[0];
    emxEnsureCapacity((emxArray__common *) ii, i1, sizeof(int));
    iLeft = iInf->size[0];
    for (i1 = 0; i1 < iLeft; i1++) {
        ii->data[i1] = iInf->data[i1] + 1;
    }

    unnamed_idx_0 = (unsigned int) ii->size[0];
    i1 = iInfR->size[0];
    iInfR->size[0] = (int) unnamed_idx_0;
    emxEnsureCapacity((emxArray__common *) iInfR, i1, sizeof(int));
    for (nx = 0; nx + 1 <= (int) unnamed_idx_0; nx++) {
        iLeft = ii->data[nx];
        if (!(iLeft < 492)) {
            iLeft = 492;
        }

        iInfR->data[nx] = iLeft;
    }

    emxFree_int32_T(&ii);
    i1 = bxPk->size[0] * bxPk->size[1];
    bxPk->size[0] = c->size[0];
    bxPk->size[1] = 2;
    emxEnsureCapacity((emxArray__common *) bxPk, i1, sizeof(double));
    iLeft = c->size[0] << 1;
    for (i1 = 0; i1 < iLeft; i1++) {
        bxPk->data[i1] = 0.0;
    }

    emxInit_real_T1(&r1, 1);
    i1 = r1->size[0];
    r1->size[0] = iLB->size[0];
    emxEnsureCapacity((emxArray__common *) r1, i1, sizeof(double));
    iLeft = iLB->size[0];
    for (i1 = 0; i1 < iLeft; i1++) {
        r1->data[i1] = (short) (1 + (short) (iLB->data[i1] - 1));
    }

    iLeft = r1->size[0];
    for (i1 = 0; i1 < iLeft; i1++) {
        bxPk->data[(int) b_idx->data[i1] - 1] = r1->data[i1];
    }

    emxFree_real_T(&r1);
    emxInit_real_T1(&r2, 1);
    i1 = r2->size[0];
    r2->size[0] = iRB->size[0];
    emxEnsureCapacity((emxArray__common *) r2, i1, sizeof(double));
    iLeft = iRB->size[0];
    for (i1 = 0; i1 < iLeft; i1++) {
        r2->data[i1] = (short) (1 + (short) (iRB->data[i1] - 1));
    }

    iLeft = r2->size[0];
    for (i1 = 0; i1 < iLeft; i1++) {
        bxPk->data[((int) b_idx->data[i1] + bxPk->size[0]) - 1] = r2->data[i1];
    }

    emxFree_real_T(&r2);
    iLeft = iInf->size[0];
    for (i1 = 0; i1 < iLeft; i1++) {
        bxPk->data[iInfinite->data[i1] - 1] = 0.5 * (double) (short) ((short) ((short)
                                                                                       (iInf->data[i1] -
                                                                                        1) +
                                                                               (short) (
                                                                                       iInfL->data[i1] -
                                                                                       1)) + 2);
    }

    iLeft = iInf->size[0];
    for (i1 = 0; i1 < iLeft; i1++) {
        bxPk->data[(iInfinite->data[i1] + bxPk->size[0]) - 1] = 0.5 * (double) (short)
                ((short) ((short) (iInf->data[i1] - 1) + (short) (iInfR->data[i1] - 1)) + 2);
    }

    i1 = byPk->size[0] * byPk->size[1];
    byPk->size[0] = c->size[0];
    byPk->size[1] = 2;
    emxEnsureCapacity((emxArray__common *) byPk, i1, sizeof(double));
    iLeft = c->size[0] << 1;
    for (i1 = 0; i1 < iLeft; i1++) {
        byPk->data[i1] = 0.0;
    }

    iLeft = iLB->size[0];
    for (i1 = 0; i1 < iLeft; i1++) {
        byPk->data[(int) b_idx->data[i1] - 1] = y[iLB->data[i1] - 1];
    }

    emxFree_int32_T(&iLB);
    iLeft = iRB->size[0];
    for (i1 = 0; i1 < iLeft; i1++) {
        byPk->data[((int) b_idx->data[i1] + byPk->size[0]) - 1] = y[iRB->data[i1] - 1];
    }

    emxFree_int32_T(&iRB);
    iLeft = iInfL->size[0];
    for (i1 = 0; i1 < iLeft; i1++) {
        byPk->data[iInfinite->data[i1] - 1] = y[iInfL->data[i1] - 1];
    }

    iLeft = iInfR->size[0];
    for (i1 = 0; i1 < iLeft; i1++) {
        byPk->data[(iInfinite->data[i1] + byPk->size[0]) - 1] = y[iInfR->data[i1] -
                                                                  1];
    }

    i1 = wxPk->size[0] * wxPk->size[1];
    wxPk->size[0] = c->size[0];
    wxPk->size[1] = 2;
    emxEnsureCapacity((emxArray__common *) wxPk, i1, sizeof(double));
    iLeft = c->size[0] << 1;
    for (i1 = 0; i1 < iLeft; i1++) {
        wxPk->data[i1] = 0.0;
    }

    for (i1 = 0; i1 < 2; i1++) {
        iLeft = b_wxPk->size[0];
        for (nx = 0; nx < iLeft; nx++) {
            wxPk->data[((int) b_idx->data[nx] + wxPk->size[0] * i1) - 1] = b_wxPk->
                    data[nx + b_wxPk->size[0] * i1];
        }
    }

    emxFree_real_T(&b_idx);
    emxFree_real_T(&b_wxPk);
    iLeft = iInf->size[0];
    for (i1 = 0; i1 < iLeft; i1++) {
        wxPk->data[iInfinite->data[i1] - 1] = 0.5 * (double) (short) ((short) ((short)
                                                                                       (iInf->data[i1] -
                                                                                        1) +
                                                                               (short) (
                                                                                       iInfL->data[i1] -
                                                                                       1)) + 2);
    }

    emxFree_int32_T(&iInfL);
    iLeft = iInf->size[0];
    for (i1 = 0; i1 < iLeft; i1++) {
        wxPk->data[(iInfinite->data[i1] + wxPk->size[0]) - 1] = 0.5 * (double) (short)
                ((short) ((short) (iInf->data[i1] - 1) + (short) (iInfR->data[i1] - 1)) + 2);
    }

    emxFree_int32_T(&iInfinite);
    emxFree_int32_T(&iInfR);
    i1 = iPk->size[0];
    iPk->size[0] = c->size[0];
    emxEnsureCapacity((emxArray__common *) iPk, i1, sizeof(int));
    iLeft = c->size[0];
    for (i1 = 0; i1 < iLeft; i1++) {
        iPk->data[i1] = c->data[i1];
    }

    emxFree_int32_T(&c);
}

//
// Arguments    : const double Yin[492]
//                double varargin_2
//                emxArray_real_T *Ypk
//                emxArray_real_T *Xpk
// Return Type  : void
//
static void findpeaks(const double Yin[492], double varargin_2, emxArray_real_T *
Ypk, emxArray_real_T *Xpk) {
    boolean_T needWidth;
    emxArray_int32_T *iPk;
    emxArray_int32_T *idx;
    emxArray_int32_T *iInfinite;
    emxArray_int32_T *iInflect;
    int k;
    int nPk;
    double base;
    emxArray_real_T *bPk;
    emxArray_int32_T *b_iPk;
    emxArray_real_T *bxPk;
    emxArray_real_T *byPk;
    emxArray_real_T *wxPk;
    emxArray_int32_T *y;
    int n;
    emxArray_int32_T *b_idx;
    emxArray_int32_T *c_iPk;
    emxArray_real_T *r0;
    needWidth = (varargin_2 > 0.0);
    emxInit_int32_T(&iPk, 1);
    emxInit_int32_T(&idx, 1);
    emxInit_int32_T(&iInfinite, 1);
    emxInit_int32_T(&iInflect, 1);
    getAllPeaksCodegen(Yin, idx, iInfinite, iInflect);
    k = iPk->size[0];
    iPk->size[0] = idx->size[0];
    emxEnsureCapacity((emxArray__common *) iPk, k, sizeof(int));
    nPk = 0;
    for (k = 0; k + 1 <= idx->size[0]; k++) {
        if (Yin[idx->data[k] - 1] > rtMinusInf) {
            if ((Yin[idx->data[k] - 2] > Yin[idx->data[k]]) || rtIsNaN(Yin[idx->data[k]])) {
                base = Yin[idx->data[k] - 2];
            } else {
                base = Yin[idx->data[k]];
            }

            if (Yin[idx->data[k] - 1] - base >= 0.0) {
                nPk++;
                iPk->data[nPk - 1] = idx->data[k];
            }
        }
    }

    k = iPk->size[0];
    if (1 > nPk) {
        iPk->size[0] = 0;
    } else {
        iPk->size[0] = nPk;
    }

    emxEnsureCapacity((emxArray__common *) iPk, k, sizeof(int));
    emxInit_real_T1(&bPk, 1);
    if (needWidth) {
        emxInit_real_T(&bxPk, 2);
        emxInit_real_T(&byPk, 2);
        emxInit_real_T(&wxPk, 2);
        findExtents(Yin, iPk, idx, iInfinite, iInflect, varargin_2, bPk, bxPk, byPk,
                    wxPk);
        emxFree_real_T(&wxPk);
        emxFree_real_T(&byPk);
        emxFree_real_T(&bxPk);
    } else {
        emxInit_int32_T(&b_iPk, 1);
        k = b_iPk->size[0];
        b_iPk->size[0] = iPk->size[0];
        emxEnsureCapacity((emxArray__common *) b_iPk, k, sizeof(int));
        nPk = iPk->size[0];
        for (k = 0; k < nPk; k++) {
            b_iPk->data[k] = iPk->data[k];
        }

        do_vectors(b_iPk, iInfinite, iPk, idx, iInflect);
        emxFree_int32_T(&b_iPk);
    }

    emxFree_int32_T(&iInflect);
    emxFree_int32_T(&iInfinite);
    emxInit_int32_T1(&y, 2);
    nPk = iPk->size[0];
    if (nPk < 1) {
        n = 0;
    } else {
        n = nPk;
    }

    k = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = n;
    emxEnsureCapacity((emxArray__common *) y, k, sizeof(int));
    if (n > 0) {
        y->data[0] = 1;
        nPk = 1;
        for (k = 2; k <= n; k++) {
            nPk++;
            y->data[k - 1] = nPk;
        }
    }

    k = idx->size[0];
    idx->size[0] = y->size[1];
    emxEnsureCapacity((emxArray__common *) idx, k, sizeof(int));
    nPk = y->size[1];
    for (k = 0; k < nPk; k++) {
        idx->data[k] = y->data[y->size[0] * k];
    }

    emxFree_int32_T(&y);
    if (idx->size[0] > 492) {
        emxInit_int32_T(&b_idx, 1);
        k = b_idx->size[0];
        b_idx->size[0] = 492;
        emxEnsureCapacity((emxArray__common *) b_idx, k, sizeof(int));
        for (k = 0; k < 492; k++) {
            b_idx->data[k] = idx->data[k];
        }

        k = idx->size[0];
        idx->size[0] = b_idx->size[0];
        emxEnsureCapacity((emxArray__common *) idx, k, sizeof(int));
        nPk = b_idx->size[0];
        for (k = 0; k < nPk; k++) {
            idx->data[k] = b_idx->data[k];
        }

        emxFree_int32_T(&b_idx);
    }

    emxInit_int32_T(&c_iPk, 1);
    k = c_iPk->size[0];
    c_iPk->size[0] = idx->size[0];
    emxEnsureCapacity((emxArray__common *) c_iPk, k, sizeof(int));
    nPk = idx->size[0];
    for (k = 0; k < nPk; k++) {
        c_iPk->data[k] = iPk->data[idx->data[k] - 1];
    }

    emxFree_int32_T(&idx);
    k = iPk->size[0];
    iPk->size[0] = c_iPk->size[0];
    emxEnsureCapacity((emxArray__common *) iPk, k, sizeof(int));
    nPk = c_iPk->size[0];
    for (k = 0; k < nPk; k++) {
        iPk->data[k] = c_iPk->data[k];
    }

    emxFree_int32_T(&c_iPk);
    if (needWidth) {
        k = Ypk->size[0];
        Ypk->size[0] = iPk->size[0];
        emxEnsureCapacity((emxArray__common *) Ypk, k, sizeof(double));
        nPk = iPk->size[0];
        for (k = 0; k < nPk; k++) {
            Ypk->data[k] = Yin[iPk->data[k] - 1];
        }

        emxInit_real_T1(&r0, 1);
        k = r0->size[0];
        r0->size[0] = iPk->size[0];
        emxEnsureCapacity((emxArray__common *) r0, k, sizeof(double));
        nPk = iPk->size[0];
        for (k = 0; k < nPk; k++) {
            r0->data[k] = (short) (1 + (short) (iPk->data[k] - 1));
        }

        k = Xpk->size[0];
        Xpk->size[0] = r0->size[0];
        emxEnsureCapacity((emxArray__common *) Xpk, k, sizeof(double));
        nPk = r0->size[0];
        for (k = 0; k < nPk; k++) {
            Xpk->data[k] = r0->data[k];
        }

        emxFree_real_T(&r0);
    } else {
        k = Ypk->size[0];
        Ypk->size[0] = iPk->size[0];
        emxEnsureCapacity((emxArray__common *) Ypk, k, sizeof(double));
        nPk = iPk->size[0];
        for (k = 0; k < nPk; k++) {
            Ypk->data[k] = Yin[iPk->data[k] - 1];
        }

        emxInit_real_T1(&r0, 1);
        k = r0->size[0];
        r0->size[0] = iPk->size[0];
        emxEnsureCapacity((emxArray__common *) r0, k, sizeof(double));
        nPk = iPk->size[0];
        for (k = 0; k < nPk; k++) {
            r0->data[k] = (short) (1 + (short) (iPk->data[k] - 1));
        }

        k = Xpk->size[0];
        Xpk->size[0] = r0->size[0];
        emxEnsureCapacity((emxArray__common *) Xpk, k, sizeof(double));
        nPk = r0->size[0];
        for (k = 0; k < nPk; k++) {
            Xpk->data[k] = r0->data[k];
        }

        emxFree_real_T(&r0);
    }

    emxFree_real_T(&bPk);
    emxFree_int32_T(&iPk);
}

//
// Arguments    : double x[518]
// Return Type  : void
//
static void flipud(double x[518]) {
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
                               emxArray_int32_T *iInf, emxArray_int32_T *iInflect) {
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
    emxEnsureCapacity((emxArray__common *) iPk, kfirst, sizeof(int));
    kfirst = iInf->size[0];
    iInf->size[0] = 492;
    emxEnsureCapacity((emxArray__common *) iInf, kfirst, sizeof(int));
    kfirst = iInflect->size[0];
    iInflect->size[0] = 492;
    emxEnsureCapacity((emxArray__common *) iInflect, kfirst, sizeof(int));
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

    if ((!isinfykfirst) && ((nInflect + 1 == 0) || (iInflect->data[nInflect] < 492))) {
        nInflect++;
        iInflect->data[nInflect] = 492;
    }

    kfirst = iPk->size[0];
    if (1 > nPk) {
        iPk->size[0] = 0;
    } else {
        iPk->size[0] = nPk;
    }

    emxEnsureCapacity((emxArray__common *) iPk, kfirst, sizeof(int));
    kfirst = iInf->size[0];
    if (1 > nInf) {
        iInf->size[0] = 0;
    } else {
        iInf->size[0] = nInf;
    }

    emxEnsureCapacity((emxArray__common *) iInf, kfirst, sizeof(int));
    kfirst = iInflect->size[0];
    if (1 > nInflect + 1) {
        i0 = -1;
    } else {
        i0 = nInflect;
    }

    iInflect->size[0] = i0 + 1;
    emxEnsureCapacity((emxArray__common *) iInflect, kfirst, sizeof(int));
}

//
// Arguments    : const double yTemp[492]
//                const emxArray_int32_T *iPeak
//                const emxArray_int32_T *iFinite
//                const emxArray_int32_T *iInflect
//                emxArray_int32_T *iBase
//                emxArray_int32_T *iSaddle
// Return Type  : void
//
static void getLeftBase(const double yTemp[492], const emxArray_int32_T *iPeak,
                        const emxArray_int32_T *iFinite, const emxArray_int32_T *iInflect,
                        emxArray_int32_T *iBase, emxArray_int32_T *iSaddle) {
    unsigned int unnamed_idx_0;
    int n;
    int i;
    emxArray_real_T *peak;
    emxArray_real_T *valley;
    emxArray_int32_T *iValley;
    int j;
    int k;
    double v;
    int iv;
    double p;
    int isv;
    unnamed_idx_0 = (unsigned int) iPeak->size[0];
    n = iBase->size[0];
    iBase->size[0] = (int) unnamed_idx_0;
    emxEnsureCapacity((emxArray__common *) iBase, n, sizeof(int));
    i = (int) unnamed_idx_0;
    for (n = 0; n < i; n++) {
        iBase->data[n] = 0;
    }

    unnamed_idx_0 = (unsigned int) iPeak->size[0];
    n = iSaddle->size[0];
    iSaddle->size[0] = (int) unnamed_idx_0;
    emxEnsureCapacity((emxArray__common *) iSaddle, n, sizeof(int));
    i = (int) unnamed_idx_0;
    for (n = 0; n < i; n++) {
        iSaddle->data[n] = 0;
    }

    emxInit_real_T1(&peak, 1);
    unnamed_idx_0 = (unsigned int) iFinite->size[0];
    n = peak->size[0];
    peak->size[0] = (int) unnamed_idx_0;
    emxEnsureCapacity((emxArray__common *) peak, n, sizeof(double));
    i = (int) unnamed_idx_0;
    for (n = 0; n < i; n++) {
        peak->data[n] = 0.0;
    }

    emxInit_real_T1(&valley, 1);
    unnamed_idx_0 = (unsigned int) iFinite->size[0];
    n = valley->size[0];
    valley->size[0] = (int) unnamed_idx_0;
    emxEnsureCapacity((emxArray__common *) valley, n, sizeof(double));
    i = (int) unnamed_idx_0;
    for (n = 0; n < i; n++) {
        valley->data[n] = 0.0;
    }

    emxInit_int32_T(&iValley, 1);
    unnamed_idx_0 = (unsigned int) iFinite->size[0];
    n = iValley->size[0];
    iValley->size[0] = (int) unnamed_idx_0;
    emxEnsureCapacity((emxArray__common *) iValley, n, sizeof(int));
    i = (int) unnamed_idx_0;
    for (n = 0; n < i; n++) {
        iValley->data[n] = 0;
    }

    n = -1;
    i = 0;
    j = 0;
    k = 0;
    v = rtNaN;
    iv = 1;
    while (k + 1 <= iPeak->size[0]) {
        while (iInflect->data[i] != iFinite->data[j]) {
            v = yTemp[iInflect->data[i] - 1];
            iv = iInflect->data[i];
            if (rtIsNaN(yTemp[iInflect->data[i] - 1])) {
                n = -1;
            } else {
                while ((n + 1 > 0) && (valley->data[n] > v)) {
                    n--;
                }
            }

            i++;
        }

        p = yTemp[iInflect->data[i] - 1];
        while ((n + 1 > 0) && (peak->data[n] < p)) {
            if (valley->data[n] < v) {
                v = valley->data[n];
                iv = iValley->data[n];
            }

            n--;
        }

        isv = iv;
        while ((n + 1 > 0) && (peak->data[n] <= p)) {
            if (valley->data[n] < v) {
                v = valley->data[n];
                iv = iValley->data[n];
            }

            n--;
        }

        n++;
        peak->data[n] = yTemp[iInflect->data[i] - 1];
        valley->data[n] = v;
        iValley->data[n] = iv;
        if (iInflect->data[i] == iPeak->data[k]) {
            iBase->data[k] = iv;
            iSaddle->data[k] = isv;
            k++;
        }

        i++;
        j++;
    }

    emxFree_int32_T(&iValley);
    emxFree_real_T(&valley);
    emxFree_real_T(&peak);
}

//
// Arguments    : const double yTemp[492]
//                const emxArray_int32_T *iPk
//                const emxArray_int32_T *iFin
//                const emxArray_int32_T *iInflect
//                emxArray_real_T *peakBase
//                emxArray_int32_T *iLeftSaddle
//                emxArray_int32_T *iRightSaddle
// Return Type  : void
//
static void getPeakBase(const double yTemp[492], const emxArray_int32_T *iPk,
                        const emxArray_int32_T *iFin, const emxArray_int32_T *iInflect,
                        emxArray_real_T *peakBase, emxArray_int32_T *iLeftSaddle, emxArray_int32_T
                        *iRightSaddle) {
    emxArray_int32_T *iLeftBase;
    emxArray_int32_T *x;
    int md2;
    int m;
    int i;
    emxArray_int32_T *b_x;
    int xtmp;
    emxArray_int32_T *c_x;
    emxArray_int32_T *iRightBase;
    double extremum;
    emxInit_int32_T(&iLeftBase, 1);
    emxInit_int32_T(&x, 1);
    getLeftBase(yTemp, iPk, iFin, iInflect, iLeftBase, iLeftSaddle);
    md2 = x->size[0];
    x->size[0] = iPk->size[0];
    emxEnsureCapacity((emxArray__common *) x, md2, sizeof(int));
    m = iPk->size[0];
    for (md2 = 0; md2 < m; md2++) {
        x->data[md2] = iPk->data[md2];
    }

    m = iPk->size[0];
    md2 = iPk->size[0] >> 1;
    for (i = 1; i <= md2; i++) {
        xtmp = x->data[i - 1];
        x->data[i - 1] = x->data[m - i];
        x->data[m - i] = xtmp;
    }

    emxInit_int32_T(&b_x, 1);
    md2 = b_x->size[0];
    b_x->size[0] = iFin->size[0];
    emxEnsureCapacity((emxArray__common *) b_x, md2, sizeof(int));
    m = iFin->size[0];
    for (md2 = 0; md2 < m; md2++) {
        b_x->data[md2] = iFin->data[md2];
    }

    m = iFin->size[0];
    md2 = iFin->size[0] >> 1;
    for (i = 1; i <= md2; i++) {
        xtmp = b_x->data[i - 1];
        b_x->data[i - 1] = b_x->data[m - i];
        b_x->data[m - i] = xtmp;
    }

    emxInit_int32_T(&c_x, 1);
    md2 = c_x->size[0];
    c_x->size[0] = iInflect->size[0];
    emxEnsureCapacity((emxArray__common *) c_x, md2, sizeof(int));
    m = iInflect->size[0];
    for (md2 = 0; md2 < m; md2++) {
        c_x->data[md2] = iInflect->data[md2];
    }

    m = iInflect->size[0];
    md2 = iInflect->size[0] >> 1;
    for (i = 1; i <= md2; i++) {
        xtmp = c_x->data[i - 1];
        c_x->data[i - 1] = c_x->data[m - i];
        c_x->data[m - i] = xtmp;
    }

    emxInit_int32_T(&iRightBase, 1);
    getLeftBase(yTemp, x, b_x, c_x, iRightBase, iRightSaddle);
    m = iRightBase->size[0];
    md2 = iRightBase->size[0] >> 1;
    i = 1;
    emxFree_int32_T(&c_x);
    emxFree_int32_T(&b_x);
    emxFree_int32_T(&x);
    while (i <= md2) {
        xtmp = iRightBase->data[i - 1];
        iRightBase->data[i - 1] = iRightBase->data[m - i];
        iRightBase->data[m - i] = xtmp;
        i++;
    }

    m = iRightSaddle->size[0];
    md2 = iRightSaddle->size[0] >> 1;
    for (i = 1; i <= md2; i++) {
        xtmp = iRightSaddle->data[i - 1];
        iRightSaddle->data[i - 1] = iRightSaddle->data[m - i];
        iRightSaddle->data[m - i] = xtmp;
    }

    if (iLeftBase->size[0] <= iRightBase->size[0]) {
        i = iLeftBase->size[0];
    } else {
        i = iRightBase->size[0];
    }

    md2 = peakBase->size[0];
    peakBase->size[0] = i;
    emxEnsureCapacity((emxArray__common *) peakBase, md2, sizeof(double));
    for (m = 0; m + 1 <= i; m++) {
        if ((yTemp[iLeftBase->data[m] - 1] > yTemp[iRightBase->data[m] - 1]) ||
            rtIsNaN(yTemp[iRightBase->data[m] - 1])) {
            extremum = yTemp[iLeftBase->data[m] - 1];
        } else {
            extremum = yTemp[iRightBase->data[m] - 1];
        }

        peakBase->data[m] = extremum;
    }

    emxFree_int32_T(&iLeftBase);
    emxFree_int32_T(&iRightBase);
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
void get_hr_rr(double X[500], emxArray_real_T *Output, double *HR_mean, double *Respiratory_rate) {
    double y;
    int i;
    double d0;
    double b_y[518];
    double dv0[4];
    static const double dv1[4] = {0.601580928135908, -1.804742784407724,
                                  1.804742784407724, -0.601580928135908};

    double dv2[4];
    static const double dv3[4] = {1.0, -2.0037974773700169, 1.44705401948938,
                                  -0.361795928227867};

    double c_y[518];
    double a[3];
    static const double b_a[3] = {-0.60158092813590658, 1.2031618562718145,
                                  -0.60158092813590747};

    double d_y[506];
    double e_y[506];
    double dv4[2];
    double X3[500];
    double X4[492];
    int ix;
    static const double B[9] = {0.0, 0.146446609406726, 0.5, 0.853553390593274,
                                1.0, 0.853553390593274, 0.5, 0.146446609406726, 0.0};

    boolean_T exitg1;
    emxArray_real_T *Peaks;
    emxArray_real_T *Locations;
    emxArray_real_T *dist;

    //  1. Remove Mean:
    y = X[0];
    for (i = 0; i < 499; i++) {
        y += X[i + 1];
    }

    y /= 500.0;
    for (i = 0; i < 500; i++) {
        X[i] -= y;
    }

    //  2. Remove baseline drift (Butterworth, high pass: [b, a] = butter(3, 5*2/62.5, 'high');
    y = 2.0 * X[0];
    d0 = 2.0 * X[499];
    for (i = 0; i < 9; i++) {
        b_y[i] = y - X[9 - i];
    }

    memcpy(&b_y[9], &X[0], 500U * sizeof(double));
    for (i = 0; i < 9; i++) {
        b_y[i + 509] = d0 - X[498 - i];
    }

    for (i = 0; i < 4; i++) {
        dv0[i] = dv1[i];
        dv2[i] = dv3[i];
    }

    for (i = 0; i < 3; i++) {
        a[i] = b_a[i] * b_y[0];
    }

    memcpy(&c_y[0], &b_y[0], 518U * sizeof(double));
    filter(dv0, dv2, c_y, a, b_y);
    flipud(b_y);
    for (i = 0; i < 4; i++) {
        dv0[i] = dv1[i];
        dv2[i] = dv3[i];
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
    d0 = 2.0 * b_y[508];
    for (i = 0; i < 3; i++) {
        d_y[i] = y - b_y[12 - i];
    }

    memcpy(&d_y[3], &b_y[9], 500U * sizeof(double));
    for (i = 0; i < 3; i++) {
        d_y[i + 503] = d0 - b_y[507 - i];
    }

    for (i = 0; i < 2; i++) {
        dv4[i] = 7.8125 + -16.5625 * (double) i;
    }

    memcpy(&e_y[0], &d_y[0], 506U * sizeof(double));
    b_filter(dv4, e_y, -8.75 * d_y[0], d_y);
    b_flipud(d_y);
    for (i = 0; i < 2; i++) {
        dv4[i] = 7.8125 + -16.5625 * (double) i;
    }

    memcpy(&e_y[0], &d_y[0], 506U * sizeof(double));
    b_filter(dv4, e_y, -8.75 * d_y[0], d_y);
    b_flipud(d_y);

    //  X2 = X2/max(X2);
    //  4. Square to accentuate ecg waveformsS
    for (i = 0; i < 500; i++) {
        X3[i] = d_y[i + 3] * d_y[i + 3];
    }

    //  5. Convolution filtering to smooth peaks:
    //  conv_filter = ones(1, round(0.150*62.5)) / round(0.150*62.5);
    //  Custom: Use Hann Window as filter - better defined peaks.
    memset(&X4[0], 0, 492U * sizeof(double));
    for (i = 0; i < 9; i++) {
        for (ix = 0; ix < 492; ix++) {
            X4[ix] += B[i] * X3[(ix - i) + 8];
        }
    }

    // rescale_minmax
    //  Extract fiducial markers (peaks);
    i = 1;
    y = X4[0];
    if (rtIsNaN(X4[0])) {
        ix = 2;
        exitg1 = false;
        while ((!exitg1) && (ix < 493)) {
            i = ix;
            if (!rtIsNaN(X4[ix - 1])) {
                y = X4[ix - 1];
                exitg1 = true;
            } else {
                ix++;
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

    emxInit_real_T1(&Peaks, 1);
    emxInit_real_T1(&Locations, 1);
    findpeaks(X4, 0.3656836669 * y, Peaks, Locations);
    i = Output->size[0];
    Output->size[0] = Peaks->size[0] + Locations->size[0];
    emxEnsureCapacity((emxArray__common *) Output, i, sizeof(double));
    ix = Peaks->size[0];
    for (i = 0; i < ix; i++) {
        Output->data[i] = Peaks->data[i];
    }

    ix = Locations->size[0];
    for (i = 0; i < ix; i++) {
        Output->data[i + Peaks->size[0]] = Locations->data[i];
    }

    emxInit_real_T(&dist, 2);

    //  calculate distance between fiducial markers:
    i = dist->size[0] * dist->size[1];
    dist->size[0] = 1;
    dist->size[1] = Peaks->size[0] - 1;
    emxEnsureCapacity((emxArray__common *) dist, i, sizeof(double));
    ix = Peaks->size[0] - 1;
    emxFree_real_T(&Peaks);
    for (i = 0; i < ix; i++) {
        dist->data[i] = 0.0;
    }

    for (i = 0; i <= Locations->size[0] - 2; i++) {
        dist->data[i] = Locations->data[i + 1] - Locations->data[i];
    }

    emxFree_real_T(&Locations);
    if (dist->size[1] == 0) {
        y = 0.0;
    } else {
        y = dist->data[0];
        for (i = 2; i <= dist->size[1]; i++) {
            y += dist->data[i - 1];
        }
    }

    //  average in seconds:
    y = 60.0 / (y / (double) dist->size[1] / 62.5);

    //  TODO: Get RR:
    *HR_mean = y;
    *Respiratory_rate = 0.0;
    emxFree_real_T(&dist);
}

//
// Arguments    : void
// Return Type  : void
//
void get_hr_rr_initialize() {
    rt_InitInfAndNaN(8U);
}

//
// Arguments    : void
// Return Type  : void
//
void get_hr_rr_terminate() {
    // (no terminate code required)
}

//
// File trailer for get_hr_rr.cpp
//
// [EOF]
//
