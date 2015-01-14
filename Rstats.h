/* C++ library */
#include <vector>
#include <iostream>
#include <complex>
#include <cmath>
#include <map>
#include <limits>

/* Fix std::isnan problem in Windows */
#ifndef _isnan
#define _isnan isnan
#endif

/* Perl headers */
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include "ppport.h"

/* suppress error - Cent OS(symbol collisions) */
#undef init_tm
#undef do_open
#undef do_close
#ifdef ENTER
#undef ENTER
#endif

/* suppress error - Mac OS X(error: declaration of 'Perl___notused' has a different language linkage) */
#ifdef __cplusplus
#  define dNOOP (void)0
#else
#  define dNOOP extern int Perl___notused(void)
#endif

// Rstats header
namespace Rstats {

  REGEXP* pl_pregcomp (SV*, IV);
  SV* pl_new_ref(SV*);
  SV* pl_new_sv_sv(SV*);
  SV* pl_new_sv_pv(const char*);
  SV* pl_new_sv_iv(IV);
  SV* pl_new_sv_nv(NV);
  AV* pl_new_av();
  SV* pl_new_av_ref();
  HV* pl_new_hv();
  SV* pl_new_hv_ref();
  SV* pl_deref(SV*);
  AV* pl_av_deref(SV*);
  HV* pl_hv_deref(SV*);
  IV pl_av_len (AV*);
  IV pl_av_len (SV*);
  SV* pl_av_fetch(AV*, IV);
  SV* pl_av_fetch(SV*, IV);
  bool pl_hv_exists(HV*, char*);
  bool pl_hv_exists(SV*, char*);
  SV* pl_hv_delete(HV*, char*);
  SV* pl_hv_delete(SV*, char*);
  SV* pl_hv_fetch(HV*, const char*);
  SV* pl_hv_fetch(SV*, const char*);
  void pl_av_store(AV*, IV, SV*);
  void pl_av_store(SV*, IV, SV*);
  SV* pl_av_copy(SV*);
  void pl_hv_store(HV*, const char*, SV*);
  void pl_hv_store(SV*, const char* key, SV*);
  void pl_av_push(AV*, SV*);
  void pl_av_push(SV*, SV*);
  SV* pl_av_pop(AV*);
  SV* pl_av_pop(SV*);
  void pl_av_unshift(AV*, SV*);
  void pl_av_unshift(SV*, SV*);
  template <class X> X pl_to_c_obj(SV*);
  template <class X> SV* pl_to_perl_obj(X, const char*);
  IV pl_pregexec(SV*, REGEXP*);

  // Rstats::VectorType header
  namespace VectorType {
    enum Enum {
      LOGICAL = 0,
      INTEGER = 1 ,
      DOUBLE = 2,
      COMPLEX = 3,
      CHARACTER = 4
    };
  }
  
  // Rstats::Util header
  namespace Util {
    SV* looks_like_na(SV*);
    SV* looks_like_integer(SV*);
    SV* looks_like_double(SV*);
    SV* looks_like_logical(SV*);
    SV* looks_like_complex(SV*);
    IV is_perl_number(SV*);
  }

  // Rstats::ElementFunc header
  namespace ElementFunc {

    std::complex<NV> add(std::complex<NV>, std::complex<NV>);
    NV add(NV, NV);
    IV add(IV, IV);

    std::complex<NV> subtract(std::complex<NV>, std::complex<NV>);
    NV subtract(NV, NV);
    IV subtract(IV, IV);

    std::complex<NV> multiply(std::complex<NV>, std::complex<NV>);
    NV multiply(NV, NV);
    IV multiply(IV, IV);

    std::complex<NV> divide(std::complex<NV>, std::complex<NV>);
    NV divide(NV, NV);
    NV divide(IV, IV);

    std::complex<NV> pow(std::complex<NV>, std::complex<NV>);
    NV pow(NV, NV);
    NV pow(IV, IV);

    std::complex<NV> reminder(std::complex<NV>, std::complex<NV>);
    NV reminder(NV, NV);
    IV reminder(IV, IV);

    NV Re(std::complex<NV>);
    NV Re(NV);
    NV Re(IV);

    NV Im(std::complex<NV>);
    NV Im(NV);
    NV Im(IV);

    std::complex<NV> Conj(std::complex<NV>);
    NV Conj(NV);
    NV Conj(IV);

    std::complex<NV> sin(std::complex<NV>);
    NV sin(NV);
    NV sin(IV);
    
    std::complex<NV> cos(std::complex<NV>);
    NV cos(NV);
    NV cos(IV);

    std::complex<NV> tan(std::complex<NV>);
    NV tan(NV);
    NV tan(IV);

    std::complex<NV> sinh(std::complex<NV>);
    NV sinh(NV);
    NV sinh(IV);

    std::complex<NV> cosh(std::complex<NV>);
    NV cosh(NV);
    NV cosh(IV);

    std::complex<NV> tanh (std::complex<NV> z);
    NV tanh(NV);
    NV tanh(IV);

    NV abs(std::complex<NV>);
    NV abs(NV);
    NV abs(IV);

    NV Mod(std::complex<NV>);
    NV Mod(NV);
    NV Mod(IV);

    std::complex<NV> log(std::complex<NV>);
    NV log(NV);
    NV log(IV);

    std::complex<NV> logb(std::complex<NV>);
    NV logb(NV);
    NV logb(IV);

    std::complex<NV> log10(std::complex<NV>);
    NV log10(NV);
    NV log10(IV);

    std::complex<NV> log2(std::complex<NV>);
    NV log2(NV);
    NV log2(IV);
    
    // expm1 (Can't separate body. I don't know the reason)
    std::complex<NV> expm1(std::complex<NV> e1) { croak("Error in expm1 : unimplemented complex function"); }
    NV expm1(NV e1) { return ::expm1(e1); }
    NV expm1(IV e1) { return expm1((NV)e1); }

    NV Arg(std::complex<NV>);
    NV Arg(NV);
    NV Arg(IV);

    std::complex<NV> exp(std::complex<NV>);
    NV exp(NV);
    NV exp(IV);

    std::complex<NV> sqrt(std::complex<NV>);
    NV sqrt(NV);
    NV sqrt(IV);

    std::complex<NV> atan(std::complex<NV>);
    NV atan(NV);
    NV atan(IV);

    std::complex<NV> asin(std::complex<NV>);
    NV asin(NV);
    NV asin(IV);

    std::complex<NV> acos(std::complex<NV>);
    NV acos(NV);
    NV acos(IV);

    std::complex<NV> asinh(std::complex<NV>);
    NV asinh(NV);
    NV asinh(IV);

    std::complex<NV> acosh(std::complex<NV>);
    NV acosh(NV);
    NV acosh(IV);

    std::complex<NV> atanh(std::complex<NV>);
    NV atanh(NV);
    NV atanh(IV);
    
    std::complex<NV> negation(std::complex<NV>);
    NV negation(NV);
    IV negation(IV);

    std::complex<NV> atan2(std::complex<NV>, std::complex<NV>);
    NV atan2(NV, NV);
    NV atan2(IV, IV);

    IV And(SV*, SV*);
    IV And(std::complex<NV>, std::complex<NV>);
    IV And(NV, NV);
    IV And(IV, IV);

    IV Or(SV*, SV*);
    IV Or(std::complex<NV>, std::complex<NV>);
    IV Or(NV, NV);
    IV Or(IV, IV);
    
    IV equal(SV*, SV*);
    IV equal(std::complex<NV>, std::complex<NV>);
    IV equal(NV, NV);
    IV equal(IV, IV);

    IV not_equal(SV*, SV*);
    IV not_equal(std::complex<NV>, std::complex<NV>);
    IV not_equal(NV, NV);
    IV not_equal(IV, IV);

    IV more_than(SV*, SV*);
    IV more_than(std::complex<NV>, std::complex<NV>);
    IV more_than(NV, NV);
    IV more_than(IV, IV);

    IV less_than(SV*, SV*);
    IV less_than(std::complex<NV>, std::complex<NV>);
    IV less_than(NV, NV);
    IV less_than(IV, IV);

    IV more_than_or_equal(SV*, SV*);
    IV more_than_or_equal(std::complex<NV>, std::complex<NV>);
    IV more_than_or_equal(NV, NV);
    IV more_than_or_equal(IV, IV);

    IV less_than_or_equal(SV*, SV*);
    IV less_than_or_equal(std::complex<NV>, std::complex<NV>);
    IV less_than_or_equal(NV, NV);
    IV less_than_or_equal(IV, IV);

    IV is_infinite(SV*);
    IV is_infinite(std::complex<NV>);
    IV is_infinite(NV);
    IV is_infinite(IV);

    IV is_finite(SV*);
    IV is_finite(std::complex<NV>);
    IV is_finite(NV);
    IV is_finite(IV);

    IV is_nan(SV*);
    IV is_nan(std::complex<NV>);
    IV is_nan(NV);
    IV is_nan(IV);
  }
}

// Rstats body
  REGEXP* Rstats::pl_pregcomp (SV* sv_re, IV flag) {
    return (REGEXP*)sv_2mortal((SV*)pregcomp(sv_re, flag));
  }
  
  SV* Rstats::pl_new_ref(SV* sv) {
    return sv_2mortal(newRV_inc(sv));
  }

  SV* Rstats::pl_new_sv_sv(SV* sv) {
    return sv_2mortal(newSVsv(sv));
  }

  SV* Rstats::pl_new_sv_pv(const char* pv) {
    return sv_2mortal(newSVpvn(pv, strlen(pv)));
  }
      
  SV* Rstats::pl_new_sv_iv(IV iv) {
    return sv_2mortal(newSViv(iv));
  }
  
  SV* Rstats::pl_new_sv_nv(NV nv) {
    return sv_2mortal(newSVnv(nv));
  }
  
  AV* Rstats::pl_new_av() {
    return (AV*)sv_2mortal((SV*)newAV());
  }
  
  SV* Rstats::pl_new_av_ref() {
    return sv_2mortal(newRV_inc((SV*)pl_new_av()));
  }
  
  HV* Rstats::pl_new_hv() {
    return (HV*)sv_2mortal((SV*)newHV());
  }

  SV* Rstats::pl_new_hv_ref() {
    return sv_2mortal(newRV_inc((SV*)pl_new_hv()));
  }

  SV* Rstats::pl_deref(SV* ref) {
    if (SvROK(ref)) {
      return SvRV(ref);
    }
    else {
      croak("Can't derefernce");
    }
  }

  AV* Rstats::pl_av_deref(SV* ref) {
    return (AV*)pl_deref(ref);
  }

  HV* Rstats::pl_hv_deref(SV* ref) {
    return (HV*)pl_deref(ref);
  }
  
  IV Rstats::pl_av_len (AV* av) {
    return av_len(av) + 1;
  }

  IV Rstats::pl_av_len (SV* av_ref) {
    return av_len((AV*)pl_deref(av_ref)) + 1;
  }
  
  SV* Rstats::pl_av_fetch(AV* av, IV pos) {
    SV** const element_ptr = av_fetch(av, pos, FALSE);
    SV* const element = element_ptr ? *element_ptr : &PL_sv_undef;
    
    return element;
  }
  
  SV* Rstats::pl_av_fetch(SV* av_ref, IV pos) {
    AV* av = (AV*)pl_deref(av_ref);
    return pl_av_fetch(av, pos);
  }
  
  bool Rstats::pl_hv_exists(HV* hv_hash, char* key) {
    return hv_exists(hv_hash, key, strlen(key));
  }

  bool Rstats::pl_hv_exists(SV* sv_hash_ref, char* key) {
    return hv_exists(pl_hv_deref(sv_hash_ref), key, strlen(key));
  }

  SV* Rstats::pl_hv_delete(HV* hv_hash, char* key) {
    return hv_delete(hv_hash, key, strlen(key), 0);
  }
  
  SV* Rstats::pl_hv_delete(SV* sv_hash_ref, char* key) {
    return hv_delete(pl_hv_deref(sv_hash_ref), key, strlen(key), 0);
  }
  
  SV* Rstats::pl_hv_fetch(HV* hv, const char* key) {
    SV** const element_ptr = hv_fetch(hv, key, strlen(key), FALSE);
    SV* const element = element_ptr ? *element_ptr : &PL_sv_undef;
    
    return element;
  }

  SV* Rstats::pl_hv_fetch(SV* hv_ref, const char* key) {
    HV* hv = pl_hv_deref(hv_ref);
    return pl_hv_fetch(hv, key);
  }
  
  void Rstats::pl_av_store(AV* av, IV pos, SV* element) {
    av_store(av, pos, SvREFCNT_inc(element));
  }
  
  void Rstats::pl_av_store(SV* av_ref, IV pos, SV* element) {
    AV* av = pl_av_deref(av_ref);
    pl_av_store(av, pos, element);
  }

  SV* Rstats::pl_av_copy(SV* sv_av_ref) {
    SV* sv_new_av_ref = pl_new_av_ref();
    
    for (IV i = 0; i < pl_av_len(sv_av_ref); i++) {
      pl_av_store(sv_new_av_ref, i, pl_new_sv_sv(pl_av_fetch(sv_av_ref, i)));
    }
    
    return sv_new_av_ref;
  }
  
  void Rstats::pl_hv_store(HV* hv, const char* key, SV* element) {
    hv_store(hv, key, strlen(key), SvREFCNT_inc(element), FALSE);
  }

  void Rstats::pl_hv_store(SV* hv_ref, const char* key, SV* element) {
    HV* hv = pl_hv_deref(hv_ref);
    return pl_hv_store(hv, key, element);
  }
  
  void Rstats::pl_av_push(AV* av, SV* sv) {
    av_push(av, SvREFCNT_inc(sv));
  }
  
  void Rstats::pl_av_push(SV* av_ref, SV* sv) {
    return pl_av_push(pl_av_deref(av_ref), sv);
  }

  SV* Rstats::pl_av_pop(AV* av_array) {
    return av_pop(av_array);
  }

  SV* Rstats::pl_av_pop(SV* sv_array_ref) {
    return av_pop(pl_av_deref(sv_array_ref));
  }

  void Rstats::pl_av_unshift(AV* av, SV* sv) {
    av_unshift(av, 1);
    pl_av_store(av, (IV)0, SvREFCNT_inc(sv));
  }
  
  void Rstats::pl_av_unshift(SV* av_ref, SV* sv) {
    av_unshift((AV*)pl_deref(av_ref), 1);
    pl_av_store((AV*)pl_deref(av_ref), 0, SvREFCNT_inc(sv));
  }

  template <class X> X Rstats::pl_to_c_obj(SV* perl_obj_ref) {
    SV* perl_obj = SvROK(perl_obj_ref) ? SvRV(perl_obj_ref) : perl_obj_ref;
    IV obj_addr = SvIV(perl_obj);
    X c_obj = INT2PTR(X, obj_addr);
    
    return c_obj;
  }

  template <class X> SV* Rstats::pl_to_perl_obj(X c_obj, const char* class_name) {
    IV obj_addr = PTR2IV(c_obj);
    SV* sv_obj_addr = pl_new_sv_iv(obj_addr);
    SV* sv_obj_addr_ref = pl_new_ref(sv_obj_addr);
    SV* perl_obj = sv_bless(sv_obj_addr_ref, gv_stashpv(class_name, 1));
    
    return perl_obj;
  }

  IV Rstats::pl_pregexec(SV* sv_str, REGEXP* sv_re) {
    char* str = SvPV_nolen(sv_str);
    
    IV ret = pregexec(
      sv_re,
      str,
      str + strlen(str),
      str,
      0,
      sv_str,
      1
    );
    
    return ret;
  }

