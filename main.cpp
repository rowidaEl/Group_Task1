#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>  
#include <iomanip>  
#include <algorithm>
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
        password=newPwd;
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
        status="sent";
        replyTo=nullptr;
        updateTimestamp();
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

    void display()  {
        // TODO: Implement message display
        updateTimestamp();
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
    vector<Message>& getMessages() {
        return messages;
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

    virtual void displayChat()  {
        // TODO: Implement chat display
        cout << "Chat: " << chatName << endl;
        for( Message& m : messages)
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

    void displayChat()  override {
        // TODO: Implement private chat display
        cout << "Private " << chatName << endl;
        for( Message& m : messages)
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
class GroupChat : public Chat {
private:
    vector<string> admins;
    string description;

public:
    // Constructor: initialize with users, name, and creator
    GroupChat(vector<string> users, string name, string creator)
        : Chat(users, name) {
        admins.push_back(creator); // creator is the first admin
        description = "No description set.";
    }

    // Add a new admin (must already be a participant)
    void addAdmin(string newAdmin) {
        if (isParticipant(newAdmin) && !isAdmin(newAdmin)) {
            admins.push_back(newAdmin);
        }
    }

    // Remove a participant (only if caller is admin)
    bool removeParticipant(const string& admin, const string& userToRemove) {
        if (!isAdmin(admin)) return false;

        auto it = find(participants.begin(), participants.end(), userToRemove);

        if (it != participants.end()) {
            participants.erase(it);
            return true;
        }

        return false;
    }

    // Check if user is admin
    bool isAdmin(string username) const {
        return find(admins.begin(), admins.end(), username) != admins.end();
    }

    // Check if user is participant
    bool isParticipant(string username) const {
        return find(participants.begin(), participants.end(), username) != participants.end();
    }

    // Set group description
    void setDescription(string desc) {
        description = desc;
    }

    // Display group chat info
    void displayChat()  override {
        cout << "Group Name: " << this->chatName << endl;
        cout << "Description: " << description << endl;

        cout << "Admins: ";
        for (const auto& admin : admins) cout << admin << " ";
        cout << endl;

        cout << "Participants: ";
        for (const auto& user : this->participants) cout << user << " ";
        cout << endl;
    }

    void sendJoinRequest(const string& username) {
        if (isParticipant(username)) {
            cout << username << " is already a member of the group.\n";
            return;
        }

        cout << username << " has requested to join the group \"" 
            << chatName << "\".\n";
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
            if(currentUserIndex == -1)
                return " " ;
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
            if(password.size()<6){
                cout<<"Password Must be at least 6 charachters\n";
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
    void updateProfile(){
        string status, phone;
        cout<<"Enter new status:\n";
        cin.ignore();
        getline(cin,status);
        cout<<"Enter new phone number:\n";
        cin>>phone;
        users[currentUserIndex].setStatus(status);
        users[currentUserIndex].setPhoneNumber(phone);
        cout<<"Profile updated successfully\n";
    }
    void changePassword(){
        string oldPass,newPass;

        cout<<"Enter old password:\n";
        cin>>oldPass;

        if(!users[currentUserIndex].checkPassword(oldPass)){
            cout<<"Incorrect password\n";
            return;
        }

        cout<<"Enter new password:\n";
        cin>>newPass;

        if(newPass.size() < 6){
            cout<<"Password must be at least 6 characters\n";
            return;
        }

        users[currentUserIndex].changePassword(newPass);

        cout<<"Password changed successfully\n";
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
        bool exit=false;
        while(!exit){
            privateChat->displayChat();
            cout<<"1. Send message\n2. Delete message\n3. Search message\n4. Exit\n";
            int choice;
            cin>>choice;
            if(choice == 1){
                cin.ignore(); 
                string content;
                PrivateChat* pc = dynamic_cast<PrivateChat*>(privateChat);
                pc->showTypingIndicator(currentUserName);
                cout << "Enter message: ";
                getline(cin, content);
                Message msg(currentUserName, content);
                privateChat->addMessage(msg);
            }
            // else if(choice == 2){
            //     int index;
            //     cout<<"Enter message index to reply to: ";
            //     cin>>index;

            //     vector<Message>& msgs = privateChat->getMessages();

            //     if(index < 0 || index >= msgs.size()){
            //         cout<<"Invalid message index\n";
            //         continue;
            //     }

            //     cin.ignore();
            //     string content;

            //     cout<<"Enter reply message: ";
            //     getline(cin,content);

            //     Message reply(currentUserName,content);
            //     reply.setReplyTo(&msgs[index]);

            //     privateChat->addMessage(reply);
            // }

            else if(choice == 2){
                int index;
                cout << "Enter message Index: ";
                cin >> index;
                if(privateChat->deleteMessage(index, currentUserName)){
                    cout << "Message deleted successfully\n";
                }
                else{
                    cout << "You can only delete your own messages\n";
                }
            }
            else if(choice == 3){
                cout<<"Enter KeyWord: ";
                string keyWord;
                cin>>keyWord;
                vector<Message> results = privateChat->searchMessages(keyWord);
                for(auto& m:results){
                    m.display();
                }
            }
            else {
               exit = true;
            }
        }
    }

    void createGroup() {
        string userName, groupName;
        string creator = getCurrentUsername();

        vector<string> users = {creator};

        cout << "Enter Group name\n";

        while (true) {
            cin.ignore();
            getline(cin, groupName);

            if (groupName.empty()) {
                cout << "Group name can't be empty\n";
            } else {
                break;
            }
        }

        int choice;
        bool Description=false;
        string description;
        while (true) {
            cout << "1. Add Group member\n2. Add Group description\n3. Create Group\n";
            cin >> choice;
            if (choice == 3) {
                break;
            }
            else if (choice == 1) {
                cout << "Enter Group member name\n";
                cin >> userName;
                for(auto &user:users){
                    if (userName == user) {
                        cout << "This user is already added\n";
                        break;
                    }
                }
                if (findUserIndex(userName) == -1) {
                    cout << "This user doesn't exist\n";
                }
                else {
                    users.push_back(userName);
                    continue;
                }
                
            }
            else if(choice ==2){
                cout<<"Enter group description:\n";
                cin.ignore();
                getline(cin,description);
                Description=true;
            }
            else {
                cout << "Invalid choice\n";
            }
        }
        Chat* groupChat = new GroupChat(users, groupName, creator);
        chats.push_back(groupChat);

        GroupChat* gc = dynamic_cast<GroupChat*>(groupChat);
        if(Description) gc->setDescription(description);

        cout << "Group created successfully\n";

        bool exit =false;
        while(!exit){
            cout<<"\nGroup Menu\n";
            cout<<"1.Add member\n2.Remove member\n3.Add admin\n4.Send message\n5.Delete message\n6.Search message\n7.Request to join\n8.Exit\n";            int choice;
            cin>>choice;
            if (choice == 1) {
                cout << "Enter Group member name\n";
                cin >> userName;
                if (findUserIndex(userName) == -1) {
                    cout << "This user doesn't exist\n";
                }
                else if (gc->isParticipant(userName)){
                    cout<<"user already in group\n";
                }
                else{
                    gc->getParticipants().push_back(userName);
                    cout<<"Member added\n";
                }
            }
            else if(choice==2){
                cout<<"Enter username to remove: ";
                string member;
                cin>>member;
                if(gc->removeParticipant(creator,member)){
                    cout<<"Member removed\n";
                }
                else{
                    cout<<"Only admins can remove members\n";
                }
            }
            else if(choice==3){
                cout<<"Enter username to make admin\n";
                string user;
                cin>>user;
                if(gc->isAdmin(creator)) gc->addAdmin(user);
                else cout<<"Only admins can add admins\n";
            }
            else if(choice==4){
                cin.ignore();
                string content;
                cout<<"Enter message: ";
                getline(cin,content);
                Message msg(creator,content);
                gc->addMessage(msg);
            }
            else if(choice == 5){
                        
                int index;
                cout << "Enter message index: ";
                cin >> index;

                if(gc->deleteMessage(index, creator))
                    cout << "Message deleted\n";
                else
                    cout << "You can only delete your own messages\n";
            }

            else if(choice == 6){

                string keyword;
                cout << "Enter keyword: ";
                cin >> keyword;

                vector<Message> results = gc->searchMessages(keyword);
                if(!results.size()){
                    cout<<"no messages found\n";
                }
                for(auto &m : results)
                    m.display();

            }

            else if(choice == 7){
                gc->sendJoinRequest(getCurrentUsername());
            }
            else if(choice == 8){
                exit = true;
            }
        }
    }
//delete participant, add admin, search for a messege
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
                cout << "\n1. Start Private Chat\n2. Create Group\n3. View Chats\n4. Update Profile\n5. Change Password\n6. Logout\nChoice: ";                int choice;
                cin >> choice;

                if (choice == 1) startPrivateChat();
                else if (choice == 2) createGroup();
                else if (choice == 3) viewChats();
                else if(choice == 4) updateProfile();
                else if(choice ==5) changePassword();
                else if(choice == 6) logout();            }
        }
    }
    ~WhatsApp() {
        for (Chat* chat : chats) {
            delete chat;
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
