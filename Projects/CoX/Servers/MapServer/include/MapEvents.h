/*
 * Super Entity Game Server Project 
 * http://segs.sf.net/
 * Copyright (c) 2006 Super Entity Game Server Team (see Authors.txt)
 * This software is licensed! (See License.txt for details)
 *
 * $Id$
 */

#pragma once
#include <ace/Assert.h>
#include "LinkLevelEvent.h"
#include "BitStream.h"
#include "CRUD_Link.h"
#include "CRUD_Events.h"
#include "MapLink.h"
class Entity;
typedef CRUDLink_Event MapLinkEvent; //<MapLink>

class MapEventTypes : public CRUD_EventTypes
{
public:
    BEGINE_EVENTS(CRUD_EventTypes)
    EVENT_DECL(evEntityEnteringMap      ,0)
    EVENT_DECL(evMapInstanceConnected   ,1)
    EVENT_DECL(evShortcutsRequest       ,2)
    EVENT_DECL(evShortcuts              ,3)
    EVENT_DECL(evSceneRequest           ,4)
    EVENT_DECL(evScene                  ,5)
    EVENT_DECL(evEntitiesRequest        ,6)
    EVENT_DECL(evEntitites              ,7)
    EVENT_DECL(evInputState             ,8)
    END_EVENTS(500)
};
//////////////////////////////////////////////////////////////////////////
// Client -> Server
#include "Events/NewEntity.h"

class MapUnknownRequest : public MapLinkEvent
{
public:
    MapUnknownRequest():MapLinkEvent(MapEventTypes::evUnknownEvent)
    {

    }
    void serializeto(BitStream &) const
    {
    }
    void serializefrom(BitStream &)
    {
    }
};
class ShortcutsRequest : public MapLinkEvent
{
public:
    ShortcutsRequest():MapLinkEvent(MapEventTypes::evShortcutsRequest)
    {}
    void serializeto(BitStream &bs) const
    {
        bs.StorePackedBits(1,4); // opcode
    }
    void serializefrom(BitStream &)
    {
    }
};

class SceneRequest : public MapLinkEvent
{
public:
    SceneRequest():MapLinkEvent(MapEventTypes::evSceneRequest)
    {}
    void serializeto(BitStream &bs) const
    {
        bs.StorePackedBits(1,3); // opcode
    }
    void serializefrom(BitStream &)
    {
    }
};

class EntitiesRequest : public MapLinkEvent
{
public:
    EntitiesRequest():MapLinkEvent(MapEventTypes::evEntitiesRequest)
    {}
    void serializeto(BitStream &bs) const
    {
        bs.StorePackedBits(1,5); // opcode
    }
    void serializefrom(BitStream &)
    {
    }

};
#include "Events/InputState.h"
//////////////////////////////////////////////////////////////////////////
// Server -> Client events
class MapInstanceConnected : public MapLinkEvent
{
public:
    MapInstanceConnected():MapLinkEvent(MapEventTypes::evMapInstanceConnected)
    {
    }
    MapInstanceConnected(EventProcessor *evsrc,uint32_t resp,const std::string &err) :
            MapLinkEvent(MapEventTypes::evMapInstanceConnected,evsrc),
            m_resp(resp),
            m_fatal_error(err)
    {
    }
    void serializeto(BitStream &bs) const
    {
        bs.StorePackedBits(1,5); //opcode
        bs.StorePackedBits(1,m_resp);
        if(m_resp)
            bs.StoreString(m_fatal_error);
    }
    void serializefrom(BitStream &src)
    {
        m_resp = src.GetPackedBits(1);
        if(m_resp==0)
            src.GetString(m_fatal_error);
    }
    uint32_t         m_resp;
    std::string m_fatal_error;

};
#include "Events/SceneEvent.h"
#include "Events/EntitiesResponse.h"
#include "Events/Shortcuts.h"
