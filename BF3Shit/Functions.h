#pragma once

bool WorldToScreen(Vector3 WorldPos, Vector3 * ScreenPos);

ClientPlayer * GetLocalPlayer();

ClientPlayer * GetPlayerById(unsigned int id);

bool IsLocalClientAlive();

bool IsClientAlive(ClientPlayer * pTarget);

void DrawCompass(Vector3 ClientPosition, D3DCOLOR Color, float CompassSize);

Vector3 Multiply(Vector3 vec, Matrix * mat);

bool Draw2DBox(ClientVehicleEntity * pEnt, D3DCOLOR color, float size);

bool TransformDrawAABB(ClientVehicleEntity * pEnt, D3DCOLOR color, float size);

bool DrawESP();
