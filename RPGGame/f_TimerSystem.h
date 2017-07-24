
unsigned long tm_last = 0;
int tm_difference = 0;
float tm_factor = 0;
float tm_result = 0;
unsigned long tm_timer = 0;




//***** 'tm_init' *************************************************************
//+**** ========= *************************************************************
void tm_init ()
{
   //<- timer-value of last update-function-call
      //<- Difference between actual and last function-call in ms
      //<- Result-Speed-Value is multiplicated with this
      //<- the resulting factor
      //<- stores the timer-value for exact calculations
   tm_timer = dbTimer();
   tm_last = tm_timer;
   tm_factor = 1;
}




//***** 'tm_update' ***********************************************************
//+**** =========== ***********************************************************
float tm_update ()
{
   tm_timer = dbTimer();
   tm_difference = tm_timer - tm_last;
   tm_last = tm_timer;
   tm_result = tm_difference * tm_factor;
   return tm_result;
}




//***** 'tm_setmultiplicator' *************************************************
//+**** ===================== *************************************************
void tm_setmultiplicator ( float f_flt )
{
   tm_factor = f_flt;
}




//***** 'tm_getfactor' ********************************************************
//+**** ============== ********************************************************
float tm_getfactor ()
{
   float f_flt = 0;


   f_flt = tm_result;
   return f_flt;
}




