#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstdio>
using namespace std;

const string file = "telefoni.txt";
const string binFile = "database.dat";

struct Phone {
	string brand, model, color = "";
	int storage = 0;
	bool dualSim = false;
	int countFromThisPhone = 0;
	double screenSize = 0;
	double price = 0;
};

struct PhonesList {
	Phone phones[100];
	int size = 0;

	Phone add(Phone phone) {
		phones[size] = phone;
		size++;
		return phone;
	}

};

void phoneFromInput(PhonesList& list);
void sorting(PhonesList& list);
void phonesFromInput(PhonesList& list);

// Functions
void menu(Phone phones[100], PhonesList& list);
void addPhoneMenu(Phone phones[100], PhonesList& list);
void showPhones(PhonesList& list);

void searchAndPrintMenu(Phone phones[100], PhonesList list);
void smallStorage(PhonesList list);
void supportDualSIM(PhonesList list);

void editPhone(PhonesList& list);
void fetchPhonesMenu(PhonesList& list);
void fetchPhonesByBrand(PhonesList& list);
void fetchPhonesByScreenSize(PhonesList& list);

void sellPhone(PhonesList& list);
void printOnTextFile(PhonesList& list);
void readFromTextFile(PhonesList& list);
void controllFilesMenu(Phone phones[100], PhonesList& list);

void saveBinaryFile(PhonesList& list);
void loadBinaryFile(PhonesList& list);
int countOfValidPhones(PhonesList& list);


// Main Function
int main() {
	int count;
	Phone phones[100] = {};
	PhonesList list = {};
	loadBinaryFile(list);
	count = countOfValidPhones(list);
	cout << "" << setw(42) << setfill('-') << "\n" << "|        Добре дошли в програмата       |\n|    за продажба на мобилни телефони    |\n" <<
		setw(41) << setfill('-') << "" << endl;
	menu(phones, list);
}


// Проверява колко телефона са добавени от файл
int countOfValidPhones(PhonesList& list)
{
	for (int i = 0; i < 100; i++)
	{
		if (list.phones[i].brand.size() != 0)
		{
			list.size++;
		}
	}

	return list.size;
}


// Главно меню
void menu(Phone phones[100], PhonesList& list)
{
	int menuNumber = 0;
	char chooice = 'n';
	do {
		cout << endl;
		cout << "1) Добавяне на нови мобилни телефони" << endl; // 
		cout << "2) Извеждане на екрана" << endl; // 
		cout << "3) Търсене и извеждане на екрана" << endl; //
		cout << "4) Подреждане на основния масив с мобилни телефони, без да се извежда на екрана" << endl;
		cout << "5) Управление на файл" << endl;

		// Допълнително първо (+ базова задача)
		cout << "6) Одит на мобилни телефони в наличност в под меню" << endl;
		cout << "7) Корекция на данни за даден телефон" << endl;
		cout << "8) Продажба на мобилни телефони" << endl;
		cout << "9) Изход от програмата" << endl;
		cout << endl;
		cout << "Моля изберете опция от менюто: ";

		while (!(cin >> menuNumber)) {
			cout << "Моля изберете опция от менюто: ";
			cin.clear();
			cin.ignore(123, '\n');
		}
		cout << endl;

		switch (menuNumber) {
		case 1:
			system("cls");
			addPhoneMenu(phones, list);
			break;
		case 2:
			system("cls");
			showPhones(list);
			break;
		case 3:
			system("cls");
			searchAndPrintMenu(phones, list);
			break;
		case 4:
			system("cls");
			sorting(list);
			break;
		case 5:
			system("cls");
			controllFilesMenu(phones, list);
			break;
		case 6:
			system("cls");
			fetchPhonesMenu(list);
			break;
		case 7:
			system("cls");
			editPhone(list);
			break;
		case 8:
			system("cls");
			sellPhone(list);
			break;
		case 9:
			while (true) {
				cout << "Сигурни ли сте, че искате да напусние програмата? (y/n): ";
				cin >> chooice;
				if (chooice != 'y' && chooice != 'n') {
					continue;
				}
				if (chooice == 'y') {
					saveBinaryFile(list);
					cout << "Вие напуснахте програмата!" << endl;
					return;
				}
				else if (chooice == 'n') {
					chooice = 'n';
					break;
				}
			}
			break;
		default:
			cout << "Моля въведете число [1 - 9]" << endl;
			break;
		}
	} while (chooice != 'y');
}


