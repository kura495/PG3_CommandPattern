#include"Particle.hlsli"
struct ParticleGPU
{
    float32_t4x4 matWorld;
    float32_t3 velocity;
    float32_t4 color;
    float32_t lifeTime;
    float32_t currentTime;
    float32_t3 translate;
};
struct ViewProjectionMatrix
{
    float32_t4x4 view;
    float32_t4x4 projection;
    float32_t3 cameraPos;
};                                                                                                                                                                       
StructuredBuffer<ParticleGPU> gParticle : register(t0);
ConstantBuffer<ViewProjectionMatrix> gViewProjectionMatrix : register(b1);
struct VertexShaderInput
{
    float32_t4 position : POSITION0;
    float32_t2 texcoord : TEXCOORD0;
    float32_t3 normal : NORMAL0;
};

VertexShaderOutput main(VertexShaderInput input ,uint32_t instanceId : SV_InstanceID)
{
    VertexShaderOutput output;
    float32_t4x4 WorldViewProjectionMatrix = mul(gViewProjectionMatrix.view, gViewProjectionMatrix.projection);
    output.position = mul(input.position, mul(gParticle[instanceId].matWorld, WorldViewProjectionMatrix));
    output.texcoord = input.texcoord;
    output.color = gParticle[instanceId].color;
    return output;
}