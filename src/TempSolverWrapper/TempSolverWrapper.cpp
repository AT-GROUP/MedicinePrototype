// This is the main DLL file.

//#include "stdafx.h"

#include "TempSolverWrapper.h"
#include <msclr/auto_gcroot.h>

using namespace System::Runtime::InteropServices;
using namespace System;

void MarshalString ( String ^ s, std::string& os ) {
   using namespace Runtime::InteropServices;
   const char* chars = 
      (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
   os = chars;
   Marshal::FreeHGlobal(IntPtr((void*)chars));
}

void MarshalString ( String ^ s, std::wstring& os ) {
   using namespace Runtime::InteropServices;
   const wchar_t* chars = 
      (const wchar_t*)(Marshal::StringToHGlobalUni(s)).ToPointer();
   os = chars;
   Marshal::FreeHGlobal(IntPtr((void*)chars));
}


struct ManagedHolder
{
	ManagedHolder()
	{
		m_pObject = gcnew SharpLib::ManagedClass(); 
	}

	msclr::auto_gcroot<SharpLib::ManagedClass^> object()
	{
		return m_pObject;
	}

	msclr::auto_gcroot<SharpLib::ManagedClass^> m_pObject;
};

TempSolverWrapper::TempSolverWrapper()
{
	m_pObjectHolder = new ManagedHolder();
}

void TempSolverWrapper::createManagedInstance()
{
	
}

int TempSolverWrapper::test()
{
	return m_pObjectHolder->object()->test();
}

std::string TempSolverWrapper::processMessage(const std::string message)
{
	String^ sharp_msg = gcnew String(message.c_str());

	String^ _result = m_pObjectHolder->object()->processMessage(sharp_msg);

	std::string result;

	MarshalString(_result, result);
	return result;
}