// Меню за добавяне на телефони
void addPhoneMenu(Phone phones[100], PhonesList& list) {
	int menuNumber = 0;
	char chooice = 'x';


	cout << "1) Добавяне на един нов мобилен телефон" << endl;
	cout << "2) Добавяне на списък от мобилни телефони.Въвежда се цяло число n и след него n на брой нови мобилни телефони" << endl;
	cout << "3) Изход" << endl;

	cout << "Моля изберете опция от менюто: ";
	do {
		while (!(cin >> menuNumber)) {
			cout << "Моля изберете опция от менюто: ";
			cin.clear();
			cin.ignore(123, '\n');
		}
		switch (menuNumber)
		{
		case 1:
			system("cls");
			phoneFromInput(list);
			menu(phones, list);
			break;
		case 2:
			system("cls");
			phonesFromInput(list);
			menu(phones, list);
			break;
		case 3:
			system("cls");
			cout << "Вие напуснахте фунцкията!" << endl;
			chooice = 'y';
			menu(phones, list);
			break;
		default:
			cout << "Моля въведете число [1 - 3]: ";
			continue;
		}
	} while (chooice != 'y');
}


// Показване на наличните телефони в "базата данни"
void showPhones(PhonesList& list) {
	if (list.size == 0) {
		cout << "Базата данни е празна!" << endl << endl;
	}
	else {
		cout << setfill(' ') << setw(4) << left << "No" << setw(20) << "| МАРКА |"
			<< setw(22) << "| МОДЕЛ |"
			<< setw(18) << "| ЦВЯТ |"
			<< setw(18) << "| ЦЕНА |"
			<< setw(18) << "| ПАМЕТ |"
			<< setw(20) << "| ДИСПЕЛЙ |"
			<< setw(14) << "| DUAL SIM |"
			<< setw(15) << "| БРОЙ |"
			<< endl;
		for (int i = 0; i < list.size; i++) {
			cout << setfill(' ') << left << setw(4) << i + 1 << "| "
				<< setw(13) << list.phones[i].brand << "| "
				<< setw(15) << list.phones[i].model << left << "| "
				<< setw(12) << left << list.phones[i].color << "| "
				<< setw(12) << list.phones[i].price << "| "
				<< setw(3) << left << list.phones[i].storage << left << " GB" << setw(5) << "" << "| "
				<< setw(11) << list.phones[i].screenSize << "| "
				<< setw(14) << (list.phones[i].dualSim ? "Да" : "Не") << "| "
				<< setw(12) << list.phones[i].countFromThisPhone
				<< endl;
		}
		cout << endl;
	}
}


// Показва телефоните с най-малко памет и телефоните, които поддържат DualSIM
void searchAndPrintMenu(Phone phones[100], PhonesList list) {
	int indexOfMinStoragePhone = 0;
	int menuNumber = 0;
	char chooice = 'x';
	int n = 0;

	cout << "1) Извеждане на мобилни телефони с най - малка памет" << endl;
	cout << "2) Извеждане на мобилни телефони, работещи с две сим карти" << endl;
	cout << "3) Назад" << endl;
	cout << "Моля изберете опция от менюто: ";

	do {
		while (!(cin >> menuNumber)) {
			cout << "Моля изберете опция от менюто: ";
			cin.clear();
			cin.ignore(123, '\n');
		}
		switch (menuNumber)
		{
		case 1:
			system("cls");
			smallStorage(list);
			menu(phones, list);
			break;
		case 2:
			system("cls");
			supportDualSIM(list);
			menu(phones, list);
			break;
		case 3:
			cout << "Вие напуснахте функцията!" << endl;
			menu(phones, list);
			break;
		default:
			cout << "Моля въведете число [1 - 3]: ";
			continue;
		}
	} while (chooice != 'y');
}


