struct ITEM
{
    ITEM(int _x, int _y, int _z, int _weight);
    ~ITEM();

    // x = 폭, y = 너비, z = 높이
    // x = width, y = length, z = height
    int x;
    int y;
    int z;

    int weight;

    int xLocation;
    int yLocation;
    int zLocation;
};

ITEM::ITEM(int _x, int _y, int _z, int _weight)
{
    x = _x;
    y = _y;
    z = _z;
    weight = _weight;
    xLocation = 0;
    yLocation = 0;
    zLocation = 0;
};

ITEM::~ITEM()
{
    x = 0;
    y = 0;
    z = 0;
    weight = 0;
    xLocation = 0;
    yLocation = 0;
    zLocation = 0;
};

struct BAG
{
    BAG(int _x, int _y, int _z, int _maxCapacity);
    ~BAG();

    int x;
    int y;
    int z;

    int maxCapacity;

    int xLocation;
    int yLocation;
    int zLocation;
};

BAG::BAG(int _x, int _y, int _z, int _maxCapacity)
{
    x = _x;
    y = _y;
    z = _z;
    maxCapacity = _maxCapacity;
    xLocation = 0;
    yLocation = 0;
    zLocation = 0;
};

BAG::~BAG()
{
    x = 0;
    y = 0;
    z = 0;
    maxCapacity = 0;
    xLocation = 0;
    yLocation = 0;
    zLocation = 0;
};

struct ITEMLIST
{
	ITEM* item;
	ITEMLIST* nextItem;
};
