#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;

// ============================================================
// COMMON VALIDATION / INPUT
// ============================================================

void showHeading(const string& title)
{
    cout << "\n==============================================\n";
    cout << "              " << title << "\n";
    cout << "==============================================\n";
}

bool isDigits(const string& s)
{
    if(s.empty()) return false;

    for(string::const_iterator it=s.begin(); it!=s.end(); ++it)
    {
        if(!isdigit((unsigned char)*it))
            return false;
    }

    return true;
}

bool isValidId(const string& id, char prefix)
{
    return id.size() >= 2 &&
           id[0] == prefix &&
           isDigits(id.substr(1));
}

bool isValidPhone(const string& p)
{
    return p.size() == 10 && isDigits(p);
}

bool isValidPassword(const string& p)
{
    if(p.size() != 8)
        return false;

    bool upper=false;
    bool number=false;
    bool special=false;

    for(string::const_iterator it=p.begin(); it!=p.end(); ++it)
    {
        char c=*it;

        if(isupper((unsigned char)c))
            upper=true;
        else if(isdigit((unsigned char)c))
            number=true;
        else if(!isalnum((unsigned char)c))
            special=true;
    }

    return upper && number && special;
}

bool isValidEmail(const string& e)
{
    size_t at=e.find('@');

    return at != string::npos &&
           at > 0 &&
           e.substr(at) == "@gmail.com";
}

string inputLine(const string& prompt)
{
    cout << prompt;

    string s;
    getline(cin >> ws,s);

    return s;
}

int inputInt(const string& prompt)
{
    int x;

    cout << prompt;
    cin >> x;

    return x;
}

string askPassword()
{
    string p;

    do
    {
        p=inputLine(
            "Password (8 chars, 1 uppercase, 1 number, 1 special): "
        );

        if(!isValidPassword(p))
        {
            cout << "Invalid password. Example: Abc@1234\n";
        }

    }while(!isValidPassword(p));

    return p;
}

string askEmail()
{
    string e;

    do
    {
        e=inputLine("Email: ");

        if(!isValidEmail(e))
        {
            cout << "Use a valid @gmail.com email.\n";
        }

    }while(!isValidEmail(e));

    return e;
}

string askPhone()
{
    string p;

    do
    {
        p=inputLine("Phone (10 digits): ");

        if(!isValidPhone(p))
        {
            cout << "Phone must contain exactly 10 digits.\n";
        }

    }while(!isValidPhone(p));

    return p;
}

// ============================================================
// USER BASE CLASS
// ============================================================

class User
{
protected:

    string id;
    string name;
    string email;
    string password;
    string phone;

public:

    User(){}

    User(string i,string n,string e,string p,string ph)
        : id(i),
          name(n),
          email(e),
          password(p),
          phone(ph)
    {
    }

    string getId() const
    {
        return id;
    }

    string getName() const
    {
        return name;
    }

    bool checkPassword(const string& p) const
    {
        return p == password;
    }

    void update(string n,string e,string ph)
    {
        name=n;
        email=e;
        phone=ph;
    }

    void display() const
    {
        cout << "ID: " << id << "\n";
        cout << "Name: " << name << "\n";
        cout << "Email: " << email << "\n";
        cout << "Phone: " << phone << "\n";
    }
};

// ============================================================
// PROBLEM
// ============================================================

class Problem
{
    string id;
    string title;
    string description;
    string difficulty;
    string creatorAdminId;

    int marks;

public:

    Problem(
        string i,
        string t,
        string d,
        string df,
        int m,
        string a
    )
        : id(i),
          title(t),
          description(d),
          difficulty(df),
          creatorAdminId(a),
          marks(m)
    {
    }

    string getId() const
    {
        return id;
    }

    string getCreator() const
    {
        return creatorAdminId;
    }

    int getMarks() const
    {
        return marks;
    }

    void update(
        string t,
        string d,
        string df,
        int m
    )
    {
        title=t;
        description=d;
        difficulty=df;
        marks=m;
    }

    void display() const
    {
        cout << "\nProblem ID: " << id
             << "\nTitle: " << title
             << "\nDescription: " << description
             << "\nDifficulty: " << difficulty
             << "\nMarks: " << marks
             << "\nCreated By Admin: " << creatorAdminId
             << "\n";
    }
};

// ============================================================
// ASSIGNMENT
// ============================================================

class Assignment
{
    string id;
    string title;
    string deadline;
    string teacherId;

    int marks;

public:

    Assignment(
        string i,
        string t,
        string d,
        int m,
        string tid
    )
        : id(i),
          title(t),
          deadline(d),
          teacherId(tid),
          marks(m)
    {
    }

    string getId() const
    {
        return id;
    }

    string getTeacherId() const
    {
        return teacherId;
    }

    int getMarks() const
    {
        return marks;
    }

    void display() const
    {
        cout << "\nAssignment ID: " << id
             << "\nTitle: " << title
             << "\nDeadline: " << deadline
             << "\nMarks: " << marks
             << "\nCreated By Teacher: " << teacherId
             << "\n";
    }
};

// ============================================================
// CONTEST
// ============================================================

class Contest
{
    string id;
    string title;
    string date;
    string teacherId;

    int maxScore;

public:

    Contest(
        string i,
        string t,
        string d,
        int m,
        string tid
    )
        : id(i),
          title(t),
          date(d),
          teacherId(tid),
          maxScore(m)
    {
    }

    string getId() const
    {
        return id;
    }

    int getMaxScore() const
    {
        return maxScore;
    }

    void display() const
    {
        cout << "\nContest ID: " << id
             << "\nTitle: " << title
             << "\nDate: " << date
             << "\nMaximum Score: " << maxScore
             << "\nCreated By Teacher: " << teacherId
             << "\n";
    }
};

