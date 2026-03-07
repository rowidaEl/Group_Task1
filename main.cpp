#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
using namespace std;

// ========================
//       USER CLASS
// ========================
class User
{
private:
    string username;
    string password;
    string phoneNumber;
    string status;
    string lastSeen;

public:
    User()
    {
        // TODO: Implement default constructor
        username = "";
        password = "";
        phoneNumber = "";
        status = "";
        lastSeen = "";
    }


    User(string uname, string pwd, string phone) {

        // TODO: Implement parameterized constructor
        username=uname;
        password=pwd;
        phoneNumber=phone;
    }


    string getUsername() const {

        // TODO: Implement getter
        return username;
    }

    string getPhoneNumber() const {
        // TODO: Implement getter
        return phoneNumber;
    }

    string getStatus() const {
        // TODO: Implement getter
        return status;
    }

    string getLastSeen() const {
        // TODO: Implement getter
        return lastSeen;
    }

    void setStatus(string newStatus) {
        // TODO: Implement setter
        status=newStatus;
    }

    void setPhoneNumber(string phone) {
        // TODO: Implement setter
        phoneNumber=phone;
    }

    void updateLastSeen() {
        // TODO: Implement last seen update
        time_t now = time(0);          // get current time , seconds since jan 1970
        tm* localTime = localtime(&now); //converts to readable format

        stringstream ss;
        ss << put_time(localTime, "%Y-%m-%d %H:%M:%S"); //format as string

        lastSeen = ss.str();
    }

    bool checkPassword(string pwd) const {
        // TODO: Implement password check
        return password==pwd;
    }

    void changePassword(string newPwd) {
        // TODO: Implement password change
        password=newPwd
    }
};

// ========================
//      MESSAGE CLASS
// ========================
class Message
{
private:
    string sender;
    string content;
    string timestamp;
    string status;
    Message* replyTo;

public:
    Message()
    {
        // TODO: Implement default constructor
        sender="";
        content="";
        timestamp="";
        status="";
        replyTo=nullptr;

    }

    Message(string sndr, string cntnt) {
        // TODO: Implement parameterized constructor
        sender=sndr;
        content=cntnt;
        timestamp="";
        status="sent";
        replyTo=nullptr;
    }

    string getContent() const {
        // TODO: Implement getter
        return content;
    }

    string getSender() const {
        // TODO: Implement getter
        return sender;
    }

    string getTimestamp() const {
        // TODO: Implement getter
        return timestamp;
    }

    string getStatus() const {
        // TODO: Implement getter
        return status;
    }

    Message* getReplyTo() const {
        // TODO: Implement getter
        return replyTo;
    }

    void setStatus(string newStatus) {
        // TODO: Implement setter
        status=newStatus;
    }

    void setReplyTo(Message* msg) {
        // TODO: Implement setter
        replyTo=msg;
    }

    void updateTimestamp() {
        // TODO: Implement timestamp update
        time_t now = time(0);          // get current time , seconds since jan 1970
        tm* localTime = localtime(&now); //converts to readable format

        stringstream ss;
        ss << put_time(localTime, "%Y-%m-%d %H:%M:%S"); //format as string

        timestamp = ss.str();
    }

    void display() const {
        // TODO: Implement message display
        cout << "[" << timestamp << "] ";
        cout << sender << ": ";
        cout << content << endl;

        if(replyTo != nullptr)
        {
            cout << "(Reply to: " << replyTo->getContent() << ")" << endl;
        }
    }

    void addEmoji(string emojiCode) {
        // TODO: Implement emoji support
        content += " " + emojiCode;
    }
};

// ========================
//       CHAT CLASS (BASE)
// ========================
class Chat
{
protected:
    vector<string> participants;
    vector<Message> messages;
    string chatName;

public:
    Chat()
    {
        // TODO: Implement default constructor
        chatName = " ";
    }

    Chat(vector<string> users, string name) {
        // TODO: Implement parameterized constructor
        participants = users;
        chatName = name;
    }

    vector<string> getParticipants(){
        return participants;
    }

    void addMessage(const Message& msg) {
        // TODO: Implement message addition
        messages.push_back(msg);
    }