// Телефони с най-малко памет
void smallStorage(PhonesList list) {
	int indexOfMinStoragePhone = 0;
	int n = 0;

	if (list.size > 0) {
		cout << "Телефоните, с най-малко памет: " << endl;
		cout << setfill(' ') << setw(4) << left << "No" << setw(20) << "| МАРКА |"
			<< setw(22) << "| МОДЕЛ |"
			<< setw(18) << "| ЦВЯТ |"
			<< setw(18) << "| ЦЕНА |"
			<< setw(18) << "| ПАМЕТ |"
			<< setw(20) << "| ДИСПЕЛЙ |"
			<< setw(14) << "| DUAL SIM |"
			<< setw(15) << "| БРОЙ |"
			<< endl;

		for (int i = 0; i < list.size; i++) {
			if (list.phones[i].storage < list.phones[indexOfMinStoragePhone].storage) {
				indexOfMinStoragePhone = i;
			}
		}

		for (int i = 0; i < list.size; i++) {
			if (list.phones[indexOfMinStoragePhone].storage == list.phones[i].storage) {
				cout << setfill(' ') << left << setw(4) << i + 1 << "| "
					<< setw(13) << list.phones[i].brand << "| "
					<< setw(15) << list.phones[i].model << left << "| "
					<< setw(12) << left << list.phones[i].color << "| "
					<< setw(12) << list.phones[i].price << "| "
					<< setw(3) << left << list.phones[i].storage << left << " GB" << setw(5) << "" << "| "
					<< setw(11) << list.phones[i].screenSize << "| "
					<< setw(14) << (list.phones[i].dualSim ? "Да" : "Не") << "| "
					<< setw(12) << list.phones[i].countFromThisPhone
					<< endl;
				n++;
			}
		}
		cout << endl;
	}
	else {
		cout << endl << "Базата данни е празна!" << endl;
	}
}


// Телефонните поддържащи DualSIM
void supportDualSIM(PhonesList list) {
	int n = 0;
	bool isHave = false;
	for (int j = 0; j < list.size; j++) {
		if (list.phones[j].dualSim == true) {
			isHave = true;
		}
	}
	if (list.size > 0 && isHave) {
		cout << "Телефоните, които поддържат Dual SIM" << endl;
		cout << setfill(' ') << setw(4) << left << "No" << setw(20) << "| МАРКА |"
			<< setw(22) << "| МОДЕЛ |"
			<< setw(18) << "| ЦВЯТ |"
			<< setw(18) << "| ЦЕНА |"
			<< setw(18) << "| ПАМЕТ |"
			<< setw(20) << "| ДИСПЕЛЙ |"
			<< setw(14) << "| DUAL SIM |"
			<< setw(15) << "| БРОЙ |"
			<< endl;
		for (int i = 0; i < list.size; i++) {
			if (list.phones[i].dualSim == true) {
				cout << setfill(' ') << left << setw(4) << i + 1 << "| "
					<< setw(13) << list.phones[i].brand << "| "
					<< setw(15) << list.phones[i].model << left << "| "
					<< setw(12) << left << list.phones[i].color << "| "
					<< setw(12) << list.phones[i].price << "| "
					<< setw(3) << left << list.phones[i].storage << left << " GB" << setw(5) << "" << "| "
					<< setw(11) << list.phones[i].screenSize << "| "
					<< setw(14) << (list.phones[i].dualSim ? "Да" : "Не") << "| "
					<< setw(12) << list.phones[i].countFromThisPhone
					<< endl;
				n++;
			}
		}
		cout << endl;
	}
	else {
		if (!isHave && list.size > 0) {
			cout << "Няма телефони, които поддържат две СИМ карти!" << endl;
		}
		else {
			cout << "Няма налични телефони!" << endl;
		}
	}
}