// Rstats::ElementFunc body
  // add
  std::complex<NV> Rstats::ElementFunc::add(std::complex<NV> e1, std::complex<NV> e2) { return e1 + e2; }
  NV Rstats::ElementFunc::add(NV e1, NV e2) { return e1 + e2; }
  IV Rstats::ElementFunc::add(IV e1, IV e2) { return e1 + e2; }

  // subtract
  std::complex<NV> Rstats::ElementFunc::subtract(std::complex<NV> e1, std::complex<NV> e2) { return e1 - e2; }
  NV Rstats::ElementFunc::subtract(NV e1, NV e2) { return e1 - e2; }
  IV Rstats::ElementFunc::subtract(IV e1, IV e2) { return e1 - e2; }

  // multiply
  std::complex<NV> Rstats::ElementFunc::multiply(std::complex<NV> e1, std::complex<NV> e2) { return e1 * e2; }
  NV Rstats::ElementFunc::multiply(NV e1, NV e2) { return e1 * e2; }
  IV Rstats::ElementFunc::multiply(IV e1, IV e2) { return e1 * e2; }

  // divide
  std::complex<NV> Rstats::ElementFunc::divide(std::complex<NV> e1, std::complex<NV> e2) { return e1 / e2; }
  NV Rstats::ElementFunc::divide(NV e1, NV e2) { return e1 / e2; }
  NV Rstats::ElementFunc::divide(IV e1, IV e2) { return e1 / e2; }

  // pow
  std::complex<NV> Rstats::ElementFunc::pow(std::complex<NV> e1, std::complex<NV> e2) { return std::pow(e1, e2); }
  NV Rstats::ElementFunc::pow(NV e1, NV e2) { return ::pow(e1, e2); }
  NV Rstats::ElementFunc::pow(IV e1, IV e2) { return pow((NV)e1, (NV)e2); }

  // reminder
  std::complex<NV> Rstats::ElementFunc::reminder(std::complex<NV> e1, std::complex<NV> e2) {
    croak("unimplemented complex operation(Rstats::VectorFunc::reminder())");
  }
  NV Rstats::ElementFunc::reminder(NV e1, NV e2) {
    if (std::isnan(e1) || std::isnan(e2) || e2 == 0) {
      return std::numeric_limits<NV>::signaling_NaN();
    }
    else {
      return e1 - std::floor(e1 / e2) * e2;
    }
  }
  IV Rstats::ElementFunc::reminder(IV e1, IV e2) {
    if (e2 == 0) {
      throw "0 divide exception\n";
    }
    return e1 % e2;
  }

  // Re
  NV Rstats::ElementFunc::Re(std::complex<NV> e1) { return e1.real(); }
  NV Rstats::ElementFunc::Re(NV e1) { return e1; }
  NV Rstats::ElementFunc::Re(IV e1) { return e1; }

  // Im
  NV Rstats::ElementFunc::Im(std::complex<NV> e1) { return e1.imag(); }
  NV Rstats::ElementFunc::Im(NV e1) { return 0; }
  NV Rstats::ElementFunc::Im(IV e1) { return 0; }

  // Conj
  std::complex<NV> Rstats::ElementFunc::Conj(std::complex<NV> e1) { return std::complex<NV>(e1.real(), -e1.imag()); }
  NV Rstats::ElementFunc::Conj(NV e1) { return e1; }
  NV Rstats::ElementFunc::Conj(IV e1) { return e1; }

  // sin
  std::complex<NV> Rstats::ElementFunc::sin(std::complex<NV> e1) { return std::sin(e1); }
  NV Rstats::ElementFunc::sin(NV e1) { return std::sin(e1); }
  NV Rstats::ElementFunc::sin(IV e1) { return sin((NV)e1); }
  
  // cos
  std::complex<NV> Rstats::ElementFunc::cos(std::complex<NV> e1) { return std::cos(e1); }
  NV Rstats::ElementFunc::cos(NV e1) { return std::cos(e1); }
  NV Rstats::ElementFunc::cos(IV e1) { return cos((NV)e1); }

  // tan
  std::complex<NV> Rstats::ElementFunc::tan(std::complex<NV> e1) { return std::tan(e1); }
  NV Rstats::ElementFunc::tan(NV e1) { return std::tan(e1); }
  NV Rstats::ElementFunc::tan(IV e1) { return tan((NV)e1); }

  // sinh
  std::complex<NV> Rstats::ElementFunc::sinh(std::complex<NV> e1) { return std::sinh(e1); }
  NV Rstats::ElementFunc::sinh(NV e1) { return std::sinh(e1); }
  NV Rstats::ElementFunc::sinh(IV e1) { return sinh((NV)e1); }

  // cosh
  std::complex<NV> Rstats::ElementFunc::cosh(std::complex<NV> e1) { return std::cosh(e1); }
  NV Rstats::ElementFunc::cosh(NV e1) { return std::cosh(e1); }
  NV Rstats::ElementFunc::cosh(IV e1) { return cosh((NV)e1); }

  // tanh
  std::complex<NV> Rstats::ElementFunc::tanh (std::complex<NV> z) {
    NV re = z.real();
    
    // For fix FreeBSD bug
    // FreeBAD return (NaN + NaNi) when real value is negative infinite
    if (std::isinf(re) && re < 0) {
      return std::complex<NV>(-1, 0);
    }
    else {
      return std::tanh(z);
    }
  }
  NV Rstats::ElementFunc::tanh(NV e1) { return std::tanh(e1); }
  NV Rstats::ElementFunc::tanh(IV e1) { return tanh((NV)e1); }

  // abs
  NV Rstats::ElementFunc::abs(std::complex<NV> e1) { return std::abs(e1); }
  NV Rstats::ElementFunc::abs(NV e1) { return std::abs(e1); }
  NV Rstats::ElementFunc::abs(IV e1) { return abs((NV)e1); }

  // abs
  NV Rstats::ElementFunc::Mod(std::complex<NV> e1) { return abs(e1); }
  NV Rstats::ElementFunc::Mod(NV e1) { return abs(e1); }
  NV Rstats::ElementFunc::Mod(IV e1) { return abs((NV)e1); }

  // log
  std::complex<NV> Rstats::ElementFunc::log(std::complex<NV> e1) { return std::log(e1); }
  NV Rstats::ElementFunc::log(NV e1) { return std::log(e1); }
  NV Rstats::ElementFunc::log(IV e1) { return log((NV)e1); }

  // logb
  std::complex<NV> Rstats::ElementFunc::logb(std::complex<NV> e1) { return log(e1); }
  NV Rstats::ElementFunc::logb(NV e1) { return log(e1); }
  NV Rstats::ElementFunc::logb(IV e1) { return log((NV)e1); }

  // log10
  std::complex<NV> Rstats::ElementFunc::log10(std::complex<NV> e1) { return std::log10(e1); }
  NV Rstats::ElementFunc::log10(NV e1) { return std::log10(e1); }
  NV Rstats::ElementFunc::log10(IV e1) { return std::log10((NV)e1); }

  // log2
  std::complex<NV> Rstats::ElementFunc::log2(std::complex<NV> e1) {
    return std::log(e1) / std::log(std::complex<NV>(2, 0));
  }
  NV Rstats::ElementFunc::log2(NV e1) {
    return std::log(e1) / std::log(2);
  }
  NV Rstats::ElementFunc::log2(IV e1) { return log2((NV)e1); }
  
  // Arg
  NV Rstats::ElementFunc::Arg(std::complex<NV> e1) {
    NV re = e1.real();
    NV im = e1.imag();
    
    if (re == 0 && im == 0) {
      return 0;
    }
    else {
      return ::atan2(im, re);
    }
  }
  NV Rstats::ElementFunc::Arg(NV e1) { croak("Error in Arg : unimplemented double function"); }
  NV Rstats::ElementFunc::Arg(IV e1) { return Arg((NV)e1); }

  // exp
  std::complex<NV> Rstats::ElementFunc::exp(std::complex<NV> e1) { return std::exp(e1); }
  NV Rstats::ElementFunc::exp(NV e1) { return std::exp(e1); }
  NV Rstats::ElementFunc::exp(IV e1) { return exp((NV)e1); }

  // sqrt
  std::complex<NV> Rstats::ElementFunc::sqrt(std::complex<NV> e1) {
    // Fix bug that clang sqrt can't right value of perfect squeres
    if (e1.imag() == 0 && e1.real() < 0) {
      return std::complex<NV>(0, std::sqrt(-e1.real()));
    }
    else {
      return std::sqrt(e1);
    }
  }
  NV Rstats::ElementFunc::sqrt(NV e1) { return std::sqrt(e1); }
  NV Rstats::ElementFunc::sqrt(IV e1) { return sqrt((NV)e1); }

  // atan
  std::complex<NV> Rstats::ElementFunc::atan(std::complex<NV> e1) {
    if (e1 == std::complex<NV>(0, 0)) {
      return std::complex<NV>(0, 0);
    }
    else if (e1 == std::complex<NV>(0, 1)) {
      return std::complex<NV>(0, INFINITY);
    }
    else if (e1 == std::complex<NV>(0, -1)) {
      return std::complex<NV>(0, -INFINITY);
    }
    else {  
      std::complex<NV> e2_i = std::complex<NV>(0, 1);
      std::complex<NV> e2_log = std::log((e2_i + e1) / (e2_i - e1));
      return (e2_i / std::complex<NV>(2, 0)) * e2_log;
    }
  }
  NV Rstats::ElementFunc::atan(NV e1) { return ::atan2(e1, 1); }
  NV Rstats::ElementFunc::atan(IV e1) { return atan2((NV)e1, (NV)1); }

  // asin
  std::complex<NV> Rstats::ElementFunc::asin(std::complex<NV> e1) {
    NV e1_re = e1.real();
    NV e1_im = e1.imag();
    
    if (e1_re == 0 && e1_im == 0) {
      return std::complex<NV>(0, 0);
    }
    else {
      NV e2_t1 = std::sqrt(
        ((e1_re + 1) * (e1_re + 1))
        +
        (e1_im * e1_im)
      );
      NV e2_t2 = std::sqrt(
        ((e1_re - 1) * (e1_re - 1))
        +
        (e1_im * e1_im)
      );
      
      NV e2_alpha = (e2_t1 + e2_t2) / 2;
      NV e2_beta  = (e2_t1 - e2_t2) / 2;
      
      if (e2_alpha < 1) {
        e2_alpha = 1;
      }
      
      if (e2_beta > 1) {
        e2_beta = 1;
      }
      else if (e2_beta < -1) {
        e2_beta = -1;
      }
      
      NV e2_u = ::atan2(
        e2_beta,
        std::sqrt(1 - (e2_beta * e2_beta))
      );
      
      NV e2_v = -std::log(
        e2_alpha
        +
        std::sqrt((e2_alpha * e2_alpha) - 1)
      );
      
      if (e1_im > 0 || ((e1_im == 0) && (e1_re < -1))) {
        e2_v = -e2_v;
      }
      
      return std::complex<NV>(e2_u, e2_v);
    }
  }
  NV Rstats::ElementFunc::asin(NV e1) { return std::asin(e1); }
  NV Rstats::ElementFunc::asin(IV e1) { return asin((NV)e1); }

  // acos
  std::complex<NV> Rstats::ElementFunc::acos(std::complex<NV> e1) {
    NV e1_re = e1.real();
    NV e1_im = e1.imag();
    
    if (e1_re == 1 && e1_im == 0) {
      return std::complex<NV>(0, 0);
    }
    else {
      NV e2_t1 = std::sqrt(
        ((e1_re + 1) * (e1_re + 1))
        +
        (e1_im * e1_im)
      );
      NV e2_t2 = std::sqrt(
        ((e1_re - 1) * (e1_re - 1))
        +
        (e1_im * e1_im)
      );
      
      NV e2_alpha = (e2_t1 + e2_t2) / 2;
      NV e2_beta  = (e2_t1 - e2_t2) / 2;
      
      if (e2_alpha < 1) {
        e2_alpha = 1;
      }
      
      if (e2_beta > 1) {
        e2_beta = 1;
      }
      else if (e2_beta < -1) {
        e2_beta = -1;
      }
      
      NV e2_u = ::atan2(
        std::sqrt(1 - (e2_beta * e2_beta)),
        e2_beta
      );
      
      NV e2_v = std::log(
        e2_alpha
        +
        std::sqrt((e2_alpha * e2_alpha) - 1)
      );
      
      if (e1_im > 0 || (e1_im == 0 && e1_re < -1)) {
        e2_v = -e2_v;
      }
      
      return std::complex<NV>(e2_u, e2_v);
    }
  }
  NV Rstats::ElementFunc::acos(NV e1) { return std::acos(e1); }
  NV Rstats::ElementFunc::acos(IV e1) { return acos((NV)e1); }

  // asinh
  std::complex<NV> Rstats::ElementFunc::asinh(std::complex<NV> e1) {
    std::complex<NV> e2_t = (
      std::sqrt((e1 * e1) + std::complex<NV>(1, 0))
      +
      e1
    );
    
    return std::log(e2_t);
  }
  NV Rstats::ElementFunc::asinh(NV e1) {
    NV e2_t = (
      e1
      +
      std::sqrt((e1 * e1) + 1)
    );
    
    return std::log(e2_t);
  }
  NV Rstats::ElementFunc::asinh(IV e1) { return asinh((NV)e1); }

  // acosh
  std::complex<NV> Rstats::ElementFunc::acosh(std::complex<NV> e1) {
    NV e1_re = e1.real();
    NV e1_im = e1.imag();

    std::complex<NV> e2_t = (
      std::sqrt(
        (e1 * e1)
        -
        std::complex<NV>(1, 0)
      )
      +
      e1
    );
    std::complex<NV> e2_u = std::log(e2_t);
    NV e2_re = e2_u.real();
    NV e2_im = e2_u.imag();
    
    std::complex<NV> e2;
    if (e1_re < 0 && e1_im == 0) {
      e2 = std::complex<NV>(e2_re, -e2_im);
    }
    else {
      e2 = std::complex<NV>(e2_re, e2_im);
    }
    
    if (e1_re < 0) {
      return -e2;
    }
    else {
      return e2;
    }
  }
  NV Rstats::ElementFunc::acosh(NV e1) {
    if (e1 >= 1) {
      if (std::isinf(e1)) {
        warn("In acosh() : NaNs produced");
        return std::numeric_limits<NV>::signaling_NaN();
      }
      else {
        return std::log(
          e1
          +
          std::sqrt((e1 * e1) - 1)
        );
      }
    }
    else {
      warn("In acosh() : NaNs produced");
      return std::numeric_limits<NV>::signaling_NaN();
    }
  }
  NV Rstats::ElementFunc::acosh(IV e1) { return acosh((NV)e1); }

  // atanh
  std::complex<NV> Rstats::ElementFunc::atanh(std::complex<NV> e1) {
    if (e1 == std::complex<NV>(1, 0)) {
      warn("In atanh() : NaNs produced");
      return std::complex<NV>(INFINITY, std::numeric_limits<NV>::signaling_NaN());
    }
    else if (e1 == std::complex<NV>(-1, 0)) {
      warn("In atanh() : NaNs produced");
      return std::complex<NV>(-INFINITY, std::numeric_limits<NV>::signaling_NaN());
    }
    else {
      return std::complex<NV>(0.5, 0)
        *
        std::log(
          (std::complex<NV>(1, 0) + e1)
          /
          (std::complex<NV>(1, 0) - e1)
        );
    }
  }
  NV Rstats::ElementFunc::atanh(NV e1) {
    if (std::isinf(e1)) {
      warn("In acosh() : NaNs produced");
      return std::numeric_limits<NV>::signaling_NaN();
    }
    else {
      if (e1 == 1) {
        return INFINITY;
      }
      else if (e1 == -1) {
        return -INFINITY;
      }
      else if (std::abs(e1) < 1) {
        return std::log((1 + e1) / (1 - e1)) / 2;
      }
      else {
        warn("In acosh() : NaNs produced");
        return std::numeric_limits<NV>::signaling_NaN();
      }
    }
  }
  NV Rstats::ElementFunc::atanh(IV e1) { return atanh((NV)e1); }
  
  // negation
  std::complex<NV> Rstats::ElementFunc::negation(std::complex<NV> e1) { return -e1; }
  NV Rstats::ElementFunc::negation(NV e1) { return -e1; }
  IV Rstats::ElementFunc::negation(IV e1) { return -e1; }

  // atan2
  std::complex<NV> Rstats::ElementFunc::atan2(std::complex<NV> e1, std::complex<NV> e2) {
    std::complex<NV> e3_s = (e1 * e1) + (e2 * e2);
    if (e3_s == std::complex<NV>(0, 0)) {
      return std::complex<NV>(0, 0);
    }
    else {
      std::complex<NV> e3_i = std::complex<NV>(0, 1);
      std::complex<NV> e3_r = e2 + (e1 * e3_i);
      return -e3_i * std::log(e3_r / std::sqrt(e3_s));
    }
  }
  NV Rstats::ElementFunc::atan2(NV e1, NV e2) { ::atan2(e1, e2); }
  NV Rstats::ElementFunc::atan2(IV e1, IV e2) { return atan2((NV)e1, (NV)e2); }

  // And
  IV Rstats::ElementFunc::And(SV* e1, SV* e2) { croak("operations are possible only for numeric, logical or complex types"); }
  IV Rstats::ElementFunc::And(std::complex<NV> e1, std::complex<NV> e2) {
    if (e1 != std::complex<NV>(0, 0) && e2 != std::complex<NV>(0, 0)) { return 1; }
    else { return 0; }
  }
  IV Rstats::ElementFunc::And(NV e1, NV e2) {
    if (std::isnan(e1) || std::isnan(e2)) { throw "Na exception"; }
    else { return e1 && e2 ? 1 : 0; }
  }
  IV Rstats::ElementFunc::And(IV e1, IV e2) { return e1 && e2 ? 1 : 0; }

  // Or
  IV Rstats::ElementFunc::Or(SV* e1, SV* e2) { croak("operations are possible only for numeric, logical or complex types"); }
  IV Rstats::ElementFunc::Or(std::complex<NV> e1, std::complex<NV> e2) {
    if (e1 != std::complex<NV>(0, 0) || e2 != std::complex<NV>(0, 0)) { return 1; }
    else { return 0; }
  }
  IV Rstats::ElementFunc::Or(NV e1, NV e2) {
    if (std::isnan(e1) || std::isnan(e2)) { throw "Na exception"; }
    else { return e1 || e2 ? 1 : 0; }
  }
  IV Rstats::ElementFunc::Or(IV e1, IV e2) { return e1 || e2 ? 1 : 0; }
  
  // equal
  IV Rstats::ElementFunc::equal(SV* e1, SV* e2) { return sv_cmp(e1, e2) == 0 ? 1 : 0; }
  IV Rstats::ElementFunc::equal(std::complex<NV> e1, std::complex<NV> e2) { return e1 == e2 ? 1 : 0; }
  IV Rstats::ElementFunc::equal(NV e1, NV e2) {
    if (std::isnan(e1) || std::isnan(e2)) { throw "Can't compare NaN"; }
    else { return e1 == e2 ? 1 : 0; }
  }
  IV Rstats::ElementFunc::equal(IV e1, IV e2) { return e1 == e2 ? 1 : 0; }

  // not equal
  IV Rstats::ElementFunc::not_equal(SV* e1, SV* e2) { return sv_cmp(e1, e2) != 0 ? 1 : 0; }
  IV Rstats::ElementFunc::not_equal(std::complex<NV> e1, std::complex<NV> e2) { return e1 != e2 ? 1 : 0; }
  IV Rstats::ElementFunc::not_equal(NV e1, NV e2) {
    if (std::isnan(e1) || std::isnan(e2)) { throw "Can't compare NaN"; }
    else { return e1 != e2 ? 1 : 0; }
  }
  IV Rstats::ElementFunc::not_equal(IV e1, IV e2) { return e1 != e2 ? 1 : 0; }

  // more_than
  IV Rstats::ElementFunc::more_than(SV* e1, SV* e2) { return sv_cmp(e1, e2) > 0 ? 1 : 0; }
  IV Rstats::ElementFunc::more_than(std::complex<NV> e1, std::complex<NV> e2) {
    croak("invalid comparison with complex values(more_than())");
  }
  IV Rstats::ElementFunc::more_than(NV e1, NV e2) {
    if (std::isnan(e1) || std::isnan(e2)) { throw "Can't compare NaN"; }
    else { return e1 > e2 ? 1 : 0; }
  }
  IV Rstats::ElementFunc::more_than(IV e1, IV e2) { return e1 > e2 ? 1 : 0; }

  // less_than
  IV Rstats::ElementFunc::less_than(SV* e1, SV* e2) { return sv_cmp(e1, e2) < 0 ? 1 : 0; }
  IV Rstats::ElementFunc::less_than(std::complex<NV> e1, std::complex<NV> e2) {
    croak("invalid comparison with complex values(less_than())");
  }
  IV Rstats::ElementFunc::less_than(NV e1, NV e2) {
    if (std::isnan(e1) || std::isnan(e2)) { throw "Can't compare NaN"; }
    else { return e1 < e2 ? 1 : 0; }
  }
  IV Rstats::ElementFunc::less_than(IV e1, IV e2) { return e1 < e2 ? 1 : 0; }

  // more_than_or_equal
  IV Rstats::ElementFunc::more_than_or_equal(SV* e1, SV* e2) { return sv_cmp(e1, e2) >= 0 ? 1 : 0; }
  IV Rstats::ElementFunc::more_than_or_equal(std::complex<NV> e1, std::complex<NV> e2) {
    croak("invalid comparison with complex values(more_than_or_equal())");
  }
  IV Rstats::ElementFunc::more_than_or_equal(NV e1, NV e2) {
    if (std::isnan(e1) || std::isnan(e2)) { throw "Can't compare NaN"; }
    else { return e1 >= e2 ? 1 : 0; }
  }
  IV Rstats::ElementFunc::more_than_or_equal(IV e1, IV e2) { return e1 >= e2 ? 1 : 0; }

  // less_than_or_equal
  IV Rstats::ElementFunc::less_than_or_equal(SV* e1, SV* e2) { return sv_cmp(e1, e2) <= 0 ? 1 : 0; }
  IV Rstats::ElementFunc::less_than_or_equal(std::complex<NV> e1, std::complex<NV> e2) {
    croak("invalid comparison with complex values(less_than_or_equal())");
  }
  IV Rstats::ElementFunc::less_than_or_equal(NV e1, NV e2) {
    if (std::isnan(e1) || std::isnan(e2)) { throw "Can't compare NaN"; }
    else { return e1 <= e2 ? 1 : 0; }
  }
  IV Rstats::ElementFunc::less_than_or_equal(IV e1, IV e2) { return e1 <= e2 ? 1 : 0; }

  // is_infinite
  IV Rstats::ElementFunc::is_infinite(SV* e1) { return 0; }
  IV Rstats::ElementFunc::is_infinite(std::complex<NV> e1) {
    if (std::isnan(e1.real()) || std::isnan(e1.imag())) {
      return 0;
    }
    else if (std::isinf(e1.real()) || std::isinf(e1.imag())) {
      return 1;
    }
    else {
      return 0;
    }
  }
  IV Rstats::ElementFunc::is_infinite(NV e1) { return std::isinf(e1); }
  IV Rstats::ElementFunc::is_infinite(IV e1) { return 0; }

  // is_finite
  IV Rstats::ElementFunc::is_finite(SV* e1) { return 0; }
  IV Rstats::ElementFunc::is_finite(std::complex<NV> e1) {
    if (std::isfinite(e1.real()) && std::isfinite(e1.imag())) {
      return 1;
    }
    else {
      return 0;
    }
  }
  IV Rstats::ElementFunc::is_finite(NV e1) { return std::isfinite(e1) ? 1 : 0; }
  IV Rstats::ElementFunc::is_finite(IV e1) { return 1; }

  // is_nan
  IV Rstats::ElementFunc::is_nan(SV* e1) { return 0; }
  IV Rstats::ElementFunc::is_nan(std::complex<NV> e1) {
    if (std::isnan(e1.real()) && std::isnan(e1.imag())) {
      return 1;
    }
    else {
      return 0;
    }
  }
  IV Rstats::ElementFunc::is_nan(NV e1) { return std::isnan(e1) ? 1 : 0; }
  IV Rstats::ElementFunc::is_nan(IV e1) { return 1; }

