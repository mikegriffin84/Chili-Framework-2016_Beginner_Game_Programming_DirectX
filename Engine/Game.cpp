/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		if (inhibitUp) 
		{
		}
		else
		{
			vy = vy + -1;
			inhibitUp = true;
		}	
	}
	else
	{
		inhibitUp = false;
	}
	
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		if (inhibitDown)
		{
		}
		else
		{
			vy = vy + 1;
			inhibitDown = true;
		}		
	}
	else
	{
		inhibitDown = false;
	}
	
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		if (inhibitLeft)
		{
		}
		else
		{
			vx = vx + -1;
			inhibitLeft = true;
		}	
	}
	else
	{
		inhibitLeft = false;
	}
	
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		if (inhibitRight)
		{
		}
		else
		{
			vx = vx + 1;
			inhibitRight = true;
		}
		 
	}
	else
	{
		inhibitRight = false;
	}
	
	VertMove = VertMove + vy;
	HorMove = HorMove + vx;
	
	
	/*
	if (HorMove >= (gfx.ScreenWidth   / 4) &&
		HorMove <= (gfx.ScreenWidth   / 4) &&
		VertMove >= (gfx.ScreenHeight / 4) &&
		VertMove <= (gfx.ScreenHeight / 4))
	{
		DrawReticle(HorMove, VertMove, 150, 150, 255);
	}
	*/
	/*else
	{
		RedC = 255;
		GreenC = 255;
		BlueC = 255;

	}*/

	// Keep cursor from going outside of bounds.
	if (HorMove + 8 >= gfx.ScreenWidth)	
	{
		HorMove = gfx.ScreenWidth - 9;
	}
	if (HorMove - 8 < 0)
	{
		HorMove = 8;
	}
	if (VertMove + 8 >= gfx.ScreenHeight)
	{
		VertMove = gfx.ScreenHeight - 9;
	}
	if (VertMove - 8 < 0)
	{
		VertMove = 8;
	}

	//HorMove >= 189 && HorMove <= 211
	/*if (HorMove >= 150 && HorMove <= 250)
	{
		if (VertMove >= 214 && VertMove <= 236)
		{
			RedC = 255;
			GreenC = 125;
			BlueC = 125;
		}
	}
	*/
	shapeIsChanged = wnd.kbd.KeyIsPressed(VK_SHIFT);

	colorIsChanged = wnd.kbd.KeyIsPressed(VK_CONTROL);
	
	colliding = OverlapTest(HorMove, VertMove, HorMoveModifier, VertMoveModifier);
}

void Game::ComposeFrame()
{
		DrawReticle(HorMove, VertMove, RedC, GreenC, BlueC);

		DrawModifierBox(HorMoveModifier, VertMoveModifier, modifierRedC, modifierGreenC, modifierBlueC);
	
		if (colorIsChanged)
		{
			DrawReticle(HorMove, VertMove, 255, 255, 0);
		}

		if (colliding)
		{
			DrawReticle(HorMove, VertMove, 255, 0, 0);
		}
		/*else
		{
			DrawReticle(HorMove, VertMove, 255, 255, 255);
		}*/

}

