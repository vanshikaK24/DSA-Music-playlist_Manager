#include <iostream>
#include <string>
#include <limits>
using namespace std;

// Node class representing one song in the playlist
class Node {
public:
    string title;
    string artist;
    Node* prev;
    Node* next;

    Node(string t, string a) {
        title = t;
        artist = a;
        prev = nullptr;
        next = nullptr;
    }
};

// Doubly Linked List for Music Playlist Manager
class MusicPlaylistManager {
private:
    Node* head;       // Points to the first song
    Node* current;    // Points to the currently selected song

public:
    // Constructor
    MusicPlaylistManager() {
        head = nullptr;
        current = nullptr;
    }

    // Release all dynamically allocated nodes(destructor)
    ~MusicPlaylistManager() {
        Node* q = head;

        while (q != nullptr) {
            Node* p = q;
            q = q->next;
            delete p;
        }
    }

    // 1. Add a song at the end of the playlist
    void addSong(string title, string artist) {
        Node* p = new Node(title, artist); // p points to new node

        if (head == nullptr) {
            head = p;
            current = p;
        } else {
            Node* q = head; // q traverses the playlist

            while (q->next != nullptr) {
                q = q->next;
            }

            q->next = p;
            p->prev = q;
        }

        cout << "Song added successfully!\n";
    }

    // 2. Delete a song by title
    void deleteSong(string title) {
        Node* p;
        Node* q = head;

        if (head == nullptr) {
            cout << "Playlist is empty!\n";
            return;
        }

        // Search for the song
        while (q != nullptr && q->title != title) {
            q = q->next;
        }

        if (q == nullptr) {
            cout << "Song not found!\n";
            return;
        }

        p = q; // p points to the node to be deleted

        // Update current before deleting its node
        if (current == p) {
            if (p->next != nullptr)
                current = p->next;
            else
                current = p->prev;
        }

        // Deleting the first node
        if (p == head) {
            head = p->next;

            if (head != nullptr) {
                head->prev = nullptr;
            }
        } else {
            p->prev->next = p->next;

            if (p->next != nullptr) {
                p->next->prev = p->prev;
            }
        }

        delete p;

        cout << "Song deleted successfully!\n";

        if (head == nullptr) {
            current = nullptr;
        }
    }

    // 3. Display playlist in forward direction
    void displayPlaylist() {
        Node* q = head;

        if (q == nullptr) {
            cout << "Playlist is empty!\n";
            return;
        }

        cout << "\n--- Music Playlist ---\n";

        int i = 1;

        while (q != nullptr) {
            cout << i++ << ". " << q->title
                 << " - " << q->artist;

            if (q == current)
                cout << " [CURRENT SONG]";

            cout << "\n";
            q = q->next;
        }
    }

    // 4. Display playlist in reverse direction
    void displayReverse() {
        Node* q = head;

        if (q == nullptr) {
            cout << "Playlist is empty!\n";
            return;
        }

        // Move q to the last node
        while (q->next != nullptr) {
            q = q->next;
        }

        cout << "\n--- Reverse Playlist ---\n";

        while (q != nullptr) {
            cout << q->title << " - "
                 << q->artist << "\n";

            q = q->prev;
        }
    }

    // 5. Play the current song
    void playCurrentSong() {
        if (current == nullptr) {
            cout << "No song available to play!\n";
            return;
        }

        cout << "\nNow Playing: " << current->title
             << " - " << current->artist << "\n";
    }

    // 6. Play the next song
    void playNextSong() {
        if (current == nullptr) {
            cout << "Playlist is empty!\n";
            return;
        }

        if (current->next == nullptr) {
            cout << "Already at the last song!\n";
            return;
        }

        current = current->next;
        playCurrentSong();
    }

    // 7. Play the previous song
    void playPreviousSong() {
        if (current == nullptr) {
            cout << "Playlist is empty!\n";
            return;
        }

        if (current->prev == nullptr) {
            cout << "Already at the first song!\n";
            return;
        }

        current = current->prev;
        playCurrentSong();
    }

    // 8. Play the complete playlist
    void playCompletePlaylist() {
        Node* q = head;

        if (q == nullptr) {
            cout << "Playlist is empty!\n";
            return;
        }

        cout << "\n--- Playing Complete Playlist ---\n";

        while (q != nullptr) {
            current = q;

            cout << "Now Playing: " << current->title
                 << " - " << current->artist << "\n";

            q = q->next;
        }

        cout << "Playlist completed!\n";
    }

    // 9. Repeat the complete playlist
    void repeatAll() {
        if (head == nullptr) {
            cout << "Playlist is empty!\n";
            return;
        }

        int repetitions;

        cout << "Enter number of repetitions: ";
        if (!(cin >> repetitions)) {
            cout << "Invalid input!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (repetitions <= 0) {
            cout << "Enter a positive number!\n";
            return;
        }

        for (int i = 1; i <= repetitions; i++) {
            cout << "\nRepetition " << i << "\n";

            // Start again from the first song
            Node* q = head;

            while (q != nullptr) {
                current = q;

                cout << "Now Playing: " << current->title
                     << " - " << current->artist << "\n";

                q = q->next;
            }
        }

        cout << "Repeat All completed!\n";
    }

    // 10. Show the current song
    void showCurrentSong() {
        if (current == nullptr) {
            cout << "No current song selected!\n";
            return;
        }

        cout << "\nCurrent Song: " << current->title
             << " - " << current->artist << "\n";
    }
};

// Main function
int main() {
    MusicPlaylistManager playlist;
    int choice;
    string title, artist;

    do {
        cout << "\n===== MUSIC PLAYLIST MANAGER =====\n";
        cout << "1. Add Song\n";
        cout << "2. Delete Song\n";
        cout << "3. Display Playlist\n";
        cout << "4. Display Playlist in Reverse\n";
        cout << "5. Play Current Song\n";
        cout << "6. Play Next Song\n";
        cout << "7. Play Previous Song\n";
        cout << "8. Play Complete Playlist\n";
        cout << "9. Repeat All\n";
        cout << "10. Show Current Song\n";
        cout << "11. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input! Enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            cout << "Enter song title: ";
            getline(cin, title);

            cout << "Enter artist name: ";
            getline(cin, artist);

            playlist.addSong(title, artist);
            break;

        case 2:
            cout << "Enter song title to delete: ";
            getline(cin, title);

            playlist.deleteSong(title);
            break;

        case 3:
            playlist.displayPlaylist();
            break;

        case 4:
            playlist.displayReverse();
            break;

        case 5:
            playlist.playCurrentSong();
            break;

        case 6:
            playlist.playNextSong();
            break;

        case 7:
            playlist.playPreviousSong();
            break;

        case 8:
            playlist.playCompletePlaylist();
            break;

        case 9:
            playlist.repeatAll();
            break;

        case 10:
            playlist.showCurrentSong();
            break;

        case 11:
            cout << "Exiting Music Playlist Manager.\n";
            break;

        default:
            cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 11);

    return 0;
}