    bool deleteMessage(int index, const string& username) {
        // TODO: Implement message deletion
        if(index >= 0 && index < messages.size())
        {
            if(messages[index].getSender() == username)
            {
                messages.erase(messages.begin() + index);
                return true;
            }
        }
        return false;
    }

    virtual void displayChat() const {
        // TODO: Implement chat display
        cout << "Chat: " << chatName << endl;
        for(const Message& m : messages)
        {
            m.display();
        }
    }

    vector<Message> searchMessages(string keyword) const {
        // TODO: Implement message search
        vector<Message> res;
        for(const Message& m : messages)
        {
            if(m.getContent().find(keyword) != string::npos)
            {
                res.push_back(m);
            }
        }

        return res;
    }

    void exportToFile(const string& filename) const {
        // TODO: Implement export to file
        ofstream file(filename);
        if(!file)
        {
            cout << "Error cannot open file " << endl;
            return ;
        }
        file << "Chat: " << chatName << endl;
        file << "Partiicipants:" << endl;
        for(const string& p : participants)
        {
            file << p << endl;

        }
        file << "\nMessages:" << endl;
        for(const Message& m : messages)
        {
            file << "[" << m.getTimestamp() << "]" << m.getSender() << ": " << m.getContent() << endl;

        }
        file.close();
    }
};

// ========================
//     PRIVATE CHAT CLASS
// ========================
class PrivateChat : public Chat
{
private:
    string user1;
    string user2;

public:
    PrivateChat(string u1, string u2)
    {
        // TODO: Implement constructor
        user1 =u1;
        user2 = u2;
        participants ={u1,u2};
        chatName = "Chat between " + u1 + " and " + u2;

    }

    void displayChat() const override {
        // TODO: Implement private chat display
        cout << "Private " << chatName << endl;
        for(const Message& m : messages)
        {
            m.display();
        }

    }

    void showTypingIndicator(const string& username) const {
        // TODO: Implement typing indicator
        cout << username << " is typing..." << endl;
    }
};

// ========================
//      GROUP CHAT CLASS
// ========================
class GroupChat : public Chat
{
private:
    vector<string> admins;
    string description;

public:
    GroupChat(vector<string> users, string name, string creator)
    {
        // TODO: Implement constructor
    }

    void addAdmin(string newAdmin) {
        // TODO: Implement add admin
    }

    bool removeParticipant(const string& admin, const string& userToRemove) {
        // TODO: Implement remove participant
        return false;
    }

    bool isAdmin(string username) const {
        // TODO: Implement admin check
        return false;
    }

    bool isParticipant(string username) const {
        // TODO: Implement participant check
        return false;
    }

    void setDescription(string desc) {
        // TODO: Implement set description
    }

    void displayChat() const override {
        // TODO: Implement group chat display
    }

    void sendJoinRequest(const string& username) {
        // TODO: Implement join request
    }
};

// ========================
//    WHATSAPP APP CLASS
// ========================
class WhatsApp
{
private:
    vector<User> users;
    vector<Chat*> chats;
    int currentUserIndex;

    int findUserIndex(string username) const {
        for(int i=0;i<users.size();i++){
            if(username==users[i].getUsername()){
                return i;
            }
        }
        return -1;
    }

    bool isLoggedIn() const {
        if(currentUserIndex!=-1){
            return true;
        }
        return false;
    }

    string getCurrentUsername() const {
        return users[currentUserIndex].getUsername();
    }

public:
    WhatsApp() : currentUserIndex(-1) {}

    void signUp() {
        string name, password, phoneNumber;
        bool Valid = false;
        cout<<"Enter Username:\n";
        while(!Valid){    
            cin>>name;
            if(!name.size()){
                cout<<"Username can't be empty\n";
                cout << "Enter another username:\n";
                continue;
            }
            if(findUserIndex(name)!=-1){
                cout<<"This Username already exists\n";
                cout << "Enter another username:\n";
            }
            else{
                Valid = true;
            }
        }
        Valid = false;
        while(!Valid){
            cout<<"Enter Password:\n";
            cin>>password;
            if(!password.size()){
                cout<<"Password can't be empty\n";
                continue;
            } 
            Valid = true;
        }
        Valid = false;
        while(!Valid){
            cout<<"Enter Phone number:\n";
            cin>>phoneNumber;
            if(!phoneNumber.size()){
                cout<<"Phone Number can't be empty\n";
                continue;
            } 
            Valid = true;
        }
        users.push_back(User(name,password,phoneNumber));
        currentUserIndex = users.size()-1;
        cout<<"Account created Successfully\n";
    }

