int final(IplImage* img)
{
	int a,b;
	int m=100;
	int max;
	int count=0;
	for(a=0;a<720;a++)
	{
		max=0;
		for(b=0;b<595;b++)
		{

			if(IMGDATA(img,b,a,0)==255)
				{
					max++;
		     	}
		}
		if(max>m )
		{
			count++;
			if(count>50)
				{
					return 1;
				}
			else
				{
					return 0;
				}

		}
		else 
		{
			count=0;
		}
			
			
		
		m=max;
	}

}