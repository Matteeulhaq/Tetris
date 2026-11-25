//Name : Mattee ul haq Ghauri
//Roll no.: 22i-0989
//project




/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 * */

//---Piece Starts to Fall When Game Starts---//
void nextPiece( int& next1, int& next2, int& next3, int& difficulty) /// check which shape will be formed next. next 1 is the first shape
{
	
		if (difficulty == 1)
		{	
		  	next1=rand()%4;
		  	next2= rand()%4;
		   	next3= rand()%4;
		}
		else if (difficulty == 2)
		{
			next3 = rand()%7;
			next2 = rand()%7;
		 	next1 = rand()%7;
		   	
		   	
		}
	
}

void nextpieces(float& timer,float& delay , int nextpiece_1[4][2], int nextpiece_2[4][2], int nextpiece_3[4][2], int& next1, int& next2, int& next3 ,int& difficulty)		/// makes the next 3 pieces
{
	
	if (timer>delay)
    {
    	nextPiece(next1,next2,next3,difficulty);
		for(int i = 0; i<4; i++)
		{
			nextpiece_1[i][0] = BLOCKS[next1][i] % 2;   		// x axis value of the first next piece 
			nextpiece_1[i][1] = BLOCKS[next1][i] / 2;			// y axis value of the first next piece
		}
		for(int i = 0; i<4; i++)
		{
			nextpiece_2[i][0] = BLOCKS[next2][i] % 2;   		// x axis value of the second next piece 
			nextpiece_2[i][1] = BLOCKS[next2][i] / 2;			// y axis value of the second next piece
		}
		for(int i = 0; i<4; i++)
		{
			nextpiece_3[i][0] = BLOCKS[next3][i] % 2;   		// x axis value of the third next piece 
			nextpiece_3[i][1] = BLOCKS[next3][i] / 2;			// y axis value of the third next piece
		}
	}
}


void fallingPiece(float& timer, float& delay, int& colorNum, int difficulty, int& next1, int& next2, int& next3)
{
    if (timer>delay)
    {
        for (int i=0;i<4;i++)
        {
            point_2[i][0]=point_1[i][0];
            point_2[i][1]=point_1[i][1];
            point_1[i][1]+=1;                   //How much units downward
        }
        
        if (!anamoly())
        {
        	for (int i =0; i<4 ; i++)
        		gameGrid[point_2[i][1]][point_2[i][0]] = colorNum;
        	colorNum = 1+rand()%7;
        	int n = rand()% 7;
        	if (difficulty == 1)
        	{	
            	n= next1;
            }
            else if (difficulty ==2)
            {
            	n = next1;
            }
            	//--- Un-Comment this Part When You Make BLOCKS array---//
            
            
            for (int i=0;i<4;i++)
            {
     	       point_1[i][0] = BLOCKS[n][i] % 2; // value of x axis
               point_1[i][1] = BLOCKS[n][i] / 2; // value of y axis 
            }
            
            nextpieces(timer, delay, nextpiece_1, nextpiece_2, nextpiece_3, next1, next2, next3, difficulty);
            
            
        }
        timer=0;
    }
}

/////////////////////////////////////////////
///*** START CODING YOUR FUNTIONS HERE ***///
void movement( int& delta_x)		// movement of the blocks. left, right.. it is easier to implement this in a function because of programmer readablity and less bugs 
{
            
	for (int i=0;i<4;i++)
       	{
        	point_1[i][0] += delta_x;
        }
        if (!anamoly())
        {
        	for (int i=0;i<4;i++)
       	{
        	point_1[i][0] -= delta_x;
        }
        }
        
        delta_x = 0;
            
}
void rotation(bool& rotate)			/// Rotation of the blocks . it is easier to implement this in a function because of programmer readablity and less bugs 
{
	if (rotate)
	{
		
		for (int i=0; i<4; i++)
		{
			int x = point_1[i][1] - point_1[1][1]; 		// for x axis rotation  // point of x axis rotation  = point[1][0]
			int y = point_1[i][0] - point_1[1][0];		// for y axis rotation	// point of y axis rotation = point[1][1]
			point_1[i][0] = point_1[1][0] - x;
			point_1[i][1] = point_1[1][1] + y;	
		}
		
		
		for (int i=0;i<4;i++)
       	{
       		while(point_1[i][0]<0)
			{
	        	for (int j=0;j<4;j++)
	       			point_1[j][0] += 1;
	       	}
       		while(point_1[i][0]>=N)
			{
	   			for (int j=0;j<4;j++)
        			point_1[j][0] -= 1;
        	}
        }
		
		
	}
	rotate = false;
}