// ============================================================
// STUDENT
// ============================================================

class Student : public User
{
    int problemsSolved;
    int assignmentsCompleted;
    int score;

    int contestsParticipated;
    int contestWins;
    int contestScore;

    int leetcodeSolved;
    int codechefSolved;
    int hackerrankSolved;
    int gfgSolved;
    int codeforcesSolved;

    int activeDays;

    vector<string> solvedProblems;
    vector<string> completedAssignments;
    vector<string> participatedContests;

public:

    Student(
        string i,
        string n,
        string e,
        string p,
        string ph
    )
        : User(i,n,e,p,ph),
          problemsSolved(0),
          assignmentsCompleted(0),
          score(0),
          contestsParticipated(0),
          contestWins(0),
          contestScore(0),
          leetcodeSolved(0),
          codechefSolved(0),
          hackerrankSolved(0),
          gfgSolved(0),
          codeforcesSolved(0),
          activeDays(0)
    {
    }

    bool hasSolved(const string& id) const
    {
        return find(
            solvedProblems.begin(),
            solvedProblems.end(),
            id
        ) != solvedProblems.end();
    }

    bool hasCompleted(const string& id) const
    {
        return find(
            completedAssignments.begin(),
            completedAssignments.end(),
            id
        ) != completedAssignments.end();
    }

    bool hasParticipated(const string& id) const
    {
        return find(
            participatedContests.begin(),
            participatedContests.end(),
            id
        ) != participatedContests.end();
    }

    void solve(const Problem& p)
    {
        if(hasSolved(p.getId()))
        {
            cout << "Already solved.\n";
            return;
        }

        solvedProblems.push_back(p.getId());

        problemsSolved++;

        score += p.getMarks();

        cout << "Problem solved! Score +"
             << p.getMarks()
             << "\n";
    }

    void complete(const Assignment& a)
    {
        if(hasCompleted(a.getId()))
        {
            cout << "Already completed.\n";
            return;
        }

        completedAssignments.push_back(a.getId());

        assignmentsCompleted++;

        score += a.getMarks();

        cout << "Assignment completed! Score +"
             << a.getMarks()
             << "\n";
    }

    void participateContest(
        const Contest& c,
        int obtainedScore,
        bool won
    )
    {
        if(hasParticipated(c.getId()))
        {
            cout << "Already participated in this contest.\n";
            return;
        }

        if(
            obtainedScore < 0 ||
            obtainedScore > c.getMaxScore()
        )
        {
            cout << "Score must be between 0 and "
                 << c.getMaxScore()
                 << ".\n";

            return;
        }

        participatedContests.push_back(c.getId());

        contestsParticipated++;

        contestScore += obtainedScore;

        score += obtainedScore;

        if(won)
            contestWins++;

        cout << "Contest result recorded.\n";

        cout << "Contest Score +"
             << obtainedScore
             << "\n";

        if(won)
            cout << "Congratulations! Contest win recorded.\n";
    }

    void updatePlatformProgress()
    {
        showHeading("UPDATE / VIEW MY CODING PROGRESS");

        // These two counts are automatically updated when the student
        // solves a problem or participates in a contest.
        cout << "\n--- CURRENT CODING ACTIVITY ---\n";
        cout << "Coding Problems Solved: "
             << problemsSolved << "\n";
        cout << "Coding Contests Attended: "
             << contestsParticipated << "\n";
        cout << "Contest Wins: "
             << contestWins << "\n";
        cout << "Contest Score: "
             << contestScore << "\n";

        cout << "\n--- CODING PLATFORM PROGRESS ---\n";
        cout << "Current LeetCode: " << leetcodeSolved << "\n";
        cout << "Current CodeChef: " << codechefSolved << "\n";
        cout << "Current HackerRank: " << hackerrankSolved << "\n";
        cout << "Current GeeksforGeeks: " << gfgSolved << "\n";
        cout << "Current Codeforces: " << codeforcesSolved << "\n";
        cout << "Current Total Platform Problems: "
             << getPlatformTotal() << "\n";
        cout << "Current Active Days: " << activeDays << "\n";

        cout << "\nEnter UPDATED number of problems solved on each platform.\n";

        int value;

        do
        {
            value=inputInt("LeetCode: ");
            if(value < 0) cout << "Enter 0 or a positive number.\n";
        }while(value < 0);
        leetcodeSolved=value;

        do
        {
            value=inputInt("CodeChef: ");
            if(value < 0) cout << "Enter 0 or a positive number.\n";
        }while(value < 0);
        codechefSolved=value;

        do
        {
            value=inputInt("HackerRank: ");
            if(value < 0) cout << "Enter 0 or a positive number.\n";
        }while(value < 0);
        hackerrankSolved=value;

        do
        {
            value=inputInt("GeeksforGeeks: ");
            if(value < 0) cout << "Enter 0 or a positive number.\n";
        }while(value < 0);
        gfgSolved=value;

        do
        {
            value=inputInt("Codeforces: ");
            if(value < 0) cout << "Enter 0 or a positive number.\n";
        }while(value < 0);
        codeforcesSolved=value;

        do
        {
            value=inputInt("Consistent active days: ");
            if(value < 0) cout << "Enter 0 or a positive number.\n";
        }while(value < 0);
        activeDays=value;

        cout << "\n========== UPDATED PROGRESS ==========" << "\n";
        cout << "Coding Problems Solved: " << problemsSolved << "\n";
        cout << "Coding Contests Attended: " << contestsParticipated << "\n";
        cout << "Contest Wins: " << contestWins << "\n";
        cout << "Contest Score: " << contestScore << "\n";
        cout << "LeetCode: " << leetcodeSolved << "\n";
        cout << "CodeChef: " << codechefSolved << "\n";
        cout << "HackerRank: " << hackerrankSolved << "\n";
        cout << "GeeksforGeeks: " << gfgSolved << "\n";
        cout << "Codeforces: " << codeforcesSolved << "\n";
        cout << "Total Platform Problems: " << getPlatformTotal() << "\n";
        cout << "Active Days: " << activeDays << "\n";
        cout << "======================================\n";
    }

