#include <stdint.h>
#include <iostream>


uint8_t c2hex(char c) {
    if (c == 'f' || c == 'F')
        return 15;
    if (c == 'e' || c == 'E')
        return 14;
    if (c == 'd' || c == 'D')
        return 13;
    if (c == 'c' || c == 'C')
        return 12;
    if (c == 'b' || c == 'B')
        return 11;
    if (c == 'a' || c == 'A')
        return 10;
    if (c == '9')
        return 9;
    if (c == '8')
        return 8;
    if (c == '7')
        return 7;
    if (c == '6')
        return 6;
    if (c == '5')
        return 5;
    if (c == '4')
        return 4;
    if (c == '3')
        return 3;
    if (c == '2')
        return 2;
    if (c == '1')
        return 1;
    if (c == '0')
        return 0;

    // Otherwise just return -1
    return -1;
}



static const uint8_t data[48] = {
    0x00, 0x00, 0x00, 0x00, 0x66, 0x77, 0x11, 0xFF, 0x88, 0x8B, 0x00, 0x01,
    0x33, 0x3B, 0x07, 0x06, 0x0F, 0x03, 0x66, 0x66, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x66, 0x66, 0x11, 0x11, 0xBB, 0xB9, 0x11, 0x3D,
    0xBB, 0xBB, 0x66, 0x63, 0x33, 0x7B, 0x66, 0x66, 0x00, 0x00, 0x00, 0x00,
};
int main()
{

	// Reading the file the user wants to read
	std::cout << "Enter the .txt file containing hex code you wish to decode: ";
	char filename[255];
	std::cin >> filename;
	std::cout << filename << std::endl;
	FILE *fp = fopen(filename, "r");
	char rawHex[96];
	uint8_t finHex[48];

	if(fp == NULL) {
		std::cout << "Error: " << filename << " not found!" << std::endl;
		return -1;
	}

	for(int i=0; i<96; i++)
		rawHex[i] = fgetc(fp);
	
	std::cout << "The hex code to be decoded: ";
	for(int i=0; i<48; i++) {
		finHex[i] = c2hex(rawHex[2*i])*16+c2hex(rawHex[2*i+1]);
		std::printf("%02X ",finHex[i]);
	}

	std::cout << std::endl << std::endl << "After decoding..." << std::endl << std::endl;

	for(int y=0; y<8; ++y) {
	    int i = ((y/2)%2)+(y/4)*24;
	    for(int x=0; x<12; ++x,i+=2)
	    {
		const uint8_t nibble = (y%2) ? (finHex[i]&0xF) : (finHex[i]>>4);
		for(int b=4; b--;) std::cout << (((nibble>>b)&1) ? "*" : " ");
	    }
	    std::cout << std::endl;
	}
}
