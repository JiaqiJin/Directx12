#include "Cube.hlsli"

float4 PS(VertexOut pin) : SV_Target
{
    return pin.Color;
}