void Game::DrawReticle(int x, int y, int r, int g, int b)
{
	if (shapeIsChanged)
	{
		//Square cube-reticle is 17x17 pixels
		//Top Left of Square Reticle
		gfx.PutPixel(x + -5, y + -8, r, g, b);
		gfx.PutPixel(x + -6, y + -8, r, g, b);
		gfx.PutPixel(x + -7, y + -8, r, g, b);
		gfx.PutPixel(x + -8, y + -8, r, g, b);
		gfx.PutPixel(x + -8, y + -7, r, g, b);
		gfx.PutPixel(x + -8, y + -6, r, g, b);
		gfx.PutPixel(x + -8, y + -5, r, g, b);

		//Bottom Left of Square Reticle
		gfx.PutPixel(x + -5, y + 8, r, g, b);
		gfx.PutPixel(x + -6, y + 8, r, g, b);
		gfx.PutPixel(x + -7, y + 8, r, g, b);
		gfx.PutPixel(x + -8, y + 8, r, g, b);
		gfx.PutPixel(x + -8, y + 7, r, g, b);
		gfx.PutPixel(x + -8, y + 6, r, g, b);
		gfx.PutPixel(x + -8, y + 5, r, g, b);

		//Top Right of Square Reticle
		gfx.PutPixel(x + 5, y + -8, r, g, b);
		gfx.PutPixel(x + 6, y + -8, r, g, b);
		gfx.PutPixel(x + 7, y + -8, r, g, b);
		gfx.PutPixel(x + 8, y + -8, r, g, b);
		gfx.PutPixel(x + 8, y + -7, r, g, b);
		gfx.PutPixel(x + 8, y + -6, r, g, b);
		gfx.PutPixel(x + 8, y + -5, r, g, b);

		//Bottome Right of Square Reticle
		gfx.PutPixel(x + 5, y + 8, r, g, b);
		gfx.PutPixel(x + 6, y + 8, r, g, b);
		gfx.PutPixel(x + 7, y + 8, r, g, b);
		gfx.PutPixel(x + 8, y + 8, r, g, b);
		gfx.PutPixel(x + 8, y + 7, r, g, b);
		gfx.PutPixel(x + 8, y + 6, r, g, b);
		gfx.PutPixel(x + 8, y + 5, r, g, b);

		if (shapeIsChanged && colorIsChanged)
		{
			//Square cube-reticle is 17x17 pixels
			//Top Left of Square Reticle
			gfx.PutPixel(x + -5, y + -8, r, g, b);
			gfx.PutPixel(x + -6, y + -8, r, g, b);
			gfx.PutPixel(x + -7, y + -8, r, g, b);
			gfx.PutPixel(x + -8, y + -8, r, g, b);
			gfx.PutPixel(x + -8, y + -7, r, g, b);
			gfx.PutPixel(x + -8, y + -6, r, g, b);
			gfx.PutPixel(x + -8, y + -5, r, g, b);

			//Bottom Left of Square Reticle
			gfx.PutPixel(x + -5, y + 8, r, g, b);
			gfx.PutPixel(x + -6, y + 8, r, g, b);
			gfx.PutPixel(x + -7, y + 8, r, g, b);
			gfx.PutPixel(x + -8, y + 8, r, g, b);
			gfx.PutPixel(x + -8, y + 7, r, g, b);
			gfx.PutPixel(x + -8, y + 6, r, g, b);
			gfx.PutPixel(x + -8, y + 5, r, g, b);

			//Middle of Square Reticle
			gfx.PutPixel(x + 0, y + 3, r, g, b);
			gfx.PutPixel(x + 0, y + 2, r, g, b);
			gfx.PutPixel(x + 0, y + 1, r, g, b);
			gfx.PutPixel(x + 0, y + 0, r, g, b);
			gfx.PutPixel(x + 0, y + -1, r, g, b);
			gfx.PutPixel(x + 0, y + -2, r, g, b);
			gfx.PutPixel(x + 0, y + -3, r, g, b);

			gfx.PutPixel(x + 3, y + 0, r, g, b);
			gfx.PutPixel(x + 2, y + 0, r, g, b);
			gfx.PutPixel(x + 1, y + 0, r, g, b);
			gfx.PutPixel(x + 0, y + 0, r, g, b);
			gfx.PutPixel(x + -1, y +0, r, g, b);
			gfx.PutPixel(x + -2, y +0, r, g, b);
			gfx.PutPixel(x + -3, y +0, r, g, b);

			//Top Right of Square Reticle
			gfx.PutPixel(x + 5, y + -8, r, g, b);
			gfx.PutPixel(x + 6, y + -8, r, g, b);
			gfx.PutPixel(x + 7, y + -8, r, g, b);
			gfx.PutPixel(x + 8, y + -8, r, g, b);
			gfx.PutPixel(x + 8, y + -7, r, g, b);
			gfx.PutPixel(x + 8, y + -6, r, g, b);
			gfx.PutPixel(x + 8, y + -5, r, g, b);

			//Bottome Right of Square Reticle
			gfx.PutPixel(x + 5, y + 8, r, g, b);
			gfx.PutPixel(x + 6, y + 8, r, g, b);
			gfx.PutPixel(x + 7, y + 8, r, g, b);
			gfx.PutPixel(x + 8, y + 8, r, g, b);
			gfx.PutPixel(x + 8, y + 7, r, g, b);
			gfx.PutPixel(x + 8, y + 6, r, g, b);
			gfx.PutPixel(x + 8, y + 5, r, g, b);
		}
	}
	else
	{
		//Bullseye is 17x17 pixels
		//Crosshair variables that move the crosshair from dead-center of screen
		gfx.PutPixel(x + -5, y + 0, r, g, b);
		gfx.PutPixel(x + -6, y + 0, r, g, b);
		gfx.PutPixel(x + -7, y + 0, r, g, b);
		gfx.PutPixel(x + -8, y + 0, r, g, b);
					 
		gfx.PutPixel(x + 5, y + 0, r, g, b);
		gfx.PutPixel(x + 6, y + 0, r, g, b);
		gfx.PutPixel(x + 7, y + 0, r, g, b);
		gfx.PutPixel(x + 8, y + 0, r, g, b);
					 		
		gfx.PutPixel(x + 0, y + -5, r, g, b);
		gfx.PutPixel(x + 0, y + -6, r, g, b);
		gfx.PutPixel(x + 0, y + -7, r, g, b);
		gfx.PutPixel(x + 0, y + -8, r, g, b);
					 		
		gfx.PutPixel(x + 0, y + 5, r, g, b);
		gfx.PutPixel(x + 0, y + 6, r, g, b);
		gfx.PutPixel(x + 0, y + 7, r, g, b);
		gfx.PutPixel(x + 0, y + 8, r, g, b);



	}
}

