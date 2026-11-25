//Name : Mattee ul haq Ghauri
//Roll no.: 22i-0989
//project




/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You don't need to change anything in the driver code/main function except the part(s) where instructed.
 * You are expected to define your functionalities in the "functionality.h" header and call them here in the instructed part(s).
 * The game is started with a small box, you need to create other possible in "pieces.h" file in form of array.
    E.g., Syntax for 2 pieces, each having four coordinates -> int Pieces[2][4];
 * Load the images into the textures objects from img directory.
 * Don't make any changes to the "utils.h" header file except for changing the coordinate of screen or global variables of the game.
 * SUGGESTION: If you want to make changes in "utils.h", do it once you complete rest of the functionalities.
 * TIP: You can study SFML for drawing scenes, sprites and window.
 * */

#include <SFML/Graphics.hpp>
#include <time.h>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
using namespace sf;
int main()
{
    srand(time(0));
    RenderWindow window(VideoMode(320, 480), title);
    Texture obj1, obj2, obj3, obj4, obj5, obj6, obj7, obj8, obj9;
    /*
        Load "frames.png","tiles.png" and "background.png" for Texture objects
    */
        obj1.loadFromFile( "img/tiles.png");
        obj2.loadFromFile("img/background.png");
        obj3.loadFromFile( "img/frame.png");
        obj4.loadFromFile("img/shadow.png");
    	obj5.loadFromFile("img/Tetris.png");
    	obj6.loadFromFile("img/Levels.png");
    	obj7.loadFromFile("img/pausemenu.png");
    	obj8.loadFromFile("img/Gameover.png");
    	obj9.loadFromFile("img/Highscores.png");
    	
    Sprite sprite(obj1), background(obj2), frame(obj3), shadow(obj4), menu(obj5), level(obj6), pausemenu(obj7), Game_over(obj8);
    Sprite highscores(obj9);
    int delta_x=0, colorNum=1, gamestate = 1;			// game has different states (1 = main menu, 2= levels, 3 = gameover, 4 = highscores, 5 = Pause))
	int color_of_piece;
    float timer=0, delay=0.3;
    bool rotate=0, drop = false;
    int score= 0, difficulty = 0;
    int next1 = rand() %7, next2 =rand()%7 , next3 = rand()%7;
    
    Clock clock;
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;

        //---Event Listening Part---//
        Event e;
        while (window.pollEvent(e))
        {                    				   			   //Event is occurring - until the game is in running state
            if (e.type == Event::Closed)                   //If cross/close is clicked/pressed
                window.close();                            //Opened window disposes
            if (e.type == Event::KeyPressed) 
            {        									   //If any other key (not cross) is pressed
                if (e.key.code == Keyboard::Up)            //Check if the other key pressed is UP key
                {
                    rotate = true;						   //Rotation gets on
                    if (e.key.code != Keyboard::Up)
                    	rotate = false;
                }                            
                else if (e.key.code == Keyboard::Left)     //Check if the other key pressed is LEFT key
                {
                    delta_x = -1;                          //Change in X-Axis - Negative
                }    	
                else if (e.key.code == Keyboard::Right)    //Check if the other key pressed is RIGHT key
                {
                    delta_x = 1;     						//Change in X-Axis - Positive
                }
                else if (e.key.code == Keyboard:: Space)
                {
                	drop += 1;
                }
                else if ((e.key.code == Keyboard:: P)|| (e.key.code == Keyboard :: H))		// access pause menu
                {
                	gamestate = 5;
            		delay = 100000;	
            		if ( gamestate != 0 )
            		{
            			for ( int i = 0 ; i < 4; ++i )
            			{
		    			paused_position[i][0]=point_1[i][0];		// saving the game in the exact same current state
		    			paused_position[i][1]=point_1[i][1];
            			}
            			
            			for ( int i = 0 ; i < 4; ++i )
            			{
		    			point_1[i][0] = 0;						// assign point_1 = 0 so that if the user wants to start a new game the game down't start from the same position
		    			point_1[i][1] = 0;
            			}
            		}
                }
                ///***Checking game states***///
                switch (gamestate)
                {
                	case 1:			//Main menu
                		score = 0;
                		if (e.key.code == Keyboard::Num1)		// play
						{
							gamestate = 2;
						}
							
						
						else if (e.key.code == Keyboard::Num2)	// highscores
						{
							gamestate = 4;
						}
						
						else if (e.key.code == Keyboard::Num3)	// Quit
							window.close();
                		break;
                	case 2: 		//Levels
                		if (e.key.code == Keyboard::Num1)		// Easy
                		{
                			difficulty = 1;
                			delay = 0.3/difficulty;
                			for (int i=0;i<4;i++)
							{
								point_1[i][0]=0;
								point_1[i][1]=0;
							}
							///***Sets the grid to the initial value of zero so the game starts again instead of the blocks remaining there***///
							for (int i = 0; i<M ; i++)
							{
								for (int j= 0; j <N ; j++)
									gameGrid[i][j] =0;
							}
							gamestate = 0;				// game playing state
                			
                		}
                		else if (e.key.code == Keyboard::Num2)	// Hard
                		{
                			difficulty = 2;
                			delay = 0.3/difficulty;
                			
                			for (int i=0;i<4;i++)
							{
								point_1[i][0]=0;
								point_1[i][1]=0;
							}
							for (int i = 0; i<M ; i++)
							{
								for (int j= 0; j <N ; j++)
									gameGrid[i][j] =0;
							}
							gamestate = 0; 				// game playing state
                		}
                		
                		score =0;
                		break;
                	case 3:			//Game Over
                		
                		if (e.key.code == Keyboard::Num2)			// restart 
						{
							score =0;
							gamestate = 0;
							delay = (0.3/difficulty);
							for ( int i = 0 ; i < 4; ++i )
								{
									point_1[i][0]=0;
									point_1[i][1]=0;
								}
						}
						else if (e.key.code == Keyboard::Num1) 		// Go to main menu
						{
							gamestate = 1;
							score =0;
							for (int i = 0; i<M;i++)
							{
								for (int j= 0; j>N; j++)
								{
									gameGrid[i][j] = 0;
								}
							}
						}
						else if (e.key.code == Keyboard::Num4)			// Closes the game
							window.close();
                		break;
                	case 4:			// high scores
                		delay = 100000;
						if (e.key.code == Keyboard::Num1)		// Return to menu
						{	if (paused_position)
								gamestate = 5;
							else
								gamestate = 1;
						}	
                		break;
                	case 5: 			// Pause menu
                		if (e.key.code == Keyboard::Num1)		// Continue
                		{
                			
							gamestate = 0;
							delay = (0.3/difficulty);
							for ( int i = 0 ; i < 4; ++i )
							{
								point_1[i][0]=paused_position[i][0];
								point_1[i][1]=paused_position[i][1];
							}
						}
						else if (e.key.code == Keyboard::Num2)		// New game
						{
							gamestate = 2;
							
						}
						else if (e.key.code == Keyboard::Num3)		// highscores
						{
							gamestate = 4;
						}
						else if (e.key.code == Keyboard::Num4)		// Quit
						{
							window.close();
						}
						
				}
			
                		
                		break;
                	
                		
                    	
            } 
        }
        if (Keyboard::isKeyPressed(Keyboard::Down))   //Just another way to detect key presses without event listener
            delay=0.05;                                    //If DOWN key is pressed, delay in falling piece decreases from 0 to 0.05
        else 
        	delay = 0.3;

		

        ///////////////////////////////////////////////
        ///*** START CALLING YOUR FUNCTIONS HERE ***///
        if (Gameover())
		{
			gamestate = 3;
			
			
			for ( int i = 0 ; i < 4; ++i )
		    {
				point_1[i][0] = 0;
				point_1[i][1] = 0;
		   	}
		        		
		    delay = 100000;
		        		
		    for ( int i = 0; i < M ; ++i)
			{
				for ( int j = 0; j < N; ++j)
					gameGrid[i][j] = 0;
			}
			for ( int i = 0 ; i < 4; ++i )
            {
		    	paused_position[i][0]=point_1[i][0];
		    	paused_position[i][1]=point_1[i][1];
      	    }
		        			
		        
		} 
        fallingPiece(timer, delay, colorNum, difficulty, next1, next2, next3);               //Example: fallingPiece() function is called here
        nextpieces(timer, delay,nextpiece_1, nextpiece_2, nextpiece_3, next1, next2, next3, difficulty);
        shadow_display(point_of_shadow);
        movement(delta_x);
        Drop(drop);   
        rotation(rotate);
        Completeline(score);
       // new_high_score(high_score, score, score_check);
        
        
        
        ///*** YOUR CALLING STATEMENTS END HERE ***///
        
        
        //////////////////////////////////////////////
        window.clear(Color::Black);
        window.draw(background);
        ///***scores***///
        Font font;
		font.loadFromFile("img/Robot_Dreamer.otf"); // font of the game
		Text game_score, score_txt;
		game_score.setPosition(260,300);
		game_score.setCharacterSize(28);
		game_score.setFont(font);
		game_score.setFillColor(Color::White);
		game_score.setString(std::__cxx11::to_string(score));
		score_txt.setPosition(230,270);
		score_txt.setCharacterSize(22);
		score_txt.setFont(font);
		score_txt.setFillColor(Color::White);
		score_txt.setString("Score:");
		
		///*** Highscores***///
		Text highscore, highscore_1, highscore_2, highscore_3, highscore_4;
		
		
		// First high score 5000
		highscore.setPosition(138,140);
		highscore.setFont(font);
		highscore.setCharacterSize(15);
		highscore.setFillColor(Color::White);
		highscore.setString(std::__cxx11::to_string(HighScores[0]));
		
		// Second highscore 4000
		highscore_1.setPosition(138,160);
		highscore_1.setFont(font);
		highscore_1.setCharacterSize(15);
		highscore_1.setFillColor(Color::White);
		highscore_1.setString(std::__cxx11::to_string(HighScores[1]));
		
		//Third highscore 3000
		
		highscore_2.setPosition(138,180);
		highscore_2.setFont(font);
		highscore_2.setCharacterSize(15);
		highscore_2.setFillColor(Color::White);
		highscore_2.setString(std::__cxx11::to_string(HighScores[2]));
		
		//4 highscore 2000
		
		highscore_3.setPosition(138,200);
		highscore_3.setFont(font);
		highscore_3.setCharacterSize(15);
		highscore_3.setFillColor(Color::White);
		highscore_3.setString(std::__cxx11::to_string(HighScores[3]));
		
		
		// last high score 
		
		highscore_4.setPosition(138,220);
		highscore_4.setFont(font);
		highscore_4.setCharacterSize(15);
		highscore_4.setFillColor(Color::White);
		highscore_4.setString(std::__cxx11::to_string(HighScores[4]));
		
        for (int i=0; i<M; i++){
            for (int j=0; j<N; j++){
                if (gameGrid[i][j]==0)
                    continue;
                sprite.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
                sprite.setPosition(j*18,i*18);
                sprite.move(28,31); //offset
                window.draw(sprite);
            }
        }
        
        ///***Next pieces***///
        ///***next piece 1 ***///
        for (int i=0; i<4; i++)
        {
		    sprite.setTextureRect(IntRect(colorNum*18,0,18,18));
		    sprite.setPosition(((nextpiece_1[i][0]*18)+252),((nextpiece_1[i][1]*18)+36));
		    window.draw(sprite);
		}
		///***next piece 2 ***///
		
		for (int i=0; i<4; i++)
        {
		    sprite.setTextureRect(IntRect(colorNum*18,0,18,18));
		    sprite.setPosition(((nextpiece_2[i][0]*18)+252),((nextpiece_2[i][1]*18)+100));
		    window.draw(sprite);
		}
		
		///***next piece 3 ***///
		
		for (int i=0; i<4; i++)
        {
		    sprite.setTextureRect(IntRect(colorNum*18,0,18,18));
		    sprite.setPosition(((nextpiece_3[i][0]*18)+252),((nextpiece_3[i][1]*18)+200));
		    window.draw(sprite);
		}
        
        
        for (int i=0; i<4; i++){
            sprite.setTextureRect(IntRect(colorNum*18,0,18,18));
            sprite.setPosition(point_1[i][0]*18,point_1[i][1]*18);
            sprite.move(28,31);
            window.draw(sprite);
          }
          
          ///***Shadow***///
          
        for (int i=0; i<4; i++)
        {
		
		    shadow.setTextureRect(IntRect(colorNum*18,0,18,18));
		    shadow.setPosition(point_of_shadow[i][0]*18,point_of_shadow[i][1]*18);
		    shadow.move(28,31);
		    window.draw(shadow);
		}
		///***Tiles of the game***///
		for (int i=0; i<4; i++)
		{
		    sprite.setTextureRect(IntRect(colorNum*18,0,18,18));
		    sprite.setPosition(point_1[i][0]*18,point_1[i][1]*18);
		    sprite.move(28,31);
		    window.draw(sprite);
		}
		
        //---The Final on Which Everything is Drawn Over is Loaded---//
        window.draw(frame);
		window.draw(game_score);
		window.draw(score_txt);
		
		///***Game states***///
		switch (gamestate)
		{
			case 1 :					// Main menu state
				window.draw(menu);
				break;
			case 2:
				window.draw(level);		// Level select
				break;
			case 3: 					
				window.draw(Game_over);		// Game Over
				game_score.setPosition(144,80);
				game_score.setCharacterSize(50);
				score_txt.setPosition(144,80);
				score_txt.setCharacterSize(22);
				score_txt.setFont(font);
				score_txt.setFillColor(Color::White);
				score_txt.setString("Score:");
				window.draw(game_score);
				
				break;
			case 4:
				window.draw(highscores);
				highscore_4.setCharacterSize(20);
				highscore_3.setCharacterSize(20);
				highscore_2.setCharacterSize(20);
				highscore_1.setCharacterSize(20);
				highscore.setCharacterSize(20);
				
				highscore.setPosition(134,120);
				highscore_1.setPosition(134,150);
				highscore_2.setPosition(134,180);
				highscore_3.setPosition(134,210);
				highscore_4.setPosition(134,240);

				window.draw(highscore);
				window.draw(highscore_1);
				window.draw(highscore_2);
				window.draw(highscore_3);
				window.draw(highscore_4);
				break;
				
			case 5:
				window.draw(pausemenu);	
				break;			
		}
        //---The Window that now Contains the Frame is Displayed---//
        window.display();
        
        
    }
    return 0;
}
