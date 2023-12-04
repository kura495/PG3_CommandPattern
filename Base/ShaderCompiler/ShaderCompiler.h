#pragma once

#include "Base/DirectXCommon.h"

class ShaderCompiler
{
public:

	static ShaderCompiler* GetInstance();

	void Initalize();
	IDxcBlob* CompileShader(const std::wstring& filePath, const wchar_t* profile);

private:
	ShaderCompiler() = default;
	~ShaderCompiler() = default;
	ShaderCompiler(const ShaderCompiler& obj) = delete;
	ShaderCompiler& operator=(const ShaderCompiler& obj) = delete;

	void MakeDXC();
	
	HRESULT hr;

	IDxcUtils* dxcUtils = nullptr;
	IDxcCompiler3* dxcCompiler = nullptr;
	IDxcIncludeHandler* includeHandler = nullptr;

	IDxcBlob* shaderBlob = nullptr;
	IDxcBlobUtf8* shaderError = nullptr;
};