void Game::DrawModifierBox(int x, int y, int r, int g, int b)
{
	//Top Left of Square Reticle
	gfx.PutPixel(x + -5, y + -8, r, g, b);
	gfx.PutPixel(x + -6, y + -8, r, g, b);
	gfx.PutPixel(x + -7, y + -8, r, g, b);
	gfx.PutPixel(x + -8, y + -8, r, g, b);
	gfx.PutPixel(x + -8, y + -7, r, g, b);
	gfx.PutPixel(x + -8, y + -6, r, g, b);
	gfx.PutPixel(x + -8, y + -5, r, g, b);

	//Bottom Left of Square Reticle
	gfx.PutPixel(x + -5, y + 8, r, g, b);
	gfx.PutPixel(x + -6, y + 8, r, g, b);
	gfx.PutPixel(x + -7, y + 8, r, g, b);
	gfx.PutPixel(x + -8, y + 8, r, g, b);
	gfx.PutPixel(x + -8, y + 7, r, g, b);
	gfx.PutPixel(x + -8, y + 6, r, g, b);
	gfx.PutPixel(x + -8, y + 5, r, g, b);

	//Top Right of Square Reticle
	gfx.PutPixel(x + 5, y + -8, r, g, b);
	gfx.PutPixel(x + 6, y + -8, r, g, b);
	gfx.PutPixel(x + 7, y + -8, r, g, b);
	gfx.PutPixel(x + 8, y + -8, r, g, b);
	gfx.PutPixel(x + 8, y + -7, r, g, b);
	gfx.PutPixel(x + 8, y + -6, r, g, b);
	gfx.PutPixel(x + 8, y + -5, r, g, b);

	//Bottome Right of Square Reticle
	gfx.PutPixel(x + 5, y + 8, r, g, b);
	gfx.PutPixel(x + 6, y + 8, r, g, b);
	gfx.PutPixel(x + 7, y + 8, r, g, b);
	gfx.PutPixel(x + 8, y + 8, r, g, b);
	gfx.PutPixel(x + 8, y + 7, r, g, b);
	gfx.PutPixel(x + 8, y + 6, r, g, b);
	gfx.PutPixel(x + 8, y + 5, r, g, b);
}

bool Game::OverlapTest(int box0x, int box0y, int box1x, int box1y)
{
	//Collide check logic of cursor and modifier
	const int left_box0 = box0x - 8;
	const int right_box0 = box0x + 8;
	const int top_box0 = box0y - 8;
	const int bottom_box0 = box0y + 8;
	
	const int left_box1 = box1x - 8;
	const int right_box1 = box1x + 8;
	const int top_box1 = box1y - 8;
	const int bottom_box1 = box1y + 8;

	return
		left_box0 <= right_box1  &&
		right_box0 >= left_box1   &&
		top_box0 <= bottom_box1 &&
		bottom_box0 >= top_box1;
}
