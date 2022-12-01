//
// Created by User on 23/11/2022.
//

#include"iostream"
#include"bankassignment.h"
#include"fstream"
#include"string"
using namespace std;
using namespace M;

void bank::mainMenu(){
    string press;
    cout << "Press 1 to register: " << endl;
    cout << "Press 2 to login: " << endl;
    cout << "Press 3 to exit: " << endl;
    cin >> press;

    if (press == "1"){
        reGister();
    }else if (press == "2"){
        login();
    }else if (press == "3"){
        recording();
        exit(0);
    }else{
        mainMenu();
    }
}

int bank::usernameExit(string username){
    for (i = 0;i < usernameIndex;i++){
        if (arr_username[i] == username){
            return i;
        }
    }
    return 1111;
}

void bank::showAllInfo() {
    for (i = 0;i < usernameIndex;i++){
        cout << "Username: " << arr_username[i]  << " Password: " << arr_password[i] << " Amount: " << arr_amount[i] << endl;
    }
}

void bank::reGister(){
    cout << "Please enter your name: ";
    cin >> r_username;
    int result = usernameExit(r_username);
    while (result == 1111) {
        cout << r_username << " is valid " << endl;
        cout << "Please enter your password: ";
        cin >> r_password;
        cout << "Please enter your confirm password: ";
        cin >> confirmPassword;
        while (true) {
            if (r_password == confirmPassword) {
                cout << "Please enter your amount: ";
                cin >> r_amount;
                cout << "Please enter your phone number: ";
                cin >> r_phNumber;
                cout << "Please enter your address: ";
                cin >> r_address;
                arr_username[usernameIndex] = r_username;
                arr_password[passwordIndex] = r_password;
                arr_amount[amountIndex] = r_amount;
                arr_phNumber[phNumberIndex] = r_phNumber;
                arr_address[addressIndex] = r_address;
                usernameIndex++;
                passwordIndex++;
                amountIndex++;
                phNumberIndex++;
                addressIndex++;
                cout << "Registration success " << endl;
                mainMenu();
            } else {
                cout << "Your password is not match! Try Again! " << endl;
                break;
            }
        }
    }
    cout << "Username is already exist: " <<endl;
    reGister();

}

void bank::login() {
    string adminpass;
    cout << "Please enter your name: ";
    cin >> l_username;
        int answer = adminCheckusername(l_username);
        if (answer >= 0){
            cout << "Please enter password for admin: ";
            cin >> adminpass;
            int status = adminForchecking(l_username, adminpass);

            if (status == -1) {
                login();
            }
        } else {
            int result = usernameExit(l_username);
            if (result != 1111) {
                cout << l_username << " is valid / Enter your password: ";
                cin >> l_password;
                if (l_username == arr_username[result] && l_password == arr_password[result]) {
                    current = i;
                    currentAmount = arr_amount[i];
                    cout << "Login success " << endl;
                    cout << "Welcome " << l_username << endl;
                    exchange();
                } else {
                    cout << "Your password is not match " << endl;
                    login();
                }
            } else {
                cout << "Your name is invalid " << endl;
                login();
            }
        }


}

void bank::exchange() {
    string exOption;
    cout << "Press 1 to transfer money\nPress 2 to withdraw money\n Press 3 to update money\nPress 4 to exit " << endl;
    cin >> exOption;
    if (exOption == "1"){
        transfer();
        exchange();
    }else if (exOption == "2") {
        withdraw();
        exchange();
    }else if (exOption == "3"){
        update();
        exchange();
    }else if (exOption == "4"){
       mainMenu();
    }else{
        exchange();
    }
}

void bank::transfer(){
    string toTransferName;
    int transferAmount = 0;
    cout << "Please enter your transfer name: ";
    cin >> toTransferName;
     receiver = usernameExit(toTransferName);
    if ( receiver >= 0 ) {
        while (receiver >= 0) {
            cout << "Please enter your transfer amount: ";
            cin >> transferAmount;
            if (transferAmount >= currentAmount) {
                cout << "Invalid amount " << endl;
                continue;
            }else{
                toTransferFun(current,receiver,transferAmount);
                showAllInfo();
                recording();
                exchange();
            }
        }
    }else{
        cout << "username doesn't have in our bank account!" << endl;
        transfer();
    }
}

