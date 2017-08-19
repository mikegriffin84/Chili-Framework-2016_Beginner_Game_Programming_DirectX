/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;

	/*********************************/
	//My added functions
	void DrawReticle(int x, int y, int r, int g, int b);
	void DrawModifierBox(int x, int y, int r, int g, int b);
	bool OverlapTest(int box0x, int box0y, int box1x, int box1y);

	/********************************/
	/*  User Variables              */
	/*Adjust Cursor start location 
	751 = middle of x axis 
	501 = middle of y axis*/
	int HorMove = 400;
	int VertMove = 350;
	/********************************/
	//Adjust Modifier cube location
	int HorMoveModifier = 200;
	int VertMoveModifier = 225;
	/********************************/
	int vx = 0;
	int vy = 0;
	//is a variable used to toggle the color of the cursor
	int RedC = 255;
	int GreenC = 255;
	int BlueC = 255;

	int gb = 255;
	
	//Collide variable
	bool colliding = false;
		
	/********************************/
	//Controls the 3 colors of the Modifier Square
	int modifierRedC = 0;
	int modifierGreenC = 255;
	int modifierBlueC = 0;
	/********************************/
	bool shapeIsChanged = false;
	bool colorIsChanged = false;
	bool inhibitUp = false;
	bool inhibitDown = false;
	bool inhibitLeft = false;
	bool inhibitRight = false;
	/********************************/
};