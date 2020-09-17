/*
        /////////////////////
        //   Do not copy   //
        //   Created By    //
        //   XomoX#8227    //
        /////////////////////
*/

#include <YSI_Data\y_iterate>
#include <streamer>
#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_timers>

#if !defined MAX_ENEX
    #define MAX_ENEX                (50)
#endif

#define ENEX_STREAMER_IDENTIFIER    (100)

#define MAX_ENEX_NAME               (30)

static 
    // Entrance
    entranceStoreName[MAX_ENEX][MAX_ENEX_NAME],
    entrancePickup[MAX_ENEX],
    Float: enX[MAX_ENEX],
    Float: enY[MAX_ENEX],
    Float: enZ[MAX_ENEX],
    Float: enAng[MAX_ENEX],

    // Exit
    exitPickup[MAX_ENEX],
    Float: exX[MAX_ENEX],
    Float: exY[MAX_ENEX],
    Float: exZ[MAX_ENEX],
    Float: exAng[MAX_ENEX],
    exVirtualID[MAX_ENEX],
    exInteriorID[MAX_ENEX],

    // Other
    Iterator: enexID<MAX_ENEX>,
    getShopName[MAX_PLAYERS][MAX_ENEX_NAME],
    bool:enexFreezePlayer[MAX_ENEX];

Float:GetXYInFrontOfEnex(Float:x, Float:y, Float:a, &Float:q, &Float:w, Float:distance)
{
    q = x;
    w = y;
    q += (distance * floatsin(-a, degrees));
    w += (distance * floatcos(-a, degrees));
    return a;
}


stock Enex_SetIcon(id, iconid)
{
    if(!Iter_Contains(enexID, id)) {
        return 0;
    }

    CreateDynamicMapIcon(enX[id], enY[id], enZ[id], iconid, -1, .streamdistance = 200.0, .style = MAPICON_GLOBAL);
    return 1;
}

stock Enex_SetName(id, const name[])
{
    if(!Iter_Contains(enexID, id)) {
        return 0;
    }

    if(isnull(name)) {
        printf("[X:ERROR]: %d's Entrance Name is null", id);
        return 0;
    }

    strcpy(entranceStoreName[id], name, MAX_ENEX_NAME);
    CreateDynamic3DTextLabel(name, COLOR_YELLOW, enX[id],enY[id], enZ[id], 50.0, .testlos = 1, .streamdistance = TEXTLABEL_STREAMDISTANCE);
    return 1;
}

stock Enex_PlayerIn(playerid) {
    return (!isnull(getShopName[playerid])) ? getShopName[playerid] : "None";
}

stock Enex_EnableFreeze(id, bool:status) 
{
    if(!Iter_Contains(enexID, id)) {
        return 0;
    }

    enexFreezePlayer[id] = status;
    return 1;
}

stock Enex_Create(Float:entX, Float:entY, Float:entZ, Float:entAng, Float:exiX, Float:exiY, Float:exiZ, Float:exiAng, vwid, int)
{
    new
        id = Iter_Alloc(enexID),
        arr[2]
    ;

    arr[0] = ENEX_STREAMER_IDENTIFIER;
    arr[1] = id;

    entrancePickup[id] = CreateDynamicPickup(19135, 1, entX, entY, entZ);
    exitPickup[id] = CreateDynamicPickup(19135, 1, exiX, exiY, exiZ, vwid, int);

    Streamer_SetArrayData(STREAMER_TYPE_PICKUP, entrancePickup[id], E_STREAMER_EXTRA_ID, arr, sizeof(arr));
    Streamer_SetArrayData(STREAMER_TYPE_PICKUP, exitPickup[id], E_STREAMER_EXTRA_ID, arr, sizeof(arr));

    enX[id]             = entX;
    enY[id]             = entY;
    enZ[id]             = entZ;
    enAng[id]           = entAng;

    exX[id]             = exiX;
    exY[id]             = exiY;
    exZ[id]             = exiZ;
    exAng[id]           = exiAng;
    exVirtualID[id]     = vwid;
    exInteriorID[id]    = int;
    return id;
}

timer void:EnexUnfreezePlayer[seconds](playerid, seconds)
{
    #pragma unused seconds
    TogglePlayerControllable(playerid, true);
}

hook OnPlayerPickUpDynPickup(playerid, pickupid)
{
    new
        arr[2],
        id;

    new
        Float:fixedx,
        Float:fixedy;

    Streamer_GetArrayData(STREAMER_TYPE_PICKUP, pickupid, E_STREAMER_EXTRA_ID, arr);

    id = arr[1];

    if(arr[0] == ENEX_STREAMER_IDENTIFIER)
    {
        if(IsPlayerInAnyVehicle(playerid)) {
            return 1;
        }

        if(pickupid == entrancePickup[id]) {

            if(enexFreezePlayer[id]) {
                TogglePlayerControllable(playerid, false);
                defer EnexUnfreezePlayer(playerid, 1200 + GetPlayerPing(playerid));
            }

            SetPlayerVirtualWorld(playerid, exVirtualID[id]);
            SetPlayerInterior(playerid, exInteriorID[id]);

            GetXYInFrontOfEnex(exX[id], exY[id], exAng[id], fixedx, fixedy, 5.0);

            SetPlayerPos(playerid, fixedx, fixedy, exZ[id]);
            SetPlayerFacingAngle(playerid, exAng[id]);

            strcpy(getShopName[playerid], entranceStoreName[id], MAX_ENEX_NAME);
        }

        if(pickupid == exitPickup[id]) {

            SetPlayerInterior(playerid, 0);
            SetPlayerVirtualWorld(playerid, 0);

            TogglePlayerControllable(playerid, true);

            GetXYInFrontOfEnex(enX[id], enY[id], enAng[id], fixedx, fixedy, 5.0);

            SetPlayerPos(playerid, fixedx, fixedy, enZ[id]);
            SetPlayerFacingAngle(playerid, enAng[id]);

            getShopName[playerid][0] = EOS;
        }
    }
    return 1;
}