    int getProblemsSolved() const
    {
        return problemsSolved;
    }

    int getAssignmentsCompleted() const
    {
        return assignmentsCompleted;
    }

    int getScore() const
    {
        return score;
    }

    int getContestsParticipated() const
    {
        return contestsParticipated;
    }

    int getContestWins() const
    {
        return contestWins;
    }

    int getContestScore() const
    {
        return contestScore;
    }

    int getPlatformTotal() const
    {
        return
            leetcodeSolved +
            codechefSolved +
            hackerrankSolved +
            gfgSolved +
            codeforcesSolved;
    }

    int getActiveDays() const
    {
        return activeDays;
    }

    void showPlatformStats() const
    {
        showHeading("CODING PLATFORM PROFILE");

        cout << "LeetCode Problems Solved: "
             << leetcodeSolved << "\n";

        cout << "CodeChef Problems Solved: "
             << codechefSolved << "\n";

        cout << "HackerRank Problems Solved: "
             << hackerrankSolved << "\n";

        cout << "GeeksforGeeks Problems Solved: "
             << gfgSolved << "\n";

        cout << "Codeforces Problems Solved: "
             << codeforcesSolved << "\n";

        cout << "Total External Platform Problems: "
             << getPlatformTotal()
             << "\n";

        cout << "Consistent Active Days: "
             << activeDays
             << "\n";
    }

    void show() const
    {
        display();

        cout << "\n--- Academic / Portal Progress ---\n";

        cout << "Portal Problems Solved: "
             << problemsSolved
             << "\n";

        cout << "Assignments Completed: "
             << assignmentsCompleted
             << "\n";

        cout << "Portal Total Score: "
             << score
             << "\n";

        cout << "\n--- Coding Contest Progress ---\n";

        cout << "Contests Participated: "
             << contestsParticipated
             << "\n";

        cout << "Contest Wins: "
             << contestWins
             << "\n";

        cout << "Contest Score: "
             << contestScore
             << "\n";

        cout << "\n--- External Coding Platform Progress ---\n";

        cout << "Total Platform Problems: "
             << getPlatformTotal()
             << "\n";

        cout << "Consistent Active Days: "
             << activeDays
             << "\n";

        cout << "\nSolved Problem IDs: ";

        if(solvedProblems.empty())
        {
            cout << "None";
        }
        else
        {
            for(
                vector<string>::const_iterator it=
                solvedProblems.begin();

                it!=solvedProblems.end();

                ++it
            )
            {
                cout << *it << " ";
            }
        }

        cout << "\nCompleted Assignment IDs: ";

        if(completedAssignments.empty())
        {
            cout << "None";
        }
        else
        {
            for(
                vector<string>::const_iterator it=
                completedAssignments.begin();

                it!=completedAssignments.end();

                ++it
            )
            {
                cout << *it << " ";
            }
        }

        cout << "\nParticipated Contest IDs: ";

        if(participatedContests.empty())
        {
            cout << "None";
        }
        else
        {
            for(
                vector<string>::const_iterator it=
                participatedContests.begin();

                it!=participatedContests.end();

                ++it
            )
            {
                cout << *it << " ";
            }
        }

        cout << "\n";
    }
};

// ============================================================
// TEACHER
// ============================================================

class Teacher : public User
{
    string subject;

public:

    Teacher(
        string i,
        string n,
        string e,
        string p,
        string ph,
        string s
    )
        : User(i,n,e,p,ph),
          subject(s)
    {
    }

    string getSubject() const
    {
        return subject;
    }

    void show() const
    {
        display();

        cout << "Subject: "
             << subject
             << "\n";
    }
};

// ============================================================
// ADMIN
// ============================================================

class Admin : public User
{
public:

    Admin(
        string i,
        string n,
        string e,
        string p,
        string ph
    )
        : User(i,n,e,p,ph)
    {
    }

    void show() const
    {
        display();
    }
};

// ============================================================
// GLOBAL STORAGE
// ============================================================

vector<Student> students;
vector<Teacher> teachers;
vector<Admin> admins;

vector<Problem> problems;
vector<Assignment> assignments;
vector<Contest> contests;

// ============================================================
// FIND USER FUNCTIONS
// ============================================================

Student* findStudent(const string& id)
{
    for(
        vector<Student>::iterator it=
        students.begin();

        it!=students.end();

        ++it
    )
    {
        if(it->getId()==id)
            return &(*it);
    }

    return NULL;
}

Teacher* findTeacher(const string& id)
{
    for(
        vector<Teacher>::iterator it=
        teachers.begin();

        it!=teachers.end();

        ++it
    )
    {
        if(it->getId()==id)
            return &(*it);
    }

    return NULL;
}

Admin* findAdmin(const string& id)
{
    for(
        vector<Admin>::iterator it=
        admins.begin();

        it!=admins.end();

        ++it
    )
    {
        if(it->getId()==id)
            return &(*it);
    }

    return NULL;
}

// ============================================================
// GLOBAL UNIQUE USER ID CHECK
// ============================================================