void Completeline(int& score)			/// checks if the line is completed then pops the rows .it is easier to implement this in a function because of programmer readablity and less bugs 
{
	int no_lines_popped = 0;			/// variable checking how many lines are popped.
	int line = M-1;						/// the line being checked
	for ( int i=line; i>0 ;--i)
	{
		int linecheck = 0;
		for(int j = 0; j<N; j++)
		{
			if (gameGrid[i][j] != 0)
			{
				linecheck++;
			}
			
			gameGrid[line][j] = gameGrid[i][j];
		}
		if ( linecheck < N )
		{	
			line -= 1; 
		}
		
		if ( linecheck  == N )
		{
			no_lines_popped += 1;
		}
	}
	
	switch (no_lines_popped)
	{
		case 1: 		// score awarded when 1 line is pooped
			score += 10 ;
			break;
		case 2:			// score awarded when 2 lines are pooped
			score += 30 ;
			break;
		case 3:			// score awarded when 3 line are pooped
			score += 60 ;
			break;
		case 4:			// score awarded when 4 line are pooped
			score += 100 ;
			break;
	}
}



bool Gameover()			// checks if the total no. of rows of the grid are completed then clears the grid because game is over .it is easier to implement this in a function because of programmer readablity and less bugs 
{
	int line = 0;
	int line_count = 0;
		
	for ( int j = 0; j < N; ++j )
	{
		if (gameGrid[0][j]) 
			line_count += 1;
		
		if (gameGrid[1][j]) 
			line_count += 1;
	}
	if ( line_count > 0 )
	{	
		line += 1; 
	}
	if (line != 0)
		return 1; 
	else
		return 0;
}

void Drop(bool& drop)			// makes hard drop when user presses spacebar key . it is easier to implement this in a function because of programmer readablity and less bugs 
{
	if (drop)
	{
		while(anamoly())
		{
			for (int i=0;i<4;i++)
		    {
		        point_2[i][0]=point_1[i][0];
		        point_2[i][1]=point_1[i][1];
		        point_1[i][1]+=1;                   //How much units downward
		    }
		}
		for (int i=0;i<4;i++)
        {
            point_2[i][0]=point_1[i][0];
            point_2[i][1]=point_1[i][1];
            point_1[i][1]-=1;                   // the last block should be one less then the number of rows else it is an anamoly
        }
		drop = false;
	}
}
bool anamoly_of_shadow(int point_of_shadow[4][2])			// checks if there is an anamoly in the shadow (for example if thheir is a piece then the shadow forms above that piece.
{
	 for (int i=0;i<4;i++)
     {   if (point_of_shadow[i][0]<0 || point_of_shadow[i][0]>=N || point_of_shadow[i][1]>=M)
            return 0;
        else if (gameGrid[point_of_shadow[i][1]][point_of_shadow[i][0]])
            return 0;
     }
    return 1;
}

void shadow_display(int point_of_shadow[4][2])			//makes the point of shadow where it will be shown. it is easier to implement this in a function because of programmer readablity and less bugs 
{	
	for (int i=0;i<4;i++)
    {
	    point_of_shadow[i][0]=point_1[i][0];
        point_of_shadow[i][1]=point_1[i][1];				//How much units downward
    }
    while(anamoly_of_shadow(point_of_shadow))			// checks if there is an anomaly in those 4 co ordinates 
    {
    	for (int i=0;i<4;i++)
		{
			point_of_shadow[i][1] += 1; 					//moves the shadow downwards
		}
    }
    for (int i=0;i<4;i++)
	{
		point_of_shadow[i][1] += -1; 					//moves the shadow above other blocks
	} 
}


void update_highscore(int HighScores[4], int& score)			// Updates the high score of the player
{		
	for (int i = 0; i<5;i++)
	{
		if (score >	HighScores[i])
		{
			HighScores[i] = score;
		}
	}
}





///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////