    void login() {
        string userName,password;
        int index;
        bool Valid = false;
        cout<<"Enter Username\n";
        while (!Valid)
        {

            cin>>userName;
            index=findUserIndex(userName);
            if(index!=-1){
                Valid = true;
            }
            else{
                cout<<"This Username doesn't exist\n";
                cout<<"Enter another Username\n";
            }
        }
        Valid = false;
        cout<<"Enter Your Password\n";
        while(!Valid){
            cin>>password;
            if(users[index].checkPassword(password)){
                Valid=true;
            }
            else{
                cout<<"Incorrect Password\n";
                cout<<"Enter another Password\n";
            }
        }
        currentUserIndex = index;
        cout<<"Logged in Successfully\n";
    }

    void startPrivateChat() {
        cout << "Enter username to start chat with: \n";
        bool Valid =false;
        string currentUserName = getCurrentUsername(),userName;
        while(!Valid){
            cin>>userName;
            if(userName==currentUserName){
                cout<<"You can't start a private chat with yourself\n";
                cout << "Enter another username:\n";
            }
            else if(findUserIndex(userName)==-1){
                cout<<"This user doesn't exist\n";
                cout << "Enter another username:\n";
            }
            else{
                Valid = true;
            }
        }
        Chat* privateChat = new  PrivateChat(currentUserName,userName);
        chats.push_back(privateChat);
    }

    void createGroup() {
        string userName, groupName;
        string creator = getCurrentUsername();

        vector<string> users = {creator};

        cout << "Enter Group name\n";

        while (true) {
            cin >> groupName;

            if (groupName.empty()) {
                cout << "Group name can't be empty\n";
            } else {
                break;
            }
        }

        int choice;

        while (true) {
            cout << "1. Add Group member\n2. Create Group\n";
            cin >> choice;
            if (choice == 2) {
                break;
            }
            if (choice == 1) {
                cout << "Enter Group member name\n";
                while (true) {
                    cin >> userName;
                    for(auto &user:users){
                        if (userName == user) {
                            cout << "This user is already added\nEnter another name\n";
                            break;
                        }
                    }
                    if (findUserIndex(userName) == -1) {
                        cout << "This user doesn't exist\nEnter another name\n";
                    }
                    else {
                        users.push_back(userName);
                        break;
                    }
                }
            }
            else {
                cout << "Invalid choice\n";
            }
        }
        Chat* groupChat = new GroupChat(users, groupName, creator);
        chats.push_back(groupChat);
        cout << "Group created successfully\n";
    }

    void viewChats() {
        string currentUser = getCurrentUsername();
        vector<Chat*> myChats;

        cout << "\nYour Chats:\n";

        for(auto & chat:chats){
            for(auto& user:chat->getParticipants()){
                if(user==currentUser){
                    myChats.push_back(chat);
                    break;
                }
            }
        }

        if (myChats.empty()) {
            cout << "No chats found\n";
            return;
        }
        for( auto & chat:myChats){
            chat->displayChat();
        }
    }

    void logout() {
        currentUserIndex = -1;
        return;
    }

    void run() {
        while (true) {
            if (!isLoggedIn()) {
                cout << "\n1. Login\n2. Sign Up\n3. Exit\nChoice: ";
                int choice;
                cin >> choice;

                if (choice == 1) login();
                else if (choice == 2) signUp();
                else if (choice == 3) break;
            }
            else
            {
                cout << "\n1. Start Private Chat\n2. Create Group\n3. View Chats\n4. Logout\nChoice: ";
                int choice;
                cin >> choice;

                if (choice == 1) startPrivateChat();
                else if (choice == 2) createGroup();
                else if (choice == 3) viewChats();
                else if (choice == 4) logout();
            }
        }
    }
};

// ========================
//          MAIN
// ========================
int main()
{
    WhatsApp whatsapp;
    whatsapp.run();
    return 0;
}
