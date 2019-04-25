//
//  main.hpp
//  lab4
//
//  Created by 邱煜 on 2019/4/12.
//  Copyright © 2019 邱煜. All rights reserved.
//

#ifndef main_hpp
#define main_hpp

struct Blocks {
    int id;
    int startCode;
    int endCode;
    std::string codeName;
};


// return the id of the block of the corresponding codepoint
// return -1 if not found
int findId(int codepoint);

// trim the spaces in the starting and ending of the str
void trim(std::string &str);

// set the value of the key +1
// if this key not exist, add this key add set its value to 1
void addOccurence(int key);

// find the code block index which has the maximum occurence
int findMaxId(void);

// utf8_to_codepoint returns 0 if conversion fails. If it succeeds,
// the value pointed by lenptr is set to the number of bytes of the
// UTF-8 character
unsigned int utf8_to_codepoint(const unsigned char *u, int *lenptr);

// Returns the length in bytes, 0 if invalid
int isutf8(const unsigned char *u);
#endif /* main_hpp */
