///////////////////////////////////////////////////////
// ���������� ��� ��������� ����
const int border(2);
const int amountShips(10), sizeRectangleWeb(12 + border); 
const int amountEveryType[] = { 4, 3, 2, 1 };
char myPlace[sizeRectangleWeb][sizeRectangleWeb];// ����
char enemyPlace[sizeRectangleWeb][sizeRectangleWeb];
int coordinatesMyShips[amountShips][4];// ������ ������ � ����� �������
int coordinatesEnemyShips[amountShips][4];
///////////////////////////////////////////////////////

////////////////////////////////////////
// ���������� ������ ����������
int countMyDestroyShips(0), countEnemyDestroyShips(0);// ������� ���� � ��������� ��������
int victoryNumber(10);// ����� ��������� ������ ����������� ��� ������
int lastTile[] = { -1, -1 };// ������ ������ ��������� � ���� ����
int direction, x, y;// ����������� �������
bool findDirection(false);
bool directionNotRedefine(true);
bool findShip(false);// ���� ������� ������� 2 ������ �� ���������� ��������� �����
int memberDirection[] = { 0, 0, 0 };
/////////////////////////////////////////

/////////////////////////////////////////
// ��������� ����
bool gameNotFinish(true);
bool myQueue(true);
/////////////////////////////////////////

/////////////////////////////////////////
// ��� ������ ��������� � ��������� ������� ��������
bool isFindStart(false);
bool isNotFindEnd(true);
bool isNotDestroyShip(true);
int countTile(0);
/////////////////////////////////////////

enum stateTile
{
	Unknow,
	Empty,
	isShip,
	shipDestroy
};

enum direction
{
	None,
	Up,
	Down,
	Left,
	Right,
	Up_Left,
	Up_Right,
	Down_Left,
	Down_right
};