void bank::toTransferFun(int current, int receiver, int transferAmount) {
    if (arr_amount[current]-100 > 0) {
        arr_amount[current] = arr_amount[current] - transferAmount;
        arr_amount[receiver] = arr_amount[receiver] + transferAmount;
        cout << "Money successfully transferred to " << arr_username[receiver] << endl;
        cout << "Transferred Amount is " << transferAmount << endl;
    }else{
        cout << "Your amount is lower than 0 Ks" << endl;
        cout << "You have only " << arr_amount[current] << " kyats" << endl;
        exit(0);
    }

    string filename = arr_username[current] + ".txt";
    ofstream specfile;
    ofstream allfile;
    specfile.open(filename,ios::app);
    allfile.open("transationrecord.txt",ios::app);

    if (!specfile.is_open()){
        cout << "Unable to open file ! " << endl;
    }
    if (!allfile.is_open()){
        cout << "Unable to open file ! " << endl;
    }

    string recordFile = "From " + arr_username[current] + " To " + arr_username[receiver] + " Transferred " + to_string(transferAmount) + "\n";
    specfile << recordFile;
    allfile << recordFile;
    specfile.close();
    allfile.close();

}

void bank::withdraw(){
    cout << "Please enter your withdraw amount: ";
    cin >> withdrawAmount;

    if (arr_amount[current]-100 > withdrawAmount){
        withdrawFun(current,withdrawAmount);
    }else{
        cout << "Invalid amount !" << withdrawAmount << endl;
        withdraw();
    }
}

void bank::withdrawFun(int current,int withdrawAmount){
    arr_amount[current] = arr_amount[current]-withdrawAmount;
    cout << "Username:" << arr_username[current] << endl << " Amount: " << arr_amount[current] << endl;
    recording();
    showAllInfo();
}

void bank::update(){
    int updateAmount = 0;
    string updateOption;
    cout << "Press 1 to add money " << endl;
    cout << "Press 2 to sub money " << endl;
    cin >> updateOption;
      cout << "Please enter your update amount: " << endl;
      cin >> updateAmount;
    if (updateOption == "1"){
      updateOptionFun(updateOption,updateAmount);
      showAllInfo();
      recording();
      exchange();
    }else if (updateOption == "2"){
        updateOptionFun(updateOption,updateAmount);
        showAllInfo();
        recording();
        exchange();
    }else if (updateOption == "3"){
        exchange();
    }else{
        update();
    }
}

void bank::updateOptionFun(string updateOption,int updateAmount) {
    if (updateOption == "1"){
        arr_amount[current] = arr_amount[current] + updateAmount;
    }else if (updateOption == "2") {
        if (arr_amount[current]-100 > updateAmount) {
            arr_amount[current] = arr_amount[current] - updateAmount;
        }else{
            cout << "Invalid amount! " << endl;
            update();
        }
    }
}


void bank::adminOption() {
    string option;
    cout << "Hello Admin " << endl;
    cout << "Press 1 to know all info of the user: " << endl;
    cout << "Press 2 to know specific info: " << endl;
    cout << "Press 3 to manage user account: " << endl;
    cout << "Press 4 to exit: " << endl;
    cin >> option;
    if (option == "1"){
        cout << "All info of user " << endl;
        showAlldata();
        adminOption();
    }else if (option == "2"){
        cout << "This is specific info " << endl;
        specificFun();
        adminOption();
    }else if (option == "3"){
        cout << "This is manage account " << endl;
        manageFun();
    }else if (option == "4"){
        exit(0);
    }else{
        cout << "Invalid option " << endl;
        adminOption();
    }

}

void bank::specificFun() {
    string data;
    string specUsername;
    cout << "Please enter you want to know username: ";
    cin >> specUsername;
    string fileData("allbankdata.txt");
    string dataLine;
    ifstream dataFile(fileData);
    if (dataFile.is_open()) {
        while (getline(dataFile, dataLine)) {
            dataLine = dataLine + " ";
            for (auto &ch: dataLine) {
                if (ch == ' ') {
                    if (data == specUsername) {
                        cout << "Data: " << dataLine << endl;
                        data = "";
                    } else {
                        data = "";
                    }

                } else {
                    string st(1, ch);
                    data = data + st;
                }
            }
        }
    }
    dataFile.close();
}

void bank::manageFun() {
    string manageOption;
    cout << "Press 1 to change username: " << endl;
    cout << "Press 2 to change password: " << endl;
    cout << "Press 3 to exit: " << endl;
    cin >> manageOption;
    if (manageOption == "1"){
        changeuserNameFun();
    }else if (manageOption == "2") {
        changeuserPassword();
    }else if (manageOption == "3"){
        adminOption();
    }else{
        manageFun();
    }
}