// Въвеждане на телефон 
void phoneFromInput(PhonesList& list) {
	if (list.size < 100) {
		string brand, model, color = "";
		double price = 0.0;
		double screenSize = 0.0;
		int storage = 0;
		bool dualSim = false;
		int countFromThisPhone = 0;

		Phone phone[100];
		cout << "Въведете марка на телефона: ";
		cin >> brand;
		cout << "Въведете модел на телефона: ";
		cin.ignore(10, '\n');
		getline(cin, model);
		cout << "Въведете цвят на телефона: ";
		cin >> color;
		cout << "Въведете цена на телефона: ";
		while (!(cin >> price)) {
			cout << "Въведете цена на телефона: ";
			cin.clear();
			cin.ignore(123, '\n');
		}
		cout << "Въведете вградената памет в (GB): ";
		while (!(cin >> storage)) {
			cout << "Въведете вградената памет в (GB): ";
			cin.clear();
			cin.ignore(123, '\n');
		}
		cout << "Въведете в размер на екрана в (inch): ";
		while (!(cin >> screenSize)) {
			cout << "Въведете в размер на екрана в (inch): ";
			cin.clear();
			cin.ignore(123, '\n');
		}

		while (true) {
			cout << "Въведете може ли да работи с две SIM карти (yes/no): ";
			string dualSimStr;
			cin >> dualSimStr;
			if (dualSimStr == "yes") {
				dualSim = true;
				break;
			}
			else if (dualSimStr == "no") {
				dualSim = false;
				break;
			}
		}
		cout << "Въведете бройка от този телефон: ";
		while (!(cin >> countFromThisPhone)) {
			cout << "Въведете бройка от този телефон: ";
			cin.clear();
			cin.ignore(123, '\n');
		}


		phone[list.size].brand = brand;
		phone[list.size].model = model;
		phone[list.size].color = color;
		phone[list.size].price = price;
		phone[list.size].storage = storage;
		phone[list.size].screenSize = screenSize;
		phone[list.size].dualSim = dualSim;
		phone[list.size].countFromThisPhone = countFromThisPhone;
		list.add(phone[list.size]);
		system("cls");
		cout << "Успеншо беше добавен " << brand << " " << model << endl;
	}
	else {
		cout << endl << "Няма достатъчно място в склада!" << endl;
	}
}


// Въвеждане на телефони
void phonesFromInput(PhonesList& list) {
	int n;
	cout << "Въведете колко телефона, желаете да добавите: ";
	cin >> n;
	cout << endl;
	if (list.size + n <= 100) {
		string brand, model, color = "";
		double price = 0.0;
		double screenSize = 0.0;
		int storage = 0;
		bool dualSim = false;
		int countFromThisPhone = 0;

		for (int i = 0; i < n; i++) {
			cout << "Въвеждане на данни за телефон № " << i + 1 << endl;
			Phone phone[100];
			cout << "Въведете марка на телефона: ";
			cin >> brand;
			cout << "Въведете модел на телефона: ";
			cin.ignore(10, '\n');
			getline(cin, model);
			cout << "Въведете цвят на телефона: ";
			cin >> color;
			cout << "Въведете цена на телефона: ";
			while (!(cin >> price)) {
				cout << "Въведете цена на телефона: ";
				cin.clear();
				cin.ignore(123, '\n');
			}
			cout << "Въведете вградената памет в (GB): ";
			while (!(cin >> storage)) {
				cout << "Въведете вградената памет в (GB): ";
				cin.clear();
				cin.ignore(123, '\n');
			}
			cout << "Въведете в размер на екрана в (inch): ";
			while (!(cin >> screenSize)) {
				cout << "Въведете в размер на екрана в (inch): ";
				cin.clear();
				cin.ignore(123, '\n');
			}
			while (true) {
				cout << "Въведете може ли да работи с две SIM карти (yes/no): ";
				string dualSimStr;
				cin >> dualSimStr;
				if (dualSimStr == "yes") {
					dualSim = true;
					break;
				}
				else if (dualSimStr == "no") {
					dualSim = false;
					break;
				}
			}
			cout << "Въведете бройка от този телефон: ";
			while (!(cin >> countFromThisPhone)) {
				cout << "Въведете бройка от този телефон: ";
				cin.clear();
				cin.ignore(123, '\n');
			}

			phone[list.size].brand = brand;
			phone[list.size].model = model;
			phone[list.size].color = color;
			phone[list.size].price = price;
			phone[list.size].storage = storage;
			phone[list.size].screenSize = screenSize;
			phone[list.size].dualSim = dualSim;
			phone[list.size].countFromThisPhone = countFromThisPhone;
			list.add(phone[list.size]);
			cout << endl;
		}
	}
	else {
		cout << endl << "Няма достатъчно място в склада!" << endl;
	}
}


// Сортиране на телефони по низходящ ред на цената
void sorting(PhonesList& list) {
	Phone tmp;

	for (int i = 0; i < list.size; i++) {
		for (int j = i + 1; j < list.size; j++) {
			if (list.phones[i].price > list.phones[j].price) {
				tmp = list.phones[i];
				list.phones[i] = list.phones[j];
				list.phones[j] = tmp;
			}
		}
	}
}


