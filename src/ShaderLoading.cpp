#include <d3d11.h>
#include <d3d11shader.h>
#include <d3dcompiler.h>

#include "Debug.h"
#include "ReadData.h"
#include "ShaderLoading.h"

namespace ShaderLoading
{
    int ReflectVShaderInputLayout(std::vector<uint8_t>& vShaderBytecode,
        ID3D11Device* dev, ID3D11InputLayout** outIL);

	int LoadVertexShader(std::string filename, ID3D11Device* dev,
		ID3D11VertexShader** outVS, ID3D11InputLayout** outIL)
	{
        HRESULT hr;
		auto shaderBytecode = DX::ReadData(std::wstring(filename.begin(), filename.end()).c_str());
		hr = dev->CreateVertexShader(
			shaderBytecode.data(), shaderBytecode.size(), NULL, outVS);

		if (FAILED(hr))
		{
			LOG("Failed to load vertex shader" + filename + ".");
			return hr;
		}

        hr = ReflectVShaderInputLayout(shaderBytecode, dev, outIL);
        if (FAILED(hr))
        {
            LOG("Failed to reflect vertex shader" + filename + ".");
            return hr;
        }

		return S_OK;
	}

	int LoadPixelShader(std::string filename, ID3D11Device* dev, ID3D11PixelShader** outPS)
	{
		auto shaderBytecode = DX::ReadData(std::wstring(filename.begin(), filename.end()).c_str());
		HRESULT hr = dev->CreatePixelShader(
			shaderBytecode.data(), shaderBytecode.size(), NULL, outPS);

		if (FAILED(hr))
		{
			LOG("Failed to load pixel shader" + filename + ".");
			return hr;
		}

		return S_OK;
	}

	int ReflectVShaderInputLayout(std::vector<uint8_t>& vShaderBytecode,
        ID3D11Device* dev, ID3D11InputLayout** outIL)
    {
        ID3D11ShaderReflection* vReflector = NULL;
        D3DReflect(vShaderBytecode.data(), vShaderBytecode.size(),
            IID_ID3D11ShaderReflection, (void**)&vReflector);

        D3D11_SHADER_DESC desc;
        vReflector->GetDesc(&desc);

        D3D11_SIGNATURE_PARAMETER_DESC* signatureParamDescriptions =
            new D3D11_SIGNATURE_PARAMETER_DESC[desc.InputParameters]{ 0 };
        for (UINT i = 0; i < desc.InputParameters; i++)
        {
            vReflector->GetInputParameterDesc(i, &signatureParamDescriptions[i]);
        }

        // Signature param desc masks as follows: float4 = 15, float3 = 7, float2 = 3, float[1] = 1. These are bitmasks 
        // To put together input layout from shader info it's something like this:
        D3D11_INPUT_ELEMENT_DESC* ied = new D3D11_INPUT_ELEMENT_DESC[desc.InputParameters]{ 0 };
        for (size_t i = 0; i < desc.InputParameters; i++)
        {
            ied[i].SemanticName = signatureParamDescriptions[i].SemanticName;
            ied[i].SemanticIndex = signatureParamDescriptions[i].SemanticIndex;
            if (signatureParamDescriptions[i].ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) {
                switch (signatureParamDescriptions[i].Mask) { // Yes I know this is ugly, trying to keep it compact and easily readable for this
                case 1:     ied[i].Format = DXGI_FORMAT_R32_FLOAT;          break; // float1
                case 3:     ied[i].Format = DXGI_FORMAT_R32G32_FLOAT;       break; // float2
                case 7:     ied[i].Format = DXGI_FORMAT_R32G32B32_FLOAT;    break; // float3
                case 15:    ied[i].Format = DXGI_FORMAT_R32G32B32A32_FLOAT; break; // float4
                default: break; // uh oh
                }
            } // The above only covers ---x, --yx, -zyx, wzyx. It may be possible
              //for a mask to be -yx- or yx-- or zyx- (6, 12, 14), but very unlikely
            ied[i].InputSlot = 0;
            ied[i].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
            ied[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
            ied[i].InstanceDataStepRate = 0;
        }

        HRESULT result = dev->CreateInputLayout(ied, desc.InputParameters,
            vShaderBytecode.data(), vShaderBytecode.size(), outIL);
        if (FAILED(result))
        {
            LOG("Failed to create input layout");
            return result;
        }

        delete[] signatureParamDescriptions;
        delete[] ied;

        return S_OK;
	}
}