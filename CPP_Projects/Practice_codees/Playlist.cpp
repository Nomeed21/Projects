#include <iostream>

using namespace std;

/*Add a song to the end
Remove a song by title
Search for a song
Display the playlist in order
Move to the next song*/
struct Node{
    string title;
    Node *next;
    Node *prev;

    Node(string name):title(name){}
};

class Playlist{
    private:
    Node *head;
    Node *tail;

    public:
    Playlist():head(nullptr), tail(nullptr){};
    ~Playlist(){
        Node *p;
        while(p!=nullptr){
            p = head;
            head = head->next;
            delete(p);
        }
    }

    int menu();
    void addSong(string name);
    void delSong(string name);
    void search(string name);
    void display();
    void nextSong();
    void currentSong();
};

int main(){
    Playlist list;
    string name;
    bool running = true;
    while(running){
        system("cls");
        

        switch(list.menu()){
            case 1:
            cout << "Enter song title: ";
            getline(cin, name);
            list.addSong(name);
            system("pause");
            break;

            case 2:
            cout << "Enter song title to delete: ";
            getline(cin, name);
            list.delSong(name);
            system("pause");
            break;

            case 3:
            cout << "Enter title to search";
            getline(cin, name);
            list.search(name);
            system("pause");
            break;

            case 4:
            list.display();
            system("pause");
            break;

            case 5:
            list.nextSong();
            system("pause");
            break;

            case 6:
            exit(0);
            
            default:
            cout << "Invalid choice!!!" << endl;
            system("pause");
        }
    }

    return 0;
}

int Playlist::menu(){
    int choice;
    if(head != nullptr){
            cout << "Current song playing: " << endl;
            currentSong();
    }
    cout << "Song player Menu" << endl
    << "[1] Add a Song" << endl
    << "[2] Remove a Song" << endl 
    << "[3] Search" << endl
    << "[4] Display all songs in queue" << endl
    << "[5] Skip" << endl
    << "[6] Exit" << endl;
    cin >> choice;
    cin.ignore();
    return choice;
}

    void Playlist::addSong(string name){
        Node *newNode;
        newNode = new Node(name);

        if(head==nullptr){
            head = newNode;
            tail = newNode;
        } else{
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }
    void Playlist::delSong(string name){
        Node *p, *q;
        p = q = head;
        while(p!=nullptr && p->title != name){
            q = p;
            p = p->next;
        }
        if(p == nullptr){
            cout << "No name found!" << endl;
        } else{
            if (p->prev != nullptr){
                p->prev->next = p->next;
            } else{
                head = head->next;
            }

            if (p->prev != nullptr)
                p->prev->next = p->next;
            else    
                tail = tail->prev;

            delete(p);
            cout << name << "Removed" << endl;
        }
    }
    void Playlist::search(string name){
        Node *p;
        p = head;
        int count;
        while(p!=nullptr && p->title != name){
            p = p->next;
            count++;
        }
        if(p==nullptr){
            cout << "Title not found!" << endl;
        }
        else{
            cout << "Song in queue at :" << count << endl;
        }
    }
    void Playlist::display(){
        Node *p;
        p = head;
        int count = 0;
        while(p!=nullptr){
            cout << "No." << ++count << "Title: " << p->title << endl;  
            p = p->next;
        }
    }
    void Playlist::nextSong(){
        Node *p;
        p = head;
        if(head->next == nullptr){
            delete(head);
        } else{
            head = head->next;
            delete(p);
        }
    }
    void Playlist::currentSong(){
        cout << head->title << endl;
    }