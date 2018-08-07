/*
 * SEGS - Super Entity Game Server
 * http://www.segs.io/
 * Copyright (c) 2006 - 2018 SEGS Team (see AUTHORS.md)
 * This software is licensed under the terms of the 3-clause BSD License. See LICENSE.md for details.
 */

#pragma once
#include "AuthProtocol/AuthEvents.h"

// [[ev_def:type]]
class ServerSelectRequest : public AuthLinkEvent
{
public:
    ServerSelectRequest() : AuthLinkEvent(evServerSelectRequest)
    {}
    void init(EventProcessor *ev_src,uint8_t server_id)
    {
        m_server_id    = server_id;
        m_event_source = ev_src;
    }
    void serializefrom(GrowingBuffer &buf)
    {
        uint8_t op;
        buf.uGet(op);
        buf.uGetBytes(unkLoginArray, sizeof(unkLoginArray));
        buf.uGet(m_server_id);
    }
    void serializeto(GrowingBuffer &buf) const
    {
        buf.uPut((uint8_t)2);
        buf.uPutBytes(unkLoginArray, sizeof(unkLoginArray));
        buf.uPut(m_server_id);
    }
    // [[ev_def:field]]
    uint8_t unkLoginArray[8];
    // [[ev_def:field]]
    uint8_t m_server_id = 0;
};
