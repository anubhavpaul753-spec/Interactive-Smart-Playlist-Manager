#include <iostream>
#include <vector>
using namespace std;

class Node {
    public:
        int data;
        Node* next;
        Node* prev;

        Node(int val) {
            data = val;
            next = nullptr;
            prev = nullptr;
        }
};

class DoublyCircularList {
    public:
        Node* head;
        Node* tail;
        int len;

        DoublyCircularList() {
            head = tail = nullptr;
            len = 0;
        }

        void VectorToList(vector<int> nums) {
            int n = nums.size();
            for(int i = 0; i < n; i++) {
                Node* tmp = new Node(nums[i]);
                if(head == nullptr) {
                    head = tail = tmp;
                }
                else {
                    tail->next = tmp;
                    tmp->prev = tail;
                    tail = tmp;
                }
                len++;
            }
            tail->next = head;
            head->prev = tail;
        }

        void AddNewSong(int id) {
            Node* newsong = new Node(id);
            if(head == nullptr) {
                head = tail = newsong;
                head->next = head;
                head->prev = head;
                len++;
            }
            else {
                tail->next = newsong;
                newsong->prev = tail;
                tail = newsong;
                tail->next = head;
                head->prev = tail;
                len++;
            }
        }

        void DeleteAtIdx(int idx) {
            if(idx < 1 || idx > len) {
                cout << "Invalid Index" << endl;
                return;
            }
            else if(idx == 1) {
                if(head->next == head) {
                    Node* del = head;
                    head = tail = nullptr;
                    delete(del);
                }
                else {
                    Node* head2 = head->next;
                    head2->prev = tail;
                    tail->next = head2;
                    Node* del = head;
                    head = head2;
                    delete(del);
                }
                len--;
            }
            else if(idx == len) {
                if(head->next == head) {
                    Node* del = head;
                    head = tail = nullptr;
                    delete(del);
                }
                else {
                    Node* beforetail = tail->prev;
                    beforetail->next = head;
                    head->prev = beforetail;
                    Node* del = tail;
                    tail = beforetail;
                    delete(del);
                }
                len--;
            }
            else {
                Node* curr = head;
                for(int i = 1; i <= (idx - 2); i++) {
                    curr = curr->next;
                }
                Node* del = curr->next;
                curr->next = curr->next->next;
                curr->next->prev = curr;
                delete(del);
                len--;
            }
        }

        void PlayBackMenu() {
            if(head == nullptr) {
                cout << "The Song List is Empty" << endl;
                return;
            }
            else {
                Node* curr = head;
                int choice = 0;
                cout << "--- SMART PLAYLIST (REPEAT: ON) ---" << endl;
                while(true) {
                    cout << endl;
                    cout << "Currently Playing Song ID: " << curr->data << endl;
                    cout << "1. Next Song" << endl;
                    cout << "2. Previous Song" << endl;
                    cout << "3. Add Song" << endl;
                    cout << "4. Delete Song At Index" << endl;
                    cout << "5. Show Entire Playlist" << endl;
                    cout << "6. Exit" << endl;
                    cout << "Choice: ";
                    cin >> choice;

                    if(choice == 1) {
                        if(curr->next != head) {
                            curr = curr->next;
                            cout << "Now Playing Song ID: " << curr->data << endl;
                        }
                        else {
                            cout << "End of playlist, looping back to start..." << endl;
                            curr = curr->next;
                            cout << "Now Playing Song ID: " << curr->data << endl;
                        }
                    }
                    else if(choice == 2) {
                        if(curr->prev != tail) {
                            curr = curr->prev;
                            cout << "Now Playing Song ID: " << curr->data << endl;
                        }
                        else {
                            cout << "Start of playlist, looping to the end..." << endl;
                            curr = curr->prev;
                            cout << "Now Playing Song ID: " << curr->data << endl;
                        }
                    }
                    else if(choice == 3) {
                        int val;
                        cout << "Enter new Song ID: ";
                        cin >> val;
                        AddNewSong(val);
                        cout << "Song " << val << " added to the queue!" << endl;
                    }
                    else if(choice == 4) {
                        int index;
                        cout << "Choose an index between 1 and " << len << " to delete: ";
                        cin >> index;

                        if(index < 1 || index > len) {
                            cout << "Invalid Index" << endl;
                        }
                        else {
                            Node* check = head;
                            for(int i = 1; i < index; i++) {
                                check = check->next;
                            }

                            if(check == curr) {
                                if(len == 1) {
                                    DeleteAtIdx(index);
                                    cout << "Playlist is now empty." << endl;
                                    curr = nullptr;
                                    break;
                                }
                                else {
                                    curr = curr->next;
                                }
                            }
                            DeleteAtIdx(index);
                        }
                    }
                    else if(choice == 5) {
                        cout << "Playlist: ";
                        Node* travel = head;
                        do {
                            cout << travel->data << " -> ";
                            travel = travel->next;
                        } while(travel != head);
                        cout << "(Back to " << head->data << ")" << endl;
                    }
                    else if(choice == 6) {
                        if(head != nullptr) {
                            tail->next = nullptr;
                            Node* travel = head;
                            while(travel != nullptr) {
                                Node* after = travel->next;
                                delete(travel);
                                travel = after;
                            }
                            head = tail = nullptr;
                        }
                        cout << "Breaking the circle and freeing memory..." << endl;
                        cout << "Program terminated successfully." << endl;
                        break;
                    }
                }
            }
        }
};

int main() {
    vector<int> arr = {101, 202, 303, 404, 505, 606, 707};
    DoublyCircularList playlist;
    playlist.VectorToList(arr);
    playlist.PlayBackMenu();
    return 0;
}