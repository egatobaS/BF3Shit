//--------------------------------------------------------------------------------------
// AtgUtil.h
//
// Helper functions and typing shortcuts for samples
//
// Xbox Advanced Technology Group.
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#pragma once
#ifndef ATGUTIL_H
#define ATGUTIL_H

#include <xboxmath.h>
#include <stdio.h>
#include <assert.h>

namespace ATG
{

//--------------------------------------------------------------------------------------
// Some macro definitions
//--------------------------------------------------------------------------------------

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) { if ( (x) != NULL && (x)->Release() == 0 ) { (x) = NULL; } }
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(x) { if ( (x) != NULL ) { delete (x); (x) = NULL; } }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p) = NULL; } }
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) ( sizeof(x) / sizeof(x[0] ) )
#endif

#ifndef RETURN_ON_FAIL
#define RETURN_ON_FAIL(fn) { HRESULT hr; if ( FAILED( hr = (fn) ) ) return hr;}
#endif

#ifndef RETURN_ON_NULL
#define RETURN_ON_NULL(x) { if ( (x) == NULL ) return E_FAIL;}
#endif


//--------------------------------------------------------------------------------------
// Debug spew and error handling routines
//--------------------------------------------------------------------------------------
#ifdef  _
	_format_string_  // VC++ 2008 and later support this annotation
VOID CDECL DebugSpew( _In_z_ _Printf_format_string_ const CHAR*, ... );  // Un-modified debug spew
VOID CDECL __declspec(noreturn) FatalError( _In_z_ _Printf_format_string_ const CHAR*, ... ); // Debug spew with a forced break and exit
#else
VOID CDECL DebugSpew( const CHAR*, ... );  // Un-modified debug spew
VOID CDECL __declspec(noreturn) FatalError( const CHAR*, ... ); // Debug spew with a forced break and exit
#endif

// Macros for printing warnings/errors with prepended file and line numbers
#define ATG_PrintWarning ATG::DebugSpew( "%s(%d): warning: ", __FILE__, __LINE__ ), ATG::DebugSpew
#define ATG_PrintError   ATG::DebugSpew( "%s(%d): error: ",   __FILE__, __LINE__ ), ATG::DebugSpew
#define ATG_PrintError2   ATG::DebugSpew( "%s(%d): error: ",   __FILE__, __LINE__ ), ATG::DebugSpew, ATG::DebugSpew

// Avoid compiler warnings for unused variables
#define ATG_Unused( x )   ((VOID)(x))




} // namespace ATG

#endif // ATGUTIL_H