// Корекция на даден телефон
void editPhone(PhonesList& list) {
	bool isStock = false;
	PhonesList listOfPhones = list;

	string searchBrand = "";
	string searchModel = "";
	cout << "Въведете марката на телефона, който желаете да редактирате: ";
	cin >> searchBrand;
	cout << "Въведете модел на телефона: ";
	cin.ignore();
	getline(cin, searchModel);

	int index = 0;

	for (int i = 0; i < searchBrand.length(); i++) {
		if (searchBrand[i] >= 'A' && searchBrand[i] <= 'Z') {
			searchBrand[i] = searchBrand[i] + 32;
		}
	}

	for (int i = 0; i < searchModel.length(); i++) {
		if (searchModel[i] >= 'A' && searchModel[i] <= 'Z') {
			searchModel[i] = searchModel[i] + 32;
		}
	}

	for (int i = 0; i < list.size; i++) {
		for (int j = 0; j < (listOfPhones.phones[i].brand).length(); j++) {
			if (listOfPhones.phones[i].brand[j] >= 'A' && listOfPhones.phones[i].brand[j] <= 'Z') {
				listOfPhones.phones[i].brand[j] = listOfPhones.phones[i].brand[j] + 32;
			}
		}

		for (int j = 0; j < (listOfPhones.phones[i].model).length(); j++) {
			if (listOfPhones.phones[i].model[j] >= 'A' && listOfPhones.phones[i].model[j] <= 'Z') {
				listOfPhones.phones[i].model[j] = listOfPhones.phones[i].model[j] + 32;
			}
		}

		if (searchBrand == listOfPhones.phones[i].brand && searchModel == listOfPhones.phones[i].model) {
			if (listOfPhones.phones[i].countFromThisPhone > 0) {
				isStock = true;
				index = i;
				string brand, model, color = "";
				double price = 0.0;
				double screenSize = 0.0;
				int storage = 0;
				bool dualSim = false;
				int countFromThisPhone = 0;

				Phone phone[100];
				cout << endl << "Моля попълнене новите данни на телефона :)" << endl;
				cout << "Въведете марка на телефона: ";
				cin >> brand;
				cout << "Въведете модел на телефона: ";
				cin.ignore(10, '\n');
				getline(cin, model);
				cout << "Въведете цвят на телефона: ";
				cin >> color;
				cout << "Въведете цена на телефона: ";
				while (!(cin >> price)) {
					cout << "Въведете цена на телефона: ";
					cin.clear();
					cin.ignore(123, '\n');
				}

				cout << "Въведете вградената памет в (GB): ";
				while (!(cin >> storage)) {
					cout << "Въведете вградената памет в (GB): ";
					cin.clear();
					cin.ignore(123, '\n');
				}
				cout << "Въведете в размер на екрана в (screenSize): ";
				while (!(cin >> screenSize)) {
					cout << "Въведете в размер на екрана в (screenSize): ";
					cin.clear();
					cin.ignore(123, '\n');
				}

				while (true) {
					cout << "Въведете може ли да работи с две SIM карти (yes/no): ";
					string dualSimStr;
					cin >> dualSimStr;
					if (dualSimStr == "yes") {
						dualSim = true;
						break;
					}
					else if (dualSimStr == "no") {
						dualSim = false;
						break;
					}
				}
				cout << "Въведете бройка от този телефон: ";
				while (!(cin >> countFromThisPhone)) {
					cout << "Въведете бройка от този телефон: ";
					cin.clear();
					cin.ignore(123, '\n');
				}

				list.phones[index].brand = brand;
				list.phones[index].model = model;
				list.phones[index].color = color;
				list.phones[index].price = price;
				list.phones[index].storage = storage;
				list.phones[index].screenSize = screenSize;
				list.phones[index].dualSim = dualSim;
				list.phones[index].countFromThisPhone = countFromThisPhone;
				system("cls");
				cout << "Данните бяха записани в базата данни!" << endl;
				cout << endl;
				break;
			}
			else {
				cout << "От този телефон няма в наличност!" << endl;
				continue;
			}
		}
		else {
			if (isStock == false && i == list.size) {
				cout << endl << "Не съществува такъв телефон в базата данни!" << endl << endl;
				break;
			}
			else {
				continue;
			}
		}
	}
}


