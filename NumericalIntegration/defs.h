
//vim: fdm=indent:ai:si:ts=2:st=2:tw=0:nohls:noic:nocp:nobk
// defs.h 20100423, piotao, @venona
// 20100908, piotao: added EPSILON defined as 1/MAXDATA

#ifndef DEFS_H_
#define DEFS_H_

#define SELECT_DOUBLE
//#define SELECT_FLOAT

// main data type in every library
typedef double  Data;
typedef Data*  pData;
typedef pData* ppData;

#if defined(SELECT_FLOAT)
#	include <values.h>
#	define MAXDATA MAXFLOAT
# define EPSILON (1/(MAXDATA-1.0f))
#endif

#if defined(SELECT_DOUBLE) || defined(SELECT_LONGDOUBLE)
#	include <values.h>
#	define MAXDATA MAXDOUBLE
# define EPSILON (1/(MAXDATA-1.0f))
#endif

#if defined(SELECT_INT)
#	include <values.h>
#	define MAXDATA MAXINT
# define EPSILON 0
#endif

#if defined(SELECT_LONGINT)
#	define MAXDATA MAXLONG
# define EPSILON 0
#endif

#ifndef MAXDATA
#	define MAXDATA 1e10
# define EPSILON 0
#endif


#endif /* DEFS_H_ */

