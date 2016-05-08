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
#include <ray/game_object.h>
#include <ray/game_object_manager.h>
#include <ray/game_component.h>

_NAME_BEGIN

__ImplementSubClass(GameObject, rtti::Interface, "Object")

GameObject::GameObject() noexcept
	: _active(true)
	, _layer(0)
	, _needUpdates(true)
	, _scaling(float3::One)
	, _translate(float3::Zero)
	, _quat(Quaternion::Zero)
	, _euler(float3::Zero)
	, _right(float3::Right)
	, _up(float3::Up)
	, _forward(float3::Forward)
{
	GameObjectManager::instance()->_instanceObject(this, _instanceID);
	GameObjectManager::instance()->_activeObject(this, true);
}

GameObject::~GameObject() noexcept
{
	this->cleanupChildren();
	this->cleanupComponents();

	GameObjectManager::instance()->_unsetObject(this);
}

void
GameObject::setName(const std::string& name) noexcept
{
	_name = name;
}

void
GameObject::setName(std::string&& name) noexcept
{
	_name = std::move(name);
}

const std::string&
GameObject::getName() const noexcept
{
	return _name;
}

void
GameObject::setActive(bool active) except
{
	if (_active != active)
	{
		GameObjectManager::instance()->_activeObject(this, active);

		for (auto& it : _components)
		{
			if (active)
			{
				if (it->getActive())
					it->onActivate();
			}
			else
			{
				if (it->getActive())
					it->onDeactivate();
			}
		}

		_active = active;
	}
}

void
GameObject::setActiveUpwards(bool active) except
{
	if (_active != active)
	{
		for (auto& it : _components)
		{
			if (active)
			{
				if (it->getActive())
					it->onActivate();
			}
			else
			{
				if (it->getActive())
					it->onDeactivate();
			}
		}

		auto parent = this->getParent();
		if (parent)
			parent->setActiveUpwards(active);

		_active = active;
	}
}

void
GameObject::setActiveDownwards(bool active) except
{
	if (_active != active)
	{
		for (auto& it : _components)
		{
			if (active)
			{
				if (it->getActive())
					it->onActivate();
			}
			else
			{
				if (it->getActive())
					it->onDeactivate();
			}
		}

		for (auto& it : _children)
			it->setActiveDownwards(true);

		_active = active;
	}
}

bool
GameObject::getActive() const noexcept
{
	return _active;
}

void
GameObject::setLayer(std::uint8_t layer) noexcept
{
	if (_layer != layer)
	{
		for (auto& it : _components)
		{
			if (it->getActive())
				it->onLayerChangeBefore();
		}

		_layer = layer;

		for (auto& it : _components)
		{
			if (it->getActive())
				it->onLayerChangeAfter();
		}
	}
}

std::uint8_t
GameObject::getLayer() const noexcept
{
	return _layer;
}

std::uint32_t
GameObject::getInstanceID() const noexcept
{
	return _instanceID;
}

void
GameObject::setParent(GameObjectPtr& parent) noexcept
{
	assert(this != parent.get());

	auto _weak = _parent.lock();
	if (_weak != parent)
	{
		for (auto& it : _components)
			it->onParentChangeBefore();

		if (_weak)
		{
			auto it = _weak->_children.begin();
			auto end = _weak->_children.end();

			for (; it != end; ++it)
			{
				if ((*it).get() == this)
				{
					_weak->_children.erase(it);
					break;
				}
			}
		}

		_parent = parent;
		if (parent)
			parent->_children.push_back(this->cast<GameObject>());

		for (auto& it : _components)
			it->onParentChangeAfter();
	}
}

void
GameObject::setParent(GameObjectPtr&& parent) noexcept
{
	this->setParent(parent);
}

GameObjectPtr
GameObject::getParent() const noexcept
{
	return _parent.lock();
}

void
GameObject::addChild(GameObjectPtr& entity) noexcept
{
	assert(entity);
	entity->setParent(std::dynamic_pointer_cast<GameObject>(this->shared_from_this()));
}

