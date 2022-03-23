/*
	FPEnvironment_SUN.h - Definitions of class FPEnvironmentImpl for Solaris.
*/


#ifndef Core_FPEnvironment_SUN_INCLUDED
#define Core_FPEnvironment_SUN_INCLUDED


#include "../Core.h"
#include <ieeefp.h>


namespace Poco {

class FPEnvironmentImpl {
protected:
	enum RoundingModeImpl {
		FP_ROUND_DOWNWARD_IMPL   = FP_RM,
		FP_ROUND_UPWARD_IMPL     = FP_RP,
		FP_ROUND_TONEAREST_IMPL  = FP_RN,
		FP_ROUND_TOWARDZERO_IMPL = FP_RZ
	};
	
	enum FlagImpl {
		FP_DIVIDE_BY_ZERO_IMPL = FP_X_DZ,
		FP_INEXACT_IMPL        = FP_X_IMP,
		FP_OVERFLOW_IMPL       = FP_X_OFL,
		FP_UNDERFLOW_IMPL      = FP_X_UFL,
		FP_INVALID_IMPL        = FP_X_INV
	};
	
	FPEnvironmentImpl();
	FPEnvironmentImpl(const FPEnvironmentImpl& env);
	~FPEnvironmentImpl();
	FPEnvironmentImpl& operator = (const FPEnvironmentImpl& env);
	void keepCurrentImpl();		
	static void clearFlagsImpl();
	static bool isFlagImpl(FlagImpl flag);	
	static void setRoundingModeImpl(RoundingModeImpl mode);
	static RoundingModeImpl getRoundingModeImpl();
	static bool isInfiniteImpl(float value);		
	static bool isInfiniteImpl(double value);
	static bool isInfiniteImpl(long double value);
	static bool isNaNImpl(float value);		
	static bool isNaNImpl(double value);
	static bool isNaNImpl(long double value);
	static float copySignImpl(float target, float source);		
	static double copySignImpl(double target, double source);
	static long double copySignImpl(long double target, long double source);

private:
	fp_rnd    _rnd;
	fp_except _exc;
};

} // namespace Poco


#endif // Core_FPEnvironment_SUN_INCLUDED
