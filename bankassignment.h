//
// Created by User on 23/11/2022.
//

#ifndef MY_PROJECT_BANKASSIGNMENT_H
#define MY_PROJECT_BANKASSIGNMENT_H

#endif //MY_PROJECT_BANKASSIGNMENT_H

#include"iostream"
using namespace std;

namespace M{
    class bank{
    public:
        // attribute and behaviour
        int i = 0;
        int receiver = 0;
        int current = 0;
        int currentAmount = 0;
        int withdrawAmount = 0;
        string arr_username[100];
        string arr_password[100];
        int arr_amount[100];
        string arr_phNumber[100];
        string arr_address[100];
        string r_username;
        string r_password;
        int r_amount = 0;
        string r_phNumber;
        string r_address;
        string l_username;
        string l_password;
        string confirmPassword;
        string admin[3] = {"admin1@gmail.com","admin2@gmail.com","admin3@gmail.com"};
        string adminpw[3] = {"admin","admin","admin"};
        //
        int usernameIndex = 0;
        int passwordIndex = 0;
        int amountIndex = 0;
        int phNumberIndex = 0;
        int addressIndex = 0;
        // method
        void mainLoading();
        void showAlldata();
        void reGister();
        void login();
        void mainMenu();
        int usernameExit(string username);
        void exchange();
        void recording();
        int adminForchecking(string adname,string adpw);
        int adminCheckusername(string username);
        void adminOption();
        void specificFun();
        void manageFun();
        void transfer();
        void toTransferFun(int current,int receiver,int transferAmount);
        void withdraw();
        void showAllInfo();
        void withdrawFun(int current,int withdrawAmount);
        void changeuserNameFun();
        void changeuserPassword();
        void update();
        void updateOptionFun(string updateOption,int updateAmount);

    };
}
