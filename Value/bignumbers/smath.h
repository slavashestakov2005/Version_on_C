#ifndef SMATH_H_INCLUDED
#define SMATH_H_INCLUDED

Bignum sin(const Bignum& x);
Bignum cos(const Bignum& x);
Bignum tan(const Bignum& x);
Bignum sinh(const Bignum& x);
Bignum cosh(const Bignum& x);
Bignum tanh(const Bignum& x);
Bignum asin(const Bignum& x);
Bignum acos(const Bignum& x);
Bignum atan(const Bignum& x);
Bignum atan2(const Bignum& x, const Bignum& y);
Bignum exp(const Bignum& x);
Bignum log(const Bignum& x);
Bignum log10(const Bignum& x);
Bignum pow(const Bignum& x, const Bignum& y);
Bignum sqrt(const Bignum& x);
Bignum cbrt(const Bignum& x);
Bignum hypot(const Bignum& x, const Bignum& y);
Bignum to_degrees(const Bignum& x);
Bignum to_radians(const Bignum& x);
Bignum copy_sign(const Bignum& x, const Bignum& y);
Bignum expm1(const Bignum& x);
Bignum log1p(const Bignum& x);

Bignum ceil(const Bignum& x);
Bignum floor(const Bignum& x);
Bignum round(const Bignum& x);
Bignum abs(const Bignum& x);

/*
_CRTIMP double __cdecl sin (double);
_CRTIMP double __cdecl cos (double);
_CRTIMP double __cdecl tan (double);
_CRTIMP double __cdecl sinh (double);
_CRTIMP double __cdecl cosh (double);
_CRTIMP double __cdecl tanh (double);

_CRTIMP double __cdecl asin (double);
_CRTIMP double __cdecl acos (double);
_CRTIMP double __cdecl atan (double);

_CRTIMP double __cdecl atan2 (double, double);
_CRTIMP double __cdecl exp (double);
_CRTIMP double __cdecl log (double);
_CRTIMP double __cdecl log10 (double);
_CRTIMP	double __cdecl pow (double, double);
_CRTIMP double __cdecl sqrt (double);
_CRTIMP double __cdecl ceil (double);
_CRTIMP double __cdecl floor (double);
_CRTIMP double __cdecl fabs (double);

_CRTIMP double __cdecl ldexp (double, int);
_CRTIMP double __cdecl frexp (double, int*);
_CRTIMP double __cdecl modf (double, double*);
_CRTIMP double __cdecl fmod (double, double);
*/

#endif // SMATH_H_INCLUDED
