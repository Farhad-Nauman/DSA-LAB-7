
#include <iostream>
#include <string>
using namespace std;

struct Student {
    int studentID;
    string name;
    float GPA;
    Student* left;
    Student* right;
    Student(int id, string n, float g) {
        studentID = id;
        name = n;
        GPA = g;
        left = NULL;
        right = NULL;
    }
};
Student* insert(Student* root, int id, string name, float gpa) {
    if (root == NULL)
        return new Student(id, name, gpa);

    if (id < root->studentID)
        root->left = insert(root->left, id, name, gpa);
    else if (id > root->studentID)
        root->right = insert(root->right, id, name, gpa);
    else
        cout << "Student ID already exists." << endl;

    return root;
}
Student* search(Student* root, int id) {
    if (root == NULL || root->studentID == id)
        return root;

    if (id < root->studentID)
        return search(root->left, id);

    return search(root->right, id);
}
Student* minimum(Student* root) {
    while (root != NULL && root->left != NULL)
        root = root->left;
    return root;
}
Student* removeStudent(Student* root, int id) {
    if (root == NULL)
        return NULL;

    if (id < root->studentID) {
        root->left = removeStudent(root->left, id);
    } else if (id > root->studentID) {
        root->right = removeStudent(root->right, id);
    } else {
        if (root->left == NULL) {
            Student* temp = root->right;
            delete root;
            return temp;
        }
        if (root->right == NULL) {
            Student* temp = root->left;
            delete root;
            return temp;
        }
        Student* temp = minimum(root->right);
        root->studentID = temp->studentID;
        root->name = temp->name;
        root->GPA = temp->GPA;
        root->right = removeStudent(root->right, temp->studentID);
    }
    return root;
}
void inorder(Student* root) {
    if (root == NULL)
        return;

    inorder(root->left);
    cout << "ID: " << root->studentID
         << ", Name: " << root->name
         << ", GPA: " << root->GPA << endl;
    inorder(root->right);
}
int countStudents(Student* root) {
    if (root == NULL)
        return 0;

    return 1 + countStudents(root->left)
             + countStudents(root->right);
}
void findGPA(Student* root, Student*& high, Student*& low) {
    if (root == NULL)
        return;
    if (high == NULL || root->GPA > high->GPA)
        high = root;
    if (low == NULL || root->GPA < low->GPA)
        low = root;
    findGPA(root->left, high, low);
    findGPA(root->right, high, low);
}
void aboveGPA(Student* root, float limit) {
    if (root == NULL)
        return;
    aboveGPA(root->left, limit);

    if (root->GPA > limit) {
        cout << "ID: " << root->studentID
             << ", Name: " << root->name
             << ", GPA: " << root->GPA << endl;
    }
    aboveGPA(root->right, limit);
}
int main() {
    Student* root = NULL;
    int choice, id;
    string name;
    float gpa, limit;
    do {
        cout << "\n1. Insert Student";
        cout << "\n2. Search Student";
        cout << "\n3. Delete Student";
        cout << "\n4. Display All Students";
        cout << "\n5. Count Students";
        cout << "\n6. Highest and Lowest GPA";
        cout << "\n7. Students Above GPA";
        cout << "\n0. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter student ID: ";
            cin >> id;
            cout << "Enter name: ";
            cin >> ws;
            getline(cin, name);
            cout << "Enter GPA: ";
            cin >> gpa;
            root = insert(root, id, name, gpa);
        } else if (choice == 2) {
            cout << "Enter student ID: ";
            cin >> id;
            Student* s = search(root, id);

            if (s != NULL) {
                cout << "ID: " << s->studentID
                     << ", Name: " << s->name
                     << ", GPA: " << s->GPA << endl;
            } else {
                cout << "Student not found." << endl;
            }
        } else if (choice == 3) {
            cout << "Enter student ID: ";
            cin >> id;
            if (search(root, id) == NULL) {
                cout << "Student not found." << endl;
            } else {
                root = removeStudent(root, id);
                cout << "Student deleted." << endl;
            }
        } else if (choice == 4) {
            if (root == NULL)
                cout << "No student records." << endl;
            else
                inorder(root);
        } else if (choice == 5) {
            cout << "Total students: "
                 << countStudents(root) << endl;
        } else if (choice == 6) {
            Student* high = NULL;
            Student* low = NULL;

            findGPA(root, high, low);

            if (high == NULL) {
                cout << "No student records." << endl;
            } else {
                cout << "Highest GPA: " << high->name
                     << " (" << high->GPA << ")" << endl;
                cout << "Lowest GPA: " << low->name
                     << " (" << low->GPA << ")" << endl;
            }
        } else if (choice == 7) {
            cout << "Enter GPA threshold: ";
            cin >> limit;

            aboveGPA(root, limit);
        } else if (choice != 0) {
            cout << "Invalid choice." << endl;
        }
    } while (choice != 0);

    cout << "Program ended." << endl;
    return 0;
}
