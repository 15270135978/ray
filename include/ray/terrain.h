// +----------------------------------------------------------------------
// | Project : ray.
// | All rights reserved.
// +----------------------------------------------------------------------
// | Copyright (c) 2013-2017.
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
#ifndef _H_TERRAIN_H_
#define _H_TERRAIN_H_

#include <ray/terrain_chunk.h>
#include <ray/terrain_observer.h>

_NAME_BEGIN

class Terrain final
{
public:
	typedef std::vector<TerrainChunkPtr>::iterator ChunkIteraotr;

public:
	Terrain() noexcept;
	~Terrain() noexcept;

	void addObServer(TerrainObserverPtr observer) noexcept;
	void removeObServer(TerrainObserverPtr observer) noexcept;

	void computeVisiable(TerrainObserverPtr observer, std::vector<TerrainChunkPtr>& chunks) noexcept;

	void update() noexcept;

private:

	int convChunked(float x);

	void createChunks();
	void destroyChunks();

	TerrainChunkPtr find(int q, int p);

private:

	int _chunkSize;

	int _radiusRender;
	int _radiusDestroy;
	int _radiusCreate;

	std::vector<TerrainChunkPtr> _chunks;
	std::vector<TerrainObserverPtr> _observer;
};

_NAME_END

#endif