#include<iostream>
#include <windows.h>
#include<stdio.h>
void Log(const char* message); //declaration 

struct projectile
{
	char unsigned IsThisOnFire;
	int Damage;
	int ParticlesPerSecond;
	short HowManyCooks;

	//1 byte + 4 byte + 4 byte + 2 bytes = 11 bytes
	//however in memory it is not necessarily to locate 11 bytes, could be more, for cpu efficiency or something  
	//it could be cpu is much slower for accessing 8 bit value vs 32 bit value
};

void HexaDecimalTest()
{
	int x = 5;
	int y = 10;
	int z = 12;

	x = 0xA; //10
	//shift bits
	//each shift is 2^number
	//here is 2^4
	//either value * 2^4 or value/2^4
	x = x << 1; // 10 * 2 =20; set first bit
	x = x << 1; // 20 * 2 = 40
	x = x << 1; // 40 * 2 = 80
	x = x << 1; // 80 * 2 = 160
	x = x >> 4; // 160 / 2^4 = 10; set 4th bit

	//-------------test other operators
	x = 0;
	x = x | (1 << 4); // or, combines all set bits => 0x00000010
	//   0x00000000  => x
	//|  0x00000010  => (1<<4)
	//   0x00000010

	//any bits that set in either of two, set all of them
	x = x | (1 << 8); //0x00000010 => 0x00000110, keep preset bits x and set next bits as well
	//   0x00000010  => x
	//|  0x00000100  => (1<<8)
	//   0x00000110

	x = x & (1 << 4); //only leave comment set bits
	//    0x00000110  => x
	//&   0x00000010  => (1 << 4)
	// 	  0x00000010 

	x = 0;
	x = x | (1 << 4);
	x = x | (1 << 3);
	x = x | (1 << 14);
	x = x | (1 << 30);

	y = ((1 << 4) | (1 << 31));
	x = x & y; //0x00000010, coz only 4th bit got set in both x and y

	x = (1 << 4) | (1 << 8) | (1 << 16) | (1 << 20);
	x = ~x; // invert, 1=>0; 0=>1

	x = (1 << 4) | (1 << 8);
	y = (1 << 8) | (1 << 16);
	x = x ^ y; //exclusive or => either of bits are set, it will set; but both of bits are set, it wont be
	x = x ^ y; // invert it again, get original value back
	//x = x ^ (1 << 8);

}

void pointer()
{
	int* ptr = 0;
	int y = 5;
	int x = 10;

	ptr = &x;

	*ptr = 6; //*ptr refers to what's in that location, x=6
	y = *ptr; //6


	//------pointer pointer
	int** ptrptr = 0;
	int w = 9;
	ptr = &w;
	ptrptr = &ptr; //pointing to the pointer that pointing to w
	int z = **ptrptr; //9
	//dereference operator chases pointer
	//go to where this pointer points, the thing you are pointing to is a pointer, then go find where that is pointing to

	//ptr->, -> means dereference pointer first then do the . thing

}

int main()
{
	/*
	Log("hello world");
	char unsigned Test;
	char unsigned* TestPointer;
	TestPointer = &Test;

	Test = 125;
	Test = Test + 1;

	printf("this is printf");
	OutputDebugStringA("this is from 2014");
	std::cin.get();

	*/

	unsigned short Test;
	Test = 500;
	Test = Test + 1;

	/*
	* read vertically hex decimal table
		   52 1
		   15 2631
		   26 8426 8421
	0000 0001 1111 0100

			  1111 0100 is one byte = 244; this is lower byte
	0000 0001 = 1; this is higher byte

	endianess
	little endian: lower byte comes first stored in memory
	big endian: higher byte comes first stored in memory
	*/

	projectile testStruct;
	int size = sizeof(testStruct);
	// this is not necessarily the size of each variable in projectile sums up.
	//sum of variables in projectile is 11 bytes. 
	//here it automatically located 16 bytes

	testStruct.IsThisOnFire = 1;
	testStruct.Damage = 2 + testStruct.IsThisOnFire;
	testStruct.ParticlesPerSecond = 3;
	testStruct.HowManyCooks = 4;
	//can also ask in watch window each individual part of the structure is: &testStruct.OarticlesPerSecond. 

	//cast
	projectile* projectilePointerTest = &testStruct;
	unsigned short* AnotherPointer = (unsigned short*)&testStruct;

	//in watch window you can do: AnotherPointer,8 => This gives 8 different values, 
	//projectile is 16 bytes, 2 bytes for each value, short is 2 bytes

	projectile Projectiles[40];
	int whichProjectile = 4;
	Projectiles[whichProjectile];
	// layout 40 of them can avoid doing 
	//Projectile1 = ..; 
	//Projectile2 = ..; 
	//Projectile3 = ..; 
	//if (WhichProjectile ==1) do something with projectile1
	//else do something with projectile 2
	projectile* projectilePointer = Projectiles; // get pointer of first one 

	int SizeOfProjectiles = sizeof(Projectiles); //16*4
	int SizeOfProjectilePoiner = sizeof(projectilePointer); //4 

	Projectiles[30].Damage = 60;
	//projectilePointer + 30 is 30th projectile, it does the size multiplication for you automatically
	(projectilePointer + 30)->Damage = 100;

	//to do entire thing manually: need to cast pointer to only point to 8 bit char, 
	((projectile*)((char*)projectilePointer + 30 * sizeof(projectile)))->Damage = 200;
	char* BytePointer = (char*)projectilePointer;
	BytePointer = BytePointer + 30 * sizeof(projectile);

	//this is wrong, since BytePointer is just one byte, there is no Damage
	//BytePointer->Damage =200
	projectile* Thirty = (projectile*)BytePointer;
	Thirty->Damage = 200;


	//for pointer, if you want to access content, you need to use ->
	// -> is same as .
	projectile* test1;
	test1 = &testStruct;
	int Damage1 = test1->Damage;

	projectile test2;
	test2.Damage = 32;
	int Damage2 = test2.Damage;


	// test some hexadecimal operations
	HexaDecimalTest();

	//pointer
	pointer();
}

#pragma region How to read HexDecimal
/*

	0 - 0
	1 - 1
	2 - 2
	3 - 3
	4 - 4
	5 - 5
	6 - 6
	7 - 7
	8 - 8
	9 - 9
   10 - A
   11 - B
   12 - C
   13 - D
   14 - E
   15 - F

   0X => prefix for hexadecimal

   0XA = 10
   0XAA = 16 * 10 + 10 = 170
   0XAAA = 16 * 16 * 10 + 16 * 10 + 10

   It is like decimal 444 = 4* 10 * 10 + 4 * 10 + 4


*/

#pragma endregion