// Одит  на телефони 
void fetchPhonesMenu(PhonesList& list) {
	int menuNumber = 0;
	char chooice = 'x';

	do
	{
		cout << "1) Извличане на мобилни телефони по марка и сортиране по цена" << endl;
		cout << "2) Извличане на мобилни телефони по размер на екрана на телефона и сортиране по цена" << endl;
		cout << "3) Изход" << endl << endl;
		cout << "Моля изберете опция от менюто: ";
		while (!(cin >> menuNumber)) {
			cout << "Моля изберете опция от менюто: ";
			cin.clear();
			cin.ignore(123, '\n');
		}

		switch (menuNumber)
		{
		case 1:
			system("cls");
			fetchPhonesByBrand(list);
			break;
		case 2:
			system("cls");
			fetchPhonesByScreenSize(list);
			break;
		case 3:
			chooice = 'y';
			break;
		default:
			cout << "Моля въведете число [1 - 3]: ";
			continue;
		}
	} while (chooice == 'x');
}


// Извличане на телефони по марка и сортиране на цената
void fetchPhonesByBrand(PhonesList& list) {
	Phone tmp;
	PhonesList listOfPhones = list;
	PhonesList copiedArray = {};
	int count = 0;
	string searchBrand = "";

	cout << "Моля въведете марка на телефона: ";
	cin >> searchBrand;

	for (int i = 0; i < searchBrand.length(); i++) {
		if (searchBrand[i] >= 'A' && searchBrand[i] <= 'Z') {
			searchBrand[i] = searchBrand[i] + 32;
		}
	}

	for (int i = 0; i < list.size; i++) {
		for (int j = 0; j < (listOfPhones.phones[i].brand).length(); j++) {
			if (listOfPhones.phones[i].brand[j] >= 'A' && listOfPhones.phones[i].brand[j] <= 'Z') {
				listOfPhones.phones[i].brand[j] = listOfPhones.phones[i].brand[j] + 32;
			}

		}
		if (listOfPhones.phones[i].brand == searchBrand && listOfPhones.phones[i].countFromThisPhone > 0) {
			copiedArray.add(list.phones[i]);
			count++;
		}
	}

	for (int i = 0; i < copiedArray.size; i++) {
		for (int j = i + 1; j < copiedArray.size; j++) {
			if (copiedArray.phones[i].price > copiedArray.phones[j].price) {
				tmp = copiedArray.phones[i];
				copiedArray.phones[i] = copiedArray.phones[j];
				copiedArray.phones[j] = tmp;
			}
		}
	}
	if (count > 0) {

		cout << endl << setfill(' ') << setw(4) << left << "No" << setw(20) << "| МАРКА |"
			<< setw(22) << "| МОДЕЛ |"
			<< setw(18) << "| ЦВЯТ |"
			<< setw(18) << "| ЦЕНА |"
			<< setw(18) << "| ПАМЕТ |"
			<< setw(20) << "| ДИСПЕЛЙ |"
			<< setw(14) << "| DUAL SIM |"
			<< setw(15) << "| БРОЙ |"
			<< endl;
		for (int i = 0; i < copiedArray.size; i++) {
			cout << setfill(' ') << left << setw(4) << i + 1 << "| "
				<< setw(13) << copiedArray.phones[i].brand << "| "
				<< setw(15) << copiedArray.phones[i].model << left << "| "
				<< setw(12) << left << copiedArray.phones[i].color << "| "
				<< setw(12) << copiedArray.phones[i].price << "| "
				<< setw(3) << left << copiedArray.phones[i].storage << left << " GB" << setw(5) << "" << "| "
				<< setw(11) << copiedArray.phones[i].screenSize << "| "
				<< setw(14) << (copiedArray.phones[i].dualSim ? "Да" : "Не") << "| "
				<< setw(12) << copiedArray.phones[i].countFromThisPhone
				<< endl;
		}
		cout << endl;
	}
	else {
		cout << "Няма намерен телефон/и!" << searchBrand << endl;
	}
}


