//--------------------------------------------------------------------------------------
// File: Lab03.fx
//
// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License (MIT).
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
/*--------------------------------------------------------------------
  TODO: Vertex Shader function VS definition (remove the comment)
--------------------------------------------------------------------*/
float4 VS( float4 Pos : POSITION ) : SV_POSITION
{
    return Pos;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
/*--------------------------------------------------------------------
  TODO: Pixel Shader function PS definition (remove the comment)
--------------------------------------------------------------------*/
float4 PS( float4 Pos : SV_POSITION ) : SV_Target
{
    return float4( 1.0f, 1.0f, 0.0f, 1.0f );    // Yellow, with Alpha = 1
}