bool userIdExists(const string& id)
{
    if(findStudent(id) != NULL)
        return true;

    if(findTeacher(id) != NULL)
        return true;

    if(findAdmin(id) != NULL)
        return true;

    return false;
}

// ============================================================
// FIND ANY USER
// ============================================================

void viewUserById(const string& id)
{
    Student* s=findStudent(id);

    if(s != NULL)
    {
        showHeading("STUDENT FOUND");

        s->show();

        return;
    }

    Teacher* t=findTeacher(id);

    if(t != NULL)
    {
        showHeading("TEACHER FOUND");

        t->show();

        return;
    }

    Admin* a=findAdmin(id);

    if(a != NULL)
    {
        showHeading("ADMIN FOUND");

        a->show();

        return;
    }

    cout << "\nNo user exists with ID: "
         << id
         << "\n";
}

// ============================================================
// FIND PROBLEM
// ============================================================

Problem* findProblem(const string& id)
{
    for(
        vector<Problem>::iterator it=
        problems.begin();

        it!=problems.end();

        ++it
    )
    {
        if(it->getId()==id)
            return &(*it);
    }

    return NULL;
}

// ============================================================
// FIND ASSIGNMENT
// ============================================================

Assignment* findAssignment(const string& id)
{
    for(
        vector<Assignment>::iterator it=
        assignments.begin();

        it!=assignments.end();

        ++it
    )
    {
        if(it->getId()==id)
            return &(*it);
    }

    return NULL;
}

// ============================================================
// FIND CONTEST
// ============================================================

Contest* findContest(const string& id)
{
    for(
        vector<Contest>::iterator it=
        contests.begin();

        it!=contests.end();

        ++it
    )
    {
        if(it->getId()==id)
            return &(*it);
    }

    return NULL;
}

// ============================================================
// BUILT-IN DATA
// ============================================================

void seedData()
{
    students.push_back(
        Student(
            "S101",
            "Anu",
            "anu101@gmail.com",
            "Abc@1234",
            "9876543210"
        )
    );

    students.push_back(
        Student(
            "S102",
            "Ravi",
            "ravi102@gmail.com",
            "Rav@12345",
            "9123456780"
        )
    );

    students.push_back(
        Student(
            "S103",
            "Sneha",
            "sneha103@gmail.com",
            "Sne@1234",
            "9988776655"
        )
    );

    teachers.push_back(
        Teacher(
            "T101",
            "Priya",
            "priya101@gmail.com",
            "Pri@12345",
            "9000011111",
            "C++"
        )
    );

    teachers.push_back(
        Teacher(
            "T102",
            "Kiran",
            "kiran102@gmail.com",
            "Kir@12345",
            "9000022222",
            "Python"
        )
    );

    admins.push_back(
        Admin(
            "A101",
            "Main Admin",
            "admin101@gmail.com",
            "Adm@1234",
            "9000099999"
        )
    );

    problems.push_back(
        Problem(
            "P101",
            "Hello World",
            "Print Hello World",
            "Easy",
            5,
            "SYSTEM"
        )
    );

    problems.push_back(
        Problem(
            "P102",
            "Sum of Two Numbers",
            "Read two integers and print their sum",
            "Easy",
            10,
            "SYSTEM"
        )
    );

    problems.push_back(
        Problem(
            "P103",
            "Even or Odd",
            "Check whether a number is even or odd",
            "Easy",
            10,
            "SYSTEM"
        )
    );

    problems.push_back(
        Problem(
            "P104",
            "Largest of Three",
            "Find the largest among three numbers",
            "Easy",
            15,
            "SYSTEM"
        )
    );

    assignments.push_back(
        Assignment(
            "AS101",
            "C++ Basics",
            "30-09-2026",
            20,
            "T101"
        )
    );

    assignments.push_back(
        Assignment(
            "AS102",
            "Python Basics",
            "05-10-2026",
            25,
            "T102"
        )
    );

    contests.push_back(
        Contest(
            "C101",
            "Beginner Coding Challenge",
            "10-10-2026",
            100,
            "T101"
        )
    );

    contests.push_back(
        Contest(
            "C102",
            "Python Problem Solving Contest",
            "20-10-2026",
            100,
            "T102"
        )
    );
}

// ============================================================
// DISPLAY STUDENTS
// ============================================================

void viewStudents()
{
    showHeading("STUDENT INFORMATION");

    if(students.empty())
    {
        cout << "No students.\n";
        return;
    }

    for(
        vector<Student>::const_iterator it=
        students.begin();

        it!=students.end();

        ++it
    )
    {
        const Student& s=*it;

        cout << "\n--------------------------------\n";

        s.show();
    }
}

// ============================================================
// DISPLAY TEACHERS
// ============================================================

void viewTeachers()
{
    showHeading("TEACHER INFORMATION");

    if(teachers.empty())
    {
        cout << "No teachers.\n";
        return;
    }

    for(
        vector<Teacher>::const_iterator it=
        teachers.begin();

        it!=teachers.end();

        ++it
    )
    {
        const Teacher& t=*it;

        cout << "\n--------------------------------\n";

        t.show();
    }
}

// ============================================================
// DISPLAY PROBLEMS
// ============================================================

void viewProblems()
{
    showHeading("CODING PROBLEMS");

    if(problems.empty())
    {
        cout << "No problems available.\n";
        return;
    }

    for(
        vector<Problem>::const_iterator it=
        problems.begin();

        it!=problems.end();

        ++it
    )
    {
        it->display();
    }
}

// ============================================================
// DISPLAY ASSIGNMENTS
// ============================================================

