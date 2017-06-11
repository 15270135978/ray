// +----------------------------------------------------------------------
// | Project : ray.
// | All rights reserved.
// +----------------------------------------------------------------------
// | Copyright (c) 2013-2016.
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
// +-----------------------------------------------------------------------
#include "fimic.h"
#include <ray/material.h>

#include <ray/graphics_framebuffer.h>
#include <ray/graphics_texture.h>
#include <ray/render_pipeline.h>

_NAME_BEGIN

FimicToneMapping::Setting::Setting() noexcept
	: bloomThreshold(1.0f)
	, bloomIntensity(0.5f)
	, exposure(2.0f)
{
}

FimicToneMapping::FimicToneMapping() noexcept
{
}

FimicToneMapping::~FimicToneMapping() noexcept
{
}

void
FimicToneMapping::setSetting(const Setting& setting) noexcept
{
	_bloomThreshold->uniform1f(_setting.bloomThreshold);
	_bloomIntensity->uniform1f(_setting.bloomIntensity);

	_toneLumExposure->uniform1f(setting.exposure);

	_setting = setting;
}

const FimicToneMapping::Setting&
FimicToneMapping::getSetting() const noexcept
{
	return _setting;
}

void
FimicToneMapping::sumLum(RenderPipeline& pipeline, const GraphicsTexturePtr& source, const GraphicsFramebufferPtr& dest, std::uint8_t level) noexcept
{
	auto width = source->getGraphicsTextureDesc().getWidth();
	auto height = source->getGraphicsTextureDesc().getHeight();

	_texSource->uniformTexture(source);
	_texSourceLevel->uniform1i(level);
	_texSourceSizeInv->uniform2f(float(1 << level) / width, float(1 << level) / height);

	pipeline.setFramebuffer(dest);
	pipeline.discardFramebuffer(0);
	pipeline.drawScreenQuad(*_sumLum);
}

void
FimicToneMapping::sumLumLog(RenderPipeline& pipeline, const GraphicsTexturePtr& source, const GraphicsFramebufferPtr& dest) noexcept
{
	auto width = source->getGraphicsTextureDesc().getWidth();
	auto height = source->getGraphicsTextureDesc().getHeight();

	_texSource->uniformTexture(source);
	_texSourceSizeInv->uniform2f(1.0f / width, 1.0f / height);

	pipeline.setFramebuffer(dest);
	pipeline.discardFramebuffer(0);
	pipeline.drawScreenQuad(*_sumLumLog);
	pipeline.generateMipmap(dest->getGraphicsFramebufferDesc().getColorAttachment(0).getBindingTexture());
}

void
FimicToneMapping::avgLuminance(RenderPipeline& pipeline, const GraphicsTexturePtr& adaptedLum, const GraphicsTexturePtr& source, const GraphicsFramebufferPtr& dest) noexcept
{
	float width = source->getGraphicsTextureDesc().getWidth();
	float height = source->getGraphicsTextureDesc().getHeight();

	_timer->update();

	_texSource->uniformTexture(source);
	_texSourceSizeInv->uniform2f(1.0f / width, 1.0f / height);

	_texLumAve->uniformTexture(adaptedLum);

	_delta->uniform2f(1.0f - pow(0.98f, 50.0f * _timer->delta()), _timer->delta());

	pipeline.setFramebuffer(dest);
	pipeline.drawScreenQuad(*_avgLuminance);
}

void
FimicToneMapping::generateBloom(RenderPipeline& pipeline, const GraphicsTexturePtr& source, const GraphicsFramebufferPtr& dest) noexcept
{
	_texSource->uniformTexture(source);

	pipeline.setFramebuffer(dest);
	pipeline.discardFramebuffer(0);
	pipeline.drawScreenQuad(*_bloom);
	pipeline.generateMipmap(dest->getGraphicsFramebufferDesc().getColorAttachment(0).getBindingTexture());
}

