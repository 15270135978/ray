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
#include <ray/game_scene.h>
#include <ray/game_scene_manager.h>
#include <ray/game_listener.h>
#include <ray/game_component.h>

#include <ray/rtti_factory.h>

#include <ray/jsonreader.h>

_NAME_BEGIN

__ImplementSubClass(GameScene, rtti::Interface, "GameScene")

GameScene::RootObject::RootObject(GameScene* scene) noexcept
	: _scene(scene)
{
	assert(scene);
}

GameScene::RootObject::~RootObject() noexcept
{
}

GameScene*
GameScene::RootObject::getGameScene() noexcept
{
	return _scene;
}

const GameScene*
GameScene::RootObject::getGameScene() const noexcept
{
	return _scene;
}

GameScene::GameScene() noexcept
	: _root(std::make_unique<RootObject>(this))
{
	GameSceneManager::instance()->_instanceScene(this, _instanceID);
}

GameScene::GameScene(const util::string& name) noexcept
	: _name(name)
{
	GameSceneManager::instance()->_instanceScene(this, _instanceID);
}

GameScene::~GameScene() noexcept
{
	assert(_root.unique());

	this->setActive(false);
	_root.unique();

	GameSceneManager::instance()->_unsetScene(this);
}

void
GameScene::setActive(bool active) except
{
	if (this->getActive() != active)
	{
		GameSceneManager::instance()->_activeScene(this, active);

		_root->setActiveDownwards(active);
	}
}

bool
GameScene::getActive() const noexcept
{
	return _root->getActive();
}

void
GameScene::setGameListener(const GameListenerPtr& listener) noexcept
{
	if (_gameListener != listener)
		_gameListener = listener;
}

GameListenerPtr
GameScene::getGameListener() const noexcept
{
	return _gameListener;
}

void
GameScene::setName(util::string&& name) noexcept
{
	_name = std::move(name);
}

void
GameScene::setName(const util::string& name) noexcept
{
	_name = name;
}

const util::string&
GameScene::getName() const noexcept
{
	return _name;
}

std::size_t
GameScene::getInstanceID() const noexcept
{
	return _instanceID;
}

GameObjectPtr
GameScene::getRootObject() const noexcept
{
	return _root;
}

void
GameScene::sendMessage(const MessagePtr& message) except
{
	if (this->getActive())
	{
		auto root = this->getRootObject();
		if (root)
		{
			auto childrens = root->getChildren();
			for (auto& child : childrens)
				child->sendMessageDownwards(message);
		}
	}
}

bool
GameScene::load(const util::string& sceneURL) noexcept
{
	assert(!sceneURL.empty());

	try
	{
		StreamReaderPtr stream;
		if (!IoServer::instance()->openFileURL(stream, sceneURL, ios_base::in))
		{
			if (_gameListener)
				_gameListener->onMessage("Failed to open file : " + sceneURL);

			return false;
		}

		JsonReader reader(*stream);
		if (!reader.is_object())
		{
			if (_gameListener)
				_gameListener->onMessage("Non readable Scene file : " + sceneURL);

			return false;
		}

		return this->load(reader);
	}
	catch (const exception& e)
	{
		if (_gameListener)
			_gameListener->onMessage(e.what());

		return false;
	}
}

bool
GameScene::load(const iarchive& reader) noexcept
{
	try
	{
		const auto& scene = reader["scene"];
		if (!scene.is_object())
		{
			if (_gameListener)
				_gameListener->onMessage("scene is not a object type");

			return false;
		}

		const auto& sceneName = scene["name"];
		if (sceneName.is_string())
			this->setName(scene["name"].get<archive::string_t>());

		const auto& objects = scene["objects"];
		if (!objects.is_array())
		{
			if (_gameListener)
				_gameListener->onMessage("objects is not a array type");

			return false;
		}

		const auto& objectValues = objects.get<archive::array_t>();
		for (auto& object : objectValues)
		{
			if (!object.is_object())
				continue;

			auto actor = std::make_shared<GameObject>();
			actor->setParent(_root);
			actor->load(object);

			auto& components = object["components"];
			if (!components.is_array())
			{
				if (_gameListener)
					_gameListener->onMessage("components is not a array type");

				continue;
			}

			const auto& componentValues = components.get<archive::array_t>();
			for (auto& component : componentValues)
			{
				auto& className = component["class"].get<archive::string_t>();
				if (className.empty())
				{
					if (_gameListener)
						_gameListener->onMessage("Component class entry cannot be empty.");

					continue;
				}

				try
				{
					auto actorComponent = rtti::make_shared<GameComponent>(className);
					if (!actorComponent)
					{
						if (_gameListener)
							_gameListener->onMessage("Failed to create component : " + className);

						continue;
					}

					actorComponent->load(component);

					actor->addComponent(actorComponent);
				}
				catch (const std::exception& e)
				{
					if (_gameListener)
						_gameListener->onMessage("Failed to create component " + className + " with game object  " + actor->getName() + " : \n" + e.what());

					return false;
				}
			}
		}

		return true;
	}
	catch (const std::exception& e)
	{
		if (_gameListener)
			_gameListener->onMessage(e.what());

		return false;
	}
}

bool
GameScene::save(oarchive& reader) noexcept
{
	return false;
}

bool
GameScene::save(const util::string& sceneURL) noexcept
{
	return false;
}

GameScenePtr
GameScene::clone() const noexcept
{
	auto scene = std::make_shared<GameScene>();
	scene->setName(this->getName());
	scene->_root = _root->clone();
	return scene;
}

_NAME_END