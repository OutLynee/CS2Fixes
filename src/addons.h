/* ************************************Admins chat**************************************************************
*/ 
CON_COMMAND_CHAT(u, "admins chat")
{
    if (!player)
        return;

    int iCommandPlayer = player->GetPlayerSlot(); 

    ZEPlayer *pPlayer = g_playerManager->GetPlayer(iCommandPlayer);
    if (args.ArgC() < 2)
    {
        
        ClientPrint(player, HUD_PRINTTALK, CHAT_PREFIX "Usage: /u <msg to admins>");
        return;
    }
	
for (int i = 0; i < MAXPLAYERS; i++)
	{
    ZEPlayer* pAdmin = g_playerManager->GetPlayer(i); //player who sent mesg
    CBasePlayerController* cPlayer = (CBasePlayerController*)g_pEntitySystem->GetBaseEntity((CEntityIndex)(i + 1));

    if (!cPlayer || !pAdmin || pAdmin->IsFakeClient() || !pAdmin->IsAdminFlagSet(ADMFLAG_SLAY))
        continue;
        ClientPrint(cPlayer, HUD_PRINTTALK," \3*************\14Admins Chat\3*************");
        ClientPrint(cPlayer, HUD_PRINTTALK, " \7[Admins]\4 %s \1from \7%s ", args.ArgS(), player->GetPlayerName());
        ClientPrint(cPlayer, HUD_PRINTTALK, " \3**************************************");
	}
	//ClientPrint(cPlayer, HUD_PRINTTALK, " \7[To Admins] \4%s \1, message sent to \7Admins", args.ArgS());
	ClientPrint(player, HUD_PRINTTALK, " \7[To Admins] Message: \4%s \1, sent to \7Admins", args.ArgS());
}
//***************************************************Reset Score***********************************************
CON_COMMAND_CHAT(rs, "reset your score")
{
	if (!player)
		return;
	
	player->m_pActionTrackingServices->m_matchStats().m_iKills = 0;
	player->m_pActionTrackingServices->m_matchStats().m_iDeaths = 0;
	player->m_pActionTrackingServices->m_matchStats().m_iAssists = 0;
	player->m_pActionTrackingServices->m_matchStats().m_iDamage = 0;
	player->m_iScore = 0;
	player->m_iMVPs = 0;

	ClientPrint(player, HUD_PRINTTALK, " \7[Reset Score]\1 You have successfully reset your score.");
}
CON_COMMAND_CHAT(RS, "reset your score")
{
	if (!player)
		return;
	
	player->m_pActionTrackingServices->m_matchStats().m_iKills = 0;
	player->m_pActionTrackingServices->m_matchStats().m_iDeaths = 0;
	player->m_pActionTrackingServices->m_matchStats().m_iAssists = 0;
	player->m_pActionTrackingServices->m_matchStats().m_iDamage = 0;
	player->m_iScore = 0;
	player->m_iMVPs = 0;

	ClientPrint(player, HUD_PRINTTALK, " \7[Reset Score]\1 You have successfully reset your score.");
}
//************************************end reset**************************************************************
CON_COMMAND_CHAT(ws, "use console command for skins")
{
    if (!player)
        return;

    ClientPrint(player, HUD_PRINTTALK, CHAT_PREFIXS " \7[Skin]\1 Use console to activate skins \2skin <id skin> 0 0.");
}
CON_COMMAND_CHAT(knife, "use consola command for knife")
{
    if (!player)
        return;

    ClientPrint(player, HUD_PRINTTALK, CHAT_PREFIXS " \7[Skin]\1 Use console to activate knife \2skin 0 0 0 <knife id>.");
}
CON_COMMAND_CHAT(help, "help")
{
		if (!player)
		return;

ClientPrint(player, HUD_PRINTTALK, CHAT_PREFIXS "Player commands: !medic, !rs, !RS, !sound, !stats, !vip, !stats, !hide, /u.");
ClientPrint(player, HUD_PRINTTALK, CHAT_PREFIXS "Admin commands: /ban, /mute, /unmute, /gag, /ungag, /kick, /slay, /slap, /move, /silence, /unsilence, /entfire, /entfirepawn, /entfirecontroller, /map, /hsay, /rcon, /extend.");
}
CON_COMMAND_CHAT(vip, "vip info")
{
	if (!player)
		return;

	ClientPrint(player, HUD_PRINTTALK, CHAT_PREFIXV"\1Starting health: \5 100-115.");
	ClientPrint(player, HUD_PRINTTALK, CHAT_PREFIXV"\1Starting armor: \5 110-200.");
	ClientPrint(player, HUD_PRINTTALK, CHAT_PREFIXV"\1Money added every round: \5 1000-5000.");
	ClientPrint(player, HUD_PRINTTALK, CHAT_PREFIXV"\1Starting with: \5 defeuser, he, smoke, molotov, flashbang, healthshot.");
	ClientPrint(player, HUD_PRINTTALK, CHAT_PREFIXV"\1Smoke color: \5 green, \14blue, \7red, \2r\4a\3n\5d\6o\7m.");
	ClientPrint(player, HUD_PRINTTALK, CHAT_PREFIXV"\1For buying VIP, contact \7FOUNDER.");
}

