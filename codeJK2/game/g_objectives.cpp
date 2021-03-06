/*
This file is part of Jedi Knight 2.

    Jedi Knight 2 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 2
    as published by the Free Software Foundation.

    Jedi Knight 2 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Jedi Knight 2.  If not, see <http://www.gnu.org/licenses/>.
*/
// Copyright 2001-2013 Raven Software

// leave this line at the top for all g_xxxx.cpp files...
#include "g_headers.h"


//g_objectives.cpp
//reads in ext_data\objectives.dat to objectives[]

#include "g_local.h"
#include "g_items.h"

#define	G_OBJECTIVES_CPP

#include "objectives.h"

qboolean	missionInfo_Updated;


/*
============
OBJ_SetPendingObjectives
============
*/
void OBJ_SetPendingObjectives(gentity_t *ent)
{
	int i;

	for (i=0;i<MAX_OBJECTIVES;++i)
	{
		if ((ent->client->sess.mission_objectives[i].status == OBJECTIVE_STAT_PENDING) && 
			(ent->client->sess.mission_objectives[i].display))
		{
			ent->client->sess.mission_objectives[i].status = OBJECTIVE_STAT_FAILED;
		}
	}
}

/*
============
OBJ_SaveMissionObjectives
============
*/
void OBJ_SaveMissionObjectives( gclient_t *client )
{
	gi.AppendToSaveGame(INT_ID('O','B','J','T'), client->sess.mission_objectives, sizeof(client->sess.mission_objectives));
}


/*
============
OBJ_SaveObjectiveData
============
*/
void OBJ_SaveObjectiveData(void)
{
	gclient_t *client;

	client = &level.clients[0];

	OBJ_SaveMissionObjectives( client );
}

/*
============
OBJ_LoadMissionObjectives
============
*/
void OBJ_LoadMissionObjectives( gclient_t *client )
{
	gi.ReadFromSaveGame(INT_ID('O','B','J','T'), (void *) &client->sess.mission_objectives, sizeof(client->sess.mission_objectives), NULL);
}


/*
============
OBJ_LoadObjectiveData
============
*/
void OBJ_LoadObjectiveData(void)
{
	gclient_t *client;

	client = &level.clients[0];

	OBJ_LoadMissionObjectives( client );
}
