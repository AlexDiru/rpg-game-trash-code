//SOME INSPIRATION DOWN MY POCKET
//http://forum.thegamecreators.com/?m=forum_view&t=129598&b=8 <- technically not fantasy but cool
//																 none the less :)


#include <DarkGDK.h>
#include <SC_Collision.h>
#include "f_Free.h"
#include "m_GameStructs.h" 
#include "f_TimerSystem.h"
#include "f_NPC.h"

#define RUNFWFRAMESTART 0
#define RUNFWFRAMEEND 0
#define RUNBWFRAMESTART 0
#define RUNBWFRAMEEND 0
#define RUNLFRAMESTART 0
#define RUNLFRAMEEND 0
#define RUNRFRAMESTART 0
#define RUNRFRAMEEND 0
#define JUMPFRAMESTART 0
#define	JUMPFRAMEEND 0

#define NUMBEROFMAPS 1

//float for the timer system
float TIMERUPDATE;

//Player struct
PLAYER Player[1];

NPC Enemy[1];

//Map struct
PMap Map[NUMBEROFMAPS];
//Map[0] = TestMap

void LoadPlayerData(int Array);
void LoadPlayerModel(int Array);
void MovePlayer(int Array);
void LoadMapScript(char* File,int Array);
void LoadMap(int Array);

void DarkGDK ( void )
{
	//Set the sync rate
	dbSyncOn();
	dbSyncRate(28);

	//Start the sliding collision
	SC_Start();

	//Variables which don't need to be loaded from a file
	Player[0].Logic.rtimer = 0;Player[0].Logic.stimer = 0;Player[0].Logic.vtimer = 0;Player[0].Logic.gravity = -0.1f;
	Player[0].Logic.slope = 0.5f;Player[0].Logic.ground = 1;Player[0].Logic.jumptimer = 0;Player[0].Logic.vx = 0;
	Player[0].Logic.vy = 0;Player[0].Logic.vz = 0;Player[0].Logic.angy = 0;Player[0].Logic.oldx = 0;
	Player[0].Logic.oldy = 0;Player[0].Logic.oldz = 0;Player[0].Logic.x = 0;Player[0].Logic.y = 0;Player[0].Logic.z = 0;
	Player[0].Logic.radius = 3;Player[0].Logic.ny = 0; Player[0].GUI.HeroWindowOff = true; Player[0].GUI.HeroWindowFlag = true;

	//Load variables which need to be read from a file
	LoadPlayerData(0);

	//Process the variables which have just been loaded
	LoadPlayerModel(0);

	//Set the health and mana
	Player[0].Game.Health = Player[0].Game.MaxHealth;
	Player[0].Game.Mana = Player[0].Game.MaxMana;

	dbPositionObject(Player[0].Logic.id,0,50,0);

	//initialize the timer system
	tm_init();

	Enemy[0].Hostile = true;
	Enemy[0].File.Obj = "Media//Models//Player Heroes//Warrior_M.x";
	Enemy[0].Logic.id = FObj();
	dbLoadObject(Enemy[0].File.Obj,Enemy[0].Logic.id);

	while (LoopGDK())
	{
		if (CheckIfNPCShouldAttackPlayer(Enemy[0].Logic.id,Player[0].Logic.id,Enemy[0].Hostile) == true)
		{
			dbPrint("UR BEEN ATCKD BY PPL :)");
		}
		else
		{
			dbPrint("UR SAFEEEEEEEE");
		}

		MovePlayer(0);
		
		//PLACEHOLDER camera code
		dbPositionCamera( dbObjectPositionX(Player[0].Logic.id),dbObjectPositionY(Player[0].Logic.id),dbObjectPositionZ(Player[0].Logic.id));
		//dbSetCameraToObjectOrientation(Player[0].Logic.id);
		dbMoveCamera(-30);
		dbMoveCameraUp(0,22.5);

		//rotate the camera up and down if pg up = ks 201 and pg down = ks 209 are pressed
		//new code is q = up e = down
		if (dbKeyState(16))
		{
			dbXRotateCamera(dbCameraAngleX() - 3);
		}
		if (dbKeyState(18))
		{
			dbXRotateCamera(dbCameraAngleX() + 3);
		}
		
		//Display Health
		dbText(0,0,"Health:");
		dbText(0,12,dbStr(Player[0].Game.Health));
		//Display Mana
		dbText(0,24,"Mana:");
		dbText(0,36,dbStr(Player[0].Game.Mana));
		//Display Name
		dbText(dbScreenWidth()-(dbLen(Player[0].Game.Name)*8),0,Player[0].Game.Name);

		//Update the timer system
		TIMERUPDATE = tm_update();

		dbSync();
	}
	return;
}

