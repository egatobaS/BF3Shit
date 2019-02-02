//--------------------------------------------------------------------------------------
// AtgUtil.cpp
//
// Helper functions and typing shortcuts for samples
//
// Xbox Advanced Technology Group.
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include "stdafx.h"
#include "AtgUtil.h"

namespace ATG
{

// Global access to the main D3D device
extern D3DDevice* g_pd3dDevice;



//--------------------------------------------------------------------------------------
// Name: DebugSpewV()
// Desc: Internal helper function
//--------------------------------------------------------------------------------------
static VOID DebugSpewV( const CHAR* strFormat, const va_list pArgList )
{
    CHAR str[2048];
    // Use the secure CRT to avoid buffer overruns. Specify a count of
    // _TRUNCATE so that too long strings will be silently truncated
    // rather than triggering an error.
    _vsnprintf_s( str, _TRUNCATE, strFormat, pArgList );
    OutputDebugStringA( str );
}


//--------------------------------------------------------------------------------------
// Name: DebugSpew()
// Desc: Prints formatted debug spew
//--------------------------------------------------------------------------------------
#ifdef  _Printf_format_string_  // VC++ 2008 and later support this annotation
VOID CDECL DebugSpew( _In_z_ _Printf_format_string_ const CHAR* strFormat, ... )
#else
VOID CDECL DebugSpew( const CHAR* strFormat, ... )
#endif
{
    va_list pArgList;
    va_start( pArgList, strFormat );
    DebugSpewV( strFormat, pArgList );
    va_end( pArgList );
}


//--------------------------------------------------------------------------------------
// Name: FatalError()
// Desc: Prints formatted debug spew and breaks into the debugger. Exits the application.
//--------------------------------------------------------------------------------------
#ifdef  _Printf_format_string_  // VC++ 2008 and later support this annotation
VOID CDECL FatalError( _In_z_ _Printf_format_string_ const CHAR* strFormat, ... )
#else
VOID CDECL FatalError( const CHAR* strFormat, ... )
#endif
{
    va_list pArgList;
    va_start( pArgList, strFormat );
    DebugSpewV( strFormat, pArgList );
    va_end( pArgList );

    DebugBreak();

    exit(0);
}


} // namespace ATG