void
FimicToneMapping::blurh(RenderPipeline& pipeline, const GraphicsTexturePtr& source, const GraphicsFramebufferPtr& dest, std::uint32_t level) noexcept
{
	_texSource->uniformTexture(source);
	_texSourceLevel->uniform1i(level);
	_texSourceSizeInv->uniform2f(float(1 << level) / source->getGraphicsTextureDesc().getWidth(), 0.0);

	pipeline.setFramebuffer(dest);
	pipeline.discardFramebuffer(0);
	pipeline.drawScreenQuad(*_blur);
}

void
FimicToneMapping::blurv(RenderPipeline& pipeline, const GraphicsTexturePtr& source, const GraphicsFramebufferPtr& dest, std::uint32_t level) noexcept
{
	_texSource->uniformTexture(source);
	_texSourceLevel->uniform1i(level);
	_texSourceSizeInv->uniform2f(0.0, float(1 << level) / source->getGraphicsTextureDesc().getHeight());

	pipeline.setFramebuffer(dest);
	pipeline.discardFramebuffer(0);
	pipeline.drawScreenQuad(*_blur);
}

void
FimicToneMapping::bloomCombine(RenderPipeline& pipeline, const GraphicsTexturePtr& source, const GraphicsFramebufferPtr& dest) noexcept
{
	_texSource->uniformTexture(source);

	pipeline.setFramebuffer(dest);
	pipeline.discardFramebuffer(0);
	pipeline.drawScreenQuad(*_bloomCombine);
}

void
FimicToneMapping::generateToneMapping(RenderPipeline& pipeline, const GraphicsTexturePtr& bloom, const GraphicsTexturePtr& source, const GraphicsFramebufferPtr& dest) noexcept
{
	_texSource->uniformTexture(source);
	_toneBloom->uniformTexture(bloom);

	pipeline.setFramebuffer(dest);
	pipeline.discardFramebuffer(0);
	pipeline.drawScreenQuad(*_tone);
}