void viewAssignments()
{
    showHeading("ASSIGNMENTS");

    if(assignments.empty())
    {
        cout << "No assignments available.\n";
        return;
    }

    for(
        vector<Assignment>::const_iterator it=
        assignments.begin();

        it!=assignments.end();

        ++it
    )
    {
        it->display();
    }
}

// ============================================================
// DISPLAY CONTESTS
// ============================================================

void viewContests()
{
    showHeading("CODING CONTESTS");

    if(contests.empty())
    {
        cout << "No contests available.\n";
        return;
    }

    for(
        vector<Contest>::const_iterator it=
        contests.begin();

        it!=contests.end();

        ++it
    )
    {
        it->display();
    }
}

// ============================================================
// ADD STUDENT - ADMIN ONLY
// ============================================================

void addStudent()
{
    string id;

    do
    {
        id=inputLine("Student ID (S123): ");

        if(!isValidId(id,'S'))
        {
            cout << "Invalid ID. Use S followed by numbers.\n";
            continue;
        }

        if(userIdExists(id))
        {
            cout << "\nThis ID already exists!\n";
            cout << "Showing existing user details...\n";

            viewUserById(id);

            cout << "\nA person can have only ONE unique ID.\n";
            cout << "Student was NOT added.\n";

            return;
        }

    }while(!isValidId(id,'S'));

    string name=inputLine("Name: ");

    string email=askEmail();

    string phone=askPhone();

    string pw=askPassword();

    students.push_back(
        Student(
            id,
            name,
            email,
            pw,
            phone
        )
    );

    cout << "\nStudent added successfully.\n";

    cout << "Student ID: "
         << id
         << "\n";
}

// ============================================================
// ADD TEACHER - ADMIN ONLY
// ============================================================

void addTeacher()
{
    string id;

    do
    {
        id=inputLine("Teacher ID (T123): ");

        if(!isValidId(id,'T'))
        {
            cout << "Invalid ID. Use T followed by numbers.\n";
            continue;
        }

        if(userIdExists(id))
        {
            cout << "\nThis ID already exists!\n";
            cout << "Showing existing user details...\n";

            viewUserById(id);

            cout << "\nA person can have only ONE unique ID.\n";
            cout << "Teacher was NOT added.\n";

            return;
        }

    }while(!isValidId(id,'T'));

    string name=inputLine("Name: ");

    string email=askEmail();

    string phone=askPhone();

    string pw=askPassword();

    string subject=inputLine("Subject: ");

    teachers.push_back(
        Teacher(
            id,
            name,
            email,
            pw,
            phone,
            subject
        )
    );

    cout << "\nTeacher added successfully.\n";

    cout << "Teacher ID: "
         << id
         << "\n";
}

// ============================================================
// ADD USER - ADMIN ONLY
// ============================================================

void addUser()
{
    int c;

    do
    {
        showHeading("ADD USER - ADMIN ONLY");

        cout << "1. Add Student\n";
        cout << "2. Add Teacher\n";
        cout << "3. Back\n";

        c=inputInt("Choice: ");

        switch(c)
        {
            case 1:
                addStudent();
                break;

            case 2:
                addTeacher();
                break;

            case 3:
                break;

            default:
                cout << "Invalid choice.\n";
        }

    }while(c!=3);
}

// ============================================================
// REMOVE USER - ADMIN
// ============================================================

void removeUser()
{
    string id=inputLine(
        "Enter Student/Teacher ID to remove: "
    );

    for(
        vector<Student>::iterator it=
        students.begin();

        it!=students.end();

        ++it
    )
    {
        if(it->getId()==id)
        {
            students.erase(it);

            cout << "Student removed successfully.\n";

            return;
        }
    }

    for(
        vector<Teacher>::iterator it=
        teachers.begin();

        it!=teachers.end();

        ++it
    )
    {
        if(it->getId()==id)
        {
            teachers.erase(it);

            cout << "Teacher removed successfully.\n";

            return;
        }
    }

    cout << "User not found.\n";
}

// ============================================================
// UPDATE USER - ADMIN
// ============================================================

void updateUser()
{
    string id=inputLine(
        "Enter Student/Teacher ID to update: "
    );

    Student* s=findStudent(id);

    if(s != NULL)
    {
        cout << "\nExisting Student:\n";

        s->show();

        cout << "\nEnter new details.\n";

        string n=inputLine("New Name: ");

        string e=askEmail();

        string p=askPhone();

        s->update(n,e,p);

        cout << "Student updated successfully.\n";

        return;
    }

    Teacher* t=findTeacher(id);

    if(t != NULL)
    {
        cout << "\nExisting Teacher:\n";

        t->show();

        cout << "\nEnter new details.\n";

        string n=inputLine("New Name: ");

        string e=askEmail();

        string p=askPhone();

        t->update(n,e,p);

        cout << "Teacher updated successfully.\n";

        return;
    }

    cout << "User not found.\n";
}

// ============================================================
// PROBLEM MANAGEMENT
// ============================================================

void addProblem(const string& adminId)
{
    string id;

    do
    {
        id=inputLine("Problem ID (P123): ");

        if(!isValidId(id,'P'))
        {
            cout << "Use P followed by numbers.\n";
        }

        if(findProblem(id)!=NULL)
        {
            cout << "Problem ID already exists.\n";

            return;
        }

    }while(!isValidId(id,'P'));

    string title=inputLine("Title: ");

    string description=inputLine("Description: ");

    string difficulty=inputLine("Difficulty: ");

    int marks=inputInt("Marks: ");

    problems.push_back(
        Problem(
            id,
            title,
            description,
            difficulty,
            marks,
            adminId
        )
    );

    cout << "Problem created by Admin "
         << adminId
         << ".\n";
}

