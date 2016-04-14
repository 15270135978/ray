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
// +----------------------------------------------------------------------
#include "vk_memory.h"
#include "vk_device.h"
#include "vk_system.h"

_NAME_BEGIN

VulkanMemory::VulkanMemory() noexcept
	: _vkMemory(VK_NULL_HANDLE)
	, _isMapping(false)
	, _size(0)
{
}

VulkanMemory::~VulkanMemory() noexcept
{
	this->close();
}

bool
VulkanMemory::setup(const char* stream, std::uint32_t streamSize, std::uint32_t typeBits, std::uint32_t mask) noexcept
{
	assert(streamSize > 0);

	VkMemoryAllocateInfo memInfo;
	memInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	memInfo.pNext = nullptr;
	memInfo.allocationSize = streamSize;
	memInfo.memoryTypeIndex = 0;

	VkPhysicalDeviceMemoryProperties memoryProperties;
	vkGetPhysicalDeviceMemoryProperties(this->getDevice()->downcast<VulkanDevice>()->getPhysicsDevice(), &memoryProperties);

	memory_type_from_properties(memoryProperties.memoryTypes, typeBits, mask, &memInfo.memoryTypeIndex);

	if (vkAllocateMemory(this->getDevice()->downcast<VulkanDevice>()->getDevice(), &memInfo, nullptr, &_vkMemory) > 0)
	{
		VK_PLATFORM_LOG("vkAllocateMemory() fail.");
		return false;
	}

	_size = streamSize;
	if (stream)
	{
		void* data = this->map(GraphicsAccessFlagsBits::GraphicsAccessFlagsMapReadBit);
		if (data)
		{
			std::memcpy(data, stream, streamSize);
			this->unmap();
		}
	}

	return true;
}

void 
VulkanMemory::close() noexcept
{
	if (_vkMemory != VK_NULL_HANDLE)
	{
		vkFreeMemory(this->getDevice()->downcast<VulkanDevice>()->getDevice(), _vkMemory, nullptr);
		_size = 0;
		_vkMemory = VK_NULL_HANDLE;
	}
}

std::uint32_t 
VulkanMemory::size() const noexcept
{
	return _size;
}

void*
VulkanMemory::map(std::uint32_t access) noexcept
{
	return this->map(0, this->size(), access);
}

void*
VulkanMemory::map(std::uint32_t offset, std::uint32_t cnt, std::uint32_t access) noexcept
{
	assert(!_isMapping);
	assert(_vkMemory != VK_NULL_HANDLE);

	void* data = nullptr;
	if (vkMapMemory(this->getDevice()->downcast<VulkanDevice>()->getDevice(), _vkMemory, offset, cnt, 0, &data) != VK_SUCCESS)
		return false;

	_isMapping = true;
	return data;
}

void 
VulkanMemory::unmap() noexcept
{
	assert(_isMapping);
	assert(_vkMemory != VK_NULL_HANDLE);

	_isMapping = false;
	vkUnmapMemory(this->getDevice()->downcast<VulkanDevice>()->getDevice(), _vkMemory);
}

VkDeviceMemory
VulkanMemory::getDeviceMemory() const noexcept
{
	return _vkMemory;
}

void
VulkanMemory::setDevice(GraphicsDevicePtr device) noexcept
{
	_device = device;
}

GraphicsDevicePtr
VulkanMemory::getDevice() noexcept
{
	return _device.lock();
}

bool
VulkanMemory::memory_type_from_properties(VkMemoryType memoryTypes[], uint32_t typeBits, VkFlags requirements_mask, uint32_t *typeIndex)
{
	// Search memtypes to find first index with those properties
	for (uint32_t i = 0; i < 32; i++)
	{
		if ((typeBits & 1) == 1)
		{
			// Type is available, does it match user properties?
			if ((memoryTypes[i].propertyFlags & requirements_mask) == requirements_mask)
			{
				*typeIndex = i;
				return true;
			}
		}
		typeBits >>= 1;
	}
	// No memory types matched, return failure
	return false;
}

_NAME_END