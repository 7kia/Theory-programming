void enemyQueue(char(*myPlace)[sizeRectangleWeb], int &direction,
	int &countMyDestroyShips, int &victoryNumber, int *lastTile,
	int(*coordinatesMyShips)[4], int(*memberDirection),
	bool &findDirection, bool &findShip, bool &myQueue, bool &gameNotFinish,
	int &x, int &y)
{

	if (findShip)
	{
		if (findDirection)
		{
			/////////////////////////////////////////////
			// ���� ����� �����������

			switch (direction)
			{
			case direction::Up:
				//x = x;
				y = y + 1;
				break;
			case direction::Down:
				//x = lastTile[0];
				y = y - 1;
				break;
			case direction::Left:
				x = x + 1;
				//y = lastTile[1];
				break;
			case direction::Right:
				x = x - 1;
				//y = lastTile[1];
				break;
			}

			/////////////////////////////////////////////
			// ������������ � ����� �����������
			while (myPlace[y][x] == '#')
			{
				myPlace[y][x] = 'X';

				switch (direction)
				{
				case direction::Up:
					y = y + 1;
					break;
				case direction::Down:
					y = y - 1;
					break;
				case direction::Left:
					x = x + 1;
					break;
				case direction::Right:
					x = x - 1;
					break;
				}

			}
			///////////////////////////////////////////

			// ��������� �� ��������� ������������ ������
			switch (direction)
			{
			case direction::Up:
				//x = x;
				y = lastTile[1] - 1;
				break;
			case direction::Down:
				//x = lastTile[0];
				y = lastTile[1] + 1;
				break;
			case direction::Left:
				x = lastTile[0] - 1;
				//y = lastTile[1];
				break;
			case direction::Right:
				x = lastTile[0] + 1;
				//y = lastTile[1];
				break;
			}

			//////////////////////////////////////////////////////
			// ������������ � ��������������� �����������
			while (myPlace[y][x] == '#')
			{
				myPlace[y][x] = 'X';

				switch (direction)
				{
				case direction::Up:
					//x = x;
					y = y - 1;
					break;
				case direction::Down:
					//x = lastTile[0];
					y = y + 1;
					break;
				case direction::Left:
					x = x - 1;
					//y = lastTile[1];
					break;
				case direction::Right:
					x = x + 1;
					//y = lastTile[1];
					break;
				}

			}
			///////////////////////////////////////////
			findShip = findDirection = false;
			countMyDestroyShips += 1;

			//////////////////////////////////
			// �������� �����������
			for (int i = 0; i < 3; i++)
			{
				memberDirection[i] = 0;
			}

		}
		else
		{
			//////////////////////////////////////////////////////////////
			// ���� ����������
			do
			{
				direction = 1 + +rand() % 4;

				switch (direction)
				{
				case direction::Up:
					x = lastTile[0];
					y = lastTile[1] + 1;
					break;
				case direction::Down:
					x = lastTile[0];
					y = lastTile[1] - 1;
					break;
				case direction::Left:
					x = lastTile[0] + 1;
					y = lastTile[1];
					break;
				case direction::Right:
					x = lastTile[0] - 1;
					y = lastTile[1];
					break;
				}
			} while ((myPlace[y][x] == 'X' || myPlace[y][x] == '0')// � ��� ������������ ������ �� ������������
				&& (x < sizeRectangleWeb) && (x > 0) && (y < sizeRectangleWeb) && (y > 0));// �������� �� ����� �� ������� 
																						   /////////////////////////////////////////////

			if (myPlace[y][x] == '#')
			{
				myPlace[y][x] = 'X';
				findDirection = true;

			}
			else
			{
				/////////////////////////////////////////
				// ���� �� ������ ���������� ����������� � ���� ������
				myQueue = !myQueue;
				myPlace[y][x] = '0';

				for (int i = 0; i < 3; i++)
				{
					if (memberDirection[i] == 0)
					{
						memberDirection[i] = direction;
					}
				}
				/////////////////////////////////////////
			}
			///////////////////////////////////////////////////////////////
		}
	}
	else
	{
		/////////////////////////////////////////////////
		// ���� �������
		do
		{
			x = 1 + rand() % (sizeRectangleWeb - 1);
			y = 1 + rand() % (sizeRectangleWeb - 1);
		} while (myPlace[y][x] == 'X' || myPlace[y][x] == '0');

		if (myPlace[y][x] == '#')
		{
			myPlace[y][x] = 'X';

			/////////////////////////////////////////////////////////////////////
			// ���� ���������� ������ � ����� �� ���������
			// �� ������ �� ����� ���������-��������� �������.

			for (int i = 0; i < 10 - 1; i++)
			{
				// ���� ���������� ������ � ����� ���������
				if (x == coordinatesMyShips[i][0] && x == coordinatesMyShips[i][2]
					&& y == coordinatesMyShips[i][1] && y == coordinatesMyShips[i][3])
				{
					findShip = findDirection = false;

					for (int i = 0; i < 3; i++)
					{
						memberDirection[i] = 0;
					}

					countMyDestroyShips += 1;
					break;
				}
				else
				{
					lastTile[0] = x;
					lastTile[1] = y;
					findShip = true;
				}

			}
			//////////////////////////////////////////////////////////////////////

		}
		else
		{
			myPlace[y][x] = '0';
			myQueue = !myQueue;
		}
		/////////////////////////////////////////////////
	}


	if (countMyDestroyShips == victoryNumber)
	{
		printf("//////////////////////\n");
		printf("	Defeat !\n");
		printf("//////////////////////\n");
		gameNotFinish = !gameNotFinish;
	}


}
