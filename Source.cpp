#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
using namespace std;
struct user {
	int Id;
	string Name, Password, Email;
};
struct question
{
	int to, from, idq;
	string ques;
	bool anon;
};
struct answer {
	int ID_user, ID_quse;
	string ans;
};
class Uploading {
protected:
	vector<user>User;
	vector<question>Ques;
	vector<answer>Ans;
	string s;
	int cont;
public:
	void Uploade_Users() {
		User.clear();
		ifstream all_users("users.txt", ios::in);
		cont = 0;
		s;
		user U;
		while (getline(all_users, s)) {
			if (cont % 4 == 0) {
				U.Email = s;
			}
			else if (cont % 4 == 1) {
				U.Name = s;
			}
			else if (cont % 4 == 2) {
				U.Password = s;
			}
			else {
				U.Id = stoi(s);
				User.push_back(U);
			}
			cont++;
		}
		all_users.close();
	}
	void Uploade_Questions() {
		Ques.clear();
		ifstream Questions("Question.txt", ios::in);
		cont = 0;
		s = "";
		question q;
		while (getline(Questions, s)) {
			if (cont % 5 == 0) {
				q.to = stoi(s);
			}
			else if (cont % 5 == 1) {
				if (stoi(s) == 1) {
					q.anon = true;
				}
				else {
					q.anon = false;
				}
			}
			else if (cont % 5 == 2) {
				q.ques = s;
			}
			else if (cont % 5 == 3) {
				q.from = stoi(s);
			}
			else {
				q.idq = stoi(s);
				Ques.push_back(q);
			}
			cont++;
		}
		Questions.close();
	}
	void Uploade_Anserwers() {
		Ans.clear();
		ifstream Answers("answers.txt", ios::in);
		cont = 0;
		s = "";
		answer a;
		while (getline(Answers, s)) {
			if (cont % 3 == 0) {
				a.ID_user = stoi(s);
			}
			else if (cont % 3 == 1) {
				a.ID_quse = stoi(s);
			}
			else {
				a.ans = s;
				Ans.push_back(a);
			}
			cont++;
		}
		Answers.close();
	}
};
class Account :public Uploading {
protected:
	user U;
	question q;
	answer a;
	bool found = 1, b = 1, empty;
public:
	Account() {};
	void sign_up() {
		Uploade_Users();
		Uploade_Questions();
		Uploade_Anserwers();
		ofstream enter_Ueser("users.txt", ios::app);
		cout << "Enter your Email\n";
		cin >> U.Email;
		bool x = 0;
		int indx = 0;
		found = 1;
		while (found) {
			for (int i = 0;i < U.Email.size();i++) {
				if (U.Email[i] == '@' && i < U.Email.size() - 5 && i>0) {
					x = 1;
					indx = i;
					break;
				}
			}
			bool yes = 0;
			if (U.Email[U.Email.size() - 4] == '.' && U.Email[U.Email.size() - 3] == 'c'
				&& U.Email[U.Email.size() - 2] == 'o' && U.Email[U.Email.size() - 1] == 'm' && x && indx) {
				yes = 1;
			}
			if (!yes) {
				cout << "\nEnter Vaild Email\n";
				cin >> U.Email;
			}
			else {
				enter_Ueser << U.Email << '\n';
				found = 0;
			}
		}
		cout << "Enter your username\n";
		cin >> U.Name;
		found = 1;
		b = 1;
		while (found) {
			b = 1;
			for (int i = 0;i < User.size();i++) {
				if (U.Name == User[i].Name) {
					cout << "This username is taken Enter another one\n";
					cin >> U.Name;
					b = 0;
				}

			}
			if (b) {
				found = 0;
			}
		}
		enter_Ueser << U.Name << "\n";
		cout << "Enter password\n";
		cin >> U.Password;
		enter_Ueser << U.Password << "\n";
		cout << "Enter your ID\n";
		cin >> U.Id;
		found = 1;
		b = 1;
		while (found) {
			b = 1;
			for (int i = 0;i < User.size();i++) {
				if (U.Id == User[i].Id) {
					cout << "This ID is taken Enter another one\n";
					cin >> U.Id;
					b = 0;
				}

			}
			if (b) {
				found = 0;
			}
		}
		enter_Ueser << U.Id << '\n';
		enter_Ueser.close();
		User.push_back(U);
	}
	void login() {
		Uploade_Users();
		Uploade_Questions();
		Uploade_Anserwers();
		string Pass;
		cout << "Enter your username\n";
		cin >> U.Name;
		found = 1;
		while (found)
		{
			for (int i = 0;i < User.size();i++) {
				if (U.Name == User[i].Name) {
					found = 0;
					Pass = User[i].Password;
					U.Id = User[i].Id;
				}
			}
			if (found) {
				cout << "Not found \nEnter the correct name\n";
				cin >> U.Name;
			}
		}
		found = 1;
		cout << "Enter your password\n";
		cin >> U.Password;
		while (found) {
			if (Pass != U.Password) {
				cout << "Isn't correct\ntry again\n";
				cin >> U.Password;
			}
			else {
				found = 0;

			}
		}


	}
	void Userss() {
		Uploade_Users();
		ifstream show("users.txt", ios::in);
		string s;
		int cont = 0;
		for (int i = 0;i < User.size();i++) {
			cout << "Name : " << User[i].Name << " ID : " << User[i].Id << '\n';
		}

	}
	bool questionss() {
		Uploade_Users();
		Uploade_Questions();
		Uploade_Anserwers();
		empty = 1;
		int x = 1;
		for (int i = 0;i < Ques.size();i++) {
			bool f = 1;
			if (Ques[i].to == U.Id) {
				cout << "ID ( " << Ques[i].idq << " ) " << Ques[i].ques;
				for (int j = 0;j < User.size();j++) {
					if (User[j].Id == Ques[i].from) {
						if (Ques[i].anon == 0) {
							cout << " From ( " << User[j].Name << " )\n";
						}
						else {
							cout << " From ( anonymous ) \n";
						}
					}
				}
				for (int j = 0;j < Ans.size();j++) {
					if (Ans[j].ID_user == U.Id && Ans[j].ID_quse == Ques[i].idq) {
						f = 0;
						cout << " answer : " << Ans[j].ans << '\n';
					}
				}
				if (f) {
					cout << "  Not answered yet\n";
				}
				empty = 0;
			}

		}
		if (empty) {
			cout << "There are no questions\n";
			return 0;
		}
		else {
			return 1;
		}
	}
	bool questions_From_me() {
		Uploade_Users();
		Uploade_Questions();
		Uploade_Anserwers();
		bool x = 1;
		for (int i = 0;i < Ques.size();i++) {
			if (Ques[i].from == U.Id) {
				x = 0;
				cout << "ID ( " << Ques[i].idq << " ) " << Ques[i].ques << " To ";
				for (int j = 0;j < User.size();j++) {
					if (Ques[i].to == User[j].Id) {
						cout << "( " << User[j].Name << " )\n";
						break;
					}
				}
				found = 1;
				for (int j = 0;j < Ans.size();j++) {
					if (Ques[i].idq == Ans[j].ID_quse && Ans[j].ID_user == Ques[i].to) {
						found = 0;
						cout << " answer : " << Ans[j].ans << '\n';
					}
				}
				if (found) {
					cout << "  Not answered yet\n";
				}
			}
		}
		if (x) {
			cout << "NO Questions\n";
			return 0;
		}
		else {
			return 1;
		}
	}
	void ask() {
		found = 1;
		b = 1;
		ofstream Q("Question.txt", ios::app);
		cout << "Enter ID of the user you want to ask\n";
		cin >> q.to;
		while (found || b) {
			found = 1;b = 1;
			for (int i = 0;i < User.size();i++) {
				if (q.to == User[i].Id) {
					found = 0;
					break;
				}
			}
			if (found) {
				cout << "Not found  \nEnter the correct ID\n";
				cin >> q.to;
			}
			if (q.to == U.Id) {
				cout << "Can't ask yourself \nEnter ID user\n";
				cin >> q.to;
			}
			else {
				b = 0;
			}
		}
		Q << q.to << '\n';
		cout << "Do you want anonymous Enter (1 or 0)\n";
		cin >> q.anon;
		Q << q.anon << '\n';
		cout << "Enter your question\n";
		cin.ignore();
		getline(cin, q.ques);
		Q << q.ques << '\n';
		q.from = U.Id;
		Q << q.from << '\n';
		if (Ques.empty()) {
			q.idq = 1;
		}
		else {
			q.idq = Ques[Ques.size() - 1].idq + 1;
		}
		Q << q.idq << "\n";
		Ques.push_back(q);
		Q.close();
		Uploade_Questions();
	}
	void Respod() {
		ofstream file_Ans("answers.txt", ios::app);
		cout << "Enter ID questoin to respod\n";
		cin >> a.ID_quse;
		found = 1;
		while (found) {
			for (int i = 0;i < Ques.size();i++) {
				if (Ques[i].to == U.Id && Ques[i].idq == a.ID_quse) {
					found = 0;
					a.ID_user = U.Id;

				}
			}
			if (found) {
				cout << "This ID question not found, enter ID questoin\n";
				cin >> a.ID_quse;
			}
		}
		found = 1;
		int indx;
		for (int i = 0;i < Ans.size();i++) {
			if (a.ID_quse == Ans[i].ID_quse) {
				cout << "Answer will be updated\n";
				cout << "Enter your answer\n";
				cin.ignore();
				getline(cin, Ans[i].ans);
				found = 0;
				break;
			}
		}
		if (found) {
			cout << "Enter your answer\n";
			cin.ignore();
			getline(cin, a.ans);
			Ans.push_back(a);
			file_Ans << a.ID_user << '\n' << a.ID_quse << '\n' << a.ans << '\n';
			file_Ans.close();
		}
		else {
			ofstream UpdateAnswer("answers.txt", ios::trunc);
			for (int i = 0;i < Ans.size();i++) {
				UpdateAnswer << Ans[i].ID_user << "\n" << Ans[i].ID_quse << '\n' << Ans[i].ans << '\n';
			}
			UpdateAnswer.close();
		}
		Uploade_Anserwers();
	}
	void Delete() {
		Uploade_Anserwers();
		Uploade_Questions();
		int id, idUser;
		cout << "Enter ID question to delete\n";
		cin >> id;
		found = 1;
		while (found) {
			for (int i = 0;i < Ques.size();i++) {
				if (Ques[i].idq == id && Ques[i].from == U.Id) {
					found = 0;

				}
			}
			if (found) {
				cout << "This ID question not found, Enter ID questoin\n";
				cin >> id;
			}
		}
		found = 1;
		if (Ques.size() == 1) {
			Ques.clear();
			Ans.clear();
		}
		else {
			for (int i = 0;i < Ques.size() - 1;i++) {
				if (id == Ques[i].idq && U.Id == Ques[i].from) {
					idUser = Ques[i].to;
					found = 0;
				}
				if (found == 0) {
					Ques[i].from = Ques[i + 1].from;
					Ques[i].idq = Ques[i + 1].idq;
					Ques[i].ques = Ques[i + 1].ques;
					Ques[i].to = Ques[i + 1].to;
					Ques[i].anon = Ques[i + 1].anon;
				}
			}
			Ques.pop_back();
			found = 1;
			for (int i = 0;i < Ans.size();i++) {
				if (id == Ans[i].ID_quse && Ans[i].ID_user == idUser) {
					found = 0;
				}
			}
			if (found == 0) {
				found = 1;
				for (int i = 0;i < Ans.size() - 1;i++) {
					if (id == Ans[i].ID_quse && Ans[i].ID_user == U.Id) {
						found = 0;
					}
					if (found == 0) {
						Ans[i].ans = Ans[i + 1].ans;
						Ans[i].ID_quse = Ans[i + 1].ID_quse;
						Ans[i].ID_user = Ans[i + 1].ID_user;
					}

				}
				Ans.pop_back();
			}
		}
		ofstream Q("Question.txt", ios::trunc);
		ofstream An("answers.txt", ios::trunc);
		for (int i = 0;i < Ques.size();i++) {
			Q << Ques[i].to << '\n' << Ques[i].anon << '\n' << Ques[i].ques << '\n' << Ques[i].from << '\n' << Ques[i].idq << '\n';
		}
		Q.close();
		for (int i = 0;i < Ans.size();i++) {
			An << Ans[i].ID_user << '\n' << Ans[i].ID_quse << '\n' << Ans[i].ans << '\n';
		}
		An.close();
		cout << "\n  Done\n";

	}
	~Account() {}
};
int main() {
	Account A;
	cout << "Enter 1 to sign up\nEnter 2 to sign in\n";
	int n;
	cin >> n;
	if (n == 1) {
		A.sign_up();
	}
	else if (n == 2) {
		A.login();
	}
	else {
		return 0;
	}
	int cnt = 0;
	while (1) {
		cout << "\nEnter 1 to See Users\nEnter 2 to See questions forwarded to you\n";
		cout << "Enter 3 to See qusestions you asked\nEnter 4 to Ask anyone\n";
		cout << "Enter 5 to Respond questions\nEnter 6 to Delete question\nEnter 7 to Log out\n";
		cout << "Enter 8 to End the program\n";
		cin >> cnt;
		if (cnt == 1) {
			system("cls");
			A.Userss();
		}
		else if (cnt == 2) {
			system("cls");
			A.questionss();
		}
		else if (cnt == 4) {
			system("cls");
			A.Userss();
			A.ask();
		}
		else if (cnt == 3) {
			system("cls");
			A.questions_From_me();
		}
		else if (cnt == 5) {
			system("cls");
			if (A.questionss()) {
				A.Respod();
			}
		}
		else if (cnt == 6) {
			system("cls");
			if (A.questions_From_me()) {
				A.Delete();
			}
		}
		else if (cnt == 7) {
			system("cls");
			cout << "Enter 1 to sign up\nEnter 2 to sign in\n";
			cin >>
				cnt;
			if (cnt == 1) {
				A.sign_up();
			}
			else if (cnt == 2) {
				A.login();
			}
		}
		else {
			break;
		}
	}
	return 0;
}