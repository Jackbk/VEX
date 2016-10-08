
void drive(char movement, int ldistance, int rdistance, int lmspeed, int rmspeed, int time, int reset)
{
	if(reset == 1)
	{
		SensorValue[leftEncoder] = 0;
		SensorValue[rightEncoder] = 0;
	}
	ltspeed = 0;
	rtspeed = 0;
	rpreviousdifference = 0;
	lpreviousdifference = 0;
	rloopsatvalue = 0;
	lloopsatvalue = 0;
	time1[T1] = 0;

	if(movement == 's')																																	//STRAIGHT MOVEMENT
	{

		while (time1[T1] < time)
		{																																									// Setting Differences
			int ldifference = ldistance - SensorValue[leftEncoder];
			int rdifference = rdistance + SensorValue[rightEncoder];

			int sideDifference = ldifference - rdifference;
			//Setting Integrals
			lintegral = lintegral + ldifference;
			if(ldifference == 0)
			{
				lintegral = 0;
			}
			else
			{
			}

			rintegral = rintegral + rdifference;
			if(rdifference == 0)
			{
				rintegral = 0;
			}
			else
			{
			}

			//Setting Derivative

			rderivative = ( (rdifference) - (rpreviousdifference) );
			rpreviousdifference = rderivative;

			lderivative = ( (ldifference) - (lpreviousdifference) );
			lpreviousdifference = lderivative;


			if(lDifference < 20 && rDifference < 20)
				sideDifference = 0;

			float lspeed = (ldifference * sp + lintegral*si + lderivative*sd );
			float rspeed = (rdifference * sp + rintegral*si + rderivative*sd );

			if (lspeed > 0)
				lspeed = lspeed+change;

			if(lspeed < 0)
				lspeed = lspeed-change;


			if (rspeed > 0)
				rspeed = rspeed+change;

			if(rspeed < 0)
				rspeed = rspeed-change;





			if(lspeed > 127)																																//Accelleration Code
			{
				ltspeed = ltspeed + speedchangeperloop;
			}


			else if(lspeed < -127)
			{
				ltspeed = ltspeed - speedchangeperloop;
			}

			else
			{
				ltspeed = lspeed;
			}
			if(ltspeed > lmspeed)
			{
				ltspeed = lmspeed;
			}


			if(rspeed > 127)
			{
				rtspeed = rtspeed + speedchangeperloop;
			}

			else if(rspeed < -127)
			{
				rtspeed = rtspeed - speedchangeperloop;
			}

			else
			{
				rtspeed = rspeed;
			}

			if(rtspeed > rmspeed)
			{
				rtspeed = rmspeed;
			}

			setDriveSpeed(ltspeed - sideDifference*sidep, rtspeed + sideDifference*sidep);

			if ( abs(ldifference) <= accuracy )
			{
				lloopsatvalue = lloopsatvalue + 1;
			}

			if ( abs(rdifference) <= accuracy )
			{
				rloopsatvalue = rloopsatvalue + 1;
			}
		}
	}
	if(movement == 't')
	{
		while (time1[T1] < time)
		{																																									// Setting Differences
			int ldifference = ldistance - SensorValue[leftEncoder];
			int rdifference = rdistance + SensorValue[rightEncoder];

			int sideDifference = 0;
			//Setting Integrals
			lintegral = lintegral + ldifference;
			if(ldifference == 0)
			{
				lintegral = 0;
			}


			rintegral = rintegral + rdifference;
			if(rdifference == 0)
			{
				rintegral = 0;
			}

			//Setting Derivative

			rderivative = ( (rdifference) - (rpreviousdifference) );
			rpreviousdifference = rderivative;

			lderivative = ( (ldifference) - (lpreviousdifference) );
			lpreviousdifference = lderivative;

			float lspeed = (ldifference * tp + lintegral*ti + lderivative*td);
			float rspeed = (rdifference * tp + rintegral*ti + rderivative*td);

			if (lspeed > 0)
				lspeed = lspeed+tchange;

			if(lspeed < 0)
				lspeed = lspeed-tchange;


			if (rspeed > 0)
				rspeed = rspeed+tchange;

			if(rspeed < 0)
				rspeed = rspeed-tchange;

			if(lspeed > 127)																																//Accelleration Code
			{
				ltspeed = ltspeed + speedchangeperloop;
			}

			else if(lspeed < -127)
			{
				ltspeed = ltspeed - speedchangeperloop;
			}

			else
			{
				ltspeed = lspeed;
			}
			if(ltspeed > lmspeed)
			{
				ltspeed = lmspeed;
			}

			if(rspeed > 127)
			{
				rtspeed = rtspeed + speedchangeperloop;
			}

			else if(rspeed < -127)
			{
				rtspeed = rtspeed - speedchangeperloop;
			}

			else
			{
				rtspeed = rspeed;
			}

			if(rtspeed > rmspeed)
			{
				rtspeed = rmspeed;
			}

			setDriveSpeed(ltspeed, rtspeed);

			if ( abs(ldifference) <= accuracy )
			{
				lloopsatvalue = lloopsatvalue + 1;
			}

			if ( abs(rdifference) <= accuracy )
			{
				rloopsatvalue = rloopsatvalue + 1;
			}
		}
	}

	setDriveSpeed(0, 0);
}
