/*
 * opencog/cogserver/proxy/WriteThruProxy.h
 *
 * Module for starting up s-expression shells
 * Copyright (c) 2008, 2020, 2022 Linas Vepstas <linas@linas.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License v3 as
 * published by the Free Software Foundation and including the exceptions
 * at http://opencog.org/wiki/Licenses
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program; if not, write to:
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef _OPENCOG_WRITE_THRU_PROXY_H
#define _OPENCOG_WRITE_THRU_PROXY_H

#include <vector>

#include <opencog/cogserver/proxy/Proxy.h>
#include <opencog/persist/api/StorageNode.h>
#include <opencog/persist/sexpr/Commands.h>

namespace opencog {
/** \addtogroup grp_server
 *  @{
 */

class WriteThruProxy : public Proxy
{
	protected:
		Handle _truth_key;
		std::vector<StorageNodePtr> _targets;

		Commands _decoder;

		void set_value_cb(const Handle&, const Handle&, const ValuePtr&);
		void set_values_cb(const Handle&);
		void set_tv_cb(const Handle&, const TruthValuePtr&);
		void update_value_cb(const Handle&, const Handle&, const ValuePtr&);

		std::string cog_extract_helper(const std::string&, bool);

		/// Methods that implement the interpreted commands
		std::string cog_extract(const std::string& arg)
			{ return cog_extract_helper(arg, false); }
		std::string cog_extract_recursive(const std::string& arg)
			{ return cog_extract_helper(arg, true); }
		std::string cog_set_value(const std::string&);
		std::string cog_set_values(const std::string&);
		std::string cog_set_tv(const std::string&);
		std::string cog_update_value(const std::string&);

	public:
		WriteThruProxy(CogServer&);
		virtual ~WriteThruProxy();

		static const char *id(void);
		virtual void init(void);
		virtual bool config(const char*);

		virtual void setup(SexprEval*);
};

/** @}*/
}

#endif // _OPENCOG_WRITE_THRU_PROXY_H