// ============================================================
// UPDATE PROBLEM
// ============================================================

void updateProblem(const string& adminId)
{
    string id=inputLine(
        "Problem ID to update: "
    );

    Problem* p=findProblem(id);

    if(p==NULL)
    {
        cout << "Problem not found.\n";
        return;
    }

    if(p->getCreator()!=adminId)
    {
        cout <<
            "Access denied. Only the admin who created "
            "this problem can update it.\n";

        return;
    }

    string title=inputLine("New Title: ");

    string description=inputLine(
        "New Description: "
    );

    string difficulty=inputLine(
        "New Difficulty: "
    );

    int marks=inputInt("New Marks: ");

    p->update(
        title,
        description,
        difficulty,
        marks
    );

    cout << "Problem updated successfully.\n";
}

// ============================================================
// DELETE PROBLEM
// ============================================================

void deleteProblem(const string& adminId)
{
    string id=inputLine(
        "Problem ID to delete: "
    );

    for(
        vector<Problem>::iterator it=
        problems.begin();

        it!=problems.end();

        ++it
    )
    {
        if(it->getId()==id)
        {
            if(it->getCreator()!=adminId)
            {
                cout <<
                    "Access denied. Only the admin who created "
                    "this problem can delete it.\n";

                return;
            }

            problems.erase(it);

            cout << "Problem deleted.\n";

            return;
        }
    }

    cout << "Problem not found.\n";
}

// ============================================================
// ADD ASSIGNMENT
// ============================================================

void addAssignment(const string& teacherId)
{
    string id;

    do
    {
        id=inputLine(
            "Assignment ID (AS123): "
        );

        if(
            id.rfind("AS",0)!=0 ||
            id.size()<3 ||
            !isDigits(id.substr(2))
        )
        {
            cout << "Use AS followed by numbers.\n";
        }

        if(findAssignment(id)!=NULL)
        {
            cout << "Assignment ID already exists.\n";

            return;
        }

    }while(
        id.rfind("AS",0)!=0 ||
        id.size()<3 ||
        !isDigits(id.substr(2))
    );

    string title=inputLine(
        "Assignment Title: "
    );

    string deadline=inputLine(
        "Deadline: "
    );

    int marks=inputInt("Marks: ");

    assignments.push_back(
        Assignment(
            id,
            title,
            deadline,
            marks,
            teacherId
        )
    );

    cout <<
        "Assignment created and visible to students.\n";
}

// ============================================================
// ADD CONTEST
// ============================================================

void addContest(const string& teacherId)
{
    string id;

    do
    {
        id=inputLine(
            "Contest ID (C123): "
        );

        if(!isValidId(id,'C'))
        {
            cout << "Use C followed by numbers.\n";
        }

        if(findContest(id)!=NULL)
        {
            cout << "Contest ID already exists.\n";

            return;
        }

    }while(!isValidId(id,'C'));

    string title=inputLine(
        "Contest Title: "
    );

    string date=inputLine(
        "Contest Date: "
    );

    int maxScore=inputInt(
        "Maximum Score: "
    );

    contests.push_back(
        Contest(
            id,
            title,
            date,
            maxScore,
            teacherId
        )
    );

    cout << "Contest created successfully.\n";
}

// ============================================================
// CODING PLATFORMS
// ============================================================

void viewCodingPlatforms()
{
    showHeading("CODING PLATFORMS");

    cout << "1. LeetCode\n";
    cout << "2. CodeChef\n";
    cout << "3. HackerRank\n";
    cout << "4. GeeksforGeeks\n";
    cout << "5. Codeforces\n";

    cout <<
        "\nStudents can maintain their solved-problem "
        "count and consistency for these platforms.\n";
}

// ============================================================
// STUDENT DASHBOARD
// ============================================================

void studentDashboard(
    Student& s,
    bool adminPreview=false
)
{
    int c;

    do
    {
        showHeading(
            adminPreview
            ? "STUDENT MODULE (ADMIN VIEW)"
            : "STUDENT DASHBOARD"
        );

        cout << "Logged-in Student: "
             << s.getId()
             << " - "
             << s.getName()
             << "\n\n";

        cout << "1. View Coding Problems\n";
        cout << "2. Solve Problem\n";
        cout << "3. View Assignments\n";
        cout << "4. Complete Assignment\n";
        cout << "5. View Coding Contests\n";
        cout << "6. Participate / Record Contest Result\n";
        cout << "7. View My Progress\n";
        cout << "8. Update / View My Coding Progress\n";
        cout << "9. View Coding Platforms\n";
        cout << "10. Logout\n";

        c=inputInt("Choice: ");

        switch(c)
        {
            case 1:

                viewProblems();

                break;

            case 2:
            {
                viewProblems();

                string id=inputLine(
                    "Enter Problem ID to solve: "
                );

                Problem* p=findProblem(id);

                if(p!=NULL)
                    s.solve(*p);
                else
                    cout << "Problem not found.\n";

                break;
            }

            case 3:

                viewAssignments();

                break;

            case 4:
            {
                viewAssignments();

                string id=inputLine(
                    "Enter Assignment ID: "
                );

                Assignment* a=findAssignment(id);

                if(a!=NULL)
                    s.complete(*a);
                else
                    cout << "Assignment not found.\n";

                break;
            }

            case 5:

                viewContests();

                break;

            case 6:
            {
                viewContests();

                string id=inputLine(
                    "Enter Contest ID: "
                );

                Contest* contest=findContest(id);

                if(contest==NULL)
                {
                    cout << "Contest not found.\n";
                    break;
                }

                int obtained=inputInt(
                    "Enter your contest score: "
                );

                int won=inputInt(
                    "Did you win? (1=Yes, 0=No): "
                );

                s.participateContest(
                    *contest,
                    obtained,
                    won==1
                );

                break;
            }

            case 7:

                s.show();

                break;

            case 8:

                s.updatePlatformProgress();

                break;

            case 9:

                viewCodingPlatforms();

                break;

            case 10:

                cout << "Student logged out.\n";

                break;

            default:

                cout << "Invalid choice.\n";
        }

    }while(c!=10);
}

