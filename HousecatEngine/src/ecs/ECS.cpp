#include <algorithm>

#include "ECS.h"



//--------------------------------------------------//
//                    COMPONENT                     //
//--------------------------------------------------//
int IComponent::nextID = 0;





//--------------------------------------------------//
//                    ENTITY                        //
//--------------------------------------------------//
int Entity::GetID() const {
	return ID;
}

void Entity::Kill() {
	housecat->KillEntity(*this);
}

void Entity::Tag(const std::string& tag) {
	housecat->AddTag(*this, tag);
}

bool Entity::HasTag(const std::string& tag) const {
	return housecat->HasTag(*this, tag);
}

void Entity::Group(const std::string& group) {
	housecat->AddGroup(*this, group);
}

bool Entity::HasGroup(const std::string& group) const {
	return housecat->HasGroup(*this, group);
}

//REMIND
//TODO

//freeze
//tag and? group
//Tag(), NeedsTag(), GetTag(), HasTag()





//--------------------------------------------------//
//                    SYSTEM                        //
//--------------------------------------------------//
std::vector<Entity> System::GetSystemEntities() const {
	return entities;
}

const Signature& System::GetComponentSignature() const {
	return componentSignature;
}

void System::AddEntityToSystem(Entity entity) {
	entities.push_back(entity);
}

void System::RemoveEntityFromSystem(Entity entity) {
	//TODO
	//HORRIBLE SYNTAX. FIX LATER
	entities.erase(std::remove_if(entities.begin(),entities.end(),[&entity](Entity other) {
		return entity == other;
	}), entities.end());
}






//--------------------------------------------------//
//                    HOUSECAT                      //
//--------------------------------------------------//
Entity Housecat::CreateEntity() {
	int entityID;

	if (freedIDs.empty()) {
		entityID = numOfEntities++;
		if (static_cast<size_t>(entityID) >= entityComponentSignatures.size()) {
			entityComponentSignatures.resize(entityID + 1);
		}
	}
	else {
		//reuse IDs
		entityID = freedIDs.front();
		freedIDs.pop_front();
	}

	Entity entity(entityID);
	entity.housecat = this;
	entitiesToAdd.insert(entity);

	//TODO smart ptr
	//entity.housecat = std::weak_ptr<Housecat>(std::shared_ptr<Housecat>());

	if (static_cast<unsigned int>(entityID) >= entityComponentSignatures.size()) {
		entityComponentSignatures.resize(entityID + 1);
	}

	//TODO
	//try entity ID reusability design?

	//REMIND TESTING remove latr
	Logger::Log("Entity [" + std::to_string(entityID) + "] Created!");

	return entity;
}

void Housecat::KillEntity(Entity entity) {
	entitiesToKill.insert(entity);
}

void Housecat::AddEntityToSystems(Entity entity) {
	const auto entityID = entity.GetID();
	const auto& entityComponentSignature = entityComponentSignatures[entityID];

	for (auto& system : systems) {
		const auto& systemComponentSignature = system.second->GetComponentSignature();
		//bitset comparisn
		bool interestedFlag = (entityComponentSignature & systemComponentSignature) == systemComponentSignature;
		//matched, adds entity val to system
		if (interestedFlag) {
			system.second->AddEntityToSystem(entity);
		}
	}
}

//FIXED
void Housecat::RemoveEntityFromSystems(Entity entity) {
	for (auto system : systems) {
		system.second->RemoveEntityFromSystem(entity);
	}
}

void Housecat::AddTag(Entity entity, const std::string& tag) {
	entityByTag.emplace(tag, entity);
	tagByEntityID.emplace(entity.GetID(), tag);
}

void Housecat::RemoveTag(Entity entity) {
	auto taggedEntity = tagByEntityID.find(entity.GetID());
	if (taggedEntity != tagByEntityID.end()) {
		auto tag = taggedEntity->second;
		entityByTag.erase(tag);
		tagByEntityID.erase(taggedEntity);
	}
}

bool Housecat::HasTag(Entity entity, const std::string& tag) const {
	if (tagByEntityID.find(entity.GetID()) == tagByEntityID.end()) {
		return false;
	}
	return entityByTag.find(tag)->second == entity;
}

Entity Housecat::GetTag(const std::string& tag) const {
	return entityByTag.at(tag);
}

void Housecat::AddGroup(Entity entity, const std::string& group) {
	entitiesByGroup.emplace(group, std::set<Entity>());
	entitiesByGroup[group].emplace(entity);
	groupByEntityID.emplace(entity.GetID(), group);
}

void Housecat::RemoveGroup(Entity entity) {
	auto groupedEntity = groupByEntityID.find(entity.GetID());
	if (groupedEntity != groupByEntityID.end()) {
		auto group = entitiesByGroup.find(groupedEntity->second);
		if (group != entitiesByGroup.end()) {
			auto entityInGroup = group->second.find(entity);
			if (entityInGroup != group->second.end()) {
				group->second.erase(entityInGroup);
			}
		}
		groupByEntityID.erase(groupedEntity);
	}
}
bool Housecat::HasGroup(Entity entity, const std::string& group) const {
	if (entitiesByGroup.find(group) == entitiesByGroup.end()) {
		return false;
	}
	auto groupEntities = entitiesByGroup.at(group);
	return groupEntities.find(entity.GetID()) != groupEntities.end();
}

std::vector<Entity> Housecat::GetGroup(const std::string& group) const {
	auto& setEntities = entitiesByGroup.at(group);
	return std::vector<Entity>(setEntities.begin(), setEntities.end());
}

//process housecat management
void Housecat::Update() {
	//creation
	for (auto entity : entitiesToAdd) {
		AddEntityToSystems(entity);
	}
	entitiesToAdd.clear();

	//deletion
	for (auto entity : entitiesToKill) {
		RemoveEntityFromSystems(entity);
		entityComponentSignatures[entity.GetID()].reset();

		//remove entity from pool
		for (auto pool : componentPools) {
			//fixes null fault
			if (pool) {
				pool->RemoveEntityFromPool(entity.GetID());
			}
		}

		//reuse that ID
		freedIDs.push_back(entity.GetID());

		//remove their tags|groups
		RemoveTag(entity);
		RemoveGroup(entity);
	}
	entitiesToKill.clear();
}

Housecat& Housecat::GetInstance() {
	static Housecat instance;
	return instance;
}

//TODO
//adding entity Kill(), Tag()
//use housecat for management

//Housecat::KillEntity()