namespace Rstats {
  // Macro for Rstats::Vector
# define RSTATS_DEF_VECTOR_FUNC_UN_IS(FUNC_NAME, ELEMENT_FUNC_NAME) \
    Rstats::Vector* FUNC_NAME(Rstats::Vector* e1) { \
      IV length = e1->get_length(); \
      Rstats::Vector* e2 = Rstats::Vector::new_logical(length); \
      Rstats::VectorType::Enum type = e1->get_type(); \
      switch (type) { \
        case Rstats::VectorType::CHARACTER : \
          for (IV i = 0; i < length; i++) { \
            e2->set_integer_value(i, ELEMENT_FUNC_NAME(e1->get_character_value(i))); \
          } \
          break; \
        case Rstats::VectorType::COMPLEX : \
          for (IV i = 0; i < length; i++) { \
            e2->set_integer_value(i, ELEMENT_FUNC_NAME(e1->get_complex_value(i))); \
          } \
          break; \
        case Rstats::VectorType::DOUBLE : \
          for (IV i = 0; i < length; i++) { \
            e2->set_integer_value(i, ELEMENT_FUNC_NAME(e1->get_double_value(i))); \
          } \
          break; \
        case Rstats::VectorType::INTEGER : \
        case Rstats::VectorType::LOGICAL : \
          for (IV i = 0; i < length; i++) { \
            e2->set_integer_value(i, ELEMENT_FUNC_NAME(e1->get_integer_value(i))); \
          } \
          break; \
        default: \
          croak("Error in %s() : invalid argument to %s()", #FUNC_NAME, #FUNC_NAME); \
          break; \
      } \
      for (IV i = 0; i < length; i++) { \
        if (e1->exists_na_position(i)) { \
          e2->set_integer_value(i, 0); \
        } \
      } \
      return e2; \
    }

# define RSTATS_DEF_VECTOR_FUNC_UN_MATH(FUNC_NAME, ELEMENT_FUNC_NAME) \
    Rstats::Vector* FUNC_NAME(Rstats::Vector* e1) { \
      IV length = e1->get_length(); \
      Rstats::Vector* e2; \
      Rstats::VectorType::Enum type = e1->get_type(); \
      switch (type) { \
        case Rstats::VectorType::COMPLEX : \
          e2 = Rstats::Vector::new_complex(length); \
          for (IV i = 0; i < length; i++) { \
            e2->set_complex_value(i, ELEMENT_FUNC_NAME(e1->get_complex_value(i))); \
          } \
          break; \
        case Rstats::VectorType::DOUBLE : \
          e2 = Rstats::Vector::new_double(length); \
          for (IV i = 0; i < length; i++) { \
            e2->set_double_value(i, ELEMENT_FUNC_NAME(e1->get_double_value(i))); \
          } \
          break; \
        case Rstats::VectorType::INTEGER : \
        case Rstats::VectorType::LOGICAL : \
          e2 = Rstats::Vector::new_integer(length); \
          for (IV i = 0; i < length; i++) { \
            e2->set_integer_value(i, ELEMENT_FUNC_NAME(e1->get_integer_value(i))); \
          } \
          break; \
        default: \
          croak("Error in %s() : invalid argument to %s()", #FUNC_NAME, #FUNC_NAME); \
          break; \
      } \
      e2->merge_na_positions(e1); \
      return e2; \
    }
    
# define RSTATS_DEF_VECTOR_FUNC_UN_MATH_INTEGER_TO_DOUBLE(FUNC_NAME, ELEMENT_FUNC_NAME) \
    Rstats::Vector* FUNC_NAME(Rstats::Vector* e1) { \
      IV length = e1->get_length(); \
      Rstats::Vector* e2; \
      Rstats::VectorType::Enum type = e1->get_type(); \
      switch (type) { \
        case Rstats::VectorType::COMPLEX : \
          e2 = Rstats::Vector::new_complex(length); \
          for (IV i = 0; i < length; i++) { \
            e2->set_complex_value(i, ELEMENT_FUNC_NAME(e1->get_complex_value(i))); \
          } \
          break; \
        case Rstats::VectorType::DOUBLE : \
          e2 = Rstats::Vector::new_double(length); \
          for (IV i = 0; i < length; i++) { \
            e2->set_double_value(i, ELEMENT_FUNC_NAME(e1->get_double_value(i))); \
          } \
          break; \
        case Rstats::VectorType::INTEGER : \
        case Rstats::VectorType::LOGICAL : \
          e2 = Rstats::Vector::new_double(length); \
          for (IV i = 0; i < length; i++) { \
            e2->set_double_value(i, ELEMENT_FUNC_NAME(e1->get_integer_value(i))); \
          } \
          break; \
        default: \
          croak("Error in %s() : non-numeric argument to Rstats::Vector::%s", #FUNC_NAME, #FUNC_NAME); \
          break; \
      } \
      e2->merge_na_positions(e1); \
      return e2; \
    }

# define RSTATS_DEF_VECTOR_FUNC_UN_MATH_COMPLEX_INTEGER_TO_DOUBLE(FUNC_NAME, ELEMENT_FUNC_NAME) \
    Rstats::Vector* FUNC_NAME(Rstats::Vector* e1) { \
      IV length = e1->get_length(); \
      Rstats::Vector* e2; \
      Rstats::VectorType::Enum type = e1->get_type(); \
      switch (type) { \
        case Rstats::VectorType::COMPLEX : \
          e2 = Rstats::Vector::new_double(length); \
          for (IV i = 0; i < length; i++) { \
            e2->set_double_value(i, ELEMENT_FUNC_NAME(e1->get_complex_value(i))); \
          } \
          break; \
        case Rstats::VectorType::DOUBLE : \
          e2 = Rstats::Vector::new_double(length); \
          for (IV i = 0; i < length; i++) { \
            e2->set_double_value(i, ELEMENT_FUNC_NAME(e1->get_double_value(i))); \
          } \
          break; \
        case Rstats::VectorType::INTEGER : \
        case Rstats::VectorType::LOGICAL : \
          e2 = Rstats::Vector::new_double(length); \
          for (IV i = 0; i < length; i++) { \
            e2->set_double_value(i, ELEMENT_FUNC_NAME(e1->get_integer_value(i))); \
          } \
          break; \
        default: \
          croak("Error in %s() : non-numeric argument to Rstats::Vector::%s", #FUNC_NAME, #FUNC_NAME); \
          break; \
      } \
      e2->merge_na_positions(e1); \
      return e2; \
    }

# define RSTATS_DEF_VECTOR_FUNC_BIN_TO_LOGICAL(FUNC_NAME, ELEMENT_FUNC_NAME) \
    Rstats::Vector* FUNC_NAME(Rstats::Vector* e1, Rstats::Vector* e2) { \
      if (e1->get_type() != e2->get_type()) { \
        croak("Can't add different type(Rstats::VectorFunc::%s())", #FUNC_NAME); \
      } \
      if (e1->get_length() != e2->get_length()) { \
        croak("Can't add different length(Rstats::VectorFunc::%s())", #FUNC_NAME); \
      } \
      IV length = e1->get_length(); \
      Rstats::Vector* e3 = Rstats::Vector::new_logical(length); \
      Rstats::VectorType::Enum type = e1->get_type(); \
      switch (type) { \
        case Rstats::VectorType::CHARACTER : \
          for (IV i = 0; i < length; i++) { \
            e3->set_integer_value(i, ELEMENT_FUNC_NAME(e1->get_character_value(i), e2->get_character_value(i)) ? 1 : 0); \
          } \
          break; \
        case Rstats::VectorType::COMPLEX : \
          for (IV i = 0; i < length; i++) { \
            e3->set_integer_value(i, ELEMENT_FUNC_NAME(e1->get_complex_value(i), e2->get_complex_value(i)) ? 1 : 0); \
          } \
          break; \
        case Rstats::VectorType::DOUBLE : \
          for (IV i = 0; i < length; i++) { \
            try {\
              e3->set_integer_value(i, ELEMENT_FUNC_NAME(e1->get_double_value(i), e2->get_double_value(i)) ? 1 : 0); \
            } catch (const char* e) {\
              e3->add_na_position(i);\
            }\
          } \
          break; \
        case Rstats::VectorType::INTEGER : \
        case Rstats::VectorType::LOGICAL : \
          for (IV i = 0; i < length; i++) { \
            try {\
              e3->set_integer_value(i, ELEMENT_FUNC_NAME(e1->get_integer_value(i), e2->get_integer_value(i)) ? 1 : 0); \
            }\
            catch (const char* e) {\
              e3->add_na_position(i);\
            }\
          } \
          break; \
        default: \
          croak("Error in %s() : non-comparable argument to %s()", #FUNC_NAME, #FUNC_NAME); \
      } \
      e3->merge_na_positions(e1); \
      e3->merge_na_positions(e2); \
      return e3; \
    }
    
# define RSTATS_DEF_VECTOR_FUNC_BIN_MATH(FUNC_NAME, ELEMENT_FUNC_NAME) \
    Rstats::Vector* FUNC_NAME(Rstats::Vector* e1, Rstats::Vector* e2) { \
      if (e1->get_type() != e2->get_type()) { \
        croak("Can't add different type(Rstats::VectorFunc::%s())", #FUNC_NAME); \
      } \
      if (e1->get_length() != e2->get_length()) { \
        croak("Can't add different length(Rstats::VectorFunc::%s())", #FUNC_NAME); \
      } \
      IV length = e1->get_length(); \
      Rstats::Vector* e3; \
      Rstats::VectorType::Enum type = e1->get_type(); \
      switch (type) { \
        case Rstats::VectorType::COMPLEX : \
          e3 = Rstats::Vector::new_complex(length); \
          for (IV i = 0; i < length; i++) { \
            e3->set_complex_value(i, ELEMENT_FUNC_NAME(e1->get_complex_value(i), e2->get_complex_value(i))); \
          } \
          break; \
        case Rstats::VectorType::DOUBLE : \
          e3 = Rstats::Vector::new_double(length); \
          for (IV i = 0; i < length; i++) { \
            e3->set_double_value(i, ELEMENT_FUNC_NAME(e1->get_double_value(i), e2->get_double_value(i))); \
          } \
          break; \
        case Rstats::VectorType::INTEGER : \
        case Rstats::VectorType::LOGICAL : \
          e3 = Rstats::Vector::new_integer(length); \
          for (IV i = 0; i < length; i++) { \
            try {\
              e3->set_integer_value(i, ELEMENT_FUNC_NAME(e1->get_integer_value(i), e2->get_integer_value(i))); \
            }\
            catch (const char* e) {\
              e3->add_na_position(i);\
            }\
          } \
          break; \
        default: \
          croak("Error in %s() : non-numeric argument to %s()", #FUNC_NAME, #FUNC_NAME); \
      } \
      e3->merge_na_positions(e1); \
      e3->merge_na_positions(e2); \
      return e3; \
    }

# define RSTATS_DEF_VECTOR_FUNC_BIN_MATH_INTEGER_TO_DOUBLE(FUNC_NAME, ELEMENT_FUNC_NAME) \
    Rstats::Vector* FUNC_NAME(Rstats::Vector* e1, Rstats::Vector* e2) { \
      if (e1->get_type() != e2->get_type()) { \
        croak("Can't add different type(Rstats::VectorFunc::%s())", #FUNC_NAME); \
      } \
      if (e1->get_length() != e2->get_length()) { \
        croak("Can't add different length(Rstats::VectorFunc::%s())", #FUNC_NAME); \
      } \
      IV length = e1->get_length(); \
      Rstats::Vector* e3; \
      Rstats::VectorType::Enum type = e1->get_type(); \
      switch (type) { \
        case Rstats::VectorType::COMPLEX : \
          e3 = Rstats::Vector::new_complex(length); \
          for (IV i = 0; i < length; i++) { \
            e3->set_complex_value(i, ELEMENT_FUNC_NAME(e1->get_complex_value(i), e2->get_complex_value(i))); \
          } \
          break; \
        case Rstats::VectorType::DOUBLE : \
          e3 = Rstats::Vector::new_double(length); \
          for (IV i = 0; i < length; i++) { \
            e3->set_double_value(i, ELEMENT_FUNC_NAME(e1->get_double_value(i), e2->get_double_value(i))); \
          } \
          break; \
        case Rstats::VectorType::INTEGER : \
        case Rstats::VectorType::LOGICAL : \
          e3 = Rstats::Vector::new_double(length); \
          for (IV i = 0; i < length; i++) { \
            e3->set_double_value(i, ELEMENT_FUNC_NAME(e1->get_integer_value(i), e2->get_integer_value(i))); \
          } \
          break; \
        default: \
          croak("Error in %s() : non-numeric argument to %s()", #FUNC_NAME, #FUNC_NAME); \
      } \
      e3->merge_na_positions(e1); \
      e3->merge_na_positions(e2); \
      return e3; \
    }
  
  // Rstats::Vector header
  class Vector {
    private:
    Rstats::VectorType::Enum type;
    std::map<IV, IV> na_positions;
    void* values;
    
    public:

    ~Vector ();
    
    SV* get_value(IV);
    SV* get_values();
    
    bool is_character ();
    bool is_complex ();
    bool is_double ();
    bool is_integer ();
    bool is_numeric ();
    bool is_logical ();
    
    std::vector<SV*>* get_character_values();
    std::vector<std::complex<NV> >* get_complex_values();
    std::vector<NV>* get_double_values();
    std::vector<IV>* get_integer_values();
    
    Rstats::VectorType::Enum get_type();
    void add_na_position(IV);
    bool exists_na_position(IV position);
    void merge_na_positions(Rstats::Vector* elements);
    std::map<IV, IV> get_na_positions();
    IV get_length ();
    
    static Rstats::Vector* new_character(IV, SV*);
    static Rstats::Vector* new_character(IV);
    SV* get_character_value(IV);
    void set_character_value(IV, SV*);
    static Rstats::Vector* new_complex(IV);
    static Rstats::Vector* new_complex(IV, std::complex<NV>);
    std::complex<NV> get_complex_value(IV);
    void set_complex_value(IV, std::complex<NV>);
    static Rstats::Vector* new_double(IV);
    static Rstats::Vector* new_double(IV, NV);
    NV get_double_value(IV);
    void set_double_value(IV, NV);

    static Rstats::Vector* new_integer(IV);
    static Rstats::Vector* new_integer(IV, IV);
    
    IV get_integer_value(IV);
    void set_integer_value(IV, IV);
    
    static Rstats::Vector* new_logical(IV);
    static Rstats::Vector* new_logical(IV, IV);
    static Rstats::Vector* new_true();
    static Rstats::Vector* new_false();
    static Rstats::Vector* new_nan();
    static Rstats::Vector* new_negative_inf();
    static Rstats::Vector* new_inf();
    static Rstats::Vector* new_na();
    static Rstats::Vector* new_null();
    
    Rstats::Vector* as (SV*);
    SV* to_string_pos(IV);
    SV* to_string();
    Rstats::Vector* as_character();
    Rstats::Vector* as_double();
    Rstats::Vector* as_numeric();
    Rstats::Vector* as_integer();
    Rstats::Vector* as_complex();
    Rstats::Vector* as_logical();
  };
}

// Rstats::Vector body
  Rstats::Vector::~Vector () {
    IV length = this->get_length();
    
    Rstats::VectorType::Enum type = this->get_type();
    switch (type) {
      case Rstats::VectorType::CHARACTER : {
        std::vector<SV*>* values = this->get_character_values();
        for (IV i = 0; i < length; i++) {
          if ((*values)[i] != NULL) {
            SvREFCNT_dec((*values)[i]);
          }
        }
        delete values;
        break;
      }
      case Rstats::VectorType::COMPLEX : {
        std::vector<std::complex<NV> >* values = this->get_complex_values();
        delete values;
        break;
      }
      case Rstats::VectorType::DOUBLE : {
        std::vector<NV>* values = this->get_double_values();
        delete values;
        break;
      }
      case Rstats::VectorType::INTEGER :
      case Rstats::VectorType::LOGICAL : {
        std::vector<IV>* values = this->get_integer_values();
        delete values;
      }
    }
  }
  
  SV* Rstats::Vector::get_value(IV pos) {

    SV* sv_value;
    
    Rstats::VectorType::Enum type = this->get_type();
    switch (type) {
      case Rstats::VectorType::CHARACTER :
        if (this->exists_na_position(pos)) {
          sv_value = &PL_sv_undef;
        }
        else {
          sv_value = this->get_character_value(pos);
        }
        break;
      case Rstats::VectorType::COMPLEX :
        if (this->exists_na_position(pos)) {
          sv_value = &PL_sv_undef;
        }
        else {
          std::complex<NV> z = this->get_complex_value(pos);
          
          NV re = z.real();
          SV* sv_re;
          if (std::isnan(re)) {
            sv_re = Rstats::pl_new_sv_pv("NaN");
          }
          else if (std::isinf(re) && re > 0) {
            sv_re = Rstats::pl_new_sv_pv("Inf");
          }
          else if (std::isinf(re) && re < 0) {
            sv_re = Rstats::pl_new_sv_pv("-Inf");
          }
          else {
            sv_re = Rstats::pl_new_sv_nv(re);
          }
          
          NV im = z.imag();
          SV* sv_im;
          if (std::isnan(im)) {
            sv_im = Rstats::pl_new_sv_pv("NaN");
          }
          else if (std::isinf(im) && im > 0) {
            sv_im = Rstats::pl_new_sv_pv("Inf");
          }
          else if (std::isinf(im) && im < 0) {
            sv_im = Rstats::pl_new_sv_pv("-Inf");
          }
          else {
            sv_im = Rstats::pl_new_sv_nv(im);
          }

          sv_value = Rstats::pl_new_hv_ref();
          Rstats::pl_hv_store(sv_value, "re", sv_re);
          Rstats::pl_hv_store(sv_value, "im", sv_im);
        }
        break;
      case Rstats::VectorType::DOUBLE :
        if (this->exists_na_position(pos)) {
          sv_value = &PL_sv_undef;
        }
        else {
          NV value = this->get_double_value(pos);
          if (std::isnan(value)) {
            sv_value = Rstats::pl_new_sv_pv("NaN");
          }
          else if (std::isinf(value) && value > 0) {
            sv_value = Rstats::pl_new_sv_pv("Inf");
          }
          else if (std::isinf(value) && value < 0) {
            sv_value = Rstats::pl_new_sv_pv("-Inf");
          }
          else {
            sv_value = Rstats::pl_new_sv_nv(value);
          }
        }
        break;
      case Rstats::VectorType::INTEGER :
      case Rstats::VectorType::LOGICAL :
        if (this->exists_na_position(pos)) {
          sv_value = &PL_sv_undef;
        }
        else {
          IV value = this->get_integer_value(pos);
          sv_value = Rstats::pl_new_sv_iv(value);
        }
        break;
      default:
        sv_value = &PL_sv_undef;
    }
    
    return sv_value;
  }

  SV* Rstats::Vector::get_values() {
    
    IV length = this->get_length();
    SV* sv_values = Rstats::pl_new_av_ref();
    for (IV i = 0; i < length; i++) {
      Rstats::pl_av_push(sv_values, this->get_value(i));
    }
    
    return sv_values;
  }

  bool Rstats::Vector::is_character () {
    return this->get_type() == Rstats::VectorType::CHARACTER;
  }

  bool Rstats::Vector::is_complex () {
    return this->get_type() == Rstats::VectorType::COMPLEX;
  }

  bool Rstats::Vector::is_double () {
    return this->get_type() == Rstats::VectorType::DOUBLE;
  }

  bool Rstats::Vector::is_integer () {
    return this->get_type() == Rstats::VectorType::INTEGER;
  }

  bool Rstats::Vector::is_numeric () {
    return this->get_type() == Rstats::VectorType::DOUBLE || this->get_type() == Rstats::VectorType::INTEGER;
  }

  bool Rstats::Vector::is_logical () {
    return this->get_type() == Rstats::VectorType::LOGICAL;
  }

  std::vector<SV*>* Rstats::Vector::get_character_values() {
    return (std::vector<SV*>*)this->values;
  }
  
  std::vector<std::complex<NV> >* Rstats::Vector::get_complex_values() {
    return (std::vector<std::complex<NV> >*)this->values;
  }
  
  std::vector<NV>* Rstats::Vector::get_double_values() {
    return (std::vector<NV>*)this->values;
  }
  
  std::vector<IV>* Rstats::Vector::get_integer_values() {
    return (std::vector<IV>*)this->values;
  }
  
  Rstats::VectorType::Enum Rstats::Vector::get_type() {
    return this->type;
  }

  void Rstats::Vector::add_na_position(IV position) {
    this->na_positions[position] = 1;
  }

  bool Rstats::Vector::exists_na_position(IV position) {
    return this->na_positions.count(position);
  }
  
  void Rstats::Vector::merge_na_positions(Rstats::Vector* elements) {
    for(std::map<IV, IV>::iterator it = elements->na_positions.begin(); it != elements->na_positions.end(); ++it) {
      this->add_na_position(it->first);
    }
  }
  
  std::map<IV, IV> Rstats::Vector::get_na_positions() {
    return this->na_positions;
  }

  IV Rstats::Vector::get_length () {
    if (this->values == NULL) {
      return 0;
    }
    
    switch (type) {
      case Rstats::VectorType::CHARACTER :
        return this->get_character_values()->size();
        break;
      case Rstats::VectorType::COMPLEX :
        return this->get_complex_values()->size();
        break;
      case Rstats::VectorType::DOUBLE :
        return this->get_double_values()->size();
        break;
      case Rstats::VectorType::INTEGER :
      case Rstats::VectorType::LOGICAL :
        return this->get_integer_values()->size();
        break;
    }
  }

  Rstats::Vector* Rstats::Vector::new_character(IV length, SV* sv_str) {

    Rstats::Vector* elements = Rstats::Vector::new_character(length);
    for (IV i = 0; i < length; i++) {
      elements->set_character_value(i, sv_str);
    }
    elements->type = Rstats::VectorType::CHARACTER;
    
    return elements;
  }

  Rstats::Vector* Rstats::Vector::new_character(IV length) {

    Rstats::Vector* elements = new Rstats::Vector;
    elements->values = new std::vector<SV*>(length);
    elements->type = Rstats::VectorType::CHARACTER;
    
    return elements;
  }

  SV* Rstats::Vector::get_character_value(IV pos) {
    SV* value = (*this->get_character_values())[pos];
    if (value == NULL) {
      return NULL;
    }
    else {
      return Rstats::pl_new_sv_sv(value);
    }
  }
  
  void Rstats::Vector::set_character_value(IV pos, SV* value) {
    if (value != NULL) {
      SvREFCNT_dec((*this->get_character_values())[pos]);
    }
    
    SV* new_value = Rstats::pl_new_sv_sv(value);
    (*this->get_character_values())[pos] = SvREFCNT_inc(new_value);
  }

  Rstats::Vector* Rstats::Vector::new_complex(IV length) {
    
    Rstats::Vector* elements = new Rstats::Vector;
    elements->values = new std::vector<std::complex<NV> >(length, std::complex<NV>(0, 0));
    elements->type = Rstats::VectorType::COMPLEX;
    
    return elements;
  }
      
  Rstats::Vector* Rstats::Vector::new_complex(IV length, std::complex<NV> z) {
    
    Rstats::Vector* elements = new Rstats::Vector;
    elements->values = new std::vector<std::complex<NV> >(length, z);
    elements->type = Rstats::VectorType::COMPLEX;
    
    return elements;
  }

  std::complex<NV> Rstats::Vector::get_complex_value(IV pos) {
    return (*this->get_complex_values())[pos];
  }
  
  void Rstats::Vector::set_complex_value(IV pos, std::complex<NV> value) {
    (*this->get_complex_values())[pos] = value;
  }
  
  Rstats::Vector* Rstats::Vector::new_double(IV length) {
    Rstats::Vector* elements = new Rstats::Vector;
    elements->values = new std::vector<NV>(length);
    elements->type = Rstats::VectorType::DOUBLE;
    
    return elements;
  }

  Rstats::Vector* Rstats::Vector::new_double(IV length, NV value) {
    Rstats::Vector* elements = new Rstats::Vector;
    elements->values = new std::vector<NV>(length, value);
    elements->type = Rstats::VectorType::DOUBLE;
    
    return elements;
  }
  
  NV Rstats::Vector::get_double_value(IV pos) {
    return (*this->get_double_values())[pos];
  }
  
  void Rstats::Vector::set_double_value(IV pos, NV value) {
    (*this->get_double_values())[pos] = value;
  }

  Rstats::Vector* Rstats::Vector::new_integer(IV length) {
    
    Rstats::Vector* elements = new Rstats::Vector;
    elements->values = new std::vector<IV>(length);
    elements->type = Rstats::VectorType::INTEGER;
    
    return elements;
  }

  Rstats::Vector* Rstats::Vector::new_integer(IV length, IV value) {
    
    Rstats::Vector* elements = new Rstats::Vector;
    elements->values = new std::vector<IV>(length, value);
    elements->type = Rstats::VectorType::INTEGER;
    
    return elements;
  }

  IV Rstats::Vector::get_integer_value(IV pos) {
    return (*this->get_integer_values())[pos];
  }
  
  void Rstats::Vector::set_integer_value(IV pos, IV value) {
    (*this->get_integer_values())[pos] = value;
  }
  
  Rstats::Vector* Rstats::Vector::new_logical(IV length) {
    Rstats::Vector* elements = new Rstats::Vector;
    elements->values = new std::vector<IV>(length);
    elements->type = Rstats::VectorType::LOGICAL;
    
    return elements;
  }

  Rstats::Vector* Rstats::Vector::new_logical(IV length, IV value) {
    Rstats::Vector* elements = new Rstats::Vector;
    elements->values = new std::vector<IV>(length, value);
    elements->type = Rstats::VectorType::LOGICAL;
    
    return elements;
  }
  
  Rstats::Vector* Rstats::Vector::new_true() {
    return new_logical(1, 1);
  }

  Rstats::Vector* Rstats::Vector::new_false() {
    return new_logical(1, 0);
  }
  
  Rstats::Vector* Rstats::Vector::new_nan() {
    return  Rstats::Vector::new_double(1, NAN);
  }

  Rstats::Vector* Rstats::Vector::new_negative_inf() {
    return Rstats::Vector::new_double(1, -(INFINITY));
  }
  
  Rstats::Vector* Rstats::Vector::new_inf() {
    return Rstats::Vector::new_double(1, INFINITY);
  }
  
  Rstats::Vector* Rstats::Vector::new_na() {
    Rstats::Vector* elements = new Rstats::Vector;
    elements->values = new std::vector<IV>(1, 0);
    elements->type = Rstats::VectorType::LOGICAL;
    elements->add_na_position(0);
    
    return elements;
  }
  
  Rstats::Vector* Rstats::Vector::new_null() {
    Rstats::Vector* elements = new Rstats::Vector;
    elements->values = NULL;
    elements->type = Rstats::VectorType::LOGICAL;
    return elements;
  }

  Rstats::Vector* Rstats::Vector::as (SV* sv_type) {
    Rstats::Vector* e2;
    if (SvOK(sv_type)) {
      char* type = SvPV_nolen(sv_type);
      if (strEQ(type, "character")) {
        e2 = this->as_character();
      }
      else if (strEQ(type, "complex")) {
        e2 = this->as_complex();
      }
      else if (strEQ(type, "double")) {
        e2 = this->as_double();
      }
      else if (strEQ(type, "numeric")) {
        e2 = this->as_numeric();
      }
      else if (strEQ(type, "integer")) {
        e2 = this->as_integer();
      }
      else if (strEQ(type, "logical")) {
        e2 = this->as_logical();
      }
      else {
        croak("Invalid mode is passed(Rstats::Vector::as())");
      }
    }
    else {
      croak("Invalid mode is passed(Rstats::Vector::as())");
    }
    
    return e2;
  }
  
  SV* Rstats::Vector::to_string_pos(IV pos) {
    Rstats::VectorType::Enum type = this->get_type();
    SV* sv_str;
    if (this->exists_na_position(pos)) {
      sv_str = Rstats::pl_new_sv_pv("NA");
    }
    else {
      switch (type) {
        case Rstats::VectorType::CHARACTER :
          sv_str = this->get_character_value(pos);
          break;
        case Rstats::VectorType::COMPLEX : {
          std::complex<NV> z = this->get_complex_value(pos);
          NV re = z.real();
          NV im = z.imag();
          
          sv_str = Rstats::pl_new_sv_pv("");
         if (std::isinf(re) && re > 0) {
            sv_catpv(sv_str, "Inf");
          }
          else if (std::isinf(re) && re < 0) {
            sv_catpv(sv_str, "-Inf");
          }
          else if (std::isnan(re)) {
            sv_catpv(sv_str, "NaN");
          }
          else {
            sv_catpv(sv_str, SvPV_nolen(Rstats::pl_new_sv_nv(re)));
          }

          if (std::isinf(im) && im > 0) {
            sv_catpv(sv_str, "+Inf");
          }
          else if (std::isinf(im) && im < 0) {
            sv_catpv(sv_str, "-Inf");
          }
          else if (std::isnan(im)) {
            sv_catpv(sv_str, "+NaN");
          }
          else {
            if (im >= 0) {
              sv_catpv(sv_str, "+");
            }
            sv_catpv(sv_str, SvPV_nolen(Rstats::pl_new_sv_nv(im)));
          }
          
          sv_catpv(sv_str, "i");
          break;
        }
        case Rstats::VectorType::DOUBLE : {
          NV value = this->get_double_value(pos);
          if (std::isinf(value) && value > 0) {
            sv_str = Rstats::pl_new_sv_pv("Inf");
          }
          else if (std::isinf(value) && value < 0) {
            sv_str = Rstats::pl_new_sv_pv("-Inf");
          }
          else if (std::isnan(value)) {
            sv_str = Rstats::pl_new_sv_pv("NaN");
          }
          else {
            sv_str = Rstats::pl_new_sv_nv(value);
            sv_catpv(sv_str, "");
          }
          break;
        }
        case Rstats::VectorType::INTEGER :
          sv_str = Rstats::pl_new_sv_iv(this->get_integer_value(pos));
          sv_catpv(sv_str, "");
          break;
        case Rstats::VectorType::LOGICAL :
          sv_str = this->get_integer_value(pos)
            ? Rstats::pl_new_sv_pv("TRUE") : Rstats::pl_new_sv_pv("FALSE");
          break;
        default:
          croak("Invalid type");
      }
    }
    
    return sv_str;
  }
  
  SV* Rstats::Vector::to_string() {
    
    SV* sv_strs = Rstats::pl_new_av_ref();
    for (IV i = 0; i < this->get_length(); i++) {
      SV* sv_str = this->to_string_pos(i);
      Rstats::pl_av_push(sv_strs, sv_str);
    }

    SV* sv_str_all = Rstats::pl_new_sv_pv("");
    IV sv_strs_length = Rstats::pl_av_len(sv_strs);
    for (IV i = 0; i < sv_strs_length; i++) {
      SV* sv_str = Rstats::pl_av_fetch(sv_strs, i);
      sv_catpv(sv_str_all, SvPV_nolen(sv_str));
      if (i != sv_strs_length - 1) {
        sv_catpv(sv_str_all, ",");
      }
    }
    
    return sv_str_all;
  }
  
  Rstats::Vector* Rstats::Vector::as_character () {
    IV length = this->get_length();
    Rstats::Vector* e2 = new_character(length);
    Rstats::VectorType::Enum type = this->get_type();
    switch (type) {
      case Rstats::VectorType::CHARACTER :
        for (IV i = 0; i < length; i++) {
          SV* sv_value = this->get_character_value(i);
          e2->set_character_value(i, sv_value);
        }
        break;
      case Rstats::VectorType::COMPLEX :
        for (IV i = 0; i < length; i++) {
          std::complex<NV> z = this->get_complex_value(i);
          NV re = z.real();
          NV im = z.imag();
          
          SV* sv_re = Rstats::pl_new_sv_nv(re);
          SV* sv_im = Rstats::pl_new_sv_nv(im);
          SV* sv_str = Rstats::pl_new_sv_pv("");
          
          sv_catpv(sv_str, SvPV_nolen(sv_re));
          if (im >= 0) {
            sv_catpv(sv_str, "+");
          }
          sv_catpv(sv_str, SvPV_nolen(sv_im));
          sv_catpv(sv_str, "i");

          e2->set_character_value(i, sv_str);
        }
        break;
      case Rstats::VectorType::DOUBLE :
        for (IV i = 0; i < length; i++) {
          NV value = this->get_double_value(i);
          SV* sv_str = Rstats::pl_new_sv_pv("");
          if (std::isinf(value) && value > 0) {
            sv_catpv(sv_str, "Inf");
          }
          else if (std::isinf(value) && value < 0) {
            sv_catpv(sv_str, "-Inf");
          }
          else if (std::isnan(value)) {
            sv_catpv(sv_str, "NaN");
          }
          else {
            sv_catpv(sv_str, SvPV_nolen(Rstats::pl_new_sv_nv(value)));
          }
          e2->set_character_value(i, sv_str);
        }
        break;
      case Rstats::VectorType::INTEGER :
        for (IV i = 0; i < length; i++) {
          e2->set_character_value(
            i,
            Rstats::pl_new_sv_iv(this->get_integer_value(i))
          );
        }
        break;
      case Rstats::VectorType::LOGICAL :
        for (IV i = 0; i < length; i++) {
          if (this->get_integer_value(i)) {
            e2->set_character_value(i, Rstats::pl_new_sv_pv("TRUE"));
          }
          else {
            e2->set_character_value(i, Rstats::pl_new_sv_pv("FALSE"));
          }
        }
        break;
      default:
        croak("unexpected type");
    }

    e2->merge_na_positions(this);
    
    return e2;
  }
  
  Rstats::Vector* Rstats::Vector::as_double() {

    IV length = this->get_length();
    Rstats::Vector* e2 = new_double(length);
    Rstats::VectorType::Enum type = this->get_type();
    switch (type) {
      case Rstats::VectorType::CHARACTER :
        for (IV i = 0; i < length; i++) {
          SV* sv_value = this->get_character_value(i);
          SV* sv_value_fix = Rstats::Util::looks_like_double(sv_value);
          if (SvOK(sv_value_fix)) {
            NV value = SvNV(sv_value_fix);
            e2->set_double_value(i, value);
          }
          else {
            warn("NAs introduced by coercion");
            e2->add_na_position(i);
          }
        }
        break;
      case Rstats::VectorType::COMPLEX :
        warn("imaginary parts discarded in coercion");
        for (IV i = 0; i < length; i++) {
          e2->set_double_value(i, this->get_complex_value(i).real());
        }
        break;
      case Rstats::VectorType::DOUBLE :
        for (IV i = 0; i < length; i++) {
          e2->set_double_value(i, this->get_double_value(i));
        }
        break;
      case Rstats::VectorType::INTEGER :
      case Rstats::VectorType::LOGICAL :
        for (IV i = 0; i < length; i++) {
          e2->set_double_value(i, this->get_integer_value(i));
        }
        break;
      default:
        croak("unexpected type");
    }

    e2->merge_na_positions(this);
    
    return e2;
  }

  Rstats::Vector* Rstats::Vector::as_numeric() {
    return this->as_double();
  }

  Rstats::Vector* Rstats::Vector::as_integer() {

    IV length = this->get_length();
    Rstats::Vector* e2 = new_integer(length);
    Rstats::VectorType::Enum type = this->get_type();
    switch (type) {
      case Rstats::VectorType::CHARACTER :
        for (IV i = 0; i < length; i++) {
          SV* sv_value = this->get_character_value(i);
          SV* sv_value_fix = Rstats::Util::looks_like_double(sv_value);
          if (SvOK(sv_value_fix)) {
            IV value = SvIV(sv_value_fix);
            e2->set_integer_value(i, value);
          }
          else {
            warn("NAs introduced by coercion");
            e2->add_na_position(i);
          }
        }
        break;
      case Rstats::VectorType::COMPLEX :
        warn("imaginary parts discarded in coercion");
        for (IV i = 0; i < length; i++) {
          e2->set_integer_value(i, (IV)this->get_complex_value(i).real());
        }
        break;
      case Rstats::VectorType::DOUBLE :
        NV value;
        for (IV i = 0; i < length; i++) {
          value = this->get_double_value(i);
          if (std::isnan(value) || std::isinf(value)) {
            e2->add_na_position(i);
          }
          else {
            e2->set_integer_value(i, (IV)value);
          }
        }
        break;
      case Rstats::VectorType::INTEGER :
      case Rstats::VectorType::LOGICAL :
        for (IV i = 0; i < length; i++) {
          e2->set_integer_value(i, this->get_integer_value(i));
        }
        break;
      default:
        croak("unexpected type");
    }

    e2->merge_na_positions(this);
    
    return e2;
  }

  Rstats::Vector* Rstats::Vector::as_complex() {

    IV length = this->get_length();
    Rstats::Vector* e2 = new_complex(length);
    Rstats::VectorType::Enum type = this->get_type();
    switch (type) {
      case Rstats::VectorType::CHARACTER :
        for (IV i = 0; i < length; i++) {
          SV* sv_value = this->get_character_value(i);
          SV* sv_z = Rstats::Util::looks_like_complex(sv_value);
          
          if (SvOK(sv_z)) {
            SV* sv_re = Rstats::pl_hv_fetch(sv_z, "re");
            SV* sv_im = Rstats::pl_hv_fetch(sv_z, "im");
            NV re = SvNV(sv_re);
            NV im = SvNV(sv_im);
            e2->set_complex_value(i, std::complex<NV>(re, im));
          }
          else {
            warn("NAs introduced by coercion");
            e2->add_na_position(i);
          }
        }
        break;
      case Rstats::VectorType::COMPLEX :
        for (IV i = 0; i < length; i++) {
          e2->set_complex_value(i, this->get_complex_value(i));
        }
        break;
      case Rstats::VectorType::DOUBLE :
        for (IV i = 0; i < length; i++) {
          NV value = this->get_double_value(i);
          if (std::isnan(value)) {
            e2->add_na_position(i);
          }
          else {
            e2->set_complex_value(i, std::complex<NV>(this->get_double_value(i), 0));
          }
        }
        break;
      case Rstats::VectorType::INTEGER :
      case Rstats::VectorType::LOGICAL :
        for (IV i = 0; i < length; i++) {
          e2->set_complex_value(i, std::complex<NV>(this->get_integer_value(i), 0));
        }
        break;
      default:
        croak("unexpected type");
    }

    e2->merge_na_positions(this);
    
    return e2;
  }
  
  Rstats::Vector* Rstats::Vector::as_logical() {
    IV length = this->get_length();
    Rstats::Vector* e2 = new_logical(length);
    Rstats::VectorType::Enum type = this->get_type();
    switch (type) {
      case Rstats::VectorType::CHARACTER :
        for (IV i = 0; i < length; i++) {
          SV* sv_value = this->get_character_value(i);
          SV* sv_logical = Rstats::Util::looks_like_logical(sv_value);
          if (SvOK(sv_logical)) {
            if (SvTRUE(sv_logical)) {
              e2->set_integer_value(i, 1);
            }
            else {
              e2->set_integer_value(i, 0);
            }
          }
          else {
            warn("NAs introduced by coercion");
            e2->add_na_position(i);
          }
        }
        break;
      case Rstats::VectorType::COMPLEX :
        warn("imaginary parts discarded in coercion");
        for (IV i = 0; i < length; i++) {
          e2->set_integer_value(i, this->get_complex_value(i).real() ? 1 : 0);
        }
        break;
      case Rstats::VectorType::DOUBLE :
        for (IV i = 0; i < length; i++) {
          NV value = this->get_double_value(i);
          if (std::isnan(value)) {
            e2->add_na_position(i);
          }
          else if (std::isinf(value)) {
            e2->set_integer_value(i, 1);
          }
          else {
            e2->set_integer_value(i, value ? 1 : 0);
          }
        }
        break;
      case Rstats::VectorType::INTEGER :
      case Rstats::VectorType::LOGICAL :
        for (IV i = 0; i < length; i++) {
          e2->set_integer_value(i, this->get_integer_value(i) ? 1 : 0);
        }
        break;
      default:
        croak("unexpected type");
    }

    e2->merge_na_positions(this);
    
    return e2;
  }

namespace Rstats {
  // Rstats::VectorFunc
  namespace VectorFunc {
    RSTATS_DEF_VECTOR_FUNC_UN_IS(is_infinite, Rstats::ElementFunc::is_infinite)
    RSTATS_DEF_VECTOR_FUNC_UN_IS(is_finite, Rstats::ElementFunc::is_finite)
    RSTATS_DEF_VECTOR_FUNC_UN_IS(is_nan, Rstats::ElementFunc::is_nan)
    
    RSTATS_DEF_VECTOR_FUNC_UN_MATH(negation, Rstats::ElementFunc::negation)

    RSTATS_DEF_VECTOR_FUNC_UN_MATH_INTEGER_TO_DOUBLE(sin, Rstats::ElementFunc::sin)
    RSTATS_DEF_VECTOR_FUNC_UN_MATH_INTEGER_TO_DOUBLE(cos, Rstats::ElementFunc::cos)
    RSTATS_DEF_VECTOR_FUNC_UN_MATH_INTEGER_TO_DOUBLE(tan, Rstats::ElementFunc::tan)
    RSTATS_DEF_VECTOR_FUNC_UN_MATH_INTEGER_TO_DOUBLE(sinh, Rstats::ElementFunc::sinh)
    RSTATS_DEF_VECTOR_FUNC_UN_MATH_INTEGER_TO_DOUBLE(cosh, Rstats::ElementFunc::cosh)
    RSTATS_DEF_VECTOR_FUNC_UN_MATH_INTEGER_TO_DOUBLE(tanh, Rstats::ElementFunc::tanh)
    RSTATS_DEF_VECTOR_FUNC_UN_MATH_INTEGER_TO_DOUBLE(log, Rstats::ElementFunc::log)
    RSTATS_DEF_VECTOR_FUNC_UN_MATH_INTEGER_TO_DOUBLE(logb, Rstats::ElementFunc::logb)
    RSTATS_DEF_VECTOR_FUNC_UN_MATH_INTEGER_TO_DOUBLE(log10, Rstats::ElementFunc::log10)
    RSTATS_DEF_VECTOR_FUNC_UN_MATH_INTEGER_TO_DOUBLE(log2, Rstats::ElementFunc::log2)
    RSTATS_DEF_VECTOR_FUNC_UN_MATH_INTEGER_TO_DOUBLE(expm1, Rstats::ElementFunc::expm1)
    RSTATS_DEF_VECTOR_FUNC_UN_MATH_INTEGER_TO_DOUBLE(exp, Rstats::ElementFunc::exp)
    RSTATS_DEF_VECTOR_FUNC_UN_MATH_INTEGER_TO_DOUBLE(sqrt, Rstats::ElementFunc::sqrt)
    RSTATS_DEF_VECTOR_FUNC_UN_MATH_INTEGER_TO_DOUBLE(atan, Rstats::ElementFunc::atan)
    RSTATS_DEF_VECTOR_FUNC_UN_MATH_INTEGER_TO_DOUBLE(asin, Rstats::ElementFunc::asin)
    RSTATS_DEF_VECTOR_FUNC_UN_MATH_INTEGER_TO_DOUBLE(acos, Rstats::ElementFunc::acos)
    RSTATS_DEF_VECTOR_FUNC_UN_MATH_INTEGER_TO_DOUBLE(asinh, Rstats::ElementFunc::asinh)
    RSTATS_DEF_VECTOR_FUNC_UN_MATH_INTEGER_TO_DOUBLE(acosh, Rstats::ElementFunc::acosh)
    RSTATS_DEF_VECTOR_FUNC_UN_MATH_INTEGER_TO_DOUBLE(atanh, Rstats::ElementFunc::atanh)
    RSTATS_DEF_VECTOR_FUNC_UN_MATH_INTEGER_TO_DOUBLE(Conj, Rstats::ElementFunc::Conj)

    RSTATS_DEF_VECTOR_FUNC_UN_MATH_COMPLEX_INTEGER_TO_DOUBLE(Arg, Rstats::ElementFunc::Arg)
    RSTATS_DEF_VECTOR_FUNC_UN_MATH_COMPLEX_INTEGER_TO_DOUBLE(abs, Rstats::ElementFunc::abs)
    RSTATS_DEF_VECTOR_FUNC_UN_MATH_COMPLEX_INTEGER_TO_DOUBLE(Mod, Rstats::ElementFunc::Mod)
    RSTATS_DEF_VECTOR_FUNC_UN_MATH_COMPLEX_INTEGER_TO_DOUBLE(Re, Rstats::ElementFunc::Re)
    RSTATS_DEF_VECTOR_FUNC_UN_MATH_COMPLEX_INTEGER_TO_DOUBLE(Im, Rstats::ElementFunc::Im)

    RSTATS_DEF_VECTOR_FUNC_BIN_TO_LOGICAL(equal, Rstats::ElementFunc::equal);
    RSTATS_DEF_VECTOR_FUNC_BIN_TO_LOGICAL(not_equal, Rstats::ElementFunc::not_equal);
    RSTATS_DEF_VECTOR_FUNC_BIN_TO_LOGICAL(more_than, Rstats::ElementFunc::more_than);
    RSTATS_DEF_VECTOR_FUNC_BIN_TO_LOGICAL(less_than, Rstats::ElementFunc::less_than);
    RSTATS_DEF_VECTOR_FUNC_BIN_TO_LOGICAL(more_than_or_equal, Rstats::ElementFunc::more_than_or_equal);
    RSTATS_DEF_VECTOR_FUNC_BIN_TO_LOGICAL(less_than_or_equal, Rstats::ElementFunc::less_than_or_equal);
    RSTATS_DEF_VECTOR_FUNC_BIN_TO_LOGICAL(And, Rstats::ElementFunc::And);
    RSTATS_DEF_VECTOR_FUNC_BIN_TO_LOGICAL(Or, Rstats::ElementFunc::Or);

    RSTATS_DEF_VECTOR_FUNC_BIN_MATH(add, Rstats::ElementFunc::add)
    RSTATS_DEF_VECTOR_FUNC_BIN_MATH(subtract, Rstats::ElementFunc::subtract)
    RSTATS_DEF_VECTOR_FUNC_BIN_MATH(multiply, Rstats::ElementFunc::multiply)
    RSTATS_DEF_VECTOR_FUNC_BIN_MATH(reminder, Rstats::ElementFunc::reminder)

    RSTATS_DEF_VECTOR_FUNC_BIN_MATH_INTEGER_TO_DOUBLE(divide, Rstats::ElementFunc::divide)
    RSTATS_DEF_VECTOR_FUNC_BIN_MATH_INTEGER_TO_DOUBLE(atan2, Rstats::ElementFunc::atan2)
    RSTATS_DEF_VECTOR_FUNC_BIN_MATH_INTEGER_TO_DOUBLE(pow, Rstats::ElementFunc::pow)
    
    Rstats::Vector* cumprod(Rstats::Vector* e1) {
      IV length = e1->get_length();
      Rstats::Vector* e2;
      Rstats::VectorType::Enum type = e1->get_type();
      switch (type) {
        case Rstats::VectorType::CHARACTER :
          croak("Error in cumprod() : non-numeric argument to binary operator");
          break;
        case Rstats::VectorType::COMPLEX : {
          e2 = Rstats::Vector::new_complex(length);
          std::complex<NV> e2_total(1, 0);
          for (IV i = 0; i < length; i++) {
            e2_total *= e1->get_complex_value(i);
            e2->set_complex_value(i, e2_total);
          }
          break;
        }
        case Rstats::VectorType::DOUBLE : {
          e2 = Rstats::Vector::new_double(length);
          NV e2_total(1);
          for (IV i = 0; i < length; i++) {
            e2_total *= e1->get_double_value(i);
            e2->set_double_value(i, e2_total);
          }
          break;
        }
        case Rstats::VectorType::INTEGER :
        case Rstats::VectorType::LOGICAL : {
          e2 = Rstats::Vector::new_integer(length);
          IV e2_total(1);
          for (IV i = 0; i < length; i++) {
            e2_total *= e1->get_integer_value(i);
            e2->set_integer_value(i, e2_total);
          }
          break;
        }
        default:
          croak("Invalid type");

      }

      e2->merge_na_positions(e1);
      
      return e2;
    }
    
    Rstats::Vector* cumsum(Rstats::Vector* e1) {
      IV length = e1->get_length();
      Rstats::Vector* e2;
      Rstats::VectorType::Enum type = e1->get_type();
      switch (type) {
        case Rstats::VectorType::CHARACTER :
          croak("Error in cumsum() : non-numeric argument to binary operator");
          break;
        case Rstats::VectorType::COMPLEX : {
          e2 = Rstats::Vector::new_complex(length);
          std::complex<NV> e2_total(0, 0);
          for (IV i = 0; i < length; i++) {
            e2_total += e1->get_complex_value(i);
            e2->set_complex_value(i, e2_total);
          }
          break;
        }
        case Rstats::VectorType::DOUBLE : {
          e2 = Rstats::Vector::new_double(length);
          NV e2_total(0);
          for (IV i = 0; i < length; i++) {
            e2_total += e1->get_double_value(i);
            e2->set_double_value(i, e2_total);
          }
          break;
        }
        case Rstats::VectorType::INTEGER :
        case Rstats::VectorType::LOGICAL : {
          e2 = Rstats::Vector::new_integer(length);
          IV e2_total(0);
          for (IV i = 0; i < length; i++) {
            e2_total += e1->get_integer_value(i);
            e2->set_integer_value(i, e2_total);
          }
          break;
        }
        default:
          croak("Invalid type");

        e2->merge_na_positions(e1);
      }
      
      return e2;
    }

    Rstats::Vector* prod(Rstats::Vector* e1) {
      
      IV length = e1->get_length();
      Rstats::Vector* e2;
      Rstats::VectorType::Enum type = e1->get_type();
      switch (type) {
        case Rstats::VectorType::CHARACTER :
          croak("Error in prod() : non-numeric argument to prod()");
          break;
        case Rstats::VectorType::COMPLEX : {
          e2 = Rstats::Vector::new_complex(1);
          std::complex<NV> e2_total(1, 0);
          for (IV i = 0; i < length; i++) {
            e2_total *= e1->get_complex_value(i);
          }
          e2->set_complex_value(0, e2_total);
          break;
        }
        case Rstats::VectorType::DOUBLE : {
          e2 = Rstats::Vector::new_double(1);
          NV e2_total(1);
          for (IV i = 0; i < length; i++) {
            e2_total *= e1->get_double_value(i);
          }
          e2->set_double_value(0, e2_total);
          break;
        }
        case Rstats::VectorType::INTEGER :
        case Rstats::VectorType::LOGICAL : {
          e2 = Rstats::Vector::new_integer(1);
          IV e2_total(1);
          for (IV i = 0; i < length; i++) {
            e2_total *= e1->get_integer_value(i);
          }
          e2->set_integer_value(0, e2_total);
          break;
        }
        default:
          croak("Invalid type");

      }

      for (IV i = 0; i < length; i++) {
        if (e1->exists_na_position(i)) {
          e2->add_na_position(0);
          break;
        }
      }
            
      return e2;
    }
    
    Rstats::Vector* sum(Rstats::Vector* e1) {
      
      IV length = e1->get_length();
      Rstats::Vector* e2;
      Rstats::VectorType::Enum type = e1->get_type();
      switch (type) {
        case Rstats::VectorType::CHARACTER :
          croak("Error in a - b : non-numeric argument to binary operator");
          break;
        case Rstats::VectorType::COMPLEX : {
          e2 = Rstats::Vector::new_complex(1);
          std::complex<NV> e2_total(0, 0);
          for (IV i = 0; i < length; i++) {
            e2_total += e1->get_complex_value(i);
          }
          e2->set_complex_value(0, e2_total);
          break;
        }
        case Rstats::VectorType::DOUBLE : {
          e2 = Rstats::Vector::new_double(1);
          NV e2_total(0);
          for (IV i = 0; i < length; i++) {
            e2_total += e1->get_double_value(i);
          }
          e2->set_double_value(0, e2_total);
          break;
        }
        case Rstats::VectorType::INTEGER :
        case Rstats::VectorType::LOGICAL : {
          e2 = Rstats::Vector::new_integer(1);
          IV e2_total(0);
          for (IV i = 0; i < length; i++) {
            e2_total += e1->get_integer_value(i);
          }
          e2->set_integer_value(0, e2_total);
          break;
        }
        default:
          croak("Invalid type");

      }
      
      for (IV i = 0; i < length; i++) {
        if (e1->exists_na_position(i)) {
          e2->add_na_position(0);
          break;
        }
      }
      
      return e2;
    }

    Rstats::Vector* clone(Rstats::Vector* e1) {
      
      IV length = e1->get_length();
      Rstats::Vector* e2;
      Rstats::VectorType::Enum type = e1->get_type();
      switch (type) {
        case Rstats::VectorType::CHARACTER :
          e2 = Rstats::Vector::new_character(length);
          for (IV i = 0; i < length; i++) {
            e2->set_character_value(i, e1->get_character_value(i));
          }
          break;
        case Rstats::VectorType::COMPLEX :
          e2 = Rstats::Vector::new_complex(length);
          for (IV i = 0; i < length; i++) {
            e2->set_complex_value(i, e1->get_complex_value(i));
          }
          break;
        case Rstats::VectorType::DOUBLE :
          e2 = Rstats::Vector::new_double(length);
          for (IV i = 0; i < length; i++) {
            e2->set_double_value(i, e1->get_double_value(i));
          }
          break;
        case Rstats::VectorType::INTEGER :
          e2 = Rstats::Vector::new_integer(length);
          for (IV i = 0; i < length; i++) {
            e2->set_integer_value(i, e1->get_integer_value(i));
          }
          break;
        case Rstats::VectorType::LOGICAL :
          e2 = Rstats::Vector::new_logical(length);
          for (IV i = 0; i < length; i++) {
            e2->set_integer_value(i, e1->get_integer_value(i));
          }
          break;
        default:
          croak("Invalid type");

      }
      
      e2->merge_na_positions(e1);
      
      return e2;
    }
  }

  // Rstats::ArrayFunc
  namespace ArrayFunc {
    SV* new_array() {
      
      SV* sv_self = Rstats::pl_new_hv_ref();
      sv_bless(sv_self, gv_stashpv("Rstats::Array", 1));
      
      return sv_self;
    }
    
    void set_vector(SV* sv_a1, Rstats::Vector* v1) {
      SV* sv_vector = Rstats::pl_to_perl_obj<Rstats::Vector*>(v1, "Rstats::Vector");
      Rstats::pl_hv_store(sv_a1, "vector", sv_vector);
    }
    
    Rstats::Vector* get_vector(SV* sv_a1) {
      SV* sv_vector = Rstats::pl_hv_fetch(sv_a1, "vector");
      Rstats::Vector* vector = Rstats::pl_to_c_obj<Rstats::Vector*>(sv_vector);
      return vector;
    }

    void set_dim(SV* sv_a1, Rstats::Vector* v1) {
      SV* sv_dim = Rstats::pl_to_perl_obj<Rstats::Vector*>(v1, "Rstats::Vector");
      Rstats::pl_hv_store(sv_a1, "dim", sv_dim);
    }
    
    Rstats::Vector* get_dim(SV* sv_a1) {
      SV* sv_dim = Rstats::pl_hv_fetch(sv_a1, "dim");
      Rstats::Vector* dim = Rstats::pl_to_c_obj<Rstats::Vector*>(sv_dim);
      return dim;
    }

    SV* c(SV* sv_elements) {

      IV element_length = Rstats::pl_av_len(sv_elements);
      // Check type and length
      std::map<Rstats::VectorType::Enum, IV> type_h;
      IV length = 0;
      for (IV i = 0; i < element_length; i++) {
        Rstats::VectorType::Enum type;
        SV* sv_element = Rstats::pl_av_fetch(sv_elements, i);
        if (sv_isobject(sv_element) && sv_derived_from(sv_element, "Rstats::Array")) {
          length += Rstats::ArrayFunc::get_vector(sv_element)->get_length();
          type = Rstats::ArrayFunc::get_vector(sv_element)->get_type();
          type_h[type] = 1;
        }
        else if (sv_isobject(sv_element) && sv_derived_from(sv_element, "Rstats::Vector")) {
          length += Rstats::pl_to_c_obj<Rstats::Vector*>(sv_element)->get_length();
          type = Rstats::pl_to_c_obj<Rstats::Vector*>(sv_element)->get_type();
          type_h[type] = 1;
        }
        else {
          if (SvOK(sv_element)) {
            if (Rstats::Util::is_perl_number(sv_element)) {
              type_h[Rstats::VectorType::DOUBLE] = 1;
            }
            else {
              type_h[Rstats::VectorType::CHARACTER] = 1;
            }
          }
          else {
            type_h[Rstats::VectorType::LOGICAL] = 1;
          }
          length += 1;
        }
      }

      // Decide type
      Rstats::Vector* v2;
      if (type_h[Rstats::VectorType::CHARACTER]) {
        v2 = Rstats::Vector::new_character(length);
      }
      else if (type_h[Rstats::VectorType::COMPLEX]) {
        v2 = Rstats::Vector::new_complex(length);
      }
      else if (type_h[Rstats::VectorType::DOUBLE]) {
        v2 = Rstats::Vector::new_double(length);
      }
      else if (type_h[Rstats::VectorType::INTEGER]) {
        v2 = Rstats::Vector::new_integer(length);
      }
      else {
        v2 = Rstats::Vector::new_logical(length);
      }
      
      Rstats::VectorType::Enum type = v2->get_type();
      
      IV pos = 0;
      for (IV i = 0; i < element_length; i++) {
        SV* sv_element = Rstats::pl_av_fetch(sv_elements, i);
        if (sv_derived_from(sv_element, "Rstats::Array") || sv_derived_from(sv_element, "Rstats::Vector")) {
          
          Rstats::Vector* v1;
          if (sv_derived_from(sv_element, "Rstats::Array")) {
            v1 = Rstats::ArrayFunc::get_vector(sv_element);
          }
          else {
            v1 = Rstats::pl_to_c_obj<Rstats::Vector*>(sv_element);
          }
          
          Rstats::Vector* v_tmp;
          if (v1->get_type() == type) {
            v_tmp = v1;
          }
          else {
            if (type == Rstats::VectorType::CHARACTER) {
              v_tmp = v1->as_character();
            }
            else if (type == Rstats::VectorType::COMPLEX) {
              v_tmp = v1->as_complex();
            }
            else if (type == Rstats::VectorType::DOUBLE) {
              v_tmp = v1->as_double();
            }
            else if (type == Rstats::VectorType::INTEGER) {
              v_tmp = v1->as_integer();
            }
            else {
              v_tmp = v1->as_logical();
            }
          }
          
          for (IV k = 0; k < v_tmp->get_length(); k++) {
            if (v_tmp->exists_na_position(k)) {
              v2->add_na_position(pos);
            }
            else {
              if (type == Rstats::VectorType::CHARACTER) {
                v2->set_character_value(pos, v_tmp->get_character_value(k));
              }
              else if (type == Rstats::VectorType::COMPLEX) {
                v2->set_complex_value(pos, v_tmp->get_complex_value(k));
              }
              else if (type == Rstats::VectorType::DOUBLE) {
                v2->set_double_value(pos, v_tmp->get_double_value(k));
              }
              else if (type == Rstats::VectorType::INTEGER) {
                v2->set_integer_value(pos, v_tmp->get_integer_value(k));
              }
              else {
                v2->set_integer_value(pos, v_tmp->get_integer_value(k));
              }
            }
            
            pos++;
          }
          
          if (v_tmp != v1) {
            delete v_tmp;
          }
        }
        else {
          if (SvOK(sv_element)) {
            if (type == Rstats::VectorType::CHARACTER) {
              v2->set_character_value(pos, sv_element);
            }
            else if (type == Rstats::VectorType::COMPLEX) {
              v2->set_complex_value(pos, std::complex<NV>(SvNV(sv_element), 0));
            }
            else if (type == Rstats::VectorType::DOUBLE) {
              v2->set_double_value(pos, SvNV(sv_element));
            }
            else if (type == Rstats::VectorType::INTEGER) {
              v2->set_integer_value(pos, SvIV(sv_element));
            }
            else {
              v2->set_integer_value(pos, SvIV(sv_element));
            }
          }
          else {
            v2->add_na_position(pos);
          }
          pos++;
        }
      }
      
      // Array
      SV* sv_x1 = Rstats::ArrayFunc::new_array();
      Rstats::ArrayFunc::set_vector(sv_x1, v2);

      return sv_x1;
    }

    SV* to_c(SV* sv_x) {

      IV is_container = sv_isobject(sv_x) && sv_derived_from(sv_x, "Rstats::Container");
      
      SV* sv_x1;
      if (is_container) {
        sv_x1 = sv_x;
      }
      else {
        SV* sv_tmp = Rstats::pl_new_av_ref();
        Rstats::pl_av_push(sv_tmp, sv_x);
        sv_x1 = Rstats::ArrayFunc::c(sv_tmp);
      }
      
      return sv_x1;
    }
  }
  
  // Rstats::Util body
  namespace Util {
    REGEXP* LOGICAL_RE = pregcomp(newSVpv("^ *(T|TRUE|F|FALSE) *$", 0), 0);
    REGEXP* LOGICAL_TRUE_RE = pregcomp(newSVpv("T", 0), 0);
    REGEXP* INTEGER_RE = pregcomp(newSVpv("^ *([\\-\\+]?[0-9]+) *$", 0), 0);
    REGEXP* DOUBLE_RE = pregcomp(newSVpv("^ *([\\-\\+]?[0-9]+(?:\\.[0-9]+)?) *$", 0), 0);
    REGEXP* COMPLEX_IMAGE_ONLY_RE = pregcomp(newSVpv("^ *([\\+\\-]?[0-9]+(?:\\.[0-9]+)?)i *$", 0), 0);
    REGEXP* COMPLEX_RE = pregcomp(newSVpv("^ *([\\+\\-]?[0-9]+(?:\\.[0-9]+)?)(?:([\\+\\-][0-9]+(?:\\.[0-9]+)?)i)? *$", 0), 0);

    SV* args(SV* sv_names, SV* sv_args) {
      
      IV args_length = Rstats::pl_av_len(sv_args);
      SV* sv_opt;
      SV* sv_arg_last = Rstats::pl_av_fetch(sv_args, args_length - 1);
      if (!sv_isobject(sv_arg_last) && sv_derived_from(sv_arg_last, "HASH")) {
        sv_opt = Rstats::pl_av_pop(sv_args);
      }
      else {
        sv_opt = Rstats::pl_new_hv_ref();
      }
      
      SV* sv_new_opt = Rstats::pl_new_hv_ref();
      IV names_length = Rstats::pl_av_len(sv_names);
      for (IV i = 0; i < names_length; i++) {
        SV* sv_name = Rstats::pl_av_fetch(sv_names, i);
        if (Rstats::pl_hv_exists(sv_opt, SvPV_nolen(sv_name))) {
          Rstats::pl_hv_store(
            sv_new_opt,
            SvPV_nolen(sv_name),
            Rstats::ArrayFunc::to_c(Rstats::pl_hv_delete(sv_opt, SvPV_nolen(sv_name)))
          );
        }
        else if (i < names_length) {
          SV* sv_name = Rstats::pl_av_fetch(sv_names, i);
          SV* sv_arg = Rstats::pl_av_fetch(sv_args, i);
          if (SvOK(sv_arg)) {
            Rstats::pl_hv_store(
              sv_new_opt,
              SvPV_nolen(sv_name),
              Rstats::ArrayFunc::to_c(sv_arg)
            );
          }
        }
      }

      // SV* sv_key;
      // while ((sv_key = hv_iterkeysv(hv_iternext(Rstats::pl_hv_deref(sv_opt)))) != NULL) {
        // croak("unused argument (%s)", SvPV_nolen(sv_key));
      // }
      
      return sv_new_opt;
    }

    IV is_perl_number(SV* sv_str) {
      if (!SvOK(sv_str)) {
        return 0;
      }
      
      if ((SvIOKp(sv_str) || SvNOKp(sv_str)) && 0 + sv_cmp(sv_str, sv_str) == 0 && SvIV(sv_str) * 0 == 0) {
        return 1;
      }
      else {
        return 0;
      }
    }
    
    SV* cross_product(SV* sv_values) {
      
      IV values_length = Rstats::pl_av_len(sv_values);
      SV* sv_idxs = Rstats::pl_new_av_ref();
      for (IV i = 0; i < values_length; i++) {
        Rstats::pl_av_push(sv_idxs, Rstats::pl_new_sv_iv(0)); 
      }
      
      SV* sv_idx_idx = Rstats::pl_new_av_ref();
      for (IV i = 0; i < values_length; i++) {
        Rstats::pl_av_push(sv_idx_idx, Rstats::pl_new_sv_iv(i));
      }
      
      SV* sv_x1 = Rstats::pl_new_av_ref();
      for (IV i = 0; i < values_length; i++) {
        SV* sv_value = Rstats::pl_av_fetch(sv_values, i);
        Rstats::pl_av_push(sv_x1, Rstats::pl_av_fetch(sv_value, 0));
      }

      SV* sv_result = Rstats::pl_new_av_ref();
      Rstats::pl_av_push(sv_result, Rstats::pl_av_copy(sv_x1));
      IV end_loop = 0;
      while (1) {
        for (IV i = 0; i < values_length; i++) {
          
          if (SvIV(Rstats::pl_av_fetch(sv_idxs, i)) < Rstats::pl_av_len(Rstats::pl_av_fetch(sv_values, i)) - 1) {
            
            SV* sv_idxs_tmp = Rstats::pl_av_fetch(sv_idxs, i);
            sv_inc(sv_idxs_tmp);
            Rstats::pl_av_store(sv_x1, i, Rstats::pl_av_fetch(Rstats::pl_av_fetch(sv_values, i), SvIV(sv_idxs_tmp)));
            
            Rstats::pl_av_push(sv_result, Rstats::pl_av_copy(sv_x1));
            
            break;
          }
          
          if (i == SvIV(Rstats::pl_av_fetch(sv_idx_idx, values_length - 1))) {
            end_loop = 1;
            break;
          }
          
          Rstats::pl_av_store(sv_idxs, i, Rstats::pl_new_sv_iv(0));
          Rstats::pl_av_store(sv_x1, i, Rstats::pl_av_fetch(Rstats::pl_av_fetch(sv_values, i), 0));
        }
        if (end_loop) {
          break;
        }
      }

      return sv_result;
    }

    SV* pos_to_index(SV* sv_pos, SV* sv_dim) {
      
      SV* sv_index = Rstats::pl_new_av_ref();
      IV pos = SvIV(sv_pos);
      IV before_dim_product = 1;
      for (IV i = 0; i < Rstats::pl_av_len(sv_dim); i++) {
        before_dim_product *= SvIV(Rstats::pl_av_fetch(sv_dim, i));
      }
      
      for (IV i = Rstats::pl_av_len(sv_dim) - 1; i >= 0; i--) {
        IV dim_product = 1;
        for (IV k = 0; k < i; k++) {
          dim_product *= SvIV(Rstats::pl_av_fetch(sv_dim, k));
        }
        
        IV reminder = pos % before_dim_product;
        IV quotient = (IV)(reminder / dim_product);
        
        Rstats::pl_av_unshift(sv_index, Rstats::pl_new_sv_iv(quotient + 1));
        before_dim_product = dim_product;
      }
      
      return sv_index;
    }

    SV* index_to_pos(SV* sv_index, SV* sv_dim_values) {
      
      IV pos = 0;
      for (IV i = 0; i < Rstats::pl_av_len(sv_dim_values); i++) {
        if (i > 0) {
          IV tmp = 1;
          for (IV k = 0; k < i; k++) {
            tmp *= SvIV(Rstats::pl_av_fetch(sv_dim_values, k));
          }
          pos += tmp * (SvIV(Rstats::pl_av_fetch(sv_index, i)) - 1);
        }
        else {
          pos += SvIV(Rstats::pl_av_fetch(sv_index, i));
        }
      }
      
      SV* sv_pos = Rstats::pl_new_sv_iv(pos - 1);
      
      return sv_pos;
    }

    SV* looks_like_complex (SV* sv_value) {
      
      SV* sv_ret;
      if (!SvOK(sv_value) || sv_len(sv_value) == 0) {
        sv_ret = &PL_sv_undef;
      }
      else {
        SV* sv_re;
        SV* sv_im;
        if (Rstats::pl_pregexec(sv_value, COMPLEX_IMAGE_ONLY_RE)) {
          sv_re = Rstats::pl_new_sv_nv(0);
          SV* sv_im_str = Rstats::pl_new_sv_pv("");
          Perl_reg_numbered_buff_fetch(aTHX_ COMPLEX_IMAGE_ONLY_RE, 1, sv_im_str);
          sv_im = Rstats::pl_new_sv_nv(SvNV(sv_im_str));
          
          sv_ret = Rstats::pl_new_hv_ref();
          Rstats::pl_hv_store(sv_ret, "re", sv_re);
          Rstats::pl_hv_store(sv_ret, "im", sv_im);
        }
        else if(Rstats::pl_pregexec(sv_value, COMPLEX_RE)) {
          SV* sv_re_str = Rstats::pl_new_sv_pv("");
          Perl_reg_numbered_buff_fetch(aTHX_ COMPLEX_RE, 1, sv_re_str);
          sv_re = Rstats::pl_new_sv_nv(SvNV(sv_re_str));

          SV* sv_im_str = Rstats::pl_new_sv_pv("");
          Perl_reg_numbered_buff_fetch(aTHX_ COMPLEX_RE, 2, sv_im_str);
          if (SvOK(sv_im_str)) {
            sv_im = Rstats::pl_new_sv_nv(SvNV(sv_im_str));
          }
          else {
            sv_im = Rstats::pl_new_sv_nv(0);
          }

          sv_ret = Rstats::pl_new_hv_ref();
          Rstats::pl_hv_store(sv_ret, "re", sv_re);
          Rstats::pl_hv_store(sv_ret, "im", sv_im);
        }
        else {
          sv_ret = &PL_sv_undef;
        }
      }
      
      return sv_ret;
    }
    
    SV* looks_like_logical (SV* sv_value) {
      
      SV* sv_ret;
      if (!SvOK(sv_value) || sv_len(sv_value) == 0) {
        sv_ret = &PL_sv_undef;
      }
      else {
        if (Rstats::pl_pregexec(sv_value, LOGICAL_RE)) {
          if (Rstats::pl_pregexec(sv_value, LOGICAL_TRUE_RE)) {
            sv_ret = Rstats::pl_new_sv_iv(1);
          }
          else {
            sv_ret = Rstats::pl_new_sv_iv(0);
          }
        }
        else {
          sv_ret = &PL_sv_undef;
        }
      }
      return sv_ret;
    }

    SV* looks_like_na (SV* sv_value) {
      
      SV* sv_ret;
      if (!SvOK(sv_value) || sv_len(sv_value) == 0) {
        sv_ret = &PL_sv_undef;
      }
      else {
        SV* sv_na = Rstats::pl_new_sv_pv("NA");
        if (sv_cmp(sv_value, sv_na) == 0) {
          sv_ret = Rstats::pl_to_perl_obj(Rstats::Vector::new_na(), "Rstats::Vector");
        }
        else {
          sv_ret = &PL_sv_undef;
        }
      }
      
      return sv_ret;
    }
    
    SV* looks_like_integer(SV* sv_str) {
      
      SV* sv_ret;
      if (!SvOK(sv_str) || sv_len(sv_str) == 0) {
        sv_ret = &PL_sv_undef;
      }
      else {
        IV ret = Rstats::pl_pregexec(sv_str, INTEGER_RE);
        if (ret) {
          SV* match1 = Rstats::pl_new_sv_pv("");
          Perl_reg_numbered_buff_fetch(aTHX_ INTEGER_RE, 1, match1);
          sv_ret = Rstats::pl_new_sv_iv(SvIV(match1));
        }
        else {
          sv_ret = &PL_sv_undef;
        }
      }
      
      return sv_ret;
    }

    SV* looks_like_double (SV* sv_value) {
      
      SV* sv_ret;
      if (!SvOK(sv_value) || sv_len(sv_value) == 0) {
        sv_ret =  &PL_sv_undef;
      }
      else {
        IV ret = Rstats::pl_pregexec(sv_value, DOUBLE_RE);
        if (ret) {
          SV* match1 = Rstats::pl_new_sv_pv("");
          Perl_reg_numbered_buff_fetch(aTHX_ DOUBLE_RE, 1, match1);
          sv_ret = Rstats::pl_new_sv_nv(SvNV(match1));
        }
        else {
          sv_ret = &PL_sv_undef;
        }
      }
      
      return sv_ret;
    }
  }
}
