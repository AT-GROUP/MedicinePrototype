// TempSolverWrapper.h

#ifndef TempSolverWrapper_TempSolverWrapper_H
#define TempSolverWrapper_TempSolverWrapper_H


//using namespace System;
#include <string>


#ifndef INTEROPBRIDGE_API
	#define INTEROPBRIDGE_API __declspec(dllexport)
#endif

struct ManagedHolder;

class INTEROPBRIDGE_API TempSolverWrapper
{
public:
	TempSolverWrapper();
	void createManagedInstance();
	int test();
	std::string processMessage(const std::string message);
private:
	ManagedHolder  * m_pObjectHolder;
};

/*namespace TempSolverWrapper
{

	public ref class Class1
	{
		// TODO: Add your methods for this class here.
	};
}
*/
#endif
