// //������ � ����
//#include <iostream>
//#include <fstream>
//#include <windows.h>
//using namespace std;
//// ��������� ������ ������� �������
//struct Person
//{
//	char name[25];  //���
//	int height;		//����
//	int weight;		//���
//} A;
//void main() {
//	setlocale(LC_ALL, "rus");
//
//	const char* nameR = "D:\REQUEST.bin";
//	//���� ��� �������� ��������
//	const char* nameA = "D:\ANSWER.bin";
//	//���� ��� ������� �������
//	ofstream f_REQ;
//	ifstream f_ANS;
//	long pred_size;
//	int answer;
//	while (true)
//	{
//		// �������� ������ �� ������� �������
//		cout << "������� ������: ������� ���� ���" << endl;
//		cin >> A.name >> A.height >> A.weight;
//		cout << A.name<<" " << A.height<<" " << A.weight;
//		f_REQ.open(nameR, ios::app | ios::binary);
//		//�������� ����� REQUEST 
//		f_REQ.write((char*)&A, sizeof(A));
//		//������ ������� � ���� REQUEST
//		f_REQ.close();
//
//		// �������� ����� �� �������?
//		f_ANS.open(nameA, ios::binary);
//		//�������� ����� ANSWER
//		f_ANS.seekg(0, ios::end);
//		//������� � ����� ����� ANSWER
//		pred_size = f_ANS.tellg();
//		while (pred_size >= f_ANS.tellg())
//		{
//			Sleep(100);
//			// ���� � ��������� � ����� ����� ANSWER
//			f_ANS.seekg(0, ios::end);
//		}
//		// ��������� ������ �� �������	
//		f_ANS.seekg(pred_size, ios::beg);
//		// �� ������ ������ ������
//		f_ANS.read((char*)&answer, sizeof(answer));//���������� ������
//		f_ANS.close();
//
//		// ����������� ������
//		switch (answer) {
//		case 0: { cout << "\n���������� ����\n"; break; }
//		case 1: { cout << "\n����� ����\n"; break; }
//		case 2: { cout << "\n������� ����\n"; break; }
//		}
//	} //while
//}

//�������: ������� ����, ������� ����� ��������� ������� �������� � 4 ������. 
//(��������, 5 5 4 4) � ��������, ����� �������� ��������� � ����� ���.
//(�������, ���������� ���������) ��� ������� � �������� ��������������


//client
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>

using namespace std;

const string REQUEST_FILE = "D:\\REQUEST.bin";
const string ANSWER_FILE = "D:\\ANSWER.bin";
const int NAME_SIZE = 25;

struct Student {
    char lastName[NAME_SIZE];
    int grades[4];
};

struct ScholarshipInfo {
    int status;  // 0 - ��� ���������, 1 - �������, 2 - ����������
    int debtCount;
};


int main() {
    setlocale(LC_ALL, "ru");

    while (true) {
        Student student;

        cout << "������� ������� �������� (�� " << NAME_SIZE<< " ��������): ";
        cin >> student.lastName;

        cout << "������� 4 ������ �������� (����������� ���������): ";
        for (int i = 0; i < 4; ++i) {
            cin >> student.grades[i];
        }

        ofstream requestFile(REQUEST_FILE, ios::binary | ios::app);
        requestFile.write((char*)&student, sizeof(Student));
        requestFile.close();

        cout << endl;
        cout << "������ ���������. �������� ������..." << endl;
        cout << endl;


        ifstream answerFile(ANSWER_FILE, ios::binary);
        ScholarshipInfo scholarshipInfo;

        answerFile.seekg(0, ios::end);

        long pred_size;

        pred_size = answerFile.tellg();

        while (pred_size >= answerFile.tellg()) {
            Sleep(100);
            answerFile.seekg(0, ios::end);
        }

        answerFile.seekg(pred_size, ios::beg);

        answerFile.read((char*)&scholarshipInfo, sizeof(ScholarshipInfo));
        answerFile.close();

        cout << "����� �������:" << endl;
        if (scholarshipInfo.status == 0) {
            cout << "������� " << student.lastName << " �� �������� ���������. ���������� ��������������: " << scholarshipInfo.debtCount << endl;
            cout << endl;
        }
        else if (scholarshipInfo.status == 1) {
            cout << "������� " << student.lastName << " �������� ������� ���������." << endl;
            cout << endl;
        }
        else {
            cout << "������� " << student.lastName << " �������� ���������� ���������!" << endl;
            cout<< endl;
        }

    }

    return 0;
}