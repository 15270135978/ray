// +----------------------------------------------------------------------
// | Project : ray.
// | All rights reserved.
// +----------------------------------------------------------------------
// | Copyright (c) 2013-2015.
// +----------------------------------------------------------------------
// | * Redistribution and use of this software in source and binary forms,
// |   with or without modification, are permitted provided that the following
// |   conditions are met:
// |
// | * Redistributions of source code must retain the above
// |   copyright notice, this list of conditions and the
// |   following disclaimer.
// |
// | * Redistributions in binary form must reproduce the above
// |   copyright notice, this list of conditions and the
// |   following disclaimer in the documentation and/or other
// |   materials provided with the distribution.
// |
// | * Neither the name of the ray team, nor the names of its
// |   contributors may be used to endorse or promote products
// |   derived from this software without specific prior
// |   written permission of the ray team.
// |
// | THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// | "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// | LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// | A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// | OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// | SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// | LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// | DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// | THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// | (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// | OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// +----------------------------------------------------------------------
#ifndef _H_IMAGE_TYPES_H_
#define _H_IMAGE_TYPES_H_

#include <ray/imagdef.h>
#include <ray/iostream.h>

_NAME_BEGIN

namespace image
{

enum class format_t : uint8_t
{
	Undefined,
	R4G4UNormPack8,
	R4G4B4A4UNormPack16,
	B4G4R4A4UNormPack16,
	R5G6B5UNormPack16,
	B5G6R5UNormPack16,
	R5G5B5A1UNormPack16,
	B5G5R5A1UNormPack16,
	A1R5G5B5UNormPack16,
	L8UNorm,
	L8SNorm,
	L8UScaled,
	L8SScaled,
	L8UInt,
	L8SInt,
	L8SRGB,
	A8UNorm,
	A8SNorm,
	A8UScaled,
	A8SScaled,
	A8UInt,
	A8SInt,
	A8SRGB,
	R8UNorm,
	R8SNorm,
	R8UScaled,
	R8SScaled,
	R8UInt,
	R8SInt,
	R8SRGB,
	L8A8UNorm,
	L8A8SNorm,
	L8A8UScaled,
	L8A8SScaled,
	L8A8UInt,
	L8A8SInt,
	L8A8SRGB,
	R8G8UNorm,
	R8G8SNorm,
	R8G8UScaled,
	R8G8SScaled,
	R8G8UInt,
	R8G8SInt,
	R8G8SRGB,
	R8G8B8UNorm,
	R8G8B8SNorm,
	R8G8B8UScaled,
	R8G8B8SScaled,
	R8G8B8UInt,
	R8G8B8SInt,
	R8G8B8SRGB,
	B8G8R8UNorm,
	B8G8R8SNorm,
	B8G8R8UScaled,
	B8G8R8SScaled,
	B8G8R8UInt,
	B8G8R8SInt,
	B8G8R8SRGB,
	R8G8B8A8UNorm,
	R8G8B8A8SNorm,
	R8G8B8A8UScaled,
	R8G8B8A8SScaled,
	R8G8B8A8UInt,
	R8G8B8A8SInt,
	R8G8B8A8SRGB,
	B8G8R8A8UNorm,
	B8G8R8A8SNorm,
	B8G8R8A8UScaled,
	B8G8R8A8SScaled,
	B8G8R8A8UInt,
	B8G8R8A8SInt,
	B8G8R8A8SRGB,
	A8B8G8R8UNormPack32,
	A8B8G8R8SNormPack32,
	A8B8G8R8UScaledPack32,
	A8B8G8R8SScaledPack32,
	A8B8G8R8UIntPack32,
	A8B8G8R8SIntPack32,
	A8B8G8R8SRGBPack32,
	A2R10G10B10UNormPack32,
	A2R10G10B10SNormPack32,
	A2R10G10B10UScaledPack32,
	A2R10G10B10SScaledPack32,
	A2R10G10B10UIntPack32,
	A2R10G10B10SIntPack32,
	A2B10G10R10UNormPack32,
	A2B10G10R10SNormPack32,
	A2B10G10R10UScaledPack32,
	A2B10G10R10SScaledPack32,
	A2B10G10R10UIntPack32,
	A2B10G10R10SIntPack32,
	L16UNorm,
	L16SNorm,
	L16UScaled,
	L16SScaled,
	L16UInt,
	L16SInt,
	L16SFloat,
	A16UNorm,
	A16SNorm,
	A16UScaled,
	A16SScaled,
	A16UInt,
	A16SInt,
	A16SFloat,
	R16UNorm,
	R16SNorm,
	R16UScaled,
	R16SScaled,
	R16UInt,
	R16SInt,
	R16SFloat,
	L16A16UNorm,
	L16A16SNorm,
	L16A16UScaled,
	L16A16SScaled,
	L16A16UInt,
	L16A16SInt,
	L16A16SRGB,
	R16G16UNorm,
	R16G16SNorm,
	R16G16UScaled,
	R16G16SScaled,
	R16G16UInt,
	R16G16SInt,
	R16G16SFloat,
	R16G16B16UNorm,
	R16G16B16SNorm,
	R16G16B16UScaled,
	R16G16B16SScaled,
	R16G16B16UInt,
	R16G16B16SInt,
	R16G16B16SFloat,
	R16G16B16A16UNorm,
	R16G16B16A16SNorm,
	R16G16B16A16UScaled,
	R16G16B16A16SScaled,
	R16G16B16A16UInt,
	R16G16B16A16SInt,
	R16G16B16A16SFloat,
	R32UInt,
	R32SInt,
	R32SFloat,
	R32G32UInt,
	R32G32SInt,
	R32G32SFloat,
	R32G32B32UInt,
	R32G32B32SInt,
	R32G32B32SFloat,
	R32G32B32A32UInt,
	R32G32B32A32SInt,
	R32G32B32A32SFloat,
	R64UInt,
	R64SInt,
	R64SFloat,
	R64G64UInt,
	R64G64SInt,
	R64G64SFloat,
	R64G64B64UInt,
	R64G64B64SInt,
	R64G64B64SFloat,
	R64G64B64A64UInt,
	R64G64B64A64SInt,
	R64G64B64A64SFloat,
	B10G11R11UFloatPack32,
	E5B9G9R9UFloatPack32,
	D16UNorm,
	X8_D24UNormPack32,
	D32_SFLOAT,
	S8UInt,
	D16UNorm_S8UInt,
	D24UNorm_S8UInt,
	D32_SFLOAT_S8UInt,
	BC1RGBUNormBlock,
	BC1RGBSRGBBlock,
	BC1RGBAUNormBlock,
	BC1RGBASRGBBlock,
	BC2UNormBlock,
	BC2SRGBBlock,
	BC3UNormBlock,
	BC3SRGBBlock,
	BC4UNormBlock,
	BC4SNormBlock,
	BC5UNormBlock,
	BC5SNormBlock,
	BC6HUFloatBlock,
	BC6HSFloatBlock,
	BC7UNormBlock,
	BC7SRGBBlock,
	ETC2R8G8B8UNormBlock,
	ETC2R8G8B8SRGBBlock,
	ETC2R8G8B8A1UNormBlock,
	ETC2R8G8B8A1SRGBBlock,
	ETC2R8G8B8A8UNormBlock,
	ETC2R8G8B8A8SRGBBlock,
	EACR11UNormBlock,
	EACR11SNormBlock,
	EACR11G11UNormBlock,
	EACR11G11SNormBlock,
	ASTC4x4UNormBlock,
	ASTC4x4SRGBBlock,
	ASTC5x4UNormBlock,
	ASTC5x4SRGBBlock,
	ASTC5x5UNormBlock,
	ASTC5x5SRGBBlock,
	ASTC6x5UNormBlock,
	ASTC6x5SRGBBlock,
	ASTC6x6UNormBlock,
	ASTC6x6SRGBBlock,
	ASTC8x5UNormBlock,
	ASTC8x5SRGBBlock,
	ASTC8x6UNormBlock,
	ASTC8x6SRGBBlock,
	ASTC8x8UNormBlock,
	ASTC8x8SRGBBlock,
	ASTC10x5UNormBlock,
	ASTC10x5SRGBBlock,
	ASTC10x6UNormBlock,
	ASTC10x6SRGBBlock,
	ASTC10x8UNormBlock,
	ASTC10x8SRGBBlock,
	ASTC10x10UNormBlock,
	ASTC10x10SRGBBlock,
	ASTC12x10UNormBlock,
	ASTC12x10SRGBBlock,
	ASTC12x12UNormBlock,
	ASTC12x12SRGBBlock,
	BeginRange = Undefined,
	EndRange = ASTC12x12SRGBBlock,
	RangeSize = (EndRange - BeginRange + 1),
};

enum class swizzle_t : uint8_t
{
	R,
	RG,
	RGB,
	BGR,
	RGBA,
	BGRA,
	ABGR,
	Depth,
	Stencil,
	DepthStencil,
	BeginRange = R,
	EndRange = DepthStencil,
	RangeSize = (EndRange - BeginRange + 1),
};

enum class value_t : std::uint8_t
{
	Null,
	SNorm,
	UNorm,
	UNorm5_6_5,
	UNorm5_5_5_1,
	UNorm1_5_5_5,
	UNorm2_10_10_10,
	UFloatB10G11R11Pack32,
	UFloatE5B9G9R9Pack32,
	SScaled,
	UScaled,
	SInt,
	UInt,
	SRGB,
	Float,
	D16UNorm_S8UInt,
	D24UNorm_S8UInt,
	D24UNormPack32,
	D32_SFLOAT_S8UInt,
	Compressed,
	BeginRange = SNorm,
	EndRange = Compressed,
	RangeSize = (EndRange - BeginRange + 1),
};

typedef std::shared_ptr<class Image> ImagePtr;
typedef std::shared_ptr<class ImageHandler> ImageHandlerPtr;

}

_NAME_END

#endif