void
GameObject::addChild(GameObjectPtr&& entity) noexcept
{
	assert(entity);
	entity->setParent(std::dynamic_pointer_cast<GameObject>(this->shared_from_this()));
}

void
GameObject::removeChild(GameObjectPtr& entity) noexcept
{
	assert(entity);

	auto it = _children.begin();
	auto end = _children.end();
	for (; it != end; ++it)
	{
		if ((*it) == entity)
		{
			(*it)->setParent(nullptr);
			break;
		}
	}

	if (it != end)
	{
		_children.erase(it);
	}
}

void
GameObject::removeChild(GameObjectPtr&& entity) noexcept
{
	this->removeChild(entity);
}

void
GameObject::cleanupChildren() noexcept
{
	for (auto& it : _children)
		it.reset();

	_children.clear();
}

GameObjectPtr
GameObject::findChild(const std::string& name, bool recuse) noexcept
{
	for (auto& it : _children)
	{
		if (it->getName() == name)
		{
			return it;
		}
	}

	if (recuse)
	{
		for (auto& it : _children)
		{
			auto result = it->findChild(name, recuse);
			if (result)
			{
				return result;
			}
		}
	}

	return nullptr;
}

std::uint32_t
GameObject::getChildCount() const noexcept
{
	return _children.size();
}

GameObjects&
GameObject::getChildren() noexcept
{
	return _children;
}

const GameObjects&
GameObject::getChildren() const noexcept
{
	return _children;
}

void
GameObject::setTranslate(const float3& pos) noexcept
{
	if (_translate != pos)
	{
		if (this->getActive())
		{
			this->_onMoveBefore();
		}

		_translate = pos;
		_needUpdates = true;

		if (this->getActive())
		{
			this->_onMoveAfter();
		}
	}
}

void
GameObject::setTranslateAccum(const float3& v) noexcept
{
	this->setTranslate(_translate + v);
}

const float3&
GameObject::getTranslate() const noexcept
{
	return _translate;
}

void
GameObject::setScale(const float3& pos) noexcept
{
	if (_scaling != pos)
	{
		if (this->getActive())
		{
			this->_onMoveBefore();
		}

		_scaling = pos;
		_needUpdates = true;

		if (this->getActive())
		{
			this->_onMoveAfter();
		}
	}
}

void
GameObject::setScaleAccum(const float3& scale) noexcept
{
	this->setScale(_scaling + scale);
}

const float3&
GameObject::getScale() const noexcept
{
	return _scaling;
}

void
GameObject::setQuaternion(const Quaternion& quat) noexcept
{
	if (_quat != quat)
	{
		if (this->getActive())
		{
			this->_onMoveBefore();
		}

		_quat = quat;
		_euler.makeRotate(_quat);
		_needUpdates = true;

		if (this->getActive())
		{
			this->_onMoveAfter();
		}
	}
}

void
GameObject::setQuaternionAccum(const Quaternion& quat) noexcept
{
	this->setQuaternion(math::cross(quat, _quat));
}

const Quaternion&
GameObject::getQuaternion() const noexcept
{
	return _quat;
}

void
GameObject::setEulerAngles(const EulerAngles& euler) noexcept
{
	if (_euler != euler)
	{
		if (this->getActive())
		{
			this->_onMoveBefore();
		}

		_euler = euler;
		_quat.makeRotate(euler);
		_needUpdates = true;

		if (this->getActive())
		{
			this->_onMoveAfter();
		}
	}
}

void
GameObject::setEulerAnglesAccum(const EulerAngles& euler) noexcept
{
	this->setEulerAngles(_euler + euler);
}

const EulerAngles&
GameObject::getEulerAngles() const noexcept
{
	return _euler;
}

const float3&
GameObject::getRight() const noexcept
{
	_updateTransform();
	return _right;
}

