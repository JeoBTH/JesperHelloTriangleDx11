#pragma once
#include "Renderer.h"
#include <fstream>
#include <vector>

using namespace std;

class Triangle
{
private:
	ID3D11Buffer* m_vertexBuffer = nullptr;
	ID3D11VertexShader* m_vertexShader = nullptr;
	ID3D11PixelShader* m_pixelShader = nullptr;
	ID3D11InputLayout* m_inputLayout = nullptr;
	void createMesh(Renderer& renderer);
	void createShader(Renderer& renderer);


public:
	Triangle(Renderer& renderer);
	~Triangle();
	void draw(Renderer& renderer);



};
