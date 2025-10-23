// //������ � ����
//#include <iostream>
//#include <fstream>
//#include <windows.h>
//using namespace std;
//struct Person
//{
//	char name[25];	 //��� 
//	int height;		//����
//	int weight;		//���
//}B;
//int answer;
//long size_pred;
//int main() {
//	ifstream fR;
//	ofstream fA;
//	setlocale(LC_ALL, "rus");
//	const char* nameR = "D:\REQUEST.bin";
//	//���� �������� ��������
//	const char* nameA = "D:\ANSWER.bin";
//	//���� ������� �������
//	cout << "server is working" << endl;
//	// ��������� ���������
//	fR.open(nameR, ios::binary);
//	//�������� ����� REQUEST
//	fR.seekg(0, ios::end);
//	size_pred = fR.tellg();
//	//��������� ������� ������� � ����� REQUEST
//	fR.close();
//
//	// ������ ������ �������
//	while (true)
//	{
//		fR.open(nameR, ios::binary);
//		//�������� ����� REQUEST
//		fR.seekg(0, ios::end);
//		//������� � ����� ����� REQUEST
//		// ���� ����� ������� �� ��������? 
//		while (size_pred >= fR.tellg())
//		{
//			Sleep(100); fR.seekg(0, ios::end);
//		}
//		// ������� ����� ������ 
//		fR.seekg(size_pred, ios::beg);
//		//������� � ������ ����������� �������
//		fR.read((char*)&B, sizeof(B));
//		//���������� ������ �������
//		size_pred = fR.tellg();
//		// �� ����� ������������ ������
//		fR.close();
//		// ����������� ������� �����	
//		double IMT = B.weight / (0.01 * B.height) / (0.01 * B.height);
//		if (18.5 <= IMT && IMT < 25) answer = 1;
//		if (18.5 > IMT) answer = 0;
//		if (IMT >= 25)answer = 2;
//
//		// �������� ������ �������
//		fA.open(nameA, ios::binary | ios::app);
//		//�������� ����� ANSWER
//		fA.write((char*)&answer, sizeof(answer));
//		//������ ������ �������
//		fA.close();
//	}// while
//}


// server
#include <iostream>
#include <fstream>
#include <string>
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
    int status;
    int debtCount;
};

ScholarshipInfo analyzeGrades(const Student& student) {
    ScholarshipInfo info;
    info.status = 1;
    info.debtCount = 0;

    bool allExcellent = true;

    for (int i = 0; i < 4; ++i) {
        if (student.grades[i] < 4) {
            info.status = 0;
            info.debtCount++;
            allExcellent = false;
        }
        else if (student.grades[i] < 5)
        {
            allExcellent = false;
        }

    }

    if (allExcellent) {
        info.status = 2;
    }

    return info;
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "������ �������..." << endl;
    cout << endl;

    long lastFileSize = 0;

    while (true) {
        ifstream requestFile(REQUEST_FILE, ios::binary);
        requestFile.seekg(0, ios::end);
        long currentFileSize = requestFile.tellg();
        requestFile.close();

        if (currentFileSize > lastFileSize) {
            // ��������� ����� ������
            requestFile.open(REQUEST_FILE, ios::binary);
            requestFile.seekg(lastFileSize, ios::beg);

            Student student;
            while (requestFile.read((char*)&student, sizeof(Student))) {
                ScholarshipInfo scholarshipInfo = analyzeGrades(student);

                ofstream answerFile(ANSWER_FILE, ios::binary | ios::app);
                answerFile.write((char*)&scholarshipInfo, sizeof(ScholarshipInfo));
                answerFile.close();

                cout << "��������� ������ ��� ��������: " << student.lastName << endl;
                cout << "�������������: " << scholarshipInfo.debtCount << endl;
                cout << "������: " << scholarshipInfo.status << endl;
                cout << endl;
            }

            lastFileSize = currentFileSize;
            requestFile.close();
        }
        else {
            Sleep(100);
        }
    }

    return 0;
}