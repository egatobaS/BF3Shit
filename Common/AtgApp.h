//--------------------------------------------------------------------------------------
// AtgApp.h
//
// Application class for samples
//
// Xbox Advanced Technology Group.
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#pragma once
#ifndef ATGAPP_H
#define ATGAPP_H

// Use the overloaded D3DDevice class

// Disable warning C4324: structure padded due to __declspec(align())
// Warning C4324 comes up often in samples derived from the Application class, since 
// they use XMVECTOR, XMMATRIX, and other member data types that must be aligned.
#pragma warning( disable:4324 )

namespace ATG
{

// Global access to the main D3D device
extern D3DDevice* g_pd3dDevice;


} // namespace ATG

#endif // ATGAPP_H
