#pragma once
#include "stdafx.h"

namespace statedb {
	struct db_magic { const char value[7] = "StAtE1"; };

	struct db_pointers
	{
		size_t dtypes;
		size_t info;
		size_t data;
	};

	struct db_meta
	{
		const byte_t version = 1;
		db_pointers pointers;
	};

	struct db_info
	{
		char * name;
		char * description;
	};

	WRITE_OBJECT_SPECIALIZATION(db_info)
	{
		_Stream << _Val.name << _Val.description;
	}

	READ_OBJECT_SPECIALIZATION(db_info)
	{
		_Stream >> _Dest->name >> _Dest->description;
	}

	struct db_header
	{
		const db_magic magic;
		static const size_t magic_offset = sizeof(db_magic);
		db_meta meta;

		db_info info;
	};
}

MAKE_HASHABLE(statedb::db_info, _.description, _.name)

// https://gist.github.com/codebrainz/8ece2a9015a3ed0d260f
namespace std
{
	template <>
	struct hash<char*>
	{
		size_t operator()(const char *s) const
		{
			// http://www.cse.yorku.ca/~oz/hash.html
			size_t h = 5381;
			int c;
			while ((c = *s++))
				h = ((h << 5) + h) + c;
			return h;
		}
	};
}