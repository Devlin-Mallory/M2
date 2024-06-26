#ifndef _gmp_util_h_
#  define _gmp_util_h_

#  include "engine-includes.hpp"

/**
   Multiprecision arithmetic allocation utility routines
 */

#  if defined(__cplusplus)
extern "C" {
#  endif

inline void mpz_reallocate_limbs (mpz_ptr _z)
{ 
  int _s = _z->_mp_size;
  int _as = (_s>0)?_s:-_s;
  mp_limb_t *_p = (mp_limb_t*) getmem_atomic(_as*sizeof(mp_limb_t));
  memcpy(_p,_z->_mp_d,_as*sizeof(mp_limb_t));
  mpz_clear(_z);
  _z->_mp_d = _p;
  _z->_mp_size = _s;
  _z->_mp_alloc = _as;
}

  inline gmp_QQ moveTo_gmpQQ (mpq_ptr z)
  {
    mpz_reallocate_limbs(mpq_numref(z));
    mpz_reallocate_limbs(mpq_denref(z));
    return z;
  }

inline void mpfr_reallocate_limbs (mpfr_ptr _z)
{
  __mpfr_struct tmp;
  tmp = *_z;
  int limb_size = (_z->_mpfr_prec - 1) / GMP_NUMB_BITS + 1;
  mp_limb_t *p = (mp_limb_t*) getmem_atomic(limb_size * sizeof(mp_limb_t));
  memcpy(p, _z->_mpfr_d, limb_size * sizeof(mp_limb_t));
  mpfr_clear(_z);
  _z->_mpfr_prec = tmp._mpfr_prec;
  _z->_mpfr_sign = tmp._mpfr_sign;
  _z->_mpfr_exp = tmp._mpfr_exp;
  _z->_mpfr_d = p;
}
    
inline void mpfi_reallocate_limbs (mpfi_ptr _z)
{
    mpfr_reallocate_limbs(&(_z->left));
    mpfr_reallocate_limbs(&(_z->right));
}

  typedef struct {
    mpfr_srcptr re;
    mpfr_srcptr im;
  } CC_struct;

  typedef struct {
    mpfr_ptr re;
    mpfr_ptr im;
  } CCmutable_struct;

  //  typedef CCmutable_struct* gmp_CCmutable;
  //  typedef CC_struct* gmp_CC;

  inline mpfr_srcptr moveTo_gmpRR (mpfr_ptr _z)
  {
    mpfr_reallocate_limbs(_z);
    return _z;
  }
    
  inline mpfi_srcptr moveTo_gmpRRi (mpfi_ptr _z)
  {
    mpfr_reallocate_limbs(&(_z->left));
    mpfr_reallocate_limbs(&(_z->right));
    return _z;
  }
  
  inline gmp_CC moveTo_gmpCC (gmp_CCmutable _z)
  {
    CCmutable_struct* a = (CCmutable_struct*) _z;
    mpfr_reallocate_limbs(a->re);
    mpfr_reallocate_limbs(a->im);
    return (gmp_CC) a;
  }

#  if defined(__cplusplus)
  }
#  endif

#endif /* _gmp_util_h_ */

// Local Variables:
// indent-tabs-mode: nil
// End:
