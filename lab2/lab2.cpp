//
//  main.cpp
//  lab_2
//
//  Created by 邱煜 on 2019/3/14.
//  Copyright © 2019 邱煜. All rights reserved.
//

#include <iostream>
#include <string>

#define START_CMD 0
#define STOP_CMD 1
#define RES_CMD 2
#define STATUS_CMD 3
#define EXIT_CMD 4
#define INVALID_CMD -1

using namespace std;

const string cmds[] = {"start", "stop", "restart", "status", "exit"};
const int length = sizeof(cmds)/sizeof(cmds[0]);

int searchCmd(string cmd); // search and return the input command's index in array cmds. -1 if not found.
void cmdRecog(string cmd); // print the display messages.

int main(int argc, const char * argv[]) {
    string cmd;
    while(1){
        cout << "> ";
        cin >> cmd;
        int cmd_idx = searchCmd(cmd);
        switch (cmd_idx) {
            case START_CMD:
                cmdRecog("start");
                break;
            case STOP_CMD:
                cmdRecog("stop");
                break;
            case RES_CMD:
                cmdRecog("restart");
                break;
            case STATUS_CMD:
                cmdRecog("status");
                break;
            case EXIT_CMD:
                exit(0);
                break;
            default:
                cout << "Invalid command" << endl;
                break;
        }
    }
    return 0;
}

int searchCmd(string cmd){
    int idx = INVALID_CMD;
    for (int i = 0; i < length; i++) {
        if(cmd.compare(cmds[i])==0){
            idx = i;
            break;
        }
    }
    return idx;
}

void cmdRecog(string cmd){
    cout << "command " << cmd << " recognized." << endl;
}
