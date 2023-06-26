#include "framework.h"
#include "SRV.h"

SRV::SRV(wstring path)
{
	ScratchImage img;
	LoadFromWICFile(path.c_str(), WIC_FLAGS_NONE, nullptr, img);
	
	_imgSize.x = img.GetMetadata().width;
	_imgSize.y = img.GetMetadata().height;

	CreateShaderResourceView(DEVICE.Get(), img.GetImages(),
		img.GetImageCount(), img.GetMetadata(), _srv.GetAddressOf());
}

void SRV::SetSRV(UINT slot)
{
	DC->PSSetShaderResources(slot, 1, _srv.GetAddressOf());
}