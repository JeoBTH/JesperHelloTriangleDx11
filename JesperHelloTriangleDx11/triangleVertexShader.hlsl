struct Input
{
    float2 pos : POSITION;
    float3 color : COLOR;
};

struct Output
{
    float4 position : SV_Position;
    float3 color : COLOR;
};

Output main(Input input) 
{
    
    Output output;
    
    output.position = float4(input.pos.x, input.pos.y, 0, 1);
    output.color = input.color;
    
    return output;
    
}