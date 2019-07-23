#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <algorithm>
#include <random>

long long int convertKey(std::string key) //gets the decimal representation of the key. reason its Long not int is due to the greater size needed
{
	long long int temp = 0;
	for (int x = 0; x < key.size(); x++)
	{
		if (key.at(x) == '1')
		{
			temp += pow(2, key.size() - x - 1);
		}
	}
	return temp;
}

long long int convertTheta(int input, int keyPos, long long int rand, int num1, std::string key, int mode, int maxShift) //converts theta from unscrambled to scrambled, and back again
{
	long long int temp = (input + 180) % 360;
	long long int addon = ((int)pow(-1, num1 + (key.at(keyPos) - '0')) * rand * key.size()) % maxShift;
	temp = temp + (addon * (int)(pow(-1,mode+1))); //adds if mode is odd, subtracts is mode is even
	if (temp < 0)
		temp = 360 + temp;
	return temp % 360;
}

long long int convertCoord(int input, int keyPos, long long int rand, int minOther, int max, int min, std::string key, int mode) //converts spatial coordinates from unscrambled to scrambled, and vice versa
{

	long long int temp = input;
	long long int addon = (int)(pow(-1, minOther + (key.at(keyPos) - '0')))*rand;
	temp = temp + (addon * (int)(pow(-1, mode + 1)));
	while (temp < (min + 1))
		temp = (max - 1) - ((min + 1) - temp - 1);
	while (temp > max - 1)
		temp = (temp - (max - 1)) + min;
	return temp;
}

struct minutia //structure used to hold information for each minutia
{
	int x,y,theta,quality;
};

bool operator<(minutia a, minutia b) //following operators are used to sort the minutia. Follows scheme found in original .xyt files
{
	if (a.x < b.x)
	{
		return true;
	}
	if (a.x == b.x)
	{
		if (a.y > b.y)
		{
			return true;
		}
	}
	return false;
}

bool operator>(minutia a, minutia b)
{
	if (a.x > b.x)
	{
		return true;
	}
	if (a.x == b.x)
	{
		if (a.y < b.y)
		{
			return true;
		}
	}
	return false;
}

std::ostream& operator<<(std::ostream &strm, minutia m)
{
	return strm << m.x << " " << m.y << " " << m.theta << " " << m.quality << "\n";
}

int main(int argc, char * argv[])
{
	if (argc < 5)
	{
		std::cout << "This command requires four arguments: path to the .xyt file, path to new file, key, and mode(scramble or unscramble) \n";
		exit(-1);
		
	} 


	std::ifstream original;
	std::ofstream edited;
	std::string ipath, opath;
	int count = 0;
	int circulator = 0;
	std::string key = argv[3]; //keep key simple, might not need letters 
	int num1, num0, mode, maxX, maxY, minX, minY; //use these sizes when scrambling x and y
	num1 = 0;
	num0 = 0;
	ipath = argv[1]; 
	opath = argv[2];
	mode = *argv[4] - '0'; //1 to scramble, 2 to unscramble
	maxX = maxY = INT_MIN;
	minX = minY = INT_MAX;
	


	for (int x = 0; x < key.size(); x++)
	{
		if (key.at(x) % 2 == 1)
			num1++;
		else
			num0++;
	}
	
	original.open(ipath);
	edited.open(opath);

	if (!original || !edited)
	{
		std::cout << "ERROR: CAN NOT FIND ALL FILES. EXITING NOW.\n";
		exit(-1);
	}

	struct minutia temp;
	std::vector<minutia> list;

	while (!original.eof()) //reads in each minutia in the original .xyt also finds largest and smallest values for x and y
	{
		original >> temp.x;
		original >> temp.y;
		original >> temp.theta;
		original >> temp.quality;
		list.push_back(temp);
		if (temp.x < minX)
			minX = temp.x;
		if (temp.y < minY)
			minY = temp.y;
		if (temp.x > maxX)
			maxX = temp.x;
		if (temp.y > maxY)
			maxY = temp.y;
	}

	original.close();

	//what about seeding a rand and using it here for the function? makes it more random at least.
	//srand(convertKey(key));
	std::mt19937_64 eng(convertKey(key));
	std::uniform_int_distribution<long long int> dist{LLONG_MIN, LLONG_MAX};

	for (int i = 0; i < list.size() - 1; i++) //this takes each minutia struct in the vector and applies the scrambling/unscrambling procedure.
	{// 
		//cout << "Minutua " << i+1 << " is:" << list.at(i) << "\n";
		if (key.at(circulator) % 2 == 1)
		{
			list.at(i).theta = convertTheta(list.at(i).theta, circulator, dist(eng), num1, key, mode, 45); //when editing x, tighter angle change
			if (list.at(i).x != minX && list.at(i).x != maxX) //change x unless x is edge
			{
				list.at(i).x = convertCoord(list.at(i).x, circulator, ((dist(eng) % ((maxX - 1) - (minX + 1) + 1)) + minX + 1), minY, maxX, minX, key, mode);
			}
			else //change y if it is not edge
			{
				if (list.at(i).y != minY && list.at(i).y != maxY)
				{
					list.at(i).y = convertCoord(list.at(i).y, circulator, ((dist(eng) % ((maxY - 1) - (minY + 1) + 1)) + minY + 1), minX, maxY, minY, key, mode);
				}
			}
		}
		else
		{
			list.at(i).theta = convertTheta(list.at(i).theta, circulator, dist(eng), num1, key, mode, 90);//changing gives a broader theta change

			if (list.at(i).y != minY && list.at(i).y != maxY) //same as with x coordinate, change y unless its edge, then change x if it isn't an edge
			{
				list.at(i).y = convertCoord(list.at(i).y, circulator, ((dist(eng) % ((maxY - 1) - (minY + 1) + 1)) + minY + 1), minX, maxY, minY, key, mode);
			}
			else
			{
				if (list.at(i).x != minX && list.at(i).x != maxX)
				{
					list.at(i).x = convertCoord(list.at(i).x, circulator, ((dist(eng) % ((maxX - 1) - (minX + 1) + 1)) + minX + 1), minY, maxX, minX, key, mode);
				}
			}

				/*int temp = list.at(i).y;// (list.at(i).x + midX) % (maxX); //do we need to flip?
				int addon = (int)(pow(-1, minX + key.at(circulator)))*((rand() % ((maxY - 1) - (minY + 1) + 1)) + minY + 1);//(int)((int)(pow(-1, minY + key.at(circulator)) * (1 / (maxY + 1)) * (key.size()) * midY) % (int)floor((double)(midX/2)));
				temp = temp + addon;
				if (temp < (minY + 1))
					temp = (maxY - 1) - ((minY + 1) - temp - 1);
				if (temp > maxY - 1)
					temp = (temp - (maxY - 1)) + minY;
				if (list.at(i).y != minX && list.at(i).y != maxY)
					list.at(i).y = temp % maxY;*/
		}
		circulator = (circulator + 1) % (key.size());
	}

	//sort(list.begin(), list.end());
	//since sorting would mess up order of rands recieved, perhaps encoding the original order into quality might work?
	//if qualities in order originally, sorting via x and y would jumble them up, to be unjumbled when going to decrypt.

	for (int i = 0; i < list.size() - 1; i++)
	{
		edited << list.at(i); //writes to the file
	}

	edited.close();
}