const float3&
GameObject::getUpVector() const noexcept
{
	_updateTransform();
	return _up;
}

const float3&
GameObject::getForward() const noexcept
{
	_updateTransform();
	return _forward;
}

void 
GameObject::setTransform(const float4x4& transform) noexcept
{
	this->_onMoveBefore();

	_transform = transform.getTransform(_scaling, _quat, _translate);
	_transformInverse = math::transformInverse(_transform);
	_transformInverseTranspose = math::transpose(_transformInverse);

	_euler.makeRotate(_quat);

	_right = _transform.getRight();
	_up = _transform.getUpVector();
	_forward = _transform.getForward();

	this->_onMoveAfter();
}

const Matrix4x4&
GameObject::getTransform() const noexcept
{
	this->_updateTransform();
	return _transform;
}

const Matrix4x4&
GameObject::getTransformInverse() const noexcept
{
	this->_updateTransform();
	return _transformInverse;
}

const Matrix4x4&
GameObject::getTransformInverseTranspose() const noexcept
{
	this->_updateTransform();
	return _transformInverseTranspose;
}

void
GameObject::addComponent(GameComponentPtr& component) except
{
	assert(component);
	assert(component->_gameObject == nullptr);

	auto it = std::find(_components.begin(), _components.end(), component);
	if (it == _components.end())
	{
		component->_setGameObject(this);
		component->onAttach();

		if (this->getActive() && component->getActive())
			component->onActivate();

		for (auto& it : _components)
			component->onAttachComponent(it);

		for (auto& it : _components)
			it->onAttachComponent(component);

		_components.push_back(component);
	}
}

void
GameObject::addComponent(GameComponentPtr&& component) except
{
	this->addComponent(component);
}

void
GameObject::removeComponent(GameComponentPtr& component) noexcept
{
	assert(component);
	assert(component->_gameObject == this);

	auto it = std::find(_components.begin(), _components.end(), component);
	if (it != _components.end())
	{
		_components.erase(it);

		for (auto& it : _components)
			component->onDetachComponent(it);

		for (auto& it : _components)
			it->onDetachComponent(component);

		if (this->getActive() && component->getActive())
			component->onDeactivate();

		component->onDetach();
		component->_setGameObject(nullptr);
	}
}

void
GameObject::removeComponent(GameComponentPtr&& component) noexcept
{
	this->removeComponent(component);
}

void
GameObject::cleanupComponents() noexcept
{
	for (auto& it : _components)
	{
		for (auto& component : _components)
		{
			if (it != component)
				it->onDetachComponent(component);
		}

		if (it->getActive())
			it->onDeactivate();

		it->onDetach();
	}

	_components.clear();
}

GameComponentPtr
GameObject::getComponent(const rtti::Rtti* type) const noexcept
{
	assert(type);

	for (auto& it : _components)
	{
		if (it->isA(type))
			return it;
	}

	return nullptr;
}

GameComponentPtr
GameObject::getComponent(const rtti::Rtti& type) const noexcept
{
	return this->getComponent(&type);
}

GameComponentPtr
GameObject::getComponentInChildren(const rtti::Rtti* type) const noexcept
{
	assert(type);

	for (auto& it : _components)
	{
		if (it->isA(type))
			return it;
	}

	for (auto& it : _children)
	{
		auto component = it->getComponentInChildren(type);
		if (component)
			return component;
	}

	return nullptr;
}

GameComponentPtr
GameObject::getComponentInChildren(const rtti::Rtti& type) const noexcept
{
	return this->getComponentInChildren(&type);
}

void 
GameObject::getComponentsInChildren(const rtti::Rtti* type, GameComponents& components) const noexcept
{
	for (auto& it : _components)
	{
		if (it->isA(type))
		{
			components.push_back(it);
			break;
		}			
	}

	for (auto& it : _children)
		it->getComponentsInChildren(type, components);
}

