struct PLogic
{
	int id;
	int rtimer;
	int stimer;
	int vtimer;
	float gravity;
	float slope;
	int ground;
	int jumptimer;
	float vx;
	float vy;
	float vz;
	float x;
	float y;
	float z;
	float angy;
	float radius;
	int collide;
	float ny;
	float oldx;
	float oldy;
	float oldz;
	unsigned long tm_last;
	int tm_difference;
	float tm_factor;
	float tm_result;
	unsigned long tm_timer;

	PCam Camera;
};