void bank::changeuserNameFun() { // all username can change // that error
    string newUsername;
    string changingName;
    showAlldata();
    cout << "Please enter admin want to change " << endl;
    cin >> changingName;
    int check = usernameExit(changingName);
    if (check >= 0){
        cout << "Please enter  new username: ";
        cin >> newUsername;
        int status = usernameExit(newUsername);
        if (status == 1111) { // not include username in DB
            cout << "Updating new username: " << endl;
            for (i = 0;i < usernameIndex;i++) {
                if (changingName == arr_username[i]) {
                    arr_username[i] = newUsername;
                    if (arr_username[i] == newUsername) {
                        cout << "Changing process is success" << endl;
                        cout << "This is  new username: " << newUsername << endl;
                        showAllInfo();
                        recording();
                        manageFun();
                        mainMenu();
                    } else {
                        cout << "Invalid username! " << endl;
                        changeuserNameFun();
                    }
                }
            }
        } else {
            cout << "New user Name is already exit " << endl;
            manageFun();
        }
    }

}


void bank::changeuserPassword() {
    string changingName;
    string currentPassword;
    string newPassword;
    showAlldata();
    cout << "Please enter name admin want to change password: " << endl;
    cin >> changingName;
    int status = usernameExit(changingName);
    if (status >= 0){
            cout << "Please enter  current password: " << endl;
            cin >> currentPassword;
                if (currentPassword == arr_password[status]) {
                    cout << "Please enter  new password: " << endl;
                    cin >> newPassword;
                    if (newPassword == currentPassword) {
                        cout << "Same password !" << endl;
                        changeuserPassword();
                    } else {
                        if (currentPassword == arr_password[status]) {
                            arr_password[status] = newPassword;
                            cout << "Password changing process is success!" << endl;
                            cout << "This is " << arr_username[status] << " 's new password: " << newPassword << endl;
                            showAllInfo();
                            recording();
                            manageFun();
                        }
                    }
                } else {
                    cout << "Password is not exit " << endl;
                    manageFun();
                }

        }else{
           cout << "Username doesn't exit in DB!" << endl;
           manageFun();
        }


}

int bank::adminForchecking(string adname,string adpw) {
    for (i = 0;i < 3;i++) {
        if (admin[i] == adname && adminpw[i] == adpw) {
           adminOption();
        }
    }
    return -1;
}

int bank::adminCheckusername(string username) {
    for (i = 0;i < 3;i++){
        if (username == admin[i]){
            return i;
        }
    }
    return -1;
}

void bank::showAlldata(){
    for ( i = 0;i < usernameIndex;i++){
        current = i;
        cout << arr_username[i] << " " << arr_password[i] << " " << arr_amount[i] << " " << arr_phNumber[i] << " "<< arr_address[i] << endl;
    }
}

void bank::recording() {
    string filedataName = "allbankdata.txt";
    ofstream recordfileName(filedataName);

    if (!recordfileName.is_open()){
        cout << "Unable to record: ";
    }else{
        for (i = 0;i < usernameIndex;i++){
            string data = arr_username[i] + " " + arr_password[i] + " " + to_string(arr_amount[i]) + " " + arr_phNumber[i] + " "+ arr_address[i] + "\n";
            recordfileName<< data;
        }
    }
    recordfileName.close();
}

void bank::mainLoading(){
    int count = 0;
    string data;
    cout << "Main Loading is running....\n.\n.\n";
    string fileData("allbankdata.txt");
    string dataLine;
    ifstream dataFile(fileData);
    if (dataFile.is_open()){
        while(getline(dataFile,dataLine)){
            dataLine = dataLine + " ";
            for (auto &ch: dataLine){
                if (ch == ' '){
                    if (count == 0){
                        arr_username[usernameIndex] = data;
                        usernameIndex++;
                        cout << "We found one space " << endl;
                        data = "";
                        count++;
                    }else if (count == 1){
                        arr_password[passwordIndex] = data;
                        passwordIndex++;
                        cout << "We found two space " << endl;
                        data = "";
                        count++;

                    }else if (count == 2){
                        arr_amount[amountIndex] = stoi(data);
                        amountIndex++;
                        cout << "We found three space " << endl;
                        data = "";
                        count++;
                    }else if (count == 3){
                        arr_phNumber[phNumberIndex] = data;
                        phNumberIndex++;
                        cout << "We found four space " << endl;
                        data = "";
                        count++;
                    }else if(count == 4){
                        arr_address[addressIndex] = data;
                        addressIndex++;
                        cout << "We found five space " << endl;
                        data = "";
                        count = 0;
                    }
                }else{
                    string st(1,ch);
                    data = data + st;
                }
            }
        }
    }else{
        cout << "File can't opening !";
    }
    showAlldata();
    dataFile.close();
}
