struct SkillTemplate
{
	char* Name;
	int ImageID; // img skill is represented by
	char* Desc; // description of skill
	int HealthCost;
	int ManaCost; 
	int CastTime; //measured in sec
	int BONUS_VictimHealth; //damage caused on victim
	int BONUS_Health; // health given to you
	int BONUS_VictimMana; //mana taken from victim
	int BONUS_Mana; // mana given 2 u
};