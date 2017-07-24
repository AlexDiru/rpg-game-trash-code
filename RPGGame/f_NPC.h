//Check if enemy is hostile and smaller than a dist of 25 before following player
bool CheckIfNPCShouldAttackPlayer(int EnemyObject,int PlayerObject,bool EnemyHostile)
//If the NPC is hostile and in range of player it attacks
{
	if (EnemyHostile == true)
	{
		//Get positions of all the objs
		float EneX = dbObjectPositionX(EnemyObject);
		float EneY = dbObjectPositionY(EnemyObject);
		float EneZ = dbObjectPositionZ(EnemyObject);
		float PlrX = dbObjectPositionX(PlayerObject);
		float PlrY = dbObjectPositionY(PlayerObject);
		float PlrZ = dbObjectPositionZ(PlayerObject);
		//Calculate dist between objs
		float DAX = (PlrX-EneX);
		float DAY = (PlrY-EneY);
		float DAZ = (PlrZ-EneZ);
		float DistA = dbSQRT((DAZ*DAZ)+(DAX*DAX)+(DAY*DAY));
		//If DistA is under 150
		if (DistA < 150)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}