void 
GameObject::getComponentsInChildren(const rtti::Rtti& type, GameComponents& components) const noexcept
{
	return this->getComponentsInChildren(&type, components);
}

const GameComponents&
GameObject::getComponents() const noexcept
{
	return _components;
}

void
GameObject::destroy() noexcept
{
	this->cleanupChildren();
	this->cleanupComponents();
	this->setParent(nullptr);
}

void
GameObject::sendMessage(const MessagePtr& message) noexcept
{
	assert(message);

	if (!this->getActive())
		return;

	for (auto& it : _components)
	{
		if (it->getActive())
			it->onMessage(message);
	}
}

void
GameObject::sendMessageUpwards(const MessagePtr& message) noexcept
{
	assert(message);

	if (!this->getActive())
		return;

	for (auto& it : _components)
	{
		if (it->getActive())
			it->onMessage(message);
	}

	auto parent = _parent.lock();
	if (parent)
		parent->sendMessageDownwards(message);
}

void
GameObject::sendMessageDownwards(const MessagePtr& message) noexcept
{
	assert(message);

	if (!this->getActive())
		return;

	for (auto& it : _components)
	{
		if (it->getActive())
			it->onMessage(message);
	}

	for (auto& it : _children)
		it->sendMessageDownwards(message);
}

void
GameObject::load(iarchive& reader) noexcept
{
	std::string name;
	bool active;
	int layer;
	float3 position;
	float3 scale;
	float3 rotate;

	if (reader.getValue("name", name))
		this->setName(std::move(name));

	if (reader.getValue("active", active))
		this->setActive(active);
	else
		this->setActive(false);

	if (reader.getValue("layer", layer))
		this->setLayer(layer);

	if (reader.getValue("position", position))
		this->setTranslate(position);

	if (reader.getValue("scale", scale))
		this->setScale(scale);

	if (reader.getValue("rotate", rotate))
		this->setEulerAngles(EulerAngles(rotate));
}

void
GameObject::save(oarchive& write) noexcept
{
}

GameObjectPtr
GameObject::clone() const noexcept
{
	auto instance = std::make_shared<GameObject>();
	instance->setParent(this->getParent());
	instance->setName(this->getName());
	instance->setLayer(this->getLayer());
	instance->setQuaternion(this->getQuaternion());
	instance->setScale(this->getScale());
	instance->setTranslate(this->getTranslate());

	for (auto& it : _components)
		instance->addComponent(it->clone());

	for (auto& it : this->getChildren())
		instance->addChild(it->clone());

	return instance;
}

void
GameObject::_onFrameBegin() except
{
	assert(this->getActive());

	for (auto& it : _components)
	{
		if (it->getActive())
			it->onFrameBegin();
	}
}

void
GameObject::_onFrame() except
{
	assert(this->getActive());

	for (auto& it : _components)
	{
		if (it->getActive())
			it->onFrame();
	}
}

void
GameObject::_onFrameEnd() except
{
	assert(this->getActive());

	for (auto& it : _components)
	{
		if (it->getActive())
			it->onFrameEnd();
	}
}

void
GameObject::_onMoveBefore() except
{
	for (auto& it : _components)
	{
		if (it->getActive())
			it->onMoveBefore();
	}

	for (auto& it : _children)
		it->_onMoveBefore();
}

void
GameObject::_onMoveAfter() except
{
	for (auto& it : _components)
	{
		if (it->getActive())
			it->onMoveAfter();
	}

	for (auto& it : _children)
		it->_onMoveAfter();
}

void
GameObject::_updateTransform() const noexcept
{
	if (_needUpdates)
	{
		_transform.makeRotate(_quat);
		_transform.scale(_scaling);
		_transform.setTranslate(_translate);

		_right = _transform.getRight();
		_up = _transform.getUpVector();
		_forward = _transform.getForward();

		_transformInverse = math::transformInverse(_transform);
		_transformInverseTranspose = math::transpose(_transformInverse);

		_needUpdates = false;
	}
}

_NAME_END