//****************************************MEDIC********************************************************
CON_COMMAND_CHAT(medic, "medic")
{
	if (!player)
		return;

	int health = 0;
	int iPlayer = player->GetPlayerSlot();

	Z_CBaseEntity* pEnt = (Z_CBaseEntity*)player->GetPawn();

	//ClientPrint(player, HUD_PRINTTALK, CHAT_PREFIXM"pZEPlayer testing...");

	ZEPlayer* pZEPlayer = g_playerManager->GetPlayer(iPlayer);
	if (!pZEPlayer)
	{
		ClientPrint(player, HUD_PRINTTALK, CHAT_PREFIXM"Invalid target.");
		return;
	}

	//ClientPrint(player, HUD_PRINTTALK, CHAT_PREFIXM"pZEPlayer valid.");

	if (pEnt->m_iHealth() < 1)
	{
		ClientPrint(player, HUD_PRINTTALK, CHAT_PREFIXM"You need to be alive in order to use your medkit.");
		return;
	}
	
	if (pZEPlayer->WasUsingMedkit())
	{
		ClientPrint(player, HUD_PRINTTALK, CHAT_PREFIXM"You already used your medkit in this round.");
		g_pEngineServer2->ClientCommand(player->GetPlayerSlot(), "play training/puck_fail");
		return;
	}

		if (pEnt->m_iHealth() > 99)
	{
		ClientPrint(player, HUD_PRINTTALK, CHAT_PREFIXM"You already have enough life.");
		return;
	}

	health = pEnt->m_iHealth() + 50;

	if (health > 100)
		health = 100;

	pEnt->m_iHealth = health;

	pZEPlayer->SetUsedMedkit(true);

	ClientPrint(player, HUD_PRINTTALK, CHAT_PREFIXM"Medkit used! Your health is now at %d", health);
	g_pEngineServer2->ClientCommand(player->GetPlayerSlot(), "play items/healthshot_success_01"); // Disabled due to not being affected by the ingame volume mixer.
}
CON_COMMAND_CHAT(stats, "get your stats")
{
	if (!player)
		return;

	CSMatchStats_t *stats = &player->m_pActionTrackingServices->m_matchStats();

	ClientPrint(player, HUD_PRINTTALK, CHAT_PREFIXS"Kills: %d", stats->m_iKills.Get());
	ClientPrint(player, HUD_PRINTTALK, CHAT_PREFIXS"Deaths: %d", stats->m_iDeaths.Get());
	ClientPrint(player, HUD_PRINTTALK, CHAT_PREFIXS"Assists: %d", stats->m_iAssists.Get());
	ClientPrint(player, HUD_PRINTTALK, CHAT_PREFIXS"Damage: %d", stats->m_iDamage.Get());
}

CON_COMMAND_CHAT(say, "say something using console")
{
	ClientPrintAll(HUD_PRINTTALK, "%s", args.ArgS());
}
