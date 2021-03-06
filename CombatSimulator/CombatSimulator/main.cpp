#include <iostream>   //Biblioteki.
#include <random>
#include <ctime>
#include <windows.h>

using namespace std;   //Standaryzowanie komend.

int number1();
int number2();
int customStatsFUN();
void mainLoop(int zombHit, int zombHealth, int survDamage, int total, int numZombies, int zombHealth2, int numSurivors, int numZombies2, int numSurvivors2,int survHit,int zombDamage,int survHealth,int survHealth2);

int main()             //G��wna funkcja.
{

	int numSurvivors, numZombies, survHealth, zombHealth = 50, survDamage = 25, zombDamage = 25;     //Zmienne.
	int numSurvivors2, numZombies2, zombHealth2, survHealth2, total;

	float survHit = 75, zombHit = 25;

	numSurvivors = number1();
	numZombies = number2();

	if (numSurvivors <= 0 || numZombies <= 0)
	{
		cout << "Please provide correct value.\n";

		system("PAUSE");
		return 0;
	}

	zombHealth, zombDamage, zombHit, survHit, survDamage, survHealth = customStatsFUN();

	survHealth2 = survHealth;
	zombHealth2 = zombHealth;

	cout << endl;

	numSurvivors2 = numSurvivors;                   //Liczba zombie i survivor�w przed bitw�.
	numZombies2 = numZombies;

	total = numSurvivors + numZombies;	//Liczba wszystkich uczestnik�w bitwy.

	system("cls");

	mainLoop(zombHit, zombHealth, survDamage, total, numZombies, zombHealth2, numSurvivors, numZombies2, numSurvivors2, survHit, zombDamage, survHealth, survHealth2);

	system("PAUSE");         //Zatrzymanie konsoli.
	return 0;                //Zwr�cenie poprawnej warto�ci do systemu.

}
int number1()
{
	int numSurvivors;

	cout << "** Combat Simulator v.2.0 **\n";

	cout << "Type how many survivors will take part in a combat\n";
	cin >> numSurvivors;

	return numSurvivors;
}
int number2()
{
	int numZombies;

	cout << "Type how many zombies will take part in a combat\n";
	cin >> numZombies;

	return numZombies;
}

int customStatsFUN()
{
	int zombHealth, zombDamage, zombHit, survHealth, survDamage, survHit;
	char customStats;

	cout << "Type 'y' if u want to change survivors and zombie stats, and 'n' if you would like to stick to original.\n";

	cin >> customStats;

	if (customStats == 'y')
	{
		cout << "Zombie health:\n";
		cin >> zombHealth;

		cout << "Zombie Damage:\n";
		cin >> zombDamage;

		cout << "Zombie attack chance:\n";
		cin >> zombHit;

		cout << "Survivor health:\n";
		cin >> survHealth;

		cout << "Survivor Damage:\n";
		cin >> survDamage;

		cout << "Survivor attack chance:\n";
		cin >> survHit;

	}
	else
	{
		zombHealth = 50;
		zombDamage = 25;
		zombHit = 25;
		survHealth = 100;
		survDamage = 25;
		survHit = 75;
	}

	return zombHealth, zombDamage, zombHit, survHealth, survDamage, survHit;
}

void mainLoop(int zombHit, int zombHealth, int survDamage, int total, int numZombies, int zombHealth2, int numSurvivors, int numZombies2, int numSurvivors2, int survHit, int zombDamage, int survHealth, int survHealth2)
{
	int x = 0;

	for (int i = 0; i <= total; x++)                  //G��wna p�tla programu.
	{
		static mt19937 generateEngine(time(NULL));    //Generowanie liczby.

		uniform_real_distribution<float> survChance(0, 100);    //Szansa na trafienie przez cz�owieka i zombiego  (od 0-100).
		uniform_real_distribution<float> zombChance(0, 100);

		if (survChance(generateEngine) > zombHit)                      //Je�li wylosuje co� powy�ej szans na atak cz�owieka, to zaatakuje on
		{															  //za ilo�� obra�e� cz�owieka.
			zombHealth = zombHealth - survDamage;


			if (zombHealth <= 0)                                       //Je�li zombie b�dzie mie� 0hp to znaczy, �e umar� i trzeba wstawi� nowego na jego miejsce
			{														  //oraz da� mu pocz�tkow� ilo�� zdrowia.
				numZombies--;
				zombHealth = zombHealth2;

				i++;
			}

		}

		if (numZombies == 0)                                        //Je�li �aden zombie nie pozosta� przy �yciu to zako�cz walk�.
		{
			cout << "Humans won!\n";
			cout << "There are " << numSurvivors << " humans left.\n";
			cout << numZombies2 << " zombies and " << numSurvivors2 - numSurvivors << " survivors lost their lives." << endl << endl;
			cout << "Battle ended in " << x << " turns\n";

			break;           //Przerwanie p�tli.
		}

		if (zombChance(generateEngine) > survHit)					  //Je�li wylosuje co� powy�ej szans na atak zombiego zaatakuje on
		{															  //za ilo�� obra�e� zombie.

			survHealth = survHealth - zombDamage;

			if (survHealth <= 0)										  //Je�li cz�owiek b�dzie mie� 0hp to znaczy, �e umar� i trzeba wstawi� nowego na jego miejsce
			{														  //oraz da� mu pocz�tkow� ilo�� zdrowia.
				numSurvivors--;
				survHealth = survHealth2;

				i++;
			}

		}

		if (numSurvivors == 0)                                      //Je�li �aden cz�owiek nie pozosta� przy �yciu to zako�cz walk�.
		{
			cout << "Zombies won!\n";
			cout << "There are " << numZombies << " zombies left.\n";
			cout << numSurvivors2 << " survivors and " << numZombies2 - numZombies << " zombies lost their lives.\n";
			cout << "Battle ended in " << x << " turns\n";

			break;            //Przerwanie p�tli.
		}

	}
}