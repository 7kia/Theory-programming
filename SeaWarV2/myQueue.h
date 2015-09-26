void ifMyQueue(int &numberX, int &numberY, int &countEnemyDestroyShips, int &victoryNumber,
	char (*enemyPlace)[sizeRectangleWeb], int (*coordinatesEnemyShips)[4],
	bool &isNotFindEnd, bool &isFindStart, bool &gameNotFinish, bool &myQueue)
{

	// Если мы нажимаем в области поля противника
	if ((numberX < sizeRectangleWeb - 1) && (numberX > 0) && (numberY < sizeRectangleWeb - 1) && (numberY > 0))
	{
		if (enemyPlace[numberY][numberX] == 'X' || enemyPlace[numberY][numberX] == '0')
		{
			printf("You here already shot!\n");
		}
		else if (enemyPlace[numberY][numberX] == '#')
		{
			enemyPlace[numberY][numberX] = 'X';

			///////////////////////////////////////////////
			// Проверка свободного места
			int lastX = numberX;
			int lastY = numberY;
			int dirCount(0);

			for (int directionFind = 1; directionFind <= 4; directionFind++)
			{
				x = lastX;
				y = lastY;
				while (enemyPlace[y][x] == 'X')
				{
					switch (directionFind)
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

				if (enemyPlace[y][x] != '#')
				{
					printf("%d %d\n", x, y);
					dirCount++;
				}
				else
				{
					dirCount = 0;
					break;
				}
			}
			///////////////////////////////////////////////

			if (dirCount)
			{
				printf("Ship is DESTROY!\n");
				countEnemyDestroyShips += 1;
			}
			else
			{
				printf("Ship is damage!\n");
			}

			if (countEnemyDestroyShips == victoryNumber)
			{
				printf("//////////////////////\n");
				printf("	My victory!\n");
				printf("//////////////////////\n");
				gameNotFinish = !gameNotFinish;
			}
		}
		else
		{
			enemyPlace[numberY][numberX] = '0';
			myQueue = !myQueue;
		}
	}


}
