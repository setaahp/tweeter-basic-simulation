#include <iostream>
#include <string>
#include<algorithm>
#include<fstream>
#include<filesystem>
#include <algorithm> // for using transform 
#include <cctype> // for using toupper 
#include "menu/mmaker.h"
using namespace std;
namespace fs = std::filesystem;

int CUR_YEAR = 2024;
string ID = "0";
long long int ID_int = 0;
void find_id()
{
    string id;
    fstream file;
    string line = "";
    file.open("tweetID.txt", ios::in);
    if (!file)
        cout << "Error" << endl;
    file >> line;
    if (line.empty())
        line = "1";
    id  = line;
    file.close();
    ID_int = stoi(id) + 1;
    ID = to_string(ID_int);
}
int find_likes(string username, string id)
{
    vector<string> likes;
    int flag = 0;
    fstream file;
    string line = "";
    file.open(username + "/" + id + "/likes.txt", ios::in);
    if (!file)
        cout << "Error" << endl;
    while (!(file.eof()))
    {
        file >> line;
        if (line.empty())
            break;  
        for (int i = 0; i < likes.size(); i++)
        {
            if (line == likes[i])
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
            likes.push_back(line);
        flag = 0;        
    }
    file.close();
    return likes.size();
}
class Exit
{
    public:
        Exit(string);
};
class Main_page
{
    public:
        Main_page();
};
class Login;
string remove_space(string line)
{
    string result = "";
    for (int i = 0; i < line.size(); i++)
    {
        if (line[i] == ' ');
        else
            result += line[i];
    }
    return result;
}
bool space(string line)// if there is space returns true
{
    for (int i = 0; i < line.size(); i++) 
    {
        if (line[i] == ' ')
            return true;
    }
    return false;
};
bool check_sex(string sex) // returns false if sexuality is correct.
{
    if (int(sex[0]) == 0)
        return false;
    transform(sex.begin(), sex.end(), sex.begin(), ::toupper); 
    if (sex == "F" || sex == "FEMALE" || sex == "MALE" || sex == "M")
        return false;
    return true;
};
bool check_date(string date) // returns false if date is correct.
{
    int flag = 0;
    vector<int> d;
    int day, month, year = 0;
    if (int(date[0]) == 0)
        return false;
    if (date[2] == '/' && date[5] == '/')
    {
        for (int i = 0; i < date.size(); i++)
        {
            if (int(date[i]) - 48 <= 9 && int(date[i]) - 48 >= 0)
                d.push_back(int(date[i]) - 48);
            else
                flag ++;
        }
        if (flag == 2)
        {
            day = d[0] * 10 + d[1];
            month = d[2] * 10 + d[3];
            for (int i = 4; i < d.size(); i++)
                year = year * 10 + d[i];
            if (month <= 12 && month > 0)
            {
                // mpnth = 1, 3, 5, 7, 8, 10, 12 => 31 days.
                if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
                    if (day > 31 || day <= 0)
                        return true;
                // month = 4, 6, 9, 11 => 30 days.
                if (month == 4 || month == 6 || month == 9 || month == 11)
                    if (day > 30 || day <= 0)
                        return true;
                // month = 2 => 29 days.
                if (month == 2)
                    if (day > 29 || day <= 0)
                        return true;
                if (year > CUR_YEAR || year < 0)
                    return true;
                return false;
            }
            else    
                return true;
        }
        else 
            return true;
    }
    return true;   
};
bool check_username(string username) // returns false if it's unique.
{
    fstream file;
    string line;
    file.open("accounts.txt", ios::in);
    if (!file)
        cout << "Error" << endl;
    while(!(file.eof()))
    {
        file >> line;
        if (line == username)
        {
            file.close();
            return true;
        } 
    }
    file.close();
    return false;
};
vector<string> following;
bool check_following(string username, string username2) // if username in following username2 return false.
{
    //following.clear();
    fstream file;
    string line;
    file.open(username2 + "/followings.txt", ios::in);
    while (!(file.eof()))
    {
        file >> line;
        if (username == line) 
            return false;                
    }
    file.close();
    return true;    
}
bool check_email(string email)
{
    fstream file;
    string line;
    file.open("emails.txt", ios::in);
    if (!file)
        cout << "Error" << endl;
    while(!(file.eof()))
    {
        file >> line;
        if (line == email)
        {
            file.close();
            return true;
        }  
    }
    file.close();
    return false;
}
bool valid_email(string email) // if email is valid returns false.
{
    int anum = 0 , dnum = 0;
    if (email.size() == 0)
        return true;
    if (email[0] == '@' || email[email.size() - 1] == '@')
        return true;
    if (email[email.size() - 1] == '.')
        return true;
    for (int i = 0; i < email.size(); i++)
    {
        if (email[i] == '@')
            anum ++;
        if (email[i] == '.')
            dnum ++;
    }
    if (anum == 1 && dnum > 0)
    {
        for (int i = 0; i < email.size(); i++)
        {
            if (email[i] == '@')
                anum = i;
            if (email[i] == '.')
               dnum = i;
        }
        if (anum + 1 < dnum)
            return false;
        else    
            return true;
    }
    else
        return true;
}
bool valid_pass(string password) //if pass is valid returms false.
{
    int countnum = 0 , countl = 0 , countu = 0 , counts = 0;
    if (password.size() < 8)
        return true;
    for (int i = 0; i < password.size(); i++)
    {
        if (password[i] >= 48 && password[i] <= 57)
                countnum ++;
        if (password[i] >= 97 && password[i] <= 122)
                countl ++;
        if (password[i] >= 65 && password[i] <= 90)
                countu ++;
        if ((password[i] >= 33 && password[i] <= 47) || (password[i] >= 58 && password[i] <= 64) || 
            (password[i] >= 91 && password[i] <= 96) || (password[i] >= 123 && password[i] <= 126))
                counts ++;
    }
    if (countnum > 0 && countl > 0 && countu > 0 && counts > 0)
            return false;
    else
        return true;
}
bool check_pass(string username, string password) // if password is correct, returns true.
{
    fstream file;
    string line;
    file.open(username + "/password.txt", ios::in);
    if (!file)
        cout << "Error" << endl;
    file >> line;
    if (line == password)
        return true;
    return false;
    file.close();
}
bool check_delete(string id) // if deleted returns false.
{
    fstream file;
    string line;
    file.open("deletedID.txt", ios::in);
    if (!file)
        cout << "Error" << endl;
    while (!(file.eof()))
    {
        file >> line;
        if (line == id)
            return false;                   
    }
    file.close();
    return true;
}

class Tweet 
{
    private:
        string tweet;
        string id;
        string username; // this tweet is by username.
        string username2; // username2 wants to see this tweet.
        vector<string> like; // these people have liked this tweet.
        int likes = 0;
    public:
        void enter_tweet() 
        {
            menu obj6;
            string dummy = username + " : " + tweet; 
            string dummy2 = to_string(likes) + " LIKES ❤️";
            obj6.menu_head(dummy);
            obj6.add(dummy2, 1, "Like this Tweet."); 
            obj6.add("Replies", 2, "show / add replies."); 
            obj6.add("Back", 3, "Go Back.");
            if (username2 == username)
                obj6.add("Delete", 4, "Delete this Tweet.");
            getch();
            int w = obj6.display();
            switch (w)
            {
                case 1 :
                {
                    // you can like a tweet multiple times, but it will still count as one.
                    fstream file;
                    file.open(username + "/" + id + "/likes.txt", ios::app);
                    if (!file)
                        cout << "Error" << endl;
                    file << username2 << endl;
                    likes = find_likes(username, id);
                    enter_tweet();
                    break;
                }
                case 2 :
                {
                    someline5:
                    menu obj7;
                    obj7.menu_head("Replies");
                    obj7.add("Post reply", 1, "add a reply."); 
                    obj7.add("Replies", 2, "show all replies to this tweet."); 
                    obj7.add("Back", 3, "go back."); 
                    getch();
                    int r = obj7.display();
                    switch (r)
                    {
                        case 1 :
                        {
                            cout << "                                                                                                        Post Reply" << endl;
                            cout << "                                                                                                    ******************" << endl << endl;
                            string line;
                            string post;
                            find_id();
                            fs::create_directories(username + "/" + id + "/" + ID);
                            ofstream file(username + "/" + id + "/" + ID + "/tweet.txt");
                            if (!file)
                                cout << "Error" << endl;
                            cout << "Enter your Reply : ";
                            getline(cin, post);
                            file << post;
                            file.close();
                            ofstream file2(username + "/" + id + "/" + ID + "/likes.txt");
                            file2.close();
                            ofstream file5(username + "/" + id + "/" + ID + "/reply_by.txt");
                            file5 << username2;
                            file5.close();
                            fs::create_directories(username2 + "/" + ID);
                            ofstream file3(username2 + "/" + ID + "/tweet.txt");
                            if (!file3)
                                cout << "Error" << endl;
                            file3 << post;
                            file3.close();
                            ofstream file4(username2 + "/" + ID + "/likes.txt");
                            file4.close();
                            fstream file6;
                            file6.open("tweetID.txt", ios::out | ios::trunc);
                            file6 << ID;
                            file6.close();
                            goto someline5;
                            break;
                        }
                        case 2 :
                        {
                            menu obj8;
                            obj8.menu_head("Replies to : " + id);
                            obj8.add("Back", 1, "Go back."); //ok
                            fstream file;
                            string line;
                            int counter_id = 2;
                            find_id();
                            int max_id = stoi(ID);
                            string dummy3 = "";
                            while (counter_id < max_id)
                            {
                                string scounter_id = to_string(counter_id);
                                if (check_delete(scounter_id))
                                {
                                    file.open(username + "/" + id + "/" + scounter_id + "/tweet.txt", ios::in);
                                    if (!file);
                                    else
                                    {
                                        while (!(file.eof()))
                                        {
                                            file >> line;
                                            dummy3 = dummy3 + line + " ";
                                        }
                                        obj8.add(dummy3, counter_id, "open this reply.");
                                        file.close();
                                    }
                                }
                                counter_id ++;
                            } 
                            getch();
                            int k = obj8.display();
                            switch(k)
                            {
                                case 1 :
                                {
                                    break;
                                }
                                default : 
                                {
                                    fstream file;
                                    string line;
                                    string username_dummy;
                                    string scounterid = to_string(k);
                                    file.open(username + "/" + id + "/" + scounterid + "/reply_by.txt", ios::in);
                                    file >> line;
                                    username_dummy = line;
                                    file.close();
                                    Tweet tweetttt(username_dummy, username2, to_string(k));
                                    enter_tweet();
                                    break;
                                }
                            }
                            goto someline5;
                            break;

                        }
                        case 3 :
                        {
                            break;
                        }
                    }
                    break;
                }
                case 3 :
                {
                    break;
                }
                case 4 :
                {
                    fstream file;
                    file.open("deletedID.txt", ios::app);
                    if (!file)
                        cout << "Error" << endl;
                    file << endl << id;
                    file.close();
                    std::filesystem::remove_all(username + "/" + id); 
                    break;
                }
            }
            
        }
        Tweet(string username, string username2, string id) // username2 has opened a tweet by username
        {
            this -> username = username;
            this -> username2 = username2;
            this -> id = id;
            fstream file;
            string line;
            file.open(username + "/" + id + "/tweet.txt", ios::in);
            if (!file)
                cout << "Error" << endl;
            while (!(file.eof()))
            {
                file >> line;
                tweet = tweet + line + " ";
            }
            file.close();
            likes = find_likes(username, id);
            enter_tweet();
        }
};

class Profile
{
    private:
        string username;
        string username2;
        string name;
        string lname;
        string date;
        string sex;
    public:
        void enter_profile()
        {
            menu obj4;
            obj4.menu_head(username);
            obj4.add("Profile", 1, "Display Profile."); 
            obj4.add("Tweets", 2, "Display Tweets."); 
            obj4.add("Followers / Followings", 3, "Display Followers and Followings.");
            obj4.add("FOLLOW", 4, "To follow user."); 
            obj4.add("Back", 5, "Go to Home Page.");
            getch();
            int t = obj4.display();
            switch (t)
            {
                case 1 :
                {
                    fstream file;
                    string line;
                    file.open("accounts.txt", ios::in);
                    if (!file)
                        cout << "Error" << endl;
                    while(!(file.eof()))
                        {
                            file >> line;
                            if (line == username)
                            {
                                this -> username = line;
                                file.close();
                                file.open(username + "/name.txt", ios::in);
                                file >> line;
                                this -> name = line;
                                file.close();
                                file.open(username + "/lastname.txt", ios::in);
                                file >> line;
                                this -> lname = line;
                                file.close();
                                file.open(username + "/date.txt", ios::in);
                                file >> line;
                                this -> date = line;
                                file.close();
                                file.close();
                                file.open(username + "/sexuality.txt", ios::in);
                                file >> line;
                                this -> sex = line;
                                file.close();
                            }
                        }
                        file.close();
                        cout << "Username : " << username << endl;
                        cout << "Name : " << name << endl;
                        cout << "Last Name : " << lname << endl;
                        if (date == lname)
                            cout << "Date of birth : " << endl;
                        else
                            cout << "Date of birth : " << date << endl;
                        if (sex == lname || sex == date)
                            cout << "Sexuality : " << endl;
                        else
                            cout << "Sexuality : " << sex << endl;
                        enter_profile();
                        break;
                }
                case 2 :
                {
                    some_line2:
                    menu tweets;
                    tweets.menu_head("Tweets");
                    int flag = 0;
                    fstream file;
                    string line;
                    int counter_id = 2;
                    find_id();
                    int max_id = stoi(ID);
                    while (counter_id < max_id)
                    {
                        string scounter_id = to_string(counter_id);
                        if (check_delete(scounter_id))
                        {                       
                            file.open(username + "/" + scounter_id + "/tweet.txt", ios::in);
                            if(!file);
                            else 
                            {
                                string dummy = "";
                                while (!(file.eof()))
                                {
                                    file >> line;        
                                    dummy = dummy + line + " ";    
                                }
                                tweets.add(dummy, counter_id , username);
                                file.close();
                            }
                        }
                        counter_id++;
                        
                    }
                    tweets.add("Back", 1, "Go back.");
                    getch();
                    int e = tweets.display();
                    switch(e)
                    {
                        case 1 :
                        {
                            break;
                        }
                        default : 
                        {
                            Tweet tweetttt(username, username2, to_string(e));
                            goto some_line2;
                            break;
                        }
                    }
                    enter_profile();
                    break;
                }
                case 3 :
                {
                    fstream file;
                    string line;
                    file.open(username + "/followers.txt", ios::in);
                    if (!file)
                        cout << "Error" << endl;
                    cout << "Followers : " << endl;
                    while (!(file.eof()))
                    {
                        file >> line;
                        cout << line << endl;
                    }
                    file.close();
                    file.open(username + "/followings.txt", ios::in);
                    if (!file)
                        cout << "Error" << endl;
                    cout << "Followings : " << endl;
                    while (!(file.eof()))
                    {
                        file >> line;
                        cout << line << endl;
                    }
                    file.close();
                    enter_profile();
                    break;
                }
                case 4 :
                {
                    int flag = 0;
                    if (username == username2)
                    {
                        cout << "you can't follow yourself." << endl;
                        enter_profile();
                        break;
                    }
                    if (!check_following(username, username2))
                    {
                        cout << "you already follow this user." << endl;
                        flag = 1;
                    }  
                    if (flag == 0)
                    {
                        fstream file;
                        file.open(username2 + "/followings.txt", ios::app);
                        file << username;
                        file.close();
                        file.open(username + "/followers.txt", ios::app);
                        file << username2;
                        file.close();
                    }
                    enter_profile();
                    break;
                }
                case 5 : 
                {
                    break;
                }
            }
        }
        Profile(string username , string username2) // username2 searchs for username.
        {
            this -> username = username;
            this -> username2 = username2;
            enter_profile();
        }

};

class Signup
{
    private:
        string name;
        string lname;
        string username;
        string password;
        string password2;
        string email;
        string date;
        string sex;
        public:
        void create_account()
        {
            fstream file;
            file.open("accounts.txt", ios::app);
            if (!file)
                cout << "Error" << endl;
            file << username << endl;
            file.close();
            file.open("emails.txt", ios::app);
            if (!file)
                cout << "Error" << endl;
            file << email << endl;
            file.close();
            fs::create_directories(username);
            ofstream file1(username + "/name.txt");
            file1 << name;
            file1.close();
            ofstream file2(username + "/lastname.txt");
            file2 << lname;
            file2.close();
            ofstream file3(username + "/password.txt");
            file3 << password;
            file3.close();
            ofstream file4(username + "/date.txt");
            file4 << date;
            file4.close();
            ofstream file5(username + "/sexuality.txt");
            file5 << sex;
            file5.close();
            ofstream file6(username + "/email.txt");
            file6 << email;
            file6.close();
            ofstream file7(username + "/followers.txt");
            file7.close();
            ofstream file8(username + "/followings.txt");
            file8.close();

        }
        Signup()
        {
            cout << "\n\n";
            cout << "Name : ";
            getline(cin, name);
            while (space(name) || name.size() == 0)
            {
                cout << "Enter name without space !" << endl;
                cout << "Name : ";
                getline(cin, name);
            }
            cout << "Last Name : ";
            getline(cin, lname);
            while (space(lname) || lname.size() == 0)
            {
                cout << "Enter last name without space !" << endl;
                cout << "Last Name : ";
                getline(cin, lname);
            }
            cout << "Username : ";
            getline(cin, username);
            while (check_username(username) || space(username) || username.size() == 0)
            {
                cout << "please enter a different username." << endl;
                cout << "Username : ";
                getline(cin, username);
            }
            cout << "Email : ";
            getline(cin, email);
            while (check_email(email) || valid_email(email) || space(email))
            {
                cout << "please enter a different / valid emial." << endl;
                cout << "Email : ";
                getline(cin, email);
            }
            cout << "Password : ";
            getline(cin, password);
            while(valid_pass(password) || space(password) || password.size() == 0)
            {
                cout << "please enter a valid password." << endl;
                cout << "Password : ";
                getline(cin, password);
            }
            cout << "Repeat your Password : ";
            getline(cin, password2);
            while (password2 != password)
            {
                cout << "Password doesn't match." << endl;
                cout << "Password : ";
                getline(cin, password);
                while(valid_pass(password) || space(password) || password.size() == 0)
                {
                    cout << "please enter a valid password." << endl;
                    cout << "Password : ";
                    getline(cin, password);
                }
                cout << "Repeat your Password : ";
                getline(cin, password2);
            }
            cout << "Birth Date (Day / Month / Year): ";
            getline(cin, date);
            date = remove_space(date);
            while (check_date(date))
            {
                cout << "We don't accept alien dates, try again." << endl;
                cout << "Birth Date (Day / Month / Year): ";
                getline(cin, date);
                date = remove_space(date);   
            }
            cout << "Sexuality (F / M) : ";
            getline(cin, sex);
            sex = remove_space(sex);
            while (check_sex(sex))
            {
                cout << "try again." << endl;
                cout << "Sexuality (F / M) : ";
                getline(cin, sex);
                sex = remove_space(sex); 
            }
            create_account();
            Main_page main_page4;
        }
};

class Login
{
    private:
        string username;
        string password;
        string name;
        string lname;
        string sex;
        string date;
        string email;    
    public:
        void enter()
        {
            vector<string> tweets_v;
            menu obj2;
            obj2.menu_head("Home Page");
            obj2.add("Tweets", 1, "All the Tweets.");
            obj2.add("Settings", 2, "For exit.");
            obj2.add("Post", 3, "Post a Tweet.");
            obj2.add("My Profile", 4, "Personal information.");
            obj2.add("Search", 5, "Search");
            getch();
            int y = obj2.display();
            switch (y)
            {
                case 1 :
                {
                    some_line:
                    menu tweets;
                    tweets.menu_head("Tweets");
                    vector<pair<int,string>> id_following;
                    int flag = 0;
                    fstream file, file2;
                    string line;
                    file.open(username + "/followings.txt", ios::in);
                    if (!file)
                        cout << "Error" << endl;
                    while (!(file.eof()))
                    {
                        file >> line;
                        string username_dummy = line;
                        int flag = 0;
                        fstream file;
                        string line2;
                        int counter_id = 2;
                        find_id();
                        int max_id = stoi(ID);
                        while (counter_id < max_id)
                        {
                            string scounter_id = to_string(counter_id);
                            if (check_delete(scounter_id))
                            {                       
                                file2.open(username_dummy + "/" + scounter_id + "/tweet.txt", ios::in);
                                if (!file2);
                                else
                                {
                                    string dummy = "";
                                    while (!(file2.eof()))
                                    {
                                        file2 >> line2;        
                                        dummy = dummy + line2 + " ";    
                                    }
                                    tweets.add(dummy, counter_id , username_dummy);
                                    id_following.push_back({counter_id, username_dummy});
                                    file2.close();  
                                }
                            }
                            counter_id++;
                        }
                          
                    }
                    file.close();
                    tweets.add("Back", 1, "Go back.");
                    getch();
                    int q = tweets.display();
                    switch(q)
                    {
                        case 1 :
                        {
                            break;
                        }
                        default : 
                        {
                            for (int i = 0; i < id_following.size(); i++)
                            {
                                if (q == id_following[i].first)
                                    Tweet tweetttt(id_following[i].second, username, to_string(id_following[i].first));
                            } 
                            goto some_line;
                            break;
                        }
                    }
                    enter();
                    break;
                }
                case 2 :
                {
                    menu setting;
                    setting.menu_head("Settings");
                    setting.add("Edit", 1, "For Editting.");
                    setting.add("Exit", 2, "For Exit.");
                    getch();
                    int settt = setting.display();
                    string name2 = name;
                    string lname2 = lname;
                    string date2 = date;
                    string sex2 = sex;
                    string password2 = password;
                    switch (settt)
                    {
                        case 1 :
                        {
                            someline3:
                            menu edit;
                            edit.menu_head("Edit");
                            edit.add("Back", 1, "Go Back");
                            edit.add("Name", 2, "Change Name");
                            edit.add("Last Name", 3, "Change Last Name");
                            edit.add("Date", 4, "Change Date");
                            edit.add("Sexuality", 5, "Change Sexuality");
                            edit.add("Password", 6, "Change Password");
                            edit.add("Enter", 7, "To Finalize The Changes.");
                            getch();
                            int edittt = edit.display();
                            switch (edittt)
                            {
                                case 1 :
                                {
                                    enter();
                                    break;
                                }
                                case 2 :
                                {
                                    cout << "New Name : ";
                                    getline(cin, name2);
                                    while (space(name2) || name2.size() == 0)
                                    {
                                        cout << "Enter new name without space !" << endl;
                                        cout << "New Name : ";
                                        getline(cin, name2);
                                    }
                                    goto someline3;
                                    break;
                                }
                                case 3 :
                                {
                                    cout << "New Last Name : ";
                                    getline(cin, lname2);
                                    while (space(lname2) || lname2.size() == 0)
                                    {
                                        cout << "Enter new last name without space !" << endl;
                                        cout << "New Last Name : ";
                                        getline(cin, lname2);
                                    }
                                    goto someline3;
                                    break;
                                }
                                case 4 :
                                {
                                    cout << "New Birth Date (Day / Month / Year): ";
                                    getline(cin, date2);
                                    date2 = remove_space(date2);
                                    while (check_date(date2))
                                    {
                                        cout << "We don't accept alien dates, try again." << endl;
                                        cout << "New Birth Date (Day / Month / Year): ";
                                        getline(cin, date2);
                                        date2 = remove_space(date2);   
                                    }
                                    if (date2.size() == 0)
                                        date2 = "";
                                    goto someline3;
                                    break;
                                }
                                 case 5 :
                                {
                                    cout << "New Sexuality (F / M) : ";
                                    getline(cin, sex2);
                                    sex2 = remove_space(sex2);
                                    while (check_sex(sex2))
                                    {
                                        cout << "try again." << endl;
                                        cout << "New Sexuality (F / M) : ";
                                        getline(cin, sex2);
                                        sex2 = remove_space(sex2); 
                                    }
                                    if (sex2.size() == 0)
                                        sex = "";
                                    goto someline3;
                                    break;
                                }
                                case 6 :
                                {
                                    string password3;
                                    cout << "Password : ";
                                    getline(cin, password2);
                                    while(valid_pass(password2) || space(password2) || password2.size() == 0)
                                    {
                                        cout << "please enter a valid password." << endl;
                                        cout << "Password : ";
                                        getline(cin, password2);
                                    }
                                    cout << "Repeat your Password : ";
                                    getline(cin, password3);
                                    while (password3 != password2)
                                    {
                                        cout << "Password doesn't match." << endl;
                                        cout << "Password : ";
                                        getline(cin, password2);
                                        while(valid_pass(password2) || space(password2) || password2.size() == 0)
                                        {
                                            cout << "please enter a valid password." << endl;
                                            cout << "Password : ";
                                            getline(cin, password2);
                                        }
                                        cout << "Repeat your Password : ";
                                        getline(cin, password3);
                                    }
                                    goto someline3;
                                    break;
                                }
                                case 7 :
                                {
                                    name = name2;
                                    lname = lname2;
                                    date = date2;
                                    password = password2;
                                    sex = sex2;
                                    fstream file;
                                    string line;
                                    file.open(username + "/name.txt", ios::out | ios::trunc);
                                    file << name2;
                                    file.close();
                                    file.open(username + "/lastname.txt", ios::out | ios::trunc);
                                    file << lname2;
                                    file.close();
                                    file.open(username + "/date.txt", ios::out | ios::trunc);
                                    file << date2;
                                    file.close();
                                    file.open(username + "/password.txt", ios::out | ios::trunc);
                                    file << password2;
                                    file.close();
                                    file.open(username + "/sexuality.txt", ios::out | ios::trunc);
                                    file << sex2;
                                    file.close();
                                    enter();
                                    break;
                                }
                            }
                            break;
                        }
                        case 2 :
                        {
                            Exit exit(username);
                            break;
                        }
                    }
                    break;
                }
                case 3 :
                {
                    cout << "                                                                                                        Post" << endl;
                    cout << "                                                                                                    ************" << endl << endl;
                    string line;
                    string post;
                    find_id();
                    fs::create_directories(username + "/" + ID);
                    ofstream file(username + "/" + ID + "/tweet.txt");
                    if (!file)
                        cout << "Error" << endl;
                    cout << "Enter your Tweet : ";
                    getline(cin, post);
                    file << post;
                    file.close();
                    ofstream file2(username + "/" + ID + "/likes.txt");
                    file2.close();
                    fstream file3;
                    file3.open("tweetID.txt", ios::out | ios::trunc);
                    file3 << ID;
                    file3.close();
                    enter();
                    break;
                }
                case 4 :
                {
                    Profile profile(username, username);
                    enter();
                    break;
                }
                case 5 : 
                {
                    string username_s;
                    cout << "Search :   ";
                    getline(cin, username_s);
                    fstream file;
                    string line;
                    vector<pair<string,int>> search1;
                    vector<tuple<string,string,int>> search2;
                    int counter = 2;
                    someline4:
                    menu searched;
                    searched.menu_head("Results for " + username_s);
                    searched.add("Back", 1, "Go back");
                    file.open("accounts.txt", ios::in);
                    while(!(file.eof()))
                    {
                        int flag = 0;
                        string username_dummy, name_dummy, lname_dummy;
                        file >> line;
                        username_dummy = line;
                        fstream file2;
                        string line2;
                        file2.open(username_dummy + "/name.txt", ios::in);
                        file2 >> line2;
                        name_dummy = line2;
                        file2.close();
                        file2.open(username_dummy + "/lastname.txt", ios::in);
                        file2 >> line2;
                        lname_dummy = line2;
                        file2.close();
                        file2.open(username_dummy + "/" + username_s + "/tweet.txt", ios::in);
                        if (file2)
                            flag = 1;
                        file2.close();
                        if(username_dummy == username_s || name_dummy == username_s || lname_dummy == username_s)
                        {
                            if (search1.size() > 0 )
                            {
                                if(search1[search1.size() - 1].first == username_dummy);
                                else
                                {
                                    search1.push_back({username_dummy, counter});
                                    counter ++;
                                }
                            }
                            else
                            {
                                search1.push_back({username_dummy, counter});
                                counter ++;
                            }
                        }
                        else if (flag == 1)
                        {
                            search2.push_back({username_s, username_dummy, counter}); // tweet by username_dummy with id username_s.
                            counter ++;
                        }
                    }
                    file.close();
                    for (int  i = 0; i < search1.size(); i++)
                        searched.add(search1[i].first, search1[i].second, "Open this profile.");
                    for (int  i = 0; i < search2.size(); i++)
                        searched.add(get<0>(search2[i]), get<2>(search2[i]), "Open this tweet.");
                    getch();
                    int v = searched.display();
                    switch (v)
                    {
                        case 1 :
                        {
                            enter();
                            break;
                        }
                        default :
                        {
                            for (int i = 0; i < search1.size(); i++)
                            {
                                if (v == search1[i].second)
                                {
                                    Profile(search1[i].first, username);
                                    goto someline4;
                                }
                            }
                            for (int i = 0; i <search2.size(); i++)
                            {
                                if (v == get<2>(search2[i]))
                                {
                                    Tweet(get<1>(search2[i]), username, get<0>(search2[i]));
                                    enter();
                                }
                            }
                            break;
                        }
                    }
                }
            }
        }
        void set(string username)
        {
            fstream file, file2;
            string line;
            int flag = 0;
            file.open("accounts.txt", ios::in);
            if (!file)
                cout << "Error" << endl;
            while(!(file.eof()))
            {
                file >> line;
                if (username == line)
                {
                    this -> username = line;
                    flag = 1;
                }
            }
            file.close();
            file.open("emails.txt", ios::in);
            if (!file)
                cout << "Error" << endl;
            while(!(file.eof()) && flag == 0)
            {
                file >> line;
                if (username == line)
                {
                    this -> email = line;
                    flag = 2;
                }
            }
            file.close();
            int counter = 0;
            int counter2 = 0;
            if (flag == 2)
            {
                
                file.open("emails.txt", ios::in);
                if (!file)
                    cout << "Error" << endl;
                while(!(file.eof()))
                {
                    file >> line;
                    if (line == email)
                    {
                        if (counter == 0)
                            flag = 3;
                        break;
                    }
                        
                    counter++;
                }
                file.close();
            }
            file.open("accounts.txt", ios::in);
            if (!file)
                cout << "Error" << endl;
            while(!(file.eof()))
                {
                    file >> line;
                    if (line == username || (counter2 == counter && counter != 0 || flag == 3) )
                    {
                        this -> username = line;
                        string line2;
                        file2.open(line + "/name.txt", ios::in);
                        file2 >> line2;
                        this -> name = line2;
                        file2.close();
                        file2.open(line + "/lastname.txt", ios::in);
                        file2 >> line2;
                        this -> lname = line2;
                        file2.close();
                        file2.open(line + "/date.txt", ios::in);
                        line2 = "";
                        file2 >> line2;
                        this -> date = line2;
                        file2.close();
                        file2.open(line + "/password.txt", ios::in);
                        file2 >> line2;
                        this -> password = line2;
                        file2.close();
                        file2.open(line + "/sexuality.txt", ios::in);
                        line2 = "";
                        file2 >> line2;
                        this -> sex = line2;
                        file2.close();
                        file2.open(line + "/email.txt", ios::in);
                        file2 >> line2;
                        this -> email = line2;
                        file2.close();
                    }
                    flag = 0;
                    counter2++;
                }
                file.close();


        }
        Login()
        {
            cout << "Username or Email : ";
            getline(cin, username);
            while (!(check_username(username)) && !(check_email(username)))
            {
                cout << "please enter a valid username or email." << endl;
                cout << "Username or Email : ";
                getline(cin, username);
            }
            set(username);
            cout << "Password : ";
            getline(cin, password);
            while (!(check_pass(username, password)))
            {
                cout << "please enter the correct password." << endl;
                cout << "Password : ";
                getline(cin, password);
            }
            enter();
        }
        Login(string username)
        {
            set(username);   
        }
        friend class Exit;
};

Main_page::Main_page()
{
    menu obj;
    obj.menu_head("My Twitter");
    obj.add("Login", 1, "I already have an account.");
    obj.add("Signup", 2, "I want to make an account.");
    obj.add("Exit", 3, "I want to Exit.");
    getch();
    int x = obj.display();
        switch (x)
        {
            case 1 :
            {
                cout << "                                                                                                       Login" << endl;
                cout<< "                                                                                                  ***************" << endl << endl;
                Login login;
                break;
            }
            case 2 :
            {
                cout << "                                                                                                       Signup" << endl;
                cout << "                                                                                                 ******************" << endl << endl;
                Signup signup;
                break;
            }
            case 3 :
                Exit exit("main_page");
                break;
        }
};

Exit::Exit(string command)
{
    if (command == "main_page")
    {
        menu obj3;
        obj3.add("Yes", 1, "Are you sure you want to exit ?");
        obj3.add("No", 2, "Are you sure you want to exit ?");
        int z = obj3.display();
        switch (z)
        {
            case 1 :
            {
                break;
            }
            case 2 :
            {
                Main_page main_page2;
                break;
            }
        }
    }
    else
    {
        menu obj3;
        obj3.menu_head("Exit");
        obj3.add("Yes", 1, "Are you sure you want to exit ?");
        obj3.add("No", 2, "Are you sure you want to exit ?");
        int z = obj3.display();
        switch (z)
        {
            case 1 :
            {
                Main_page main_page3;
                break;
            }
            case 2 :
            {
                Login login(command);
                login.enter();
                break;
            }
        }
    }
};

int main()
{
    Main_page main_page;
}