void LoadPlayerModel(int Array)
{
	//if player is a MALE KNIGHT
	if (Player[Array].Game.Profession == 0 && Player[Array].Game.Gender == 0)
	{
		//Load the MALE KNIGHT MODEL
		//Load Player Armour will define the textures
		Player[Array].Logic.id = FObj();
		dbLoadObject("Media//Models//Player Heroes//Warrior_M.x",Player[Array].Logic.id);
		SC_SetupComplexObject(Player[Array].Logic.id,0,2);
		dbXRotateObject(Player[Array].Logic.id,-90);
		dbScaleObject(Player[Array].Logic.id,5,5,5);
		dbFixObjectPivot(Player[Array].Logic.id);

		//Set the strings
		Player[0].Game.ProfessionString = "Knight";
		Player[0].Game.ProfessionStringAbv = "Kn";
	}

	//if player is a FEMALE KNIGHT
	if (Player[Array].Game.Profession == 0 && Player[Array].Game.Gender == 1)
	{
		//Load the FEMALE KNIGHT MODEL
		//Load Player Armour will define the textures
		Player[Array].Logic.id = FObj();
		dbLoadObject("Media//Models//Player Heroes//Warrior_F.x",Player[Array].Logic.id);
		SC_SetupComplexObject(Player[Array].Logic.id,0,2);
		dbXRotateObject(Player[Array].Logic.id,-90);
		dbScaleObject(Player[Array].Logic.id,10,10,10);
		dbFixObjectPivot(Player[Array].Logic.id);

		//Set the strings
		Player[0].Game.ProfessionString = "Knight";
		Player[0].Game.ProfessionStringAbv = "Kn";
	}

	//if player's secondary prof is an assassin
	if (Player[Array].Game.SProfession == 4)
	{
		//Set the strings
		Player[0].Game.SProfessionString = "Assassin";
		Player[0].Game.SProfessionStringAbv = "As";
	}

	if (Player[Array].Game.Location == 0)
	{
		//load testmap.ms
		LoadMapScript("Media//Scripts//Maps//testmap.ms",0);
		LoadMap(0);
	}
}

void LoadMap(int Array)
{
	//load scenery
	Map[0].sid = FObj();
	dbLoadObject(Map[0].ObjectFile,Map[0].sid);
	//load collision map
	Map[0].cid = FObj();
	dbLoadObject(Map[0].ObjectFile,Map[0].cid);
	SC_SetupObject(Map[0].cid,1,0);
	dbHideObject(Map[0].cid);
}

void LoadMapScript(char* File,int Array)
{
	char* TInt;
	dbOpenToRead(1,File);
	Map[Array].Name = dbReadString(1);
	Map[Array].Description = dbReadString(1);
	TInt = dbReadString(1);
	Map[Array].LocationNumber = atoi(TInt);
	Map[Array].ObjectFile = dbReadString(1);
	Map[Array].CollisionMapFile = dbReadString(1);
	dbCloseFile(1);
}


void LoadPlayerData(int Array)
{
	 dbOpenToRead(1,"Media//Scripts//Player//savegame.ps");

	Player[Array].Game.Name = dbReadString(1);
	char* TInt;
	TInt = dbReadString(1);
	Player[Array].Game.Profession = atoi(TInt);
	TInt = dbReadString(1);
	Player[Array].Game.SProfession = atoi(TInt);
	TInt = dbReadString(1);
	Player[Array].Game.Gender = atoi(TInt);
	TInt = dbReadString(1);
	Player[Array].Game.Location = atoi(TInt);
	TInt = dbReadString(1);
	Player[Array].Game.Level = atoi(TInt);
	TInt = dbReadString(1); 
	Player[Array].Game.MaxHealth = atoi(TInt);
 	TInt = dbReadString(1); 
	Player[Array].Game.MaxMana = atoi(TInt);

	dbCloseFile(1);
}

