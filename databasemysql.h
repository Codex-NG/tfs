//////////////////////////////////////////////////////////////////////
// OpenTibia - an opensource roleplaying game
//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//////////////////////////////////////////////////////////////////////

#ifndef __OTSERV_DATABASEMYSQL_H__
#define __OTSERV_DATABASEMYSQL_H__

#ifndef __OTSERV_DATABASE_H__
#error "database.h should be included first."
#endif

#ifdef __MYSQL_ALT_INCLUDE__
#include <mysql.h>
#else
#include <mysql/mysql.h>
#endif
#include <sstream>
#include <map>

#define MAX_RECONNECT_ATTEMPTS 3

class DatabaseMySQL : public _Database
{
	public:
		DatabaseMySQL();
		DATABASE_VIRTUAL ~DatabaseMySQL();

		DATABASE_VIRTUAL bool getParam(DBParam_t param);

		DATABASE_VIRTUAL bool beginTransaction();
		DATABASE_VIRTUAL bool rollback();
		DATABASE_VIRTUAL bool commit();

		DATABASE_VIRTUAL bool executeQuery(const std::string &query);
		DATABASE_VIRTUAL DBResult* storeQuery(const std::string &query);

		DATABASE_VIRTUAL std::string escapeString(const std::string &s);
		DATABASE_VIRTUAL std::string escapeBlob(const char* s, uint32_t length);

		DATABASE_VIRTUAL void freeResult(DBResult *res);

		DATABASE_VIRTUAL DatabaseEngine_t getDatabaseEngine() {return DATABASE_ENGINE_MYSQL;}

	protected:
		DATABASE_VIRTUAL void keepAlive();
		DATABASE_VIRTUAL bool reconnect();

		MYSQL m_handle;
		uint32_t m_attempts;
};

class MySQLResult : public _DBResult
{
	friend class DatabaseMySQL;

	public:
		DATABASE_VIRTUAL int32_t getDataInt(const std::string &s);
		DATABASE_VIRTUAL int64_t getDataLong(const std::string &s);
		DATABASE_VIRTUAL std::string getDataString(const std::string &s);
		DATABASE_VIRTUAL const char* getDataStream(const std::string &s, uint64_t &size);

		DATABASE_VIRTUAL bool next();
		DATABASE_VIRTUAL void free() {delete *this;}

	protected:
		MySQLResult(MYSQL_RES* res);
		DATABASE_VIRTUAL ~MySQLResult() {mysql_free_result(m_handle);}

		typedef std::map<const std::string, uint32_t> listNames_t;
		listNames_t m_listNames;

		MYSQL_RES* m_handle;
		MYSQL_ROW m_row;
};

#endif
