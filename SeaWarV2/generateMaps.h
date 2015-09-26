void generateMaps(const int amountShips, 
	const int *amountEveryType, char(*myPlace)[sizeRectangleWeb], char(*enemyPlace)[sizeRectangleWeb],
	int(*coordinatesMyShips)[4], int(*coordinatesEnemyShips)[4])
{
	int sizeShip(0);
	int countMyShips(0), countEnemyShips(0);

	///////////////////////////////////////////////
	// �������� ������� ���� 
	int i, j;

	for (i = 0; i < sizeRectangleWeb; i++)
	{
		for (j = 0; j < sizeRectangleWeb; j++)
		{
			myPlace[i][j] = '_';
			enemyPlace[i][j] = '_';
		}
	}
	///////////////////////////////////////////////

	///////////////////////////////////////////////
	// ��������� �������� 
	int x, y, leftEdge, rightEdge;
	bool positionNotFind(true), directionUp(false), isEmptyTiles(true), condition;

	srand(time(0)); // �������������� ������������


	///////////////////////////////////////////////
	// ��������� ���� �������� 
	for (sizeShip = 0; sizeShip < 4; sizeShip++)
	{
		// ��� ������ �������� ����� �������� ���������� ��������
		for (int countType = 0; countType < amountEveryType[sizeShip]; countType++)
		{
			while (positionNotFind)
			{
				x = 1 + rand() % (sizeRectangleWeb - sizeShip - 2);
				y = 1 + rand() % (sizeRectangleWeb - sizeShip - 2);
				directionUp = 0 + rand() % 2;

				leftEdge = -1;
				rightEdge = sizeShip + 1;

				//////////////////////////////////////////////////////////
				// �������� �����������
				if (directionUp)
				{
					///////////////////////////////////////////////
					// �������� ���������� �����
					while (leftEdge <= rightEdge)
					{

						condition = (myPlace[y + leftEdge][x] == '#')
							|| (myPlace[y + leftEdge][x - 1] == '#')
							|| (myPlace[y + leftEdge][x + 1] == '#');

						if (condition)
						{
							isEmptyTiles = false;
							positionNotFind = true;
							break;
						}
						leftEdge += 1;
					}
					///////////////////////////////////////////////

					///////////////////////////////////////////////
					// ��������� �������
					if (isEmptyTiles)
					{
						positionNotFind = false;
						for (i = 0; i <= sizeShip; i++)
						{
							myPlace[y + i][x] = '#';
							if (i == 0)
							{
								coordinatesMyShips[countMyShips][0] = x;
								coordinatesMyShips[countMyShips][1] = y + i;
								if (sizeShip == 0)
								{
									coordinatesMyShips[countMyShips][2] = x;
									coordinatesMyShips[countMyShips][3] = y + i;
									countMyShips += 1;
								}
							}
							else if (i == sizeShip)
							{
								coordinatesMyShips[countMyShips][2] = x;
								coordinatesMyShips[countMyShips][3] = y + i;
								countMyShips += 1;
							}
						}
					///////////////////////////////////////////////

					}
				//////////////////////////////////////////////////////////
				}
				else
				{
					///////////////////////////////////////////////
					// �������� ���������� �����
					while (leftEdge <= rightEdge)
					{
						condition = (myPlace[y][x + leftEdge] == '#')
							|| (myPlace[y - 1][x + leftEdge] == '#')
							|| (myPlace[y + 1][x + leftEdge] == '#');
						
						if (condition)
						{
							isEmptyTiles = false;
							positionNotFind = true;;
							break;
						}
						leftEdge += 1;
					}
					///////////////////////////////////////////////

					///////////////////////////////////////////////
					// ��������� �������
					if (isEmptyTiles)
					{
						positionNotFind = false;
						for (i = 0; i <= sizeShip; i++)
						{
							myPlace[y][x + i] = '#';
							if (i == 0)
							{
								coordinatesMyShips[countMyShips][0] = x + i;
								coordinatesMyShips[countMyShips][1] = y;
								if (sizeShip == 0)
								{
									coordinatesMyShips[countMyShips][2] = x + i;
									coordinatesMyShips[countMyShips][3] = y;
									countMyShips += 1;

								}

							}
							else if (i == sizeShip)
							{
								coordinatesMyShips[countMyShips][2] = x + i;
								coordinatesMyShips[countMyShips][3] = y;
								countMyShips += 1;
							}
						}
					}
					///////////////////////////////////////////////
				}
				///////////////////////////////////////////////

				isEmptyTiles = true;
			}

			positionNotFind = true;
		}

	}


	///////////////////////////////////////////////
	// ��������� ��������� ��������
	for (sizeShip = 0; sizeShip < 4; sizeShip++)
	{
		// ��� ������ �������� ����� �������� ���������� ��������
		for (int countType = 0; countType < amountEveryType[sizeShip]; countType++)
		{
			while (positionNotFind)
			{
				x = 1 + rand() % (sizeRectangleWeb - sizeShip - 2);
				y = 1 + rand() % (sizeRectangleWeb - sizeShip - 2);
				directionUp = 0 + rand() % 2;

				leftEdge = -1;
				rightEdge = sizeShip + 1;

				///////////////////////////////////////////////
				// �������� �����������
				if (directionUp)
				{
					///////////////////////////////////////////////
					// �������� ���������� �����
					while (leftEdge <= rightEdge)
					{
						condition = (enemyPlace[y + leftEdge][x] == '#')
							|| (enemyPlace[y + leftEdge][x - 1] == '#')
							|| (enemyPlace[y + leftEdge][x + 1] == '#');

						if (condition)
						{
							isEmptyTiles = false;
							positionNotFind = true;
							break;
						}
						leftEdge += 1;
					}
					///////////////////////////////////////////////

					///////////////////////////////////////////////
					// ��������� �������
					if (isEmptyTiles)
					{
						positionNotFind = false;
						for (i = 0; i <= sizeShip; i++)
						{
							enemyPlace[y + i][x] = '#';
							if (i == 0)
							{
								coordinatesEnemyShips[countEnemyShips][0] = x;
								coordinatesEnemyShips[countEnemyShips][1] = y + i;
								if (sizeShip == 0)
								{
									coordinatesEnemyShips[countEnemyShips][2] = x;
									coordinatesEnemyShips[countEnemyShips][3] = y + i;
									countEnemyShips += 1;

								}
							}
							else if (i == sizeShip)
							{
								coordinatesEnemyShips[countEnemyShips][2] = x;
								coordinatesEnemyShips[countEnemyShips][3] = y + i;
								countEnemyShips += 1;
							}
						}
					}
					///////////////////////////////////////////////
				}
				else
				{
					///////////////////////////////////////////////
					// �������� ���������� �����
					while (leftEdge <= rightEdge)
					{

						condition = (enemyPlace[y][x + leftEdge] == '#')
							|| (enemyPlace[y - 1][x + leftEdge] == '#')
							|| (enemyPlace[y + 1][x + leftEdge] == '#');
						
						if (condition)
						{
							isEmptyTiles = false;
							positionNotFind = true;;
							break;
						}
						leftEdge += 1;
					}
					///////////////////////////////////////////////

					///////////////////////////////////////////////
					// ��������� �������
					if (isEmptyTiles)
					{
						positionNotFind = false;
						for (i = 0; i <= sizeShip; i++)
						{
							enemyPlace[y][x + i] = '#';
							if (i == 0)
							{
								coordinatesEnemyShips[countEnemyShips][0] = x + i;
								coordinatesEnemyShips[countEnemyShips][1] = y;
								if (sizeShip == 0)
								{
									coordinatesEnemyShips[countEnemyShips][2] = x + i;
									coordinatesEnemyShips[countEnemyShips][3] = y;
									countEnemyShips += 1;

								}
							}
							else if (i == sizeShip)
							{
								coordinatesEnemyShips[countEnemyShips][2] = x + i;
								coordinatesEnemyShips[countEnemyShips][3] = y;
								countEnemyShips += 1;

							}
						}

					}
					///////////////////////////////////////////////
				}
				///////////////////////////////////////////////

				isEmptyTiles = true;
			}

			positionNotFind = true;
		}

	}

	// ��������� ���� ��� ��������
	
	for (int countMaps = 0; countMaps < 2; countMaps++)
	{
		for (int countTile = 0; countTile < sizeRectangleWeb; countTile++)
		{
			for (int countTile2 = 0; countTile2 < sizeRectangleWeb; countTile2++)
			{
				if (countMaps)
				{

					printf("%c", enemyPlace[countTile][countTile2]);

				}
				else
				{
					printf("%c", myPlace[countTile][countTile2]);
				}
			}
			printf("\n");
		}
		printf("\n");
	}

	// ��� �������� ������������ ���������*/
	for (i = 0; i < 10; i++)
	{
		printf("%d value %d %d; %d %d\n", i, coordinatesEnemyShips[i][0],
			coordinatesEnemyShips[i][1], coordinatesEnemyShips[i][2],
			coordinatesEnemyShips[i][3]);

	}
	
}
