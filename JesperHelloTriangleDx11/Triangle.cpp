#include "Triangle.h"

struct Vertex
{
	float x, y;
	float r, g, b;
};

void Triangle::createMesh(Renderer& renderer)
{
	// Define our vertices
	Vertex vertices[] = {
		{-1.f,-1.f, 1.f,0.f,0.f},
		{0.f,1.f, 0.f,1.f,0.f},
		{1.f,-1.f, 0.f,0.f,1.f}
	};

	// Create our Vertex Buffer Descriptor
	// Move our vertices from RAM to VRAM
	auto vertexBufferDesc = CD3D11_BUFFER_DESC(sizeof(vertices), D3D11_BIND_VERTEX_BUFFER); // how much byte to take
	D3D11_SUBRESOURCE_DATA vertexData = { 0 };
	vertexData.pSysMem = vertices; // where to take
	// Create our Vertex Buffer
	renderer.getDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
}

void Triangle::createShader(Renderer& renderer)
{
	// Create Shaders
	ifstream vsFile("triangleVertexShader.cso", ios::binary);
	ifstream psFile("trianglePixelShader.cso", ios::binary);

	vector<char> vsData = { istreambuf_iterator<char>(vsFile), istreambuf_iterator <char>() };
	vector<char> psData = { istreambuf_iterator<char>(psFile), istreambuf_iterator <char>() };

	renderer.getDevice()->CreateVertexShader(vsData.data(), vsData.size(), nullptr, &this->m_vertexShader);
	renderer.getDevice()->CreatePixelShader(psData.data(), psData.size(), nullptr, &this->m_pixelShader);

	// Create Input Layouts
	// You need thís to bridge your data to your vertex shader
	// D3D11_APPEND_ALIGNED_ELEMENT, offset the necessary bytes based on the previous line. In this case 8 bytes, since the pos consist of two floats
	D3D11_INPUT_ELEMENT_DESC layout[]{ {"POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0} };

	renderer.getDevice()->CreateInputLayout(layout, 2, vsData.data(), vsData.size(), &m_inputLayout);



}

Triangle::Triangle(Renderer& renderer)
{
	createMesh(renderer);
	createShader(renderer);
}

Triangle::~Triangle()
{
	m_vertexBuffer->Release();
	m_vertexShader->Release();
	m_pixelShader->Release();
	m_inputLayout->Release();
}

void Triangle::draw(Renderer& renderer)
{
	// Bind our shaders
	// Bind input assembler
	renderer.getDeviceContext()->IASetInputLayout(m_inputLayout);
	renderer.getDeviceContext()->VSSetShader(m_vertexShader, nullptr, 0);
	renderer.getDeviceContext()->PSSetShader(m_pixelShader, nullptr, 0);




	// Bind our Vertex Buffer 
	// stride is the size between each vertex, when im done with that point, how much in memory do i have to go until i reach the next one
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	renderer.getDeviceContext()->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset); // why pointers, because you can set two buffers, then you'd have an array of offet[] = [0,0}; which is automatically treated as a pointer when passed through. Single / Due support

	renderer.getDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Draw
	renderer.getDeviceContext()->Draw(3, 0);


}
