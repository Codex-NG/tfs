////////////////////////////////////////////////////////////////////////
// OpenTibia - an opensource roleplaying game
////////////////////////////////////////////////////////////////////////
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////

#ifndef __SPAWN__
#define __SPAWN__
#include "otsystem.h"

#include "templates.h"
#include "position.h"

#include "tile.h"
#include "monster.h"

class Spawn;
typedef std::list<Spawn*> SpawnList;

class Spawns
{
	private:
		Spawns();

	public:
		static Spawns* getInstance()
		{
			static Spawns instance;
			return &instance;
		}

		bool isInZone(const Position& centerPos, int32_t radius, const Position& pos);

		virtual ~Spawns();

		bool loadFromXml(const std::string& _filename);
		void startup();
		void clear();

		bool isLoaded() {return loaded;}
		bool isStarted() {return started;}

	private:
		typedef std::list<Npc*> NpcList;
		NpcList npcList;
		SpawnList spawnList;
		bool loaded, started;
		std::string filename;
};

struct spawnBlock_t
{
	MonsterType* mType;
	Position pos;
	Direction direction;

	uint32_t interval;
	int64_t lastSpawn;
};

class Spawn
{
	public:
		Spawn(const Position& _pos, int32_t _radius);
		virtual ~Spawn();

		bool addMonster(const std::string& _name, const Position& _pos, Direction _dir, uint32_t _interval);
		void removeMonster(Monster* monster);

		uint32_t getInterval() {return interval;}
		void startup();

		void startSpawnCheck();
		void stopEvent();

		bool isInSpawnZone(const Position& pos);

	private:
		Position centerPos;
		int32_t radius;
		int32_t despawnRange;
		int32_t despawnRadius;

		//map of creatures in the spawn
		typedef std::map<uint32_t, spawnBlock_t> SpawnMap;
		SpawnMap spawnMap;

		//map of the spawned creatures
		typedef std::multimap<uint32_t, Monster*, std::less<uint32_t> > SpawnedMap;
		typedef SpawnedMap::value_type SpawnedPair;
		SpawnedMap spawnedMap;

		uint32_t interval;
		uint32_t checkSpawnEvent;

		bool findPlayer(const Position& pos);
		bool spawnMonster(uint32_t spawnId, MonsterType* mType, const Position& pos, Direction dir, bool startup = false);
		void checkSpawn();
};
#endif