void
FimicToneMapping::onActivate(RenderPipeline& pipeline) noexcept
{
	std::uint32_t width, height;
	pipeline.getWindowResolution(width, height);

	GraphicsTextureDesc samplerBloomDesc;
	samplerBloomDesc.setWidth(width / 2);
	samplerBloomDesc.setHeight(height / 2);
	samplerBloomDesc.setTexDim(GraphicsTextureDim::GraphicsTextureDim2D);
	samplerBloomDesc.setTexFormat(GraphicsFormat::GraphicsFormatR16G16B16A16SFloat);
	samplerBloomDesc.setMipBase(0);
	samplerBloomDesc.setMipNums(5);
	samplerBloomDesc.setSamplerWrap(GraphicsSamplerWrap::GraphicsSamplerWrapClampToEdge);
	samplerBloomDesc.setSamplerFilter(GraphicsSamplerFilter::GraphicsSamplerFilterLinearMipmapNearest, GraphicsSamplerFilter::GraphicsSamplerFilterLinearMipmapNearest);
	_texBloomMap = pipeline.createTexture(samplerBloomDesc);
	_texBloomTempMap = pipeline.createTexture(samplerBloomDesc);

	GraphicsTextureDesc samplerLogDesc;
	samplerLogDesc.setWidth(256);
	samplerLogDesc.setHeight(256);
	samplerLogDesc.setTexDim(GraphicsTextureDim::GraphicsTextureDim2D);
	samplerLogDesc.setTexFormat(GraphicsFormat::GraphicsFormatR16SFloat);
	samplerLogDesc.setMipBase(0);
	samplerLogDesc.setMipNums(9);
	samplerLogDesc.setSamplerWrap(GraphicsSamplerWrap::GraphicsSamplerWrapClampToEdge);
	samplerLogDesc.setSamplerFilter(GraphicsSamplerFilter::GraphicsSamplerFilterNearestMipmapNearest, GraphicsSamplerFilter::GraphicsSamplerFilterNearestMipmapNearest);
	_texSampleLogMap = pipeline.createTexture(samplerLogDesc);

	GraphicsTextureDesc samplerLumDesc;
	samplerLumDesc.setWidth(1);
	samplerLumDesc.setHeight(1);
	samplerLumDesc.setTexDim(GraphicsTextureDim::GraphicsTextureDim2D);
	samplerLumDesc.setTexFormat(GraphicsFormat::GraphicsFormatR32SFloat);
	samplerLumDesc.setSamplerFilter(GraphicsSamplerFilter::GraphicsSamplerFilterNearest, GraphicsSamplerFilter::GraphicsSamplerFilterNearest);
	samplerLumDesc.setSamplerWrap(GraphicsSamplerWrap::GraphicsSamplerWrapClampToEdge);
	_texSampleLumMap = pipeline.createTexture(samplerLumDesc);

	GraphicsFramebufferLayoutDesc framebufferBloomLayoutDesc;
	framebufferBloomLayoutDesc.addComponent(GraphicsAttachmentLayout(0, GraphicsImageLayout::GraphicsImageLayoutColorAttachmentOptimal, GraphicsFormat::GraphicsFormatR16G16B16A16SFloat));
	_sampleBloomImageLayout = pipeline.createFramebufferLayout(framebufferBloomLayoutDesc);

	GraphicsFramebufferLayoutDesc framebufferLogLayoutDesc;
	framebufferLogLayoutDesc.addComponent(GraphicsAttachmentLayout(0, GraphicsImageLayout::GraphicsImageLayoutColorAttachmentOptimal, GraphicsFormat::GraphicsFormatR16SFloat));
	_sampleLogImageLayout = pipeline.createFramebufferLayout(framebufferLogLayoutDesc);

	GraphicsFramebufferDesc sampleLogViewDesc;
	sampleLogViewDesc.setWidth(256);
	sampleLogViewDesc.setHeight(256);
	sampleLogViewDesc.addColorAttachment(GraphicsAttachmentBinding(_texSampleLogMap, 0, 0));
	sampleLogViewDesc.setGraphicsFramebufferLayout(_sampleLogImageLayout);
	_texSampleLogView = pipeline.createFramebuffer(sampleLogViewDesc);

	GraphicsFramebufferDesc sampleLog1ViewDesc;
	sampleLog1ViewDesc.setWidth(1);
	sampleLog1ViewDesc.setHeight(1);
	sampleLog1ViewDesc.addColorAttachment(GraphicsAttachmentBinding(_texSampleLumMap, 0, 0));
	sampleLog1ViewDesc.setGraphicsFramebufferLayout(_sampleLogImageLayout);
	_texSampleLumView = pipeline.createFramebuffer(sampleLog1ViewDesc);

	_texBloomView.resize(5);
	_texBloomTempView.resize(5);

	for (std::uint8_t i = 0; i < 5; i++)
	{
		GraphicsFramebufferDesc bloomViewDesc;
		bloomViewDesc.setWidth(width / ((2 << i)));
		bloomViewDesc.setHeight(height / ((2 << i)));
		bloomViewDesc.addColorAttachment(GraphicsAttachmentBinding(_texBloomMap, i, 0));
		bloomViewDesc.setGraphicsFramebufferLayout(_sampleBloomImageLayout);
		_texBloomView[i] = pipeline.createFramebuffer(bloomViewDesc);

		GraphicsFramebufferDesc bloomTempViewDesc;
		bloomTempViewDesc.setWidth(width / ((2 << i)));
		bloomTempViewDesc.setHeight(height / ((2 << i)));
		bloomTempViewDesc.addColorAttachment(GraphicsAttachmentBinding(_texBloomTempMap, i, 0));
		bloomTempViewDesc.setGraphicsFramebufferLayout(_sampleBloomImageLayout);
		_texBloomTempView[i] = pipeline.createFramebuffer(bloomTempViewDesc);
	}

	_fimic = pipeline.createMaterial("sys:fx/PostProcessBloom.fxml");
	assert(_fimic);

	_sumLum = _fimic->getTech("SumLum");
	_sumLumLog = _fimic->getTech("SumLumLog");
	_avgLuminance = _fimic->getTech("AvgLuminance");
	_bloom = _fimic->getTech("GenerateBloom");
	_blur = _fimic->getTech("BlurBloom");
	_bloomCombine = _fimic->getTech("BloomCombine");
	_tone = _fimic->getTech("FimicTongMapping");

	_bloomThreshold = _fimic->getParameter("bloomThreshold");
	_bloomIntensity = _fimic->getParameter("bloomIntensity");
	_bloomWeights = _fimic->getParameter("bloomWeights");
	_bloomFactors = _fimic->getParameter("bloomFactors");

	_toneBloom = _fimic->getParameter("texBloom");
	_toneLumExposure = _fimic->getParameter("exposure");

	_delta = _fimic->getParameter("delta");

	_texLumAve = _fimic->getParameter("texLumAve");
	_texSource = _fimic->getParameter("texSource");
	_texSourceSizeInv = _fimic->getParameter("texSourceSizeInv");
	_texSourceLevel = _fimic->getParameter("texSourceLevel");

	_texLumAve->uniformTexture(_texSampleLumMap);
	_toneLumExposure->uniform1f(_setting.exposure);

	float weights[] = { 0.048297,0.08393,0.124548,0.157829,0.170793,0.157829,0.124548,0.08393,0.048297 };
	float factors[] = { 0.341586,0.315658,0.249096,0.16786,0.096594 };

	_bloomWeights->uniform1fv(sizeof(weights) / sizeof(weights[0]), weights);
	_bloomFactors->uniform1fv(sizeof(factors) / sizeof(factors[0]), factors);

	_timer = std::make_shared<Timer>();
	_timer->open();

	this->setSetting(_setting);
}