// ============================================================
// TEACHER DASHBOARD
// ============================================================

void teacherDashboard(
    Teacher& t,
    bool adminPreview=false
)
{
    int c;

    do
    {
        showHeading(
            adminPreview
            ? "TEACHER MODULE (ADMIN VIEW)"
            : "TEACHER DASHBOARD"
        );

        cout << "Logged-in Teacher: "
             << t.getId()
             << " - "
             << t.getName()
             << "\n\n";

        cout << "1. View Teacher Details\n";
        cout << "2. Create Assignment\n";
        cout << "3. View Assignments\n";
        cout << "4. Create Coding Contest\n";
        cout << "5. View Coding Contests\n";
        cout << "6. View Students Progress\n";
        cout << "7. View Coding Platforms\n";
        cout << "8. Logout\n";

        c=inputInt("Choice: ");

        switch(c)
        {
            case 1:

                t.show();

                break;

            case 2:

                addAssignment(t.getId());

                break;

            case 3:

                viewAssignments();

                break;

            case 4:

                addContest(t.getId());

                break;

            case 5:

                viewContests();

                break;

            case 6:
            {
                showHeading(
                    "STUDENT PROGRESS / COMPLETED ASSIGNMENTS"
                );

                if(students.empty())
                {
                    cout << "No students available.\n";
                    break;
                }

                for(
                    vector<Student>::const_iterator it=
                    students.begin();

                    it!=students.end();

                    ++it
                )
                {
                    cout <<
                        "\n----------------------------------------\n";

                    cout << "Student ID: "
                         << it->getId()
                         << "\n";

                    cout << "Student Name: "
                         << it->getName()
                         << "\n";

                    cout << "Problems Solved: "
                         << it->getProblemsSolved()
                         << "\n";

                    cout << "Assignments Completed: "
                         << it->getAssignmentsCompleted()
                         << "\n";

                    cout << "Total Score: "
                         << it->getScore()
                         << "\n";

                    cout << "Completed Assignment IDs: ";

                    /*
                       Student::show() contains the actual
                       completed assignment IDs.
                    */

                    it->show();
                }

                break;
            }

            case 7:

                viewCodingPlatforms();

                break;

            case 8:

                cout << "Teacher logged out.\n";

                break;

            default:

                cout << "Invalid choice.\n";
        }

    }while(c!=8);
}

// ============================================================
// ADMIN - MANAGE USERS
// ============================================================

void manageUsers()
{
    int c;

    do
    {
        showHeading("MANAGE USERS - ADMIN ONLY");

        cout << "1. View All Students\n";
        cout << "2. View All Teachers\n";
        cout << "3. Find User By ID\n";
        cout << "4. Add Student\n";
        cout << "5. Add Teacher\n";
        cout << "6. Remove User\n";
        cout << "7. Update User\n";
        cout << "8. Back\n";

        c=inputInt("Choice: ");

        switch(c)
        {
            case 1:

                viewStudents();

                break;

            case 2:

                viewTeachers();

                break;

            case 3:
            {
                string id=inputLine(
                    "Enter User ID: "
                );

                viewUserById(id);

                break;
            }

            case 4:

                addStudent();

                break;

            case 5:

                addTeacher();

                break;

            case 6:

                removeUser();

                break;

            case 7:

                updateUser();

                break;

            case 8:

                break;

            default:

                cout << "Invalid choice.\n";
        }

    }while(c!=8);
}

// ============================================================
// MANAGE PROBLEMS
// ============================================================

void manageProblems(
    const string& adminId
)
{
    int c;

    do
    {
        showHeading("MANAGE PROBLEMS");

        cout << "1. Add Problem\n";
        cout << "2. View Problems\n";
        cout << "3. Update My Problem\n";
        cout << "4. Delete My Problem\n";
        cout << "5. Back\n";

        c=inputInt("Choice: ");

        switch(c)
        {
            case 1:

                addProblem(adminId);

                break;

            case 2:

                viewProblems();

                break;

            case 3:

                updateProblem(adminId);

                break;

            case 4:

                deleteProblem(adminId);

                break;

            case 5:

                break;

            default:

                cout << "Invalid choice.\n";
        }

    }while(c!=5);
}

// ============================================================
// ADMIN DASHBOARD
// ============================================================