// Извличане на телефони по размер на екрана и сортиране на цената
void fetchPhonesByScreenSize(PhonesList& list) {
	Phone tmp;
	PhonesList listOfPhones = list;
	PhonesList copiedArray = {};
	int count = 0;

	double screenSize = 0;
	cout << "Въведи размер на екрана: ";
	while (!(cin >> screenSize)) {
		cout << "Въведи размер на екрана: ";
		cin.clear();
		cin.ignore(123, '\n');
	}
	for (int i = 0; i < list.size; i++) {
		if (screenSize == list.phones[i].screenSize) {
			copiedArray.add(list.phones[i]);
			count++;
		}
	}

	for (int i = 0; i < copiedArray.size; i++) {
		for (int j = i + 1; j < copiedArray.size; j++) {
			if (copiedArray.phones[i].price > copiedArray.phones[j].price) {
				tmp = copiedArray.phones[i];
				copiedArray.phones[i] = copiedArray.phones[j];
				copiedArray.phones[j] = tmp;
			}
		}
	}
	if (count > 0) {
		cout << "Телефони с " << screenSize << " inches размер на екрана" << endl;
		cout << endl << setfill(' ') << setw(4) << left << "No" << setw(20) << "| МАРКА |"
			<< setw(22) << "| МОДЕЛ |"
			<< setw(18) << "| ЦВЯТ |"
			<< setw(18) << "| ЦЕНА |"
			<< setw(18) << "| ПАМЕТ |"
			<< setw(20) << "| ДИСПЕЛЙ |"
			<< setw(14) << "| DUAL SIM |"
			<< setw(15) << "| БРОЙ |"
			<< endl;
		for (int i = 0; i < copiedArray.size; i++) {
			cout << setfill(' ') << left << setw(4) << i + 1 << "| "
				<< setw(13) << copiedArray.phones[i].brand << "| "
				<< setw(15) << copiedArray.phones[i].model << left << "| "
				<< setw(12) << left << copiedArray.phones[i].color << "| "
				<< setw(12) << copiedArray.phones[i].price << "| "
				<< setw(3) << left << copiedArray.phones[i].storage << left << " GB" << setw(5) << "" << "| "
				<< setw(11) << copiedArray.phones[i].screenSize << "| "
				<< setw(14) << (copiedArray.phones[i].dualSim ? "Да" : "Не") << "| "
				<< setw(12) << copiedArray.phones[i].countFromThisPhone
				<< endl;
		}
		cout << endl;

	}
	else {
		cout << "Няма телефони с такъв размер!" << endl;
	}
}


// Продажба на мобилен телефон
void sellPhone(PhonesList& list) {
	PhonesList listOfPhones = list;
	bool isStock = false;

	string searchBrand = "";
	string searchModel = "";
	cout << "Въведете марката на телефона: ";
	cin >> searchBrand;
	cout << "Въведете модел на телефона: ";
	cin.ignore();
	getline(cin, searchModel);


	for (int i = 0; i < searchBrand.length(); i++) {
		if (searchBrand[i] >= 'A' && searchBrand[i] <= 'Z') {
			searchBrand[i] = searchBrand[i] + 32;
		}
	}

	for (int i = 0; i < searchModel.length(); i++) {
		if (searchModel[i] >= 'A' && searchModel[i] <= 'Z') {
			searchModel[i] = searchModel[i] + 32;
		}
	}

	for (int i = 0; i < list.size; i++) {
		for (int j = 0; j < (listOfPhones.phones[i].brand).length(); j++) {
			if (listOfPhones.phones[i].brand[j] >= 'A' && listOfPhones.phones[i].brand[j] <= 'Z') {
				listOfPhones.phones[i].brand[j] = listOfPhones.phones[i].brand[j] + 32;
			}
		}

		for (int j = 0; j < (listOfPhones.phones[i].model).length(); j++) {
			if (listOfPhones.phones[i].model[j] >= 'A' && listOfPhones.phones[i].model[j] <= 'Z') {
				listOfPhones.phones[i].model[j] = listOfPhones.phones[i].model[j] + 32;
			}
		}

		if (searchBrand == listOfPhones.phones[i].brand && searchModel == listOfPhones.phones[i].model && list.phones[i].countFromThisPhone > 0) {
			if (list.phones[i].countFromThisPhone > 0) {
				list.phones[i].countFromThisPhone--;
				isStock = true;
				cout << endl << "Беше продаден телефон: " << list.phones[i].brand << " " << list.phones[i].model << endl << endl;
			}
			else {
				cout << endl << "В момента не е наличен " << list.phones[i].brand << " " << list.phones[i].model << endl;
			}
		}
		else {
			if (isStock == false && i + 1 == list.size) {
				cout << endl << "Не съществува такъв телефон в базата данни!" << endl << endl;
				break;
			}
			else {
				continue;
			}
		}
	}
}


