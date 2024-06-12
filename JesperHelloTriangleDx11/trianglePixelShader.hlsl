struct Input
{
    float4 position : SV_Position;
    float3 color : COLOR;
};

float4 main(Input input) : SV_TARGET
{
    return float4(input.color.r,input.color.g,input.color.b,1);
}