void MovePlayer(int Array)
{	
		//rotate player with mouse
		//dbYRotateObject(Player[Array].Logic.id,dbObjectAngleY(Player[Array].Logic.id) + dbMouseMoveX()/3.0f );
		//dbXRotateObject( Player[Array].Logic.id,dbObjectAngleX(Player[Array].Logic.id) + dbMouseMoveY()/3.0f );

		Player[Array].Logic.oldx = dbObjectPositionX(Player[Array].Logic.id);
		Player[Array].Logic.oldy = dbObjectPositionY(Player[Array].Logic.id);
		Player[Array].Logic.oldz = dbObjectPositionZ(Player[Array].Logic.id);
		
		//apply gravity, and user changes to movement
		Player[Array].Logic.angy = dbObjectAngleY(Player[Array].Logic.id);
		Player[Array].Logic.vx = 0;
		Player[Array].Logic.vz = 0;

		//if player is jumping or falling then apply 'normal' gravity
		//if not attempt to keep the player stuck to the floor
		if ( Player[Array].Logic.vy == 0 && Player[Array].Logic.jumptimer == 0 ) Player[Array].Logic.vy = Player[Array].Logic.vy + 10*Player[Array].Logic.gravity; 
		else Player[Array].Logic.vy = Player[Array].Logic.vy + Player[Array].Logic.gravity;

		//if (dbKeyState(32) == 1 ) { Player[Array].Logic.vx = Player[Array].Logic.vx + (TIMERUPDATE/10)*dbCos(Player[Array].Logic.angy); Player[Array].Logic.vz = Player[Array].Logic.vz - (TIMERUPDATE/10)*dbSin(Player[Array].Logic.angy); }//Player[Array].Logic.vx = Player[Array].Logic.vx + dbCos(Player[Array].Logic.angy); Player[Array].Logic.vz = Player[Array].Logic.vz - dbSin(Player[Array].Logic.angy); }
		//if (dbKeyState(30) == 1 ) { Player[Array].Logic.vx = Player[Array].Logic.vx - (TIMERUPDATE/10)*dbCos(Player[Array].Logic.angy); Player[Array].Logic.vz = Player[Array].Logic.vz + (TIMERUPDATE/10)*dbSin(Player[Array].Logic.angy); }//Player[Array].Logic.vx = Player[Array].Logic.vx - dbCos(Player[Array].Logic.angy); Player[Array].Logic.vz = Player[Array].Logic.vz + dbSin(Player[Array].Logic.angy); }
		if (dbKeyState(31) == 1 ) { Player[Array].Logic.vx = Player[Array].Logic.vx - (TIMERUPDATE/10)*dbSin(Player[Array].Logic.angy); Player[Array].Logic.vz = Player[Array].Logic.vz - (TIMERUPDATE/10)*dbCos(Player[Array].Logic.angy); }
		if (dbKeyState(17) == 1 ) { Player[Array].Logic.vx = Player[Array].Logic.vx + (TIMERUPDATE/10)*dbSin(Player[Array].Logic.angy); Player[Array].Logic.vz = Player[Array].Logic.vz + (TIMERUPDATE/10)*dbCos(Player[Array].Logic.angy); }
		//Press 'a' and 'd' to turn left and right
		if (dbKeyState(30)) { dbYRotateCamera(dbWrapValue(dbCameraAngleY()-5)); }
		if (dbKeyState(32)) { dbYRotateCamera(dbWrapValue(dbCameraAngleY()+5)); }
		dbSetObjectToCameraOrientation(Player[0].Logic.id);

		//only jump if on ground, and a certain time after last jump
		if ( Player[Array].Logic.ground == 1 ) 
		{
			if ( dbSpaceKey() == 1 && Player[Array].Logic.jumptimer == 0 ) 
			{
				Player[Array].Logic.vy = Player[Array].Logic.vy + 5.0f;
				Player[Array].Logic.jumptimer = 20;
			}
		}
		
		//this would be the player's final position without collision
		Player[Array].Logic.x = Player[Array].Logic.oldx + Player[Array].Logic.vx;
		Player[Array].Logic.y = Player[Array].Logic.oldy + Player[Array].Logic.vy;
		Player[Array].Logic.z = Player[Array].Logic.oldz + Player[Array].Logic.vz;
		
		Player[Array].Logic.collide = SC_SphereCastGroup( 1, Player[Array].Logic.oldx,Player[Array].Logic.oldy,Player[Array].Logic.oldz,Player[Array].Logic.oldx,Player[Array].Logic.oldy+Player[Array].Logic.vy,Player[Array].Logic.oldz,Player[Array].Logic.radius,0 );
		
		if ( Player[Array].Logic.collide > 0 )
		{
			//how flat is this ground
			Player[Array].Logic.ny = SC_GetCollisionNormalY();
			if ( dbAbs(Player[Array].Logic.ny) > Player[Array].Logic.slope )
			{
				//FLAT, stick
				Player[Array].Logic.oldy = SC_GetStaticCollisionY();
			}
			else
			{
				//STEEP, slide
				Player[Array].Logic.x = Player[Array].Logic.x - Player[Array].Logic.oldx; Player[Array].Logic.z = Player[Array].Logic.z - Player[Array].Logic.oldz;
				Player[Array].Logic.oldx = SC_GetCollisionSlideX();
				Player[Array].Logic.oldy = SC_GetCollisionSlideY();
				Player[Array].Logic.oldz = SC_GetCollisionSlideZ();
				Player[Array].Logic.x = Player[Array].Logic.x + Player[Array].Logic.oldx; Player[Array].Logic.z = Player[Array].Logic.z + Player[Array].Logic.oldz;
			}
			
			//ny#<0 means the player has hit a ceiling rather than a floor
			
			if ( Player[Array].Logic.ny > Player[Array].Logic.slope )
			{
				//only on ground if standing on flat ground
				Player[Array].Logic.ground = 1;
				Player[Array].Logic.vy = 0;
			}
			else 
			{
				Player[Array].Logic.ground = 0;
				//if player has hit a flat ceiling then stop vy# movement
				if ( Player[Array].Logic.ny < -Player[Array].Logic.slope ) Player[Array].Logic.vy = Player[Array].Logic.gravity;
			}
		}
		else
		{
			//nothing below player, not on ground, add vertical speed to player
			Player[Array].Logic.oldy = Player[Array].Logic.oldy + Player[Array].Logic.vy;
			Player[Array].Logic.ground = 0;
		}
		
		//jumptimer will decrease only when player is back on ground
		//creates a pause between two successive jumps
		if ( Player[Array].Logic.ground == 1 && Player[Array].Logic.jumptimer > 0 ) Player[Array].Logic.jumptimer--;
		
		//handle horizontal movement as sliding
		//player only collides with group 1 (level) objs and moves freely through others
		Player[Array].Logic.collide = SC_SphereSlideGroup( 1, Player[Array].Logic.oldx,Player[Array].Logic.oldy,Player[Array].Logic.oldz,Player[Array].Logic.x,Player[Array].Logic.oldy,Player[Array].Logic.z,Player[Array].Logic.radius,0 );
		
		if ( Player[Array].Logic.collide > 0 )
		{
			Player[Array].Logic.x = SC_GetCollisionSlideX();
			Player[Array].Logic.oldy = SC_GetCollisionSlideY();
			Player[Array].Logic.z = SC_GetCollisionSlideZ();
			Player[Array].Logic.vx = 0;
			Player[Array].Logic.vz = 0;
		}

		dbPositionObject( Player[Array].Logic.id,Player[Array].Logic.x,Player[Array].Logic.oldy,Player[Array].Logic.z );
		
		SC_UpdateObject(Player[Array].Logic.id);
}