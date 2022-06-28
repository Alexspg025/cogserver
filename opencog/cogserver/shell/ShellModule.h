/*
 * opencog/cogserver/shell/ShellModule.h
 *
 * Copyright (C) 2022 Linas Vepstas <linasvepstas@gmail.com>
 *
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#ifndef _OPENCOG_SHELL_MODULE_H
#define _OPENCOG_SHELL_MODULE_H

#include <string>
#include <opencog/cogserver/server/Module.h>

/**
 * DEFINE_SHELL_MODULE -- Declare a new C++ Module class, suitable
 * for providing a network shell. Network shells can respond to inputs
 * coming over a network TCP/IP socket. All the details of socket
 * handling are abstracted away.
 */
#define DEFINE_SHELL_MODULE(MODNAME)                                  \
namespace opencog {                                                   \
                                                                      \
class MODNAME : public Module {                                       \
    private:                                                          \
        class shelloutRequest : public Request                        \
        {                                                             \
            public:                                                   \
                static const RequestClassInfo& info(void);            \
                shelloutRequest(CogServer& cs) : Request(cs) {};      \
                virtual ~shelloutRequest() {};                        \
                virtual bool execute(void);                           \
                virtual bool isShell(void) { return true; }           \
        };                                                            \
        Factory<shelloutRequest, Request> shelloutFactory;            \
        static std::string _config_setting;                           \
    public:                                                           \
        MODNAME(CogServer&);                                          \
        virtual ~MODNAME();                                           \
        static const char *id(void);                                  \
        virtual void init(void);                                      \
        virtual bool config(const char *);                            \
};                                                                    \
std::string MODNAME::_config_setting;                                 \
}

#endif // _OPENCOG_SHELL_MODULE_H