void
FimicToneMapping::onDeactivate(RenderPipeline& pipeline) noexcept
{
	_timer.reset();
	_fimic.reset();
	_sumLum.reset();
	_sumLumLog.reset();
	_avgLuminance.reset();
	_bloom.reset();
	_blur.reset();
	_tone.reset();
	_bloomThreshold.reset();
	_bloomIntensity.reset();
	_bloomWeights.reset();
	_toneBloom.reset();
	_toneLumAve.reset();
	_toneLumKey.reset();
	_toneLumExposure.reset();
	_toneBurnout.reset();
	_toneDefocus.reset();
	_delta.reset();
	_texLumAve.reset();
	_texSource.reset();
	_texSourceSizeInv.reset();

	_texBloomView.clear();
	_texBloomTempView.clear();
	_texSampleLogView.reset();
	_texSampleLumView.reset();

	_texBloomMap.reset();
	_texBloomTempMap.reset();
	_texSampleLogMap.reset();
	_texSampleLumMap.reset();

	_sampleBloomImageLayout.reset();
	_sampleLogImageLayout.reset();
}

bool
FimicToneMapping::onRender(RenderPipeline& pipeline, RenderQueue queue, GraphicsFramebufferPtr& source, GraphicsFramebufferPtr swap) noexcept
{
	if (queue != RenderQueue::RenderQueuePostprocess)
		return false;

	auto texture = source->getGraphicsFramebufferDesc().getColorAttachment(0).getBindingTexture();

	this->sumLum(pipeline, texture, _texBloomTempView[0], 0);
	this->sumLumLog(pipeline, _texBloomTempMap, _texSampleLogView);

	this->avgLuminance(pipeline, _texSampleLumMap, _texSampleLogMap, _texSampleLumView);

	this->generateBloom(pipeline, _texBloomTempMap, _texBloomView[0]);

	for (std::uint8_t i = 0; i < 5; i++)
	{
		this->blurh(pipeline, _texBloomMap, _texBloomTempView[i], i);
		this->blurv(pipeline, _texBloomTempMap, _texBloomView[i], i);
		if (i < 4) this->sumLum(pipeline, _texBloomMap, _texBloomView[i + 1], i);
	}

	this->bloomCombine(pipeline, _texBloomMap, _texBloomTempView[0]);

	this->generateToneMapping(pipeline, _texBloomTempMap, texture, swap);

	return true;
}

_NAME_END