void adminDashboard(Admin& a)
{
    int c;

    do
    {
        showHeading("ADMIN DASHBOARD");

        cout << "Logged-in Admin: "
             << a.getId()
             << " - "
             << a.getName()
             << "\n\n";

        cout << "1. View Admin Details\n";
        cout << "2. Manage Users\n";
        cout << "3. Manage Problems\n";
        cout << "4. View Assignments\n";
        cout << "5. View Coding Contests\n";
        cout << "6. Open Student Module By ID\n";
        cout << "7. Open Teacher Module By ID\n";
        cout << "8. Find User By ID\n";
        cout << "9. Student Coding Progress Control\n";
        cout << "10. Logout\n";

        c=inputInt("Choice: ");

        switch(c)
        {
            case 1:

                a.show();

                break;

            case 2:

                manageUsers();

                break;

            case 3:

                manageProblems(a.getId());

                break;

            case 4:

                viewAssignments();

                break;

            case 5:

                viewContests();

                break;

            case 6:
            {
                string id=inputLine(
                    "Enter Student ID: "
                );

                Student* s=findStudent(id);

                if(s!=NULL)
                {
                    studentDashboard(
                        *s,
                        true
                    );
                }
                else
                {
                    cout << "Student ID not found.\n";
                }

                break;
            }

            case 7:
            {
                string id=inputLine(
                    "Enter Teacher ID: "
                );

                Teacher* t=findTeacher(id);

                if(t!=NULL)
                {
                    teacherDashboard(
                        *t,
                        true
                    );
                }
                else
                {
                    cout << "Teacher ID not found.\n";
                }

                break;
            }

            case 8:
            {
                string id=inputLine(
                    "Enter User ID: "
                );

                viewUserById(id);

                break;
            }

            case 9:
            {
                string id=inputLine("Enter Student ID for Progress: ");
                Student* s=findStudent(id);

                if(s!=NULL)
                {
                    showHeading("ADMIN - STUDENT CODING PROGRESS");
                    cout << "Student: " << s->getId()
                         << " - " << s->getName() << "\n";
                    s->show();
                }
                else
                {
                    cout << "Student ID not found.\n";
                }

                break;
            }

            case 10:

                cout << "Admin logged out.\n";

                break;

            default:

                cout << "Invalid choice.\n";
        }

    }while(c!=10);
}

// ============================================================
// ADMIN MENU
// ============================================================

void adminMenu()
{
    int c;

    do
    {
        showHeading("ADMIN");

        cout << "1. Login\n";
        cout << "2. Registration\n";
        cout << "3. Back\n";

        c=inputInt("Choice: ");

        if(c==1)
        {
            string id=inputLine(
                "Admin ID (A123): "
            );

            string p=inputLine(
                "Password: "
            );

            Admin* a=findAdmin(id);

            if(a!=NULL && a->checkPassword(p))
            {
                cout << "\nLogin successful.\n";

                cout << "Welcome, "
                     << a->getName()
                     << "!\n";

                adminDashboard(*a);
            }
            else
            {
                cout <<
                    "Invalid Admin ID or password.\n";
            }
        }

        else if(c==2)
        {
            string id;

            do
            {
                id=inputLine(
                    "Admin ID (A123): "
                );

                if(!isValidId(id,'A'))
                {
                    cout <<
                        "Use A followed by numbers.\n";

                    continue;
                }

                if(userIdExists(id))
                {
                    cout <<
                        "\nThis ID already exists!\n";

                    viewUserById(id);

                    cout <<
                        "\nAdmin was NOT registered.\n";

                    id="";

                    break;
                }

            }while(!isValidId(id,'A'));

            if(id.empty())
                continue;

            string n=inputLine("Name: ");

            string e=askEmail();

            string ph=askPhone();

            string p=askPassword();

            admins.push_back(
                Admin(
                    id,
                    n,
                    e,
                    p,
                    ph
                )
            );

            cout <<
                "Admin registered successfully.\n";
        }

    }while(c!=3);
}

// ============================================================
// TEACHER MENU
// ONLY LOGIN - NO REGISTRATION
// ADMIN CREATES TEACHERS
// ============================================================

void teacherMenu()
{
    int c;

    do
    {
        showHeading("TEACHER");

        cout << "1. Login\n";
        cout << "2. Back\n";

        c=inputInt("Choice: ");

        if(c==1)
        {
            string id=inputLine(
                "Teacher ID (T123): "
            );

            string p=inputLine(
                "Password: "
            );

            Teacher* t=findTeacher(id);

            if(t!=NULL && t->checkPassword(p))
            {
                cout << "\nLogin successful.\n";

                cout << "Teacher Details:\n";

                t->show();

                teacherDashboard(*t);
            }
            else
            {
                cout <<
                    "\nTeacher ID or password is invalid.\n";

                cout <<
                    "If you are a new teacher, please contact Admin.\n";
            }
        }

    }while(c!=2);
}

// ============================================================
// STUDENT MENU
// ONLY LOGIN - NO REGISTRATION
// ADMIN CREATES STUDENTS
// ============================================================

void studentMenu()
{
    int c;

    do
    {
        showHeading("STUDENT");

        cout << "1. Login\n";
        cout << "2. Back\n";

        c=inputInt("Choice: ");

        if(c==1)
        {
            string id=inputLine(
                "Student ID (S123): "
            );

            string p=inputLine(
                "Password: "
            );

            Student* s=findStudent(id);

            if(s!=NULL && s->checkPassword(p))
            {
                cout << "\nLogin successful.\n";

                cout << "Student Details:\n";

                s->show();

                studentDashboard(*s);
            }
            else
            {
                cout <<
                    "\nStudent ID or password is invalid.\n";

                cout <<
                    "If you are a new student, please contact Admin.\n";
            }
        }

    }while(c!=2);
}

// ============================================================
// MAIN MENU
// ============================================================

int main()
{
    seedData();

    int c;

    do
    {
        showHeading(
            "CODING PLATFORM MANAGEMENT SYSTEM"
        );

        cout << "1. Admin\n";
        cout << "2. Teacher\n";
        cout << "3. Student\n";
        cout << "4. Exit\n";

        c=inputInt("Choice: ");

        switch(c)
        {
            case 1:

                adminMenu();

                break;

            case 2:

                teacherMenu();

                break;

            case 3:

                studentMenu();

                break;

            case 4:

                cout <<
                    "Thank you for using the system!\n";

                break;

            default:

                cout << "Invalid choice.\n";
        }

    }while(c!=4);

    return 0;
}
