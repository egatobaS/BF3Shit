//--------------------------------------------------------------------------------------
// AtgApp.cpp
//
// Application class for samples
//
// Xbox Advanced Technology Group.
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include "stdafx.h"
#include "AtgApp.h"
#include "AtgUtil.h"

// Ignore warning about "unused" pD3D variable
#pragma warning( disable: 4189 )

namespace ATG
{

//--------------------------------------------------------------------------------------
// Globals
//--------------------------------------------------------------------------------------

// Global access to the main D3D device
D3DDevice* g_pd3dDevice = NULL;

} // namespace ATG