// Меню за управление на файлове
void controllFilesMenu(Phone phones[100], PhonesList& list) {
	int menuNumber = 0;
	char chooice = 'x';

	cout << "1) Извеждане на масива с мобилни телефони във файл (текстов)" << endl;
	cout << "2) Въвеждане на масива с мобилни телефони от файл (текстов)" << endl;
	cout << "3) Изход" << endl;

	cout << "Моля изберете опция от менюто: ";
	do {
		while (!(cin >> menuNumber)) {
			cout << "Моля изберете опция от менюто: ";
			cin.clear();
			cin.ignore(123, '\n');
		}
		switch (menuNumber)
		{
		case 1:
			system("cls");
			printOnTextFile(list);
			menu(phones, list);
			break;
		case 2:
			system("cls");
			readFromTextFile(list);
			menu(phones, list);
			break;
		case 3:
			cout << "Вие напуснахте фунцкията!" << endl;
			chooice = 'y';
			menu(phones, list);
			break;
		default:
			cout << "Моля въведете число [1 - 3]: ";
			continue;
		}
	} while (chooice != 'y');
	cout << endl;
}


// Отпечатване на текстов файл
void printOnTextFile(PhonesList& list) {
	ofstream savePhones(file);

	if (savePhones.is_open()) {
		for (int i = 0; i < list.size; i++) {
			savePhones << list.phones[i].brand << endl;
			savePhones << list.phones[i].model << endl;
			savePhones << list.phones[i].color << endl;
			savePhones << list.phones[i].price << endl;
			savePhones << list.phones[i].storage << endl;
			savePhones << list.phones[i].screenSize << endl;
			savePhones << list.phones[i].dualSim << endl;
			savePhones << list.phones[i].countFromThisPhone << endl;
		}
		cout << endl << "Файлът беше успешно запазен!" << endl;
	}
	else {
		cout << endl << "Възникна грешка!" << endl;
	}
}


// Четене от текстов файл
void readFromTextFile(PhonesList& list) {
	ifstream readPhones;
	Phone phone;

	readPhones.open("telefoni.txt");
	if (!readPhones.is_open())
	{
		cout << "\nВъзникна грешка при отварянето на файла!";
		return;
	}

	string brand, model, color = "";
	int storage = 0;
	bool dualSim = false;
	int countFromThisPhone = 0;
	double screenSize = 0;
	double price = 0;
	int i = 0;

	while (!readPhones.eof()) {
		getline(readPhones >> ws, brand);
		getline(readPhones >> ws, model);
		getline(readPhones >> ws, color);
		readPhones >> price;
		readPhones >> storage;
		readPhones >> screenSize;
		readPhones >> dualSim;
		readPhones >> countFromThisPhone;

		phone.brand = brand;
		phone.model = model;
		phone.color = color;
		phone.price = price;
		phone.storage = storage;
		phone.screenSize = screenSize;
		phone.dualSim = dualSim;
		phone.countFromThisPhone = countFromThisPhone;
		if (readPhones.eof()) {
			return;
		}
		i++;
		list.add(phone);
		list.size = i;
	}
	readPhones.close();
	cout << endl << "Файлът е успешно зареден!" << endl;
}


// Записване на двоичен файл
void saveBinaryFile(PhonesList& list) {
	fstream file;
	file.open(binFile, ios::out | ios::binary);

	if (file.fail()) {
		cout << endl << "Възникна грешка!" << endl;
		exit(1);
	}
	file.write((char*)list.phones, sizeof(Phone) * list.size);
	file.close();
	cout << endl << "Файлът беше успешно запазен!" << endl;
}


// Зареждане от двоичен файл
void loadBinaryFile(PhonesList& list) {
	fstream file;
	file.open(binFile, ios::binary | ios::in);
	Phone phone;
	if (file.fail()) {
		cout << endl << "Не беше намерен файл database.dat !" << endl;
		exit(1);
	}
	file.seekg(0l, ios::end);
	long pos = file.tellg() / (sizeof(Phone));
	file.close();

	file.open(binFile, ios::binary | ios::in);
	if (file.fail()) {
		cout << endl << "Не беше намерен файл database.dat !" << endl;
		exit(1);
	}
	file.read((char*)list.phones, sizeof(Phone) * pos);
	file.close();
	cout << "Файлът беше успешно зареден!" << endl << endl;
}