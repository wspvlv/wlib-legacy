#include <wl/stdc/complex.h>
#include <wl/stdc/math.h>

double		complex csin(double			complex z) {
	double x = creal(z);
	double y = cimag(z);
	return CMPLX(sin(x) * cosh(y), cos(x) * sinh(y));
}

float		complex csinf(float			complex z) {
	float x = crealf(z);
	float y = cimagf(z);
	return CMPLXF(sinf(x) * coshf(y), cosf(x) * sinhf(y));
}
long double complex csinl(long double	complex z) {
	long double x = creall(z);
	long double y = cimagl(z);
	return CMPLXL(sinl(x) * coshl(y), cosl(x) * sinhl(y));
}